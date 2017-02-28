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
  TFile* inputDCAfloat = new TFile(Form("../floatDCAwidth/%s/rootfiles/bFeedDownResult.root",tcolyDCA.Data()));

  TGraphErrors* grFractionDCA = (TGraphErrors*)inputDCA->Get("grPromptFraction2");
  grFractionDCA->SetName("grFractionDCA");
  grFractionDCA->SetLineWidth(1.);
  grFractionDCA->SetMarkerSize(0.8);
  grFractionDCA->SetMarkerStyle(20);
  grFractionDCA->SetLineColor(kBlack);
  grFractionDCA->SetMarkerColor(kBlack);

  TGraphErrors* grFractionDCAfloat = (TGraphErrors*)inputDCAfloat->Get("grPromptFraction2");
  grFractionDCAfloat->SetName("grFractionDCAfloat");
  grFractionDCAfloat->SetLineWidth(1.);
  grFractionDCAfloat->SetMarkerSize(0.8);
  grFractionDCAfloat->SetMarkerStyle(20);
  grFractionDCAfloat->SetLineColor(kGreen+3);
  grFractionDCAfloat->SetMarkerColor(kGreen+3);

  TGraphAsymmErrors* grFraction = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction");
  grFraction->SetLineWidth(1.);
  grFraction->SetMarkerSize(0.8);
  grFraction->SetMarkerStyle(20);
  grFraction->SetLineColor(kRed);
  grFraction->SetMarkerColor(kRed);
  TGraphAsymmErrors* grFraction3 = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3");
  TGraphAsymmErrors* grFractionDa = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFractionDa");
  TGraphAsymmErrors* grFraction3Da = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3Da");
  TGraphAsymmErrors* grFractionNPJ = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFractionNPJ");
  TGraphAsymmErrors* grFraction3NPJ = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3NPJ");

  TGraphAsymmErrors* grFractionRatio = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction");
  grFractionRatio->SetName("grFractionRatio");
  grFractionRatio->SetLineWidth(1.);
  grFractionRatio->SetMarkerSize(0.8);
  grFractionRatio->SetMarkerStyle(20);
  grFractionRatio->SetLineColor(kBlack);
  grFractionRatio->SetMarkerColor(kBlack);
  TGraphAsymmErrors* grFractionRatiofloat = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction");
  grFractionRatiofloat->SetName("grFractionRatiofloat");
  grFractionRatiofloat->SetLineWidth(1.);
  grFractionRatiofloat->SetMarkerSize(0.8);
  grFractionRatiofloat->SetMarkerStyle(20);
  grFractionRatiofloat->SetLineColor(kGreen+3);
  grFractionRatiofloat->SetMarkerColor(kGreen+3);
  TGraphAsymmErrors* grFractionRatio3 = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3");
  TGraphAsymmErrors* grFractionRatio3Da = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3Da");
  TGraphAsymmErrors* grFractionRatio3NPJ = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3NPJ");

  TH1F* hBoverDh = (TH1F*)inputFONLL->Get("hBoverDh");
  TH1F* hBoverDl = (TH1F*)inputFONLL->Get("hBoverDl");
  TH1F* hBoverDhDa = (TH1F*)inputFONLL->Get("hBoverDhDa");
  TH1F* hBoverDlDa = (TH1F*)inputFONLL->Get("hBoverDlDa");
  TH1F* hBoverDhNPJ = (TH1F*)inputFONLL->Get("hBoverDhNPJ");
  TH1F* hBoverDlNPJ = (TH1F*)inputFONLL->Get("hBoverDlNPJ");
  TGraphAsymmErrors* grBoverD3 = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3");
  TGraphAsymmErrors* grBoverD3Da = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3Da");
  TGraphAsymmErrors* grBoverD3NPJ = (TGraphAsymmErrors*)inputFONLL->Get("grPromptFraction3NPJ");

  for(int i=0;i<grFraction->GetN();i++)
    {
      Double_t pt,fracDCA,fracDCAfloat;
      grFractionDCA->GetPoint(i,pt,fracDCA);
      grFractionDCA->SetPointError(i,0,grFractionDCA->GetErrorY(i));
      grFractionDCAfloat->GetPoint(i,pt,fracDCAfloat);
      grFractionDCAfloat->SetPointError(i,0,grFractionDCAfloat->GetErrorY(i));

      Double_t frac,frac3;
      grFraction->GetPoint(i,pt,frac);
      grFraction3->GetPoint(i,pt,frac3);
      Double_t fcenter = (frac+frac3)/2.;
      Double_t ferror = (frac-frac3)/2.;
      grFraction3->SetPoint(i,pt,fcenter);
      grFraction3->SetPointEYlow(i,ferror);
      grFraction3->SetPointEYhigh(i,ferror);
      Double_t rh = fracDCA/frac;
      Double_t rl = fracDCA/frac3;
      Double_t rcenter = (rh+rl)/2.;
      Double_t rerror = (rh-rl)/2.;
      grFractionRatio3->SetPoint(i,pt,rcenter);
      grFractionRatio3->SetPointEYlow(i,rerror);
      grFractionRatio3->SetPointEYhigh(i,rerror);
      Double_t BoverDcenter = (hBoverDh->GetBinContent(i+1)+hBoverDl->GetBinContent(i+1))/2.;
      Double_t BoverDerror = (hBoverDh->GetBinContent(i+1)-hBoverDl->GetBinContent(i+1))/2.;
      grBoverD3->SetPoint(i,pt,BoverDcenter);
      grBoverD3->SetPointEYlow(i,BoverDerror);
      grBoverD3->SetPointEYhigh(i,BoverDerror);

      grFractionRatio->SetPoint(i,pt,fracDCA/frac);
      grFractionRatio->SetPointEYlow(i,0);
      grFractionRatio->SetPointEYhigh(i,0);

      grFractionRatiofloat->SetPoint(i,pt,fracDCAfloat/frac);
      grFractionRatiofloat->SetPointEYlow(i,0);
      grFractionRatiofloat->SetPointEYhigh(i,0);

      Double_t fracDa,frac3Da;
      grFractionDa->GetPoint(i,pt,fracDa);
      grFraction3Da->GetPoint(i,pt,frac3Da);
      Double_t fcenterDa = (fracDa+frac3Da)/2.;
      Double_t ferrorDa = (fracDa-frac3Da)/2.;
      grFraction3Da->SetPoint(i,pt,fcenterDa);
      grFraction3Da->SetPointEYlow(i,ferrorDa);
      grFraction3Da->SetPointEYhigh(i,ferrorDa);
      Double_t rhDa = fracDCA/fracDa;
      Double_t rlDa = fracDCA/frac3Da;
      Double_t rcenterDa = (rhDa+rlDa)/2.;
      Double_t rerrorDa = (rhDa-rlDa)/2.;
      grFractionRatio3Da->SetPoint(i,pt,rcenterDa);
      grFractionRatio3Da->SetPointEYlow(i,rerrorDa);
      grFractionRatio3Da->SetPointEYhigh(i,rerrorDa);
      Double_t BoverDcenterDa = (hBoverDhDa->GetBinContent(i+1)+hBoverDlDa->GetBinContent(i+1))/2.;
      Double_t BoverDerrorDa = (hBoverDhDa->GetBinContent(i+1)-hBoverDlDa->GetBinContent(i+1))/2.;
      grBoverD3Da->SetPoint(i,pt,BoverDcenterDa);
      grBoverD3Da->SetPointEYlow(i,BoverDerrorDa);
      grBoverD3Da->SetPointEYhigh(i,BoverDerrorDa);

      Double_t fracNPJ,frac3NPJ;
      grFractionNPJ->GetPoint(i,pt,fracNPJ);
      grFraction3NPJ->GetPoint(i,pt,frac3NPJ);
      Double_t fcenterNPJ = (fracNPJ+frac3NPJ)/2.;
      Double_t ferrorNPJ = (fracNPJ-frac3NPJ)/2.;
      grFraction3NPJ->SetPoint(i,pt,fcenterNPJ);
      grFraction3NPJ->SetPointEYlow(i,ferrorNPJ);
      grFraction3NPJ->SetPointEYhigh(i,ferrorNPJ);
      Double_t rhNPJ = fracDCA/fracNPJ;
      Double_t rlNPJ = fracDCA/frac3NPJ;
      Double_t rcenterNPJ = (rhNPJ+rlNPJ)/2.;
      Double_t rerrorNPJ = (rhNPJ-rlNPJ)/2.;
      grFractionRatio3NPJ->SetPoint(i,pt,rcenterNPJ);
      grFractionRatio3NPJ->SetPointEYlow(i,rerrorNPJ);
      grFractionRatio3NPJ->SetPointEYhigh(i,rerrorNPJ);
      Double_t BoverDcenterNPJ = (hBoverDhNPJ->GetBinContent(i+1)+hBoverDlNPJ->GetBinContent(i+1))/2.;
      Double_t BoverDerrorNPJ = (hBoverDhNPJ->GetBinContent(i+1)-hBoverDlNPJ->GetBinContent(i+1))/2.;
      grBoverD3NPJ->SetPoint(i,pt,BoverDcenterNPJ);
      grBoverD3NPJ->SetPointEYlow(i,BoverDerrorNPJ);
      grBoverD3NPJ->SetPointEYhigh(i,BoverDerrorNPJ);

    }

  grFraction3->SetFillStyle(1001);
  grFraction3->SetLineColor(kRed-9);
  grFraction3->SetFillColor(kRed-9);
  grFraction3Da->SetFillStyle(1001);
  grFraction3Da->SetLineColor(kAzure-9);
  grFraction3Da->SetFillColor(kAzure-9);
  grFraction3NPJ->SetFillStyle(1001);
  grFraction3NPJ->SetLineColor(kViolet+6);
  grFraction3NPJ->SetFillColorAlpha(kViolet+6,0.4);

  grFractionRatio3->SetFillStyle(1001);
  grFractionRatio3->SetLineColor(kRed-9);
  grFractionRatio3->SetFillColor(kRed-9);
  grFractionRatio3Da->SetFillStyle(1001);
  grFractionRatio3Da->SetLineColor(kAzure-9);
  grFractionRatio3Da->SetFillColor(kAzure-9);
  grFractionRatio3NPJ->SetFillStyle(1001);
  grFractionRatio3NPJ->SetLineColor(kViolet+6);
  grFractionRatio3NPJ->SetFillColorAlpha(kViolet+6,0.4);

  grBoverD3->SetFillStyle(1001);
  grBoverD3->SetLineColor(kRed-9);
  grBoverD3->SetFillColor(kRed-9);
  grBoverD3Da->SetFillStyle(1001);
  grBoverD3Da->SetLineColor(kAzure-9);
  grBoverD3Da->SetFillColor(kAzure-9);
  grBoverD3NPJ->SetFillStyle(1001);
  grBoverD3NPJ->SetLineColor(kViolet+6);
  grBoverD3NPJ->SetFillColorAlpha(kViolet+6,0.4);

  TH2F* hempty = new TH2F("hempty","",20,1.,200.,10.,0.,1.1);
  hempty->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("Prompt fraction");
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

  TH2F* hempty2 = new TH2F("hempty2","",20,1.,200.,5.,0.4,1.6);
  hempty2->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty2->GetYaxis()->SetTitle("Fit / FONLL");
  hempty2->GetXaxis()->SetNdivisions(515);
  hempty2->GetYaxis()->SetNdivisions(505);
  hempty2->GetXaxis()->CenterTitle();
  hempty2->GetYaxis()->CenterTitle();
  hempty2->GetXaxis()->SetTitleOffset(1.0);
  hempty2->GetYaxis()->SetTitleOffset(0.5);
  hempty2->GetXaxis()->SetTitleSize(0.10);
  hempty2->GetYaxis()->SetTitleSize(0.10);
  hempty2->GetXaxis()->SetTitleFont(42);
  hempty2->GetYaxis()->SetTitleFont(42);
  hempty2->GetXaxis()->SetLabelFont(42);
  hempty2->GetYaxis()->SetLabelFont(42);
  hempty2->GetXaxis()->SetLabelSize(0.088);
  hempty2->GetYaxis()->SetLabelSize(0.088);

  TH2F* hempty3 = new TH2F("hempty3","",20,1.,200.,5.,0.,3.5);
  hempty3->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty3->GetYaxis()->SetTitle("B R_{AA} / D R_{AA}");
  hempty3->GetXaxis()->SetNdivisions(515);
  hempty3->GetYaxis()->SetNdivisions(505);
  hempty3->GetXaxis()->CenterTitle();
  hempty3->GetYaxis()->CenterTitle();
  hempty3->GetXaxis()->SetTitleOffset(1.0);
  hempty3->GetYaxis()->SetTitleOffset(0.5);
  hempty3->GetXaxis()->SetTitleSize(0.10);
  hempty3->GetYaxis()->SetTitleSize(0.10);
  hempty3->GetXaxis()->SetTitleFont(42);
  hempty3->GetYaxis()->SetTitleFont(42);
  hempty3->GetXaxis()->SetLabelFont(42);
  hempty3->GetYaxis()->SetLabelFont(42);
  hempty3->GetXaxis()->SetLabelSize(0.088);
  hempty3->GetYaxis()->SetLabelSize(0.088);

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
  if(isPbPb) grFraction3->Draw("same2");
  else grFraction->Draw("samepe");
  if(isPbPb) grFraction3Da->Draw("same2");
  if(isPbPb) grFraction3NPJ->Draw("same5");
  grFractionDCA->Draw("samepe");
  grFractionDCAfloat->Draw("samepe");
  TLatex* texCms = new TLatex(0.12,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",coly.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();
  //drawCMS(coly);
  TLegend* leg;
  if(!isPbPb)
    {
      leg = new TLegend(0.30,0.15,0.90,0.33);
      setleg(leg);
      leg->AddEntry(grFractionDCA,"Fit DCA","pl");
      leg->AddEntry(grFractionDCAfloat,"Fit DCA (float DCA width)","pl");
      leg->AddEntry(grFraction,"FONLL + MC eff","pl");          
    }
  else
    {
      leg = new TLegend(0.24,0.03,0.75,0.33);
      setleg(leg);
      leg->AddEntry(grFractionDCA,"Fit DCA","pl");
      leg->AddEntry(grFractionDCAfloat,"Fit DCA (float DCA width)","pl");
      leg->AddEntry(grFraction3Da,"FONLL (B R_{AA} / D R_{AA} from data)","f");
      leg->AddEntry(grFraction3,"FONLL (B R_{AA} / D R_{AA} varies 0.2~2(3))","f");
      leg->AddEntry(grFraction3NPJ,"FONLL (J/#psi R_{AA} / D R_{AA} from data)","f");
    }
  leg->Draw();
  TString per = "%";
  TLatex* centtex = new TLatex(0.26,0.36,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(centtex);
  if(isPbPb) centtex->Draw();
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
  if(isPbPb) grFractionRatio3->Draw("same2");
  else 
    {
      grFractionRatio->Draw("samepe");
      grFractionRatiofloat->Draw("samepe");
    }
  if(isPbPb) grFractionRatio3Da->Draw("same2");
  if(isPbPb) grFractionRatio3NPJ->Draw("same5");
  TLine* l = new TLine(1,1,200,1);
  l->SetLineStyle(2);
  l->SetLineColor(kBlack);
  l->SetLineWidth(2);
  l->Draw();
  c2->cd();

  c2->SaveAs(Form("plots/cfpromptComparisonVsfloat_%s.pdf",tcoly.Data()));

  if(isPbPb)
    {
      TCanvas* c3 = new TCanvas("c3","",600,1040);
      TPad* pad31 = new TPad("pad31","",0,0.46154,1,1);
      pad31->SetLogx();
      pad31->SetBottomMargin(0);
      pad31->SetRightMargin(0.043);
      pad31->SetLeftMargin(0.12);
      pad31->SetTopMargin(0.1);
      pad31->Draw();
      pad31->cd();
      hempty->Draw();
      if(isPbPb) grFraction3->Draw("same2");
      else grFraction->Draw("samepe");
      if(isPbPb) grFraction3Da->Draw("same2");
      if(isPbPb) grFraction3NPJ->Draw("same5");
      grFractionDCA->Draw("samepe");
      grFractionDCAfloat->Draw("samepe");
      texCms->Draw();
      texCol->Draw();
      leg->Draw();
      if(isPbPb) centtex->Draw();
      c3->cd();
      
      TPad* pad32 = new TPad("pad32","",0,0.23077,1,0.46154);
      pad32->SetLogx();
      pad32->SetTopMargin(0);
      pad32->SetRightMargin(0.043);
      pad32->SetLeftMargin(0.12);
      pad32->SetBottomMargin(0);
      pad32->Draw();
      pad32->cd();
      hempty2->Draw();
      if(isPbPb) grFractionRatio3->Draw("same2");
      else grFractionRatio->Draw("samepe");
      if(isPbPb) grFractionRatio3Da->Draw("same2");
      if(isPbPb) grFractionRatio3NPJ->Draw("same5");
      l->Draw();
      c3->cd();

      TPad* pad33 = new TPad("pad33","",0,0,1,0.23077);
      pad33->SetLogx();
      pad33->SetTopMargin(0);
      pad33->SetRightMargin(0.043);
      pad33->SetLeftMargin(0.12);
      pad33->SetBottomMargin(0.25);
      pad33->Draw();
      pad33->cd();
      hempty3->Draw();
      grBoverD3->Draw("same2");
      grBoverD3Da->Draw("same2");
      grBoverD3NPJ->Draw("same5");
      l->Draw();
      c3->cd();      
      
      c3->SaveAs(Form("plots/cfpromptComparisonFullVsfloat_%s.pdf",tcoly.Data()));
      
    }
}
