cd submissions
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
done
