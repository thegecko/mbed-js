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

#ifndef __JSMBED_WRAP_FUNCTION_MAILMAN_H__
#define __JSMBED_WRAP_FUNCTION_MAILMAN_H__

#include "jerry-core/jerry.h"

#include "jsmbed_wrap_log_macros.h"

enum CallbackAction {
  INVALID,
  CALL,
  CALL_1ARG,
  RELEASE,
  ERROR_CORRUPT_JS_CALLBACK
};

typedef struct {
  jerry_object_t *function;
  CallbackAction action;
  jerry_value_t arg1_value;
} callback_message;

/*
 * This class stores a jerry_object_t, that represents
 * the function that should be executed from the main event loop
 * when some C++ class that uses callbacks calls post_call_callback_msg.
 *
 * This class is responsible for posting messages to the main
 * event loop indicating that the associated jerry_object_t should
 * be called or released.
 */
class JSFunctionMailman
{
public:
  JSFunctionMailman() : javascript_function(NULL)
  {
    LOG_PRINT("[MAILMAN] CONSTRUCTOR 0x%x\n", this);
  }

  ~JSFunctionMailman()
  {
    LOG_PRINT("[MAILMAN] DESTRUCTOR 0x%x\n", this);
    post_release_callback_msg();
    LOG_PRINT("[MAILMAN] DESTRUCTOR-COMPLETE\n");
  }

  void set_post_function(jerry_object_t *f)
  {
    LOG_PRINT("[MAILMAN] SET-POST 0x%x\n", f);
    post_release_callback_msg();
    javascript_function = f;
    LOG_PRINT("[MAILMAN] SET-POST-COMPLETE 0x%x\n", f);
  }

  void unset_post_function()
  {
    LOG_PRINT("[MAILMAN] UNSET-POST\n");
    post_release_callback_msg();
    javascript_function = NULL;
    LOG_PRINT("[MAILMAN] UNSET-POST-COMPLETE\n");
  }

  void post_call_callback_msg();
  void post_call_callback_msg_1arg(jerry_value_t arg);
  void post_call_callback_msg_string_arg(void* string_arg);

private:
  void post_release_callback_msg();

  jerry_object_t *javascript_function;
};


#endif
