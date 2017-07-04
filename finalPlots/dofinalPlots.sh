#!/bin/bash

COL=$1
COLY=("PP" "PbPb" "PbPb")
CENTMIN=(0 0 0)
CENTMAX=(0 100 10)
PCOLOR=(1 634 863)
BCOLOR=(920 623 851)
PSTYLE=(20 21 22)


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
root -l -b -q "fpromptPlots.C+("\"${COLY[$COL]}\"","${PCOLOR[$COL]}","${BCOLOR[$COL]}","${PSTYLE[$COL]}","${CENTMIN[$COL]}","${CENTMAX[$COL]}")"

rm uti.h

#