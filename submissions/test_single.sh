#!/usr/bin/env bash

#sub=$1
for sub in *.hw3b; do
	user=$(basename $sub .hw3b)
	echo $user
	# if [[ -d $user ]]; then
	#     rm -rf $user
	# fi
	mkdir -p $user
	tar xf $sub -C $user
	for subdir in $(find $user/* -type d); do
				     cp $subdir/* $user/
				     done
				     cp ../tester/* $user/
				     cd $user
	# Test
	make -f Makefile clean > /dev/null
	make -f Makefile encodeChar > make_output1.txt 2>&1
	make -f Makefile decodeChar > make_output2.txt 2>&1
	make -f Makefile decodeARM > make_output3.txt 2>&1
	#retval=$?
	#if [ $retval -ne 0 ]; then # Make failed, try compiling ASM separately
	#    make -k -f backup_makefile tests > make_output2.txt 2>&1
	#fi
	./encodeChar
	./decodeChar
	./decodeARM
	cd ..
done
