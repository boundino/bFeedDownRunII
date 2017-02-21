using namespace std;
#include "uti.h"
#include "parameters.h"

void bFeedDownFONLL(TString coly, TString outputFonllP, TString outputFonllNP, TString outputEffP, TString outputEffNP, TString outputBRAA, TString outputFraction, Float_t centmin=0, Float_t centmax=100)
{
  Bool_t isPbPb = (coly=="PbPb")?true:false;

  TFile* inputFileFonllP = new TFile(outputFonllP);
  TFile* inputFileFonllNP = new TFile(outputFonllNP);
  TString tcoly = isPbPb?Form("%s_cent_%.0f_%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* inputFileEffP = new TFile(Form("%s_%s.root",outputEffP.Data(),tcoly.Data()));
  TFile* inputFileEffNP = new TFile(Form("%s_%s.root",outputEffNP.Data(),tcoly.Data()));
  TFile* inputBRAA = new TFile(outputBRAA);

  TH1D* hEffP = (TH1D*)inputFileEffP->Get("hEff");                                          hEffP->SetName("hEffP");
  TH1D* hEffNP = (TH1D*)inputFileEffNP->Get("hEff");                                        hEffNP->SetName("hEffNP");
  TGraphAsymmErrors* gFonllP = (TGraphAsymmErrors*)inputFileFonllP->Get("gaeSigmaDzero");   gFonllP->SetName("gFonllP");
  TGraphAsymmErrors* gFonllNP = (TGraphAsymmErrors*)inputFileFonllNP->Get("gaeSigmaDzero"); gFonllNP->SetName("gFonllNP");
  TGraphAsymmErrors* grFraction = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction");
  TGraphAsymmErrors* grFraction3 = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction");
  TH1D* hFraction = new TH1D("hFraction","",nPtBins,ptBins);
  TH1D* hFraction3 = new TH1D("hFraction3","",nPtBins,ptBins);
  grFraction3->SetName("grPromptFraction3");
  TH1F* hBoverDh = (TH1F*)inputBRAA->Get("hBoverDh");
  TH1F* hBoverDl = (TH1F*)inputBRAA->Get("hBoverDl");

  for(int i=0;i<nPtBins;i++)
    {
      Double_t effP = hEffP->GetBinContent(i+1);
      Double_t effNP = hEffNP->GetBinContent(i+1);
      Double_t effPErr = hEffP->GetBinError(i+1)/effP;
      Double_t effNPErr = hEffNP->GetBinError(i+1)/effNP;
      Double_t fonllP,fonllNP,pt;
      gFonllP->GetPoint(i,pt,fonllP);
      gFonllNP->GetPoint(i,pt,fonllNP);
      Double_t fonllPErrl = gFonllP->GetErrorYlow(i)/fonllP;
      Double_t fonllPErrh = gFonllP->GetErrorYhigh(i)/fonllP;
      Double_t fonllNPErrl = gFonllNP->GetErrorYlow(i)/fonllNP;
      Double_t fonllNPErrh = gFonllNP->GetErrorYhigh(i)/fonllNP;
      Double_t nfP = fonllP*effP;
      Double_t nfNP = fonllNP*effNP;
      Double_t nfPErrl = TMath::Sqrt(fonllPErrl*fonllPErrl+effPErr*effPErr);
      Double_t nfPErrh = TMath::Sqrt(fonllPErrh*fonllPErrh+effPErr*effPErr);
      Double_t nfNPErrl = TMath::Sqrt(fonllNPErrl*fonllNPErrl+effNPErr*effNPErr);
      Double_t nfNPErrh = TMath::Sqrt(fonllNPErrh*fonllNPErrh+effNPErr*effNPErr);
      Double_t pFraction = nfP/(nfP+nfNP*hBoverDl->GetBinContent(i+1));
      Double_t pFraction3 = nfP/(nfP+nfNP*hBoverDh->GetBinContent(i+1));
      //Double_t pFractionErrl = TMath::Sqrt(nfPErrl*nfPErrl+(nfPErrl*nfPErrl*nfNP*nfNP+nfNPErrh*nfNPErrh*nfP*nfP)/((nfP+nfNP)*(nfP+nfNP)));
      //Double_t pFractionErrh = TMath::Sqrt(nfPErrh*nfPErrh+(nfPErrh*nfPErrh*nfNP*nfNP+nfNPErrl*nfNPErrl*nfP*nfP)/((nfP+nfNP)*(nfP+nfNP)));
      grFraction->SetPoint(i,pt,pFraction);
      grFraction->SetPointEYlow(i,0);
      grFraction->SetPointEYhigh(i,0);
      grFraction3->SetPoint(i,pt,pFraction3);
      grFraction3->SetPointEYlow(i,0);
      grFraction3->SetPointEYhigh(i,0);
      hFraction->SetBinContent(i+1,pFraction);
      hFraction3->SetBinContent(i+1,pFraction3);
    }
  TFile* fout = new TFile(Form("%s_%s.root",outputFraction.Data(),tcoly.Data()), "recreate");
  grFraction->Write();
  grFraction3->Write();
  hFraction->Write();
  hFraction3->Write();
  fout->Close();

}

int main(int argc, char *argv[])
{
  if(argc==10)
    {
      bFeedDownFONLL(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],atof(argv[8]),atof(argv[9]));
      return 0;
    }
  if(argc==8)
    {
      bFeedDownFONLL(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}
