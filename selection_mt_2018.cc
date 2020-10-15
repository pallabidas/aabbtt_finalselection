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
    
    //sample weights
    float xs, weight, luminosity = 59740.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt12"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt12"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt20"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt30"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt40"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt50"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "VBFbbtt60"){xs = 0.01*3.782; weight = luminosity*xs/N;}
    else if(sample == "embedded"){weight = 1.0;}
    else if(sample == "DY"){weight = 1.0;}
    else if(sample == "DY1"){weight = 1.0;}
    else if(sample == "DY2"){weight = 1.0;}
    else if(sample == "DY3"){weight = 1.0;}
    else if(sample == "DY4"){weight = 1.0;}
    else if(sample == "GGHTT"){xs = 48.58*0.0627; weight = luminosity*xs/N;}
    else if(sample == "GGZHLLTT"){xs = 0.1227*0.0627*3*0.033658; weight = luminosity*xs/N;}
    else if(sample == "GGZHNNTT"){xs = 0.1227*0.0627*0.2000; weight = luminosity*xs/N;}
    else if(sample == "GGZHQQTT"){xs = 0.1227*0.0627*0.6991; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_antitop"){xs = 35.85; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.85; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 80.94; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 136.02; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 13.84; weight = luminosity*xs/N;}//11.95
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.52; weight = luminosity*xs/N;}//5.595
    else if(sample == "WZ3LNu"){xs = 4.43; weight = luminosity*xs/N;}//4.708
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.38; weight = luminosity*xs/N;}//3.22
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
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
    TH1F * hist_m_bb = new TH1F("", "", 30, 0., 300.);
    TH1F * hist_m_bb_qcd = new TH1F("", "", 30, 0., 300.);
    TH1F * hist_m_mtb = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_m_mtb_qcd = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_m_mtbb = new TH1F("", "", 50, 0., 500.);
    TH1F * hist_m_mtbb_qcd = new TH1F("", "", 50, 0., 500.);
    TH1F * hist_pt_m = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_m_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1 = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_eta_m = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_eta_m_qcd = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_eta_t = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_eta_t_qcd = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_eta_b1 = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_eta_b1_qcd = new TH1F("", "", 24, -2.4, 2.4);
    TH1F * hist_iso_m = new TH1F("", "", 15, 0., 0.15);
    TH1F * hist_iso_m_qcd = new TH1F("", "", 15, 0., 0.15);

    TH1F * hist_met = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_met_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_mjj = new TH1F("", "", 40, 0., 800.);
    TH1F * hist_mjj_qcd = new TH1F("", "", 40, 0., 800.);
    
    TH1F * hist_mt_mumet = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_mt_mumet_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_mt_taumet = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_mt_taumet_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_dz = new TH1F("", "", 30, -150., 150.);
    TH1F * hist_dz_qcd = new TH1F("", "", 30, -150., 150.);
    
    TH1F * hist_m_mt_VBF = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_VBF_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mtb_VBF = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_m_mtb_VBF_qcd = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_pt_m_VBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_m_VBF_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t_VBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t_VBF_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1_VBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1_VBF_qcd = new TH1F("", "", 15, 0., 150.);
    
    TH1F * hist_m_mt_nonVBF = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mt_nonVBF_qcd = new TH1F("", "", 25, 0., 250.);
    TH1F * hist_m_mtb_nonVBF = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_m_mtb_nonVBF_qcd = new TH1F("", "", 45, 0., 450.);
    TH1F * hist_pt_m_nonVBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_m_nonVBF_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t_nonVBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_t_nonVBF_qcd = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1_nonVBF = new TH1F("", "", 15, 0., 150.);
    TH1F * hist_pt_b1_nonVBF_qcd = new TH1F("", "", 15, 0., 150.);
    
    
    //declare workspace for scale factors
    TFile fwmc("htt_scalefactors_legacy_2018.root");
    RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
    fwmc.Close();
    
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
        bool trigger24OR27 = ((passMu24 && matchMu24_1 && filterMu24_1 && pt_1>25) or (passMu27 && matchMu27_1 && filterMu27_1 && pt_1>25));
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
            if (sample!="gghbbtt12" && sample!="gghbbtt20" && sample!="gghbbtt30" && sample!="gghbbtt40" && sample!="gghbbtt50" && sample!="gghbbtt60" && sample!="VBFbbtt12" && sample!="VBFbbtt20" && sample!="VBFbbtt30" && sample!="VBFbbtt40" && sample!="VBFbbtt50" && sample!="VBFbbtt60" && name!="HTT"){
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
            }
            else{
                float trg_sf=wmc->function("t_trg_pog_deeptau_medium_mutau_ratio")->getVal();
                sf_MC *= wmc->function("m_trg_20_ratio")->getVal()*trg_sf;
            }
            
            //muon ID/iso/tracking scale factors
            sf_MC *= wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_ratio")->getVal();
            
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
            
            if (gen_match_2==6) continue;
            
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
            }
            else{
                float trg_sf=wmc->function("t_trg_mediumDeepTau_mutau_embed_ratio")->getVal();
                sf_MC *= wmc->function("m_trg_20_ic_embed_ratio")->getVal()*trg_sf;
            }//t_trg_pog_deeptau_medium_mutau_ratio
            
            //muon ID/iso/tracking scale factors
            sf_embed *= wmc->function("m_trk_ratio")->getVal()*wmc->function("m_idiso_ic_embed_ratio")->getVal();
            
            //efficiency of selecting Z->mumu data
            wmc->var("gt1_pt")->setVal(genpt_1);
            wmc->var("gt2_pt")->setVal(pt_2);
            wmc->var("gt1_eta")->setVal(geneta_1);
            wmc->var("gt2_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_trg_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(genpt_1);
            wmc->var("gt_eta")->setVal(geneta_1);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            wmc->var("gt_pt")->setVal(pt_2);
            wmc->var("gt_eta")->setVal(eta_2);
            sf_embed *= wmc->function("m_sel_id_ic_ratio")->getVal();
            
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
        float m_bb = (myb1 + myb2).M();
        
        //jet faking tau_h (to be failed in qcd)
        if (byMediumDeepVSjet_2){
            //at least 1 b
            if(nbtag20==1 or nbtag20==2){
                hist_m_mt->Fill(m_mt,weight_corr*weight_btag_atleast1b);
                hist_m_mtb->Fill(m_mtb,weight_corr*weight_btag_atleast1b);
                if(nbtag20==2){
                    hist_m_bb->Fill(m_bb,weight_corr*weight_btag_atleast1b);
                    hist_m_mtbb->Fill(m_mtbb,weight_corr*weight_btag_atleast1b);
                }
                hist_pt_m->Fill(pt_1,weight_corr*weight_btag_atleast1b);
                hist_pt_t->Fill(pt_2,weight_corr*weight_btag_atleast1b);
                hist_pt_b1->Fill(bpt_deepcsv_1,weight_corr*weight_btag_atleast1b);
                hist_eta_m->Fill(eta_1,weight_corr*weight_btag_atleast1b);
                hist_eta_t->Fill(eta_2,weight_corr*weight_btag_atleast1b);
                hist_eta_b1->Fill(beta_deepcsv_1,weight_corr*weight_btag_atleast1b);
                hist_iso_m->Fill(iso_1,weight_corr*weight_btag_atleast1b);

                hist_met->Fill(met,weight_corr*weight_btag_atleast1b);
                hist_mjj->Fill(mjj,weight_corr*weight_btag_atleast1b);
                hist_mt_mumet->Fill(mt_mumet,weight_corr*weight_btag_atleast1b);
                hist_mt_taumet->Fill(mt_taumet,weight_corr*weight_btag_atleast1b);
                hist_dz->Fill(dzeta,weight_corr*weight_btag_atleast1b);
            }
            //vbf
            if(nbtag20==1 && mjj>500){
                hist_m_mt_VBF->Fill(m_mt,weight_corr*weight_btag_1b);
                hist_m_mtb_VBF->Fill(m_mtb,weight_corr*weight_btag_1b);
                hist_pt_m_VBF->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_pt_t_VBF->Fill(pt_2,weight_corr*weight_btag_1b);
                hist_pt_b1_VBF->Fill(bpt_deepcsv_1,weight_corr*weight_btag_1b);
            }
            //nonvbf
            if(nbtag20==1 && mjj<500){
                hist_m_mt_nonVBF->Fill(m_mt,weight_corr*weight_btag_1b);
                hist_m_mtb_nonVBF->Fill(m_mtb,weight_corr*weight_btag_1b);
                hist_pt_m_nonVBF->Fill(pt_1,weight_corr*weight_btag_1b);
                hist_pt_t_nonVBF->Fill(pt_2,weight_corr*weight_btag_1b);
                hist_pt_b1_nonVBF->Fill(bpt_deepcsv_1,weight_corr*weight_btag_1b);
            }
        }
        
        //for qcd background
        if (byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2){
            //fake rates
            float fr = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dm0M,g_taufr_dm1M,g_taufr_dm10M,g_taufr_dm11M,0);
            float fr_jet = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,0);
            float weight_qcd = fr/(1-fr);
            float weight_qcd_jet = fr_jet/(1-fr_jet);
            
            if (trigger2027 or trigger2027HPS){
                weight_qcd *= 1.5;
                weight_qcd_jet *= 1.5;
            }
            
            //at least 1 b
            if(nbtag20==1 or nbtag20==2){
                hist_m_mt_qcd->Fill(m_mt,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_m_mtb_qcd->Fill(m_mtb,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                if(nbtag20==2){
                    hist_m_bb_qcd->Fill(m_bb,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                    hist_m_mtbb_qcd->Fill(m_mtbb,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                }
                hist_pt_m_qcd->Fill(pt_1,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_pt_t_qcd->Fill(pt_2,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_pt_b1_qcd->Fill(bpt_deepcsv_1,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_eta_m_qcd->Fill(eta_1,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_eta_t_qcd->Fill(eta_2,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_eta_b1_qcd->Fill(beta_deepcsv_1,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_iso_m_qcd->Fill(iso_1,weight_corr*weight_btag_atleast1b*weight_qcd_jet);

                hist_met_qcd->Fill(met,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_mjj_qcd->Fill(mjj,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_mt_mumet_qcd->Fill(mt_mumet,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_mt_taumet_qcd->Fill(mt_taumet,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
                hist_dz_qcd->Fill(dzeta,weight_corr*weight_btag_atleast1b*weight_qcd_jet);
            }
            //vbf
            if(nbtag20==1 && mjj>500){
                hist_m_mt_VBF_qcd->Fill(m_mt,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_m_mtb_VBF_qcd->Fill(m_mtb,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_m_VBF_qcd->Fill(pt_1,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_t_VBF_qcd->Fill(pt_2,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_b1_VBF_qcd->Fill(bpt_deepcsv_1,weight_corr*weight_btag_1b*weight_qcd_jet);
            }
            //nonvbf
            if(nbtag20==1 && mjj<500){
                hist_m_mt_nonVBF_qcd->Fill(m_mt,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_m_mtb_nonVBF_qcd->Fill(m_mtb,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_m_nonVBF_qcd->Fill(pt_1,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_t_nonVBF_qcd->Fill(pt_2,weight_corr*weight_btag_1b*weight_qcd_jet);
                hist_pt_b1_nonVBF_qcd->Fill(bpt_deepcsv_1,weight_corr*weight_btag_1b*weight_qcd_jet);
            }
        }
    }
    
    TFile * fout = TFile::Open(output.c_str(), "RECREATE");
    TDirectory * td1 = fout->mkdir("m_mt");
    TDirectory * td2 = fout->mkdir("m_bb");
    TDirectory * td3 = fout->mkdir("m_mtb");
    TDirectory * td4 = fout->mkdir("m_mtbb");
    TDirectory * td5 = fout->mkdir("pt_m");
    TDirectory * td6 = fout->mkdir("pt_t");
    TDirectory * td7 = fout->mkdir("pt_b1");
    TDirectory * td8 = fout->mkdir("eta_m");
    TDirectory * td9 = fout->mkdir("eta_t");
    TDirectory * td10 = fout->mkdir("eta_b1");
    TDirectory * td11 = fout->mkdir("iso_m");

    TDirectory * td13 = fout->mkdir("met");
    TDirectory * td14 = fout->mkdir("mjj");
    TDirectory * td15 = fout->mkdir("mt_mtmet");
    TDirectory * td16 = fout->mkdir("mt_taumet");
    TDirectory * td17 = fout->mkdir("dz");
    TDirectory * td18 = fout->mkdir("m_mt_VBF");
    TDirectory * td19 = fout->mkdir("m_mtb_VBF");
    TDirectory * td20 = fout->mkdir("pt_m_VBF");
    TDirectory * td21 = fout->mkdir("pt_t_VBF");
    TDirectory * td22 = fout->mkdir("pt_b1_VBF");
    TDirectory * td23 = fout->mkdir("m_mt_nonVBF");
    TDirectory * td24 = fout->mkdir("m_mtb_nonVBF");
    TDirectory * td25 = fout->mkdir("pt_m_nonVBF");
    TDirectory * td26 = fout->mkdir("pt_t_nonVBF");
    TDirectory * td27 = fout->mkdir("pt_b1_nonVBF");
    
    TString qcd="_qcd";
    
    td1->cd();
    hist_m_mt->SetName(name.c_str());
    hist_m_mt->Write();
    hist_m_mt_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_qcd->Write();
    
    td2->cd();
    hist_m_bb->SetName(name.c_str());
    hist_m_bb->Write();
    hist_m_bb_qcd->SetName(name.c_str()+qcd);
    hist_m_bb_qcd->Write();
    
    td3->cd();
    hist_m_mtb->SetName(name.c_str());
    hist_m_mtb->Write();
    hist_m_mtb_qcd->SetName(name.c_str()+qcd);
    hist_m_mtb_qcd->Write();
    
    td4->cd();
    hist_m_mtbb->SetName(name.c_str());
    hist_m_mtbb->Write();
    hist_m_mtbb_qcd->SetName(name.c_str()+qcd);
    hist_m_mtbb_qcd->Write();
    
    td5->cd();
    hist_pt_m->SetName(name.c_str());
    hist_pt_m->Write();
    hist_pt_m_qcd->SetName(name.c_str()+qcd);
    hist_pt_m_qcd->Write();
    
    td6->cd();
    hist_pt_t->SetName(name.c_str());
    hist_pt_t->Write();
    hist_pt_t_qcd->SetName(name.c_str()+qcd);
    hist_pt_t_qcd->Write();
    
    td7->cd();
    hist_pt_b1->SetName(name.c_str());
    hist_pt_b1->Write();
    hist_pt_b1_qcd->SetName(name.c_str()+qcd);
    hist_pt_b1_qcd->Write();
    
    td8->cd();
    hist_eta_m->SetName(name.c_str());
    hist_eta_m->Write();
    hist_eta_m_qcd->SetName(name.c_str()+qcd);
    hist_eta_m_qcd->Write();
    
    td9->cd();
    hist_eta_t->SetName(name.c_str());
    hist_eta_t->Write();
    hist_eta_t_qcd->SetName(name.c_str()+qcd);
    hist_eta_t_qcd->Write();
    
    td10->cd();
    hist_eta_b1->SetName(name.c_str());
    hist_eta_b1->Write();
    hist_eta_b1_qcd->SetName(name.c_str()+qcd);
    hist_eta_b1_qcd->Write();
    
    td11->cd();
    hist_iso_m->SetName(name.c_str());
    hist_iso_m->Write();
    hist_iso_m_qcd->SetName(name.c_str()+qcd);
    hist_iso_m_qcd->Write();
    

    
    td13->cd();
    hist_met->SetName(name.c_str());
    hist_met->Write();
    hist_met_qcd->SetName(name.c_str()+qcd);
    hist_met_qcd->Write();
    
    td14->cd();
    hist_mjj->SetName(name.c_str());
    hist_mjj->Write();
    hist_mjj_qcd->SetName(name.c_str()+qcd);
    hist_mjj_qcd->Write();
    
    td15->cd();
    hist_mt_mumet->SetName(name.c_str());
    hist_mt_mumet->Write();
    hist_mt_mumet_qcd->SetName(name.c_str()+qcd);
    hist_mt_mumet_qcd->Write();
    
    td16->cd();
    hist_mt_taumet->SetName(name.c_str());
    hist_mt_taumet->Write();
    hist_mt_taumet_qcd->SetName(name.c_str()+qcd);
    hist_mt_taumet_qcd->Write();
    
    td17->cd();
    hist_dz->SetName(name.c_str());
    hist_dz->Write();
    hist_dz_qcd->SetName(name.c_str()+qcd);
    hist_dz_qcd->Write();
    
    td18->cd();
    hist_m_mt_VBF->SetName(name.c_str());
    hist_m_mt_VBF->Write();
    hist_m_mt_VBF_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_VBF_qcd->Write();
    
    td19->cd();
    hist_m_mtb_VBF->SetName(name.c_str());
    hist_m_mtb_VBF->Write();
    hist_m_mtb_VBF_qcd->SetName(name.c_str()+qcd);
    hist_m_mtb_VBF_qcd->Write();
    
    td20->cd();
    hist_pt_m_VBF->SetName(name.c_str());
    hist_pt_m_VBF->Write();
    hist_pt_m_VBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_m_VBF_qcd->Write();
    
    td21->cd();
    hist_pt_t_VBF->SetName(name.c_str());
    hist_pt_t_VBF->Write();
    hist_pt_t_VBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_t_VBF_qcd->Write();
    
    td22->cd();
    hist_pt_b1_VBF->SetName(name.c_str());
    hist_pt_b1_VBF->Write();
    hist_pt_b1_VBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_b1_VBF_qcd->Write();
    
    td23->cd();
    hist_m_mt_nonVBF->SetName(name.c_str());
    hist_m_mt_nonVBF->Write();
    hist_m_mt_nonVBF_qcd->SetName(name.c_str()+qcd);
    hist_m_mt_nonVBF_qcd->Write();
    
    td24->cd();
    hist_m_mtb_nonVBF->SetName(name.c_str());
    hist_m_mtb_nonVBF->Write();
    hist_m_mtb_nonVBF_qcd->SetName(name.c_str()+qcd);
    hist_m_mtb_nonVBF_qcd->Write();
    
    td25->cd();
    hist_pt_m_nonVBF->SetName(name.c_str());
    hist_pt_m_nonVBF->Write();
    hist_pt_m_nonVBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_m_nonVBF_qcd->Write();
    
    td26->cd();
    hist_pt_t_nonVBF->SetName(name.c_str());
    hist_pt_t_nonVBF->Write();
    hist_pt_t_nonVBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_t_nonVBF_qcd->Write();
    
    td27->cd();
    hist_pt_b1_nonVBF->SetName(name.c_str());
    hist_pt_b1_nonVBF->Write();
    hist_pt_b1_nonVBF_qcd->SetName(name.c_str()+qcd);
    hist_pt_b1_nonVBF_qcd->Write();

    
    
    fout->Close();
    
    delete wmc;
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}








