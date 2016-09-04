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

#include "jsmbed_wrap_function_mailman.h"
#include "jsmbed_wrap_log_macros.h"
#include "jsmbed_wrap_name_macros.h"

#include "pkgjsmbed_base_native.h"

uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I_I) (int pin, int value)
{
  uintptr_t handle = (uintptr_t) new DigitalOut((PinName) pin, value);
  LOG_PRINT("[WRAPPER] CREATE DigitalOut 0x%x (0x%x) - %d %d\n", handle, *((uint32_t*)handle), pin, value);
  return handle;
}

uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I) (int pin)
{
  uintptr_t handle = (uintptr_t) new DigitalOut((PinName) pin);
  LOG_PRINT("[WRAPPER] CREATE DigitalOut 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), pin);
  return handle;
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(DigitalOut) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] DESTROY DigitalOut 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  delete (DigitalOut*) handle;
  LOG_PRINT("[WRAPPER] DESTROY-COMPLETE DigitalOut\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, write) (uintptr_t handle, int value)
{
  LOG_PRINT("[WRAPPER] CALL DigitalOut.write 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), value);
  ((DigitalOut*) handle)->write(value);
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, read) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL DigitalOut.read 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  int retval = ((DigitalOut*) handle)->read();
  LOG_PRINT("[WRAPPER] RETURN DigitalOut.read 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, is_connected) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL DigitalOut.is_connected 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  int retval = ((DigitalOut*) handle)->is_connected();
  LOG_PRINT("[WRAPPER] RETURN DigitalOut.is_connected 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

//
// - I2C ---
//
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(I2C, I_I) (int sda, int scl)
{
  uintptr_t handle = (uintptr_t) new I2C((PinName) sda, (PinName) scl);
  LOG_PRINT("[WRAPPER] CREATE I2C 0x%x (0x%x) - %d %d\n", handle, *((uint32_t*)handle), sda, scl);
  return handle;
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(I2C) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] DESTROY I2C 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  delete (I2C*) handle;
  LOG_PRINT("[WRAPPER] DESTROY-COMPLETE I2C\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, frequency) (uintptr_t handle, int hz)
{
  LOG_PRINT("[WRAPPER] CALL I2C.frequency 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), hz);
  ((I2C*) handle)->frequency(hz);
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I_PC_I_B)
    (uintptr_t handle, int address, char *data, int length, bool repeated)
{
  LOG_PRINT("[WRAPPER] CALL I2C.read 0x%x (0x%x) - %d 0x%x %d %d\n", handle, *((uint32_t*)handle), address, data, length, repeated);
  int retval = ((I2C*) handle)->read(address, data, length, repeated);
  LOG_PRINT("[WRAPPER] RETURN I2C.read 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I) (uintptr_t handle, int ack)
{
  LOG_PRINT("[WRAPPER] CALL I2C.read 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), ack);
  int retval = ((I2C*) handle)->read(ack);
  LOG_PRINT("[WRAPPER] RETURN I2C.read 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I_KPC_I_B)
    (uintptr_t handle, int address, const char *data, int length, bool repeated)
{
  LOG_PRINT("[WRAPPER] CALL I2C.write 0x%x (0x%x) - %d 0x%x %d %d\n", handle, *((uint32_t*)handle), address, data, length, repeated);
  int retval = ((I2C*) handle)->write(address, data, length, repeated);
  LOG_PRINT("[WRAPPER] RETURN I2C.write 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I) (uintptr_t handle, int data)
{
  LOG_PRINT("[WRAPPER] CALL I2C.write 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), data);
  int retval = ((I2C*) handle)->write(data);
  LOG_PRINT("[WRAPPER] RETURN I2C.write 0x%x (0x%x) ==> %d\n", handle, *((uint32_t*)handle), retval);
  return retval;
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, start) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL I2C.start 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((I2C*) handle)->start();
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, stop) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL I2C.stop 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((I2C*) handle)->stop();
}


//
// - Ticker ---
//
class WrappedTicker : public Ticker
{
public:
  WrappedTicker() :
    mailman_for_attach(new JSFunctionMailman())
  {
    LOG_PRINT("[WRAPPER] CONSTRUCTOR WrappedTicker 0x%x (0x%x)\n", this, *((uint32_t*)this));
  }

  ~WrappedTicker()
  {
    LOG_PRINT("[WRAPPER] DESTRUCTOR WrappedTicker 0x%x (0x%x)\n", this, *((uint32_t*)this));
    delete mailman_for_attach;
    LOG_PRINT("[WRAPPER] DESTRUCTOR-COMPLETE WrappedTicker\n");
  }

  void set_attach_callback(jerry_object_t *f)
  {
    LOG_PRINT("[WRAPPER] SET-CALLBACK WrappedTicker.attach 0x%x (0x%x) - 0x%x\n", this, *((uint32_t*)this), f);
    mailman_for_attach->set_post_function(f);
    LOG_PRINT("[WRAPPER] SET-CALLBACK-COMPLETE WrappedTicker.attach\n");
  }

  void unset_attach_callback()
  {
    LOG_PRINT("[WRAPPER] UNSET-CALLBACK WrappedTicker.attach 0x%x (0x%x)\n", this, *((uint32_t*)this));
    mailman_for_attach->unset_post_function();
    LOG_PRINT("[WRAPPER] SET-CALLBACK-COMPLETE WrappedTicker.attach\n");
  }

  JSFunctionMailman *get_attach_mailman()
  {
    return mailman_for_attach;
  }

private:
  JSFunctionMailman *mailman_for_attach;
};

uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(Ticker, _) ()
{
  LOG_PRINT("[WRAPPER] CREATE Ticker\n");
  uintptr_t handle = (uintptr_t) new WrappedTicker();
  LOG_PRINT("[WRAPPER] CREATE-COMPLETE Ticker 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  return handle;
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Ticker) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] DESTROY Ticker 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((WrappedTicker*) handle)->detach();
  delete (WrappedTicker*) handle;
  LOG_PRINT("[WRAPPER] DESTROY-COMPLETE Ticker\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach) (uintptr_t handle, jerry_object_t* fptr, float t)
{
  LOG_PRINT("[WRAPPER] CALL Ticker.attach 0x%x (0x%x) - 0x%x %f\n", handle, *((uint32_t*)handle), fptr, t);
  WrappedTicker *this_ticker = (WrappedTicker*) handle;
  this_ticker->set_attach_callback(fptr);
  this_ticker->attach(this_ticker->get_attach_mailman(),
    (void (JSFunctionMailman::*)(void)) &JSFunctionMailman::post_call_callback_msg,
    t);
  LOG_PRINT("[WRAPPER] CALL-COMPLETE Ticker.attach\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach_us) (uintptr_t handle, jerry_object_t* fptr, int t)
{
  LOG_PRINT("[WRAPPER] CALL Ticker.attach_us 0x%x (0x%x) - 0x%x %d\n", handle, *((uint32_t*)handle), fptr, t);
  WrappedTicker *this_ticker = (WrappedTicker*) handle;
  this_ticker->set_attach_callback(fptr);
  this_ticker->attach_us(this_ticker->get_attach_mailman(),
    (void (JSFunctionMailman::*)(void)) &JSFunctionMailman::post_call_callback_msg,
    (timestamp_t) t);
  LOG_PRINT("[WRAPPER] CALL-COMPLETE Ticker.attach_us\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, detach) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL Ticker.detach 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  WrappedTicker *this_ticker = (WrappedTicker*) handle;
  this_ticker->unset_attach_callback();
  this_ticker->detach();
  LOG_PRINT("[WRAPPER] CALL-COMPLETE Ticker.detach\n");
}

//
// - InterruptIn ---
//
class WrappedInterruptIn : public InterruptIn
{
public:
  WrappedInterruptIn(PinName pin) :
    InterruptIn(pin),
    mailman_for_rise(new JSFunctionMailman()),
    mailman_for_fall(new JSFunctionMailman())
  {
    LOG_PRINT("[WRAPPER] CONSTRUCTOR WrappedInterruptIn 0x%x (0x%x) - %d\n", this, *((uint32_t*)this), pin);
  }

  ~WrappedInterruptIn()
  {
    LOG_PRINT("[WRAPPER] DESTRUCTOR WrappedInterruptIn 0x%x (0x%x)\n", this, *((uint32_t*)this));
    delete mailman_for_rise;
    delete mailman_for_fall;
    LOG_PRINT("[WRAPPER] DESTRUCTOR-COMPLETE WrappedInterruptIn\n");
  }

  void set_rise_callback(jerry_object_t *f)
  {
    LOG_PRINT("[WRAPPER] SET-CALLBACK WrappedInterruptIn.rise 0x%x (0x%x) - 0x%x\n", this, *((uint32_t*)this), f);
    mailman_for_rise->set_post_function(f);
    LOG_PRINT("[WRAPPER] SET-CALLBACK-COMPLETE WrappedInterruptIn.rise\n");
  }

  void unset_rise_callback()
  {
    LOG_PRINT("[WRAPPER] UNSET-CALLBACK WrappedInterruptIn.rise 0x%x (0x%x)\n", this, *((uint32_t*)this));
    mailman_for_rise->unset_post_function();
    LOG_PRINT("[WRAPPER] UNSET-CALLBACK-COMPLETE WrappedInterruptIn.rise\n");
  }

  void set_fall_callback(jerry_object_t *f)
  {
    LOG_PRINT("[WRAPPER] SET-CALLBACK WrappedInterruptIn.fall 0x%x (0x%x) - 0x%x\n", this, *((uint32_t*)this), f);
    mailman_for_fall->set_post_function(f);
    LOG_PRINT("[WRAPPER] SET-CALLBACK-COMPLETE WrappedInterruptIn.fall\n");
  }

  void unset_fall_callback()
  {
    LOG_PRINT("[WRAPPER] UNSET-CALLBACK WrappedInterruptIn.fall 0x%x (0x%x)\n", this, *((uint32_t*)this));
    mailman_for_fall->unset_post_function();
    LOG_PRINT("[WRAPPER] UNSET-CALLBACK-COMPLETE WrappedInterruptIn.fall\n");
  }

  JSFunctionMailman *get_rise_mailman()
  {
    return mailman_for_rise;
  }

  JSFunctionMailman *get_fall_mailman()
  {
    return mailman_for_fall;
  }

private:
  JSFunctionMailman *mailman_for_rise;
  JSFunctionMailman *mailman_for_fall;
};

uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(InterruptIn, I) (int pin)
{
  LOG_PRINT("[WRAPPER] CREATE InterruptIn\n");
  uintptr_t handle = (uintptr_t) new WrappedInterruptIn((PinName) pin);
  LOG_PRINT("[WRAPPER] CREATE-COMPLETE InterruptIn 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), pin);
  return handle;
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(InterruptIn) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] DESTROY InterruptIn 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((WrappedInterruptIn*) handle)->rise(0);
  ((WrappedInterruptIn*) handle)->fall(0);
  delete (WrappedInterruptIn*) handle;
  LOG_PRINT("[WRAPPER] DESTROY-COMPLETE InterruptIn\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, rise) (uintptr_t handle, jerry_object_t *fptr)
{
  LOG_PRINT("[WRAPPER] CALL InterruptIn.rise 0x%x (0x%x) - 0x%x\n", handle, *((uint32_t*)handle), fptr);
  WrappedInterruptIn *this_interruptin = (WrappedInterruptIn*) handle;

  if (fptr != 0)
  {
    this_interruptin->set_rise_callback(fptr);
    this_interruptin->rise(this_interruptin->get_rise_mailman(),
      (void (JSFunctionMailman::*)(void)) &JSFunctionMailman::post_call_callback_msg);
  }
  else
  {
    this_interruptin->unset_rise_callback();
    this_interruptin->rise(0);
  }
  LOG_PRINT("[WRAPPER] CALL-COMPLETE InterruptIn.rise\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, fall) (uintptr_t handle, jerry_object_t *fptr)
{
  LOG_PRINT("[WRAPPER] CALL InterruptIn.fall 0x%x (0x%x) - 0x%x\n", handle, *((uint32_t*)handle), fptr);
  WrappedInterruptIn *this_interruptin = (WrappedInterruptIn*) handle;

  if (fptr != 0)
  {
    this_interruptin->set_fall_callback(fptr);
    this_interruptin->fall(this_interruptin->get_fall_mailman(),
      (void (JSFunctionMailman::*)(void)) &JSFunctionMailman::post_call_callback_msg);
  }
  else
  {
    this_interruptin->unset_fall_callback();
    this_interruptin->fall(0);
  }
  LOG_PRINT("[WRAPPER] CALL-COMPLETE InterruptIn.fall\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, mode) (uintptr_t handle, int pull)
{
  LOG_PRINT("[WRAPPER] CALL InterruptIn.mode 0x%x (0x%x) - %d\n", handle, *((uint32_t*)handle), pull);
  ((InterruptIn*) handle)->mode((PinMode) pull);
  LOG_PRINT("[WRAPPER] CALL-COMPLETE InterruptIn.mode\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, disable_irq) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL InterruptIn.disable_irq 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((InterruptIn*) handle)->disable_irq();
  LOG_PRINT("[WRAPPER] CALL-COMPLETE InterruptIn.disable_irq\n");
}

void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, enable_irq) (uintptr_t handle)
{
  LOG_PRINT("[WRAPPER] CALL InterruptIn.enable_irq 0x%x (0x%x)\n", handle, *((uint32_t*)handle));
  ((InterruptIn*) handle)->enable_irq();
  LOG_PRINT("[WRAPPER] CALL-COMPLETE InterruptIn.enable_irq\n");
}
