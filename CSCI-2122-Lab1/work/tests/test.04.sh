#!/bin/sh
export LC_ALL=C

if [ ! -f answers.txt ]; then
  echo FAILED: answers.txt not present in repository
  exit 1
fi 

if ! grep '^ERROR[ \t]*11[ \t]*$' answers.txt > /dev/null; then
    echo Incorrect line number of error in C program.
    exit 1
fi

cd work
if ! make; then
    echo C program does not compile.
    cd ..
    exit 1
fi

./revlin < test.2.in > output.txt
diff test.2.in output.txt > /dev/null
DIFF=$?
rm output.txt
rm revlin
cd ..

if [ $DIFF -ne 0 ]; then
    echo C program is not fixed correctly
    exit 1
fi 

exit 0
