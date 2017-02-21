using namespace std;
#include "uti.h"

void finalPlots(TString coly, TString outputFraction, Float_t centmin=0, Float_t centmax=100)
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
  TString tcoly = isPbPb?Form("%s_cent_%.0f_%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* inputFONLL = new TFile(Form("%s_%s.root",outputFraction.Data(),tcoly.Data()));
  TString tcolyDCA = isPbPb?Form("%scent%.0f%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* inputDCA = new TFile(Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCA.Data()));

  TGraphAsymmErrors* grFraction = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction");
  grFraction->SetLineWidth(1.);
  grFraction->SetMarkerSize(0.8);
  grFraction->SetMarkerStyle(20);
  grFraction->SetLineColor(kRed);
  grFraction->SetMarkerColor(kRed);
  TGraphAsymmErrors* grFraction3 = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3");
  for(int i=0;i<grFraction->GetN();i++)
    {
      Double_t pt,frac,frac3;
      grFraction->GetPoint(i,pt,frac);
      grFraction3->GetPoint(i,pt,frac3);
      Double_t fcenter = (frac+frac3)/2.;
      Double_t ferror = (frac-frac3)/2.;
      grFraction3->SetPoint(i,pt,fcenter);
      grFraction3->SetPointEYlow(i,ferror);
      grFraction3->SetPointEYhigh(i,ferror);
    }
  grFraction3->SetLineWidth(1.);
  grFraction3->SetLineColor(kRed);
  grFraction3->SetFillColor(kRed);
  grFraction3->SetFillStyle(3001);

  TGraphErrors* grFractionDCA = (TGraphErrors*)inputDCA->Get("grPromptFraction");
  grFractionDCA->SetName("grFractionDCA");
  grFractionDCA->SetLineWidth(1.);
  grFractionDCA->SetMarkerSize(0.8);
  grFractionDCA->SetMarkerStyle(20);
  grFractionDCA->SetLineColor(kBlack);
  grFractionDCA->SetMarkerColor(kBlack);

  TH2F* hempty = new TH2F("hempty","",20,0.,100.,10.,0.,1.);
  hempty->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("Prompt fraction");
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.3);
  hempty->GetYaxis()->SetTitleOffset(1.8);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);

  TCanvas* c = new TCanvas("c","",600,600);
  hempty->Draw();
  if(isPbPb) grFraction3->Draw("same2");
  else grFraction->Draw("samepe");
  grFractionDCA->Draw("samepe");
  drawCMS(coly);
  TLegend* leg = new TLegend(0.60,0.30,0.90,0.42);
  setleg(leg);
  leg->AddEntry(grFractionDCA,"Fit DCA","pl");
  if(isPbPb) leg->AddEntry(grFraction3,"FONLL + MC eff","f");
  else leg->AddEntry(grFraction,"FONLL + MC eff","pl");
  leg->Draw();
  TString per = "%";
  TLatex* centtex = new TLatex(0.62,0.45,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(centtex);
  if(isPbPb) centtex->Draw();
  c->SaveAs(Form("plots/cfpromptComparison_%s.pdf",tcoly.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      finalPlots(argv[1],argv[2],atof(argv[3]),atof(argv[4]));
      return 0;
    }
  else if(argc==3)
    {
      finalPlots(argv[1],argv[2]);
      return 0;
    }
  else
    {
      cout<<"  Error: Arguments number is invalid."<<endl;
      return 1;
    }

}

