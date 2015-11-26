#!/usr/bin/env bash

#sub=$1
for sub in *.hw3b; do
	user=$(basename $sub .hw3b)
	echo $user
	# if [[ -d $user ]]; then
	#     rm -rf $user
	# fi
	rm -rf $user
done
