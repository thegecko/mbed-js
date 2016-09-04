jerryscript
===

Integration between jerryscript and mbed. Comprised of three major components.
These components are:

1. `jsmbed_js` - an API for launching a JavaScript engine in your program.
   First create a `struct jsmbed_js_source_t` array called
   `jsmbed_js_code_storage`, and populate with your source code. Then call
   `jsmbed_js_launch()` to start executing JavaScript. Any wrappers that are
   needed within JavaScript code must be pre-registered calling
   `JSMBED_USE_WRAPPER(name)` before launching the JS engine. The header file
   that includes the `DECLARE_JS_WRAPPER_REGISTRATION` line for the wrapper
   must also be included in your source file. The code for this component can
   be found in `source/jsmbed_js_api`.

2. `jsmbed_wrap` - an API that wrappers can use for hooking into jerryscript, and a large
   number of functions that can be used for frequent operations. The wrapper
   API can be found in `source/jsmbed_wrap_api`, with most functionality
   implemented in `source/jsmbed_wrap_api/jsmbed_wrap_tools.h`.

3. A package of wrappers for the common classes defined in the mbed HAL API,
   A.K.A, the "base" wrapper package. This package can be found in
   `source/pkgjsmbed_base`.

Starting the JS engine will execute the initial entry in the
`jsmbed_js_code_storage` array as the entry point, eval the rest of the
entries, and then loop, waiting for callbacks from Ticker or InterruptIn
objects.

See https://github.com/ARMmbed/javascript-app for example usage.

Supported Classes
===

DigitalOut
I2C
Ticker
InterruptIn

Debugging Info
===

Define `DEBUG_WRAPPER` to print out debugging info from the event loop and wrappers.