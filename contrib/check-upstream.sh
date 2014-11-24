#!/bin/sh

# Usage: check <repo> <branch> <last commit checked>

function check(){
	output="merge-$1-$2.txt"

	echo "Checking $1..."

	git fetch $1
	git cherry -v master $1/$2 $3 > $output

	echo "Done, check $output"
}

check bitcoin \
	master \
	6c37f7fd78832442a26e56bd0787974927df4fb2

check litecoin \
	master-0.8 \
	fab1907372397423e2debb44416385dc53ffd079

echo ""
echo "In the output files, commits prefixed with a + are not yet merged from upstream for some reason"
echo "or they are merged but the diffs don't match."
echo ""
echo "After checking them update the pointer to were you checked in this script."

