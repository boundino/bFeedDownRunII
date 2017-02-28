
source dofinalPlots.sh 0
source dofinalPlots.sh 1
source dofinalPlots.sh 2

cp ../uti.h .
root -l -b -q "finalPlotsRatio.C+("0","100")"
root -l -b -q "finalPlotsRatio.C+("0","10")"
rm uti.h