#!/bin/bash

if [ "$#" -eq 2 ]; then
    filesdir=$1
    searchstr=$2

    if [ -d $filesdir ]; then
        file_count=$(grep -r -l $2 $1 | wc -l)
        line_count=$(grep -r $2 $1 | wc -l)
        echo "The number of files are $file_count and the number of matching lines are $line_count"
    else
        echo "Not a files directory"
        exit 1
    fi
else
    echo "Wrong parameter count."
    exit 1
fi
