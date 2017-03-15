#include "project.h"

void projectPPMB(TString col)
{
  TFile* infData = new TFile(inputdataPPMB);
  TTree* tData = (TTree*)infData->Get("ntDkpi");
  tData->AddFriend("ntHlt");
  tData->AddFriend("ntHi");
  tData->AddFriend("ntSkim");
  
  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  TCut cutPPMb = Form("%s&&%s",TRGPPMB.Data(),CUTPPMB.Data());

  TCut cutpt = cutptMB;
  TCut cutSignal = "abs(Dmass-1.8649)<0.025";
  TCut cutSideband = "abs(Dmass-1.8649)>0.075&&abs(Dmass-1.8649)<0.1";

  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin + massBinWidth*i;

  TH3D* hSideband = new TH3D("hSideband",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hData = new TH3D("hData",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hPtMD0Dca = new TH3D("hPtMD0Dca",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  
  hSideband->Sumw2();
  hData->Sumw2();
  hPtMD0Dca->Sumw2();
  
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hSideband",cutpt&&cutPPMb&&cutSideband);
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hData",cutpt&&cutPPMb&&cutSignal);
  tData->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0Dca",cutpt&&cutPPMb);
  
  outf->Write();
}
