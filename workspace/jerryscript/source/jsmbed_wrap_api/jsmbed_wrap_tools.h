/* Copyright 2015 Samsung Electronics Co., Ltd.
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

#ifndef __JSMBED_WRAP_TOOLS_H__
#define __JSMBED_WRAP_TOOLS_H__

#include <stdlib.h>

#include "jerry-core/jerry.h"

#include "jsmbed_wrap_name_macros.h"

//
// 1. Wrapper registration macros
//

/*
 * Used in header/source files for wrappers, to declare the signature of the
 * registration function.
 */
#define DECLARE_JS_WRAPPER_REGISTRATION(NAME) \
  void jsmbed_wrap_registry_entry__ ## NAME (void)

//
// 2. Wrapper function declaration/use macros
//

// Global functions
#define DECLARE_GLOBAL_FUNCTION(NAME) \
bool \
NAME_FOR_GLOBAL_FUNCTION(NAME) (const jerry_object_t * function_obj_p, \
                  const jerry_value_t *  this_p, \
                  jerry_value_t *        ret_val_p, \
                  const jerry_value_t    args_p[], \
                  const jerry_length_t   args_count)

#define REGISTER_GLOBAL_FUNCTION(NAME) \
  jsmbed_wrap_register_global_function ( # NAME, NAME_FOR_GLOBAL_FUNCTION(NAME) )

// Class constructors
#define DECLARE_CLASS_CONSTRUCTOR(CLASS) \
bool \
NAME_FOR_CLASS_CONSTRUCTOR(CLASS) (const jerry_object_t * function_obj_p, \
                  const jerry_value_t *  this_p, \
                  jerry_value_t *        ret_val_p, \
                  const jerry_value_t    args_p[], \
                  const jerry_length_t   args_count)

#define REGISTER_CLASS_CONSTRUCTOR(CLASS) \
  jsmbed_wrap_register_class_constructor ( # CLASS, NAME_FOR_CLASS_CONSTRUCTOR(CLASS) )

// Class functions
#define DECLARE_CLASS_FUNCTION(CLASS, NAME) \
bool \
NAME_FOR_CLASS_FUNCTION(CLASS, NAME) (const jerry_object_t * function_obj_p, \
                  const jerry_value_t *  this_p, \
                  jerry_value_t *        ret_val_p, \
                  const jerry_value_t    args_p[], \
                  const jerry_length_t   args_count)

#define ATTACH_CLASS_FUNCTION(OBJECT, CLASS, NAME) \
  jsmbed_wrap_register_class_function (OBJECT, # NAME, NAME_FOR_CLASS_FUNCTION(CLASS, NAME) )

//
// 3. Argument checking macros
//
#define CHECK_ARGUMENT_COUNT(CLASS, NAME, EXPR) \
  if (!(EXPR)) \
  { \
    printf("ERROR: wrong argument count for %s.%s, expected %s.\n", # CLASS, # NAME, # EXPR ); \
    return false; \
  }

#define CHECK_ARGUMENT_TYPE_ALWAYS(CLASS, NAME, INDEX, TYPE) \
  if (!jsmbed_wrap_value_is_ ## TYPE (&args_p[INDEX])) \
  { \
    printf("ERROR: wrong argument type for %s.%s, expected argument %d to be a %s.\n", # CLASS, # NAME, INDEX, # TYPE); \
    return false; \
  }

#define CHECK_ARGUMENT_TYPE_ON_CONDITION(CLASS, NAME, INDEX, TYPE, EXPR) \
  if ((EXPR)) \
  { \
    if (!jsmbed_wrap_value_is_ ## TYPE (&args_p[INDEX])) \
    { \
      printf("ERROR: wrong argument type for %s.%s, expected argument %d to be a %s.\n", # CLASS, # NAME, INDEX, # TYPE); \
      return false; \
    } \
  }

//
// Type checkers
//
inline bool jsmbed_wrap_value_is_object(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_OBJECT);
}
inline bool jsmbed_wrap_value_is_string(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_STRING);
}
inline bool jsmbed_wrap_value_is_uint32(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_UINT32);
}
inline bool jsmbed_wrap_value_is_float32(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_FLOAT32);
}
inline bool jsmbed_wrap_value_is_float64(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_FLOAT64);
}
inline bool jsmbed_wrap_value_is_boolean(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_BOOLEAN);
}
inline bool jsmbed_wrap_value_is_null(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_NULL);
}
inline bool jsmbed_wrap_value_is_undefined(const jerry_value_t* val_p)
{
  return ((val_p)->type == JERRY_DATA_TYPE_UNDEFINED);
}
inline bool jsmbed_wrap_value_is_number(const jerry_value_t* val_p)
{
  return (((val_p)->type == JERRY_DATA_TYPE_UINT32)
    || ((val_p)->type == JERRY_DATA_TYPE_FLOAT64)
    || ((val_p)->type == JERRY_DATA_TYPE_FLOAT32));
}

//
// Value unboxers
//
inline jerry_object_t *jsmbed_wrap_unbox_object(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_object(val_p))
  {
    return val_p->u.v_object;
  }
  printf("ERROR: Attempted to get object from non-object bearing value: 0x%p\n", val_p);
  return NULL;
}
inline jerry_string_t *jsmbed_wrap_unbox_string(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_string(val_p))
  {
    return val_p->u.v_string;
  }
  printf("ERROR: Attempted to get string from non-string bearing value: 0x%p\n", val_p);
  return NULL;
}
inline uint32_t jsmbed_wrap_unbox_uint32(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_uint32(val_p))
  {
    return val_p->u.v_uint32;
  }
  printf("ERROR: Attempted to get uint32 from non-uint32 bearing value: 0x%p\n", val_p);
  return 0;
}
inline float jsmbed_wrap_unbox_float32(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_float32(val_p))
  {
    return val_p->u.v_float32;
  }
  printf("ERROR: Attempted to get float32 from non-float32 bearing value: 0x%p\n", val_p);
  return 0.0f;
}
inline double jsmbed_wrap_unbox_float64(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_float64(val_p))
  {
    return val_p->u.v_float64;
  }
  printf("ERROR: Attempted to get float64 from non-float64 bearing value: 0x%p\n", val_p);
  return 0.0;
}
inline double jsmbed_wrap_unbox_number(const jerry_value_t* val_p)
{
  return ( jsmbed_wrap_value_is_float64(val_p) ?
    jsmbed_wrap_unbox_float64(val_p) :
    (jsmbed_wrap_value_is_float32(val_p) ?
     static_cast<double>(jsmbed_wrap_unbox_float32(val_p)) :
     static_cast<double>(jsmbed_wrap_unbox_uint32(val_p))) );
}
inline bool jsmbed_wrap_unbox_boolean(const jerry_value_t* val_p)
{
  if (jsmbed_wrap_value_is_boolean(val_p))
  {
    return val_p->u.v_bool;
  }
  printf("ERROR: Attempted to get boolean from non-boolean bearing value: 0x%p\n", val_p);
  return false;
}

//
// Extras
//
inline bool jsmbed_wrap_value_is_function(const jerry_value_t* val_p)
{
  return jerry_is_function(jsmbed_wrap_unbox_object(val_p));
}

inline void jsmbed_wrap_acquire_object(jerry_object_t* obj_p)
{
  jerry_acquire_object(obj_p);
}

inline void jsmbed_wrap_release_object(jerry_object_t* obj_p)
{
  jerry_release_object(obj_p);
}

inline jerry_object_t *jsmbed_wrap_create_object()
{
  return jerry_create_object();
}

inline void jsmbed_wrap_link_objects(jerry_object_t *js_obj, uintptr_t native_obj, void (*free_function)(uintptr_t))
{
  jerry_set_object_native_handle(js_obj, native_obj, (jerry_object_free_callback_t) free_function);
}

inline uintptr_t jsmbed_wrap_get_native_handle(const jerry_value_t *val_p)
{
  uintptr_t handle;
  if (!jsmbed_wrap_value_is_object(val_p))
  {
    printf("ERROR: Cannot get native handle from non-object-bearing value.\n");
    return 0;
  }
  if (!jerry_get_object_native_handle(val_p->u.v_object, &handle))
  {
    printf("ERROR: Failed to get handle from supposedly natively-mapped object.\n");
    return 0;
  }
  return handle;
}

inline void jsmbed_wrap_box_undefined(jerry_value_t *val_p)
{
  val_p->type = JERRY_DATA_TYPE_UNDEFINED;
}
inline void jsmbed_wrap_box_object(jerry_value_t *val_p, jerry_object_t *v)
{
  val_p->type = JERRY_DATA_TYPE_OBJECT;
  val_p->u.v_object = v;
}
inline void jsmbed_wrap_box_string(jerry_value_t *val_p, jerry_string_t *v)
{
  val_p->type = JERRY_DATA_TYPE_STRING;
  val_p->u.v_string = v;
}
inline void jsmbed_wrap_box_uint32(jerry_value_t *val_p, uint32_t v)
{
  val_p->type = JERRY_DATA_TYPE_UINT32;
  val_p->u.v_uint32 = v;
}
inline void jsmbed_wrap_box_boolean(jerry_value_t *val_p, bool v)
{
  val_p->type = JERRY_DATA_TYPE_BOOLEAN;
  val_p->u.v_bool = v;
}

inline int jsmbed_wrap_get_array_length(const jerry_value_t *val_p)
{
  jerry_object_t *data_array = jsmbed_wrap_unbox_object(val_p);
  jerry_value_t length_value;
  jerry_get_object_field_value(data_array, (const unsigned char*) "length", &length_value);
  return jsmbed_wrap_unbox_number(&length_value);
}

// NB: Delete the char array when you're done with it!
inline char* jsmbed_wrap_alloc_same_sized_char_array(const jerry_value_t *val_p)
{
  int array_length = jsmbed_wrap_get_array_length(val_p);
  char *data = (char*) malloc(sizeof(char) * array_length);
  return data;
}

inline void jsmbed_wrap_copy_char_array_to_js_array(jerry_value_t *js_array, char *array)
{
  jerry_value_t out_value;
  int array_length = jsmbed_wrap_get_array_length(js_array);
  jerry_object_t *array_object = jsmbed_wrap_unbox_object(js_array);
  for (int index = 0; index < array_length; index++)
  {
    // This first bit is probably redundant.
    jerry_get_array_index_value(array_object, index, &out_value);
    jsmbed_wrap_box_uint32(&out_value, array[index]);
    jerry_set_array_index_value(array_object, index, &out_value);
  }
}

inline void jsmbed_wrap_copy_char_array_from_js_array(char *array, const jerry_value_t *js_array)
{
  jerry_value_t out_value;
  int array_length = jsmbed_wrap_get_array_length(js_array);
  jerry_object_t *array_object = jsmbed_wrap_unbox_object(js_array);
  for (int index = 0; index < array_length; index++)
  {
    jerry_get_array_index_value(array_object, index, &out_value);
    array[index] = jsmbed_wrap_unbox_number(&out_value);
  }
}

inline void jsmbed_wrap_delete_char_array(char *array)
{
  free(array);
}

inline char* jsmbed_wrap_alloc_and_copy_string_from_js_string(jerry_string_t *js_string)
{
  jerry_size_t string_size = jerry_get_string_size(js_string);
  char *char_buffer = (char*) calloc(string_size + 1, sizeof(char));
  jerry_string_to_char_buffer(js_string, (jerry_char_t*) char_buffer, string_size);
  return char_buffer;
}

inline jerry_string_t *jsmbed_wrap_create_string(const char* native_string)
{
  return jerry_create_string((const jerry_char_t *) native_string);
}

// This is not to be relied upon!!
inline int _jsmbed_wrap_get_object_ref_count(jerry_object_t *obj_p)
{
  return (int) (((*((uint16_t*)obj_p)) >> 6) & 0x3FF);
}

//
// Functions used by the wrapper registration API.
//

bool
jsmbed_wrap_register_global_function (const char* name,
                          jerry_external_handler_t handler);

bool
jsmbed_wrap_register_class_constructor (const char* name,
                            jerry_external_handler_t handler);

bool
jsmbed_wrap_register_class_function (jerry_object_t* this_obj_p,
                         const char* name,
                         jerry_external_handler_t handler);

#endif
