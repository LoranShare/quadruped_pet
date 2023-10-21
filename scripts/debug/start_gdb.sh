#!/bin/bash

arm-none-eabi-gdb -ex "file Output/Quadruped.elf" -ex "target remote localhost:3333" -ex "monitor reset halt" -ex "load"
