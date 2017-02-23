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
  TString tcoly = isPbPb?Form("%scent%.0f%.0f",col.Data(),centmin,centmax):Form("%s",col.Data());
  TFile* infAnaly = new TFile(Form("analysis/%s/rootfiles/bFeedDownResult.root",tcoly.Data()));
  TString outputname = isPbPb?Form("%s_cent_%.0f_%.0f",col.Data(),centmin,centmax):Form("%s",col.Data());
  TString outputnameMB = isPbPb?Form("%sMB_cent_%.0f_%.0f",col.Data(),centmin,centmax):Form("%sMB",col.Data());
  TFile* infTruth = new TFile(Form("%s_%s.root",outputfile.Data(),outputname.Data()));
  TFile* infTruthMB = new TFile(Form("%s_%s.root",outputfile.Data(),outputnameMB.Data()));

  int nptbinsAll,nptbinsMB;
  if(isPbPb)
    {
      nptbinsAll = 13;
      nptbinsMB = 8;
    }
  else
    {
      nptbinsAll = 14;
      nptbinsMB = 9;
    }
  
  TH1D* hAnaly = (TH1D*)infAnaly->Get("hFraction");
  hAnaly->SetName("hAnaly");
  hAnaly->SetMarkerSize(0.8);
  hAnaly->SetMarkerColor(kRed);
  hAnaly->SetLineColor(kRed);
  TH1D* hTruth = (TH1D*)infTruth->Get("hPromptFraction");
  hTruth->SetName("hTruth");
  TH1D* hTruthMB = (TH1D*)infTruthMB->Get("hPromptFraction");
  hTruthMB->SetName("hTruthMB");
  TH1D* hTruthAll = (TH1D*)hAnaly->Clone("hTruthAll");
  for(int i=0;i<nptbinsAll;i++)
    {
      if(i<nptbinsMB)
        {
          hTruthAll->SetBinContent(i+1,hTruthMB->GetBinContent(i+1));
          hTruthAll->SetBinError(i+1,hTruthMB->GetBinError(i+1));
        }
      else
        {
          hTruthAll->SetBinContent(i+1,hTruth->GetBinContent(i-7));
          hTruthAll->SetBinError(i+1,hTruth->GetBinError(i-7));          
        }
    }
  hTruthAll->SetStats(0);
  hTruthAll->SetMarkerSize(0.8);
  hTruthAll->SetMarkerColor(kBlack);
  hTruthAll->SetLineColor(kBlack);
  TH1D* hRatio = (TH1D*)hAnaly->Clone("hRatio");
  hRatio->Divide(hTruthAll);

  TCanvas* c2 = new TCanvas("c2","",600,800);
  TPad* pad1 = new TPad("pad1","",0,0.30,1,1);
  pad1->SetBottomMargin(0);
  pad1->SetRightMargin(0.043);
  pad1->SetLeftMargin(0.12);
  pad1->SetTopMargin(0.1);
  pad1->Draw();
  pad1->cd();
  Float_t maxh = hTruthMB->GetMaximum()*1.6;
  TH2F* hempty = new TH2F("hempty",";D p_{T} (GeV/c);Prompt fraction",10,0,102,10,0,maxh);
  sethempty(hempty);
  hempty->GetXaxis()->SetTitleOffset(1.3);
  hempty->GetYaxis()->SetTitleOffset(1.2);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);
  hempty->Draw();
  hTruthAll->Draw("pesame");
  hAnaly->Draw("pesame");
  TLegend* leg = new TLegend(0.60,0.75,0.90,0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(hAnaly,"DCA fitting","pl");
  leg->AddEntry(hTruthAll,"True fractions","pl");
  leg->Draw();
  TLatex* tex = new TLatex(0.20,0.83,"MC closure test");
  settex(tex);
  tex->Draw();
  TString per="%";
  TLatex* texp = new TLatex(0.20,0.78,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(texp);
  if(isPbPb) texp->Draw();
  TLatex* texCms = new TLatex(0.12,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",col.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  c2->cd();

  TPad* pad2 = new TPad("pad2","",0,0,1,0.30);
  pad2->SetTopMargin(0);
  pad2->SetRightMargin(0.043);
  pad2->SetLeftMargin(0.12);
  pad2->SetBottomMargin(0.25);
  pad2->Draw();
  pad2->cd();
  TH2F* hempty2 = new TH2F("hempty2","",20,0.,102.,5.,0.4,1.6);
  hempty2->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty2->GetYaxis()->SetTitle("Fit / True");
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
  hempty2->Draw();

  TLine* l = new TLine(0,1,102,1);
  l->SetLineStyle(2);
  l->SetLineColor(kBlack);
  l->SetLineWidth(2);
  l->Draw();
  hRatio->Draw("pesame");
  c2->cd();

  c2->SaveAs(Form("plots/cclosure_%s.pdf",outputname.Data()));
  c2->SaveAs(Form("plots/cclosure_%s.png",outputname.Data()));

  /*
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
  */
}
