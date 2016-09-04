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

#include <stdio.h>

#include "jsmbed_wrap_registry.h"

static const int jsmbed_wrap_registry_max_size = 64;
static int jsmbed_wrap_registry_count = 0;
static void (*jsmbed_wrap_registry_table[jsmbed_wrap_registry_max_size])(void) = { 0 };

void jsmbed_wrap_register_all_functions (void)
{
  for (int idx = 0; idx < jsmbed_wrap_registry_count; idx++)
  {
    (*jsmbed_wrap_registry_table[idx])();
  }
}

void jsmbed_wrap_register_wrapper (void (*wrapper)(void))
{
  if (jsmbed_wrap_registry_count < jsmbed_wrap_registry_max_size)
  {
    jsmbed_wrap_registry_table[jsmbed_wrap_registry_count] = wrapper;
    jsmbed_wrap_registry_count++;
  }
  else
  {
    printf("Currently limited to %d wrapper libraries being registered, so ignoring this one.\n",
        jsmbed_wrap_registry_max_size);
  }
}
