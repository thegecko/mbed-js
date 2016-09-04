#!/bin/bash
set -e

DOCKER_IMAGE=mbed/mbed-js
MBED_USER=mbed_user
MBED_GROUP=mbed_group
MBED_HOME=/mbed_home

USER_ID=$(id -u)
GROUP_ID=$(id -g)

PARAMS="$PARAMS -it --rm"
PARAMS="$PARAMS -v $PWD:$MBED_HOME"
PARAMS="$PARAMS -w $MBED_HOME"

run_mbed()
{
  echo \
    groupadd -f -g $GROUP_ID $MBED_GROUP '&&' \
    useradd -u $USER_ID -g $MBED_GROUP $MBED_USER '&&' \
    chown -R $MBED_USER:$MBED_GROUP $MBED_HOME '&&' \
    chown -R $MBED_USER:$MBED_GROUP /workspace '&&' \
    sudo -u $MBED_USER HOME=$MBED_HOME mbed-js
}

if [ -z "$DOCKER_HOST" ]; then
    eval docker run $PARAMS $DOCKER_IMAGE /bin/bash -ci "'$(run_mbed) $@'"
else
    eval docker run $PARAMS $DOCKER_IMAGE mbed-js $@
fi
