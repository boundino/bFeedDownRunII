
# bFeedDownRunII

bFeedDownRunII is created to extract D0 prompt fractions.

## analysis/
### Introduction
analysis/ is main anaysis macros. For each collision system, there are two steps:
<ol>
<li> `analysis/*/savehist/project*.C`: Project and save histograms </li>
<li> `analysis/bFeedDownFraction.C`: Fit DCA distributions </li>
</ol>
### How to run
<ul>
<li> Run all three collision systems (PP,PbPbcent0100,PbPbcent010)
```
cd analysis/
source doall.sh 1 1
```
where the arguments decide whether to run each step.
</li>
<li> Run one collision system (e.g. PP)
```
cd analysis/PP/
source dobFeedDown.sh 1 1
```
where the arguments decide whether to run each step.
</li>
</ul>

## pfFONLL/
### Introduction
pfFONLL/ calculates and plots prompt fractions by FONLL. There are three steps:
<ol>
<li> `pfFONLL/fonllDsigmadpt.C`: Calculate FONLL pp cross-sections </li>
<li> `MCefficiency.C``plotPnNP.C`: Calculate and MC efficiency </li>
<li> `fitBoverD.C``bFeedDownFONLL.C``plotFractions.C`: Set BRAA/DRAA ratios, calculate and plot prompt fractions </li>
</ol>
### How to run it
<ul>
<li> Run all three collision systems
```
cd pfFONLL/
source doall.sh 1 1 1
```
where the arguments decide whether to run each step.
</li>
<li> Run one collision system
```
cd pfFONLL/
source dobFeedDownFONLL.sh [c] 1 1 1
```
`[c]` decides the system (0:PP, 1:PbPbcent0100, 2:PbPbcent010), and the others decide whether to run each step.
</li>
</ul>

## finalPlots/
### Introduction
finalPlots/ plots the final plots comparing prompt fractions by DCA fitting and FONLL. There is one step:
<ol>
<li> `finalPlots.C` </li>
</ol>
It prerequires the results from `analysis/` and `pfFONLL/`. 
### How to run it
<ul>
<li> Run all three collision systems 
```
cd finalPlots/
source doall.sh
```
</li>
<li> Run one collision system
```
cd finalPlots/
source dofinalPlots.sh [c]
```
`[c]` decides the system (0:PP, 1:PbPbcent0100, 2:PbPbcent010).
</li>
</ul>

## MCclosure/
### Introduction
MCclosure/ tests closure of the machinery. There are three steps:
<ol>
<li> `analysis/*`: Calculate the prompt fractions from DCA fitting machinery </li>
<li> `trueFprompt.cc`: Count the true prompt fractions from fake data </li>
<li> `compare.cc`:  Plot the comparison of prompt fractions from DCA fitting and true values </li>
</ol>
### How to run it
```
cd MCclosure/analysis/
source doall.sh 1 1
cd ..
source doMCclosure.sh 1 1
```

