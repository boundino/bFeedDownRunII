using namespace std;
#include "uti.h"
#include "parameters.h"

void plotFractions(TString coly, TString outputFraction, Float_t centmin=0, Float_t centmax=0)
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
  TFile* inputfile = new TFile(Form("%s_%s.root",outputFraction.Data(),tcoly.Data()));
  TGraphAsymmErrors* grFraction = (TGraphAsymmErrors*)inputfile->Get("grPromptFraction");
  grFraction->SetLineWidth(1.);
  grFraction->SetMarkerSize(0.8);
  grFraction->SetMarkerStyle(20);
  grFraction->SetLineColor(kBlack);
  grFraction->SetMarkerColor(kBlack);
  TGraphAsymmErrors* grFraction3 = (TGraphAsymmErrors*)inputfile->Get("grPromptFraction3");
  grFraction3->SetLineWidth(1.);
  grFraction3->SetMarkerSize(0.8);
  grFraction3->SetMarkerStyle(20);
  grFraction3->SetLineColor(kBlack);
  grFraction3->SetMarkerColor(kBlack);

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
  TString tper = "%";
  TLatex* texCent = new TLatex(0.60,0.20, Form("Cent. %.0f-%.0f%s",centmin,centmax,tper.Data()));
  texCent->SetNDC();
  texCent->SetTextAlign(12);
  texCent->SetTextSize(0.04);
  texCent->SetTextFont(42);

  TCanvas* cMC = new TCanvas("cMC","",600,600);
  hempty->Draw();
  grFraction->Draw("psame");
  if(isPbPb) grFraction3->Draw("psame");
  if(isPbPb) texCent->Draw();
  drawCMS(coly);
  TLatex* texMethod = new TLatex(0.60,0.25, "FONLL + MC eff");
  texMethod->SetNDC();
  texMethod->SetTextAlign(12);
  texMethod->SetTextSize(0.04);
  texMethod->SetTextFont(42);
  texMethod->Draw();
  /*
  TLegend* legMC = new TLegend(0.30, 0.45, 0.80, 0.55);
  legMC->SetBorderSize(0);
  legMC->SetTextSize(0.04);
  legMC->SetTextFont(42);
  legMC->SetFillStyle(0);
  legMC->AddEntry(grFraction[0], "Inclusive", "pl");
  legMC->AddEntry(grFraction[1], "DCA < 0.008 cm", "pl");
  legMC->Draw();
  */
  cMC->SaveAs(Form("plots/cPromptFractionFONLL_%s.pdf",tcoly.Data()));

}

int main(int argc, char *argv[])
{
  if(argc==5)
    {
      plotFractions(argv[1],argv[2],atof(argv[3]), atof(argv[4]));
      return 0;
    }
  else if(argc==3)
    {
      plotFractions(argv[1],argv[2]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}
