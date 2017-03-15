#include "project.h"

void projectPP(TString col)
{
  TFile* infData = new TFile(inputdataPP);
  TTree* tData = (TTree*)infData->Get("ntDkpi");
  tData->AddFriend("ntHlt");
  tData->AddFriend("ntHi");
  tData->AddFriend("ntSkim");

  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  TCut cutpp = Form("%s&&%s",TRGPP.Data(),CUTPP.Data());
  TCut cutpt = cutptHP;

  binsY[0]=0;
  for(int i=1;i<=nBinY;i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin+massBinWidth*i;
  
  TH3D* hSideband = new TH3D("hSideband",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hData = new TH3D("hData",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hPtMD0Dca = new TH3D("hPtMD0Dca",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  
  hSideband->Sumw2();
  hData->Sumw2();
  hPtMD0Dca->Sumw2();
  
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hSideband",cutpt&&cutpp&&cutSideband);
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hData",cutpt&&cutpp&&cutSignal);
  tData->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0Dca",cutpt&&cutpp);
  
  outf->Write();
}


