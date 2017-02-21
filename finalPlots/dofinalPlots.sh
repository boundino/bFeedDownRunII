#!/bin/bash

COL=$1
COLY=("PP" "PbPb" "PbPb")
CENTMIN=(0 0 0)
CENTMAX=(100 100 10)

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

#
g++ finalPlots.C $(root-config --cflags --libs) -g -o finalPlots.exe
./finalPlots.exe ${COLY[$COL]} $OUTPUTFRACTION ${CENTMIN[$COL]} ${CENTMAX[$COL]}
rm finalPlots.exe

#
rm uti.h

#