using namespace std;
#include "uti.h"

void finalPlotsRatio(Float_t centmin=0, Float_t centmax=100)
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

  TString colyPbPb = "PbPb";
  TString tcolyPbPb = Form("%s_cent_%.0f_%.0f",colyPbPb.Data(),centmin,centmax);
  TString tcolyDCAPbPb = Form("%scent%.0f%.0f",colyPbPb.Data(),centmin,centmax);
  TFile* inputDCAPbPb = new TFile(Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCAPbPb.Data()));
  cout<<Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCAPbPb.Data())<<endl;
  TFile* inputDCAfloatPbPb = new TFile(Form("../floatDCAwidth/%s/rootfiles/bFeedDownResult.root",tcolyDCAPbPb.Data()));
  cout<<Form("../floatDCAwidth/%s/rootfiles/bFeedDownResult.root",tcolyDCAPbPb.Data())<<endl;

  TString colyPP = "PP";
  TString tcolyPP = Form("%s",colyPP.Data());
  TString tcolyDCAPP = Form("%s",colyPP.Data());
  TFile* inputDCAPP = new TFile(Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCAPP.Data()));
  cout<<Form("../analysis/%s/rootfiles/bFeedDownResult.root",tcolyDCAPP.Data())<<endl;
  TFile* inputDCAfloatPP = new TFile(Form("../floatDCAwidth/%s/rootfiles/bFeedDownResult.root",tcolyDCAPP.Data()));
  cout<<Form("../floatDCAwidth/%s/rootfiles/bFeedDownResult.root",tcolyDCAPP.Data())<<endl;

  TGraphErrors* grFractionDCAPbPb = (TGraphErrors*)inputDCAPbPb->Get("grPromptFraction2");
  grFractionDCAPbPb->SetName("grFractionDCAPbPb");
  grFractionDCAPbPb->SetLineWidth(1.);
  grFractionDCAPbPb->SetMarkerSize(0.9);
  grFractionDCAPbPb->SetMarkerStyle(20);
  grFractionDCAPbPb->SetLineColor(kBlack);
  grFractionDCAPbPb->SetMarkerColor(kBlack);

  TGraphErrors* grFractionDCAfloatPbPb = (TGraphErrors*)inputDCAfloatPbPb->Get("grPromptFraction2");
  grFractionDCAfloatPbPb->SetName("grFractionDCAfloatPbPb");
  grFractionDCAfloatPbPb->SetLineWidth(1.);
  grFractionDCAfloatPbPb->SetMarkerSize(0.9);
  grFractionDCAfloatPbPb->SetMarkerStyle(20);
  grFractionDCAfloatPbPb->SetLineColor(kGreen+3);
  grFractionDCAfloatPbPb->SetMarkerColor(kGreen+3);

  TGraphErrors* grFractionDCAPP = (TGraphErrors*)inputDCAPP->Get("grPromptFraction2");
  grFractionDCAPP->SetName("grFractionDCAPP");
  grFractionDCAPP->SetLineWidth(1.);
  grFractionDCAPP->SetMarkerSize(0.9);
  grFractionDCAPP->SetMarkerStyle(20);
  grFractionDCAPP->SetLineColor(kBlack);
  grFractionDCAPP->SetMarkerColor(kBlack);

  TGraphErrors* grFractionDCAfloatPP = (TGraphErrors*)inputDCAfloatPP->Get("grPromptFraction2");
  grFractionDCAfloatPP->SetName("grFractionDCAfloatPP");
  grFractionDCAfloatPP->SetLineWidth(1.);
  grFractionDCAfloatPP->SetMarkerSize(0.9);
  grFractionDCAfloatPP->SetMarkerStyle(20);
  grFractionDCAfloatPP->SetLineColor(kGreen+3);
  grFractionDCAfloatPP->SetMarkerColor(kGreen+3);

  //
  
  TGraphErrors* grFractionRatio = (TGraphErrors*)grFractionDCAPbPb->Clone("grFractionRatio");
  grFractionRatio->SetLineWidth(1.);
  grFractionRatio->SetMarkerSize(0.9);
  grFractionRatio->SetMarkerStyle(20);
  grFractionRatio->SetLineColor(kBlack);
  grFractionRatio->SetMarkerColor(kBlack);
  
  TGraphErrors* grFractionRatiofloat = (TGraphErrors*)grFractionDCAfloatPbPb->Clone("grFractionRatiofloat");
  grFractionRatiofloat->SetLineWidth(1.);
  grFractionRatiofloat->SetMarkerSize(0.9);
  grFractionRatiofloat->SetMarkerStyle(20);
  grFractionRatiofloat->SetLineColor(kGreen+3);
  grFractionRatiofloat->SetMarkerColor(kGreen+3);
  
  TGraphErrors* grFractionRatioDerivationfloat = (TGraphErrors*)grFractionDCAfloatPbPb->Clone("grFractionRatioDerivationfloat");
  grFractionRatioDerivationfloat->SetLineWidth(1.);
  grFractionRatioDerivationfloat->SetMarkerSize(0.9);
  grFractionRatioDerivationfloat->SetMarkerStyle(20);
  grFractionRatioDerivationfloat->SetLineColor(kGreen+3);
  grFractionRatioDerivationfloat->SetMarkerColor(kGreen+3);
  
  for(int i=0;i<grFractionDCAPbPb->GetN();i++)
    {
      Double_t pt,fracDCAPbPb,fracDCAfloatPbPb;
      grFractionDCAPbPb->GetPoint(i,pt,fracDCAPbPb);
      grFractionDCAfloatPbPb->GetPoint(i,pt,fracDCAfloatPbPb);
      Double_t fracDCAPP,fracDCAfloatPP;
      grFractionDCAPP->GetPoint(i,pt,fracDCAPP);
      grFractionDCAfloatPP->GetPoint(i,pt,fracDCAfloatPP);

      Double_t fracDCARatio = fracDCAPbPb/fracDCAPP;
      Double_t efracDCARatio = TMath::Sqrt(pow(grFractionDCAPbPb->GetErrorY(i)/fracDCAPbPb,2)+pow(grFractionDCAPP->GetErrorY(i)/fracDCAPP,2))*fracDCARatio;
      grFractionRatio->SetPoint(i,pt,fracDCARatio);
      grFractionRatio->SetPointError(i,grFractionRatio->GetErrorX(i),efracDCARatio);
      Double_t fracDCARatiofloat = fracDCAfloatPbPb/fracDCAfloatPP;
      Double_t efracDCARatiofloat = TMath::Sqrt(pow(grFractionDCAfloatPbPb->GetErrorY(i)/fracDCAfloatPbPb,2)+pow(grFractionDCAfloatPP->GetErrorY(i)/fracDCAfloatPP,2))*fracDCARatiofloat;
      grFractionRatiofloat->SetPoint(i,pt,fracDCARatiofloat);
      grFractionRatiofloat->SetPointError(i,grFractionRatiofloat->GetErrorX(i),efracDCARatiofloat);

      grFractionRatioDerivationfloat->SetPoint(i,pt,100*(fracDCARatiofloat-fracDCARatio)/fracDCARatio);
      grFractionRatioDerivationfloat->SetPointError(i,grFractionRatioDerivationfloat->GetErrorX(i),100*efracDCARatio/fracDCARatio);
    }

  TH2F* hempty = new TH2F("hempty","",20,1.,200.,10.,0.,1.5);
  hempty->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("Prompt fraction Ratio (PbPb / PP)");
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.3);
  hempty->GetYaxis()->SetTitleOffset(1.2);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);

  TH2F* hempty2 = new TH2F("hempty2","",20,1.,200.,5.,-50,50);
  hempty2->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty2->GetYaxis()->SetTitle("Derivation (%)");
  hempty2->GetXaxis()->SetNdivisions(515);
  hempty2->GetYaxis()->SetNdivisions(505);
  hempty2->GetXaxis()->CenterTitle();
  hempty2->GetYaxis()->CenterTitle();
  hempty2->GetXaxis()->SetTitleOffset(1.0);
  hempty2->GetYaxis()->SetTitleOffset(0.58);
  hempty2->GetXaxis()->SetTitleSize(0.10);
  hempty2->GetYaxis()->SetTitleSize(0.10);
  hempty2->GetXaxis()->SetTitleFont(42);
  hempty2->GetYaxis()->SetTitleFont(42);
  hempty2->GetXaxis()->SetLabelFont(42);
  hempty2->GetYaxis()->SetLabelFont(42);
  hempty2->GetXaxis()->SetLabelSize(0.088);
  hempty2->GetYaxis()->SetLabelSize(0.088);

  TCanvas* c2 = new TCanvas("c2","",600,800);
  TPad* pad1 = new TPad("pad1","",0,0.30,1,1);
  pad1->SetLogx();
  pad1->SetBottomMargin(0);
  pad1->SetRightMargin(0.043);
  pad1->SetLeftMargin(0.12);
  pad1->SetTopMargin(0.1);
  pad1->Draw();
  pad1->cd();
  hempty->Draw();
  grFractionRatiofloat->Draw("samepe");
  grFractionRatio->Draw("samepe");
  TLatex* texCms = new TLatex(0.12,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",colyPbPb.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();
  TLegend* leg = new TLegend(0.30,0.11,0.90,0.23);
  setleg(leg);
  leg->AddEntry(grFractionRatio,"Fit DCA","pl");
  leg->AddEntry(grFractionRatiofloat,"Fit DCA (float DCA width)","pl");
  leg->Draw();
  TString per = "%";
  TLatex* centtex = new TLatex(0.32,0.26,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(centtex);
  centtex->Draw();
  c2->cd();

  TPad* pad2 = new TPad("pad2","",0,0,1,0.30);
  pad2->SetLogx();
  pad2->SetTopMargin(0);
  pad2->SetRightMargin(0.043);
  pad2->SetLeftMargin(0.12);
  pad2->SetBottomMargin(0.25);
  pad2->Draw();
  pad2->cd();
  hempty2->Draw();
  TLine* l = new TLine(1,0,200,0);
  l->SetLineStyle(2);
  l->SetLineColor(kBlack);
  l->SetLineWidth(2);
  l->Draw();
  grFractionRatioDerivationfloat->Draw("samepe");
  c2->cd();

  c2->SaveAs(Form("plots/cfpromptRatio_%s.pdf",tcolyPbPb.Data()));

}
