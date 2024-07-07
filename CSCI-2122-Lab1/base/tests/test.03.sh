#!/bin/sh
export LC_ALL=C

if [ ! -f answers.txt ]; then
  echo FAILED: answers.txt not present in repository
  exit 1
fi 

if ! grep '^PROGRAM[ \t]*revlin[ \t]*$' answers.txt > /dev/null; then
    echo Incorrect name of C program.
    exit 1
fi

exit 0
