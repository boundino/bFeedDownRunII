#include "uti.h"

const int nPtBins = 14;
Double_t ptBins[nPtBins+1] = {2.0, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.5, 15.0, 20.0, 25.0, 30.0, 40.0, 60.0, 100.0};

const int nFonllBins = 400;
Double_t fstFonllBins = 0;
Double_t lstFonllBins = 100;
Double_t widFonllBins = (lstFonllBins-fstFonllBins)/nFonllBins;
