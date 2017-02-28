#!/bin/bash

COL=$1
COLY=("PP" "PbPb" "PbPb")
CENTMIN=(0 0 0)
CENTMAX=(0 100 10)

OUTPUTFRACTION="../pfFONLL/outfilesResult/bFeedDownFONLL"

#
FOLDERS=("plots")
for i in $FOLDERS
do
    if [ ! -d $i ]; then
        mkdir $i
    fi
done

##

#
cp ../uti.h .

root -l -b -q "finalPlots.C+("\"${COLY[$COL]}\"","\"$OUTPUTFRACTION\"","${CENTMIN[$COL]}","${CENTMAX[$COL]}")"

rm uti.h

#