#!/bin/sh
export LC_ALL=C

if [ ! -f answers.txt ]; then
  echo FAILED: answers.txt not present in repository
  exit 1
fi 

grep '^REVERSE' answers.txt | sort > reverse.txt

if ! diff reverse.txt base/tests/test.06.dat ; then
  echo The set of files that are the same forwards as backwards is not correct
  rm reverse.txt
  exit 1
fi 

rm reverse.txt
exit 0
