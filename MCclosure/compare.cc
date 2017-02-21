using namespace std;
#include "uti.h"

void compare(TString col, TString outputfile, Float_t centmin=0, Float_t centmax=100)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1.8,"Y");
  gStyle->SetOptStat(0);

  Bool_t isPbPb = (col=="PbPb")?true:false;
  TFile* infAnaly = new TFile(Form("analysis/%scent%.0f%.0f/rootfiles/bFeedDownResult.root",col.Data(),centmin,centmax));
  TString outputname = isPbPb?Form("_%s_cent_%.0f_%.0f",col.Data(),centmin,centmax):Form("_%s",col.Data());
  TString outputnameMB = isPbPb?Form("_%sMB_cent_%.0f_%.0f",col.Data(),centmin,centmax):Form("_%sMB",col.Data());
  TFile* infTruth = new TFile(Form("%s%s.root",outputfile.Data(),outputname.Data()));
  TFile* infTruthMB = new TFile(Form("%s%s.root",outputfile.Data(),outputnameMB.Data()));
  
  TH1D* hAnaly = (TH1D*)infAnaly->Get("hFraction");
  hAnaly->SetName("hAnaly");
  hAnaly->SetMarkerSize(0.8);
  hAnaly->SetMarkerColor(kRed);
  hAnaly->SetLineColor(kRed);
  TH1D* hTruth = (TH1D*)infTruth->Get("hPromptFraction");
  hTruth->SetStats(0);
  hTruth->SetName("hTruth");
  hTruth->SetMarkerSize(0.8);
  hTruth->SetMarkerColor(kBlack);
  hTruth->SetLineColor(kBlack);
  TH1D* hTruthMB = (TH1D*)infTruthMB->Get("hPromptFraction");
  hTruthMB->SetStats(0);
  hTruthMB->SetName("hTruthMB");
  hTruthMB->SetMarkerSize(0.8);
  hTruthMB->SetMarkerColor(kBlack);
  hTruthMB->SetLineColor(kBlack);

  TCanvas* c = new TCanvas("c","",600,600);
  Float_t maxh = hTruthMB->GetMaximum()*1.6;
  TH2F* hempty = new TH2F("hempty",";D p_{T} (GeV/c);Prompt fraction",10,0,102,10,0,maxh);
  sethempty(hempty);
  hempty->Draw();
  hTruthMB->Draw("pesame");
  hTruth->Draw("pesame");
  hAnaly->Draw("pesame");
  TLegend* leg = new TLegend(0.60,0.75,0.90,0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(hAnaly,"DCA fitting","pl");
  leg->AddEntry(hTruth,"True fractions","pl");
  leg->Draw();
  drawCMS(col);
  TLatex* tex = new TLatex(0.23,0.83,"MC closure test");
  settex(tex);
  tex->Draw();
  TString per="%";
  TLatex* texp = new TLatex(0.23,0.78,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(texp);
  texp->Draw();
  c->SaveAs(Form("plots/compare%s.pdf",outputname.Data()));

}
