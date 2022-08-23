#!/bin/sh
find . -type f -path '*.sh' -exec basename {} .sh \;
