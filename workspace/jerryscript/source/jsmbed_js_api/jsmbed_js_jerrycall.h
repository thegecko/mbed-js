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

#ifndef __JSMBED_JS_JERRYCALL_H__
#define __JSMBED_JS_JERRYCALL_H__

#include "jerry-core/jerry.h"

int jsmbed_js_entry (const char *source_p, const size_t source_size);
int jsmbed_js_eval (const char *source_p, const size_t source_size);
int jsmbed_js_exec_function (jerry_value_t *func_to_exec, jerry_value_t *args, int arg_count);
void jsmbed_js_exit (void);

#endif
