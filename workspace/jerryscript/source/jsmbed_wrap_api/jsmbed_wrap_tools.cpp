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

#include <stdlib.h>
#include <stdio.h>

#include "jsmbed_wrap_tools.h"

bool
jsmbed_wrap_register_global_function (const char* name,
                          jerry_external_handler_t handler)
{
  jerry_object_t *global_obj_p;
  jerry_object_t *reg_func_p;
  jerry_value_t reg_value;
  bool bok;

  global_obj_p = jerry_get_global ();
  reg_func_p = jerry_create_external_function (handler);

  if (!(reg_func_p != NULL
      && jerry_is_function (reg_func_p)
      && jerry_is_constructor (reg_func_p)))
  {
    printf ("Error: register_global_function failed: [%s]\r\n", name);
    jerry_release_object (global_obj_p);
    return false;
  }

  jerry_acquire_object (reg_func_p);
  reg_value.type = JERRY_DATA_TYPE_OBJECT;
  reg_value.u.v_object = reg_func_p;

  bok = jerry_set_object_field_value (global_obj_p,
                                          (jerry_char_t *) name,
                                          &reg_value);

  jerry_release_value (&reg_value);
  jerry_release_object (reg_func_p);
  jerry_release_object (global_obj_p);

  if (!bok)
  {
    printf ("Error: register_global_function failed: [%s]\r\n", name);
  }

  return bok;
}

bool
jsmbed_wrap_register_class_constructor (const char* name,
                          jerry_external_handler_t handler)
{
  // Register class constructor as a global function
  return jsmbed_wrap_register_global_function(name, handler);
}

bool
jsmbed_wrap_register_class_function (jerry_object_t* this_obj_p,
                         const char* name,
                         jerry_external_handler_t handler)
{
  jerry_object_t *reg_func_p;
  jerry_value_t reg_value;
  bool bok;

  reg_func_p = jerry_create_external_function (handler);

  if (!(reg_func_p != NULL
      && jerry_is_function (reg_func_p)
      && jerry_is_constructor (reg_func_p)))
  {
    printf ("Error: create_external_function failed !!!\r\n");
    return false;
  }

  jerry_acquire_object (reg_func_p);
  reg_value.type = JERRY_DATA_TYPE_OBJECT;
  reg_value.u.v_object = reg_func_p;

  bok = jerry_set_object_field_value (this_obj_p,
                                          (jerry_char_t *) name,
                                          &reg_value);

  jerry_release_value (&reg_value);
  jerry_release_object (reg_func_p);

  if (!bok)
  {
    printf ("Error: register_class_function failed: [%s]\r\n", name);
  }

  return bok;
}
