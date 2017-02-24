using namespace std;
#include "uti.h"
#include "parameters.h"

void fitBoverD(TString output)
{
  setgstyle();
  fillptbins(true);
  const int nPtBinsD = 13;
  Float_t ptBinsD[nPtBinsD+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.,20.,25.,30.,40.,60.};
  ifstream infD("dats/RAA_D_0100.dat");
  Float_t DRAAs[nPtBinsD],leDRAAs[nPtBinsD],heDRAAs[nPtBinsD],ptD[nPtBinsD],eptD[nPtBinsD];
  for(int i=0;i<nPtBinsD;i++) infD>>DRAAs[i]>>leDRAAs[i]>>heDRAAs[i];
  for(int i=0;i<nPtBinsD;i++)
    {
      ptD[i] = (ptBinsD[i]+ptBinsD[i+1])/2.;
      eptD[i] = 0;        
    }
  TGraphAsymmErrors* grDRAA = new TGraphAsymmErrors(nPtBinsD,ptD,DRAAs,eptD,eptD,leDRAAs,heDRAAs);
  settgraphasymmerrors(grDRAA);
  
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
  grBRAA->SetFillStyle(1001);
  grBRAA->SetFillColor(kAzure-9);
  grBRAA->SetLineWidth(0);

  const int nPtBinsNPJ = 9;
  Float_t ptBinsNPJ[nPtBinsNPJ+1] = {3.,4.5,5.5,6.5,8.5,9.5,11.,13.,16.,30.};
  ifstream infNPJ("dats/RAA_NPJpsi_0100.dat");
  Float_t NPJRAAs[nPtBinsNPJ],leNPJRAAs[nPtBinsNPJ],heNPJRAAs[nPtBinsNPJ],ptNPJ[nPtBinsNPJ],eptNPJ[nPtBinsNPJ];
  for(int i=0;i<nPtBinsNPJ;i++) infNPJ>>temp>>NPJRAAs[i]>>temp>>leNPJRAAs[i]>>temp>>heNPJRAAs[i];
  TH1F* hNPJRAAh = new TH1F("hNPJRAAh","",nPtBinsNPJ,ptBinsNPJ);
  TH1F* hNPJRAAl = new TH1F("hNPJRAAl","",nPtBinsNPJ,ptBinsNPJ);
  for(int i=0;i<nPtBinsNPJ;i++)
    {
      hNPJRAAh->SetBinContent(i+1,heNPJRAAs[i]);
      hNPJRAAl->SetBinContent(i+1,leNPJRAAs[i]);
      ptNPJ[i] = (ptBinsNPJ[i]+ptBinsNPJ[i+1])/2.;
      eptNPJ[i] = (ptBinsNPJ[i+1]-ptBinsNPJ[i])/2.;        
      leNPJRAAs[i] = NPJRAAs[i]-leNPJRAAs[i];
      heNPJRAAs[i] = -NPJRAAs[i]+heNPJRAAs[i];      
    }
  TGraphAsymmErrors* grNPJRAA = new TGraphAsymmErrors(nPtBinsNPJ,ptNPJ,NPJRAAs,eptNPJ,eptNPJ,leNPJRAAs,heNPJRAAs);  
  grNPJRAA->SetFillStyle(3005);
  grNPJRAA->SetFillColor(kViolet+6);
  //grNPJRAA->SetFillStyle(1001);
  //grNPJRAA->SetFillColorAlpha(kViolet+6,0.5);
  grNPJRAA->SetLineWidth(1);
  grNPJRAA->SetLineColor(kViolet+2);

  //

  TCanvas* cBoverD = new TCanvas("cBoverD","",1200,600);
  cBoverD->Divide(2,1);

  cBoverD->cd(1);
  gPad->SetLogx();
  TH2F* hempty = new TH2F("hempty",";D p_{T} (GeV/c);R_{AA}",10,1,100,10,0,1.3);
  sethempty(hempty);

  hempty->Draw();
  grBRAA->Draw("2same");
  grNPJRAA->Draw("5same");
  grDRAA->Draw("pesame");
  TF1* fDRAA = new TF1("fDRAA","[0]+[1]*log(x)+[2]*log(x)*log(x)+[3]*log(x)*log(x)*log(x)",2,60);
  fDRAA->SetLineColor(kRed);
  fDRAA->SetLineWidth(2);
  grDRAA->Fit(fDRAA,"","",2,60);
  TLegend* legD = new TLegend(0.45,0.70,0.86,0.88);
  setleg(legD,0.045);
  legD->AddEntry(grDRAA,"D^{0}, |y|<1.0","pl");
  legD->AddEntry(grBRAA,"B^{+}, |y|<2.4","f");
  legD->AddEntry(grNPJRAA,"NP J/#psi, (1.6<)|y|<2.4","f");
  legD->Draw();
  drawCMS("PbPb");

  cBoverD->cd(2);
  //gPad->SetLogx();
  TH1F* hBoverDh = new TH1F("hBoverDh","",nPtBins,ptBins);
  hBoverDh->SetLineColor(kBlack);
  TH1F* hBoverDl = new TH1F("hBoverDl","",nPtBins,ptBins);
  hBoverDl->SetLineColor(kBlack);
  TH1F* hBoverDhDa = new TH1F("hBoverDhDa","",nPtBins,ptBins);
  hBoverDhDa->SetLineColor(kBlack);
  TH1F* hBoverDlDa = new TH1F("hBoverDlDa","",nPtBins,ptBins);
  hBoverDlDa->SetLineColor(kBlack);
  TH1F* hBoverDhNPJ = new TH1F("hBoverDhNPJ","",nPtBins,ptBins);
  hBoverDhNPJ->SetLineColor(kBlack);
  TH1F* hBoverDlNPJ = new TH1F("hBoverDlNPJ","",nPtBins,ptBins);
  hBoverDlNPJ->SetLineColor(kBlack);
  Float_t apts[nPtBins],aptse[nPtBins],aBD13[nPtBins],aBD13e[nPtBins],aBDDa[nPtBins],aBDDae[nPtBins],aBDNPJ[nPtBins],aBDNPJe[nPtBins];
  for(int i=0;i<nPtBins;i++)
    {
      Float_t apt = (ptBins[i]+ptBins[i+1])/2.;
      apts[i] = apt;
      aptse[i] = -(ptBins[i]-ptBins[i+1])/2.;
      if(ptBins[i]<3.)
        {
          aBD13[i] = (3+0.2)/2.;
          aBD13e[i] = (3-0.2)/2.;
          hBoverDh->SetBinContent(i+1,3);
          hBoverDl->SetBinContent(i+1,0.2);
          //
          aBDDa[i] = -1;
          aBDDae[i] = 0;
          hBoverDhDa->SetBinContent(i+1,-1);
          hBoverDlDa->SetBinContent(i+1,-1);
          aBDNPJ[i] = -1;
          aBDNPJe[i] = 0;
          hBoverDhNPJ->SetBinContent(i+1,-1);
          hBoverDlNPJ->SetBinContent(i+1,-1);          
        }
      else if(ptBins[i]>=3. && ptBins[i]<8.)
        {
          aBD13[i] = (3+0.2)/2.;
          aBD13e[i] = (3-0.2)/2.;
          hBoverDh->SetBinContent(i+1,3);
          hBoverDl->SetBinContent(i+1,0.2);
          //
          aBDDa[i] = -1;
          aBDDae[i] = 0;
          hBoverDhDa->SetBinContent(i+1,-1);
          hBoverDlDa->SetBinContent(i+1,-1);
          int k;
          for(k=0;k<nPtBinsNPJ;k++)
            {
              if(apt>=ptBinsNPJ[k] && apt<=ptBinsNPJ[k+1]) break;
            }
          if(k>=nPtBinsNPJ)
            {
              cout<<"  Error: Over NPJ RAA range."<<endl;
              continue;
            }
          aBDNPJ[i] = (hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt)+hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt))/2.;
          aBDNPJe[i] = (hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt)-hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt))/2.;
          hBoverDhNPJ->SetBinContent(i+1,hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt));
          hBoverDlNPJ->SetBinContent(i+1,hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt));
        }
      else if(ptBins[i]>=8. && ptBins[i]<30.)
        {
          aBD13[i] = -1;
          aBD13e[i] = 0;
          int j;
          for(j=0;j<nPtBinsB;j++)
            {
              if(apt>=ptBinsB[j] && apt<=ptBinsB[j+1]) break;
            }
          if(j>=nPtBinsB)
            {
              cout<<"  Error: Over B RAA range."<<endl;
              continue;
            }
          hBoverDh->SetBinContent(i+1,hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt));
          hBoverDl->SetBinContent(i+1,hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt));
          //
          aBDDa[i] = (hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt)+hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt))/2.;
          aBDDae[i] = (hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt)-hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt))/2.;
          hBoverDhDa->SetBinContent(i+1,hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt));
          hBoverDlDa->SetBinContent(i+1,hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt));
          int k;
          for(k=0;k<nPtBinsNPJ;k++)
            {
              if(apt>=ptBinsNPJ[k] && apt<=ptBinsNPJ[k+1]) break;
            }
          if(k>=nPtBinsNPJ)
            {
              cout<<"  Error: Over NPJ RAA range."<<endl;
              continue;
            }
          aBDNPJ[i] = (hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt)+hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt))/2.;
          aBDNPJe[i] = (hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt)-hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt))/2.;
          hBoverDhNPJ->SetBinContent(i+1,hNPJRAAh->GetBinContent(k+1)/fDRAA->Eval(apt));
          hBoverDlNPJ->SetBinContent(i+1,hNPJRAAl->GetBinContent(k+1)/fDRAA->Eval(apt));
        }
      else if(ptBins[i]>=30. && ptBins[i]<60.)
        {
          aBD13[i] = -1;
          aBD13e[i] = 0;
          int j;
          for(j=0;j<nPtBinsB;j++)
            {
              if(apt>=ptBinsB[j] && apt<=ptBinsB[j+1]) break;
            }
          if(j>=nPtBinsB)
            {
              cout<<"  Error: Over B RAA range."<<endl;
              continue;
            }
          hBoverDh->SetBinContent(i+1,hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt));
          hBoverDl->SetBinContent(i+1,hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt));
          //
          aBDDa[i] = (hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt)+hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt))/2.;
          aBDDae[i] = (hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt)-hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt))/2.;
          hBoverDhDa->SetBinContent(i+1,hBRAAh->GetBinContent(j+1)/fDRAA->Eval(apt));
          hBoverDlDa->SetBinContent(i+1,hBRAAl->GetBinContent(j+1)/fDRAA->Eval(apt));
          aBDNPJ[i] = -1;
          aBDNPJe[i] = 0;
          hBoverDhNPJ->SetBinContent(i+1,-1);
          hBoverDlNPJ->SetBinContent(i+1,-1);
        }
      else if(ptBins[i]>=60.)
        {
          aBD13[i] = (2+0.2)/2.;
          aBD13e[i] = (2-0.2)/2.;
          hBoverDh->SetBinContent(i+1,2);
          hBoverDl->SetBinContent(i+1,0.2);
          aBDDa[i] = -1;
          aBDDae[i] = 0;
          hBoverDhDa->SetBinContent(i+1,-1);
          hBoverDlDa->SetBinContent(i+1,-1);
          aBDNPJ[i] = -1;
          aBDNPJe[i] = 0;
          hBoverDhNPJ->SetBinContent(i+1,-1);
          hBoverDlNPJ->SetBinContent(i+1,-1);
        }
    }
  TGraphErrors* grBD13 = new TGraphErrors(nPtBins,apts,aBD13,aptse,aBD13e);
  grBD13->SetName("grBD13");
  grBD13->SetFillStyle(1001);
  grBD13->SetFillColor(kRed-7);
  grBD13->SetLineColor(kRed-7);
  TGraphErrors* grBDDa = new TGraphErrors(nPtBins,apts,aBDDa,aptse,aBDDae);
  grBDDa->SetName("grBDDa");
  grBDDa->SetFillStyle(1001);
  grBDDa->SetFillColor(kAzure-9);
  grBDDa->SetLineColor(kAzure-9);
  TGraphErrors* grBDNPJ = new TGraphErrors(nPtBins,apts,aBDNPJ,aptse,aBDNPJe);
  grBDNPJ->SetName("grBDNPJ");
  grBDNPJ->SetFillStyle(3005);
  grBDNPJ->SetFillColor(kViolet+6);
  grBDNPJ->SetLineWidth(1);
  grBDNPJ->SetLineColor(kViolet+2);

  TH2F* hempty2 = new TH2F("hempty2",";p_{T} (GeV/c);R_{AA}(B) / R_{AA}(D)",10,0,102,10,0,3.5);
  sethempty(hempty2);

  hempty2->Draw();
  grBD13->Draw("5same");
  grBDDa->Draw("5same");
  grBDNPJ->Draw("5same");
  hBoverDh->Draw("same");
  hBoverDl->Draw("same");
  TLegend* legBoverD = new TLegend(0.50,0.70,0.94,0.88);
  setleg(legBoverD,0.045);
  legBoverD->AddEntry(grBD13,"0.2~2(3)","f");
  legBoverD->AddEntry(grBDDa,"B^{+} / D^{0}","f");
  legBoverD->AddEntry(grBDNPJ,"NP J/#psi / D^{0}","f");
  legBoverD->Draw();
  drawCMS("PbPb");

  cBoverD->SaveAs("plots/cBoverD.pdf");
  cBoverD->SaveAs("plots/cBoverD.png");

  TFile* outputfile = new TFile(output,"recreate");
  outputfile->cd();
  hBoverDh->Write();
  hBoverDl->Write();
  hBoverDhDa->Write();
  hBoverDlDa->Write();
  outputfile->Close();

  TCanvas* cFit = new TCanvas("cFit","",600,600);
  hempty->Draw();
  grBRAA->Draw("2same");
  grNPJRAA->Draw("2same");
  grDRAA->Draw("pesame");
  fDRAA->Draw("same");
  legD->Draw();
  drawCMS("PbPb");
  cFit->SaveAs("plots/cBoverD_Fit.pdf");
  TCanvas* cResult = new TCanvas("cResult","",600,600);
  hempty2->Draw();
  grBD13->Draw("5same");
  grBDDa->Draw("5same");
  grBDNPJ->Draw("5same");
  hBoverDh->Draw("same");
  hBoverDl->Draw("same");
  legBoverD->Draw();
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
