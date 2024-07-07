#!/bin/sh
export LC_ALL=C

if [ ! -f answers.txt ]; then
  echo FAILED: answers.txt not present in repository
  exit 1
fi 

grep '^DIRECTORY' answers.txt | sort > directory.txt

if ! diff directory.txt base/tests/test.02.dat ; then
  echo Incorrect number of files listed for some directories.
  rm directory.txt
  exit 1
fi 

rm directory.txt
exit 0
