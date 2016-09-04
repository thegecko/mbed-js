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

#ifndef __PKGJSMBED_BASE_NATIVE_H__
#define __PKGJSMBED_BASE_NATIVE_H__

#include "jerry-core/jerry.h"
#include "jsmbed_wrap_name_macros.h"

// DigitalOut
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I_I) (int pin, int value);
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(DigitalOut, I) (int pin);
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(DigitalOut) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, write) (uintptr_t handle, int value);
int NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, read) (uintptr_t handle);
int NAME_FOR_CLASS_NATIVE_FUNCTION(DigitalOut, is_connected) (uintptr_t handle);

// I2C
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(I2C, I_I) (int sda, int scl);
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(I2C) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, frequency) (uintptr_t handle, int hz);
int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I_PC_I_B)
    (uintptr_t handle, int address, char *data, int length, bool repeated);
int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, read_I) (uintptr_t handle, int ack);
int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I_KPC_I_B)
    (uintptr_t handle, int address, const char *data, int length, bool repeated);
int NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, write_I) (uintptr_t handle, int data);
void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, start) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(I2C, stop) (uintptr_t handle);

// Ticker
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(Ticker, _) ();
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Ticker) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach) (uintptr_t handle, jerry_object_t* fptr, float t);
void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, attach_us) (uintptr_t handle, jerry_object_t* fptr, int t);
void NAME_FOR_CLASS_NATIVE_FUNCTION(Ticker, detach) (uintptr_t handle);

// InterruptIn
uintptr_t NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(InterruptIn, I) (int pin);
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(InterruptIn) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, rise) (uintptr_t handle, jerry_object_t *fptr);
void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, fall) (uintptr_t handle, jerry_object_t *fptr);
void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, mode) (uintptr_t handle, int pull);
void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, disable_irq) (uintptr_t handle);
void NAME_FOR_CLASS_NATIVE_FUNCTION(InterruptIn, enable_irq) (uintptr_t handle);

#endif
