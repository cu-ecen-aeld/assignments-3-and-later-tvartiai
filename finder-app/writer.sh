#!/bin/bash

if [ "$#" -eq 2 ]; then
    #echo $2 > $1
    mkdir -p "$(dirname "$1")" && echo $2 > $1
    if [ $? -ne 1 ]; then
        echo "File created"
    else
        echo "File could not be created"
        exit 1
    fi
else
    echo "Wrong parameter count."
    exit 1
fi
