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

// Provides jsmbed_js_launch()
#include "jsmbed_js_launcher.h"

// Provides JSMBED_USE_WRAPPER()
#include "jsmbed_wrap_registry.h"

// Provides the base wrapper registration symbol that JSMBED_USE_WRAPPER uses.
// This means all of the base handlers will be registered.
#include "pkgjsmbed_base_wrapper.h"

int main() {
  JSMBED_USE_WRAPPER(base);
  // Incude more wrapper packages here if you want to use them. For exmaple:
  //JSMBED_USE_WRAPPER(lwip_interface);
  //JSMBED_USE_WRAPPER(esp8266_interface);
  //JSMBED_USE_WRAPPER(simple_mbed_client);
  jsmbed_js_launch();
  return 0;
}