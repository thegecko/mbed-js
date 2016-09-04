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

#include "jsmbed_wrap_tools.h"
#include "pkgjsmbed_base_native.h"
#include "pkgjsmbed_base_wrapper.h"

DECLARE_GLOBAL_FUNCTION(assert)
{
  CHECK_ARGUMENT_COUNT(global, assert, (args_count == 1));
  CHECK_ARGUMENT_TYPE_ALWAYS(global, assert, 0, boolean);

  if (!jsmbed_wrap_unbox_boolean(&args_p[0]))
  {
    printf("ERROR: Script assertion failed\n");
    exit(1);
    return false;
  }

  return true;
}

DECLARE_GLOBAL_FUNCTION(gc)
{
  jerry_gc();
  return true;
}

//
// DigitalOut
//
DECLARE_CLASS_FUNCTION(DigitalOut, write)
{
  CHECK_ARGUMENT_COUNT(DigitalOut, write, (args_count == 1));
  CHECK_ARGUMENT_TYPE_ALWAYS(DigitalOut, write, 0, number);
  int value = jsmbed_wrap_unbox_number(&args_p[0]);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, write)(native_handle, value);
  return true;
}

DECLARE_CLASS_FUNCTION(DigitalOut, read)
{
  CHECK_ARGUMENT_COUNT(DigitalOut, read, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  int result = NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, read)(native_handle);
  jsmbed_wrap_box_uint32(ret_val_p, result);
  return true;
}

DECLARE_CLASS_FUNCTION(DigitalOut, is_connected)
{
  CHECK_ARGUMENT_COUNT(DigitalOut, is_connected, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  int result = NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, is_connected)(native_handle);
  jsmbed_wrap_box_uint32(ret_val_p, result);
  return true;
}


DECLARE_CLASS_CONSTRUCTOR(DigitalOut)
{
  CHECK_ARGUMENT_COUNT(DigitalOut, __constructor, (args_count == 1 || args_count == 2));
  CHECK_ARGUMENT_TYPE_ALWAYS(DigitalOut, __constructor, 0, number);
  CHECK_ARGUMENT_TYPE_ON_CONDITION(DigitalOut, __constructor, 1, number, (args_count == 2));

  int pin = jsmbed_wrap_unbox_number(&args_p[0]);
  uintptr_t native_handle;

  if (args_count == 1)
  {
    native_handle = NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I) (pin);
  }
  if (args_count == 2)
  {
    int value = jsmbed_wrap_unbox_number(&args_p[1]);
    native_handle = NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I_I) (pin, value);
  }

  jerry_object_t *js_object = jsmbed_wrap_create_object();
  jsmbed_wrap_link_objects(js_object, native_handle, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(DigitalOut));
  ATTACH_CLASS_FUNCTION(js_object, DigitalOut, write);
  ATTACH_CLASS_FUNCTION(js_object, DigitalOut, read);
  ATTACH_CLASS_FUNCTION(js_object, DigitalOut, is_connected);

  jsmbed_wrap_box_object(ret_val_p, js_object);
  return true;
}

//
// I2C
//
DECLARE_CLASS_FUNCTION(I2C, frequency)
{
  CHECK_ARGUMENT_COUNT(Ticker, frequency, (args_count == 1));
  CHECK_ARGUMENT_TYPE_ALWAYS(Ticker, frequency, 0, number);
  int hz = jsmbed_wrap_unbox_number(&args_p[0]);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, frequency)(native_handle, hz);
  return true;
}

DECLARE_CLASS_FUNCTION(I2C, read)
{
  if (args_count == 1)
  {
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, read, 0, number);
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    int data = jsmbed_wrap_unbox_number(&args_p[0]);
    int result = NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I)(native_handle, data);
    jsmbed_wrap_box_uint32(ret_val_p, result);
    return true;
  }
  else if (args_count == 3 || args_count == 4)
  {
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, read, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, read, 1, object);
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, read, 2, number);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(I2C, read, 3, boolean, (args_count == 4));
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    int address = jsmbed_wrap_unbox_number(&args_p[0]);
    char *data = jsmbed_wrap_alloc_same_sized_char_array(&args_p[1]);
    int length = jsmbed_wrap_unbox_number(&args_p[2]);
    bool repeated = false;
    if (args_count == 4)
    {
      repeated = jsmbed_wrap_unbox_boolean(&args_p[3]);
    }

    int result = NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I_PC_I_B)
        (native_handle, address, data, length, repeated);
    jsmbed_wrap_box_uint32(ret_val_p, result);

    // Have to cast because we are intentionally modifying this argument.
    jsmbed_wrap_copy_char_array_to_js_array((jerry_value_t*) &args_p[1], data);

    jsmbed_wrap_delete_char_array(data);

    return true;
  }
  printf("ERROR: Unexpected number of arguments to I2C.read, expected 1, 3 or 4.");
  return false;
}

DECLARE_CLASS_FUNCTION(I2C, write)
{
  if (args_count == 1)
  {
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, write, 0, number);
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    int data = jsmbed_wrap_unbox_number(&args_p[0]);
    int result = NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I)(native_handle, data);
    jsmbed_wrap_box_uint32(ret_val_p, result);
    return true;
  }
  else if (args_count == 3 || args_count == 4)
  {
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, write, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, write, 1, object);
    CHECK_ARGUMENT_TYPE_ALWAYS(I2C, write, 2, number);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(I2C, write, 3, boolean, (args_count == 4));
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    int address = jsmbed_wrap_unbox_number(&args_p[0]);
    char *data = jsmbed_wrap_alloc_same_sized_char_array(&args_p[1]);
    jsmbed_wrap_copy_char_array_from_js_array(data, &args_p[1]);
    int length = jsmbed_wrap_unbox_number(&args_p[2]);
    bool repeated = false;
    if (args_count == 4)
    {
      repeated = jsmbed_wrap_unbox_boolean(&args_p[3]);
    }

    int result = NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I_KPC_I_B)
        (native_handle, address, (const char*) data, length, repeated);
    jsmbed_wrap_box_uint32(ret_val_p, result);

    jsmbed_wrap_delete_char_array(data);

    return true;
  }
  printf("ERROR: Unexpected number of arguments to I2C.write, expected 1, 3 or 4.");
  return false;
}

DECLARE_CLASS_FUNCTION(I2C, start)
{
  CHECK_ARGUMENT_COUNT(I2C, start, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, start)(native_handle);
  return true;
}

DECLARE_CLASS_FUNCTION(I2C, stop)
{
  CHECK_ARGUMENT_COUNT(I2C, stop, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, stop)(native_handle);
  return true;
}

DECLARE_CLASS_CONSTRUCTOR(I2C)
{
  CHECK_ARGUMENT_COUNT(I2C, __constructor, (args_count == 2));
  CHECK_ARGUMENT_TYPE_ALWAYS(I2C, __constructor, 0, number);
  CHECK_ARGUMENT_TYPE_ALWAYS(I2C, __constructor, 1, number);

  int sda = jsmbed_wrap_unbox_number(&args_p[0]);
  int scl = jsmbed_wrap_unbox_number(&args_p[1]);

  uintptr_t native_handle = NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(I2C, I_I) (sda, scl);

  jerry_object_t *js_object = jsmbed_wrap_create_object();
  jsmbed_wrap_link_objects(js_object, native_handle, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(I2C));
  ATTACH_CLASS_FUNCTION(js_object, I2C, frequency);
  ATTACH_CLASS_FUNCTION(js_object, I2C, read);
  ATTACH_CLASS_FUNCTION(js_object, I2C, write);
  ATTACH_CLASS_FUNCTION(js_object, I2C, start);
  ATTACH_CLASS_FUNCTION(js_object, I2C, stop);

  jsmbed_wrap_box_object(ret_val_p, js_object);
  return true;
}

//
// Ticker
//
DECLARE_CLASS_FUNCTION(Ticker, attach)
{
  CHECK_ARGUMENT_COUNT(Ticker, attach, (args_count == 2));
  CHECK_ARGUMENT_TYPE_ALWAYS(Ticker, attach, 0, function);
  CHECK_ARGUMENT_TYPE_ALWAYS(Ticker, attach, 1, number);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  jerry_object_t *fptr = jsmbed_wrap_unbox_object(&args_p[0]);
  jsmbed_wrap_acquire_object(fptr);
  float t = jsmbed_wrap_unbox_number(&args_p[1]);
  NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach) (native_handle, fptr, t);
  return true;
}

DECLARE_CLASS_FUNCTION(Ticker, attach_us)
{
  CHECK_ARGUMENT_COUNT(Ticker, attach_us, (args_count == 2));
  CHECK_ARGUMENT_TYPE_ALWAYS(Ticker, attach_us, 0, function);
  CHECK_ARGUMENT_TYPE_ALWAYS(Ticker, attach_us, 1, number);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  jerry_object_t *fptr = jsmbed_wrap_unbox_object(&args_p[0]);
  jsmbed_wrap_acquire_object(fptr);
  int t = jsmbed_wrap_unbox_number(&args_p[1]);
  NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach_us) (native_handle, fptr, t);
  return true;
}

DECLARE_CLASS_FUNCTION(Ticker, detach)
{
  CHECK_ARGUMENT_COUNT(Ticker, detach, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, detach)(native_handle);
  return true;
}

DECLARE_CLASS_CONSTRUCTOR(Ticker)
{
  CHECK_ARGUMENT_COUNT(Ticker, __constructor, (args_count == 0));

  uintptr_t native_handle = NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(Ticker, _) ();

  jerry_object_t *js_object = jsmbed_wrap_create_object();
  jsmbed_wrap_link_objects(js_object, native_handle, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Ticker));
  ATTACH_CLASS_FUNCTION(js_object, Ticker, attach);
  ATTACH_CLASS_FUNCTION(js_object, Ticker, attach_us);
  ATTACH_CLASS_FUNCTION(js_object, Ticker, detach);

  jsmbed_wrap_box_object(ret_val_p, js_object);
  return true;
}

//
// InterruptIn
//
DECLARE_CLASS_FUNCTION(InterruptIn, rise)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, rise, (args_count == 1));
  // Special case for rise(null), which means "detach the rise callback"
  if (jsmbed_wrap_value_is_null(&args_p[1]))
  {
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, rise) (native_handle, NULL);
    return true;
  }

  // Assuming we actually have a callback now...
  CHECK_ARGUMENT_TYPE_ALWAYS(InterruptIn, rise, 0, function);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  jerry_object_t *fptr = jsmbed_wrap_unbox_object(&args_p[0]);
  jsmbed_wrap_acquire_object(fptr);
  NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, rise) (native_handle, fptr);
  return true;
}

DECLARE_CLASS_FUNCTION(InterruptIn, fall)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, fall, (args_count == 1));
  // Special case for fall(null), which means "detach the fall callback"
  if (jsmbed_wrap_value_is_null(&args_p[1]))
  {
    uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
    NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, fall) (native_handle, NULL);
    return true;
  }

  // Assuming we actually have a callback now...
  CHECK_ARGUMENT_TYPE_ALWAYS(InterruptIn, fall, 0, function);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  jerry_object_t *fptr = jsmbed_wrap_unbox_object(&args_p[0]);
  jsmbed_wrap_acquire_object(fptr);
  NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, fall) (native_handle, fptr);
  return true;
}

DECLARE_CLASS_FUNCTION(InterruptIn, mode)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, mode, (args_count == 1));
  CHECK_ARGUMENT_TYPE_ALWAYS(InterruptIn, mode, 0, number);
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  int pull = jsmbed_wrap_unbox_number(&args_p[0]);
  NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, mode) (native_handle, pull);
  return true;
}

DECLARE_CLASS_FUNCTION(InterruptIn, disable_irq)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, disable_irq, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, disable_irq) (native_handle);
  return true;
}

DECLARE_CLASS_FUNCTION(InterruptIn, enable_irq)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, enable_irq, (args_count == 0));
  uintptr_t native_handle = jsmbed_wrap_get_native_handle(this_p);
  NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, enable_irq) (native_handle);
  return true;
}

DECLARE_CLASS_CONSTRUCTOR(InterruptIn)
{
  CHECK_ARGUMENT_COUNT(InterruptIn, __constructor, (args_count == 1));
  CHECK_ARGUMENT_TYPE_ALWAYS(InterruptIn, __constructor, 0, number);
  int pin = jsmbed_wrap_unbox_number(&args_p[0]);
  uintptr_t native_handle = NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(InterruptIn, I) (pin);
  jerry_object_t *js_object = jsmbed_wrap_create_object();
  jsmbed_wrap_link_objects(js_object, native_handle, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(InterruptIn));
  ATTACH_CLASS_FUNCTION(js_object, InterruptIn, rise);
  ATTACH_CLASS_FUNCTION(js_object, InterruptIn, fall);
  ATTACH_CLASS_FUNCTION(js_object, InterruptIn, mode);
  ATTACH_CLASS_FUNCTION(js_object, InterruptIn, enable_irq);
  ATTACH_CLASS_FUNCTION(js_object, InterruptIn, disable_irq);
  jsmbed_wrap_box_object(ret_val_p, js_object);
  return true;
}

DECLARE_JS_WRAPPER_REGISTRATION (base)
{
  REGISTER_GLOBAL_FUNCTION (assert);
  REGISTER_GLOBAL_FUNCTION (gc);
  REGISTER_CLASS_CONSTRUCTOR (DigitalOut);
  REGISTER_CLASS_CONSTRUCTOR (I2C);
  REGISTER_CLASS_CONSTRUCTOR (Ticker);
  REGISTER_CLASS_CONSTRUCTOR (InterruptIn);
}
