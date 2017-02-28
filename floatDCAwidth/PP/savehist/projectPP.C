using namespace std;
#include "project.h"

void projectPP(TString col)
{
  TFile* infData = new TFile(inputdataPP);
  TTree* tData = (TTree*)infData->Get("ntDkpi");
  tData->AddFriend("ntHlt");
  tData->AddFriend("ntHi");
  tData->AddFriend("ntSkim");

  TCut cutpp = Form("%s&&%s",TRGPP.Data(),CUTPP.Data());
  TCut cutpt = cutptHP;

  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin + massBinWidth*i;
  
  TH3D** ahSideband = new TH3D*[nwidth];
  TH3D** ahData = new TH3D*[nwidth];
  TH3D** ahPtMD0Dca = new TH3D*[nwidth];

  for(int i=0;i<nwidth;i++)
    {
      Float_t width = widthstart+i*widthstep;
      
      ahSideband[i] = new TH3D(Form("hSideband_%d",i),";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
      ahData[i] = new TH3D(Form("hData_%d",i),";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
      ahPtMD0Dca[i] = new TH3D(Form("hPtMD0Dca_%d",i),";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
      
      ahSideband[i]->Sumw2();
      ahData[i]->Sumw2();
      ahPtMD0Dca[i]->Sumw2();
      
      tData->Draw(Form("DsvpvDistance/DsvpvDisErr:(DsvpvDistance*sin(Dalpha))*(1-%f):Dpt>>hSideband_%d",width,i),cutpt&&cutpp&&cutSideband);
      tData->Draw(Form("DsvpvDistance/DsvpvDisErr:(DsvpvDistance*sin(Dalpha))*(1-%f):Dpt>>hData_%d",width,i),cutpt&&cutpp&&cutSignal);
      tData->Draw(Form("(DsvpvDistance*sin(Dalpha))*(1-%f):Dmass:Dpt>>hPtMD0Dca_%d",width,i),cutpt&&cutpp);
    }

  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  outf->cd();
  for(int i=0;i<nwidth;i++)
    {
      ahSideband[i]->Write();
      ahData[i]->Write();
      ahPtMD0Dca[i]->Write();
    }
  outf->Close();

}


