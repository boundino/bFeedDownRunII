using namespace std;
#include "uti.h"

void fpromptPlots(TString coly, Int_t pcolor, Int_t bcolor, Int_t pstyle, Float_t centmin=0, Float_t centmax=100)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.11);
  gStyle->SetPadLeftMargin(0.11);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  Bool_t isPbPb = (coly=="PbPb")?true:false;
  TString col = isPbPb?"PbPb":"pp";
  TString tcoly = isPbPb?Form("%s_cent_%.0f_%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TString tcolyDCA = isPbPb?Form("%scent%.0f%.0f",coly.Data(),centmin,centmax):Form("%s",coly.Data());
  TFile* inputDCA = new TFile(Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCA.Data()));

  TGraphErrors* grFractionDCA = (TGraphErrors*)inputDCA->Get("grPromptFraction2");
  grFractionDCA->SetName("grFractionDCA");
  grFractionDCA->SetLineWidth(1.);
  grFractionDCA->SetMarkerStyle(pstyle);
  grFractionDCA->SetLineColor(pcolor);
  grFractionDCA->SetMarkerColor(pcolor);
  grFractionDCA->SetMarkerSize(pstyle==33?1.3:0.9);

  TGraphErrors* grFractionSyst = (TGraphErrors*)grFractionDCA->Clone("grFractionSyst");
  grFractionSyst->SetLineWidth(0);
  grFractionSyst->SetLineColor(bcolor);
  grFractionSyst->SetFillStyle(1001);
  grFractionSyst->SetFillColor(bcolor);
  grFractionSyst->SetFillColorAlpha(bcolor, 0.7);

  for(int i=0;i<grFractionDCA->GetN();i++)
    {
      Double_t pt,fracDCA;
      grFractionDCA->GetPoint(i,pt,fracDCA);
      grFractionDCA->SetPointError(i,0,grFractionDCA->GetErrorY(i));
      grFractionSyst->SetPoint(i,pt,fracDCA);
      grFractionSyst->SetPointError(i,0.4,0.1*fracDCA);
    }

  TCanvas* cfprompt = new TCanvas("cfprompt","",600,600);
  cfprompt->cd();
  cfprompt->SetFillColor(0);
  cfprompt->SetBorderMode(0);
  cfprompt->SetBorderSize(2);
  cfprompt->SetLeftMargin(0.16);
  cfprompt->SetRightMargin(0.05);
  cfprompt->SetTopMargin(0.080);
  cfprompt->SetBottomMargin(0.150);
  cfprompt->SetFrameBorderMode(0);
  //cfprompt->SetLogx();

  TH2F* hempty = new TH2F("hempty",";p_{T} (GeV/c);Prompt fraction",10,0,100,10,0,1.3);
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.15);//0.9
  hempty->GetYaxis()->SetTitleOffset(1.15);//1.
  hempty->GetXaxis()->SetTitleSize(0.060);//0.045
  hempty->GetYaxis()->SetTitleSize(0.060);//0.045
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.050);//0.035
  hempty->GetYaxis()->SetLabelSize(0.050);//0.035  
  hempty->GetXaxis()->SetLabelOffset(0.01);
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
  grFractionSyst->Draw("5same");
  grFractionDCA->Draw("psame");
  TString per = "%";
  TLatex* texcent = new TLatex(0.60,0.44,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(texcent,0.045);
  if(isPbPb) texcent->Draw();
  TLegend* leg = new TLegend(0.58, 0.27, 1.00, 0.40);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(grFractionDCA, "stat. uncert.", "lpe");
  leg->AddEntry(grFractionSyst, "syst. uncert.", "f");
  leg->Draw();
  //TLatex* texCmsc1 = new TLatex(0.14,0.94, "#scale[1.25]{CMS} Preliminary");
  //settex(texCmsc1,0.05,12);
  TLatex* texCmsc1 = new TLatex(0.21,0.89, "CMS");
  settex(texCmsc1,0.07,13);
  texCmsc1->SetTextFont(62);
  TLatex* texDzeroc1 = new TLatex(0.91,0.913, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  settex(texDzeroc1,0.07,33);
  texDzeroc1->SetTextFont(62);
  TString tlumi = isPbPb?"530 #mub^{-1} (5.02 TeV PbPb)":"27.4 pb^{-1} (5.02 TeV pp)";
  TLatex* texColc1 = new TLatex(0.94,0.95, Form("%s",tlumi.Data()));
  settex(texColc1,0.038,32);
  texCmsc1->Draw();
  texDzeroc1->Draw();
  texColc1->Draw();

  cfprompt->SaveAs(Form("plots/cfprompt_%s.pdf",tcoly.Data()));

}
