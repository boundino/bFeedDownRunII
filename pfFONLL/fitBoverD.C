using namespace std;
#include "uti.h"
#include "parameters.h"

void fitBoverD(TString output)
{
  setgstyle();
  const int nPtBinsD = 9;
  Float_t ptBinsD[nPtBinsD+1] = {6.,8.,10.,12.5,15.,20.,25.,30.,40.,60.};
  ifstream infD("dats/RAA_D_0100.dat");
  Float_t DRAAs[nPtBinsD],leDRAAs[nPtBinsD],heDRAAs[nPtBinsD],ptD[nPtBinsD],eptD[nPtBinsD];
  for(int i=0;i<nPtBinsD;i++) infD>>DRAAs[i]>>leDRAAs[i]>>heDRAAs[i];
  for(int i=0;i<nPtBinsD;i++)
    {
      ptD[i] = (ptBinsD[i]+ptBinsD[i+1])/2.;
      eptD[i] = 0;        
    }
  
  const int nPtBinsB = 5;
  Float_t ptBinsB[nPtBinsB+1] = {7.,10.,15.,20.,30.,50.};
  ifstream infB("dats/RAA_B_0100.dat");
  Float_t BRAAs[nPtBinsB],leBRAAs[nPtBinsB],heBRAAs[nPtBinsB],ptB[nPtBinsB],eptB[nPtBinsB];
  Float_t temp;
  for(int i=0;i<nPtBinsB;i++) infB>>temp>>BRAAs[i]>>temp>>leBRAAs[i]>>temp>>heBRAAs[i];
  TH1F* hBRAAh = new TH1F("hBRAAh","",nPtBinsB,ptBinsB);
  TH1F* hBRAAl = new TH1F("hBRAAl","",nPtBinsB,ptBinsB);
  for(int i=0;i<nPtBinsB;i++)
    {
      hBRAAh->SetBinContent(i+1,heBRAAs[i]);
      hBRAAl->SetBinContent(i+1,leBRAAs[i]);
      ptB[i] = (ptBinsB[i]+ptBinsB[i+1])/2.;
      eptB[i] = (ptBinsB[i+1]-ptBinsB[i])/2.;        
      leBRAAs[i] = BRAAs[i]-leBRAAs[i];
      heBRAAs[i] = -BRAAs[i]+heBRAAs[i];      
    }
  TGraphAsymmErrors* grBRAA = new TGraphAsymmErrors(nPtBinsB,ptB,BRAAs,eptB,eptB,leBRAAs,heBRAAs);  
  grBRAA->SetFillStyle(3001);
  grBRAA->SetFillColor(kAzure-2);
  grBRAA->SetLineWidth(0);
  TGraphAsymmErrors* grDRAA = new TGraphAsymmErrors(nPtBinsD,ptD,DRAAs,eptD,eptD,leDRAAs,heDRAAs);
  settgraphasymmerrors(grDRAA);
  TH2F* hempty = new TH2F("hempty",";D p_{T} (GeV/c);R_{AA}",10,0,62,10,0,1.2);
  sethempty(hempty);

  //

  TCanvas* cBoverD = new TCanvas("cBoverD","",1200,600);
  cBoverD->Divide(2,1);

  cBoverD->cd(1);
  hempty->Draw();
  grBRAA->Draw("2same");
  grDRAA->Draw("pesame");
  TF1* fDRAA = new TF1("fDRAA","[0]*x+[1]",6,60);
  fDRAA->SetLineColor(kRed);
  fDRAA->SetLineWidth(2);
  grDRAA->Fit(fDRAA,"","",6,60);
  TLegend* legD = new TLegend(0.58,0.70,0.94,0.82);
  setleg(legD,0.045);
  legD->AddEntry(grDRAA,"D^{0}, |y|<1.0","pl");
  legD->AddEntry(grBRAA,"B^{+}, |y|<2.4","f");
  legD->Draw();
  drawCMS("PbPb");

  cBoverD->cd(2);
  TH1F* hBoverDh = new TH1F("hBoverDh","",nPtBins,ptBins);
  hBoverDh->SetLineColor(kRed);
  TH1F* hBoverDl = new TH1F("hBoverDl","",nPtBins,ptBins);
  hBoverDl->SetLineColor(kRed);
  for(int i=0;i<nPtBins;i++)
    {
      Float_t apt = (ptBins[i]+ptBins[i+1])/2.;
      if(ptBins[i]<8. || ptBins[i+1]>40.)
        {
          hBoverDh->SetBinContent(i+1,3);
          hBoverDl->SetBinContent(i+1,1);
        }
      else
        {
          int j;
          for(j=0;j<nPtBinsB;j++)
            {
              if(ptBins[i]>=ptBinsB[j] && ptBins[i+1]<=ptBinsB[j+1]) break;
            }
          if(j>=nPtBinsB)
            {
              cout<<"  Error: Over B RAA range."<<endl;
              continue;
            }
          hBoverDh->SetBinContent(i+1,hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt));
          hBoverDl->SetBinContent(i+1,hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt));
        }
    }
  TH2F* hempty2 = new TH2F("hempty2",";p_{T} (GeV/c);R_{AA}(B) / R_{AA}(D)",10,0,102,10,0,3.5);
  sethempty(hempty2);

  hempty2->Draw();
  hBoverDh->Draw("same");
  hBoverDl->Draw("same");
  drawCMS("PbPb");

  cBoverD->SaveAs("plots/cBoverD.pdf");

  TFile* outputfile = new TFile(output,"recreate");
  outputfile->cd();
  hBoverDh->Write();
  hBoverDl->Write();
  outputfile->Close();

  TCanvas* cFit = new TCanvas("cFit","",600,600);
  hempty->Draw();
  grBRAA->Draw("2same");
  grDRAA->Draw("pesame");
  fDRAA->Draw("same");
  legD->Draw();
  drawCMS("PbPb");
  cFit->SaveAs("plots/cBoverD_Fit.pdf");
  TCanvas* cResult = new TCanvas("cResult","",600,600);
  hempty2->Draw();
  hBoverDh->Draw("same");
  hBoverDl->Draw("same");
  drawCMS("PbPb");
  cResult->SaveAs("plots/cBoverD_Result.pdf");
}

int main(int argc, char* argv[])
{
  if(argc==2)
    {
      fitBoverD(argv[1]);
      return 0;
    }
  else
    {
      cout<<"  Error: invalid arguments number."<<endl;
      return 1;
    }
}
