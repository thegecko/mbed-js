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

#ifndef __JSMBED_WRAP_NAME_MACROS_H__
#define __JSMBED_WRAP_NAME_MACROS_H__

#define NAME_FOR_GLOBAL_FUNCTION(NAME) __gen_jsmbed_global_func_ ## NAME
#define NAME_FOR_CLASS_CONSTRUCTOR(CLASS) __gen_jsmbed_class_constructor_ ## CLASS
#define NAME_FOR_CLASS_FUNCTION(CLASS, NAME) __gen_jsmbed_func_c_ ## CLASS ## _f_ ## NAME

#define NAME_FOR_CLASS_NATIVE_CONSTRUCTOR(CLASS, TYPELIST) __gen_native_jsmbed_ ## CLASS ## __Special_create_ ## TYPELIST
#define NAME_FOR_CLASS_NATIVE_DESTRUCTOR(CLASS) __gen_native_jsmbed_ ## CLASS ## __Special_destroy
#define NAME_FOR_CLASS_NATIVE_FUNCTION(CLASS, NAME) __gen_native_jsmbed_ ## CLASS ## _ ## NAME

#endif
