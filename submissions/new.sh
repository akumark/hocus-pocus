#!/usr/bin/env bash

mkdir -p grade
#sub=$1
for sub in *.hw3b; do
	user=$(basename $sub .hw3b)
	echo $user
        mkdir -p grade/$user
	# if [[ -d $user ]]; then
	#     rm -rf $user
	# fi
	cp $user/grader_output.txt grade/$user/feedback.txt
	cp $user/make_output1.txt grade/$user/make_encoder_C.txt
	cp $user/make_output2.txt grade/$user/make_decoder_C.txt
	cp $user/make_output3.txt grade/$user/make_decoder_ARM.txt
done
