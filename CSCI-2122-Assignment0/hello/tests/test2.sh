#!/bin/sh

echo ======================================================
echo ====================== TEST 2 ========================
echo ======================================================
echo Testing that total output is 2 lines long
echo Output is: `./hello/hello | wc -l | sed 's/ //g'` lines long
[ `./hello/hello | wc -l | sed 's/ //g'` -eq 2 ]
