jerryscript-lib
===

A library that packages the core jerryscript engine.

Currently this just clones samsung/jerryscript, builds the external library
version of jerry-core and jerry-libm, as targets/mbed does, and then copies the
relevant libraries and headers into this project.

To update your version of jerryscript, run update\_library.sh.

The 'version' file contains the commit seen at the tip of the jerryscript repo
when the library was built. This is automatically updated by update\_library.sh.
