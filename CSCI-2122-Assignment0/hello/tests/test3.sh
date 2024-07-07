#!/bin/sh

echo ======================================================
echo ====================== TEST 3 ========================
echo ======================================================
echo Testing that second line contains the Net ID
echo Output is: \"`./hello/hello | tail -1`\"
./hello/hello | tail -1 | grep "^My NetID is " | grep -v '??' > /dev/null
