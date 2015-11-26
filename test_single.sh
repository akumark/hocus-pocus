#!/usr/bin/env bash

sub=$1
user=$(basename $sub .hw3a)
echo $user
#if [[ -d $user ]]; then
#     rm -rf $user
#fi
mkdir -p $user
tar xf $sub -C $user
for subdir in $(find $user/* -type d); do
    cp $subdir/* $user/
done
cp ../tester/* $user/
cd $user
# Test
make -f Makefile clean > /dev/null
make -f Makefile countchar > make_output.txt 2>&1
make -f Makefile reverse > make_output2.txt 2>&1
#retval=$?
#if [ $retval -ne 0 ]; then # Make failed, try compiling ASM separately
#    make -k -f backup_makefile tests > make_output2.txt 2>&1
#fi
python ./main.py
cd ..
