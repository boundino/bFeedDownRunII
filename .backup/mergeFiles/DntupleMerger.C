using namespace std;
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "iostream"
#include "iomanip"
#include "fList.h"

void addtochain(TChain* root)
{
  for(int i=0;i<nFiles;i++)
    {
      root->Add(inFileNames[i].Data());
      //root->Add(inFileNames[i].c_str());
    }	    
}

int DntupleMerger()
{
  TChain* ntDkpi = new TChain("ntDkpi");
  TChain* ntGen = new TChain("ntGen");
  TChain* ntHlt = new TChain("ntHlt");
  TChain* ntHi = new TChain("ntHi");
  TChain* ntSkim = new TChain("ntSkim");

  addtochain(ntDkpi);
  addtochain(ntGen);
  addtochain(ntHlt);
  addtochain(ntHi);
  addtochain(ntSkim);

  cout<<" -- Check evt no. for three trees"<<endl;
  cout<<"    "<<ntDkpi->GetEntries()<<", "<<ntGen->GetEntries()<<", "<<ntHlt->GetEntries()<<", "<<ntHi->GetEntries()<<", "<<ntSkim->GetEntries()<<endl;
  if(ntDkpi->GetEntries()!=ntHlt->GetEntries())
    {
      cout<<"    Error: Event numbers are different in three trees."<<endl;
      return 0;
    }
  
  TString ofname = "/data/wangj/MC2015/Dntuple/PbPb/Official/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_promptNnonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root";
  TFile* outf = TFile::Open(ofname,"recreate");
  TTree* ntDkpi_new = ntDkpi->CloneTree(0);
  TTree* ntGen_new = ntGen->CloneTree(0);
  TTree* ntHlt_new = ntHlt->CloneTree(0);
  TTree* ntHi_new = ntHi->CloneTree(0);
  TTree* ntSkim_new = ntSkim->CloneTree(0);

  Long64_t nentries = ntDkpi->GetEntries();
  cout<<" -- Event reading"<<endl;
  //for(Long64_t i=0;i<5;i++)
  for(Long64_t i=0;i<nentries;i++)
    {
      if(i%100000==0) cout<<setiosflags(ios::left)<<"    "<<setw(8)<<i<<" / "<<nentries<<endl;

      ntDkpi->GetEntry(i);
      ntGen->GetEntry(i);
      ntHlt->GetEntry(i);
      ntHi->GetEntry(i);
      ntSkim->GetEntry(i);

      ntDkpi_new->Fill();
      ntHlt_new->Fill(); 
      ntHi_new->Fill(); 
      ntSkim_new->Fill(); 
      ntGen_new->Fill();
    }

  outf->Write();
  cout<<" -- Writing new trees done"<<endl;
  outf->Close();

  return 1;  
}
