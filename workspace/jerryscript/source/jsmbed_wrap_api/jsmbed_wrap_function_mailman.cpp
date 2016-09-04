/* Copyright (c) 2016 ARM Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>

#include "mbed.h"
#include "rtos.h"

#include "jsmbed_wrap_function_mailman.h"

extern Mail<callback_message, 16> jsmbed_js_callback_mailbox;

// !!! - Called in ISR code - !!!
//  = No printf.
void JSFunctionMailman::post_call_callback_msg()
{
  if (javascript_function != NULL)
  {
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = javascript_function;
    msg->action = CALL;
    jsmbed_js_callback_mailbox.put(msg);
  }
  else
  {
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = NULL;
    msg->action = ERROR_CORRUPT_JS_CALLBACK;
    jsmbed_js_callback_mailbox.put(msg);
  }
}

// !!! - Called in ISR code - !!!
//  = No printf.
void JSFunctionMailman::post_call_callback_msg_1arg(jerry_value_t arg)
{
  if (javascript_function != NULL)
  {
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = javascript_function;
    msg->action = CALL_1ARG;
    msg->arg1_value = arg;
    jsmbed_js_callback_mailbox.put(msg);
  }
  else
  {
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = NULL;
    msg->action = ERROR_CORRUPT_JS_CALLBACK;
    jsmbed_js_callback_mailbox.put(msg);
  }
}

// !!! - Called in ISR code - !!!
//  = No printf.
void JSFunctionMailman::post_call_callback_msg_string_arg(void* string_arg)
{
  if (javascript_function == NULL)
  {
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = NULL;
    msg->action = ERROR_CORRUPT_JS_CALLBACK;
    jsmbed_js_callback_mailbox.put(msg);
    return;
  }

  // Convert to jerry string, and use the function above for posting the callback.
  // Not 100% sure if we're safe to use the API always here.
  jerry_string_t * js_string = jerry_create_string((jerry_char_t*) ((std::string*) string_arg)->c_str());
  jerry_value_t js_string_val;
  js_string_val.type = JERRY_DATA_TYPE_STRING;
  js_string_val.u.v_string = js_string;

  post_call_callback_msg_1arg(js_string_val);
}

void JSFunctionMailman::post_release_callback_msg()
{
  // Only need to delete the function if we got one.
  if (javascript_function != NULL)
  {
    LOG_PRINT("[MAILMAN] POST-RELEASE 0x%x\n", javascript_function);
    callback_message *msg = jsmbed_js_callback_mailbox.alloc();
    msg->function = javascript_function;
    msg->action = RELEASE;
    jsmbed_js_callback_mailbox.put(msg);
    LOG_PRINT("[MAILMAN] POST-RELEASE-COMPLETE\n");
  }
}
