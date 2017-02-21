using namespace std;
#include "uti.h"
#include "parameters.h"

void plotPnNP(TString coly, TString outputfileP, TString outputfileNP, Float_t centmin=0, Float_t centmax=100)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  Bool_t isPbPb = (coly=="PbPb")?true:false;
  TString tcolyend = isPbPb?Form("%s_cent_%.0f_%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* infP = new TFile(Form("%s_%s.root",outputfileP.Data(),tcolyend.Data()));
  TFile* infNP = new TFile(Form("%s_%s.root",outputfileNP.Data(),tcolyend.Data()));

  TH1D* hEffP = (TH1D*)infP->Get("hEff");          hEffP->SetName("hEffP");
  TH1D* hEffNP = (TH1D*)infNP->Get("hEff");        hEffNP->SetName("hEffNP");

  hEffP->SetTitle(";p_{T} (GeV/c);#alpha x #epsilon_{reco} x #epsilon_{sel}");
  hEffP->SetMinimum(0.);
  hEffP->SetMaximum(1.5);
  hEffP->SetLineColor(2);
  hEffP->SetMarkerStyle(20);
  hEffP->SetMarkerSize(1.);
  hEffP->SetMarkerColor(2);
  hEffP->GetXaxis()->SetTitleOffset(0.95);//0.9
  hEffP->GetYaxis()->SetTitleOffset(1.15);//1.
  hEffP->GetXaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetYaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetXaxis()->SetTitleFont(42);
  hEffP->GetYaxis()->SetTitleFont(42);
  hEffNP->SetMarkerStyle(20);
  hEffNP->SetMarkerSize(1.);
  hEffNP->SetLineColor(4);
  hEffNP->SetMarkerColor(4);

  TString texper = "%";
  TLatex* texCent = new TLatex(0.57,0.84, Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextAlign(12);
  texCent->SetTextSize(0.045);
  texCent->SetTextFont(42);

  TCanvas* cEff = new TCanvas("cEff","",600,600);
  hEffP->Draw();
  hEffNP->Draw("same");
  drawCMS(coly);
  if(isPbPb) texCent->Draw();
  TLegend* legEff = new TLegend(0.55,0.70,0.90,0.81);
  legEff->SetBorderSize(0);
  legEff->SetFillStyle(0);
  legEff->AddEntry(hEffP,"Prompt","pl");
  legEff->AddEntry(hEffNP,"Non-prompt","pl");
  legEff->Draw("same");
  cEff->SaveAs(Form("plots/cEff_%s.pdf",tcolyend.Data()));
}

int main(int argc, char* argv[])
{
  if(argc==6)
    {
      plotPnNP(argv[1],argv[2],argv[3],atof(argv[4]),atof(argv[5]));
      return 1;
    }
  else if(argc==4)
    {
      plotPnNP(argv[1],argv[2],argv[3]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
