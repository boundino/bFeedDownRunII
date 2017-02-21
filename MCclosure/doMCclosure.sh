#!/bin/bash
CENTMIN=0
CENTMAX=10

DO_TRUEFRACTIONS=$1
DO_TRUEFRACTIONS_PPMB=1
DO_TRUEFRACTIONS_PP=1
DO_TRUEFRACTIONS_PbPbMB=1
DO_TRUEFRACTIONS_PbPb=1

DO_COMPARE=$2
DO_COMPARE_PP=0
DO_COMPARE_PbPb=1

##

TCOLPPMB="PPMB"
TCOLPP="PP"
TCOLPbPbMB="PbPbMB"
TCOLPbPb="PbPb"

INPUTMCPPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCPPNP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCPbPbP="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCPbPbNP="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

WEIGHTPPMB="((pthatweight)*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10)))"
WEIGHTPP="((pthatweight)*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10)))"
#WEIGHTPbPbMB="((pthatweight)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Dgenpt*(0.0838585)+Dgenpt*Dgenpt*(-0.00991096)+Dgenpt*Dgenpt*Dgenpt*(0.000496019)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-8.50065e-06)))"
WEIGHTPbPbMB="(1)"
#WEIGHTPbPb="((pthatweight)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09)))"
WEIGHTPbPb="(1)"

CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTPbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"

OUTPUTFILES="rootfiles/ftrueFprompt"

##

cp ../uti.h .

##

NEWDIRS=("plots" "rootfiles")
for i in ${NEWDIRS[@]}
do
    if [ ! -d $i ];then
        mkdir $i
    fi
done

#
if [ $DO_TRUEFRACTIONS -eq 1 ]; then

    if [ $DO_TRUEFRACTIONS_PPMB -eq 1 ]; then
        sed '1iconst int nPtBins = 9; float ptbin[nPtBins+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.,20.};' trueFprompt.cc > trueFprompt_tmp.cc
        g++ trueFprompt_tmp.cc $(root-config --cflags --libs) -g -o trueFprompt_tmp.exe 
        ./trueFprompt_tmp.exe "$TCOLPPMB" "$INPUTMCPPP" "$INPUTMCPPNP" "$WEIGHTPPMB" "$CUTPPMB" "$OUTPUTFILES"
        rm trueFprompt_tmp.exe
        rm trueFprompt_tmp.cc
    fi
    
    if [ $DO_TRUEFRACTIONS_PP -eq 1 ]; then
        sed '1iconst int nPtBins = 5; float ptbin[nPtBins+1] = {20.,25.,30.,40.,60.,100.};' trueFprompt.cc > trueFprompt_tmp.cc
        g++ trueFprompt_tmp.cc $(root-config --cflags --libs) -g -o trueFprompt_tmp.exe 
        ./trueFprompt_tmp.exe "$TCOLPP" "$INPUTMCPPP" "$INPUTMCPPNP" "$WEIGHTPP" "$CUTPP" "$OUTPUTFILES"
        rm trueFprompt_tmp.exe
        rm trueFprompt_tmp.cc
    fi
    
    if [ $DO_TRUEFRACTIONS_PbPbMB -eq 1 ]; then
        sed '1iconst int nPtBins = 9; float ptbin[nPtBins+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.,20.};' trueFprompt.cc > trueFprompt_tmp.cc
        g++ trueFprompt_tmp.cc $(root-config --cflags --libs) -g -o trueFprompt_tmp.exe 
        ./trueFprompt_tmp.exe "$TCOLPbPbMB" "$INPUTMCPbPbP" "$INPUTMCPbPbNP" "$WEIGHTPbPbMB" "$CUTPbPbMB" "$OUTPUTFILES" "$CENTMIN" "$CENTMAX"
        rm trueFprompt_tmp.exe
        rm trueFprompt_tmp.cc
    fi
    
    if [ $DO_TRUEFRACTIONS_PbPb -eq 1 ]; then
        sed '1iconst int nPtBins = 5; float ptbin[nPtBins+1] = {20.,25.,30.,40.,60.,100.};' trueFprompt.cc > trueFprompt_tmp.cc
        g++ trueFprompt_tmp.cc $(root-config --cflags --libs) -g -o trueFprompt_tmp.exe 
        ./trueFprompt_tmp.exe "$TCOLPbPb" "$INPUTMCPbPbP" "$INPUTMCPbPbNP" "$WEIGHTPbPb" "$CUTPbPb" "$OUTPUTFILES" "$CENTMIN" "$CENTMAX"
        rm trueFprompt_tmp.exe
        rm trueFprompt_tmp.cc
    fi
    
fi

if [ $DO_COMPARE -eq 1 ]; then
    if [ $DO_COMPARE_PP -eq 1 ]; then
        root -b -q "compare.cc+("\"PP\"","\"$OUTPUTFILES\"")"
    fi
    if [ $DO_COMPARE_PbPb -eq 1 ]; then
        root -b -q "compare.cc+("\"PbPb\"","\"$OUTPUTFILES\"","$CENTMIN","$CENTMAX")"
    fi
fi

rm uti.h