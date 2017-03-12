using namespace std;
#include "bFeedDownFraction.h"
#include "savehist/project.h"

void bFeedDownFraction(TString col, Float_t centmin=0, Float_t centmax=100)
{
  Bool_t isPbPb = (col=="PbPb")?true:false;
  TString tcoly = isPbPb?Form("%s_cent_%.0f_%.0f_pt",col.Data(),centmin,centmax):Form("%s_pt",col.Data());

  cout<<endl<<endl;
  cout<<" -- Processing bFeedDownFraction: "<<col;
  if(isPbPb) cout<<Form(" - Centrality %.0f - %.0f",centmin,centmax)<<"%";
  cout<<endl;

  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TCanvas* c6 = new TCanvas("c6","",1200,600);
  c6->Divide(3,2);   
  TCanvas* c2 = new TCanvas("c2","",400,600);
  c2->Divide(1,2);
  TCanvas* c1 = new TCanvas("c1","",500,400);
  TCanvas* c15 = new TCanvas("c15","",810,1000);
  c15->Divide(3,5);
  TCanvas* c12 = new TCanvas("c12","",810,800);
  c12->Divide(3,4);
  TCanvas* c2fit = new TCanvas("c2fit","",400,600);
  c2fit->Divide(1,2);

  TFile* f = new TFile(Form("rootfiles/bFeedDown%s.hist.root",col.Data()));
  TFile* fMB = new TFile(Form("rootfiles/bFeedDown%sMB.hist.root",col.Data()));
  TFile* fMC = new TFile(Form("rootfiles/bFeedDown%sMC.hist.root",col.Data()));
  TFile* fMBMC = new TFile(Form("rootfiles/bFeedDown%sMBMC.hist.root",col.Data()));

  TH3D* hMCPSignalFile = (TH3D*)fMC->Get("hMCPSignal");
  TH3D* hMCNPSignalFile = (TH3D*)fMC->Get("hMCNPSignal");
  TH3D* hMCPSignalFileMB = (TH3D*)fMBMC->Get("hMCPSignal");
  TH3D* hMCNPSignalFileMB = (TH3D*)fMBMC->Get("hMCNPSignal");
  TH3D* hPtMD0DcaMCPSignalFile = (TH3D*)fMC->Get("hPtMD0DcaMCPSignal");
  TH3D* hPtMD0DcaMCPSwappedFile = (TH3D*)fMC->Get("hPtMD0DcaMCPSwapped");
  TH3D* hPtMD0DcaMCPSignalFileMB =(TH3D*)fMBMC->Get("hPtMD0DcaMCPSignal");
  TH3D* hPtMD0DcaMCPSwappedFileMB = (TH3D*)fMBMC->Get("hPtMD0DcaMCPSwapped");

  TH3D* hMCPSignal = (TH3D*)hMCPSignalFile->Clone("hMCPSignal");
  hMCPSignal->Sumw2();
  hMCPSignal->Add(hMCPSignalFileMB);
  TH3D* hMCNPSignal = (TH3D*)hMCNPSignalFile->Clone("hMCNPSignal");
  hMCNPSignal->Sumw2();
  hMCNPSignal->Add(hMCNPSignalFileMB);
  TH3D* hPtMD0DcaMCPSignal = (TH3D*)hPtMD0DcaMCPSignalFile->Clone("hPtMD0DcaMCPSignal");
  hPtMD0DcaMCPSignal->Sumw2();
  hPtMD0DcaMCPSignal->Add(hPtMD0DcaMCPSignalFileMB);
  TH3D* hPtMD0DcaMCPSwapped =(TH3D*)hPtMD0DcaMCPSwappedFile->Clone("hPtMD0DcaMCPSwapped");
  hPtMD0DcaMCPSwapped->Sumw2();
  hPtMD0DcaMCPSwapped->Add(hPtMD0DcaMCPSwappedFileMB);

  TLatex* texCms = new TLatex(0.15,0.95, "#scale[1.25]{CMS} Preliminary");
  settex(texCms,0.06,12);
  TLatex* texCol = new TLatex(0.96,0.95, Form("%s #sqrt{s_{NN}} = 5.02 TeV",col.Data()));
  settex(texCol,0.06,32);
  TString per = "%";
  TLatex* texCent = new TLatex(0.96,0.95, Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(texCent,0.06,32);

  float pts[nBinX];
  float ptseF[nBinX]; for(int i=0;i<nBinX;i++) ptseF[i]=0.4;

  float apromptFraction[nBinX][nwidth];
  float apromptFractionError[nBinX][nwidth];
  float apromptFractionErrorMCSmear[nBinX][nwidth];
  float apromptFractionErrorDataSmear[nBinX][nwidth];
  float apromptFractionErrorDataOnly[nBinX][nwidth];
  float atotalYield[nBinX][nwidth];
  float atotalYieldError[nBinX][nwidth];

  float aChi2ndf[nBinX][nwidth];

  float promptFraction[nBinX];
  float promptFractionError[nBinX];
  float promptFractionErrorMCSmear[nBinX];
  float promptFractionErrorDataSmear[nBinX];
  float promptFractionErrorDataOnly[nBinX];
  float totalYield[nBinX];
  float totalYieldError[nBinX];

  binsY[0]=0;
  for(int i=1;i<=nBinY;i++) binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  /*
  TH1D** ahD0DcaData = new TH1D*[nBinX];
  TH1D** ahD0DcaMCPSignal = new TH1D*[nBinX];
  TH1D** ahD0DcaMCNPSignal = new TH1D*[nBinX];
  */
  cout<<endl<<endl;
  cout<<" -- Loop pT bins "<<endl;
  for(int i=1; i<=nBinX; i++)
    {
      TH1D** ahD0DcaDataOverFit = new TH1D*[nwidth];
      
      TH3D* hPtFile = (TH3D*)f->Get("hData_0");
      TH3D* hPtFileMB = (TH3D*)fMB->Get("hData_0");
      TH3D* hPt = (TH3D*)hPtFile->Clone("hPt");
      hPt->Add(hPtFileMB);
      
      pts[i-1] = hPt->GetXaxis()->GetBinCenter(i);
      float ptLow = hPt->GetXaxis()->GetBinLowEdge(i);
      float ptHigh = hPt->GetXaxis()->GetBinUpEdge(i);
      cout<<endl<<"  - Processing: "<<ptLow<<" - "<<ptHigh<<" GeV/c"<<endl;
      
      TLatex* texPtY = new TLatex(0.32,0.82,Form("%.1f < p_{T} < %.1f GeV/c      |y| < 1.0",ptLow,ptHigh));
      settex(texPtY,0.06);
      TLatex* texPt = new TLatex(0.18,0.82,Form("%.1f < p_{T} < %.1f GeV/c",ptLow,ptHigh));
      settex(texPt,0.06);
      TLatex* texPtTitle = new TLatex(0.15,0.95,Form("%.1f < p_{T} < %.1f GeV/c",ptLow,ptHigh));
      settex(texPtTitle,0.06);
      TLatex* texY = new TLatex(0.18,0.74,Form("|y| < 1.0"));
      settex(texY,0.06);
      
      for(int k=0;k<nwidth;k++)
        {
          Float_t width = widthstart + k*widthstep;

          TH3D* hDataFile = (TH3D*)f->Get(Form("hData_%d",k));
          TH3D* hSidebandFile = (TH3D*)f->Get(Form("hSideband_%d",k));
          TH3D* hPtMD0DcaFile = (TH3D*)f->Get(Form("hPtMD0Dca_%d",k));
          TH3D* hDataFileMB = (TH3D*)fMB->Get(Form("hData_%d",k));
          TH3D* hSidebandFileMB = (TH3D*)fMB->Get(Form("hSideband_%d",k));
          TH3D* hPtMD0DcaFileMB = (TH3D*)fMB->Get(Form("hPtMD0Dca_%d",k));

          TH3D* hData = (TH3D*)hDataFile->Clone("hData");
          hData->Sumw2();
          hData->Add(hDataFileMB);
          TH3D* hSideband = (TH3D*)hSidebandFile->Clone("hSideband");
          hSideband->Sumw2();
          hSideband->Add(hSidebandFileMB);
          TH3D* hPtMD0Dca = (TH3D*)hPtMD0DcaFile->Clone("hPtMD0Dca");
          hPtMD0Dca->Sumw2();
          hPtMD0Dca->Add(hPtMD0DcaFileMB);
          
          cout<<"    Calculating sideband ratios ..."<<endl;
          c2->cd(1);
          
          hPtMD0Dca->GetZaxis()->SetRange(1,100);
          hPtMD0Dca->GetXaxis()->SetRange(i,i);
          hPtMD0DcaMCPSignal->GetXaxis()->SetRange(i,i);
          hPtMD0DcaMCPSwapped->GetXaxis()->SetRange(i,i);
          TH1D* hMData = (TH1D*)hPtMD0Dca->Project3D("y")->Clone(Form("hM_%1.1f_%1.1f", ptLow, ptHigh));
          TH1D* hMMCSignal = (TH1D*)hPtMD0DcaMCPSignal->Project3D("y");
          TH1D* hMMCSwapped = (TH1D*)hPtMD0DcaMCPSwapped->Project3D("y");

          //          
          setColorTitleLabel(hMData);
          TF1* fMass = fitMass(hMData, hMMCSignal, hMMCSwapped);
          
          texCms->Draw();
          texCol->Draw();
          texPt->Draw();
          texY->Draw();
          
          TF1* background = new TF1("fBackground","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
          background->SetParameter(0,fMass->GetParameter(3));
          background->SetParameter(1,fMass->GetParameter(4));
          background->SetParameter(2,fMass->GetParameter(5));
          background->SetParameter(3,fMass->GetParameter(6));
          
          float massD = 1.8649;
          float massSignal1 = massD-0.025;
          float massSignal2 = massD+0.025;
          float massSideBand1 = massD-0.1;
          float massSideBand2 = massD-0.075;
          float massSideBand3 = massD+0.075;
          float massSideBand4 = massD+0.1;
          
          float scaleSideBand = background->Integral(massSignal1, massSignal2)/(background->Integral(massSideBand1, massSideBand2)+background->Integral(massSideBand3, massSideBand4));
          
          TLatex* texScale = new TLatex(0.18,0.66,Form("side band scale: %1.3f", scaleSideBand));
          settex(texScale,0.06);
          texScale->Draw();
          
          TLine* lineSignal1 = new TLine(massSignal1, 0, massSignal1, background->Eval(massSignal1));
          lineSignal1->SetLineStyle(2);
          lineSignal1->SetLineWidth(2);
          lineSignal1->SetLineColor(12);
          TLine* lineSignal2 = new TLine(massSignal2, 0, massSignal2, background->Eval(massSignal2));
          lineSignal2->SetLineStyle(2);
          lineSignal2->SetLineWidth(2);
          lineSignal2->SetLineColor(12);
          TLine* lineSideBand1 = new TLine(massSideBand1, 0, massSideBand1, background->Eval(massSideBand1));
          lineSideBand1->SetLineStyle(2);
          lineSideBand1->SetLineWidth(2);
          lineSideBand1->SetLineColor(12);
          TLine* lineSideBand2 = new TLine(massSideBand2, 0, massSideBand2, background->Eval(massSideBand2));
          lineSideBand2->SetLineStyle(2);
          lineSideBand2->SetLineWidth(2);
          lineSideBand2->SetLineColor(12);
          TLine* lineSideBand3 = new TLine(massSideBand3, 0, massSideBand3, background->Eval(massSideBand3));
          lineSideBand3->SetLineStyle(2);
          lineSideBand3->SetLineWidth(2);
          lineSideBand3->SetLineColor(12);
          TLine* lineSideBand4 = new TLine(massSideBand4, 0, massSideBand4, background->Eval(massSideBand4));
          lineSideBand4->SetLineStyle(2);
          lineSideBand4->SetLineWidth(2);
          lineSideBand4->SetLineColor(12);
          
          lineSignal1->Draw();
          lineSignal2->Draw();
          lineSideBand1->Draw();
          lineSideBand2->Draw();
          lineSideBand3->Draw();
          lineSideBand4->Draw();
          
          c2->cd(2);
          gPad->SetLogy();
          
          hData->GetXaxis()->SetRange(i,i);
          hSideband->GetXaxis()->SetRange(i,i);
          hMCPSignal->GetXaxis()->SetRange(i,i);
          hMCNPSignal->GetXaxis()->SetRange(i,i);
          
          TH1D* hD0DcaData0 = (TH1D*)hData->Project3D("y")->Clone("hD0DcaData0");
          TH1D* hD0DcaSideband = (TH1D*)hSideband->Project3D("y")->Clone("hD0DcaSideband");
          TH1D* hD0DcaMCPSignal0 = (TH1D*)hMCPSignal->Project3D("y")->Clone("hD0DcaMCPSignal0");
          TH1D* hD0DcaMCNPSignal0 = (TH1D*)hMCNPSignal->Project3D("y")->Clone("hD0DcaMCNPSignal0");
          
          hD0DcaMCPSignal = hD0DcaMCPSignal0;
          hD0DcaMCNPSignal = hD0DcaMCNPSignal0;
          
          divideBinWidth(hD0DcaData0);
          divideBinWidth(hD0DcaSideband);
          setColorTitleLabel(hD0DcaData0, 1);
          hD0DcaData0->GetXaxis()->SetRangeUser(0,0.1);
          hD0DcaData0->GetYaxis()->SetTitle("counts per cm");
          
          TH1D* hD0DcaSideband0 = (TH1D*)hD0DcaSideband->Clone("hD0DcaSideband0");
          hD0DcaSideband->Scale(scaleSideBand);
          
          TH1D* hD0DcaDataSubSideBand = (TH1D*)hD0DcaData0->Clone("hD0DcaDataSubSideBand");
          hD0DcaDataSubSideBand->Add(hD0DcaSideband,-1);
          
          hD0DcaData0->SetMarkerSize(0.6);
          hD0DcaData0->Draw();
          hD0DcaSideband->Draw("hsame");
          hD0DcaSideband0->SetLineStyle(2);
          hD0DcaSideband0->Draw("hsame");

          TLegend* leg1 = new TLegend(0.44,0.6,0.90,0.76,NULL,"brNDC");
          leg1->SetBorderSize(0);
          leg1->SetTextSize(0.06);
          leg1->SetTextFont(42);
          leg1->SetFillStyle(0);
          leg1->AddEntry(hD0DcaData0,"D^{0} candidate","pl");
          leg1->AddEntry(hD0DcaSideband,"side band","l");
          leg1->AddEntry(hD0DcaSideband0,"side band unscaled","l");
          leg1->Draw("same");
          
          texCms->Draw();
          if(isPbPb) texCent->Draw();
          texPtY->Draw();
          
          c2->SaveAs(Form("plots/%s_%.0f_%.0f_sideBand_%d.pdf",tcoly.Data(),ptLow,ptHigh,k));
          
          cout<<"    Yield extraction for each DCA bin ..."<<endl;
          c15->cd(1);
          
          fitMass(hMData, hMMCSignal, hMMCSwapped);
          
          texPt->Draw();
          texY->Draw();
          texCms->Draw();
          texCol->Draw();
          
          TH1D* hD0DcaDataFit = new TH1D("hD0DcaDataFit", ";D^{0} DCA (cm);yield per cm", nBinY, binsY);
          for(int j=1; j<=13; j++)
            {
              c15->cd(j+1);
              hPtMD0Dca->GetZaxis()->SetRange(j,j);
              float D0DcaLow = hPtMD0Dca->GetZaxis()->GetBinLowEdge(j);
              float D0DcaHigh = hPtMD0Dca->GetZaxis()->GetBinUpEdge(j);
              TH1D* hMData_D0Dca = (TH1D*)hPtMD0Dca->Project3D("y")->Clone(Form("hM_pt_%1.1f_%1.1f_D0Dca_%1.4f_%1.4f", ptLow, ptHigh, D0DcaLow, D0DcaHigh));
              setColorTitleLabel(hMData_D0Dca);
              fMass = fitMass(hMData_D0Dca, hMMCSignal, hMMCSwapped);
              
              float yield = fMass->GetParameter(0)*fMass->GetParameter(7)/hMData_D0Dca->GetBinWidth(1);
              float yieldError = fMass->GetParError(0)*fMass->GetParameter(7)/hMData_D0Dca->GetBinWidth(1);
              
              hD0DcaDataFit->SetBinContent(j, yield);
              hD0DcaDataFit->SetBinError(j, yieldError);
              
              TLatex* texD0Dca = new TLatex(0.18,0.82,Form("D^{0} DCA: %1.4f - %1.4f",D0DcaLow,D0DcaHigh));
              settex(texD0Dca,0.06);
              texD0Dca->Draw();
              
              TLatex* texYield = new TLatex(0.18,0.74,Form("D^{0} yield: %1.0f #pm %1.0f",yield,yieldError));
              settex(texYield,0.06);
              texYield->Draw();
              if(j==1) texPtTitle->Draw();
              if(j==2 && isPbPb) texCent->Draw();
            } 
          
          c15->SaveAs(Form("plots/%s_%.0f_%.0f_invMassFit_%d.pdf",tcoly.Data(),ptLow,ptHigh,k));
          
          divideBinWidth(hD0DcaDataFit);
          
          cout<<"    Fitting DCA distributions ..."<<endl;
          c6->cd(1);
          gPad->SetLogy();
          
          normalize(hD0DcaMCPSignal);
          setColorTitleLabel(hD0DcaMCPSignal, 2);
          hD0DcaMCPSignal->GetXaxis()->SetRangeUser(0,0.1);
          hD0DcaMCPSignal->GetYaxis()->SetTitle("normalized counts per cm");
          //if(width==0) ahD0DcaMCPSignal[i-1] = (TH1D*)hD0DcaMCPSignal->Clone(Form("hD0DcaMCPSignal_%d",i-1));
          
          normalize(hD0DcaMCNPSignal);
          setColorTitleLabel(hD0DcaMCNPSignal, 4);
          hD0DcaMCNPSignal->GetXaxis()->SetRangeUser(0,0.1);
          hD0DcaMCNPSignal->GetYaxis()->SetTitle("normalized counts per cm");
          hD0DcaMCNPSignal->SetMaximum(hD0DcaMCPSignal->GetMaximum()*3.);
          //if(width==0) ahD0DcaMCNPSignal[i-1] = (TH1D*)hD0DcaMCNPSignal->Clone(Form("hD0DcaMCNPSignal_%d",i-1));
          
          hD0DcaMCNPSignal->Draw("");
          hD0DcaMCPSignal->Draw("same");
          
          TLegend* leg2 = new TLegend(0.49,0.72,0.90,0.88,NULL,"brNDC");
          leg2->SetBorderSize(0);
          leg2->SetTextSize(0.06);
          leg2->SetTextFont(42);
          leg2->SetFillStyle(0);
          leg2->AddEntry(hD0DcaMCPSignal,"MC Prompt D^{0}","pl");
          leg2->AddEntry(hD0DcaMCNPSignal,"MC Non-prompt D^{0}","pl");
          leg2->Draw("same");
          
          texPtTitle->Draw();
          
          c6->cd(2);
          gPad->SetLogy();
          
          TH1D* hD0DcaData = hD0DcaDataFit;
          if(pts[i-1]>20) hD0DcaData = hD0DcaDataSubSideBand;
          //if(pts[i-1]>8) hD0DcaData = hD0DcaDataSubSideBand;
          
          setColorTitleLabel(hD0DcaData, 1);
          //ahD0DcaData[i-1] = (TH1D*)hD0DcaData->Clone(Form("hD0DcaData_%d",i-1));
          
          double integralTotalYield = hD0DcaData->Integral(1,hD0DcaData->GetXaxis()->GetNbins(),"width");
          
          TF1* fMix = new TF1("fMix",&funMix, 0., 0.5, 2);
          fMix->SetParameters(integralTotalYield,0.9);
          fMix->SetParLimits(0,0,2*integralTotalYield);
          fMix->SetParLimits(1,0,1);
          
          fMix->SetLineColor(2);
          fMix->SetFillColor(2);
          fMix->SetFillStyle(3001);
          
          float fitRangeL = 0;
          float fitRangeH = 0.08;
          
          hD0DcaData->GetXaxis()->SetRangeUser(0,0.1);
          hD0DcaData->Draw();
          int fitStatus = 1;
          TFitResultPtr fitResult;
          double fitPrecision = 1.e-6;
          while(fitStatus)
            {
              TFitter::SetPrecision(fitPrecision);
              fMix->SetParameters(integralTotalYield,0.9);
              fMix->SetParError(0,0.1*integralTotalYield);
              fMix->SetParError(1,0.1);
              fitResult = hD0DcaData->Fit("fMix","E SNQ0", "", fitRangeL, fitRangeH);
              fitStatus = fitResult->Status();
              //cout<<"fit precision: "<<TFitter::GetPrecision()<<"   status: "<<fitStatus<<endl;
              if(fitStatus)
                fitPrecision *= 10;
            }
          // Main fitting
          fMix->SetParameters(integralTotalYield,0.9);
          fMix->SetParError(0,0.1*integralTotalYield);
          fMix->SetParError(1,0.1);
          fitResult = hD0DcaData->Fit("fMix","E S0Q", "", fitRangeL, fitRangeH);
          hD0DcaData->GetFunction("fMix")->Draw("flsame");
          fitStatus = fitResult->Status();
          //cout<<"fit precision: "<<TFitter::GetPrecision()<<"   status: "<<fitStatus<<endl;
          
          TF1* fNP = new TF1("fNP",&funNonPrompt, 0., 0.5, 2);
          fNP->SetParameters(fMix->GetParameter(0),fMix->GetParameter(1));
          fNP->SetRange(fitRangeL,fitRangeH);
          fNP->SetLineColor(4);
          fNP->SetFillStyle(3001);
          fNP->SetFillColor(4);
          fNP->Draw("same");  
          
          hD0DcaData->Draw("same");
          
          apromptFraction[i-1][k] = fMix->GetParameter(1);
          apromptFractionErrorDataOnly[i-1][k] = fMix->GetParError(1);
          atotalYield[i-1][k] = fMix->GetParameter(0);
          atotalYieldError[i-1][k] = fMix->GetParError(0);
          aChi2ndf[i-1][k] = fMix->GetChisquare()/fMix->GetNDF();

          texCms->Draw();
          texCol->Draw();
          texPtY->Draw();
          
          TLatex* texRatio = new TLatex(0.45,0.73,Form("Prompt frac. = %.1f #pm %.1f %%",100*fMix->GetParameter(1),100*fMix->GetParError(1)));
          settex(texRatio,0.06);
          texRatio->Draw();
          
          TLegend* leg4 = new TLegend(0.56,0.46,0.90,0.7);
          leg4->SetBorderSize(0);
          leg4->SetTextSize(0.06);
          leg4->SetTextFont(42);
          leg4->SetFillStyle(0);
          leg4->AddEntry(hD0DcaData,"Data","pl");
          leg4->AddEntry(fMix,"Prompt D^{0}","f");
          leg4->AddEntry(fNP,"Non-Prompt D^{0}","f");
          leg4->Draw("same");
          
          c2fit->cd(1);
          gPad->SetLogy();
          hD0DcaData->Draw();
          hD0DcaData->GetFunction("fMix")->Draw("flsame");
          fNP->Draw("same");
          hD0DcaData->Draw("same");
          texCms->Draw();
          texCol->Draw();
          texPtY->Draw();
          texRatio->Draw();          
          leg4->Draw("same");

          c6->cd(4);
          fitMass(hMData, hMMCSignal, hMMCSwapped);
          
          texCms->Draw();
          texCol->Draw();
          texPt->Draw();
          texY->Draw();
          texScale->Draw();
          
          lineSignal1->Draw();
          lineSignal2->Draw();
          lineSideBand1->Draw();
          lineSideBand2->Draw();
          lineSideBand3->Draw();
          lineSideBand4->Draw();
          
          //
          cout<<"    Smearing Monte-Carlo DCA templates ..."<<endl;
          c6->cd(3);
          gPad->SetLogy();
          
          hD0DcaMCPSignal = (TH1D*)hD0DcaMCPSignal0->Clone("hMCPSignal");
          hD0DcaMCNPSignal = (TH1D*)hD0DcaMCNPSignal0->Clone("hMCNPSignal");
          
          TH1D* hPromptRatio = new TH1D("hPromptRatio", "hPromptRatio", 100, 0, 1);
          setColorTitleLabel(hPromptRatio, 1);
          
          int nSmear = 1000;
          
          for(int j=0; j<nSmear; j++)
            {
              RandomSmear(hD0DcaMCPSignal0, hD0DcaMCPSignal);
              RandomSmear(hD0DcaMCNPSignal0, hD0DcaMCNPSignal);
              hD0DcaData->Fit("fMix","E QN0");
              hPromptRatio->Fill(fMix->GetParameter(1));
            }
          
          hPromptRatio->GetXaxis()->SetTitle("Prompt fraction");
          hPromptRatio->GetYaxis()->SetTitle("counts");
          hPromptRatio->SetMarkerStyle(20);
          hPromptRatio->SetStats(0);
          hPromptRatio->Draw("e");
          hPromptRatio->Fit("gaus","q");
          
          TLatex* texMCSmear = new TLatex(0.25,0.80,"Smear Monte-Carlo");
          settex(texMCSmear,0.06);
          texMCSmear->Draw();
          TLatex* texGaussMean = new TLatex(0.25,0.70,Form("#mu: %.3f",hPromptRatio->GetFunction("gaus")->GetParameter(1)));
          settex(texGaussMean,0.06);
          texGaussMean->Draw();      
          TLatex* texGaussSigma = new TLatex(0.25,0.60,Form("#sigma: %.3f",hPromptRatio->GetFunction("gaus")->GetParameter(2)));
          settex(texGaussSigma,0.06);
          texGaussSigma->Draw();
          
          apromptFractionErrorMCSmear[i-1][k] = hPromptRatio->GetFunction("gaus")->GetParameter(2);
          
          //restore original unsmeared histograms before saving plots
          delete hD0DcaMCPSignal;
          delete hD0DcaMCNPSignal;
          hD0DcaMCPSignal = hD0DcaMCPSignal0;
          hD0DcaMCNPSignal = hD0DcaMCNPSignal0;
          hD0DcaData->Fit("fMix","E QN0");
          
          if(isPbPb) texCent->Draw();

          c6->cd(5);
          
          ahD0DcaDataOverFit[k] = (TH1D*)hD0DcaData->Clone(Form("hD0DcaDataOverFit_%d",k));
          ahD0DcaDataOverFit[k]->Divide(fMix);
          ahD0DcaDataOverFit[k]->GetYaxis()->SetTitle("data / fit");
          ahD0DcaDataOverFit[k]->GetYaxis()->SetRangeUser(0,5);
          ahD0DcaDataOverFit[k]->GetXaxis()->SetRangeUser(0,0.1);
          setColorTitleLabel(ahD0DcaDataOverFit[k], 1);
          ahD0DcaDataOverFit[k]->Draw("e");
          
          TF1* fLine1 = new TF1("fLine1", "1", 0,1);
          fLine1->Draw("same");
          ahD0DcaDataOverFit[k]->Draw("esame");

          c2fit->cd(2);
          ahD0DcaDataOverFit[k]->Draw("e");
          fLine1->Draw("same");
          ahD0DcaDataOverFit[k]->Draw("esame");
          c2fit->SaveAs(Form("plots/%s_%.0f_%.0f_fitc2_%d.pdf",tcoly.Data(),ptLow,ptHigh,k));
          
          cout<<"    Smearing Data DCA distributions ..."<<endl;
          c6->cd(6);
          gPad->SetLogy();
          
          TH1D* hD0DcaDataSmear = (TH1D*)hD0DcaData->Clone("hD0DcaDataSmear");
          TH1D* hPromptRatioDataSmear = new TH1D("hPromptRatioDataSmear", "", 100, 0, 1);
          setColorTitleLabel(hPromptRatioDataSmear, 1);

          int nSmearData = 1000;
          
          for(int j=0; j<nSmearData; j++)
            {          
              RandomSmear(hD0DcaData, hD0DcaDataSmear);
              hD0DcaDataSmear->Fit("fMix","E QN0");
              hPromptRatioDataSmear->Fill(fMix->GetParameter(1));
            }
          
          hPromptRatioDataSmear->GetXaxis()->SetTitle("Prompt fraction");
          hPromptRatioDataSmear->GetYaxis()->SetTitle("counts");
          hPromptRatioDataSmear->SetMarkerStyle(20);
          hPromptRatioDataSmear->SetStats(0);
          hPromptRatioDataSmear->Draw("e");
          hPromptRatioDataSmear->Fit("gaus","q");
          
          apromptFractionErrorDataSmear[i-1][k] = hPromptRatioDataSmear->GetFunction("gaus")->GetParameter(2);
          
          TLatex* texDataSmear = new TLatex(0.25,0.80,"Smear Data");
          settex(texDataSmear,0.06);
          texDataSmear->Draw();
          TLatex* texGaussMeanData = new TLatex(0.25,0.70,Form("#mu: %.3f",hPromptRatioDataSmear->GetFunction("gaus")->GetParameter(1)));
          settex(texGaussMeanData,0.06);
          texGaussMeanData->Draw();      
          TLatex* texGaussSigmaData = new TLatex(0.25,0.60,Form("#sigma: %.3f",hPromptRatioDataSmear->GetFunction("gaus")->GetParameter(2)));
          settex(texGaussSigmaData,0.06);
          texGaussSigmaData->Draw();
          
          c6->SaveAs(Form("plots/%s_%.0f_%.0f_fit_%d.pdf",tcoly.Data(),ptLow,ptHigh,k));
          
          apromptFractionError[i-1][k] = sqrt(pow(apromptFractionErrorDataSmear[i-1][k],2)+pow(apromptFractionErrorMCSmear[i-1][k],2));

          delete hD0DcaMCPSignal;
          delete hD0DcaMCNPSignal;
          delete hD0DcaDataSmear;
          delete hPromptRatio;
          delete hPromptRatioDataSmear;
          delete hD0DcaDataFit;
          
          //
          /*
          delete hD0DcaDataSubSideBand;
          delete hD0DcaSideband0;
          delete hD0DcaMCNPSignal0;
          delete hD0DcaMCPSignal0;
          delete hD0DcaSideband;
          delete hD0DcaData0;

          delete hMMCSwapped;
          delete hMMCSignal;
          delete hMData;
          delete hPtMD0Dca;
          delete hSideband;
          delete hData;
          delete hPtMD0DcaFileMB;
          delete hSidebandFileMB;
          delete hDataFileMB;
          delete hPtMD0DcaFile;
          delete hSidebandFile;
          delete hDataFile;
          */
        }
      TH1D* hChi2ndf = new TH1D("hChi2ndf",";#alpha;#chi^{2} / ndf",nwidth,widthstart,widthstart+nwidth*widthstep);
      hChi2ndf->SetLineColor(kBlack);
      int imin = 0;
      float xmin = aChi2ndf[i-1][0];
      for(int k=0;k<nwidth;k++)
        {
          Float_t width = widthstart + k*widthstep;
          c12->cd(k+1);
          ahD0DcaDataOverFit[k]->Draw("e");
          TF1* fLine1 = new TF1("fLine1", "1", 0,1);
          fLine1->SetLineColor(kBlue);
          fLine1->Draw("same");
          ahD0DcaDataOverFit[k]->Draw("esame");
          TLatex* texalpha = new TLatex(0.18,0.82,Form("Fill %.2f DCA",1-width));
          settex(texalpha,0.06);
          texalpha->Draw();
          if(k==1) texPtTitle->Draw();
          if(k==2 && isPbPb) texCent->Draw();

          hChi2ndf->SetBinContent(k+1,aChi2ndf[i-1][k]);
          if(aChi2ndf[i-1][k]<xmin)
            {
              imin = k;
              xmin = aChi2ndf[i-1][k];
            }
        }
      c12->cd(nwidth+1);
      hChi2ndf->Draw();
      c12->cd(imin+1);
      TF1* fLine2 = new TF1("fLine2", "1", 0,1);
      fLine2->SetLineColor(kRed);
      fLine2->Draw("same");
      ahD0DcaDataOverFit[imin]->Draw("esame");
      
      c12->SaveAs(Form("plotsChi2/%s_%.0f_%.0f_Chi2.pdf",tcoly.Data(),ptLow,ptHigh));

      promptFraction[i-1] = apromptFraction[i-1][imin];
      promptFractionError[i-1] = apromptFractionError[i-1][imin];
      promptFractionErrorMCSmear[i-1] = apromptFractionErrorMCSmear[i-1][imin];
      promptFractionErrorDataSmear[i-1] = apromptFractionErrorDataSmear[i-1][imin];
      promptFractionErrorDataOnly[i-1] = apromptFractionErrorDataOnly[i-1][imin];
      totalYield[i-1] = atotalYield[i-1][imin];
      totalYieldError[i-1] = atotalYieldError[i-1][imin];

    }

  cout<<endl<<endl<<"  -- Plotting final prompt fractions ..."<<endl;
  c1->cd();

  TH2F* hempty = new TH2F("hempty",";D^{0} p_{T} (GeV/c);Prompt fraction",10,0,100,10,0,1);
  sethempty(hempty);
  hempty->Draw();

  TGraphErrors* grFraction2 = new TGraphErrors(nBinX, pts, promptFraction, ptseF, promptFractionError);
  grFraction2->SetName("grPromptFraction2");
  grFraction2->SetLineWidth(0);
  grFraction2->SetLineColor(16);
  grFraction2->SetFillStyle(1001);
  grFraction2->SetFillColor(16);
  grFraction2->Draw("5same");
  TGraphErrors* grFraction = new TGraphErrors(nBinX, pts, promptFraction, 0, promptFractionErrorDataOnly);
  grFraction->SetName("grPromptFraction");
  grFraction->SetMarkerStyle(20);
  grFraction->SetMarkerSize(0.6);  
  grFraction->SetMarkerColor(kBlack);
  grFraction->Draw("psame");
  TLatex* texcent = new TLatex(0.35,0.54,Form("Cent. %.0f-%.0f%s",centmin,centmax,per.Data()));
  settex(texcent,0.045);
  if(isPbPb) texcent->Draw();
  TLegend* leg = new TLegend(0.33, 0.37, 0.75, 0.50);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(grFraction, "Stats from DCA fitting", "lp");
  leg->AddEntry(grFraction2, "Stats from data and MC smearing", "f");
  leg->Draw();
 
  TLatex* texCmsc1 = new TLatex(0.14,0.94, "#scale[1.25]{CMS} Preliminary");
  settex(texCmsc1,0.05,12);
  TLatex* texColc1 = new TLatex(0.96,0.94, Form("%s #sqrt{s_{NN}} = 5.02 TeV",col.Data()));
  settex(texColc1,0.05,32);
  texCmsc1->Draw();
  texColc1->Draw();
  c1->SaveAs(Form("plotsResult/%s_PromptFraction.pdf",tcoly.Data()));

  TFile* fOut = new TFile("rootfiles/bFeedDownResult.root", "recreate");
  fOut->cd();
  grFraction->Write();
  grFraction2->Write();
  /*
  for(int i=0;i<nBinX;i++) ahD0DcaData[i]->Write();
  for(int i=0;i<nBinX;i++) ahD0DcaMCPSignal[i]->Write();
  for(int i=0;i<nBinX;i++) ahD0DcaMCNPSignal[i]->Write();
  */
  fOut->Close();

  cout<<endl<<" -- Final result"<<endl;
  cout<<"    ";
  for(int i=0;i<nBinX;i++) cout<<promptFraction[i]<<", ";
  cout<<endl;
  cout<<endl;

}
