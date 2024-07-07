#!/bin/sh
export LC_ALL=C

if [ ! -f answers.txt ]; then
  echo FAILED: answers.txt not present in repository
  exit 1
fi 

if ! grep '^NAME[ \t]*[^ \t]' answers.txt > /dev/null; then
    echo Your name is missing from the answers.txt
    exit 1
fi

exit 0
