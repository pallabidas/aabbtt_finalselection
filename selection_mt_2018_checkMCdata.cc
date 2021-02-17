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
#include "btagSF_2018.h"
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
    /*
    std::string dnnfile = sample.c_str();
    dnnfile = "/hdfs/store/user/htsoi/dnn/mt18/" + dnnfile + ".root";
    TFile * dnn = new TFile(dnnfile.c_str());
    TTree * tree_dnn = (TTree*) dnn->Get("mutau_tree_dnn");
    */
    //sample weights
    float xs, weight, luminosity = 59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt12"){xs = 0.01*48.58*0.0380; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58*0.0355; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58*0.0336; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58*0.0321; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58*0.0329; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58*0.0403; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt12"){xs = 0.01*3.782*0.0785; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt20"){xs = 0.01*3.782*0.0749; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt30"){xs = 0.01*3.782*0.0717; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt40"){xs = 0.01*3.782*0.0682; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt50"){xs = 0.01*3.782*0.0661; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt60"){xs = 0.01*3.782*0.0676; weight = luminosity*xs/N;}
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
    else if(sample == "ST_tW_antitop"){xs = 35.85; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.85; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 80.94; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 136.02; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VBFHWW"){xs = 3.782*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 13.84; weight = luminosity*xs/N;}//11.95
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.52; weight = luminosity*xs/N;}//5.595
    else if(sample == "WZ3LNu"){xs = 4.43; weight = luminosity*xs/N;}//4.708
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WminusHWW"){xs = 0.5328*0.2137; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHWW"){xs = 0.840*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHWW"){xs = 0.7612*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.38; weight = luminosity*xs/N;}//3.22
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
    tree->SetBranchAddress("passMu20HPSTau27", &passMu20HPSTau27);
    tree->SetBranchAddress("matchMu20HPSTau27_1", &matchMu20HPSTau27_1);
    tree->SetBranchAddress("filterMu20HPSTau27_1", &filterMu20HPSTau27_1);
    tree->SetBranchAddress("matchMu20HPSTau27_2", &matchMu20HPSTau27_2);
    tree->SetBranchAddress("filterMu20HPSTau27_2", &filterMu20HPSTau27_2);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_1", &matchEmbFilter_Mu20Tau27_1);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
    tree->SetBranchAddress("matchEmbFilter_Mu20HPSTau27_2", &matchEmbFilter_Mu20HPSTau27_2);
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
    tree->SetBranchAddress("genweight", &genweight);
    tree->SetBranchAddress("mjj", &mjj);
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
    tree->SetBranchAddress("m_trg_ic_ratio", &m_trg_ic_ratio);
    tree->SetBranchAddress("m_trg_20_ratio", &m_trg_20_ratio);
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_mutau_ratio", &t_trg_pog_deeptau_medium_mutau_ratio);
    tree->SetBranchAddress("m_trk_ratio", &m_trk_ratio);
    tree->SetBranchAddress("m_idiso_ic_ratio", &m_idiso_ic_ratio);
    tree->SetBranchAddress("zptmass_weight_nom", &zptmass_weight_nom);
    tree->SetBranchAddress("m_trg_ic_embed_ratio", &m_trg_ic_embed_ratio);
    tree->SetBranchAddress("m_trg_20_ic_embed_ratio", &m_trg_20_ic_embed_ratio);
    tree->SetBranchAddress("t_trg_mediumDeepTau_mutau_embed_ratio", &t_trg_mediumDeepTau_mutau_embed_ratio);
    tree->SetBranchAddress("m_idiso_ic_embed_ratio", &m_idiso_ic_embed_ratio);
    tree->SetBranchAddress("m_sel_trg_ic_ratio", &m_sel_trg_ic_ratio);
    tree->SetBranchAddress("m_sel_id_ic_ratio_1", &m_sel_id_ic_ratio_1);
    tree->SetBranchAddress("m_sel_id_ic_ratio_2", &m_sel_id_ic_ratio_2);
    tree->SetBranchAddress("m_sv", &m_sv);
    
    //tree_dnn->SetBranchAddress("pred_1b", &pred_1b);
    //tree_dnn->SetBranchAddress("pred_2b", &pred_2b);
    
    //1b
    TH1F * hist_pt_t1_1b_OS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t1_1b_SS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t2_1b_OS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t2_1b_SS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_m_btt_1b_OS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_btt_1b_SS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bt1_1b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_bt1_1b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_bt2_1b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_bt2_1b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_dr_tt_1b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_tt_1b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bt1_1b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bt1_1b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bt2_1b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bt2_1b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_btt_1b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_btt_1b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_pt_tt_1b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_pt_tt_1b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_eta_tt_1b_OS = new TH1F("","", 48, -2.4, 2.4);
    TH1F * hist_eta_tt_1b_SS = new TH1F("","", 48, -2.4, 2.4);
    TH1F * hist_mt_t1_1b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t1_1b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t2_1b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t2_1b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_b_1b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_b_1b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_normzeta_1b_OS = new TH1F("","", 20, 0., 2.);
    TH1F * hist_normzeta_1b_SS = new TH1F("","", 20, 0., 2.);
    TH1F * hist_dzeta_1b_OS = new TH1F("","", 35, -200., 150.);
    TH1F * hist_dzeta_1b_SS = new TH1F("","", 35, -200., 150.);
    TH1F * hist_pt_b_1b_OS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_pt_b_1b_SS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_met_1b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_met_1b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_njets_1b_OS = new TH1F("","", 8, 0., 8.);
    TH1F * hist_njets_1b_SS = new TH1F("","", 8, 0., 8.);
    
    //2b
    TH1F * hist_pt_t1_2b_OS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t1_2b_SS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t2_2b_OS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_pt_t2_2b_SS = new TH1F("","", 12, 0., 120.);
    TH1F * hist_m_b1tt_2b_OS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_b1tt_2b_SS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_b1t1_2b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b1t1_2b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b1t2_2b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b1t2_2b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_dr_tt_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_tt_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1t1_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1t1_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1t2_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1t2_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1tt_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b1tt_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_pt_tt_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_pt_tt_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_eta_tt_2b_OS = new TH1F("","", 48, -2.4, 2.4);
    TH1F * hist_eta_tt_2b_SS = new TH1F("","", 48, -2.4, 2.4);
    TH1F * hist_mt_t1_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t1_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t2_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_t2_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_b1_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_b1_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_normzeta_2b_OS = new TH1F("","", 20, 0., 2.);
    TH1F * hist_normzeta_2b_SS = new TH1F("","", 20, 0., 2.);
    TH1F * hist_dzeta_2b_OS = new TH1F("","", 35, -200., 150.);
    TH1F * hist_dzeta_2b_SS = new TH1F("","", 35, -200., 150.);
    TH1F * hist_pt_b1_2b_OS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_pt_b1_2b_SS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_met_2b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_met_2b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_njets_2b_OS = new TH1F("","", 8, 0., 8.);
    TH1F * hist_njets_2b_SS = new TH1F("","", 8, 0., 8.);
    TH1F * hist_m_b2tt_2b_OS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_b2tt_2b_SS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bbt1_2b_OS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bbt1_2b_SS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bbt2_2b_OS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bbt2_2b_SS = new TH1F("","", 42, 30., 450.);
    TH1F * hist_m_bbtt_2b_OS = new TH1F("","", 57, 30., 600.);
    TH1F * hist_m_bbtt_2b_SS = new TH1F("","", 57, 30., 600.);
    TH1F * hist_m_bb_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_m_bb_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_m_b2t1_2b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b2t1_2b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b2t2_2b_OS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_m_b2t2_2b_SS = new TH1F("","", 20, 0., 200.);
    TH1F * hist_dr_b2t1_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b2t1_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b2t2_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b2t2_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bb_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bb_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b2tt_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_b2tt_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbtt_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbtt_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbt1_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbt1_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbt2_2b_OS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_dr_bbt2_2b_SS = new TH1F("","", 50, 0., 5.);
    TH1F * hist_mt_b2_2b_OS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_mt_b2_2b_SS = new TH1F("","", 25, 0., 250.);
    TH1F * hist_pt_b2_2b_OS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_pt_b2_2b_SS = new TH1F("","", 15, 0., 150.);
    TH1F * hist_dma_2b_OS = new TH1F("","", 60, -2., 4.);
    TH1F * hist_dma_2b_SS = new TH1F("","", 60, -2., 4.);
    
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    
    //Tau id sf files for MC and embedded
    TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
    TF1 *fct_tauid = (TF1*) ftauid->Get("Medium_cent");
    TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco_EMB.root");
    TF1 *fct_tauid_emb = (TF1*) ftauid_emb->Get("Medium_cent");
    
    //access graphs for the tau fake rates
    TFile *f_taufr = new TFile("FitHistograms_tauFR_2018.root");
    TGraphAsymmErrors *g_taufr_dm0M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm0_VLe_Tmu_deepmedium_hpt_dm0_VLe_Tmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm1M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm1_VLe_Tmu_deepmedium_hpt_dm1_VLe_Tmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm10M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm10_VLe_Tmu_deepmedium_hpt_dm10_VLe_Tmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm11M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm11_VLe_Tmu_deepmedium_hpt_dm11_VLe_Tmu_deepveryveryveryloose");
    
    TGraphAsymmErrors *g_taufr_dmall = (TGraphAsymmErrors*) f_taufr->Get("hpt_dmall_VLe_Tmu_1jet_deepmedium_hpt_dmall_VLe_Tmu_1jet_deepveryveryveryloose");
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        if(i % 10000 == 0) printf("event %d of %d...\n", i, n);
        tree->GetEntry(i);
        //tree_dnn->GetEntry(i);
        
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
        bool trigger24OR27 = ((passMu24 && matchMu24_1 && filterMu24_1 && pt_1>25) or (passMu27 && matchMu27_1 && filterMu27_1 && pt_1>25));//keep 25 not 28
        bool trigger2027 = (passMu20Tau27 && matchMu20Tau27_1 && filterMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_2 && pt_1>21 && pt_1<25 && pt_2>32 && fabs(eta_2)<2.1);
        bool trigger2027HPS = (passMu20HPSTau27 && matchMu20HPSTau27_1 && filterMu20HPSTau27_1 && matchMu20HPSTau27_2 && filterMu20HPSTau27_2 && pt_1>21 && pt_1<25 && pt_2>32 && fabs(eta_2)<2.1);
        if (sample=="embedded"){
            trigger2027HPS = (matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20HPSTau27_2 && pt_1>21 && pt_1<25 && pt_2>32 && fabs(eta_2)<2.1);
            trigger24OR27 = ((passMu24 && matchMu24_1 && pt_1>25) or (passMu27 && matchMu27_1 && pt_1>25));
        }
        if (sample=="data_obs" && run<317509 && !trigger2027 && !trigger24OR27) continue;
        if (sample=="data_obs" && run>=317509 && !trigger2027HPS && !trigger24OR27) continue;
        if (sample!="data_obs" && sample!="embedded" && !trigger24OR27 && !trigger2027HPS) continue;
        if (sample=="embedded" && !trigger24OR27 && !trigger2027HPS) continue;
        
        if (!(pt_2>20)) continue;//25
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
            if (numGenJets==0) weight = 3.630;
            else if (numGenJets==1) weight = 0.6304;
            else if (numGenJets==2) weight = 0.5528;
            else if (numGenJets==3) weight = 0.6009;
            else if (numGenJets==4) weight = 0.8314;
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
            if (sample!="gghbbtt12" && sample!="gghbbtt20" && sample!="gghbbtt30" && sample!="gghbbtt40" && sample!="gghbbtt50" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt20" && sample!="vbfbbtt30" && sample!="vbfbbtt40" && sample!="vbfbbtt50" && sample!="vbfbbtt60" && name!="HTT" && name!="ttHnonbb"){
                if (gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            }

            //trigger scale factor
            if (mymu.Pt()>25){
                sf_MC *= m_trg_ic_ratio;
            }
            else{
                sf_MC *= m_trg_20_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
            }
            
            //muon ID/iso/tracking scale factors
            sf_MC *= m_trk_ratio * m_idiso_ic_ratio;
            
            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                sf_MC *= zptmass_weight_nom;
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
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5){
                sf_MC *= fct_tauid->Eval(mytau.Pt());
            }
            
            //ele->tauh and muon->tauh sf
            if (gen_match_2==1 or gen_match_2==3){
                if (fabs(eta_2)<1.448) sf_MC *= 0.95;
                else sf_MC *= 0.86;
            }
            if (gen_match_2==2 or gen_match_2==4){
                if (fabs(eta_2)<0.4) sf_MC *= 0.936*0.820;
                else if (fabs(eta_2)<0.8) sf_MC *= 0.874*1.436;
                else if (fabs(eta_2)<1.2) sf_MC *= 0.912*0.989;
                else if (fabs(eta_2)<1.7) sf_MC *= 0.953*0.875;
                else sf_MC *= 0.936*4.739;
            }
            
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            if (l2_decayMode==0) sf_embed *= 0.975;
            else if (l2_decayMode==1) sf_embed *= 0.975*1.051;
            else if (l2_decayMode==10) sf_embed *= 0.975*0.975*0.975;
            else sf_embed *= 0.975*0.975*0.975*1.051;
            
            if (gen_match_2==6) continue;
            
            //rejecting buggy events
            if (genweight>1.0) continue;
            
            //trigger scale factor
            if (mymu.Pt()>25){
                sf_MC *= m_trg_ic_embed_ratio;
            }
            else{
                sf_MC *= m_trg_20_ic_embed_ratio * t_trg_mediumDeepTau_mutau_embed_ratio;
            }//t_trg_pog_deeptau_medium_mutau_ratio
            
            //muon ID/iso/tracking scale factors
            sf_embed *= m_trk_ratio * m_idiso_ic_embed_ratio;
            
            //efficiency of selecting Z->mumu data
            sf_embed *= m_sel_trg_ic_ratio * m_sel_id_ic_ratio_1 * m_sel_id_ic_ratio_2;
            
            //generator weight
            sf_embed *= genweight;
            
            //tau id sf
            if (byMediumDeepVSjet_2 && gen_match_2==5) sf_embed *= fct_tauid_emb->Eval(mytau.Pt());
            
        }
        
        float weight_corr = weight * sf_MC * sf_embed;
        
        //counting reconstructed btagged jets
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        if (bpt_deepcsv_1>20 && bscore_deepcsv_1>0.4184 && fabs(beta_deepcsv_1)<2.4){
            bMpt_1 = bpt_deepcsv_1;
            bMflavor_1 = bflavour_deepcsv_1;
            nbtag20++;
        }
        if (bpt_deepcsv_2>20 && bscore_deepcsv_2>0.4184 && fabs(beta_deepcsv_2)<2.4){
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
//            if (nbtag20==1) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0);
//            if (nbtag20==2) weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0)+GetSF(1, bMpt_2, bMflavor_2, 0)-GetSF(1, bMpt_1, bMflavor_1, 0)*GetSF(1, bMpt_2, bMflavor_2, 0);
            weight_btag_atleast1b = GetSF(1, bMpt_1, bMflavor_1, 0);
        }
        
        //defining variables for some categories
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        
        float mt_tau1=TMass_F((mymu).Pt(),mymet.Pt(),(mymu).Px(),mymet.Px(),(mymu).Py(),mymet.Py());
        float mt_tau2=TMass_F((mytau).Pt(),mymet.Pt(),(mytau).Px(),mymet.Px(),(mytau).Py(),mymet.Py());
        
        float norm_zeta=norm_F(mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt(),mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(mymu.Px()+mytau.Px())*x_zeta+(mymu.Py()+mytau.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        TLorentzVector mytt;
        mytt.SetPtEtaPhiM((mymu+mytau+mymet).Pt(),(mymu+mytau+mymet).Eta(),(mymu+mytau+mymet).Phi(),m_sv);
        TLorentzVector myt1;
        myt1.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector myt2;
        myt2.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        //filling histograms
        float m_tt = m_sv;
        float m_b1tt = (mytt + myb1).M();
        float m_b2tt = (mytt + myb2).M();
        float m_bbtt = (mytt + myb1 + myb2).M();
        float m_b1t1 = (myt1 + myb1).M();
        float m_b1t2 = (myt2 + myb1).M();
        float m_b2t1 = (myt1 + myb2).M();
        float m_b2t2 = (myt2 + myb2).M();
        float m_bbt1 = (myt1 + myb1 + myb2).M();
        float m_bbt2 = (myt2 + myb1 + myb2).M();
        float m_bb = (myb1 + myb2).M();
        float dr_tt = myt1.DeltaR(myt2);
        float dr_bb = myb1.DeltaR(myb2);
        float dr_b1tt = myb1.DeltaR(mytt);
        float dr_b2tt = myb2.DeltaR(mytt);
        float dr_b1t1 = myb1.DeltaR(myt1);
        float dr_b1t2 = myb1.DeltaR(myt2);
        float dr_b2t1 = myb2.DeltaR(myt1);
        float dr_b2t2 = myb2.DeltaR(myt2);
        float dr_bbt1 = (myb1+myb2).DeltaR(myt1);
        float dr_bbt2 = (myb1+myb2).DeltaR(myt2);
        float dr_bbtt = (myb1+myb2).DeltaR(mytt);
        float mt_b1=TMass_F((myb1).Pt(),mymet.Pt(),(myb1).Px(),mymet.Px(),(myb1).Py(),mymet.Py());
        float mt_b2=TMass_F((myb2).Pt(),mymet.Pt(),(myb2).Px(),mymet.Px(),(myb2).Py(),mymet.Py());
        float dma = (m_bb-m_sv)/m_sv;
        
        //jet faking tau_h (to be failed in qcd)
        if (byMediumDeepVSjet_2){
            //fill 1b
            if (nbtag20==1){
                hist_pt_t1_1b_OS->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_pt_t2_1b_OS->Fill(pt_2,weight_corr*weight_btag_1b);
                hist_m_btt_1b_OS->Fill(m_b1tt,weight_corr*weight_btag_1b);
                hist_m_bt1_1b_OS->Fill(m_b1t1,weight_corr*weight_btag_1b);
                hist_m_bt2_1b_OS->Fill(m_b1t2,weight_corr*weight_btag_1b);
                hist_dr_tt_1b_OS->Fill(dr_tt,weight_corr*weight_btag_1b);
                hist_dr_bt1_1b_OS->Fill(dr_b1t1,weight_corr*weight_btag_1b);
                hist_dr_bt2_1b_OS->Fill(dr_b1t2,weight_corr*weight_btag_1b);
                hist_dr_btt_1b_OS->Fill(dr_b1tt,weight_corr*weight_btag_1b);
                hist_pt_tt_1b_OS->Fill(mytt.Pt(),weight_corr*weight_btag_1b);
                hist_eta_tt_1b_OS->Fill(mytt.Eta(),weight_corr*weight_btag_1b);
                hist_mt_t1_1b_OS->Fill(mt_tau1,weight_corr*weight_btag_1b);
                hist_mt_t2_1b_OS->Fill(mt_tau2,weight_corr*weight_btag_1b);
                hist_mt_b_1b_OS->Fill(mt_b1,weight_corr*weight_btag_1b);
                hist_normzeta_1b_OS->Fill(norm_zeta,weight_corr*weight_btag_1b);
                hist_dzeta_1b_OS->Fill(dzeta,weight_corr*weight_btag_1b);
                hist_pt_b_1b_OS->Fill(myb1.Pt(),weight_corr*weight_btag_1b);
                hist_met_1b_OS->Fill(met,weight_corr*weight_btag_1b);
                hist_njets_1b_OS->Fill(njets,weight_corr*weight_btag_1b);
            }
            //fill 2b
            if (nbtag20==2){
                hist_pt_t1_2b_OS->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_pt_t2_2b_OS->Fill(pt_2,weight_corr*weight_btag_2b);
                hist_m_b1tt_2b_OS->Fill(m_b1tt,weight_corr*weight_btag_2b);
                hist_m_b1t1_2b_OS->Fill(m_b1t1,weight_corr*weight_btag_2b);
                hist_m_b1t2_2b_OS->Fill(m_b1t2,weight_corr*weight_btag_2b);
                hist_dr_tt_2b_OS->Fill(dr_tt,weight_corr*weight_btag_2b);
                hist_dr_b1t1_2b_OS->Fill(dr_b1t1,weight_corr*weight_btag_2b);
                hist_dr_b1t2_2b_OS->Fill(dr_b1t2,weight_corr*weight_btag_2b);
                hist_dr_b1tt_2b_OS->Fill(dr_b1tt,weight_corr*weight_btag_2b);
                hist_pt_tt_2b_OS->Fill(mytt.Pt(),weight_corr*weight_btag_2b);
                hist_eta_tt_2b_OS->Fill(mytt.Eta(),weight_corr*weight_btag_2b);
                hist_mt_t1_2b_OS->Fill(mt_tau1,weight_corr*weight_btag_2b);
                hist_mt_t2_2b_OS->Fill(mt_tau2,weight_corr*weight_btag_2b);
                hist_mt_b1_2b_OS->Fill(mt_b1,weight_corr*weight_btag_2b);
                hist_normzeta_2b_OS->Fill(norm_zeta,weight_corr*weight_btag_2b);
                hist_dzeta_2b_OS->Fill(dzeta,weight_corr*weight_btag_2b);
                hist_pt_b1_2b_OS->Fill(myb1.Pt(),weight_corr*weight_btag_2b);
                hist_met_2b_OS->Fill(met,weight_corr*weight_btag_2b);
                hist_njets_2b_OS->Fill(njets,weight_corr*weight_btag_2b);
                hist_m_b2tt_2b_OS->Fill(m_b2tt,weight_corr*weight_btag_2b);
                hist_m_bbt1_2b_OS->Fill(m_bbt1,weight_corr*weight_btag_2b);
                hist_m_bbt2_2b_OS->Fill(m_bbt2,weight_corr*weight_btag_2b);
                hist_m_bbtt_2b_OS->Fill(m_bbtt,weight_corr*weight_btag_2b);
                hist_m_bb_2b_OS->Fill(m_bb,weight_corr*weight_btag_2b);
                hist_m_b2t1_2b_OS->Fill(m_b2t1,weight_corr*weight_btag_2b);
                hist_m_b2t2_2b_OS->Fill(m_b2t2,weight_corr*weight_btag_2b);
                hist_dr_b2t1_2b_OS->Fill(dr_b2t1,weight_corr*weight_btag_2b);
                hist_dr_b2t2_2b_OS->Fill(dr_b2t2,weight_corr*weight_btag_2b);
                hist_dr_bb_2b_OS->Fill(dr_bb,weight_corr*weight_btag_2b);
                hist_dr_b2tt_2b_OS->Fill(dr_b2tt,weight_corr*weight_btag_2b);
                hist_dr_bbtt_2b_OS->Fill(dr_bbtt,weight_corr*weight_btag_2b);
                hist_dr_bbt1_2b_OS->Fill(dr_bbt1,weight_corr*weight_btag_2b);
                hist_dr_bbt2_2b_OS->Fill(dr_bbt2,weight_corr*weight_btag_2b);
                hist_mt_b2_2b_OS->Fill(mt_b2,weight_corr*weight_btag_2b);
                hist_pt_b2_2b_OS->Fill(myb2.Pt(),weight_corr*weight_btag_2b);
                hist_dma_2b_OS->Fill(dma,weight_corr*weight_btag_2b);
            }
        }
        
        //for qcd background
        if (byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2){
            //fake rates
            float fr = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dm0M,g_taufr_dm1M,g_taufr_dm10M,g_taufr_dm11M,0);
            //calculated with bjet
            float fr_bjet = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,0);
            float weight_qcd_0b = fr/(1-fr);
            float weight_qcd_bjet = fr_bjet/(1-fr_bjet);
            if (trigger2027 or trigger2027HPS){
                weight_qcd_0b *= 1.5;
                weight_qcd_bjet *= 1.5;
            }
            //for 0b cat
            float weight_corr_0b = weight_corr * weight_qcd_0b;
            //for nonzero b cat
            float weight_corr_bjet = weight_corr * weight_qcd_bjet;
            
            
            weight_corr = weight_corr_bjet;
            
            //fill 1b
            if (nbtag20==1){
                hist_pt_t1_1b_SS->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_pt_t2_1b_SS->Fill(pt_2,weight_corr*weight_btag_1b);
                hist_m_btt_1b_SS->Fill(m_b1tt,weight_corr*weight_btag_1b);
                hist_m_bt1_1b_SS->Fill(m_b1t1,weight_corr*weight_btag_1b);
                hist_m_bt2_1b_SS->Fill(m_b1t2,weight_corr*weight_btag_1b);
                hist_dr_tt_1b_SS->Fill(dr_tt,weight_corr*weight_btag_1b);
                hist_dr_bt1_1b_SS->Fill(dr_b1t1,weight_corr*weight_btag_1b);
                hist_dr_bt2_1b_SS->Fill(dr_b1t2,weight_corr*weight_btag_1b);
                hist_dr_btt_1b_SS->Fill(dr_b1tt,weight_corr*weight_btag_1b);
                hist_pt_tt_1b_SS->Fill(mytt.Pt(),weight_corr*weight_btag_1b);
                hist_eta_tt_1b_SS->Fill(mytt.Eta(),weight_corr*weight_btag_1b);
                hist_mt_t1_1b_SS->Fill(mt_tau1,weight_corr*weight_btag_1b);
                hist_mt_t2_1b_SS->Fill(mt_tau2,weight_corr*weight_btag_1b);
                hist_mt_b_1b_SS->Fill(mt_b1,weight_corr*weight_btag_1b);
                hist_normzeta_1b_SS->Fill(norm_zeta,weight_corr*weight_btag_1b);
                hist_dzeta_1b_SS->Fill(dzeta,weight_corr*weight_btag_1b);
                hist_pt_b_1b_SS->Fill(myb1.Pt(),weight_corr*weight_btag_1b);
                hist_met_1b_SS->Fill(met,weight_corr*weight_btag_1b);
                hist_njets_1b_SS->Fill(njets,weight_corr*weight_btag_1b);
            }
            //fill 2b
            if (nbtag20==2){
                hist_pt_t1_2b_SS->Fill(pt_1,weight_corr*weight_btag_2b);
                hist_pt_t2_2b_SS->Fill(pt_2,weight_corr*weight_btag_2b);
                hist_m_b1tt_2b_SS->Fill(m_b1tt,weight_corr*weight_btag_2b);
                hist_m_b1t1_2b_SS->Fill(m_b1t1,weight_corr*weight_btag_2b);
                hist_m_b1t2_2b_SS->Fill(m_b1t2,weight_corr*weight_btag_2b);
                hist_dr_tt_2b_SS->Fill(dr_tt,weight_corr*weight_btag_2b);
                hist_dr_b1t1_2b_SS->Fill(dr_b1t1,weight_corr*weight_btag_2b);
                hist_dr_b1t2_2b_SS->Fill(dr_b1t2,weight_corr*weight_btag_2b);
                hist_dr_b1tt_2b_SS->Fill(dr_b1tt,weight_corr*weight_btag_2b);
                hist_pt_tt_2b_SS->Fill(mytt.Pt(),weight_corr*weight_btag_2b);
                hist_eta_tt_2b_SS->Fill(mytt.Eta(),weight_corr*weight_btag_2b);
                hist_mt_t1_2b_SS->Fill(mt_tau1,weight_corr*weight_btag_2b);
                hist_mt_t2_2b_SS->Fill(mt_tau2,weight_corr*weight_btag_2b);
                hist_mt_b1_2b_SS->Fill(mt_b1,weight_corr*weight_btag_2b);
                hist_normzeta_2b_SS->Fill(norm_zeta,weight_corr*weight_btag_2b);
                hist_dzeta_2b_SS->Fill(dzeta,weight_corr*weight_btag_2b);
                hist_pt_b1_2b_SS->Fill(myb1.Pt(),weight_corr*weight_btag_2b);
                hist_met_2b_SS->Fill(met,weight_corr*weight_btag_2b);
                hist_njets_2b_SS->Fill(njets,weight_corr*weight_btag_2b);
                hist_m_b2tt_2b_SS->Fill(m_b2tt,weight_corr*weight_btag_2b);
                hist_m_bbt1_2b_SS->Fill(m_bbt1,weight_corr*weight_btag_2b);
                hist_m_bbt2_2b_SS->Fill(m_bbt2,weight_corr*weight_btag_2b);
                hist_m_bbtt_2b_SS->Fill(m_bbtt,weight_corr*weight_btag_2b);
                hist_m_bb_2b_SS->Fill(m_bb,weight_corr*weight_btag_2b);
                hist_m_b2t1_2b_SS->Fill(m_b2t1,weight_corr*weight_btag_2b);
                hist_m_b2t2_2b_SS->Fill(m_b2t2,weight_corr*weight_btag_2b);
                hist_dr_b2t1_2b_SS->Fill(dr_b2t1,weight_corr*weight_btag_2b);
                hist_dr_b2t2_2b_SS->Fill(dr_b2t2,weight_corr*weight_btag_2b);
                hist_dr_bb_2b_SS->Fill(dr_bb,weight_corr*weight_btag_2b);
                hist_dr_b2tt_2b_SS->Fill(dr_b2tt,weight_corr*weight_btag_2b);
                hist_dr_bbtt_2b_SS->Fill(dr_bbtt,weight_corr*weight_btag_2b);
                hist_dr_bbt1_2b_SS->Fill(dr_bbt1,weight_corr*weight_btag_2b);
                hist_dr_bbt2_2b_SS->Fill(dr_bbt2,weight_corr*weight_btag_2b);
                hist_mt_b2_2b_SS->Fill(mt_b2,weight_corr*weight_btag_2b);
                hist_pt_b2_2b_SS->Fill(myb2.Pt(),weight_corr*weight_btag_2b);
                hist_dma_2b_SS->Fill(dma,weight_corr*weight_btag_2b);
            }
        }
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    
    TDirectory * t1 = fout->mkdir("pt_t1_1b");
    TDirectory * t2 = fout->mkdir("pt_t2_1b");
    TDirectory * t3 = fout->mkdir("m_btt_1b");
    TDirectory * t4 = fout->mkdir("m_bt1_1b");
    TDirectory * t5 = fout->mkdir("m_bt2_1b");
    TDirectory * t6 = fout->mkdir("dr_tt_1b");
    TDirectory * t7 = fout->mkdir("dr_bt1_1b");
    TDirectory * t8 = fout->mkdir("dr_bt2_1b");
    TDirectory * t9 = fout->mkdir("dr_btt_1b");
    TDirectory * t10 = fout->mkdir("pt_tt_1b");
    TDirectory * t11 = fout->mkdir("eta_tt_1b");
    TDirectory * t12 = fout->mkdir("mt_t1_1b");
    TDirectory * t13 = fout->mkdir("mt_t2_1b");
    TDirectory * t14 = fout->mkdir("mt_b_1b");
    TDirectory * t15 = fout->mkdir("normzeta_1b");
    TDirectory * t16 = fout->mkdir("dzeta_1b");
    TDirectory * t17 = fout->mkdir("pt_b_1b");
    TDirectory * t18 = fout->mkdir("met_1b");
    TDirectory * t19 = fout->mkdir("njets_1b");
    
    TDirectory * tt1 = fout->mkdir("pt_t1_2b");
    TDirectory * tt2 = fout->mkdir("pt_t2_2b");
    TDirectory * tt3 = fout->mkdir("m_b1tt_2b");
    TDirectory * tt4 = fout->mkdir("m_b1t1_2b");
    TDirectory * tt5 = fout->mkdir("m_b1t2_2b");
    TDirectory * tt6 = fout->mkdir("dr_tt_2b");
    TDirectory * tt7 = fout->mkdir("dr_b1t1_2b");
    TDirectory * tt8 = fout->mkdir("dr_b1t2_2b");
    TDirectory * tt9 = fout->mkdir("dr_b1tt_2b");
    TDirectory * tt10 = fout->mkdir("pt_tt_2b");
    TDirectory * tt11 = fout->mkdir("eta_tt_2b");
    TDirectory * tt12 = fout->mkdir("mt_t1_2b");
    TDirectory * tt13 = fout->mkdir("mt_t2_2b");
    TDirectory * tt14 = fout->mkdir("mt_b1_2b");
    TDirectory * tt15 = fout->mkdir("normzeta_2b");
    TDirectory * tt16 = fout->mkdir("dzeta_2b");
    TDirectory * tt17 = fout->mkdir("pt_b1_2b");
    TDirectory * tt18 = fout->mkdir("met_2b");
    TDirectory * tt19 = fout->mkdir("njets_2b");
    TDirectory * tt20 = fout->mkdir("m_b2tt_2b");
    TDirectory * tt21 = fout->mkdir("m_bbt1_2b");
    TDirectory * tt22 = fout->mkdir("m_bbt2_2b");
    TDirectory * tt23 = fout->mkdir("m_bbtt_2b");
    TDirectory * tt24 = fout->mkdir("m_bb_2b");
    TDirectory * tt25 = fout->mkdir("m_b2t1_2b");
    TDirectory * tt26 = fout->mkdir("m_b2t2_2b");
    TDirectory * tt27 = fout->mkdir("dr_b2t1_2b");
    TDirectory * tt28 = fout->mkdir("dr_b2t2_2b");
    TDirectory * tt29 = fout->mkdir("dr_bb_2b");
    TDirectory * tt30 = fout->mkdir("dr_b2tt_2b");
    TDirectory * tt31 = fout->mkdir("dr_bbtt_2b");
    TDirectory * tt32 = fout->mkdir("dr_bbt1_2b");
    TDirectory * tt33 = fout->mkdir("dr_bbt2_2b");
    TDirectory * tt34 = fout->mkdir("mt_b2_2b");
    TDirectory * tt35 = fout->mkdir("pt_b2_2b");
    TDirectory * tt36 = fout->mkdir("dma_2b");
    
    
    TString SS="_SS";
    
    t1->cd();
    hist_pt_t1_1b_OS->SetName(name.c_str());
    hist_pt_t1_1b_OS->Write();
    hist_pt_t1_1b_SS->SetName(name.c_str()+SS);
    hist_pt_t1_1b_SS->Write();
    
    t2->cd();
    hist_pt_t2_1b_OS->SetName(name.c_str());
    hist_pt_t2_1b_OS->Write();
    hist_pt_t2_1b_SS->SetName(name.c_str()+SS);
    hist_pt_t2_1b_SS->Write();
    
    t3->cd();
    hist_m_btt_1b_OS->SetName(name.c_str());
    hist_m_btt_1b_OS->Write();
    hist_m_btt_1b_SS->SetName(name.c_str()+SS);
    hist_m_btt_1b_SS->Write();
    
    t4->cd();
    hist_m_bt1_1b_OS->SetName(name.c_str());
    hist_m_bt1_1b_OS->Write();
    hist_m_bt1_1b_SS->SetName(name.c_str()+SS);
    hist_m_bt1_1b_SS->Write();
    
    t5->cd();
    hist_m_bt2_1b_OS->SetName(name.c_str());
    hist_m_bt2_1b_OS->Write();
    hist_m_bt2_1b_SS->SetName(name.c_str()+SS);
    hist_m_bt2_1b_SS->Write();
    
    t6->cd();
    hist_dr_tt_1b_OS->SetName(name.c_str());
    hist_dr_tt_1b_OS->Write();
    hist_dr_tt_1b_SS->SetName(name.c_str()+SS);
    hist_dr_tt_1b_SS->Write();
    
    t7->cd();
    hist_dr_bt1_1b_OS->SetName(name.c_str());
    hist_dr_bt1_1b_OS->Write();
    hist_dr_bt1_1b_SS->SetName(name.c_str()+SS);
    hist_dr_bt1_1b_SS->Write();
    
    t8->cd();
    hist_dr_bt2_1b_OS->SetName(name.c_str());
    hist_dr_bt2_1b_OS->Write();
    hist_dr_bt2_1b_SS->SetName(name.c_str()+SS);
    hist_dr_bt2_1b_SS->Write();
    
    t9->cd();
    hist_dr_btt_1b_OS->SetName(name.c_str());
    hist_dr_btt_1b_OS->Write();
    hist_dr_btt_1b_SS->SetName(name.c_str()+SS);
    hist_dr_btt_1b_SS->Write();
    
    t10->cd();
    hist_pt_tt_1b_OS->SetName(name.c_str());
    hist_pt_tt_1b_OS->Write();
    hist_pt_tt_1b_SS->SetName(name.c_str()+SS);
    hist_pt_tt_1b_SS->Write();
    
    t11->cd();
    hist_eta_tt_1b_OS->SetName(name.c_str());
    hist_eta_tt_1b_OS->Write();
    hist_eta_tt_1b_SS->SetName(name.c_str()+SS);
    hist_eta_tt_1b_SS->Write();
    
    t12->cd();
    hist_mt_t1_1b_OS->SetName(name.c_str());
    hist_mt_t1_1b_OS->Write();
    hist_mt_t1_1b_SS->SetName(name.c_str()+SS);
    hist_mt_t1_1b_SS->Write();
    
    t13->cd();
    hist_mt_t2_1b_OS->SetName(name.c_str());
    hist_mt_t2_1b_OS->Write();
    hist_mt_t2_1b_SS->SetName(name.c_str()+SS);
    hist_mt_t2_1b_SS->Write();
    
    t14->cd();
    hist_mt_b_1b_OS->SetName(name.c_str());
    hist_mt_b_1b_OS->Write();
    hist_mt_b_1b_SS->SetName(name.c_str()+SS);
    hist_mt_b_1b_SS->Write();
    
    t15->cd();
    hist_normzeta_1b_OS->SetName(name.c_str());
    hist_normzeta_1b_OS->Write();
    hist_normzeta_1b_SS->SetName(name.c_str()+SS);
    hist_normzeta_1b_SS->Write();
    
    t16->cd();
    hist_dzeta_1b_OS->SetName(name.c_str());
    hist_dzeta_1b_OS->Write();
    hist_dzeta_1b_SS->SetName(name.c_str()+SS);
    hist_dzeta_1b_SS->Write();
    
    t17->cd();
    hist_pt_b_1b_OS->SetName(name.c_str());
    hist_pt_b_1b_OS->Write();
    hist_pt_b_1b_SS->SetName(name.c_str()+SS);
    hist_pt_b_1b_SS->Write();
    
    t18->cd();
    hist_met_1b_OS->SetName(name.c_str());
    hist_met_1b_OS->Write();
    hist_met_1b_SS->SetName(name.c_str()+SS);
    hist_met_1b_SS->Write();
    
    t19->cd();
    hist_njets_1b_OS->SetName(name.c_str());
    hist_njets_1b_OS->Write();
    hist_njets_1b_SS->SetName(name.c_str()+SS);
    hist_njets_1b_SS->Write();
    
    //2b
    
    tt1->cd();
    hist_pt_t1_2b_OS->SetName(name.c_str());
    hist_pt_t1_2b_OS->Write();
    hist_pt_t1_2b_SS->SetName(name.c_str()+SS);
    hist_pt_t1_2b_SS->Write();
    
    tt2->cd();
    hist_pt_t2_2b_OS->SetName(name.c_str());
    hist_pt_t2_2b_OS->Write();
    hist_pt_t2_2b_SS->SetName(name.c_str()+SS);
    hist_pt_t2_2b_SS->Write();
    
    tt3->cd();
    hist_m_b1tt_2b_OS->SetName(name.c_str());
    hist_m_b1tt_2b_OS->Write();
    hist_m_b1tt_2b_SS->SetName(name.c_str()+SS);
    hist_m_b1tt_2b_SS->Write();
    
    tt4->cd();
    hist_m_b1t1_2b_OS->SetName(name.c_str());
    hist_m_b1t1_2b_OS->Write();
    hist_m_b1t1_2b_SS->SetName(name.c_str()+SS);
    hist_m_b1t1_2b_SS->Write();
    
    tt5->cd();
    hist_m_b1t2_2b_OS->SetName(name.c_str());
    hist_m_b1t2_2b_OS->Write();
    hist_m_b1t2_2b_SS->SetName(name.c_str()+SS);
    hist_m_b1t2_2b_SS->Write();
    
    tt6->cd();
    hist_dr_tt_2b_OS->SetName(name.c_str());
    hist_dr_tt_2b_OS->Write();
    hist_dr_tt_2b_SS->SetName(name.c_str()+SS);
    hist_dr_tt_2b_SS->Write();
    
    tt7->cd();
    hist_dr_b1t1_2b_OS->SetName(name.c_str());
    hist_dr_b1t1_2b_OS->Write();
    hist_dr_b1t1_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b1t1_2b_SS->Write();
    
    tt8->cd();
    hist_dr_b1t2_2b_OS->SetName(name.c_str());
    hist_dr_b1t2_2b_OS->Write();
    hist_dr_b1t2_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b1t2_2b_SS->Write();
    
    tt9->cd();
    hist_dr_b1tt_2b_OS->SetName(name.c_str());
    hist_dr_b1tt_2b_OS->Write();
    hist_dr_b1tt_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b1tt_2b_SS->Write();
    
    tt10->cd();
    hist_pt_tt_2b_OS->SetName(name.c_str());
    hist_pt_tt_2b_OS->Write();
    hist_pt_tt_2b_SS->SetName(name.c_str()+SS);
    hist_pt_tt_2b_SS->Write();
    
    tt11->cd();
    hist_eta_tt_2b_OS->SetName(name.c_str());
    hist_eta_tt_2b_OS->Write();
    hist_eta_tt_2b_SS->SetName(name.c_str()+SS);
    hist_eta_tt_2b_SS->Write();
    
    tt12->cd();
    hist_mt_t1_2b_OS->SetName(name.c_str());
    hist_mt_t1_2b_OS->Write();
    hist_mt_t1_2b_SS->SetName(name.c_str()+SS);
    hist_mt_t1_2b_SS->Write();
    
    tt13->cd();
    hist_mt_t2_2b_OS->SetName(name.c_str());
    hist_mt_t2_2b_OS->Write();
    hist_mt_t2_2b_SS->SetName(name.c_str()+SS);
    hist_mt_t2_2b_SS->Write();
    
    tt14->cd();
    hist_mt_b1_2b_OS->SetName(name.c_str());
    hist_mt_b1_2b_OS->Write();
    hist_mt_b1_2b_SS->SetName(name.c_str()+SS);
    hist_mt_b1_2b_SS->Write();
    
    tt15->cd();
    hist_normzeta_2b_OS->SetName(name.c_str());
    hist_normzeta_2b_OS->Write();
    hist_normzeta_2b_SS->SetName(name.c_str()+SS);
    hist_normzeta_2b_SS->Write();
    
    tt16->cd();
    hist_dzeta_2b_OS->SetName(name.c_str());
    hist_dzeta_2b_OS->Write();
    hist_dzeta_2b_SS->SetName(name.c_str()+SS);
    hist_dzeta_2b_SS->Write();
    
    tt17->cd();
    hist_pt_b1_2b_OS->SetName(name.c_str());
    hist_pt_b1_2b_OS->Write();
    hist_pt_b1_2b_SS->SetName(name.c_str()+SS);
    hist_pt_b1_2b_SS->Write();
    
    tt18->cd();
    hist_met_2b_OS->SetName(name.c_str());
    hist_met_2b_OS->Write();
    hist_met_2b_SS->SetName(name.c_str()+SS);
    hist_met_2b_SS->Write();
    
    tt19->cd();
    hist_njets_2b_OS->SetName(name.c_str());
    hist_njets_2b_OS->Write();
    hist_njets_2b_SS->SetName(name.c_str()+SS);
    hist_njets_2b_SS->Write();
    
    tt20->cd();
    hist_m_b2tt_2b_OS->SetName(name.c_str());
    hist_m_b2tt_2b_OS->Write();
    hist_m_b2tt_2b_SS->SetName(name.c_str()+SS);
    hist_m_b2tt_2b_SS->Write();
    
    tt21->cd();
    hist_m_bbt1_2b_OS->SetName(name.c_str());
    hist_m_bbt1_2b_OS->Write();
    hist_m_bbt1_2b_SS->SetName(name.c_str()+SS);
    hist_m_bbt1_2b_SS->Write();
    
    tt22->cd();
    hist_m_bbt2_2b_OS->SetName(name.c_str());
    hist_m_bbt2_2b_OS->Write();
    hist_m_bbt2_2b_SS->SetName(name.c_str()+SS);
    hist_m_bbt2_2b_SS->Write();
    
    tt23->cd();
    hist_m_bbtt_2b_OS->SetName(name.c_str());
    hist_m_bbtt_2b_OS->Write();
    hist_m_bbtt_2b_SS->SetName(name.c_str()+SS);
    hist_m_bbtt_2b_SS->Write();
    
    tt24->cd();
    hist_m_bb_2b_OS->SetName(name.c_str());
    hist_m_bb_2b_OS->Write();
    hist_m_bb_2b_SS->SetName(name.c_str()+SS);
    hist_m_bb_2b_SS->Write();
    
    tt25->cd();
    hist_m_b2t1_2b_OS->SetName(name.c_str());
    hist_m_b2t1_2b_OS->Write();
    hist_m_b2t1_2b_SS->SetName(name.c_str()+SS);
    hist_m_b2t1_2b_SS->Write();
    
    tt26->cd();
    hist_m_b2t2_2b_OS->SetName(name.c_str());
    hist_m_b2t2_2b_OS->Write();
    hist_m_b2t2_2b_SS->SetName(name.c_str()+SS);
    hist_m_b2t2_2b_SS->Write();
    
    tt27->cd();
    hist_dr_b2t1_2b_OS->SetName(name.c_str());
    hist_dr_b2t1_2b_OS->Write();
    hist_dr_b2t1_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b2t1_2b_SS->Write();
    
    tt28->cd();
    hist_dr_b2t2_2b_OS->SetName(name.c_str());
    hist_dr_b2t2_2b_OS->Write();
    hist_dr_b2t2_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b2t2_2b_SS->Write();
    
    tt29->cd();
    hist_dr_bb_2b_OS->SetName(name.c_str());
    hist_dr_bb_2b_OS->Write();
    hist_dr_bb_2b_SS->SetName(name.c_str()+SS);
    hist_dr_bb_2b_SS->Write();
    
    tt30->cd();
    hist_dr_b2tt_2b_OS->SetName(name.c_str());
    hist_dr_b2tt_2b_OS->Write();
    hist_dr_b2tt_2b_SS->SetName(name.c_str()+SS);
    hist_dr_b2tt_2b_SS->Write();
    
    tt31->cd();
    hist_dr_bbtt_2b_OS->SetName(name.c_str());
    hist_dr_bbtt_2b_OS->Write();
    hist_dr_bbtt_2b_SS->SetName(name.c_str()+SS);
    hist_dr_bbtt_2b_SS->Write();
    
    tt32->cd();
    hist_dr_bbt1_2b_OS->SetName(name.c_str());
    hist_dr_bbt1_2b_OS->Write();
    hist_dr_bbt1_2b_SS->SetName(name.c_str()+SS);
    hist_dr_bbt1_2b_SS->Write();
    
    tt33->cd();
    hist_dr_bbt2_2b_OS->SetName(name.c_str());
    hist_dr_bbt2_2b_OS->Write();
    hist_dr_bbt2_2b_SS->SetName(name.c_str()+SS);
    hist_dr_bbt2_2b_SS->Write();
    
    tt34->cd();
    hist_mt_b2_2b_OS->SetName(name.c_str());
    hist_mt_b2_2b_OS->Write();
    hist_mt_b2_2b_SS->SetName(name.c_str()+SS);
    hist_mt_b2_2b_SS->Write();
    
    tt35->cd();
    hist_pt_b2_2b_OS->SetName(name.c_str());
    hist_pt_b2_2b_OS->Write();
    hist_pt_b2_2b_SS->SetName(name.c_str()+SS);
    hist_pt_b2_2b_SS->Write();
    
    tt36->cd();
    hist_dma_2b_OS->SetName(name.c_str());
    hist_dma_2b_OS->Write();
    hist_dma_2b_SS->SetName(name.c_str()+SS);
    hist_dma_2b_SS->Write();
    
    
    
    fout->Close();
    
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}



