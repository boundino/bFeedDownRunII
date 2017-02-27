#!/bin/bash

CENTMIN=0
CENTMAX=0
#0:PP, 1:PbPb0100, 2:PbPb010
COL=$1
if [ $COL -eq 1 ]; then
    CENTMAX=100
fi
if [ $COL -eq 2 ]; then
    CENTMAX=10
fi

#
DO_FONLL=$2
DO_MCEFFICIENCY=$3
DO_PLOTPNNP=$3
DO_BOVERD=$4
DO_BFEEDDOWNFONLL=$4
#
DO_PLOTFRACTIONS=0
DO_PLOTFRACTIONS=$4

##

INPUTMCP_PP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCNP_PP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCP_PbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCNP_PbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

SELGEN="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUT_PP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUT_PPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUT_PbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUT_PbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"

CUTP="&&DgenBAncestorpt<=0"
CUTNP="&&DgenBAncestorpt>0"
CUTGP="&&GBAncestorpt<=0"
CUTGNP="&&GBAncestorpt>0"
WEIGHT_PP="((pthatweight)*(pthat>(1.2*maxDgenpt))*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10)))"
WEIGHTGEN_PP="((pthatweight)*(pthat>(1.2*maxDgenpt))*(0.0116437+Gpt*(0.0602697)+Gpt*Gpt*(-0.00226879)+Gpt*Gpt*Gpt*(3.91035e-05)+Gpt*Gpt*Gpt*Gpt*(-3.0699e-07)+Gpt*Gpt*Gpt*Gpt*Gpt*(8.73234e-10)))"
#WEIGHT_PbPb="(pthatweight*(pthat>(1.2*maxDgenpt))*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09)))"
WEIGHT_PbPb="(pthatweight*(pthat>(1.2*maxDgenpt))*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*((Dpt<20.)*(-0.00600791+Dgenpt*(0.0838585)+Dgenpt*Dgenpt*(-0.00991096)+Dgenpt*Dgenpt*Dgenpt*(0.000496019)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-8.50065e-06))+(Dpt>20.)))"
#WEIGHTGEN_PbPb="(pthatweight*(pthat>(1.2*maxDgenpt))*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09)))"
WEIGHTGEN_PbPb="(pthatweight*(pthat>(1.2*maxDgenpt))*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*((Gpt<20.)*(-0.00600791+Gpt*(0.0838585)+Gpt*Gpt*(-0.00991096)+Gpt*Gpt*Gpt*(0.000496019)+Gpt*Gpt*Gpt*Gpt*(-8.50065e-06))+(Gpt>20.)))"

#
if [ $COL -eq 0 ]; then
    COLY="PP"
    INPUTMCP=$INPUTMCP_PP
    INPUTMCNP=$INPUTMCNP_PP
    CUT="(((Dpt<20)&&$CUT_PPMB)||((Dpt>20)&&$CUT_PP))"
    WEIGHT=$WEIGHT_PP
    WEIGHTGEN=$WEIGHTGEN_PP
else
    COLY="PbPb"
    INPUTMCP=$INPUTMCP_PbPb
    INPUTMCNP=$INPUTMCNP_PbPb
    CUT="(((Dpt<20)&&$CUT_PbPbMB)||((Dpt>20)&&$CUT_PbPb))"
    WEIGHT=$WEIGHT_PbPb
    WEIGHTGEN=$WEIGHTGEN_PbPb
fi
#
FOLDERS=("plots" "outfiles" "outfilesResult")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]; then
        mkdir $i
    fi
done
#

INPUTFONLLP="fonlls/FONLL_pp_promptDzero_5TeV_y1.dat"
INPUTFONLLNP="fonlls/FONLL_pp_nonpromptDzero_5TeV_y1.dat"
OUTPUTFONLLP="outfiles/FONLL_pp_promptDzero_5TeV_y1.root"
OUTPUTFONLLNP="outfiles/FONLL_pp_nonpromptDzero_5TeV_y1.root"

OUTPUTMCEFFP="outfiles/MCefficiencyP"
OUTPUTMCEFFNP="outfiles/MCefficiencyNP"

OUTPUTFRACTION="outfilesResult/bFeedDownFONLL"
#OUTPUTFRACTIONcompare="../bFeedDown/outfilesResult/bFeedDownResult"
OUTPUTBRAA="outfiles/BRAAoverDRAA.root"
##
cp ../uti.h .

if [ $DO_FONLL -eq 1 ]; then 
g++ fonllDsigmadpt.C $(root-config --cflags --libs) -g -o fonllDsigmadpt.exe 
./fonllDsigmadpt.exe "$COLY" "$INPUTFONLLP" "$OUTPUTFONLLP" "$CENTMIN" "$CENTMAX"
./fonllDsigmadpt.exe "$COLY" "$INPUTFONLLNP" "$OUTPUTFONLLNP" "$CENTMIN" "$CENTMAX"
rm fonllDsigmadpt.exe
fi

if [ $DO_MCEFFICIENCY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$COLY" "$INPUTMCP" "$OUTPUTMCEFFP" "$SELGEN$CUTGP" "$CUT$CUTP" "$WEIGHT" "$WEIGHTGEN" "$CENTMIN" "$CENTMAX"
./MCefficiency.exe "$COLY" "$INPUTMCNP" "$OUTPUTMCEFFNP" "$SELGEN$CUTGNP" "$CUT$CUTNP" "$WEIGHT" "$WEIGHTGEN" "$CENTMIN" "$CENTMAX"
rm MCefficiency.exe
fi
if [ $DO_PLOTPNNP -eq 1 ]; then      
g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$COLY" "$OUTPUTMCEFFP" "$OUTPUTMCEFFNP" "$CENTMIN" "$CENTMAX"
rm plotPnNP.exe
fi

if [ $DO_BOVERD -eq 1 ]; then
g++ fitBoverD.C $(root-config --cflags --libs) -g -o fitBoverD.exe 
./fitBoverD.exe "$OUTPUTBRAA"
rm fitBoverD.exe
fi

if [ $DO_BFEEDDOWNFONLL -eq 1 ]; then      
g++ bFeedDownFONLL.C $(root-config --cflags --libs) -g -o bFeedDownFONLL.exe 
./bFeedDownFONLL.exe "$COLY" "$OUTPUTFONLLP" "$OUTPUTFONLLNP" "$OUTPUTMCEFFP" "$OUTPUTMCEFFNP" "$OUTPUTBRAA" "$OUTPUTFRACTION" "$CENTMIN" "$CENTMAX"
rm bFeedDownFONLL.exe
fi

if [ $DO_PLOTFRACTIONS -eq 1 ]; then      
g++ plotFractions.C $(root-config --cflags --libs) -g -o plotFractions.exe 
./plotFractions.exe "$COLY" "$OUTPUTFRACTION" "$CENTMIN" "$CENTMAX"
rm plotFractions.exe
fi

rm uti.h