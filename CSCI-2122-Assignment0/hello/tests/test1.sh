#!/bin/sh

echo ======================================================
echo ====================== TEST 1 ========================
echo ======================================================
echo Testing that first line is "Hello, World!"
echo Output is: \"`./hello/hello | head -1`\"
./hello/hello | head -1 | grep "^Hello, World!$" > /dev/null
