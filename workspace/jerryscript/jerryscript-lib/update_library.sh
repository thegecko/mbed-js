# Copyright (c) 2015 ARM Limited. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#!/bin/bash

BOARD=k64f
COMMIT=""
HEAP_SIZE=16
UPDATE=false

while [ "$1" ]; do
  case "$1" in
  -b | --board)
    BOARD="$2"
    shift 2
    ;;
  -c | --commit)
    COMMIT="$2"
    shift 2
    ;;
  -h | --help)
    echo "update_library.sh"
    echo "-b, --board BOARD: select build for this board (supported values: k64f)"
    echo "-c, --commit COMMIT: change jerryscript build to commit COMMIT"
    echo "-h, --help: this help"
    echo "-s, --heap-size SIZE: set jerry's heap size to SIZE KB"
    echo "-u, --update: use latest master of jerryscript, update version file"
    exit 0
    ;;
  -s | --heap-size)
    HEAP_SIZE="$2"
    shift 2
    ;;
  -u | --update)
    UPDATE=true
    shift
    ;;
  esac
done

if [[ ${UPDATE} == true && "${COMMIT}" != "" ]]; then
  echo "Cannot use -u and -c together."
  exit 1
fi

FROZEN_COMMIT=$(grep commit version | sed 's/commit //')

rm -rf lib
rm -rf include

if [[ ! -d .jerryscript ]]; then
  git clone https://github.com/samsung/jerryscript .jerryscript
  cd .jerryscript
  if [[ "${COMMIT}" == "" ]]; then
    git checkout ${FROZEN_COMMIT}
  else
    git checkout ${COMMIT}
  fi
  cd ..
fi

if [[ ${UPDATE} == true ]]; then
  cd .jerryscript
  git checkout master
  git pull
  git log -1 > ../version
  cd ..
fi

if [[ "${COMMIT}" != "" ]]; then
  cd .jerryscript
  git checkout ${COMMIT}
  cd ..
fi

cd .jerryscript
make -f targets/mbed/Makefile.mbed board=${BOARD} JERRYHEAP=${HEAP_SIZE} jerry
cd ..

mkdir lib
cp .jerryscript/targets/mbed/libjerry/* lib

mkdir include
cp .jerryscript/jerry-core include -R
cd include
find . -not -iname "*.h" -and -not -type d -delete
cd ..
