#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

//#include "/Users/cecilecaillol/ROOT/root-v5-34-00-patches/tmva/test/TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "myHelper.h"
#include "TLorentzVector.h"


using namespace TMVA;
int njets_JetAbsoluteFlavMapDown,njets_JetAbsoluteMPFBiasDown,njets_JetAbsoluteScaleDown,njets_JetAbsoluteStatDown,njets_JetEnDown,njets_JetFlavorQCDDown,njets_JetFragmentationDown,njets_JetPileUpDataMCDown,njets_JetPileUpPtBBDown,njets_JetPileUpPtEC1Down,njets_JetPileUpPtEC2Down,njets_JetPileUpPtHFDown,njets_JetPileUpPtRefDown,njets_JetRelativeBalDown,njets_JetRelativeFSRDown,njets_JetRelativeJEREC1Down,njets_JetRelativeJEREC2Down,njets_JetRelativeJERHFDown,njets_JetRelativePtBBDown,njets_JetRelativePtEC1Down,njets_JetRelativePtEC2Down,njets_JetRelativePtHFDown,njets_JetRelativeStatECDown,njets_JetRelativeStatFSRDown,njets_JetRelativeStatHFDown,njets_JetSinglePionECALDown,njets_JetSinglePionHCALDown,njets_JetTimePtEtaDown;
int njets_JetAbsoluteFlavMapUp,njets_JetAbsoluteMPFBiasUp,njets_JetAbsoluteScaleUp,njets_JetAbsoluteStatUp,njets_JetEnUp,njets_JetFlavorQCDUp,njets_JetFragmentationUp,njets_JetPileUpDataMCUp,njets_JetPileUpPtBBUp,njets_JetPileUpPtEC1Up,njets_JetPileUpPtEC2Up,njets_JetPileUpPtHFUp,njets_JetPileUpPtRefUp,njets_JetRelativeBalUp,njets_JetRelativeFSRUp,njets_JetRelativeJEREC1Up,njets_JetRelativeJEREC2Up,njets_JetRelativeJERHFUp,njets_JetRelativePtBBUp,njets_JetRelativePtEC1Up,njets_JetRelativePtEC2Up,njets_JetRelativePtHFUp,njets_JetRelativeStatECUp,njets_JetRelativeStatFSRUp,njets_JetRelativeStatHFUp,njets_JetSinglePionECALUp,njets_JetSinglePionHCALUp,njets_JetTimePtEtaUp;
float mjj_JetAbsoluteFlavMapDown,mjj_JetAbsoluteMPFBiasDown,mjj_JetAbsoluteScaleDown,mjj_JetAbsoluteStatDown,mjj_JetEnDown,mjj_JetFlavorQCDDown,mjj_JetFragmentationDown,mjj_JetPileUpDataMCDown,mjj_JetPileUpPtBBDown,mjj_JetPileUpPtEC1Down,mjj_JetPileUpPtEC2Down,mjj_JetPileUpPtHFDown,mjj_JetPileUpPtRefDown,mjj_JetRelativeBalDown,mjj_JetRelativeFSRDown,mjj_JetRelativeJEREC1Down,mjj_JetRelativeJEREC2Down,mjj_JetRelativeJERHFDown,mjj_JetRelativePtBBDown,mjj_JetRelativePtEC1Down,mjj_JetRelativePtEC2Down,mjj_JetRelativePtHFDown,mjj_JetRelativeStatECDown,mjj_JetRelativeStatFSRDown,mjj_JetRelativeStatHFDown,mjj_JetSinglePionECALDown,mjj_JetSinglePionHCALDown,mjj_JetTimePtEtaDown;
float mjj_JetAbsoluteFlavMapUp,mjj_JetAbsoluteMPFBiasUp,mjj_JetAbsoluteScaleUp,mjj_JetAbsoluteStatUp,mjj_JetEnUp,mjj_JetFlavorQCDUp,mjj_JetFragmentationUp,mjj_JetPileUpDataMCUp,mjj_JetPileUpPtBBUp,mjj_JetPileUpPtEC1Up,mjj_JetPileUpPtEC2Up,mjj_JetPileUpPtHFUp,mjj_JetPileUpPtRefUp,mjj_JetRelativeBalUp,mjj_JetRelativeFSRUp,mjj_JetRelativeJEREC1Up,mjj_JetRelativeJEREC2Up,mjj_JetRelativeJERHFUp,mjj_JetRelativePtBBUp,mjj_JetRelativePtEC1Up,mjj_JetRelativePtEC2Up,mjj_JetRelativePtHFUp,mjj_JetRelativeStatECUp,mjj_JetRelativeStatFSRUp,mjj_JetRelativeStatHFUp,mjj_JetSinglePionECALUp,mjj_JetSinglePionHCALUp,mjj_JetTimePtEtaUp;

float met_JetAbsoluteFlavMapDown,met_JetAbsoluteMPFBiasDown,met_JetAbsoluteScaleDown,met_JetAbsoluteStatDown,met_JetEnDown,met_JetFlavorQCDDown,met_JetFragmentationDown,met_JetPileUpDataMCDown,met_JetPileUpPtBBDown,met_JetPileUpPtEC1Down,met_JetPileUpPtEC2Down,met_JetPileUpPtHFDown,met_JetPileUpPtRefDown,met_JetRelativeBalDown,met_JetRelativeFSRDown,met_JetRelativeJEREC1Down,met_JetRelativeJEREC2Down,met_JetRelativeJERHFDown,met_JetRelativePtBBDown,met_JetRelativePtEC1Down,met_JetRelativePtEC2Down,met_JetRelativePtHFDown,met_JetRelativeStatECDown,met_JetRelativeStatFSRDown,met_JetRelativeStatHFDown,met_JetSinglePionECALDown,met_JetSinglePionHCALDown,met_JetTimePtEtaDown;
float met_JetAbsoluteFlavMapUp,met_JetAbsoluteMPFBiasUp,met_JetAbsoluteScaleUp,met_JetAbsoluteStatUp,met_JetEnUp,met_JetFlavorQCDUp,met_JetFragmentationUp,met_JetPileUpDataMCUp,met_JetPileUpPtBBUp,met_JetPileUpPtEC1Up,met_JetPileUpPtEC2Up,met_JetPileUpPtHFUp,met_JetPileUpPtRefUp,met_JetRelativeBalUp,met_JetRelativeFSRUp,met_JetRelativeJEREC1Up,met_JetRelativeJEREC2Up,met_JetRelativeJERHFUp,met_JetRelativePtBBUp,met_JetRelativePtEC1Up,met_JetRelativePtEC2Up,met_JetRelativePtHFUp,met_JetRelativeStatECUp,met_JetRelativeStatFSRUp,met_JetRelativeStatHFUp,met_JetSinglePionECALUp,met_JetSinglePionHCALUp,met_JetTimePtEtaUp;
float metphi_JetAbsoluteFlavMapDown,metphi_JetAbsoluteMPFBiasDown,metphi_JetAbsoluteScaleDown,metphi_JetAbsoluteStatDown,metphi_JetEnDown,metphi_JetFlavorQCDDown,metphi_JetFragmentationDown,metphi_JetPileUpDataMCDown,metphi_JetPileUpPtBBDown,metphi_JetPileUpPtEC1Down,metphi_JetPileUpPtEC2Down,metphi_JetPileUpPtHFDown,metphi_JetPileUpPtRefDown,metphi_JetRelativeBalDown,metphi_JetRelativeFSRDown,metphi_JetRelativeJEREC1Down,metphi_JetRelativeJEREC2Down,metphi_JetRelativeJERHFDown,metphi_JetRelativePtBBDown,metphi_JetRelativePtEC1Down,metphi_JetRelativePtEC2Down,metphi_JetRelativePtHFDown,metphi_JetRelativeStatECDown,metphi_JetRelativeStatFSRDown,metphi_JetRelativeStatHFDown,metphi_JetSinglePionECALDown,metphi_JetSinglePionHCALDown,metphi_JetTimePtEtaDown;
float metphi_JetAbsoluteFlavMapUp,metphi_JetAbsoluteMPFBiasUp,metphi_JetAbsoluteScaleUp,metphi_JetAbsoluteStatUp,metphi_JetEnUp,metphi_JetFlavorQCDUp,metphi_JetFragmentationUp,metphi_JetPileUpDataMCUp,metphi_JetPileUpPtBBUp,metphi_JetPileUpPtEC1Up,metphi_JetPileUpPtEC2Up,metphi_JetPileUpPtHFUp,metphi_JetPileUpPtRefUp,metphi_JetRelativeBalUp,metphi_JetRelativeFSRUp,metphi_JetRelativeJEREC1Up,metphi_JetRelativeJEREC2Up,metphi_JetRelativeJERHFUp,metphi_JetRelativePtBBUp,metphi_JetRelativePtEC1Up,metphi_JetRelativePtEC2Up,metphi_JetRelativePtHFUp,metphi_JetRelativeStatECUp,metphi_JetRelativeStatFSRUp,metphi_JetRelativeStatHFUp,metphi_JetSinglePionECALUp,metphi_JetSinglePionHCALUp,metphi_JetTimePtEtaUp;

  float pt_1_EScaleUp, pt_1_EScaleDown, pt_1_EResRhoUp, pt_1_EResRhoDown, pt_1_EResPhiDown;
  float met_ChargedUESUp, met_ChargedUESDown, met_HFUESUp, met_HFUESDown, met_ECALUESUp, met_ECALUESDown, met_HCALUESUp, met_HCALUESDown;
  float metphi_ChargedUESUp, metphi_ChargedUESDown, metphi_HFUESUp, metphi_HFUESDown, metphi_ECALUESUp, metphi_ECALUESDown, metphi_HCALUESUp, metphi_HCALUESDown;
float mjj,jdeta,pt_1,pt_2,eta_1, eta_2, deltaphi_12,mt_1,mt_2,deltaphi_taumet,deltaphi_emet,met,vbfeta,vbfmass, phi_1, phi_2, metphi,dphi_12, dphi_emet, dphi_taumet, m_coll, ptrat, deltaeta_12, m_1, m_2, mvis, l2_decayMode;
  float met_px, met_py, met_JESUp, metphi_JESUp, met_JESDown, metphi_JESDown, met_UESUp, metphi_UESUp, met_UESDown, metphi_UESDown,jdeta_JESUp, jdeta_JESDown;
  int njets, njets_JESUp, njets_JESDown;
float mjj_JESDown, mjj_JESUp;
  int gen_match_1,gen_match_2;
//float KNNforETau(TMVA::Reader *reader, float pt_1_ = 20, float pt_2_ = 20, float deltaphi_12_ = 20, float mt_1_ = 20, float mt_2_ = 20, float deltaphi_taumet_ = 20, float deltaphi_emet_ = 20, float met_, float njets_, float vbfeta_, float vbfmass_) {
float KNNforETau(TMVA::Reader *reader, float pt_1_ = 20, float pt_2_ = 20, float mt_1_ = 20, float mt_2_ = 20, float dphi_12_=20, float dphi_taumet_=20,float met_=20, float njets_=20, float vbfmass_=20, float vbfeta_=20, float eta_1_=20, float eta_2_=20, float m_coll_=20, float mvis_=20){
    gROOT->ProcessLine(".O0"); // turn off optimization in CINT
    pt_1=pt_1_;
    pt_2=pt_2_;
    mt_1=mt_1_;
    mt_2=mt_2_;
    met=met_;
    dphi_12=fabs(dphi_12_);
    dphi_taumet=fabs(dphi_taumet_);
    njets=1.0*njets_;
    if (njets<2){
       vbfmass=-0.1;
       vbfeta=-0.1;
    }
    else {
       vbfmass=vbfmass_/2600;
       vbfeta=vbfeta_/10;
    }
    ptrat=pt_1_/pt_2_;
    deltaeta_12=fabs(eta_1_-eta_2_);
    m_coll=m_coll_;
    mvis=mvis_;
    return reader->EvaluateMVA("BDT method");
}

