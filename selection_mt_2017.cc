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
#include "GetTauFR.h"

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("mutau_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    //sample weights
    float xs, weight, luminosity = 41400.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt15"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt25"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt35"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt45"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt55"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt20"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt40"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt60"){xs = 0.01*3.782; weight = luminosity*xs/N;}
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
    
    
    tree->SetBranchAddress("run", &run);
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
    tree->SetBranchAddress("l2_decayMode", &l2_decayMode);
    tree->SetBranchAddress("passMu24", &passMu24);
    tree->SetBranchAddress("matchMu24_1", &matchMu24_1);
    tree->SetBranchAddress("filterMu24_1", &filterMu24_1);
    tree->SetBranchAddress("passMu27", &passMu27);
    tree->SetBranchAddress("matchMu27_1", &matchMu27_1);
    tree->SetBranchAddress("filterMu27_1", &filterMu27_1);
    tree->SetBranchAddress("passMu20Tau27", &passMu20Tau27);
    tree->SetBranchAddress("matchMu20Tau27_1", &matchMu20Tau27_1);
    tree->SetBranchAddress("filterMu20Tau27_1", &filterMu20Tau27_1);
    tree->SetBranchAddress("matchMu20Tau27_2", &matchMu20Tau27_2);
    tree->SetBranchAddress("filterMu20Tau27_2", &filterMu20Tau27_2);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_1", &matchEmbFilter_Mu20Tau27_1);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
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
    tree->SetBranchAddress("byTightDeepVSe_2", &byTightDeepVSe_2);
    tree->SetBranchAddress("byVLooseDeepVSmu_2", &byVLooseDeepVSmu_2);
    tree->SetBranchAddress("byMediumDeepVSjet_2", &byMediumDeepVSjet_2);
    tree->SetBranchAddress("byVVVLooseDeepVSjet_2", &byVVVLooseDeepVSjet_2);
    tree->SetBranchAddress("byVLooseDeepVSe_2", &byVLooseDeepVSe_2);
    tree->SetBranchAddress("byTightDeepVSmu_2", &byTightDeepVSmu_2);
    
    TH1F * hist_m_mt = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mtb = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_mtb_qcd = new TH1F("", "", 40, 50., 450.);
    TH1F * hist_m_mtbb = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_mtbb_qcd = new TH1F("", "", 50, 100., 600.);
    TH1F * hist_m_pt = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_mt_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_mt_qcd_1 = new TH1F("", "", 8, 0., 64.);
    TH1F * hist_m_mt_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_mt_qcd_2 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_mt_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_mt_qcd_3 = new TH1F("", "", 10, 0., 80.);
    TH1F * hist_m_mt_4 = new TH1F("", "", 10, 0., 200.);
    TH1F * hist_m_mt_qcd_4 = new TH1F("", "", 10, 0., 200.);
    
    TH1F * hist_m_mt_0b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_0b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_pt_0b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_0b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_0b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_0b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_mt_1b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_1b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_pt_1b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_1b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_1b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_1b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_mt_2b = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_2b_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_pt_2b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_2b_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_2b = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_2b_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_mt_vbf = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_vbf_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_pt_vbf = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vbf_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vbf = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vbf_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_m_mt_vv = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_vv_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_pt_vv = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_m_pt_vv_qcd = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vv = new TH1F("", "", 30, 0., 150.);
    TH1F * hist_t_pt_vv_qcd = new TH1F("", "", 30, 0., 150.);
    
    TH1F * hist_0bw_0 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_0bw_1 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_0bw_2 = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_1bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_2bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_al1bw = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_zpt = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_qcd = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_sigtrg_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_xtrg_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_mid_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_top = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_pu = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_gen_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_tid_mc = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_sigtrg_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_xtrg_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_mid_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_embsel = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_gen_emb = new TH1F("", "", 40, 0., 2.);
    TH1F * hist_tid_emb = new TH1F("", "", 40, 0., 2.);
    
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
    
    //Tau id sf files for MC and embedded
    TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco.root");
    TF1 *fct_tauid = (TF1*) ftauid->Get("Medium_cent");
    TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco_EMB.root");
    TF1 *fct_tauid_emb = (TF1*) ftauid_emb->Get("Medium_cent");
    
    //access graphs for the tau fake rates
    TFile *f_taufr = new TFile("FitHistograms_tauFR_2017.root");
    TGraphAsymmErrors *g_taufr_dm0M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm0_deepmedium_hpt_dm0_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm1M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm1_deepmedium_hpt_dm1_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm10M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm10_deepmedium_hpt_dm10_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm11M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm11_deepmedium_hpt_dm11_deepveryveryveryloose");
    
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
        
        //mutau selection
        bool trigger24OR27=((passMu24 && matchMu24_1 && filterMu24_1 && pt_1>25) or (passMu27 && matchMu27_1 && filterMu27_1 && pt_1>28));
        bool trigger2027 = (passMu20Tau27 && matchMu20Tau27_1 && filterMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_2 && pt_1>21 && pt_1<25 && pt_2>32 && fabs(eta_2)<2.1);
        if (sample=="embedded") trigger2027 = (matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20Tau27_2 && pt_1>21 && pt_1<25 && pt_2>32 && fabs(eta_2)<2.1);
        if (!trigger24OR27 && !trigger2027) continue;
        
        if (!(pt_2>25)) continue;
        if (!(fabs(eta_1)<2.1 && fabs(eta_2)<2.3)) continue;
        if (!(iso_1<0.15)) continue;
        if (q_1*q_2>0) continue;
        
        //discriminators for e/mu faking tau_h (many Z->mumu so tight for mu; rare e+mu so loose for e)
        if (!(byVLooseDeepVSe_2 && byTightDeepVSmu_2)) continue;
        
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        if (!(mymu.DeltaR(mytau)>0.4)) continue;
        
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0) weight = 2.575;
            else if (numGenJets==1) weight = 0.7084;
            else if (numGenJets==2) weight = 0.9192;
            else if (numGenJets==3) weight = 1.648;
            else if (numGenJets==4) weight = 0.2192;
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0) weight = 25.46;
            else if (numGenJets==1) weight = 5.773;
            else if (numGenJets==2) weight = 1.792;
            else if (numGenJets==3) weight = 0.6829;
            else if (numGenJets==4) weight = 0.7365;
        }
        
        float sf_MC = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            //reject MC with a jet faking tau_h as duplicated in fake background estimation
            if (gen_match_2==6) continue;
            
            //reject MC with 2 taus as duplicated in embedded sample except for signal/Higgs
            if (sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="VBFbbtt20" && sample!="VBFbbtt40" && sample!="VBFbbtt60" && name!="HTT" && sample!="ttHnonbb"){
                if (gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            }
            
            //initialize workspace with lepton kinematics
            wmc->var("t_pt")->setVal(pt_2);
            wmc->var("t_eta")->setVal(eta_2);
            wmc->var("t_phi")->setVal(phi_2);
            wmc->var("t_dm")->setVal(l2_decayMode);
            wmc->var("m_pt")->setVal(pt_1);
            wmc->var("m_eta")->setVal(eta_1);
            wmc->var("m_iso")->setVal(iso_1);
            
            //trigger scale factor
            if (mymu.Pt()>25){
                sf_MC *= wmc->function("m_trg_ic_ratio")->getVal();
                hist_sigtrg_mc->Fill(wmc->function("m_trg_ic_ratio")->getVal());
            }
            else{
                float trg_sf=wmc->function("t_trg_pog_deeptau_medium_mutau_ratio")->getVal();
                sf_MC *= wmc->function("m_trg_20_ic_ratio")->getVal()*trg_sf;
                hist_xtrg_mc->Fill(wmc->function("m_trg_20_ic_ratio")->getVal()*trg_sf);
            }
            
            //muon ID/iso/tracking scale factors
            sf_MC *= wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_ratio")->getVal();
            hist_mid_mc->Fill(wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_ratio")->getVal());
            
            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                wmc->var("z_gen_mass")->setVal(genM);
                wmc->var("z_gen_pt")->setVal(genpT);
                float zptweight = wmc->function("zptmass_weight_nom")->getVal();
                sf_MC *= zptweight;
                hist_zpt->Fill(zptweight);
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                float topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
                hist_top->Fill(topfactor);
            }
            
            //re-weigh pileup distribution
            float puweight = LumiWeights_12->weight(npu);
            sf_MC *= puweight;
            hist_pu->Fill(puweight);
            
            //generator weight
            sf_MC *= genweight;
            hist_gen_mc->Fill(genweight);
            
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5){
                sf_MC *= fct_tauid->Eval(mytau.Pt());
                hist_tid_mc->Fill(fct_tauid->Eval(mytau.Pt()));
            }
            
            //ele->tauh and muon->tauh sf
            if (gen_match_2==1 or gen_match_2==3){
                if (fabs(eta_2)<1.448) sf_MC *= 0.93;
                else sf_MC *= 1.00;
            }
            if (gen_match_2==2 or gen_match_2==4){
                if (fabs(eta_2)<0.4) sf_MC *= 0.979*0.991;
                else if (fabs(eta_2)<0.8) sf_MC *= 0.953*0.675;
                else if (fabs(eta_2)<1.2) sf_MC *= 0.983*0.675;
                else if (fabs(eta_2)<1.7) sf_MC *= 0.988*1.098;
                else sf_MC *= 1.004*4.175;
            }
            
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            //rejecting buggy events
            if (genweight>1.0) continue;
            
            //initialize workspace with lepton kinematics
            wmc->var("t_pt")->setVal(pt_2);
            wmc->var("t_eta")->setVal(eta_2);
            wmc->var("t_phi")->setVal(phi_2);
            wmc->var("t_dm")->setVal(l2_decayMode);
            wmc->var("m_pt")->setVal(pt_1);
            wmc->var("m_eta")->setVal(eta_1);
            wmc->var("m_iso")->setVal(iso_1);
            
            //trigger scale factor
            if (mymu.Pt()>25){
                sf_MC *= wmc->function("m_trg_ic_embed_ratio")->getVal();
                hist_sigtrg_emb->Fill(wmc->function("m_trg_ic_embed_ratio")->getVal());
            }
            else{
                float trg_sf=wmc->function("t_trg_pog_deeptau_medium_mutau_ratio")->getVal();
                sf_MC *= wmc->function("m_trg_20_ic_embed_ratio")->getVal()*trg_sf;
                hist_xtrg_emb->Fill(wmc->function("m_trg_20_ic_embed_ratio")->getVal()*trg_sf);
            }
            
            //muon ID/iso/tracking scale factors
            sf_embed *= wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_embed_ratio")->getVal();
            hist_mid_emb->Fill(wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_embed_ratio")->getVal());
            
            //efficiency of selecting Z->mumu data
            float embsel =1.0;
            wmc->var("gt1_pt")->setVal(genpt_1);
            wmc->var("gt2_pt")->setVal(pt_2);
            wmc->var("gt1_eta")->setVal(geneta_1);
            wmc->var("gt2_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            embsel*=wmc->function("m_sel_trg_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_1);
            wmc->var("gt_eta")->setVal(geneta_1);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            embsel*=wmc->function("m_sel_id_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(pt_2);
            wmc->var("gt_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            embsel*=wmc->function("m_sel_id_ic_ratio")->getVal();
            hist_embsel->Fill(embsel);
            
            //generator weight
            sf_embed *= genweight;
            hist_gen_emb->Fill(genweight);
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5){
                sf_embed *= fct_tauid_emb->Eval(mytau.Pt());
                hist_tid_emb->Fill(fct_tauid_emb->Eval(mytau.Pt()));
            }
            
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
            
            if (nbtag20==0) hist_0bw_0->Fill(weight_btag_0b);
            if (nbtag20==1) {hist_0bw_1->Fill(weight_btag_0b); hist_1bw->Fill(weight_btag_1b);}
            if (nbtag20==2) {hist_0bw_2->Fill(weight_btag_0b); hist_2bw->Fill(weight_btag_2b);}
            if (nbtag20==1 or nbtag20==2) hist_al1bw->Fill(weight_btag_atleast1b);
            
        }
        
        //defining variables for some categories
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        
        float mt_mumet=TMass_F((mymu).Pt(),mymet.Pt(),(mymu).Px(),mymet.Px(),(mymu).Py(),mymet.Py());
        float mt_taumet=TMass_F((mytau).Pt(),mymet.Pt(),(mytau).Px(),mymet.Px(),(mytau).Py(),mymet.Py());
        
        float norm_zeta=norm_F(mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt(),mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(mymu.Px()+mytau.Px())*x_zeta+(mymu.Py()+mytau.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        //filling histograms
        float m_mt = (mymu + mytau).M();
        float m_mtb = (mymu + mytau + myb1).M();
        float m_mtbb = (mymu + mytau + myb1 + myb2).M();
        
        //jet faking tau_h (to be failed in qcd)
        if (byMediumDeepVSjet_2){
            //at least 1 b
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4))){
                
                hist_m_mt->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                hist_m_mtb->Fill(m_mtb,weight_corr*weight_btag_atleast1b);
                hist_m_pt->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                hist_t_pt->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                if (nbtag20==2) hist_m_mtbb->Fill(m_mtbb,weight_corr*weight_btag_atleast1b);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_mt_vbf->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                    hist_m_pt_vbf->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                    hist_t_pt_vbf->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                }
                
                //the 4 categories
                if (mt_taumet<60){
                    //category 1
                    if (m_mtb<75 && mt_mumet<40){
                        hist_m_mt_1->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                    }
                    //category 2
                    if (m_mtb>75 && m_mtb<95 && mt_mumet<50 && dzeta<0){
                        hist_m_mt_2->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                    }
                    //category 3
                    if (m_mtb>95 && m_mtb<115 && mt_mumet<50){
                        hist_m_mt_3->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                    }
                    //category 4
                    if (m_mtb>115 && mt_mumet<40){
                        hist_m_mt_4->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                    }
                }
            }
            //0 bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_mt_0b->Fill(m_mt,weight_corr*weight_btag_0b);
                hist_m_pt_0b->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_t_pt_0b->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_mt>100){
                    hist_m_mt_vv->Fill(m_mt,weight_corr*weight_btag_0b);
                    hist_m_pt_vv->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_t_pt_vv->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //0 bjet MC (keep events with any no. of bjet
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_mt_0b->Fill(m_mt,weight_corr*weight_btag_0b);
                hist_m_pt_0b->Fill(pt_1,weight_corr*weight_btag_0b);
                hist_t_pt_0b->Fill(pt_2,weight_corr*weight_btag_0b);
                //diboson
                if (m_mt>100){
                    hist_m_mt_vv->Fill(m_mt,weight_corr*weight_btag_0b);
                    hist_m_pt_vv->Fill(pt_1,weight_corr*weight_btag_0b);
                    hist_t_pt_vv->Fill(pt_2,weight_corr*weight_btag_0b);
                }
            }
            //1 bjet
            if (nbtag20==1){
                hist_m_mt_1b->Fill(m_mt,weight_corr*weight_btag_1b);
                hist_m_pt_1b->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_t_pt_1b->Fill(pt_2,weight_corr*weight_btag_1b);
            }
            //2 bjets
            if (nbtag20==2){
                hist_m_mt_2b->Fill(m_mt,weight_corr*weight_btag_2b);
                hist_m_pt_2b->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_t_pt_2b->Fill(pt_2,weight_corr*weight_btag_2b);
            }
        }
        
        //for qcd background
        if (byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2){
            //fake rates
            float fr = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dm0M,g_taufr_dm1M,g_taufr_dm10M,g_taufr_dm11M,0);
            float weight_qcd = fr/(1-fr);
            
            hist_qcd->Fill(weight_qcd);
            
            //at least 1 b
            if (((nbtag20==1 && fabs(beta_deepcsv_1)<2.4) or (nbtag20==2 && fabs(beta_deepcsv_1)<2.4 && fabs(beta_deepcsv_2)<2.4))){
                
                hist_m_mt_qcd->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_m_mtb_qcd->Fill(m_mtb,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_m_pt_qcd->Fill(pt_1,weight_corr*weight_btag_atleast1b*weight_qcd);
                hist_t_pt_qcd->Fill(pt_2,weight_corr*weight_btag_atleast1b*weight_qcd);
                if (nbtag20==2) hist_m_mtbb_qcd->Fill(m_mtbb,weight_corr*weight_btag_atleast1b*weight_qcd);
                
                //vbf at least 1 b
                if (mjj>500){
                    hist_m_mt_vbf_qcd->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                    hist_m_pt_vbf_qcd->Fill(pt_1,weight_corr*weight_btag_atleast1b*weight_qcd);
                    hist_t_pt_vbf_qcd->Fill(pt_2,weight_corr*weight_btag_atleast1b*weight_qcd);
                }
                
                //the 4 categories
                if (mt_taumet<60){
                    //category 1
                    if (m_mtb<75 && mt_mumet<40){
                        hist_m_mt_qcd_1->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 2
                    if (m_mtb>75 && m_mtb<95 && mt_mumet<50 && dzeta<0){
                        hist_m_mt_qcd_2->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 3
                    if (m_mtb>95 && m_mtb<115 && mt_mumet<50){
                        hist_m_mt_qcd_3->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                    //category 4
                    if (m_mtb>115 && mt_mumet<40){
                        hist_m_mt_qcd_4->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd);
                    }
                }
            }
            //0 bjet data/embedded
            if ((sample=="data_obs" or sample=="embedded") && nbtag20==0){
                hist_m_mt_0b_qcd->Fill(m_mt,weight_corr*weight_btag_0b*weight_qcd);
                hist_m_pt_0b_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                hist_t_pt_0b_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                //diboson
                if (m_mt>100){
                    hist_m_mt_vv_qcd->Fill(m_mt,weight_corr*weight_btag_0b*weight_qcd);
                    hist_m_pt_vv_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                    hist_t_pt_vv_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                }
            }
            //0 bjet MC (keep events with any no. of bjet
            if (sample!="data_obs" && sample!="embedded"){
                hist_m_mt_0b_qcd->Fill(m_mt,weight_corr*weight_btag_0b*weight_qcd);
                hist_m_pt_0b_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                hist_t_pt_0b_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                //diboson
                if (m_mt>100){
                    hist_m_mt_vv_qcd->Fill(m_mt,weight_corr*weight_btag_0b*weight_qcd);
                    hist_m_pt_vv_qcd->Fill(pt_1,weight_corr*weight_btag_0b*weight_qcd);
                    hist_t_pt_vv_qcd->Fill(pt_2,weight_corr*weight_btag_0b*weight_qcd);
                }
            }
            //1 bjet
            if (nbtag20==1){
                hist_m_mt_1b_qcd->Fill(m_mt,weight_corr*weight_btag_1b*weight_qcd);
                hist_m_pt_1b_qcd->Fill(pt_1,weight_corr*weight_btag_1b*weight_qcd);
                hist_t_pt_1b_qcd->Fill(pt_2,weight_corr*weight_btag_1b*weight_qcd);
            }
            //2 bjets
            if (nbtag20==2){
                hist_m_mt_2b_qcd->Fill(m_mt,weight_corr*weight_btag_2b*weight_qcd);
                hist_m_pt_2b_qcd->Fill(pt_1,weight_corr*weight_btag_2b*weight_qcd);
                hist_t_pt_2b_qcd->Fill(pt_2,weight_corr*weight_btag_2b*weight_qcd);
            }
        }
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    TDirectory * td1 = fout->mkdir("m_mt_1");
    TDirectory * td2 = fout->mkdir("m_mt_2");
    TDirectory * td3 = fout->mkdir("m_mt_3");
    TDirectory * td4 = fout->mkdir("m_mt_4");
    TDirectory * td5 = fout->mkdir("m_mt");
    TDirectory * td6 = fout->mkdir("m_mtb");
    TDirectory * td7 = fout->mkdir("m_mtbb");
    TDirectory * td8 = fout->mkdir("pt_m");
    TDirectory * td9 = fout->mkdir("pt_t");
    
    TDirectory * td10 = fout->mkdir("m_mt_0b");
    TDirectory * td11 = fout->mkdir("pt_m_0b");
    TDirectory * td12 = fout->mkdir("pt_t_0b");
    TDirectory * td13 = fout->mkdir("m_mt_1b");
    TDirectory * td14 = fout->mkdir("pt_m_1b");
    TDirectory * td15 = fout->mkdir("pt_t_1b");
    TDirectory * td16 = fout->mkdir("m_mt_2b");
    TDirectory * td17 = fout->mkdir("pt_m_2b");
    TDirectory * td18 = fout->mkdir("pt_t_2b");
    TDirectory * td19 = fout->mkdir("m_mt_vbf");
    TDirectory * td20 = fout->mkdir("pt_m_vbf");
    TDirectory * td21 = fout->mkdir("pt_t_vbf");
    TDirectory * td22 = fout->mkdir("m_mt_vv");
    TDirectory * td23 = fout->mkdir("pt_m_vv");
    TDirectory * td24 = fout->mkdir("pt_t_vv");
    
    TDirectory * td25 = fout->mkdir("weights");
    
    TString qcd="_qcd";
    
    td1->cd();
    hist_m_mt_1->SetName(name.c_str());
    hist_m_mt_1->Write();
    hist_m_mt_qcd_1->SetName(name.c_str()+qcd);
    hist_m_mt_qcd_1->Write();
    
    td2->cd();
    hist_m_mt_2->SetName(name.c_str());
    hist_m_mt_2->Write();
    hist_m_mt_qcd_2->SetName(name.c_str()+qcd);
    hist_m_mt_qcd_2->Write();
    
    td3->cd();
    hist_m_mt_3->SetName(name.c_str());
    hist_m_mt_3->Write();
    hist_m_mt_qcd_3->SetName(name.c_str()+qcd);
    hist_m_mt_qcd_3->Write();
    
    td4->cd();
    hist_m_mt_4->SetName(name.c_str());
    hist_m_mt_4->Write();
    hist_m_mt_qcd_4->SetName(name.c_str()+qcd);
    hist_m_mt_qcd_4->Write();
    
    td5->cd();
    hist_m_mt->SetName(name.c_str());
    hist_m_mt->Write();
    hist_m_mt_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_qcd->Write();
    
    td6->cd();
    hist_m_mtb->SetName(name.c_str());
    hist_m_mtb->Write();
    hist_m_mtb_qcd->SetName(name.c_str()+qcd);
    hist_m_mtb_qcd->Write();
    
    td7->cd();
    hist_m_mtbb->SetName(name.c_str());
    hist_m_mtbb->Write();
    hist_m_mtbb_qcd->SetName(name.c_str()+qcd);
    hist_m_mtbb_qcd->Write();
    
    td8->cd();
    hist_m_pt->SetName(name.c_str());
    hist_m_pt->Write();
    hist_m_pt_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_qcd->Write();
    
    td9->cd();
    hist_t_pt->SetName(name.c_str());
    hist_t_pt->Write();
    hist_t_pt_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_qcd->Write();
    
    td10->cd();
    hist_m_mt_0b->SetName(name.c_str());
    hist_m_mt_0b->Write();
    hist_m_mt_0b_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_0b_qcd->Write();
    
    td11->cd();
    hist_m_pt_0b->SetName(name.c_str());
    hist_m_pt_0b->Write();
    hist_m_pt_0b_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_0b_qcd->Write();
    
    td12->cd();
    hist_t_pt_0b->SetName(name.c_str());
    hist_t_pt_0b->Write();
    hist_t_pt_0b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_0b_qcd->Write();
    
    td13->cd();
    hist_m_mt_1b->SetName(name.c_str());
    hist_m_mt_1b->Write();
    hist_m_mt_1b_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_1b_qcd->Write();
    
    td14->cd();
    hist_m_pt_1b->SetName(name.c_str());
    hist_m_pt_1b->Write();
    hist_m_pt_1b_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_1b_qcd->Write();
    
    td15->cd();
    hist_t_pt_1b->SetName(name.c_str());
    hist_t_pt_1b->Write();
    hist_t_pt_1b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_1b_qcd->Write();
    
    td16->cd();
    hist_m_mt_2b->SetName(name.c_str());
    hist_m_mt_2b->Write();
    hist_m_mt_2b_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_2b_qcd->Write();
    
    td17->cd();
    hist_m_pt_2b->SetName(name.c_str());
    hist_m_pt_2b->Write();
    hist_m_pt_2b_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_2b_qcd->Write();
    
    td18->cd();
    hist_t_pt_2b->SetName(name.c_str());
    hist_t_pt_2b->Write();
    hist_t_pt_2b_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_2b_qcd->Write();
    
    td19->cd();
    hist_m_mt_vbf->SetName(name.c_str());
    hist_m_mt_vbf->Write();
    hist_m_mt_vbf_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_vbf_qcd->Write();
    
    td20->cd();
    hist_m_pt_vbf->SetName(name.c_str());
    hist_m_pt_vbf->Write();
    hist_m_pt_vbf_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_vbf_qcd->Write();
    
    td21->cd();
    hist_t_pt_vbf->SetName(name.c_str());
    hist_t_pt_vbf->Write();
    hist_t_pt_vbf_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_vbf_qcd->Write();
    
    td22->cd();
    hist_m_mt_vv->SetName(name.c_str());
    hist_m_mt_vv->Write();
    hist_m_mt_vv_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_vv_qcd->Write();
    
    td23->cd();
    hist_m_pt_vv->SetName(name.c_str());
    hist_m_pt_vv->Write();
    hist_m_pt_vv_qcd->SetName(name.c_str()+qcd);
    hist_m_pt_vv_qcd->Write();
    
    td24->cd();
    hist_t_pt_vv->SetName(name.c_str());
    hist_t_pt_vv->Write();
    hist_t_pt_vv_qcd->SetName(name.c_str()+qcd);
    hist_t_pt_vv_qcd->Write();
    
    td25->cd();
    hist_0bw_0->SetName("0bw_0b");
    hist_0bw_0->Write();
    hist_0bw_1->SetName("0bw_1b");
    hist_0bw_1->Write();
    hist_0bw_2->SetName("0bw_2b");
    hist_0bw_2->Write();
    hist_1bw->SetName("1bw");
    hist_1bw->Write();
    hist_2bw->SetName("2bw");
    hist_2bw->Write();
    hist_al1bw->SetName("al1bw");
    hist_al1bw->Write();
    hist_zpt->SetName("zptweight");
    hist_zpt->Write();
    hist_qcd->SetName("qcdweight");
    hist_qcd->Write();
    hist_sigtrg_mc->SetName("sigtrg_mc");
    hist_sigtrg_mc->Write();
    hist_xtrg_mc->SetName("xtrg_mc");
    hist_xtrg_mc->Write();
    hist_mid_mc->SetName("mid_mc");
    hist_mid_mc->Write();
    hist_top->SetName("top");
    hist_top->Write();
    hist_pu->SetName("pu");
    hist_pu->Write();
    hist_gen_mc->SetName("gen_mc");
    hist_gen_mc->Write();
    hist_tid_mc->SetName("tid_mc");
    hist_tid_mc->Write();
    hist_sigtrg_emb->SetName("sigtrg_emb");
    hist_sigtrg_emb->Write();
    hist_xtrg_emb->SetName("xtrg_emb");
    hist_xtrg_emb->Write();
    hist_mid_emb->SetName("mid_emb");
    hist_mid_emb->Write();
    hist_embsel->SetName("embsel");
    hist_embsel->Write();
    hist_gen_emb->SetName("gen_emb");
    hist_gen_emb->Write();
    hist_tid_emb->SetName("tid_emb");
    hist_tid_emb->Write();
    
    
    
    fout->Close();
    
    delete wmc;
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}






