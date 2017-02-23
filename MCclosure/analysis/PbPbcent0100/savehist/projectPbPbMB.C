#include "project.h"
void projectPbPbMB(TString col, Float_t centmin, Float_t centmax)
{
  TFile* inf = new TFile(inputdataPbPbMB);
  TTree* tData = (TTree*)inf->Get("ntDkpi");
  tData->AddFriend("ntHlt");
  tData->AddFriend("ntHi");
  tData->AddFriend("ntSkim");

  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  TCut cutPbPbMB = Form("%s&&%s&&hiBin>=(2*%f)&&hiBin<=(2*%f)",TRGPbPbMB.Data(),CUTPbPbMB.Data(),centmin,centmax);
  TCut cutpt = cutptMB;
  TCut weightfunctionreco = weightfunctionrecoPbPbMB;  

  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    {
      binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
    }
  for(int i=0; i<=nBinZ; i++)
    {
      binsZ[i] = firstBinZ+binWidthZ*i;
    }
  for(int i=0; i<=nBinM; i++)
    {
      binsM[i] = minMassBin + massBinWidth*i;
    }

  TH3D* hSideband = new TH3D("hSideband",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hData = new TH3D("hData",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hPtMD0Dca = new TH3D("hPtMD0Dca",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  
  hSideband->Sumw2();
  hData->Sumw2();
  hPtMD0Dca->Sumw2();
  
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hSideband",weightfunctionrecoPbPbMB*(cutpt&&cutPbPbMB&&cutSideband));
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hData",weightfunctionrecoPbPbMB*(cutpt&&cutPbPbMB&&cutSignal));
  tData->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0Dca",weightfunctionrecoPbPbMB*(cutpt&&cutPbPbMB));
  
  outf->Write();
}
