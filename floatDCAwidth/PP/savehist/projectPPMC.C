using namespace std;
#include "project.h"

void projectPPMC(TString col)
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

  TCut cutpp = Form("(1)&&%s",CUTPP.Data());
  TCut cutpt = cutptHP;
  TCut weightfunctionreco = weightfunctionrecoPPHP; 

  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin + massBinWidth*i;

  TH3D** ahMCPSignal = new TH3D*[nwidth];
  TH3D** ahMCNPSignal = new TH3D*[nwidth];
  TH3D** ahPtMD0DcaMCPSignal = new TH3D*[nwidth];
  TH3D** ahPtMD0DcaMCPSwapped = new TH3D*[nwidth];

  for(int i=0;i<nwidth;i++)
    {
      Float_t width = widthstart+i*widthstep;

      ahMCPSignal[i] = new TH3D(Form("hMCPSignal_%d",i),";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
      ahMCNPSignal[i] = new TH3D(Form("hMCNPSignal_%d",i),";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
      ahPtMD0DcaMCPSignal[i] = new TH3D(Form("hPtMD0DcaMCPSignal_%d",i),";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
      ahPtMD0DcaMCPSwapped[i] = new TH3D(Form("hPtMD0DcaMCPSwapped_%d",i),";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
      
      ahMCPSignal[i]->Sumw2();
      ahMCNPSignal[i]->Sumw2();
      ahPtMD0DcaMCPSignal[i]->Sumw2();
      ahPtMD0DcaMCPSwapped[i]->Sumw2();
      
      tMCP->Draw(Form("DsvpvDistance/DsvpvDisErr:(DsvpvDistance*sin(Dalpha))*(1-%f):Dpt>>hMCPSignal_%d",width,i),weightfunctionreco*(cutpt&&cutpp&&cutmc&&cutPrompt));
      tMCNP->Draw(Form("DsvpvDistance/DsvpvDisErr:(DsvpvDistance*sin(Dalpha))*(1-%f):Dpt>>hMCNPSignal_%d",width,i),weightfunctionreco*(cutpt&&cutpp&&cutmc&&cutNonPrompt));
      tMCP->Draw(Form("(DsvpvDistance*sin(Dalpha))*(1-%f):Dmass:Dpt>>hPtMD0DcaMCPSignal_%d",width,i),cutpt&&cutpp&&cutmcSignal);
      tMCP->Draw(Form("(DsvpvDistance*sin(Dalpha))*(1-%f):Dmass:Dpt>>hPtMD0DcaMCPSwapped_%d",width,i),cutpt&&cutpp&&cutmcSwapped);
    }

  TFile* outf = new TFile(Form("%s%s.hist.root",outputProject.Data(),col.Data()),"recreate");
  outf->cd();
  for(int i=0;i<nwidth;i++)
    {
      ahMCPSignal[i]->Write();
      ahMCNPSignal[i]->Write();
      ahPtMD0DcaMCPSignal[i]->Write();
      ahPtMD0DcaMCPSwapped[i]->Write();
    }
  outf->Close();

}

