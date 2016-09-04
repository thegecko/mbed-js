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

#ifndef __JSMBED_WRAP_REGISTRY_H__
#define __JSMBED_WRAP_REGISTRY_H__

/*
 * Before jsmbed_js_launch is used in a program, this macro should be
 * called to register any wrappers that will be used by the JavaScript program.
 *
 * For example
 * int main()
 * {
 *   JSMBED_USE_WRAPPER(base);
 *   JSMBED_USE_WRAPPER(lwip_interface);
 *   JSMBED_USE_WRAPPER(simple_mbed_client);
 *   jsmbed_js_launch();
 *   return 0;
 * }
 */
#define JSMBED_USE_WRAPPER(NAME) \
  jsmbed_wrap_register_wrapper(jsmbed_wrap_registry_entry__ ## NAME)

void jsmbed_wrap_register_all_functions (void);

void jsmbed_wrap_register_wrapper (void (*wrapper)(void));

#endif
