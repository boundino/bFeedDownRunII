using namespace std;
#include "savehist/project.h"
#include "../../pfFONLL/parameters.h"

void rebin(TString col)
{
  Bool_t isPbPb = (col=="PbPb")?true:false;
  fillptbins(isPbPb);

  TFile* inf = new TFile("rootfiles/bFeedDownResult.root");
  TGraphErrors* grFraction0 = (TGraphErrors*)inf->Get("grPromptFraction");
  grFraction0->SetName("grPromptFraction0");
  TGraphErrors* grFraction20 = (TGraphErrors*)inf->Get("grPromptFraction2");
  grFraction20->SetName("grPromptFraction20");
  /*
  TH1D** ahD0DcaData = new TH1D*[nBinX];
  TH1D** ahD0DcaMCPSignal = new TH1D*[nBinX];
  TH1D** ahD0DcaMCNPSignal = new TH1D*[nBinX];

  for(int i=0;i<nBinX;i++)
    {
      ahD0DcaData[i] = (TH1D*)inf->Get(Form("hD0DcaData_%d",i));
      ahD0DcaMCPSignal[i] = (TH1D*)inf->Get(Form("hD0DcaMCPSignal_%d",i));
      ahD0DcaMCNPSignal[i] = (TH1D*)inf->Get(Form("hD0DcaMCNPSignal_%d",i));
    }
  */
  double pts[nPtBins],promptFraction[nPtBins],ptsError[nPtBins],ptsErrorDataOnly[nPtBins],promptFractionError[nPtBins],promptFractionErrorDataOnly[nPtBins];
  for(int i=0;i<nPtBins;i++)
    {
      int j = (i==0||!isPbPb)?i:i-1;
      double tem;
      pts[i] = (ptBins[i]+ptBins[i+1])/2.;
      grFraction0->GetPoint(j,tem,promptFraction[i]);
      ptsErrorDataOnly[i] = grFraction0->GetErrorX(j);
      promptFractionErrorDataOnly[i] = grFraction0->GetErrorY(j);
      ptsError[i] = grFraction20->GetErrorX(j);
      promptFractionError[i] = grFraction20->GetErrorY(j);      
    }
  TGraphErrors* grFraction2 = new TGraphErrors(nPtBins, pts, promptFraction, ptsError, promptFractionError);
  grFraction2->SetName("grPromptFraction2");
  grFraction2->SetLineWidth(0);
  grFraction2->SetLineColor(16);
  grFraction2->SetFillStyle(1001);
  grFraction2->SetFillColor(16);
  TGraphErrors* grFraction = new TGraphErrors(nPtBins, pts, promptFraction, ptsErrorDataOnly, promptFractionErrorDataOnly);
  grFraction->SetName("grPromptFraction");
  grFraction->SetMarkerStyle(20);
  grFraction->SetMarkerSize(0.6);
  grFraction->SetMarkerColor(kBlack);

  TFile* fOut = new TFile("rootfiles/bFeedDownResult_temp.root", "recreate");
  fOut->cd();
  grFraction->Write();
  grFraction2->Write();
  /*
  for(int i=0;i<nBinX;i++) ahD0DcaData[i]->Write();
  for(int i=0;i<nBinX;i++) ahD0DcaMCPSignal[i]->Write();
  for(int i=0;i<nBinX;i++) ahD0DcaMCNPSignal[i]->Write();
  */
  fOut->Close();

}
