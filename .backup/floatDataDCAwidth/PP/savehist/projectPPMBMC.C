#include "project.h"
void projectPPMBMC(TString col)
{
  TFile* infMCP = new TFile(inputmcpPP);
  TFile* infMCNP = new TFile(inputmcnpPP);
  
  TTree* tMCP = (TTree*)infMCP->Get("ntDkpi");
  tMCP->AddFriend("ntHlt");
  tMCP->AddFriend("ntHi");
  tMCP->AddFriend("ntSkim");
  TTree* tMCNP = (TTree*)infMCNP->Get("ntDkpi");
  tMCNP->AddFriend("ntHlt");
  tMCNP->AddFriend("ntHi");
  tMCNP->AddFriend("ntSkim");
  
  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");  
  TCut cutPPMb = Form("(1)&&%s",CUTPPMB.Data());
  TCut cutpt = cutptMB;
  TCut weightfunctionreco = weightfunctionrecoPPMB;

  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin + massBinWidth*i;

  TH3D* hMCPSignal = new TH3D("hMCPSignal",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hMCNPSignal = new TH3D("hMCNPSignal",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hPtMD0DcaMCPSignal = new TH3D("hPtMD0DcaMCPSignal",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  TH3D* hPtMD0DcaMCPSwapped = new TH3D("hPtMD0DcaMCPSwapped",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  
  hMCPSignal->Sumw2();
  hMCNPSignal->Sumw2();
  hPtMD0DcaMCPSignal->Sumw2();
  hPtMD0DcaMCPSwapped->Sumw2();
  
  tMCP->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hMCPSignal",weightfunctionreco*(cutpt&&cutPPMb&&cutmc&&cutPrompt));
  tMCNP->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hMCNPSignal",weightfunctionreco*(cutpt&&cutPPMb&&cutmc&&cutNonPrompt));
  tMCP->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0DcaMCPSignal",cutpt&&cutPPMb&&cutmcSignal);
  tMCP->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0DcaMCPSwapped",cutpt&&cutPPMb&&cutmcSwapped);
  outf->Write();
}

