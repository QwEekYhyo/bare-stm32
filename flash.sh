#!/bin/bash

STLINK_CONFIG=/usr/share/openocd/scripts/interface/stlink.cfg
MCU_CONFIG=/usr/share/openocd/scripts/target/stm32g4x.cfg

display_help() {
    echo "USAGE:"
    echo "    $(basename $0) <binary>"
}

BINARY_PATH=$1

if [ -z $BINARY_PATH ]; then
    display_help
    exit 1
fi

openocd \
    -f $STLINK_CONFIG \
    -f $MCU_CONFIG \
    -c "program $BINARY_PATH verify reset exit"
