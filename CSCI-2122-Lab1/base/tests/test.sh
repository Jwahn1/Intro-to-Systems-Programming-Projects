#!/bin/sh
export LC_ALL=C

echo ======================================================
echo ====================== TEST $1 =======================
echo ======================================================
if base/tests/test.$1.sh; then
    echo PASSED
    exit 0
else
    echo FAILED
    exit 1
fi
