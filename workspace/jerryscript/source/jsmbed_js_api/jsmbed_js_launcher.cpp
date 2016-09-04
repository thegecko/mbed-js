/* Copyright 2014-2015 Samsung Electronics Co., Ltd.
 * Copyright (c) 2016 ARM Limited. All rights reserved.
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

#include "mbed.h"
#include "rtos.h"

#include "jerry-core/jerry.h"

#include "jsmbed_js_jerrycall.h"
#include "jsmbed_js_source.h"

#include "jsmbed_wrap_function_mailman.h"

#include "jsmbed_js_launcher.h"

extern struct jsmbed_js_source_t jsmbed_js_code_storage[];

static int load_javascript (void)
{
  int retcode;
  int src;

  /* run main.js */
  retcode = jsmbed_js_entry (jsmbed_js_code_storage[0].source, jsmbed_js_code_storage[0].length);
  if (retcode != 0)
  {
    LOG_PRINT_ALWAYS ("js_entry failed code(%d) [%s]\r\n", retcode, jsmbed_js_code_storage[0].name);
    jsmbed_js_exit ();
    return -1;
  }

  /* run rest of the js files */
  for (src = 1; jsmbed_js_code_storage[src].source; src++)
  {
    retcode = jsmbed_js_eval (jsmbed_js_code_storage[src].source, jsmbed_js_code_storage[src].length);
    if (retcode != 0)
    {
      LOG_PRINT_ALWAYS ("js_eval failed code(%d) [%s]\r\n", retcode, jsmbed_js_code_storage[src].name);
      jsmbed_js_exit ();
      return -2;
    }
  }

  return 0;
}

Mail<callback_message, 16> jsmbed_js_callback_mailbox;

void jsmbed_js_launch (void)
{
  LOG_PRINT_ALWAYS ("\r\nJerryScript in mbed 2.5\r\n");
  LOG_PRINT_ALWAYS ("   build  %s\r\n", jerry_build_date);
  LOG_PRINT_ALWAYS ("   hash   %s\r\n", jerry_commit_hash);
  LOG_PRINT_ALWAYS ("   branch %s\r\n", jerry_branch_name);

  if (load_javascript() == 0)
  {
    while (true)
    {
      osEvent evt = jsmbed_js_callback_mailbox.get(0);
      if (evt.status == osEventMail)
      {
        callback_message *msg = (callback_message*) evt.value.p;

        jerry_object_t *function = msg->function;

        if (msg->action == CALL || msg->action == CALL_1ARG)
        {
          LOG_PRINT("[EVENT LOOP] CALL 0x%p\n", function);

          // Create a new value and put the callback function object into it.
          jerry_value_t function_value;
          function_value.type = JERRY_DATA_TYPE_OBJECT;
          function_value.u.v_object = function;

          bool problem_in_execution;

          if (msg->action == CALL)
          {
            problem_in_execution = jsmbed_js_exec_function(&function_value, NULL, 0);
          }
          else if (msg->action == CALL_1ARG)
          {
            jerry_value_t args[1];
            args[0] = msg->arg1_value;
            problem_in_execution = jsmbed_js_exec_function(&function_value, args, 1);

            // This value was created for a callback. Now delete it.
            jerry_release_value(&msg->arg1_value);
          }

          if (problem_in_execution)
          {
            LOG_PRINT_ALWAYS("[EVENT LOOP] CALL ERROR\n");
            exit(1);
          }

          LOG_PRINT("[EVENT LOOP] CALL-COMPLETE 0x%p\n", function);
        }
        else if (msg->action == RELEASE)
        {
          LOG_PRINT("[EVENT LOOP] RELEASE 0x%p\n", function);
          jerry_release_object(function);
          LOG_PRINT("[EVENT LOOP] RELEASE-COMPLETE 0x%p\n", function);
        }
        else if (msg->action == ERROR_CORRUPT_JS_CALLBACK)
        {
          LOG_PRINT_ALWAYS("[EVENT LOOP] ERROR: JS_CALLBACK WAS CORRUPT: 0x%p\n", function);
          exit(1);
        }
        else
        {
          LOG_PRINT_ALWAYS("[EVENT LOOP] UNHANDLED CALLBACK MESSAGE!");
        }

        jsmbed_js_callback_mailbox.free(msg);
      }
    }
  }
}
