#!/bin/sh

echo ======================================================
echo ================ VALID SUBMISSION  ===================
echo ======================================================
diff answers.txt tests/answers.txt | grep '^<' | sed 's/^<//g' > tests/content.txt
#eval $(stat -s tests/content.txt)
export st_size=`stat -c "%s" tests/content.txt`

echo Guestimate of content is $st_size bytes
if [ $st_size -gt 100 ]; then
    echo PASSED
  else
    echo FAILED
    echo ======
    echo There does not appear to be much in answers.txt
    exit 1
fi
