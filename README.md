
# bFeedDownRunII

bFeedDownRunII is created to extract D0 prompt fractions.

## analysis/
### Introduction
analysis/ is main anaysis macros. For each collision system, there are two steps:
1. `analysis/*/savehist/project*.C`: Project and save histograms
2. `analysis/bFeedDownFraction.C`: Fit DCA distributions
### How to run
* Run all three collision systems (PP,PbPbcent0100,PbPbcent010)
```
cd analysis/
source doall.sh 1 1
```
where the arguments decide whether to run each step.
* Run one collision system (e.g. PP)
```
cd analysis/PP/
source dobFeedDown.sh 1 1
```
where the arguments decide whether to run each step.

## pfFONLL/
### Introduction
pfFONLL/ calculates and plots prompt fractions by FONLL. There are three steps:
1. `pfFONLL/fonllDsigmadpt.C`: Calculate FONLL pp cross-sections
2. `MCefficiency.C``plotPnNP.C`: Calculate and MC efficiency
3. `fitBoverD.C``bFeedDownFONLL.C``plotFractions.C`: Set BRAA/DRAA ratios, calculate and plot prompt fractions
### How to run it
* Run all three collision systems
```
cd pfFONLL/
source doall.sh 1 1 1
```
where the arguments decide whether to run each step.
* Run one collision system
```
cd pfFONLL/
source dobFeedDownFONLL.sh [c] 1 1 1
```
`[c]` decides the system (0:PP, 1:PbPbcent0100, 2:PbPbcent010), and the others decide whether to run each step.

## finalPlots/
### Introduction
finalPlots/ plots the final plots comparing prompt fractions by DCA fitting and FONLL. There are one step:
1. `finalPlots.C`
It prerequires the results from `analysis/` and `pfFONLL/`. 
### How to run it
* Run all three collision systems 
```
cd finalPlots/
source doall.sh
```
* Run one collision system
```
cd finalPlots/
source dofinalPlots.sh [c]
```
`[c]` decides the system (0:PP, 1:PbPbcent0100, 2:PbPbcent010).

## MCclosure/
### Introduction
MCclosure/ tests closure of the machinery. There are three steps:
1. `analysis/*`: Calculate the prompt fractions from DCA fitting machinery
2. `trueFprompt.cc`: Count the true prompt fractions from fake data
3. `compare.cc`:  Plot the comparison of prompt fractions from DCA fitting and true values
### How to run it
```
cd MCclosure/analysis/
source doall.sh 1 1
cd ..
source doMCclosure.sh 1 1
```

