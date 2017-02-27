using namespace std;
#include "uti.h"
#include "parameters.h"

void bFeedDownFONLL(TString coly, TString outputFonllP, TString outputFonllNP, TString outputEffP, TString outputEffNP, TString outputBRAA, TString outputFraction, Float_t centmin=0, Float_t centmax=100)
{
  Bool_t isPbPb = (coly=="PbPb")?true:false;
  fillptbins(isPbPb);

  TString tcoly = isPbPb?Form("%s_cent_%.0f_%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* inputFileFonllP = new TFile(Form("%s_%s.root",outputFonllP.Data(),tcoly.Data()));
  TFile* inputFileFonllNP = new TFile(Form("%s_%s.root",outputFonllNP.Data(),tcoly.Data()));
  TFile* inputFileEffP = new TFile(Form("%s_%s.root",outputEffP.Data(),tcoly.Data()));
  TFile* inputFileEffNP = new TFile(Form("%s_%s.root",outputEffNP.Data(),tcoly.Data()));
  TFile* inputBRAA = new TFile(outputBRAA);

  TH1D* hEffP = (TH1D*)inputFileEffP->Get("hEff");                                          hEffP->SetName("hEffP");
  TH1D* hEffNP = (TH1D*)inputFileEffNP->Get("hEff");                                        hEffNP->SetName("hEffNP");
  TGraphAsymmErrors* gFonllP = (TGraphAsymmErrors*)inputFileFonllP->Get("gaeSigmaDzero");   gFonllP->SetName("gFonllP");
  TGraphAsymmErrors* gFonllNP = (TGraphAsymmErrors*)inputFileFonllNP->Get("gaeSigmaDzero"); gFonllNP->SetName("gFonllNP");
  TGraphAsymmErrors* grFraction = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction");
  TGraphAsymmErrors* grFraction3 = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction3");
  TGraphAsymmErrors* grFractionDa = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFractionDa");
  TGraphAsymmErrors* grFraction3Da = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction3Da");
  TGraphAsymmErrors* grFractionNPJ = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFractionNPJ");
  TGraphAsymmErrors* grFraction3NPJ = (TGraphAsymmErrors*)gFonllP->Clone("grPromptFraction3NPJ");

  TH1F* hBoverDh = (TH1F*)inputBRAA->Get("hBoverDh");
  TH1F* hBoverDl = (TH1F*)inputBRAA->Get("hBoverDl");
  TH1F* hBoverDhDa = (TH1F*)inputBRAA->Get("hBoverDhDa");
  TH1F* hBoverDlDa = (TH1F*)inputBRAA->Get("hBoverDlDa");
  TH1F* hBoverDhNPJ = (TH1F*)inputBRAA->Get("hBoverDhNPJ");
  TH1F* hBoverDlNPJ = (TH1F*)inputBRAA->Get("hBoverDlNPJ");

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
      Double_t pFractionDa = nfP/(nfP+nfNP*hBoverDlDa->GetBinContent(i+1));
      Double_t pFraction3Da = nfP/(nfP+nfNP*hBoverDhDa->GetBinContent(i+1));
      Double_t pFractionNPJ = nfP/(nfP+nfNP*hBoverDlNPJ->GetBinContent(i+1));
      Double_t pFraction3NPJ = nfP/(nfP+nfNP*hBoverDhNPJ->GetBinContent(i+1));
      if(!isPbPb)
        {
          pFraction = nfP/(nfP+nfNP);
          pFraction3 = nfP/(nfP+nfNP);
        }

      grFraction->SetPoint(i,pt,pFraction);
      grFraction->SetPointEYlow(i,0);
      grFraction->SetPointEYhigh(i,0);
      grFraction3->SetPoint(i,pt,pFraction3);
      grFraction3->SetPointEYlow(i,0);
      grFraction3->SetPointEYhigh(i,0);
      grFractionDa->SetPoint(i,pt,pFractionDa);
      grFractionDa->SetPointEYlow(i,0);
      grFractionDa->SetPointEYhigh(i,0);
      grFraction3Da->SetPoint(i,pt,pFraction3Da);
      grFraction3Da->SetPointEYlow(i,0);
      grFraction3Da->SetPointEYhigh(i,0);
      if(hBoverDlDa->GetBinContent(i+1)<0 && isPbPb)
        {
          grFractionDa->SetPoint(i,pt,-1);
          grFraction3Da->SetPoint(i,pt,-1);
        }
      grFractionNPJ->SetPoint(i,pt,pFractionNPJ);
      grFractionNPJ->SetPointEYlow(i,0);
      grFractionNPJ->SetPointEYhigh(i,0);
      grFraction3NPJ->SetPoint(i,pt,pFraction3NPJ);
      grFraction3NPJ->SetPointEYlow(i,0);
      grFraction3NPJ->SetPointEYhigh(i,0);
      if(hBoverDlNPJ->GetBinContent(i+1)<0 && isPbPb)
        {
          grFractionNPJ->SetPoint(i,pt,-1);
          grFraction3NPJ->SetPoint(i,pt,-1);
        }
    }

  TFile* fout = new TFile(Form("%s_%s.root",outputFraction.Data(),tcoly.Data()), "recreate");
  grFraction->Write();
  grFraction3->Write();
  grFractionDa->Write();
  grFraction3Da->Write();
  grFractionNPJ->Write();
  grFraction3NPJ->Write();
  hBoverDh->Write();
  hBoverDl->Write();
  hBoverDhDa->Write();
  hBoverDlDa->Write();
  hBoverDhNPJ->Write();
  hBoverDlNPJ->Write();
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
