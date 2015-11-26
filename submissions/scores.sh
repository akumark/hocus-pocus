#!/usr/bin/env bash

#sub=$1
for sub in *.hw3b; do
	user=$(basename $sub .hw3b)
	echo $user
        cp extract_score.py $user/
        cd $user
	python ./extract_score.py $user
	cd ..
	# if [[ -d $user ]]; then
	#     rm -rf $user
	# fi
done
