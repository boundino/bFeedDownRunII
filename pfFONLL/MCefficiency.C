using namespace std;
#include "uti.h"
#include "parameters.h"

void MCefficiency(TString coly, TString inputmc, TString outputfile, TString selmcgen, TString cut, TString weight, TString weightgen, Float_t centmin=0, Float_t centmax=100)
{

  Bool_t isPbPb = (coly=="PbPb")?true:false;
  selmcgen = isPbPb?Form("%s&&hiBin>=(2*%f)&&hiBin<=(2*%f)",selmcgen.Data(),centmin,centmax):Form("%s",selmcgen.Data());
  cut = isPbPb?Form("%s&&hiBin>=(2*%f)&&hiBin<=(2*%f)",cut.Data(),centmin,centmax):Form("%s",cut.Data());
  fillptbins(isPbPb);

  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHi");
  ntMC->AddFriend("ntSkim");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  ntGen->AddFriend("ntHi");
  ntGen->AddFriend("ntSkim");

  TH1D* hPtMC = new TH1D("hPtMC","",nPtBins,ptBins);
  TH1D* hPtGen = new TH1D("hPtGen","",nPtBins,ptBins);

  ntMC->Project("hPtMC","Dpt",TCut(weight)*(TCut(cut.Data())&&"(Dgen==23333)"));
  divideBinWidth(hPtMC);
  ntGen->Project("hPtGen","Gpt",TCut(weightgen)*(TCut(selmcgen.Data())));
  divideBinWidth(hPtGen);
  TH1D* hEff = (TH1D*)hPtMC->Clone("hEff");
  hEff->Divide(hPtGen);

  TString outputname = isPbPb?Form("%s_%s_cent_%.0f_%.0f.root",outputfile.Data(),coly.Data(),centmin,centmax):Form("%s_%s.root",outputfile.Data(),coly.Data());
  TFile* fout = new TFile(outputname,"recreate");
  fout->cd();
  hEff->Write();
  fout->Close();
}

int main(int argc, char *argv[])
{
  if(argc==10)
    {
      MCefficiency(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],atof(argv[8]),atof(argv[9]));
      return 0;
    }
  else if(argc==8)
    {
      MCefficiency(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}
