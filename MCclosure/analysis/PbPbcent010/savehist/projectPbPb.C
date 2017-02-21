#include "project.h"
void projectPbPb(TString col)
{
  TFile* inf = new TFile(inputdataPbPb);
  TTree* tData = (TTree*)inf->Get("ntDkpi");
  tData->AddFriend("ntHlt");
  tData->AddFriend("ntHi");
  tData->AddFriend("ntSkim");

  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  TCut cutPbPb = Form("%s&&%s&&hiBin>=(2*%f)&&hiBin<=(2*%f)",TRGPbPb.Data(),CUTPbPb.Data(),centmin,centmax);
  TCut cutpt = cutptHP;
  TCut weightfunctionreco = weightfunctionrecoPbPbHP;

  binsY[0]=0;
  for(int i=1;i<=nBinY;i++)
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

  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hSideband",weightfunctionrecoPbPbHP*(cutpt&&cutPbPb&&cutSideband));
  tData->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hData",weightfunctionrecoPbPbHP*(cutpt&&cutPbPb&&cutSignal));
  tData->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0Dca",weightfunctionrecoPbPbHP*(cutpt&&cutPbPb));

  outf->Write();
}
