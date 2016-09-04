#!/bin/bash

cjsc index.js -o /workspace/js/main.js && cd /workspace/ && js2c && mbed-cli compile -t GCC_ARM -m $1 && mv .build/$1/GCC_ARM/workspace.bin /mbed_home/mbed-js.bin
