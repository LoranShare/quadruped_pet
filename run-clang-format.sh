#!/bin/bash

find software/tests/test/ -type f \( -name \*.c -o -name \*.h \) -exec clang-format-16 --verbose --style=file -i '{}' \;
find Src/ -maxdepth 1 -type f \( -name \*.c -o -name \*.h \) -exec clang-format-16 --verbose --style=file -i '{}' \;
find Inc/ -maxdepth 1 -type f \( -name \*.c -o -name \*.h \) -exec clang-format-16 --verbose --style=file -i '{}' \;
