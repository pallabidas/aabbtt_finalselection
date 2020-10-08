#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "tr_Tree.h"
#include "ScaleFactor.h"
#include "ZmmSF.h"
#include "LumiReweightingStandAlone.h"
#include "btagSF_2017.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("emu_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    //sample weights
    float xs, weight, luminosity = 41400.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt15"){xs = 48.58*0.1475; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 48.58*0.1426; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt25"){xs = 48.58*0.1381; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 48.58*0.1358; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt35"){xs = 48.58*0.1338; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 48.58*0.1322; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt45"){xs = 48.58*0.1282; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 48.58*0.1232; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt55"){xs = 48.58*0.1193; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 48.58*0.1133; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt20"){xs = 3.782*0.1983; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt40"){xs = 3.782*0.1908; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt60"){xs = 3.782*0.1799; weight = luminosity*xs/N;}
    else if(sample == "embedded"){weight = 1.0;}
    else if(sample == "DY"){weight = 1.0;}
    else if(sample == "DY1"){weight = 1.0;}
    else if(sample == "DY2"){weight = 1.0;}
    else if(sample == "DY3"){weight = 1.0;}
    else if(sample == "DY4"){weight = 1.0;}
    else if(sample == "GGHTT"){xs = 48.58*0.0627; weight = luminosity*xs/N;}
    else if(sample == "GGHWW"){xs = 48.58*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "GGZHLLTT"){xs = 0.1227*0.0627*3*0.033658; weight = luminosity*xs/N;}
    else if(sample == "GGZHNNTT"){xs = 0.1227*0.0627*0.2000; weight = luminosity*xs/N;}
    else if(sample == "GGZHQQTT"){xs = 0.1227*0.0627*0.6991; weight = luminosity*xs/N;}
    else if(sample == "GGZHWW"){xs = 0.1227*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_antitop"){xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 26.23; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 44.07; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VBFHWW"){xs = 3.782*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 11.95; weight = luminosity*xs/N;}
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    //    else if(sample == "WW"){xs = 118.7; weight = luminosity*xs/N;}
    //    else if(sample == "WW1L1Nu2Q"){xs = 49.997; weight = luminosity*xs/N;}
    //    else if(sample == "WZ"){xs = 47.13; weight = luminosity*xs/N;}
    //    else if(sample == "WZ1L1Nu2Q"){xs = 10.71; weight = luminosity*xs/N;}
    //    else if(sample == "WZ1L3Nu"){xs = 3.05; weight = luminosity*xs/N;}
    else if(sample == "WZ2L2Q"){xs = 5.595; weight = luminosity*xs/N;}
    else if(sample == "WZ3L1Nu"){xs = 4.708; weight = luminosity*xs/N;}
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WminusHWW"){xs = 0.5328*0.2137; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHWW"){xs = 0.840*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHWW"){xs = 0.7612*0.2137; weight = luminosity*xs/N;}
    //    else if(sample == "ZZ"){xs = 16.523; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.22; weight = luminosity*xs/N;}
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
    else if(sample == "ttHnonbb"){xs = 0.5071*(1-0.5824); weight = luminosity*xs/N;}
    else {cout << "Missing sample cross section!!!" << endl; return 0;}
    
    
    tree->SetBranchAddress("pt_1", &pt_1);
    tree->SetBranchAddress("phi_1", &phi_1);
    tree->SetBranchAddress("eta_1", &eta_1);
    tree->SetBranchAddress("m_1", &m_1);
    tree->SetBranchAddress("e_1", &e_1);
    tree->SetBranchAddress("q_1", &q_1);
    tree->SetBranchAddress("iso_1", &iso_1);
    tree->SetBranchAddress("pt_2", &pt_2);
    tree->SetBranchAddress("phi_2", &phi_2);
    tree->SetBranchAddress("eta_2", &eta_2);
    tree->SetBranchAddress("m_2", &m_2);
    tree->SetBranchAddress("e_2", &e_2);
    tree->SetBranchAddress("q_2", &q_2);
    tree->SetBranchAddress("iso_2", &iso_2);
    tree->SetBranchAddress("passMu23E12DZ", &passMu23E12DZ);
    tree->SetBranchAddress("passMu8E23DZ", &passMu8E23DZ);
    tree->SetBranchAddress("matchMu23E12DZ_1", &matchMu23E12DZ_1);
    tree->SetBranchAddress("matchMu8E23DZ_1", &matchMu8E23DZ_1);
    tree->SetBranchAddress("filterMu23E12DZ_1", &filterMu23E12DZ_1);
    tree->SetBranchAddress("filterMu8E23DZ_1", &filterMu8E23DZ_1);
    tree->SetBranchAddress("matchMu23E12DZ_2", &matchMu23E12DZ_2);
    tree->SetBranchAddress("matchMu8E23DZ_2", &matchMu8E23DZ_2);
    tree->SetBranchAddress("filterMu23E12DZ_2", &filterMu23E12DZ_2);
    tree->SetBranchAddress("filterMu8E23DZ_2", &filterMu8E23DZ_2);
    tree->SetBranchAddress("bpt_deepcsv_1", &bpt_deepcsv_1);
    tree->SetBranchAddress("beta_deepcsv_1", &beta_deepcsv_1);
    tree->SetBranchAddress("bphi_deepcsv_1", &bphi_deepcsv_1);
    tree->SetBranchAddress("bm_deepcsv_1", &bm_deepcsv_1);
    tree->SetBranchAddress("bflavour_deepcsv_1", &bflavour_deepcsv_1);
    tree->SetBranchAddress("bscore_deepcsv_1", &bscore_deepcsv_1);
    tree->SetBranchAddress("bpt_deepcsv_2", &bpt_deepcsv_2);
    tree->SetBranchAddress("beta_deepcsv_2", &beta_deepcsv_2);
    tree->SetBranchAddress("bphi_deepcsv_2", &bphi_deepcsv_2);
    tree->SetBranchAddress("bm_deepcsv_2", &bm_deepcsv_2);
    tree->SetBranchAddress("bflavour_deepcsv_2", &bflavour_deepcsv_2);
    tree->SetBranchAddress("bscore_deepcsv_2", &bscore_deepcsv_2);
    tree->SetBranchAddress("numGenJets", &numGenJets);
    tree->SetBranchAddress("pt_top1", &pt_top1);
    tree->SetBranchAddress("pt_top2", &pt_top2);
    tree->SetBranchAddress("npu", &npu);
    tree->SetBranchAddress("genM", &genM);
    tree->SetBranchAddress("genpT", &genpT);
    tree->SetBranchAddress("genweight", &genweight);
    tree->SetBranchAddress("genpt_1", &genpt_1);
    tree->SetBranchAddress("genpt_2", &genpt_2);
    tree->SetBranchAddress("geneta_1", &geneta_1);
    tree->SetBranchAddress("geneta_2", &geneta_2);
    tree->SetBranchAddress("mjj", &mjj);
    tree->SetBranchAddress("njets", &njets);
    tree->SetBranchAddress("gen_match_1",&gen_match_1);
    tree->SetBranchAddress("gen_match_2",&gen_match_2);
    tree->SetBranchAddress("met", &met);
    tree->SetBranchAddress("metphi", &metphi);
    tree->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices);
    tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter);
    tree->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter);
    tree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter);
    tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
    tree->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter);
    tree->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter);
    tree->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter", &Flag_ecalBadCalibReducedMINIAODFilter);
    
    TH1F * hist_m_em_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_emb_OS = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_emb_SS = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_embb_OS = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_embb_SS = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_e_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_SS = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_OS_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_em_SS_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_em_OS_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_em_SS_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_em_OS_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_em_SS_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_em_OS_4 = new TH1F("", "", 10, 0., 200.);
    TH1F * hist_m_em_SS_4 = new TH1F("", "", 10, 0., 200.);
    
    TH1F * hist_m_em_0b_OS = new TH1F("", "", 36, 0., 180.);
    TH1F * hist_m_em_0b_SS = new TH1F("", "", 36, 0., 180.);
    TH1F * hist_e_pt_0b_OS = new TH1F("", "", 80, 0., 80.);
    TH1F * hist_e_pt_0b_SS = new TH1F("", "", 80, 0., 80.);
    TH1F * hist_m_pt_0b_OS = new TH1F("", "", 80, 0., 80.);
    TH1F * hist_m_pt_0b_SS = new TH1F("", "", 80, 0., 80.);
    
    TH1F * hist_m_em_1b_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_1b_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_1b_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_1b_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_1b_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_1b_SS = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_2b_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_2b_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_2b_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_2b_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_2b_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_2b_SS = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_vbf_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_vbf_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_vbf_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_vbf_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vbf_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vbf_SS = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_em_vv_OS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_em_vv_SS = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_e_pt_vv_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_e_pt_vv_SS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vv_OS = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vv_SS = new TH1F("", "", 30, 0., 150.);
    
    
    //declare workspace for scale factors
    TFile fwmc("htt_scalefactors_legacy_2017.root");
    RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
    fwmc.Close();
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    if (sample=="W1") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
    else if (sample=="W2") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5#MINIAODSIM", "pileup");
    else if (sample=="ST_t_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="DY4" or sample=="Z4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
    else if (sample=="W") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
    else if (sample=="DY" or sample=="Z") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="WW") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="WplusH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="WZ") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="DY4" or sample=="Z4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="ST_tW_top") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
    else if (sample=="WminusH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="ST_tW_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
    else if (sample=="W3") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="ZH125") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="TTToSemiLeptonic")  LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    else if (sample=="TTTo2L2Nu") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    
    //OS-to-SS qcd correction files
    TFile fclosure("closure_em_2017.root");
    TH2F *correction=(TH2F*) fclosure.Get("correction");
    TH2F *closureOS=(TH2F*) fclosure.Get("closureOS");
    
    TFile *fosss= new TFile("osss_em_2017.root","r");
    TF1 *osss_0jet=(TF1*) fosss->Get("OSSS_qcd_0jet_2017");
    TF1 *osss_1jet=(TF1*) fosss->Get("OSSS_qcd_1jet_2017");
    TF1 *osss_2jet=(TF1*) fosss->Get("OSSS_qcd_2jet_2017");
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        if(i % 10000 == 0) printf("event %d of %d...\n", i, n);
        tree->GetEntry(i);
        
        //MET filters
        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;
        
        //emu selection
        bool isMu8E23trigger = passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2 && pt_1>24 && pt_2>10;
        bool isMu23E12trigger = passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2 && pt_1>13 && pt_2>24;
        
        if (!isMu8E23trigger && !isMu23E12trigger) continue;
        if (!(fabs(eta_1)<2.4 && fabs(eta_2)<2.4)) continue;
        if (!(iso_1<0.15 && iso_2<0.15)) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        if (!(myele.DeltaR(mymu)>0.3)) continue;
        
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0) weight = 2.575;
            else if (numGenJets==1) weight = 0.7084;
            else if (numGenJets==2) weight = 0.9192;
            else if (numGenJets==3) weight = 1.648;
            else if (numGenJets==4) weight = 0.2192;
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0) weight = 23.67;
            else if (numGenJets==1) weight = 3.106;
            else if (numGenJets==2) weight = 3.014;
            else if (numGenJets==3) weight = 2.202;
            else if (numGenJets==4) weight = 2.150;
        }
        
        float sf_MC = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            if (gen_match_1==6 or gen_match_2==6) continue;
/*
            //reject MC with tau_e+tau_mu as duplicated in embedded sample
            if (sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="VBFbbtt20" && sample!="VBFbbtt40" && sample!="VBFbbtt60" && name!="HTT" && name!="ttHnonbb"){
                if (gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            }
*/
            //initialize workspace with lepton kinematics
            wmc->var("m_pt")->setVal(pt_2);
            wmc->var("m_eta")->setVal(eta_2);
            wmc->var("m_iso")->setVal(iso_2);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);
            
            //compute trigger scale factor
            float probData = wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float probMC = wmc->function("m_trg_8_ic_mc")->getVal()*wmc->function("e_trg_23_ic_mc")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_mc")->getVal()*wmc->function("e_trg_12_ic_mc")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_mc")->getVal()*wmc->function("m_trg_23_ic_mc")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float sf_trg = probData/probMC;
            sf_MC *= sf_trg;
            
            //muon and electron ID/iso/tracking scale factors
            float sf_mu = wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_ratio")->getVal();
            float sf_e = wmc->function("e_trk_ratio")->getVal()*wmc->function("e_idiso_ic_ratio")->getVal();
            sf_MC *= sf_mu * sf_e;
            
            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                wmc->var("z_gen_mass")->setVal(genM);
                wmc->var("z_gen_pt")->setVal(genpT);
                float zptweight = wmc->function("zptmass_weight_nom")->getVal();
                sf_MC *= zptweight;
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                float topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
            }
            
            //re-weigh pileup distribution
            float puweight = LumiWeights_12->weight(npu);
            sf_MC *= puweight;
            
            //generator weight
            sf_MC *= genweight;
            
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            if (gen_match_1==6 or gen_match_2==6) continue;
            
            //initialize workspace with lepton kinematics
            wmc->var("m_pt")->setVal(pt_2);
            wmc->var("m_eta")->setVal(eta_2);
            wmc->var("m_iso")->setVal(iso_2);
            wmc->var("e_pt")->setVal(pt_1);
            wmc->var("e_eta")->setVal(eta_1);
            wmc->var("e_iso")->setVal(iso_1);
            
            //compute trigger scale factor
            float probData = wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float probEmbed = wmc->function("m_trg_8_ic_embed")->getVal()*wmc->function("e_trg_23_ic_embed")->getVal()*int(isMu8E23trigger)+wmc->function("m_trg_23_ic_embed")->getVal()*wmc->function("e_trg_12_ic_embed")->getVal()*int(isMu23E12trigger)-wmc->function("e_trg_23_ic_embed")->getVal()*wmc->function("m_trg_23_ic_embed")->getVal()*int(isMu8E23trigger && isMu23E12trigger);
            float sf_trg = probData/probEmbed;
            sf_embed *= sf_trg;
            
            //muon and electron ID/iso/tracking scale factors
            float sf_mu = wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_embed_ratio")->getVal();
            float sf_e = wmc->function("e_trk_embed_ratio")->getVal()*wmc->function("e_idiso_ic_embed_ratio")->getVal();
            sf_embed *= sf_mu * sf_e;
            
            //efficiency of selecting Z->mumu data
            wmc->var("gt1_pt")->setVal(genpt_1);
            wmc->var("gt2_pt")->setVal(genpt_2);
            wmc->var("gt1_eta")->setVal(geneta_1);
            wmc->var("gt2_eta")->setVal(geneta_2);
            sf_embed *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_1);
            wmc->var("gt_eta")->setVal(geneta_1);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_2);
            wmc->var("gt_eta")->setVal(geneta_2);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            
            //generator weight
            sf_embed *= genweight;
            
        }
        
        float weight_corr = weight * sf_MC * sf_embed;
        
        //counting reconstructed btagged jets
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        if (bpt_deepcsv_1>20 && bscore_deepcsv_1>0.4941){
            bMpt_1 = bpt_deepcsv_1;
            bMflavor_1 = bflavour_deepcsv_1;
            nbtag20++;
        }
        if (bpt_deepcsv_2>20 && bscore_deepcsv_2>0.4941){
            bMpt_2 = bpt_deepcsv_2;
            bMflavor_2 = bflavour_deepcsv_2;
            nbtag20++;
        }
        
        //btag weights for MC only
        float weight_btag_0b = 1.0;
        float weight_btag_1b = 1.0;
        float weight_btag_2b = 1.0;
        float weight_btag_atleast1b = 1.0;
        if (sample!="data_obs" && sample!="embedded"){
            //0 bjet (apply to events with any no. of b jet)
            weight_btag_0b = bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
            if (nbtag20>2) weight_btag_0b = 0;
            //1 bjet (apply to 1b events only)
            weight_btag_1b = GetSF(1, bMpt_1, bMflavor_1, 0);
            //2 bjets (apply to 2b events only)
            weight_btag_2b = GetSF(1, bMpt_1, bMflavor_1, 0)*GetSF(1, bMpt_2, bMflavor_2, 0);
            //at least 1 bjet (apply to 1b and 2b events)
            if (nbtag20==1) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0);
            if (nbtag20==2) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0)+GetSF(1, bMpt_2, bMflavor_2, 0)-GetSF(1, bMpt_1, bMflavor_1, 0)*GetSF(1, bMpt_2, bMflavor_2, 0);
        }
        
        //defining variables for some categories
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        
        float mt_emet=TMass_F((myele).Pt(),mymet.Pt(),(myele).Px(),mymet.Px(),(myele).Py(),mymet.Py());
        float mt_mumet=TMass_F((mymu).Pt(),mymet.Pt(),(mymu).Px(),mymet.Px(),(mymu).Py(),mymet.Py());
        
        float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
        float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
        float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        //filling histograms
        float m_em = (myele + mymu).M();
        float m_emb = (myele + mymu + myb1).M();
        float m_embb = (myele + mymu + myb1 + myb2).M();
        
        //OS region
        if (q_1*q_2<0){
            //0bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_em_0b_OS->Fill(m_em,weight_corr*weight_btag_0b);
                hist_e_pt_0b_OS->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_m_pt_0b_OS->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_em>100){
                    hist_m_em_vv_OS->Fill(m_em,weight_corr*weight_btag_0b);
                    hist_e_pt_vv_OS->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_m_pt_vv_OS->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //0bjet MC
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_em_0b_OS->Fill(m_em,weight_corr*weight_btag_0b);
                hist_e_pt_0b_OS->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_m_pt_0b_OS->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_em>100){
                    hist_m_em_vv_OS->Fill(m_em,weight_corr*weight_btag_0b);
                    hist_e_pt_vv_OS->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_m_pt_vv_OS->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //1bjet
            if(nbtag20==1 && fabs(beta_deepcsv_1)<2.4){
                hist_m_em_1b_OS->Fill(m_em,weight_corr*weight_btag_1b);
                hist_e_pt_1b_OS->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_m_pt_1b_OS->Fill(pt_2,weight_corr*weight_btag_1b);
            }
            
            //2bjet
            if(nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4){
                hist_m_em_2b_OS->Fill(m_em,weight_corr*weight_btag_2b);
                hist_e_pt_2b_OS->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_m_pt_2b_OS->Fill(pt_2,weight_corr*weight_btag_2b);
            }
            
            //baseline selection
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4)) && pt_1>13 && pt_2>13){
                
                hist_m_em_OS->Fill(m_em,weight_corr*weight_btag_atleast1b);
                hist_m_emb_OS->Fill(m_emb,weight_corr*weight_btag_atleast1b);
                hist_e_pt_OS->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                hist_m_pt_OS->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                if (nbtag20==2) hist_m_embb_OS->Fill(m_embb,weight_corr*weight_btag_atleast1b);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_em_vbf_OS->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    hist_e_pt_vbf_OS->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                    hist_m_pt_vbf_OS->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                }
                
                //the 4 categories
                if (mt_emet<40 && mt_mumet<40 && dzeta>-30){
                    //category 1
                    if (m_emb<65){
                        hist_m_em_OS_1->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 2
                    if (m_emb>65 && m_emb<80){
                        hist_m_em_OS_2->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 3
                    if (m_emb>80 && m_emb<95){
                        hist_m_em_OS_3->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 4
                    if (m_emb>95){
                        hist_m_em_OS_4->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                }
            }
        }
        
        
        //SS region
        if (q_1*q_2>0){
            //SS weight
            float ssweight = 1.0;
            if (njets==0) ssweight = osss_0jet->Eval(myele.DeltaR(mymu));
            else if (njets==1) ssweight = osss_1jet->Eval(myele.DeltaR(mymu));
            else ssweight = osss_2jet->Eval(myele.DeltaR(mymu));
            
            float mupt = mymu.Pt();
            float ept = myele.Pt();
            if (mupt > 100) mupt = 99;
            if (ept > 100) ept = 99;
            ssweight *= correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept));
            ssweight *= closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt),closureOS->GetYaxis()->FindBin(ept));
            
            weight_corr *= ssweight;
            
            //0bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_em_0b_SS->Fill(m_em,weight_corr*weight_btag_0b);
                hist_e_pt_0b_SS->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_m_pt_0b_SS->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_em>100){
                    hist_m_em_vv_SS->Fill(m_em,weight_corr*weight_btag_0b);
                    hist_e_pt_vv_SS->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_m_pt_vv_SS->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //0bjet MC
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_em_0b_SS->Fill(m_em,weight_corr*weight_btag_0b);
                hist_e_pt_0b_SS->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_m_pt_0b_SS->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_em>100){
                    hist_m_em_vv_SS->Fill(m_em,weight_corr*weight_btag_0b);
                    hist_e_pt_vv_SS->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_m_pt_vv_SS->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            
            //1bjet
            if(nbtag20==1 && fabs(beta_deepcsv_1)<2.4){
                hist_m_em_1b_SS->Fill(m_em,weight_corr*weight_btag_1b);
                hist_e_pt_1b_SS->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_m_pt_1b_SS->Fill(pt_2,weight_corr*weight_btag_1b);
            }
            
            //2bjet
            if(nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4){
                hist_m_em_2b_SS->Fill(m_em,weight_corr*weight_btag_2b);
                hist_e_pt_2b_SS->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_m_pt_2b_SS->Fill(pt_2,weight_corr*weight_btag_2b);
            }
            //baseline selection
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4)) && pt_1>13 && pt_2>13){
                
                hist_m_em_SS->Fill(m_em,weight_corr*weight_btag_atleast1b);
                hist_m_emb_SS->Fill(m_emb,weight_corr*weight_btag_atleast1b);
                hist_e_pt_SS->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                hist_m_pt_SS->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                if (nbtag20==2) hist_m_embb_SS->Fill(m_embb,weight_corr*weight_btag_atleast1b);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_em_vbf_SS->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    hist_e_pt_vbf_SS->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                    hist_m_pt_vbf_SS->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                }
                
                //the 4 categories
                if (mt_emet<40 && mt_mumet<40 && dzeta>-30){
                    //category 1
                    if (m_emb<65){
                        hist_m_em_SS_1->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 2
                    if (m_emb>65 && m_emb<80){
                        hist_m_em_SS_2->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 3
                    if (m_emb>80 && m_emb<95){
                        hist_m_em_SS_3->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                    //category 4
                    if (m_emb>95){
                        hist_m_em_SS_4->Fill(m_em,weight_corr*weight_btag_atleast1b);
                    }
                }
            }
        }
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    TDirectory * td1 = fout->mkdir("m_em_1");
    TDirectory * td2 = fout->mkdir("m_em_2");
    TDirectory * td3 = fout->mkdir("m_em_3");
    TDirectory * td4 = fout->mkdir("m_em_4");
    TDirectory * td5 = fout->mkdir("m_em");
    TDirectory * td6 = fout->mkdir("m_emb");
    TDirectory * td7 = fout->mkdir("m_embb");
    TDirectory * td8 = fout->mkdir("pt_e");
    TDirectory * td9 = fout->mkdir("pt_m");
    
    TDirectory * td10 = fout->mkdir("m_em_0b");
    TDirectory * td11 = fout->mkdir("pt_e_0b");
    TDirectory * td12 = fout->mkdir("pt_m_0b");
    TDirectory * td13 = fout->mkdir("m_em_1b");
    TDirectory * td14 = fout->mkdir("pt_e_1b");
    TDirectory * td15 = fout->mkdir("pt_m_1b");
    TDirectory * td16 = fout->mkdir("m_em_2b");
    TDirectory * td17 = fout->mkdir("pt_e_2b");
    TDirectory * td18 = fout->mkdir("pt_m_2b");
    TDirectory * td19 = fout->mkdir("m_em_vbf");
    TDirectory * td20 = fout->mkdir("pt_e_vbf");
    TDirectory * td21 = fout->mkdir("pt_m_vbf");
    TDirectory * td22 = fout->mkdir("m_em_vv");
    TDirectory * td23 = fout->mkdir("pt_e_vv");
    TDirectory * td24 = fout->mkdir("pt_m_vv");
    
    TString SS="_SS";
    
    td1->cd();
    hist_m_em_OS_1->SetName(name.c_str());
    hist_m_em_OS_1->Write();
    hist_m_em_SS_1->SetName(name.c_str()+SS);
    hist_m_em_SS_1->Write();
    
    td2->cd();
    hist_m_em_OS_2->SetName(name.c_str());
    hist_m_em_OS_2->Write();
    hist_m_em_SS_2->SetName(name.c_str()+SS);
    hist_m_em_SS_2->Write();
    
    td3->cd();
    hist_m_em_OS_3->SetName(name.c_str());
    hist_m_em_OS_3->Write();
    hist_m_em_SS_3->SetName(name.c_str()+SS);
    hist_m_em_SS_3->Write();
    
    td4->cd();
    hist_m_em_OS_4->SetName(name.c_str());
    hist_m_em_OS_4->Write();
    hist_m_em_SS_4->SetName(name.c_str()+SS);
    hist_m_em_SS_4->Write();
    
    td5->cd();
    hist_m_em_OS->SetName(name.c_str());
    hist_m_em_OS->Write();
    hist_m_em_SS->SetName(name.c_str()+SS);
    hist_m_em_SS->Write();
    
    td6->cd();
    hist_m_emb_OS->SetName(name.c_str());
    hist_m_emb_OS->Write();
    hist_m_emb_SS->SetName(name.c_str()+SS);
    hist_m_emb_SS->Write();
    
    td7->cd();
    hist_m_embb_OS->SetName(name.c_str());
    hist_m_embb_OS->Write();
    hist_m_embb_SS->SetName(name.c_str()+SS);
    hist_m_embb_SS->Write();
    
    td8->cd();
    hist_e_pt_OS->SetName(name.c_str());
    hist_e_pt_OS->Write();
    hist_e_pt_SS->SetName(name.c_str()+SS);
    hist_e_pt_SS->Write();
    
    td9->cd();
    hist_m_pt_OS->SetName(name.c_str());
    hist_m_pt_OS->Write();
    hist_m_pt_SS->SetName(name.c_str()+SS);
    hist_m_pt_SS->Write();
    
    td10->cd();
    hist_m_em_0b_OS->SetName(name.c_str());
    hist_m_em_0b_OS->Write();
    hist_m_em_0b_SS->SetName(name.c_str()+SS);
    hist_m_em_0b_SS->Write();
    
    td11->cd();
    hist_e_pt_0b_OS->SetName(name.c_str());
    hist_e_pt_0b_OS->Write();
    hist_e_pt_0b_SS->SetName(name.c_str()+SS);
    hist_e_pt_0b_SS->Write();
    
    td12->cd();
    hist_m_pt_0b_OS->SetName(name.c_str());
    hist_m_pt_0b_OS->Write();
    hist_m_pt_0b_SS->SetName(name.c_str()+SS);
    hist_m_pt_0b_SS->Write();
    
    td13->cd();
    hist_m_em_1b_OS->SetName(name.c_str());
    hist_m_em_1b_OS->Write();
    hist_m_em_1b_SS->SetName(name.c_str()+SS);
    hist_m_em_1b_SS->Write();
    
    td14->cd();
    hist_e_pt_1b_OS->SetName(name.c_str());
    hist_e_pt_1b_OS->Write();
    hist_e_pt_1b_SS->SetName(name.c_str()+SS);
    hist_e_pt_1b_SS->Write();
    
    td15->cd();
    hist_m_pt_1b_OS->SetName(name.c_str());
    hist_m_pt_1b_OS->Write();
    hist_m_pt_1b_SS->SetName(name.c_str()+SS);
    hist_m_pt_1b_SS->Write();
    
    td16->cd();
    hist_m_em_2b_OS->SetName(name.c_str());
    hist_m_em_2b_OS->Write();
    hist_m_em_2b_SS->SetName(name.c_str()+SS);
    hist_m_em_2b_SS->Write();
    
    td17->cd();
    hist_e_pt_2b_OS->SetName(name.c_str());
    hist_e_pt_2b_OS->Write();
    hist_e_pt_2b_SS->SetName(name.c_str()+SS);
    hist_e_pt_2b_SS->Write();
    
    td18->cd();
    hist_m_pt_2b_OS->SetName(name.c_str());
    hist_m_pt_2b_OS->Write();
    hist_m_pt_2b_SS->SetName(name.c_str()+SS);
    hist_m_pt_2b_SS->Write();
    
    td19->cd();
    hist_m_em_vbf_OS->SetName(name.c_str());
    hist_m_em_vbf_OS->Write();
    hist_m_em_vbf_SS->SetName(name.c_str()+SS);
    hist_m_em_vbf_SS->Write();
    
    td20->cd();
    hist_e_pt_vbf_OS->SetName(name.c_str());
    hist_e_pt_vbf_OS->Write();
    hist_e_pt_vbf_SS->SetName(name.c_str()+SS);
    hist_e_pt_vbf_SS->Write();
    
    td21->cd();
    hist_m_pt_vbf_OS->SetName(name.c_str());
    hist_m_pt_vbf_OS->Write();
    hist_m_pt_vbf_SS->SetName(name.c_str()+SS);
    hist_m_pt_vbf_SS->Write();
    
    td22->cd();
    hist_m_em_vv_OS->SetName(name.c_str());
    hist_m_em_vv_OS->Write();
    hist_m_em_vv_SS->SetName(name.c_str()+SS);
    hist_m_em_vv_SS->Write();
    
    td23->cd();
    hist_e_pt_vv_OS->SetName(name.c_str());
    hist_e_pt_vv_OS->Write();
    hist_e_pt_vv_SS->SetName(name.c_str()+SS);
    hist_e_pt_vv_SS->Write();
    
    td24->cd();
    hist_m_pt_vv_OS->SetName(name.c_str());
    hist_m_pt_vv_OS->Write();
    hist_m_pt_vv_SS->SetName(name.c_str()+SS);
    hist_m_pt_vv_SS->Write();
    
    fout->Close();
    
    delete wmc;
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}


