#!/bin/sh
export LC_ALL=C

FILES=`find . | grep -v '\.git'`
EX=0

for i in $FILES; do
    if ! grep "$i$" base/tests/test.07.dat > /dev/null; then
        echo File $i should not be submitted.
        EX=1
    fi
done

exit $EX
