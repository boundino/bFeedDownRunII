#include "uti.h"

Double_t ptBins_PP[15] = {2.0, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.5, 15.0, 20.0, 25.0, 30.0, 40.0, 60.0, 100.0};
//Double_t ptBins_PbPb[14] = {2.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.5, 15.0, 20.0, 25.0, 30.0, 40.0, 60.0, 100.0};
Double_t ptBins_PbPb[15] = {2.0, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.5, 15.0, 20.0, 25.0, 30.0, 40.0, 60.0, 100.0};


int nPtBins;
Double_t* ptBins;
void fillptbins(Bool_t isPbPb)
{
  if(isPbPb)
    {
      nPtBins = 14;
      //nPtBins = 13;
      ptBins = new Double_t[nPtBins+1];
      for(int i=0;i<(nPtBins+1);i++) ptBins[i] = ptBins_PbPb[i];
    }
  else
    {
      nPtBins = 14;
      ptBins = new Double_t[nPtBins+1];
      for(int i=0;i<(nPtBins+1);i++) ptBins[i] = ptBins_PP[i];
    }
}

const int nFonllBins = 400;
Double_t fstFonllBins = 0;
Double_t lstFonllBins = 100;
Double_t widFonllBins = (lstFonllBins-fstFonllBins)/nFonllBins;
