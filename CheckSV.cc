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
#include "btagSF.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("mutau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    TFile *f_Trk=new TFile("Tracking_EfficienciesAndSF_BCDEFGH.root");
    TGraph *h_Trk=(TGraph*) f_Trk->Get("ratio_eff_eta3_dr030e030_corr");

    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");

    //TFile *fZ=new TFile("zpt_weights_2016_BtoH.root");
    TFile *fZ=new TFile("zpt_weights_btag.root");
    TH2F *histZ=(TH2F*) fZ->Get("zptmass_histo");

    TFile *fM=new TFile("mbtt_weights_2016_BtoH.root");
    TH1F *histM=(TH1F*) fM->Get("mbtt_histo");

    //TFile fw("htt_scalefactors_v16_3.root");
    //RooWorkspace *w = (RooWorkspace*)fw.Get("w");
    //fw.Close();

    TFile fw2("htt_scalefactors_sm_moriond_v1.root");
    RooWorkspace *w2 = (RooWorkspace*)fw2.Get("w");
    fw2.Close();

    float xs=1.0; float weight=1.0; float luminosity=35870.0;
    if (sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=5765.4; weight=luminosity*xs/ngen;}
    else if (sample=="DYlow") {xs=18610; weight=luminosity*xs/ngen;}
    else if (sample=="DY1low") {xs=421.5; weight=luminosity*xs/ngen;}
    else if (sample=="DY2low") {xs=184.3; weight=luminosity*xs/ngen;}
    else if (sample=="TTL" or sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="QCD") {xs=720648000*0.00042; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="WZ1L1Nu2Q") {xs=10.71; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.05; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZLLLNu") {xs=4.708; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.212; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=11.95; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=26.23; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=44.07; weight=luminosity*xs/ngen;}
    else if (sample=="ggh") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="VBF") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt15") {xs=0.01*48.58*0.1475; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt20") {xs=0.01*48.58*0.1426; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt25") {xs=0.01*48.58*0.1381; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt30") {xs=0.01*48.58*0.1358; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt35") {xs=0.01*48.58*0.1338; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt40") {xs=0.01*48.58*0.1322; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt45") {xs=0.01*48.58*0.1282; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt50") {xs=0.01*48.58*0.1232; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt55") {xs=0.01*48.58*0.1193; weight=luminosity*xs/ngen;}
    else if (sample=="bbtt60") {xs=0.01*48.58*0.1133; weight=luminosity*xs/ngen;}
    else if (sample=="VBFbbtt20") {xs=0.01*3.782*0.1983; weight=luminosity*xs/ngen;}
    else if (sample=="VBFbbtt40") {xs=0.01*3.782*0.1908; weight=luminosity*xs/ngen;}
    else if (sample=="VBFbbtt60") {xs=0.01*3.782*0.1799; weight=luminosity*xs/ngen;}
    else if (sample=="WHbbtt40") {xs=0.01*(0.5328+0.840)*0.339; weight=luminosity*xs/ngen;}
    else if (sample=="ZHbbtt40") {xs=0.01*0.8839*0.242; weight=luminosity*xs/ngen;}
    else if (sample=="ggH125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="VBF125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ggH120") {xs=52.22*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="VBF120") {xs=3.935*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="ggH130") {xs=45.31*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="VBF130") {xs=3.637*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="ggH110") {xs=57.90*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="VBF110") {xs=4.434*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="ggH140") {xs=36.0*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="VBF140") {xs=3.492*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="ggHWW125") {xs=48.58*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBFWW125") {xs=3.782*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH120") {xs=0.9558*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusHWW125") {xs=0.840*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH130") {xs=0.7414*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH110") {xs=1.335*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH140") {xs=0.6308*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH120") {xs=0.6092*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusHWW125") {xs=0.5328*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH130") {xs=0.4676*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH110") {xs=0.8587*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH140") {xs=0.394*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="ZH120") {xs=0.9939*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW125") {xs=0.8839*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="ZH130") {xs=0.7899*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="ZH110") {xs=1.309*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="ZH140") {xs=0.6514*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="ZH_LLBB") {xs=0.8839*0.10974*0.5824; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH_LBB") {xs=0.5328*3*0.108535*0.5824; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH_LBB") {xs=0.840*3*0.108535*0.5824; weight=luminosity*xs/ngen;}
    else if (sample=="ttHnonbb") {xs=0.5085*(1-0.577); weight=luminosity*xs/ngen;}//FIXME
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarMuMu") {xs=2.793; weight=luminosity*xs/ngen;}
    else if (sample=="WGstarEE") {xs=3.526; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=20.25; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=25.62; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=3.987; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.01; weight=luminosity*xs/ngen;}
    else cout<<"Attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);
    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("px_1", &px_1);
    arbre->SetBranchAddress("py_1", &py_1);
    arbre->SetBranchAddress("pz_1", &pz_1);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("id_m_medium_1", &id_m_medium_1);
    arbre->SetBranchAddress("id_m_medium2016_1", &id_m_medium2016_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("nbtag_JESDown", &nbtag_JESDown);
    arbre->SetBranchAddress("nbtag_JESUp", &nbtag_JESUp);
    arbre->SetBranchAddress("nbtagL", &nbtagL);
    arbre->SetBranchAddress("nbtagT", &nbtagT);
    arbre->SetBranchAddress("nbtag15", &nbtag15);
    arbre->SetBranchAddress("nbtag15L", &nbtag15L);
    arbre->SetBranchAddress("nbtag15T", &nbtag15T);
    arbre->SetBranchAddress("bptL_1", &bptL_1);
    arbre->SetBranchAddress("betaL_1", &betaL_1);
    arbre->SetBranchAddress("bphiL_1", &bphiL_1);
    arbre->SetBranchAddress("bptL_2", &bptL_2);
    arbre->SetBranchAddress("betaL_2", &betaL_2);
    arbre->SetBranchAddress("bphiL_2", &bphiL_2);
    arbre->SetBranchAddress("bpt_1", &bpt_1);
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
    arbre->SetBranchAddress("bpt_1_JESUp", &bpt_1_JESUp);
    arbre->SetBranchAddress("beta_1_JESUp", &beta_1_JESUp);
    arbre->SetBranchAddress("bphi_1_JESUp", &bphi_1_JESUp);
    arbre->SetBranchAddress("bpt_1_JESDown", &bpt_1_JESDown);
    arbre->SetBranchAddress("beta_1_JESDown", &beta_1_JESDown);
    arbre->SetBranchAddress("bphi_1_JESDown", &bphi_1_JESDown);
    arbre->SetBranchAddress("bpt_2", &bpt_2);
    arbre->SetBranchAddress("beta_2", &beta_2);
    arbre->SetBranchAddress("bphi_2", &bphi_2);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("px_2", &px_2);
    arbre->SetBranchAddress("py_2", &py_2);
    arbre->SetBranchAddress("pz_2", &pz_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("amcatNLO_weight", &amcatNLO_weight);
    arbre->SetBranchAddress("metphi_JESDown", &metphi_JESDown);
    arbre->SetBranchAddress("metphi_JESUp", &metphi_JESUp);
    arbre->SetBranchAddress("met_JESDown", &met_JESDown);
    arbre->SetBranchAddress("met_JESUp", &met_JESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("njets_JESDown", &njets_JESDown);
    arbre->SetBranchAddress("njets_JESUp", &njets_JESUp);
    arbre->SetBranchAddress("byVLooseIsolationMVArun2v1DBoldDMwLT_2",&byVLooseIsolationMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byLooseIsolationMVArun2v1DBoldDMwLT_2",&byLooseIsolationMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byMediumIsolationMVArun2v1DBoldDMwLT_2",&byMediumIsolationMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byTightIsolationMVArun2v1DBoldDMwLT_2",&byTightIsolationMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byVTightIsolationMVArun2v1DBoldDMwLT_2",&byVTightIsolationMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byIsolationMVA3oldDMwLTraw_2",&byIsolationMVA3oldDMwLTraw_2);

    arbre->SetBranchAddress("matchIsoMu22eta2p1_1", &matchIsoMu22eta2p1_1);
    arbre->SetBranchAddress("matchIsoTkMu22eta2p1_1", &matchIsoTkMu22eta2p1_1);
    arbre->SetBranchAddress("matchIsoMu22_1", &matchIsoMu22_1);
    arbre->SetBranchAddress("matchIsoTkMu22_1", &matchIsoTkMu22_1);
    arbre->SetBranchAddress("matchIsoMu24_1", &matchIsoMu24_1);
    arbre->SetBranchAddress("matchIsoTkMu24_1", &matchIsoTkMu24_1);
    arbre->SetBranchAddress("matchIsoMu19Tau20_1", &matchIsoMu19Tau20_1);
    arbre->SetBranchAddress("matchIsoMu21Tau20_1", &matchIsoMu21Tau20_1);
    arbre->SetBranchAddress("filterIsoMu22eta2p1_1", &filterIsoMu22eta2p1_1);
    arbre->SetBranchAddress("filterIsoTkMu22eta2p1_1", &filterIsoTkMu22eta2p1_1);
    arbre->SetBranchAddress("filterIsoMu22_1", &filterIsoMu22_1);
    arbre->SetBranchAddress("filterIsoTkMu22_1", &filterIsoTkMu22_1);
    arbre->SetBranchAddress("filterIsoMu24_1", &filterIsoMu24_1);
    arbre->SetBranchAddress("filterIsoTkMu24_1", &filterIsoTkMu24_1);
    arbre->SetBranchAddress("filterIsoMu19Tau20_1", &filterIsoMu19Tau20_1);
    arbre->SetBranchAddress("filterIsoMu21Tau20_1", &filterIsoMu21Tau20_1);
    arbre->SetBranchAddress("passIsoMu22eta2p1", &passIsoMu22eta2p1);
    arbre->SetBranchAddress("passIsoTkMu22eta2p1", &passIsoTkMu22eta2p1);
    arbre->SetBranchAddress("passIsoMu22", &passIsoMu22);
    arbre->SetBranchAddress("passIsoTkMu22", &passIsoTkMu22);
    arbre->SetBranchAddress("passIsoMu24", &passIsoMu24);
    arbre->SetBranchAddress("passIsoTkMu24", &passIsoTkMu24);
    arbre->SetBranchAddress("passIsoMu19Tau20", &passIsoMu19Tau20);
    arbre->SetBranchAddress("passIsoMu21Tau20", &passIsoMu21Tau20);
    arbre->SetBranchAddress("matchIsoMu19Tau20_2", &matchIsoMu19Tau20_2);
    arbre->SetBranchAddress("matchIsoMu21Tau20_2", &matchIsoMu21Tau20_2);
    arbre->SetBranchAddress("filterIsoMu19Tau20_2", &filterIsoMu19Tau20_2);
    arbre->SetBranchAddress("filterIsoMu21Tau20_2", &filterIsoMu21Tau20_2);

    arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
    arbre->SetBranchAddress("againstElectronVLooseMVA6_2",&againstElectronVLooseMVA6_2);
    arbre->SetBranchAddress("againstElectronLooseMVA6_2",&againstElectronLooseMVA6_2);
    arbre->SetBranchAddress("againstElectronMediumMVA6_2",&againstElectronMediumMVA6_2);
    arbre->SetBranchAddress("againstElectronTightMVA6_2",&againstElectronTightMVA6_2);
    arbre->SetBranchAddress("againstElectronVTightMVA6_2",&againstElectronVTightMVA6_2);
    arbre->SetBranchAddress("againstMuonLoose3_2",&againstMuonLoose3_2);
    arbre->SetBranchAddress("againstMuonTight3_2",&againstMuonTight3_2);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("genEta",&genEta);
    arbre->SetBranchAddress("genPhi",&genPhi);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("genDR_2",&genDR_2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("bpt_1",&bpt_1);
    arbre->SetBranchAddress("bpt_2",&bpt_2);
    arbre->SetBranchAddress("bflavor_1",&bflavor_1);
    arbre->SetBranchAddress("bflavor_1_JESDown",&bflavor_1_JESDown);
    arbre->SetBranchAddress("bflavor_1_JESUp",&bflavor_1_JESUp);
    arbre->SetBranchAddress("bflavor_2",&bflavor_2);
    arbre->SetBranchAddress("bflavorL_1",&bflavorL_1);
    arbre->SetBranchAddress("bflavorL_2",&bflavorL_2);

    TH1F* h_mvis=new TH1F ("h_mvis","hOS",30,10,70);
    TH1F* h_sv=new TH1F ("h_sv","hOS",30,10,70);

   ScaleFactor * myScaleFactor_trgMu24 = new ScaleFactor();
   myScaleFactor_trgMu24->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_IsoMu24_OR_TkIsoMu24_2016BtoH_eff.root");
   ScaleFactor * myScaleFactor_trgMu19Leg = new ScaleFactor();
   myScaleFactor_trgMu19Leg->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu19leg_2016BtoH_eff.root");
   ScaleFactor * myScaleFactor_trgMu22 = new ScaleFactor();
   myScaleFactor_trgMu22->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu22OR_eta2p1_eff.root");
   ScaleFactor * myScaleFactor_trgMu19LegAnti = new ScaleFactor();
   myScaleFactor_trgMu19LegAnti->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu19leg_eta2p1_antiisolated_Iso0p15to0p3_eff_rb.root");
   ScaleFactor * myScaleFactor_trgMu22Anti = new ScaleFactor();
   myScaleFactor_trgMu22Anti->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_Mu22OR_eta2p1_antiisolated_Iso0p15to0p3_eff_rb.root");
   ScaleFactor * myScaleFactor_id = new ScaleFactor();
   myScaleFactor_id->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_IdIso_IsoLt0p15_2016BtoH_eff.root");
   ScaleFactor * myScaleFactor_idAnti = new ScaleFactor();
   myScaleFactor_idAnti->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BtoH/Muon_IdIso_antiisolated_Iso0p15to0p3_eff_rb.root");

   TString postfixTES[18]={"_CMS_scale_t_13TeVDown","_CMS_scale_t_13TeVUp","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_scale_m_13TeVUp","_CMS_scale_m_13TeVDown","_CMS_btag_heavy_13TeVUp","_CMS_btag_heavy_13TeVDown","_CMS_btag_light_13TeVUp","_CMS_btag_light_13TeVDown","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp"};
   TString postfixDM[6]={"_CMS_tauDMReco_1prong_13TeVUp","_CMS_tauDMReco_1prong_13TeVDown","_CMS_tauDMReco_1prong1pizero_13TeVUp","_CMS_tauDMReco_1prong1pizero_13TeVDown","_CMS_tauDMReco_3prong_13TeVUp","_CMS_tauDMReco_3prong_13TeVDown"};
   TString postfixFakeDM[6]={"_CMS_jetToTauDMReco_1prong_13TeVUp","_CMS_jetToTauDMReco_1prong_13TeVDown","_CMS_jetToTauDMReco_1prong1pizero_13TeVUp","_CMS_jetToTauDMReco_1prong1pizero_13TeVDown","_CMS_jetToTauDMReco_3prong_13TeVUp","_CMS_jetToTauDMReco_3prong_13TeVDown"};
   TString postfixZLshape[2]={"_CMS_htt_ZLShape_mt_13TeVUp","_CMS_htt_ZLShape_mt_13TeVDown"};
   TString postfixZLnorm[4]={"_CMS_mFakeTau_1prong_13TeVUp","_CMS_mFakeTau_1prong_13TeVDown","_CMS_mFakeTau_1prong1pizero_13TeVUp","_CMS_mFakeTau_1prong1pizero_13TeVDown"};
   TString postfixJES[56]={"_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"};
   TString postfixFake[12]={"_CMS_fakeRate10_var1_13TeVUp","_CMS_fakeRate10_var1_13TeVDown","_CMS_fakeRate10_var2_13TeVUp","_CMS_fakeRate10_var2_13TeVDown","_CMS_fakeRate1_var1_13TeVUp","_CMS_fakeRate1_var1_13TeVDown","_CMS_fakeRate1_var2_13TeVUp","_CMS_fakeRate1_var2_13TeVDown","_CMS_fakeRate0_var1_13TeVUp","_CMS_fakeRate0_var1_13TeVDown","_CMS_fakeRate0_var2_13TeVUp","_CMS_fakeRate0_var2_13TeVDown"};


   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	bool isSingleLep = (passIsoMu22 && matchIsoMu22_1 && filterIsoMu22_1) or (passIsoTkMu22 && matchIsoTkMu22_1 && filterIsoTkMu22_1) or (passIsoMu22eta2p1 && matchIsoMu22eta2p1_1 && filterIsoMu22eta2p1_1) or (passIsoTkMu22eta2p1 && matchIsoTkMu22eta2p1_1 && filterIsoTkMu22eta2p1_1);
	bool isCrossTrigger = (passIsoMu19Tau20 && matchIsoMu19Tau20_1 && filterIsoMu19Tau20_1 && matchIsoMu19Tau20_2 && filterIsoMu19Tau20_2);

        if (sample=="data_obs" && run<278820 && !id_m_medium2016_1) continue;
        if (sample=="data_obs" && run>=278820 && !id_m_medium_1) continue;

	if (pt_1<19.8) continue;
        if (fabs(eta_1)>2.1) continue;
	if (!isSingleLep && !isCrossTrigger) continue;
	if (!((isSingleLep && pt_1>23) or (isCrossTrigger && (pt_1<=23 or pt_2<22)))) continue;

	//if (!againstElectronVLooseMVA6_2 or !againstMuonLoose3_2) continue; //deja coupe dans le skim
        float sf_trg=1.0;
        float sf_id=1.0;
        float sf_id_anti=1.0;
	float sf_trg_anti=1.0;
	float eff_tau=1.0;
	float eff_tau_anti=1.0;

	if (sample!="data_obs"){
           sf_id=myScaleFactor_id->get_ScaleFactor(pt_1,eta_1);
        }

	float signalRegion=(byTightIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
	float aiRegion=(byVLooseIsolationMVArun2v1DBoldDMwLT_2 && !byTightIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
	float qcdRegion=(byLooseIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30);
        float wRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30);
        float wsfRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
        float qcdCR=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30 && iso_1>0.15);

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mybjet1L;
        mybjet1L.SetPtEtaPhiM(bptL_1,betaL_1,bphiL_1,0);
        TLorentzVector mybjet2L;
        mybjet2L.SetPtEtaPhiM(bptL_2,betaL_2,bphiL_2,0);
        TLorentzVector mybjet1T;
        mybjet1T.SetPtEtaPhiM(bptT_1,betaT_1,bphiT_1,0);
        TLorentzVector mybjet2T;
        mybjet2T.SetPtEtaPhiM(bptT_2,betaT_2,bphiT_2,0);
        TLorentzVector mybjet1;
        mybjet1.SetPtEtaPhiM(bpt_1,beta_1,bphi_1,0);
        TLorentzVector mybjet2;
        mybjet2.SetPtEtaPhiM(bpt_2,beta_2,bphi_2,0);

	//***************** Weights **************

        if (sample=="W"){
            weight=25.446;
            if (numGenJets==1) weight=6.8176;
            else if (numGenJets==2) weight=2.1038;
            else if (numGenJets==3) weight=0.6889;
            else if (numGenJets==4) weight=0.6900;
        }

        if (sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ"){
            weight=1.4184;
            if (numGenJets==1)
                weight=0.45729;
            else if (numGenJets==2)
                weight=0.4668;
            else if (numGenJets==3)
                weight=0.47995;
            else if (numGenJets==4)
                weight=0.39349;
        }

        if (sample=="DYlow" or sample=="DYlowll" or sample=="DY1low" or sample=="DY1lowll" or sample=="DY2low" or sample=="DY2lowll"){
            weight=0.0;
            if (numGenJets==1) weight=0.74;
            else if (numGenJets==2) weight=0.823;
        }

	float correction=sf_id;
	if (sample!="data_obs") correction=correction*LumiWeights_12->weight(npu);
	float aweight=amcatNLO_weight*weight*correction;

        if (sample!="data_obs"){
           if (gen_match_2==5) aweight=aweight*0.95; //Tau ID SF
           else if (gen_match_2==2 or gen_match_2==4){
               if (fabs(mytau.Eta())<0.4) aweight=aweight*1.012;
               else if (fabs(mytau.Eta())<0.8) aweight=aweight*1.007;
               else if (fabs(mytau.Eta())<1.2) aweight=aweight*0.870;
               else if (fabs(mytau.Eta())<1.7) aweight=aweight*1.154;
               else aweight=aweight*2.281;
           }
	   else if (gen_match_2==1 or gen_match_2==3){//Yiwen
              if (fabs(eta_2)<1.460) aweight=aweight*1.213;
              else if (fabs(eta_2)>1.558) aweight=aweight*1.375;
           }
	   aweight=aweight*h_Trk->Eval(eta_1);
        }

	if (sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ" or sample=="DYlow" or sample=="DY1low" or sample=="DY2low"){
	    //float zpt_corr=histZ->GetBinContent(histZ->GetXaxis()->FindBin(genM),histZ->GetYaxis()->FindBin(genpT));
	    float zpt_corr=histZ->GetBinContent(histZ->GetXaxis()->FindBin(90),histZ->GetYaxis()->FindBin(genpT));
	    if (fabs(tes)!=10) //nominal
	         aweight=aweight*zpt_corr;
	    else if (tes==10) // up
		 aweight=aweight*(1+1.10*(zpt_corr-1));
	    else if (tes==-10) // down
	 	 aweight=aweight*(1+0.90*(zpt_corr-1));
	}

	//************************ Jet to tau FR shape **************************
	if (tes==14 && (sample=="TTJ" or sample=="ZJ" or sample=="W") && gen_match_2==6){
	    float jtotau=1-(0.2*mytau.Pt()/100);
	    if (mytau.Pt()>200) jtotau=1-(0.2*200.0/100);
	    aweight=aweight*jtotau;
	}
        if (tes==-14 && (sample=="TTJ" or sample=="ZJ" or sample=="W") && gen_match_2==6){
            float jtotau=1+(0.2*mytau.Pt()/100);
            if (mytau.Pt()>200) jtotau=1+(0.2*200.0/100);
            aweight=aweight*jtotau;
        }

	// ###########################################################
	// ######## Separation between L, T and J ####################
	// ###########################################################
	
        if (sample=="ZL" && gen_match_2>4) continue;
        if (sample=="ZTT" && gen_match_2!=5) continue;
        if (sample=="ZJ" && gen_match_2!=6) continue;
        if (sample=="TTJ" && gen_match_2!=6) continue;
        //if (sample=="TTT" && gen_match_2==6) continue;
        if (sample=="TTT" && gen_match_2!=5) continue;
	if (sample=="TTL" && gen_match_2>4) continue;
	if (name=="VV" && gen_match_2==6) continue;
        if (name=="ST" && gen_match_2==6) continue;

	// #############################################################
     	// ################### Top pT reweighting ######################
     	// #############################################################
	float pttop1=pt_top1;
        if (pttop1>400) pttop1=400;
        float pttop2=pt_top2;
        if (pttop2>400) pttop2=400;
        if ((sample=="TTJ" or sample=="TTT" or sample=="TT" or sample=="TTL") && fabs(tes)!=11) aweight*=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));
        if ((sample=="TTJ" or sample=="TTT" or sample=="TT" or sample=="TTL") && tes==11) aweight*=(1+2*(sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2))-1));

	if (sample=="data_obs") aweight=1.0;

	float weight_btag_1b=1.0;
	if (sample!="data_obs"){
	    weight_btag_1b=GetSF_M(1,bpt_1,bflavor_1,0);
	}

	// ############################################################
	// ############### Loop over JES sources ######################
	// ############################################################
	//

        TLorentzVector myrawmet;
        myrawmet.SetPtEtaPhiM(met,0,metphi,0);
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawmu=mymu;
	TLorentzVector myrawbjet1=mybjet1;

	    float weight2=1.0;
	    TLorentzVector mymet=myrawmet;
	    mytau=myrawtau;
            mymu=myrawmu;
   	    mybjet1=myrawbjet1;

            if (sample!="data_obs"){
              weight_btag_1b=GetSF_M(1,bpt_1,bflavor_1,0);
            }

            bool has_1b=nbtag>=1;//FIXME
	    float dm_weight=1.0;

	    if (mytau.Pt()<25.0) continue;
	    if (mymu.Pt()<20.0) continue;

        float norm_zeta=norm_F(mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt(),mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(mymu.Px()+mytau.Px())*x_zeta+(mymu.Py()+mytau.Py())*y_zeta;
        float pzeta=p_zeta_mis-0.85*pzeta_vis;

            float mt1=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());
            float mt2=TMass_F(mytau.Pt(),mymet.Pt(),mytau.Px(),mymet.Px(),mytau.Py(),mymet.Py());
            float mt12=TMass_F((mytau+mymu).Pt(),mymet.Pt(),(mytau+mymu).Px(),mymet.Px(),(mytau+mymu).Py(),mymet.Py());
	    float mbbtt=(mymu+mytau+mybjet1L+mybjet2L).M();
            float mbtt=(mymu+mytau+mybjet1).M();
	    float mtt=(mymu+mytau).M();
	    float var_1b=mtt;
            float var_2b=mtt;

        if (sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ" or sample=="DYlow" or sample=="DY1low" or sample=="DY2low"){
	     TLorentzVector genZ;
	     genZ.SetPtEtaPhiM(genpT,genEta,genPhi,genM);
	     float genmbtt=(genZ+mybjet1).M();
	     if (genmbtt<40) genmbtt=40;
	     if (genmbtt>600) genmbtt=600;
	     float mbtt_corr=histM->GetBinContent(histM->GetXaxis()->FindBin(genmbtt));
	     if (mbtt_corr<0.5) mbtt_corr=1.0;
	     if (fabs(tes)!=8) weight2=weight2*mbtt_corr;
             if (tes==8) // up
                 weight2=weight2*(1+2.00*(mbtt_corr-1));
             if (tes==-8) // down
                 weight2=weight2*(1+0.00*(mbtt_corr-1));

	}

            if (sample!="data_obs"){
	       if (mymu.Pt()<23){ 
                   w2->var("t_pt")->setVal(mytau.Pt());
                   w2->var("t_eta")->setVal(mytau.Eta());
                   w2->var("t_dm")->setVal(l2_decayMode);
                   float eff_tau_ratio = w2->function("t_genuine_TightIso_mt_ratio")->getVal();
		   sf_trg=myScaleFactor_trgMu19Leg->get_ScaleFactor(pt_1,eta_1)*eff_tau_ratio;
	       }
	       else{
		   sf_trg=myScaleFactor_trgMu22->get_ScaleFactor(pt_1,eta_1);
	       }
	    }

	    if (sample=="data_obs") {aweight=1.0; weight2=1.0;}
            weight2=weight2*sf_trg*dm_weight;

	    float fr=1.0;
            /*float p0_dm0_B=0.218512;
            float p1_dm0_B=0.000337089;
            float p0_dm1_B=0.230227;
            float p1_dm1_B=0.000786509;
            float p0_dm10_B=0.172631;
            float p1_dm10_B=0.0000840138;

            float p0_dm0_E=0.270796;
            float p1_dm0_E=0.000821388;
            float p0_dm1_E=0.244202;
            float p1_dm1_E=0.000882359;
            float p0_dm10_E=0.214062;
            float p1_dm10_E=0.000896065;

            if (l2_decayMode==0) fr=p0_dm0_B-p1_dm0_B*pt_2;
            else if (l2_decayMode==1) fr=p0_dm1_B-p1_dm1_B*pt_2;
            else if (l2_decayMode==10) fr=p0_dm10_B-p1_dm10_B*pt_2;
            if (fabs(eta_2)>1.479){
               if (l2_decayMode==0) fr=p0_dm0_E-p1_dm0_E*pt_2;
               else if (l2_decayMode==1) fr=p0_dm1_E-p1_dm1_E*pt_2;
               else if (l2_decayMode==10) fr=p0_dm10_E-p1_dm10_E*pt_2;
            }*/
	    //Tight
	    /*if (l2_decayMode==0) fr= 0.2401 - 0.000614282 * (mytau.Pt()-40);
            if (l2_decayMode==1) fr= 0.230823 - 0.000918427 * (mytau.Pt()-40);
            if (l2_decayMode==10) fr= 0.17867 + 0.000316496 * (mytau.Pt()-40);

	    if (tes==30 && l2_decayMode==10){//FIXME
		if (k==0) fr= 0.18166+0.000239627 * (mytau.Pt()-40);
                if (k==1) fr= 0.175687 + 0.000393365 * (mytau.Pt()-40);
                if (k==2) fr= 0.178668 +0.000523315 * (mytau.Pt()-40);
                if (k==3) fr= 0.178679 +0.000109677 * (mytau.Pt()-40);
	    }
            if (tes==30 && l2_decayMode==1){
                if (k==4) fr= 0.234162 -0.000943962 * (mytau.Pt()-40);
                if (k==5) fr= 0.227485 -0.000892892 * (mytau.Pt()-40);
                if (k==6) fr= 0.230822 -0.000712327 * (mytau.Pt()-40);
                if (k==7) fr= 0.230825 -0.00112453 * (mytau.Pt()-40);
            }
            if (tes==30 && l2_decayMode==0){
                if (k==8) fr= 0.246021 -0.000686205 * (mytau.Pt()-40);
                if (k==9) fr= 0.234195 -0.00054236 * (mytau.Pt()-40);
                if (k==10) fr= 0.240103 -0.00024351 * (mytau.Pt()-40);
                if (k==11) fr= 0.240112 -0.000985054 * (mytau.Pt()-40);
            }*/

	    if (l2_decayMode==0) fr= 2.20179e-01 + 3.17084e-01*(TMath::Landau(mytau.Pt(),2.30233e+01,2.62218e+00,0));
            if (l2_decayMode==1) fr= 1.83924e-01 + 8.66271e+00*(TMath::Landau(mytau.Pt(),-2.56076e+01,4.12774e+00,0));
            if (l2_decayMode==10) fr= 6.27144e-02 + 7.25830e-01*(TMath::Landau(mytau.Pt(),6.37171e+01,3.38631e+01,0));

	    /*//Medium
	    if (l2_decayMode==0) fr= 0.3696 - 0.0009 * (pt_2-40);
            if (l2_decayMode==1) fr= 0.3608 - 0.0012 * (pt_2-40);
            if (l2_decayMode==10) fr= 0.2865 + 0.0001 * (pt_2-40);*/

	    //Very tight
	    /*if (l2_decayMode==0) fr= 0.1537 - 0.0005 * (pt_2-40);
            if (l2_decayMode==1) fr= 0.1433 - 0.0007 * (pt_2-40);
            if (l2_decayMode==10) fr= 0.1124 + 0.0003 * (pt_2-40);*/

	    float wfr=fr/(1-fr);
	    float weight_btag_2b=1.0;

                    h_mvis->Fill((mymu+mytau).M());
                    h_sv->Fill(m_sv);
    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_mvis->SetName("mvis");
    h_sv->SetName("msv");
    h_mvis->Write();
    h_sv->Write();
    fout->Close();
} 


