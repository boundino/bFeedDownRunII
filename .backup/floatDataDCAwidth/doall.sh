#!/bin/bash

CHANNELS=("PP" "PbPbcent0100" "PbPbcent010")
for i in ${CHANNELS[@]}
do
    cd $i/
    source dobFeedDown.sh $1 $2
    cd ..
done