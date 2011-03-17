#!/bin/sh

# testr.sh
# by Jakob Odersky

# Usage: testr.sh TESTDIR
# Runs all files in TESTDIR that match *Test
# A test is considered successful if it returns 0 upon execution.

red='\033[0;31m'
green='\033[0;32m'
blue='\033[0;34m'
nc='\033[0m' # No Color

#Test directory specified by first parameter
TESTDIR=$1
cd $TESTDIR

echo "[info] Analyzing directory."
TESTCOUNT=`ls -A  ./*Test | wc -l`
echo "[info] Found $TESTCOUNT tests in $TESTDIR."
echo "[info] Running tests."
echo ""

FAILED=0

for filename in ./*Test
do
	
	echo "[info] ${blue}== $filename ==${nc}"
	$filename
	OUT=$?
	echo "[info] ${blue}== $filename ==${nc}"	

	if [ $OUT -eq 0 ];then
   		echo "[info] $filename PASS"
	else
   		echo "[${red}error${nc}] $filename FAIL"
		FAILED=$(($FAILED + 1))
	fi
	echo ""
done;

echo "[info] Total: $TESTCOUNT, Failed: $FAILED, Passed: $(($TESTCOUNT - $FAILED))"

if [ $FAILED -eq 0 ];then
	echo "[${green}success${nc}] All tests PASSED."
else
	echo "[${red}error${nc}] Some tests FAILED."
fi


