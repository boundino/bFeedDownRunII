#!/bin/bash

DO_PROJECT=$1
DO_FIT=$2
COL="PP"

##

FOLDERS=("plots" "plotsResult" "rootfiles")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]; then
        mkdir $i
    fi
done

#
cp ../../../uti.h .
cp ../bFeedDownFraction.* .

if [ $DO_PROJECT -eq 1 ]; then
    cd savehist/
    SAMPLES=("${COL}MC" "${COL}MBMC" "${COL}" "${COL}MB")
    for i in ${SAMPLES[@]}
    do
        root -l -b -q "project${i}.C+("\"$i\"")"
    done
    cd ..
fi

if [ $DO_FIT -eq 1 ]; then
    root -l -b -q "bFeedDownFraction.C+("\"$COL\"")"
fi

rm bFeedDownFraction.*
rm uti.h