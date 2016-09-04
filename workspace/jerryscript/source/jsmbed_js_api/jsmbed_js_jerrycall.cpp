/* Copyright 2014-2015 Samsung Electronics Co., Ltd.
 * Copyright 2016 University of Szeged.
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

#include <stdlib.h>
#include <stdio.h>

// For jsmbed_wrap_register_all_functions
#include "jsmbed_wrap_registry.h"

#include "jsmbed_js_jerrycall.h"

extern unsigned int jsmbed_js_magic_string_count;
extern const char *jsmbed_js_magic_strings[];
extern unsigned int jsmbed_js_magic_string_lengths[];
extern unsigned int jsmbed_js_magic_string_values[];

static void jsmbed_js_load_magic_strings()
{
  if (jsmbed_js_magic_string_count == 0)
  {
    return;
  }

  jerry_register_external_magic_strings((const jerry_char_ptr_t*) jsmbed_js_magic_strings,
      (uint32_t) jsmbed_js_magic_string_count,
      (const jerry_length_t*) jsmbed_js_magic_string_lengths);

  jerry_object_t *global = jerry_get_global();

  jerry_value_t constant_value;
  constant_value.type = JERRY_DATA_TYPE_UINT32;

  for (int idx = 0; idx < jsmbed_js_magic_string_count; idx++)
  {
    constant_value.u.v_uint32 = jsmbed_js_magic_string_values[idx];
    jerry_set_object_field_value(global, (const jerry_char_t*) jsmbed_js_magic_strings[idx], &constant_value);
  }

  jerry_release_object(global);
}

int jsmbed_js_entry (const char *source_p, const size_t source_size)
{
  const jerry_char_t *jerry_src = (const jerry_char_t *) source_p;
  jerry_completion_code_t ret_code = JERRY_COMPLETION_CODE_OK;
  jerry_flag_t flags = JERRY_FLAG_EMPTY;
  jerry_object_t *err_obj_p = NULL;
  jerry_value_t err_value = jerry_create_void_value ();

  jerry_init (flags);

  jsmbed_js_load_magic_strings ();
  jsmbed_wrap_register_all_functions ();

  if (!jerry_parse (jerry_src, source_size, &err_obj_p))
  {
    printf ("Error: jerry_parse failed\r\n");
    ret_code = JERRY_COMPLETION_CODE_UNHANDLED_EXCEPTION;
    jerry_release_object (err_obj_p);
  }
  else
  {
    if ((flags & JERRY_FLAG_PARSE_ONLY) == 0)
    {
      ret_code = jerry_run (&err_value);
      jerry_string_t *err_str_p = NULL;
      if (err_obj_p != NULL)
      {
        jerry_value_t err_value = jerry_create_object_value (err_obj_p);
        err_str_p = jerry_value_to_string (&err_value);
        jerry_release_object (err_obj_p);
      }
      else if (!jerry_value_is_void (&err_value))
      {
        err_str_p = jerry_value_to_string (&err_value);
        jerry_release_value (&err_value);
      }
      if (err_str_p != NULL)
      {
        jerry_release_string (err_str_p);
      }
    }
  }

  return ret_code;
}

int jsmbed_js_eval (const char *source_p, const size_t source_size)
{
  jerry_completion_code_t status;
  jerry_value_t res;

  status = jerry_eval ((jerry_char_t *) source_p,
                           source_size,
                           false,
                           false,
                           &res);

  jerry_release_value (&res);

  return status;
}

int jsmbed_js_exec_function (jerry_value_t *func_to_exec, jerry_value_t *args, int arg_count)
{
  jerry_object_t *global_obj_p;

  global_obj_p = jerry_get_global ();
  if (!jerry_is_function (func_to_exec->u.v_object))
  {
    printf ("Error: callback is not a function!\r\n");
    jerry_release_object (global_obj_p);
    return -2;
  }

  bool is_ok;
  jerry_value_t res;

  is_ok = jerry_call_function (func_to_exec->u.v_object,
                                   global_obj_p,
                                   &res,
                                   args,
                                   arg_count);

  jerry_release_value (&res);

  jerry_release_object (global_obj_p);

  return (is_ok ? 0 : 1);
}

void jsmbed_js_exit (void)
{
  jerry_cleanup ();
}
