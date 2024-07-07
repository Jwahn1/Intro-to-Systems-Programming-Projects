#!/bin/sh
export LC_ALL=C

FILES="1 2 3 4 5"
EX=0

for i in $FILES; do
    if [ ! -f work/test.$i.out ]; then
        echo File ./work/test.$i.out was not submitted.
        EX=1
    fi
done

exit $EX
