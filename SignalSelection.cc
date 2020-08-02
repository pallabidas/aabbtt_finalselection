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

    TFile *fZ=new TFile("zpt_weights_2016_BtoH.root");
    TH2F *histZ=(TH2F*) fZ->Get("zptmass_histo");

    //TFile fw("htt_scalefactors_v16_3.root");
    //RooWorkspace *w = (RooWorkspace*)fw.Get("w");
    //fw.Close();

    TFile fw2("htt_scalefactors_sm_moriond_v1.root");
    RooWorkspace *w2 = (RooWorkspace*)fw2.Get("w");
    fw2.Close();

    float xs=1.0; float weight=1.0; float luminosity=35870.0;
    if (sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=5765.4; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
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
    else if (sample=="ggH125") {xs=48.58; weight=luminosity*xs/ngen;}
    else if (sample=="VBF125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ggH120") {xs=52.22*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="VBF120") {xs=3.935*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="ggH130") {xs=45.31*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="VBF130") {xs=3.637*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="ggH110") {xs=57.90*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="VBF110") {xs=4.434*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="ggH140") {xs=36.0*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="VBF140") {xs=3.492*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_WW125") {xs=48.58*0.2137*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBF_WW125") {xs=3.782*0.2137*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH120") {xs=0.9558*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH130") {xs=0.7414*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH110") {xs=1.335*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH140") {xs=0.6308*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH120") {xs=0.6092*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH130") {xs=0.4676*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH110") {xs=0.8587*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH140") {xs=0.394*0.0360; weight=luminosity*xs/ngen;}
    else if (sample=="ZH120") {xs=0.9939*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH130") {xs=0.7899*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="ZH110") {xs=1.309*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="ZH140") {xs=0.6514*0.0360; weight=luminosity*xs/ngen;}
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
    arbre->SetBranchAddress("bptT_1", &bptT_1);
    arbre->SetBranchAddress("betaT_1", &betaT_1);
    arbre->SetBranchAddress("bphiT_1", &bphiT_1);
    arbre->SetBranchAddress("bptT_2", &bptT_2);
    arbre->SetBranchAddress("betaT_2", &betaT_2);
    arbre->SetBranchAddress("bphiT_2", &bphiT_2);
    arbre->SetBranchAddress("bpt_1", &bpt_1);
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
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
    arbre->SetBranchAddress("mt_2", &mt_2);
    arbre->SetBranchAddress("phi_2", &phi_2);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("mjj", &mjj);
    arbre->SetBranchAddress("amcatNLO_weight", &amcatNLO_weight);
    arbre->SetBranchAddress("mjj_JESDown", &mjj_JESDown);
    arbre->SetBranchAddress("mjj_JESUp", &mjj_JESUp);
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

    arbre->SetBranchAddress("byVLooseIsolationRerunMVArun2v1DBoldDMwLT_2", &byVLooseIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byLooseIsolationRerunMVArun2v1DBoldDMwLT_2", &byLooseIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byMediumIsolationRerunMVArun2v1DBoldDMwLT_2", &byMediumIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byTightIsolationRerunMVArun2v1DBoldDMwLT_2", &byTightIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byVTightIsolationRerunMVArun2v1DBoldDMwLT_2", &byVTightIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byVVTightIsolationRerunMVArun2v1DBoldDMwLT_2", &byVVTightIsolationRerunMVArun2v1DBoldDMwLT_2);
    arbre->SetBranchAddress("byIsolationRerunMVA3oldDMwLTraw_2", &byIsolationRerunMVA3oldDMwLTraw_2);

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
    arbre->SetBranchAddress("againstMuonTight3_2",&againstMuonTight3_2);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("m_vis",&m_vis);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("genDR_2",&genDR_2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);
    arbre->SetBranchAddress("bpt_1",&bpt_1);
    arbre->SetBranchAddress("bpt_2",&bpt_2);
    arbre->SetBranchAddress("bflavor_1",&bflavor_1);
    arbre->SetBranchAddress("bflavor_2",&bflavor_2);

    arbre->SetBranchAddress("njets_JetAbsoluteFlavMapDown",&njets_JetAbsoluteFlavMapDown);
    arbre->SetBranchAddress("njets_JetAbsoluteFlavMapUp",&njets_JetAbsoluteFlavMapUp);
    arbre->SetBranchAddress("njets_JetAbsoluteMPFBiasDown",&njets_JetAbsoluteMPFBiasDown);
    arbre->SetBranchAddress("njets_JetAbsoluteMPFBiasUp",&njets_JetAbsoluteMPFBiasUp);
    arbre->SetBranchAddress("njets_JetAbsoluteScaleDown",&njets_JetAbsoluteScaleDown);
    arbre->SetBranchAddress("njets_JetAbsoluteScaleUp",&njets_JetAbsoluteScaleUp);
    arbre->SetBranchAddress("njets_JetAbsoluteStatDown",&njets_JetAbsoluteStatDown);
    arbre->SetBranchAddress("njets_JetAbsoluteStatUp",&njets_JetAbsoluteStatUp);
    arbre->SetBranchAddress("njets_JetFlavorQCDDown",&njets_JetFlavorQCDDown);
    arbre->SetBranchAddress("njets_JetFlavorQCDUp",&njets_JetFlavorQCDUp);
    arbre->SetBranchAddress("njets_JetFragmentationDown",&njets_JetFragmentationDown);
    arbre->SetBranchAddress("njets_JetFragmentationUp",&njets_JetFragmentationUp);
    arbre->SetBranchAddress("njets_JetPileUpDataMCDown",&njets_JetPileUpDataMCDown);
    arbre->SetBranchAddress("njets_JetPileUpDataMCUp",&njets_JetPileUpDataMCUp);
    arbre->SetBranchAddress("njets_JetPileUpPtBBDown",&njets_JetPileUpPtBBDown);
    arbre->SetBranchAddress("njets_JetPileUpPtBBUp",&njets_JetPileUpPtBBUp);
    arbre->SetBranchAddress("njets_JetPileUpPtEC1Down",&njets_JetPileUpPtEC1Down);
    arbre->SetBranchAddress("njets_JetPileUpPtEC1Up",&njets_JetPileUpPtEC1Up);
    arbre->SetBranchAddress("njets_JetPileUpPtEC2Down",&njets_JetPileUpPtEC2Down);
    arbre->SetBranchAddress("njets_JetPileUpPtEC2Up",&njets_JetPileUpPtEC2Up);
    arbre->SetBranchAddress("njets_JetPileUpPtHFDown",&njets_JetPileUpPtHFDown);
    arbre->SetBranchAddress("njets_JetPileUpPtHFUp",&njets_JetPileUpPtHFUp);
    arbre->SetBranchAddress("njets_JetPileUpPtRefDown",&njets_JetPileUpPtRefDown);
    arbre->SetBranchAddress("njets_JetPileUpPtRefUp",&njets_JetPileUpPtRefUp);
    arbre->SetBranchAddress("njets_JetRelativeBalDown",&njets_JetRelativeBalDown);
    arbre->SetBranchAddress("njets_JetRelativeBalUp",&njets_JetRelativeBalUp);
    arbre->SetBranchAddress("njets_JetRelativeFSRDown",&njets_JetRelativeFSRDown);
    arbre->SetBranchAddress("njets_JetRelativeFSRUp",&njets_JetRelativeFSRUp);
    arbre->SetBranchAddress("njets_JetRelativeJEREC1Down",&njets_JetRelativeJEREC1Down);
    arbre->SetBranchAddress("njets_JetRelativeJEREC1Up",&njets_JetRelativeJEREC1Up);
    arbre->SetBranchAddress("njets_JetRelativeJEREC2Down",&njets_JetRelativeJEREC2Down);
    arbre->SetBranchAddress("njets_JetRelativeJEREC2Up",&njets_JetRelativeJEREC2Up);
    arbre->SetBranchAddress("njets_JetRelativeJERHFDown",&njets_JetRelativeJERHFDown);
    arbre->SetBranchAddress("njets_JetRelativeJERHFUp",&njets_JetRelativeJERHFUp);
    arbre->SetBranchAddress("njets_JetRelativePtBBDown",&njets_JetRelativePtBBDown);
    arbre->SetBranchAddress("njets_JetRelativePtBBUp",&njets_JetRelativePtBBUp);
    arbre->SetBranchAddress("njets_JetRelativePtEC1Down",&njets_JetRelativePtEC1Down);
    arbre->SetBranchAddress("njets_JetRelativePtEC1Up",&njets_JetRelativePtEC1Up);
    arbre->SetBranchAddress("njets_JetRelativePtEC2Down",&njets_JetRelativePtEC2Down);
    arbre->SetBranchAddress("njets_JetRelativePtEC2Up",&njets_JetRelativePtEC2Up);
    arbre->SetBranchAddress("njets_JetRelativePtHFDown",&njets_JetRelativePtHFDown);
    arbre->SetBranchAddress("njets_JetRelativePtHFUp",&njets_JetRelativePtHFUp);
    arbre->SetBranchAddress("njets_JetRelativeStatECDown",&njets_JetRelativeStatECDown);
    arbre->SetBranchAddress("njets_JetRelativeStatECUp",&njets_JetRelativeStatECUp);
    arbre->SetBranchAddress("njets_JetRelativeStatFSRDown",&njets_JetRelativeStatFSRDown);
    arbre->SetBranchAddress("njets_JetRelativeStatFSRUp",&njets_JetRelativeStatFSRUp);
    arbre->SetBranchAddress("njets_JetRelativeStatHFDown",&njets_JetRelativeStatHFDown);
    arbre->SetBranchAddress("njets_JetRelativeStatHFUp",&njets_JetRelativeStatHFUp);
    arbre->SetBranchAddress("njets_JetSinglePionECALDown",&njets_JetSinglePionECALDown);
    arbre->SetBranchAddress("njets_JetSinglePionECALUp",&njets_JetSinglePionECALUp);
    arbre->SetBranchAddress("njets_JetSinglePionHCALDown",&njets_JetSinglePionHCALDown);
    arbre->SetBranchAddress("njets_JetSinglePionHCALUp",&njets_JetSinglePionHCALUp);
    arbre->SetBranchAddress("njets_JetTimePtEtaDown",&njets_JetTimePtEtaDown);
    arbre->SetBranchAddress("njets_JetTimePtEtaUp",&njets_JetTimePtEtaUp);

    arbre->SetBranchAddress("mjj_JetAbsoluteFlavMapDown",&mjj_JetAbsoluteFlavMapDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteFlavMapUp",&mjj_JetAbsoluteFlavMapUp);
    arbre->SetBranchAddress("mjj_JetAbsoluteMPFBiasDown",&mjj_JetAbsoluteMPFBiasDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteMPFBiasUp",&mjj_JetAbsoluteMPFBiasUp);
    arbre->SetBranchAddress("mjj_JetAbsoluteScaleDown",&mjj_JetAbsoluteScaleDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteScaleUp",&mjj_JetAbsoluteScaleUp);
    arbre->SetBranchAddress("mjj_JetAbsoluteStatDown",&mjj_JetAbsoluteStatDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteStatUp",&mjj_JetAbsoluteStatUp);
    arbre->SetBranchAddress("mjj_JetFlavorQCDDown",&mjj_JetFlavorQCDDown);
    arbre->SetBranchAddress("mjj_JetFlavorQCDUp",&mjj_JetFlavorQCDUp);
    arbre->SetBranchAddress("mjj_JetFragmentationDown",&mjj_JetFragmentationDown);
    arbre->SetBranchAddress("mjj_JetFragmentationUp",&mjj_JetFragmentationUp);
    arbre->SetBranchAddress("mjj_JetPileUpDataMCDown",&mjj_JetPileUpDataMCDown);
    arbre->SetBranchAddress("mjj_JetPileUpDataMCUp",&mjj_JetPileUpDataMCUp);
    arbre->SetBranchAddress("mjj_JetPileUpPtBBDown",&mjj_JetPileUpPtBBDown);
    arbre->SetBranchAddress("mjj_JetPileUpPtBBUp",&mjj_JetPileUpPtBBUp);
    arbre->SetBranchAddress("mjj_JetPileUpPtEC1Down",&mjj_JetPileUpPtEC1Down);
    arbre->SetBranchAddress("mjj_JetPileUpPtEC1Up",&mjj_JetPileUpPtEC1Up);
    arbre->SetBranchAddress("mjj_JetPileUpPtEC2Down",&mjj_JetPileUpPtEC2Down);
    arbre->SetBranchAddress("mjj_JetPileUpPtEC2Up",&mjj_JetPileUpPtEC2Up);
    arbre->SetBranchAddress("mjj_JetPileUpPtHFDown",&mjj_JetPileUpPtHFDown);
    arbre->SetBranchAddress("mjj_JetPileUpPtHFUp",&mjj_JetPileUpPtHFUp);
    arbre->SetBranchAddress("mjj_JetPileUpPtRefDown",&mjj_JetPileUpPtRefDown);
    arbre->SetBranchAddress("mjj_JetPileUpPtRefUp",&mjj_JetPileUpPtRefUp);
    arbre->SetBranchAddress("mjj_JetRelativeBalDown",&mjj_JetRelativeBalDown);
    arbre->SetBranchAddress("mjj_JetRelativeBalUp",&mjj_JetRelativeBalUp);
    arbre->SetBranchAddress("mjj_JetRelativeFSRDown",&mjj_JetRelativeFSRDown);
    arbre->SetBranchAddress("mjj_JetRelativeFSRUp",&mjj_JetRelativeFSRUp);
    arbre->SetBranchAddress("mjj_JetRelativeJEREC1Down",&mjj_JetRelativeJEREC1Down);
    arbre->SetBranchAddress("mjj_JetRelativeJEREC1Up",&mjj_JetRelativeJEREC1Up);
    arbre->SetBranchAddress("mjj_JetRelativeJEREC2Down",&mjj_JetRelativeJEREC2Down);
    arbre->SetBranchAddress("mjj_JetRelativeJEREC2Up",&mjj_JetRelativeJEREC2Up);
    arbre->SetBranchAddress("mjj_JetRelativeJERHFDown",&mjj_JetRelativeJERHFDown);
    arbre->SetBranchAddress("mjj_JetRelativeJERHFUp",&mjj_JetRelativeJERHFUp);
    arbre->SetBranchAddress("mjj_JetRelativePtBBDown",&mjj_JetRelativePtBBDown);
    arbre->SetBranchAddress("mjj_JetRelativePtBBUp",&mjj_JetRelativePtBBUp);
    arbre->SetBranchAddress("mjj_JetRelativePtEC1Down",&mjj_JetRelativePtEC1Down);
    arbre->SetBranchAddress("mjj_JetRelativePtEC1Up",&mjj_JetRelativePtEC1Up);
    arbre->SetBranchAddress("mjj_JetRelativePtEC2Down",&mjj_JetRelativePtEC2Down);
    arbre->SetBranchAddress("mjj_JetRelativePtEC2Up",&mjj_JetRelativePtEC2Up);
    arbre->SetBranchAddress("mjj_JetRelativePtHFDown",&mjj_JetRelativePtHFDown);
    arbre->SetBranchAddress("mjj_JetRelativePtHFUp",&mjj_JetRelativePtHFUp);
    arbre->SetBranchAddress("mjj_JetRelativeStatECDown",&mjj_JetRelativeStatECDown);
    arbre->SetBranchAddress("mjj_JetRelativeStatECUp",&mjj_JetRelativeStatECUp);
    arbre->SetBranchAddress("mjj_JetRelativeStatFSRDown",&mjj_JetRelativeStatFSRDown);
    arbre->SetBranchAddress("mjj_JetRelativeStatFSRUp",&mjj_JetRelativeStatFSRUp);
    arbre->SetBranchAddress("mjj_JetRelativeStatHFDown",&mjj_JetRelativeStatHFDown);
    arbre->SetBranchAddress("mjj_JetRelativeStatHFUp",&mjj_JetRelativeStatHFUp);
    arbre->SetBranchAddress("mjj_JetSinglePionECALDown",&mjj_JetSinglePionECALDown);
    arbre->SetBranchAddress("mjj_JetSinglePionECALUp",&mjj_JetSinglePionECALUp);
    arbre->SetBranchAddress("mjj_JetSinglePionHCALDown",&mjj_JetSinglePionHCALDown);
    arbre->SetBranchAddress("mjj_JetSinglePionHCALUp",&mjj_JetSinglePionHCALUp);
    arbre->SetBranchAddress("mjj_JetTimePtEtaDown",&mjj_JetTimePtEtaDown);
    arbre->SetBranchAddress("mjj_JetTimePtEtaUp",&mjj_JetTimePtEtaUp);

   float bins0[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500};
   float bins1[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500};

   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;

   TH1F *hincl=new TH1F ("hincl", "hincl", 16,0,160); hincl->Sumw2();
   TH1F *nlowhigh=new TH1F ("nlowhigh", "nlowhigh", 6,0,6);nlowhigh->Sumw2();

   TH1F *acc=new TH1F ("acc", "acc", 30,0,30); acc->Sumw2();
   TH1F *masse=new TH1F ("masse", "masse", 30,0,300); masse->Sumw2();

   std::vector<TH1F*> n70;
   std::vector<TH1F*> n70SS;

   std::vector<TH1F*> h0_CR_W;
   std::vector<TH1F*> h0_CR_QCD;
   std::vector<TH1F*> h0_CRSS_W;
   std::vector<TH1F*> h0_CRSS_QCD;
   std::vector<TH1F*> h1_CR_W;
   std::vector<TH1F*> h1_CR_QCD;
   std::vector<TH1F*> h1_CRSS_W;
   std::vector<TH1F*> h1_CRSS_QCD;
   std::vector<TH1F*> h2_CR_W;
   std::vector<TH1F*> h2_CR_QCD;
   std::vector<TH1F*> h2_CRSS_W;
   std::vector<TH1F*> h2_CRSS_QCD;

   std::vector<TH1F*> h0_OS;
   std::vector<TH1F*> h1_OS;
   std::vector<TH1F*> h0_SS;
   std::vector<TH1F*> h1_SS;
   std::vector<TH1F*> h0_QCD;
   std::vector<TH1F*> h1_QCD;
   std::vector<TH1F*> h0_WOS;
   std::vector<TH1F*> h1_WOS;
   std::vector<TH1F*> h0_WSS;
   std::vector<TH1F*> h1_WSS;

   int nbhist=1;
   if (tes==100) nbhist=56;
   if (tes==1) nbhist=12;
   if (tes==16) nbhist=6;
   if (tes==17) nbhist=12;
   if (tes==18) nbhist=4;
   if (tes==19) nbhist=6;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNn70; HNn70 << "n70" << k;
        ostringstream HNn70SS; HNn70SS << "n70SS" << k;
        n70.push_back(new TH1F (HNn70.str().c_str(),"InvMa",18,0,18)); n70[k]->Sumw2();
        n70SS.push_back(new TH1F (HNn70SS.str().c_str(),"InvMa",18,0,18)); n70SS[k]->Sumw2();

        ostringstream HNS0CRQCD; HNS0CRQCD << "h0_CR_QCD" << k;
        ostringstream HNS1CRQCD; HNS1CRQCD << "h1_CR_QCD" << k;
        ostringstream HNS2CRQCD; HNS2CRQCD << "h2_CR_QCD" << k;
        h0_CR_QCD.push_back(new TH1F (HNS0CRQCD.str().c_str(),"I",4,40,200)); h0_CR_QCD[k]->Sumw2();
        h1_CR_QCD.push_back(new TH1F (HNS1CRQCD.str().c_str(),"I",4,40,200)); h1_CR_QCD[k]->Sumw2();
        h2_CR_QCD.push_back(new TH1F (HNS2CRQCD.str().c_str(),"I",4,40,200)); h2_CR_QCD[k]->Sumw2();

        ostringstream HNS0CRW; HNS0CRW << "h0_CR_W" << k;
        ostringstream HNS1CRW; HNS1CRW << "h1_CR_W" << k;
        ostringstream HNS2CRW; HNS2CRW << "h2_CR_W" << k;
        h0_CR_W.push_back(new TH1F (HNS0CRW.str().c_str(),"I",1,80,200)); h0_CR_W[k]->Sumw2();
        h1_CR_W.push_back(new TH1F (HNS1CRW.str().c_str(),"I",1,80,200)); h1_CR_W[k]->Sumw2();
        h2_CR_W.push_back(new TH1F (HNS2CRW.str().c_str(),"I",1,80,200)); h2_CR_W[k]->Sumw2();

        ostringstream HNS0CRSSQCD; HNS0CRSSQCD << "h0_CRSS_QCD" << k;
        ostringstream HNS1CRSSQCD; HNS1CRSSQCD << "h1_CRSS_QCD" << k;
        ostringstream HNS2CRSSQCD; HNS2CRSSQCD << "h2_CRSS_QCD" << k;
        h0_CRSS_QCD.push_back(new TH1F (HNS0CRSSQCD.str().c_str(),"I",4,40,200)); h0_CRSS_QCD[k]->Sumw2();
        h1_CRSS_QCD.push_back(new TH1F (HNS1CRSSQCD.str().c_str(),"I",4,40,200)); h1_CRSS_QCD[k]->Sumw2();
        h2_CRSS_QCD.push_back(new TH1F (HNS2CRSSQCD.str().c_str(),"I",4,40,200)); h2_CRSS_QCD[k]->Sumw2();

        ostringstream HNS0CRSSW; HNS0CRSSW << "h0_CRSS_W" << k;
        ostringstream HNS1CRSSW; HNS1CRSSW << "h1_CRSS_W" << k;
        ostringstream HNS2CRSSW; HNS2CRSSW << "h2_CRSS_W" << k;
        h0_CRSS_W.push_back(new TH1F (HNS0CRSSW.str().c_str(),"I",1,80,200)); h0_CRSS_W[k]->Sumw2();
        h1_CRSS_W.push_back(new TH1F (HNS1CRSSW.str().c_str(),"I",1,80,200)); h1_CRSS_W[k]->Sumw2();
        h2_CRSS_W.push_back(new TH1F (HNS2CRSSW.str().c_str(),"I",1,80,200)); h2_CRSS_W[k]->Sumw2();
   }

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0OS; HNS0OS << "h0_OS" << k;
        ostringstream HNS1OS; HNS1OS << "h1_OS" << k;
        h0_OS.push_back(new TH1F (HNS0OS.str().c_str(),"InvMa",binnum0,bins0)); h0_OS[k]->Sumw2();
        h1_OS.push_back(new TH1F (HNS1OS.str().c_str(),"InvMa",binnum1,bins1)); h1_OS[k]->Sumw2();

        ostringstream HNS0SS; HNS0OS << "h0_SS" << k;
        ostringstream HNS1SS; HNS1OS << "h1_SS" << k;
        h0_SS.push_back(new TH1F (HNS0SS.str().c_str(),"InvMa",binnum0,bins0)); h0_SS[k]->Sumw2();
        h1_SS.push_back(new TH1F (HNS1SS.str().c_str(),"InvMa",binnum1,bins1)); h1_SS[k]->Sumw2();

        ostringstream HNS0QCD; HNS0QCD << "h0_QCD" << k;
        ostringstream HNS1QCD; HNS1QCD << "h1_QCD" << k;
        h0_QCD.push_back(new TH1F (HNS0QCD.str().c_str(),"InvMa",binnum0,bins0)); h0_QCD[k]->Sumw2();
        h1_QCD.push_back(new TH1F (HNS1QCD.str().c_str(),"InvMa",binnum1,bins1)); h1_QCD[k]->Sumw2();

        ostringstream HNS0WSS; HNS0WSS << "h0_WSS" << k;
        ostringstream HNS1WSS; HNS1WSS << "h1_WSS" << k;
        h0_WSS.push_back(new TH1F (HNS0WSS.str().c_str(),"InvMa",binnum0,bins0)); h0_WSS[k]->Sumw2();
        h1_WSS.push_back(new TH1F (HNS1WSS.str().c_str(),"InvMa",binnum1,bins1));h1_WSS[k]->Sumw2();

        ostringstream HNS0WOS; HNS0WOS << "h0_WOS" << k;
        ostringstream HNS1WOS; HNS1WOS << "h1_WOS" << k;
        h0_WOS.push_back(new TH1F (HNS0WOS.str().c_str(),"InvMa",binnum0,bins0)); h0_WOS[k]->Sumw2();
        h1_WOS.push_back(new TH1F (HNS1WOS.str().c_str(),"InvMa",binnum1,bins1)); h1_WOS[k]->Sumw2();
   }


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

   TString postfixTES[12]={"_CMS_scale_t_13TeVDown","_CMS_scale_t_13TeVUp","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_scale_met_clustered_13TeVDown","_CMS_scale_met_clustered_13TeVUp"};
   TString postfixDM[6]={"_CMS_tauDMReco_1prong_13TeVUp","_CMS_tauDMReco_1prong_13TeVDown","_CMS_tauDMReco_1prong1pizero_13TeVUp","_CMS_tauDMReco_1prong1pizero_13TeVDown","_CMS_tauDMReco_3prong_13TeVUp","_CMS_tauDMReco_3prong_13TeVDown"};
   TString postfixFakeDM[6]={"_CMS_jetToTauDMReco_1prong_13TeVUp","_CMS_jetToTauDMReco_1prong_13TeVDown","_CMS_jetToTauDMReco_1prong1pizero_13TeVUp","_CMS_jetToTauDMReco_1prong1pizero_13TeVDown","_CMS_jetToTauDMReco_3prong_13TeVUp","_CMS_jetToTauDMReco_3prong_13TeVDown"};
   TString postfixZLshape[12]={"_CMS_htt_ZLShape_mt_13TeVUp","_CMS_htt_ZLShape_mt_13TeVDown","_CMS_ZLShape_mt_0jet_1prong_13TeVUp","_CMS_ZLShape_mt_0jet_1prong_13TeVDown","_CMS_ZLShape_mt_0jet_1prong1pizero_13TeVUp","_CMS_ZLShape_mt_0jet_1prong1pizero_13TeVDown","_CMS_ZLShape_mt_1prong_13TeVUp","_CMS_ZLShape_mt_1prong_13TeVDown", "_CMS_ZLShape_mt_1prong1pizero_13TeVUp","_CMS_ZLShape_mt_1prong1pizero_13TeVDown","_CMS_ZLShape_mt_3prong_13TeVUp","_CMS_ZLShape_mt_3prong_13TeVDown"};
   TString postfixZLnorm[4]={"_CMS_mFakeTau_1prong_13TeVUp","_CMS_mFakeTau_1prong_13TeVDown","_CMS_mFakeTau_1prong1pizero_13TeVUp","_CMS_mFakeTau_1prong1pizero_13TeVDown"};
   TString postfixJES[56]={"_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	bool isSingleLep = (passIsoMu22 && matchIsoMu22_1 && filterIsoMu22_1) or (passIsoTkMu22 && matchIsoTkMu22_1 && filterIsoTkMu22_1) or (passIsoMu22eta2p1 && matchIsoMu22eta2p1_1 && filterIsoMu22eta2p1_1) or (passIsoTkMu22eta2p1 && matchIsoTkMu22eta2p1_1 && filterIsoTkMu22eta2p1_1);
	bool isCrossTrigger = (passIsoMu19Tau20 && matchIsoMu19Tau20_1 && filterIsoMu19Tau20_1 && matchIsoMu19Tau20_2 && filterIsoMu19Tau20_2);

        if (sample=="data_obs" && run<278820 && !id_m_medium2016_1) continue;
        if (sample=="data_obs" && run>=278820 && !id_m_medium_1) continue;
	if (pt_1<20) continue;
        if (fabs(eta_1)>2.1) continue;
	if (sample!="embedded" && !isSingleLep && !isCrossTrigger) continue;
	if (sample!="embedded" && (!((isSingleLep && pt_1>23) or (isCrossTrigger && pt_1<=23)))) continue;
	if (!againstElectronVLooseMVA6_2 or !againstMuonTight3_2) continue;
        float sf_trg=1.0;
        float sf_id=1.0;
        float sf_id_anti=1.0;
	float sf_trg_anti=1.0;
	float eff_tau=1.0;
	float eff_tau_anti=1.0;

	if (sample!="data_obs"){
           sf_id=myScaleFactor_id->get_ScaleFactor(pt_1,eta_1);
           sf_id_anti=myScaleFactor_idAnti->get_ScaleFactor(pt_1,eta_1);
        }

	float ratioanti=(sf_id_anti)/(sf_id);

	float signalRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
	float qcdRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30);
        float wRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30);
        float wsfRegion=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
        float qcdCR=(byMediumIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.30 && iso_1>0.15);

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        //TLorentzVector mybjet1;
        //mybjet1.SetPtEtaPhiM(bptL_1,betaL_1,bphiL_1,0);
        //TLorentzVector mybjet2;
        //mybjet2.SetPtEtaPhiM(bptL_2,betaL_2,bphiL_2,0);
        TLorentzVector mybjet1;
        mybjet1.SetPtEtaPhiM(bpt_1,beta_1,bphi_1,0);
        TLorentzVector mybjet2;
        mybjet2.SetPtEtaPhiM(bpt_2,beta_2,bphi_2,0);
//cout<<bpt_1<<" "<<bpt_2<<" "<<bptT_1<<" "<<bptT_2<<" "<<bptL_1<<" "<<bptT_2<<endl;
        TLorentzVector mybjet1T;
        mybjet1T.SetPtEtaPhiM(bptT_1,betaT_1,bphiT_1,0);
        TLorentzVector mybjet2T;
        mybjet2T.SetPtEtaPhiM(bptT_2,betaT_2,bphiT_2,0);

        TLorentzVector mybjet1L;
        mybjet1L.SetPtEtaPhiM(bptL_1,betaL_1,bphiL_1,0);
        TLorentzVector mybjet2L;
        mybjet2L.SetPtEtaPhiM(bptL_2,betaL_2,bphiL_2,0);

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

	float correction=sf_id;
	if (sample!="embedded" && sample!="data_obs") correction=correction*LumiWeights_12->weight(npu);
        if (sample=="embedded" && amcatNLO_weight>1) amcatNLO_weight=0.10;
	float aweight=amcatNLO_weight*weight*correction;

        if (sample!="data_obs"){
           if (gen_match_2==5) aweight=aweight*0.95;
           if (gen_match_2==2 or gen_match_2==4){//Yiwen reminiaod
              if (fabs(eta_2)<0.4) aweight=aweight*1.263;
              else if (fabs(eta_2)<0.8) aweight=aweight*1.364;
              else if (fabs(eta_2)<1.2) aweight=aweight*0.854;
              else if (fabs(eta_2)<1.7) aweight=aweight*1.712;
              else if (fabs(eta_2)<2.3) aweight=aweight*2.324;
	      if (sample=="ZL" && l2_decayMode==0) aweight=aweight*0.74; //ZL corrections Laura
	      else if (sample=="ZL" && l2_decayMode==1) aweight=aweight*1.0;
           }
	   if (gen_match_2==1 or gen_match_2==3){//Yiwen
              if (fabs(eta_2)<1.460) aweight=aweight*1.213;
              else if (fabs(eta_2)>1.558) aweight=aweight*1.375;
           }
           //w->var("m_pt")->setVal(mymu.Pt());
           //w->var("m_eta")->setVal(mymu.Eta());
	   //aweight=aweight*w->function("m_trk_ratio")->getVal();
	   aweight=aweight*h_Trk->Eval(eta_1);
        }

        //if (sample=="EWKZLL" or sample=="EWKZNuNu" or sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ") aweight=aweight*1.02; //Zmumu correction

	if (sample=="EWKZLL" or sample=="EWKZNuNu" or sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ"){
	    float zpt_corr=histZ->GetBinContent(histZ->GetXaxis()->FindBin(genM),histZ->GetYaxis()->FindBin(genpT));
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
        if ((sample=="TTT" or sample=="ZTT") && gen_match_2!=5) continue;
        if ((sample=="TTJ" or sample=="ZLL") && gen_match_2==5) continue;
        if (sample=="ZJ" && gen_match_2!=6) continue;

	// #############################################################
     	// ################### Top pT reweighting ######################
     	// #############################################################
	float pttop1=pt_top1;
        if (pttop1>400) pttop1=400;
        float pttop2=pt_top2;
        if (pttop2>400) pttop2=400;
        if ((sample=="TTJ" or sample=="TTT" or sample=="TT") && fabs(tes)!=11) aweight*=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));
        if ((sample=="TTJ" or sample=="TTT" or sample=="TT") && tes==11) aweight*=(1+2*(sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2))-1));

	if (sample=="data_obs") aweight=1.0;

	float weight_btag=1.0;
        if (sample!="data_obs"){
            int nbtagged=nbtag;
            if (nbtagged>2) nbtagged=2;
            weight_btag=bTagEventWeight(nbtagged,bpt_1,bflavor_1,bpt_2,bflavor_2,1,0,1) + bTagEventWeight(nbtagged,bpt_1,bflavor_1,bpt_2,bflavor_2,1,0,2);
            if (nbtagged>2) weight_btag=0;
        }
	aweight=aweight*weight_btag;
	//bool is_bveto=(sample!="data_obs" or nbtagL==0);
	if (sample=="data_obs" && nbtag<1) continue;
cout<<"2"<<endl;

	// ############################################################
	// ############### Loop over JES sources ######################
	// ############################################################
	//
	int nombrejets[56]={njets_JESDown,njets_JESUp,njets_JetAbsoluteFlavMapDown,njets_JetAbsoluteFlavMapUp,njets_JetAbsoluteMPFBiasDown,njets_JetAbsoluteMPFBiasUp,njets_JetAbsoluteScaleDown,njets_JetAbsoluteScaleUp,njets_JetAbsoluteStatDown,njets_JetAbsoluteStatUp,njets_JetFlavorQCDDown,njets_JetFlavorQCDUp,njets_JetFragmentationDown,njets_JetFragmentationUp,njets_JetPileUpDataMCDown,njets_JetPileUpDataMCUp,njets_JetPileUpPtBBDown,njets_JetPileUpPtBBUp,njets_JetPileUpPtEC1Down,njets_JetPileUpPtEC1Up,njets_JetPileUpPtEC2Down,njets_JetPileUpPtEC2Up,njets_JetPileUpPtHFDown,njets_JetPileUpPtHFUp,njets_JetPileUpPtRefDown,njets_JetPileUpPtRefUp,njets_JetRelativeBalDown,njets_JetRelativeBalUp,njets_JetRelativeFSRDown,njets_JetRelativeFSRUp,njets_JetRelativeJEREC1Down,njets_JetRelativeJEREC1Up,njets_JetRelativeJEREC2Down,njets_JetRelativeJEREC2Up,njets_JetRelativeJERHFDown,njets_JetRelativeJERHFUp,njets_JetRelativePtBBDown,njets_JetRelativePtBBUp,njets_JetRelativePtEC1Down,njets_JetRelativePtEC1Up,njets_JetRelativePtEC2Down,njets_JetRelativePtEC2Up,njets_JetRelativePtHFDown,njets_JetRelativePtHFUp,njets_JetRelativeStatECDown,njets_JetRelativeStatECUp,njets_JetRelativeStatFSRDown,njets_JetRelativeStatFSRUp,njets_JetRelativeStatHFDown,njets_JetRelativeStatHFUp,njets_JetSinglePionECALDown,njets_JetSinglePionECALUp,njets_JetSinglePionHCALDown,njets_JetSinglePionHCALUp,njets_JetTimePtEtaDown,njets_JetTimePtEtaUp};

	float massejets[56]={mjj_JESDown,mjj_JESUp,mjj_JetAbsoluteFlavMapDown,mjj_JetAbsoluteFlavMapUp,mjj_JetAbsoluteMPFBiasDown,mjj_JetAbsoluteMPFBiasUp,mjj_JetAbsoluteScaleDown,mjj_JetAbsoluteScaleUp,mjj_JetAbsoluteStatDown,mjj_JetAbsoluteStatUp,mjj_JetFlavorQCDDown,mjj_JetFlavorQCDUp,mjj_JetFragmentationDown,mjj_JetFragmentationUp,mjj_JetPileUpDataMCDown,mjj_JetPileUpDataMCUp,mjj_JetPileUpPtBBDown,mjj_JetPileUpPtBBUp,mjj_JetPileUpPtEC1Down,mjj_JetPileUpPtEC1Up,mjj_JetPileUpPtEC2Down,mjj_JetPileUpPtEC2Up,mjj_JetPileUpPtHFDown,mjj_JetPileUpPtHFUp,mjj_JetPileUpPtRefDown,mjj_JetPileUpPtRefUp,mjj_JetRelativeBalDown,mjj_JetRelativeBalUp,mjj_JetRelativeFSRDown,mjj_JetRelativeFSRUp,mjj_JetRelativeJEREC1Down,mjj_JetRelativeJEREC1Up,mjj_JetRelativeJEREC2Down,mjj_JetRelativeJEREC2Up,mjj_JetRelativeJERHFDown,mjj_JetRelativeJERHFUp,mjj_JetRelativePtBBDown,mjj_JetRelativePtBBUp,mjj_JetRelativePtEC1Down,mjj_JetRelativePtEC1Up,mjj_JetRelativePtEC2Down,mjj_JetRelativePtEC2Up,mjj_JetRelativePtHFDown,mjj_JetRelativePtHFUp,mjj_JetRelativeStatECDown,mjj_JetRelativeStatECUp,mjj_JetRelativeStatFSRDown,mjj_JetRelativeStatFSRUp,mjj_JetRelativeStatHFDown,mjj_JetRelativeStatHFUp,mjj_JetSinglePionECALDown,mjj_JetSinglePionECALUp,mjj_JetSinglePionHCALDown,mjj_JetSinglePionHCALUp,mjj_JetTimePtEtaDown,mjj_JetTimePtEtaUp};
        TLorentzVector myrawmet;
        myrawmet.SetPtEtaPhiM(met,0,metphi,0);
	TLorentzVector myrawtau=mytau;
	float ratioantiraw=ratioanti;

	for (int k=0; k<nbhist; ++k){

            int numberJets=nombrejets[k];
            float massJets=massejets[k];
	    if (tes!=100) numberJets=njets;
            if (tes!=100) massJets=mjj;
	    float weight2=1.0;

	    TLorentzVector mymet=myrawmet;
	    mytau=myrawtau;

	    if (tes==1 && gen_match_2==5){
	       if (k==0){ mytau*=0.988; mymet=mymet+(0.012/0.988)*mytau;}
               if (k==1){ mytau*=1.012; mymet=mymet-(0.012/1.012)*mytau;}
               if (k==2 && l2_decayMode==0){ mytau*=0.988; mymet=mymet+(0.012/0.988)*mytau;}
               if (k==3 && l2_decayMode==0){ mytau*=1.012; mymet=mymet-(0.012/1.012)*mytau;}
               if (k==4 && l2_decayMode==1){ mytau*=0.988; mymet=mymet+(0.012/0.988)*mytau;}
               if (k==5 && l2_decayMode==1){ mytau*=1.012; mymet=mymet-(0.012/1.012)*mytau;}
               if (k==6 && l2_decayMode==10){ mytau*=0.988; mymet=mymet+(0.012/0.988)*mytau;}
               if (k==7 && l2_decayMode==10){ mytau*=1.012; mymet=mymet-(0.012/1.012)*mytau;}
	    }

            if (tes==1){
               if (k==8){ mymet.SetPtEtaPhiM(met_UESDown,0,metphi_UESDown,0);}
               else if (k==9){ mymet.SetPtEtaPhiM(met_UESUp,0,metphi_UESUp,0);}
               else if (k==10){ mymet.SetPtEtaPhiM(met_JESDown,0,metphi_JESDown,0);}
               else if (k==11){ mymet.SetPtEtaPhiM(met_JESUp,0,metphi_JESUp,0);}
            }

	   if (tes==15 && sample=="ZL"){mytau*=1.015; mymet=mymet-(0.015/1.015)*mytau;}
           if (tes==-15 && sample=="ZL"){ mytau*=0.985; mymet=mymet+(0.015/0.985)*mytau;}
	    float dm_weight=1.0;
            if (tes==16 && gen_match_2==5){
                if (k==0 && l2_decayMode==0) dm_weight=1.03;
                else if (k==1 && l2_decayMode==0) dm_weight=0.97;
                else if (k==2 && l2_decayMode==1) dm_weight=1.03;
                else if (k==3 && l2_decayMode==1) dm_weight=0.97;
                else if (k==4 && l2_decayMode==10) dm_weight=1.03;
                else if (k==5 && l2_decayMode==10) dm_weight=0.97;
            }
            if (tes==19 && gen_match_2==6){
                if (k==0 && l2_decayMode==0) dm_weight=1.20;
                else if (k==1 && l2_decayMode==0) dm_weight=0.80;
                else if (k==2 && l2_decayMode==1) dm_weight=1.20;
                else if (k==3 && l2_decayMode==1) dm_weight=0.80;
                else if (k==4 && l2_decayMode==10) dm_weight=1.20;
                else if (k==5 && l2_decayMode==10) dm_weight=0.80;
            }

            if (tes==18 && sample=="ZL"){
                if (k==0 && l2_decayMode==0) dm_weight=1.25;
                else if (k==1 && l2_decayMode==0) dm_weight=0.75;
                else if (k==2 && l2_decayMode==1) dm_weight=1.25;
                else if (k==3 && l2_decayMode==1) dm_weight=0.75;
            }

            if (tes==17 && sample=="ZL"){
                if (k==0){ 
		     mytau*=1.015; 
		     mymet=mymet-(0.015/1.015)*mytau;
		}
                else if (k==1) { 
		     mytau*=0.985; 
		     mymet=mymet+(0.015/0.985)*mytau;
		}
                if (k==6 && l2_decayMode==0){ 
                     mytau*=1.015; 
                     mymet=mymet-(0.015/1.015)*mytau;
                }
                else if (k==7 && l2_decayMode==0) { 
                     mytau*=0.985; 
                     mymet=mymet+(0.015/0.985)*mytau;
                }
                if (k==8 && l2_decayMode==1){ 
                     mytau*=1.015; 
                     mymet=mymet-(0.015/1.015)*mytau;
                }
                else if (k==9 && l2_decayMode==1) { 
                     mytau*=0.985; 
                     mymet=mymet+(0.015/0.985)*mytau;
                }
                if (k==10 && l2_decayMode==10){ 
                     mytau*=1.015; 
                     mymet=mymet-(0.015/1.015)*mytau;
                }
                else if (k==11 && l2_decayMode==10) { 
                     mytau*=0.985; 
                     mymet=mymet+(0.015/0.985)*mytau;
                }
            }

	    if (mytau.Pt()<20) continue;

            float mt=TMass_F(mymu.Pt(),mymet.Pt(),mymu.Px(),mymet.Px(),mymu.Py(),mymet.Py());
            float mt2=TMass_F(mytau.Pt(),mymet.Pt(),mytau.Px(),mymet.Px(),mytau.Py(),mymet.Py());
	    float mbbtt=(mymu+mytau+mybjet1).M();
	    float var=100*fabs(mymet.DeltaPhi(mymu+mytau));//(mymu+mytau).M();

        float norm_zeta=norm_F(mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt(),mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(mymu.Px()+mytau.Px())*x_zeta+(mymu.Py()+mytau.Py())*y_zeta;
	float pzeta=p_zeta_mis-0.85*pzeta_vis;

	var=100*njets;//(mytau+mymu).M();//100*fabs((mybjet1.Pt())/(mymu.Pt()+mytau.Pt()));//mt2;//mymet.Pt();//100*fabs(mymet.DeltaPhi(mybjet1));//sqrt(mybjet1.DeltaPhi(mymu+mytau)*mybjet1.DeltaPhi(mymu+mytau)+(mybjet1.Eta()-(mymu+mytau).Eta())*(mybjet1.Eta()-(mymu+mytau).Eta()));
cout<<"3"<<endl;
            if (sample!="embedded" && sample!="data_obs"){
	       if (mymu.Pt()<23){ 
                   w2->var("t_pt")->setVal(mytau.Pt());
                   w2->var("t_eta")->setVal(mytau.Eta());
                   w2->var("t_dm")->setVal(l2_decayMode);
                   float eff_tau_ratio = w2->function("t_genuine_TightIso_mt_ratio")->getVal();
		   sf_trg=myScaleFactor_trgMu19Leg->get_ScaleFactor(pt_1,eta_1)*eff_tau_ratio;
		   sf_trg_anti=myScaleFactor_trgMu19LegAnti->get_ScaleFactor(pt_1,eta_1)*eff_tau_ratio;
	       }
	       else{
		   sf_trg=myScaleFactor_trgMu22->get_ScaleFactor(pt_1,eta_1);
                   sf_trg_anti=myScaleFactor_trgMu22Anti->get_ScaleFactor(pt_1,eta_1);
	       }
	    }
            if (sample=="embedded"){
               if (mymu.Pt()<23){ 
                   float eff_tau_ratio = w2->function("t_genuine_TightIso_mt_data")->getVal();
                   sf_trg=myScaleFactor_trgMu19Leg->get_EfficiencyData(pt_1,eta_1)*eff_tau_ratio;
                   sf_trg_anti=myScaleFactor_trgMu19LegAnti->get_EfficiencyData(pt_1,eta_1)*eff_tau_ratio;
               }
               else{
                   sf_trg=myScaleFactor_trgMu22->get_EfficiencyData(pt_1,eta_1);
                   sf_trg_anti=myScaleFactor_trgMu22Anti->get_EfficiencyData(pt_1,eta_1);
               }
            }

	    if (sample=="data_obs") {aweight=1.0; weight2=1.0;}
            weight2=weight2*sf_trg*dm_weight;
            ratioanti=ratioantiraw*sf_trg_anti/(sf_trg+0.000000001);

	    bool is_all=true;
	    bool is_low=(mbbtt<90 and mymet.Pt()<80 and pzeta>-80 and mt<60);

	    //************************* Fill histograms **********************

if (nbtag15>=2 and (mymu+mytau+mybjet1+mybjet2).M()<120) acc->Fill(0.5);
if (nbtag15>=2 and (mymu+mytau+mybjet1+mybjet2).M()>=120) acc->Fill(1.5);
if (nbtag15==1 and (mymu+mytau+mybjet1).M()<90) acc->Fill(2.5);
if (nbtag15==1 and (mymu+mytau+mybjet1).M()>=90) acc->Fill(3.5);

if (nbtag>=2 and (mymu+mytau+mybjet1+mybjet2).M()<120) acc->Fill(5.5);
if (nbtag>=2 and (mymu+mytau+mybjet1+mybjet2).M()>=120) acc->Fill(6.5);
if (nbtag==1 and (mymu+mytau+mybjet1).M()<90) acc->Fill(7.5);
if (nbtag==1 and (mymu+mytau+mybjet1).M()>=90) acc->Fill(8.5);

if (nbtag15L>=2 and (mymu+mytau+mybjet1L+mybjet2L).M()<120) acc->Fill(10.5);
if (nbtag15L>=2) masse->Fill((mymu+mytau+mybjet1L+mybjet2L).M());
if (nbtag15L>=2 and (mymu+mytau+mybjet1L+mybjet2L).M()>=120) acc->Fill(11.5);
if (nbtag15L==1 and (mymu+mytau+mybjet1L).M()<90) acc->Fill(12.5);
if (nbtag15L==1 and (mymu+mytau+mybjet1L).M()>=90) acc->Fill(13.5);

if (nbtagL>=2 and (mymu+mytau+mybjet1L+mybjet2L).M()<120) acc->Fill(15.5);
if (nbtagL>=2 and (mymu+mytau+mybjet1L+mybjet2L).M()>=120) acc->Fill(16.5);
if (nbtagL==1 and (mymu+mytau+mybjet1L).M()<90) acc->Fill(17.5);
if (nbtagL==1 and (mymu+mytau+mybjet1L).M()>=90) acc->Fill(18.5);
if (nbtag>=1 and !(nbtagL>=2 and (mymu+mytau+mybjet1L+mybjet2L).M()<120) and (mymu+mytau+mybjet1).M()<90) acc->Fill(19.5);

if (nbtag15T>=2 and (mymu+mytau+mybjet1T+mybjet2T).M()<120) acc->Fill(20.5);
if (nbtag15T>=2 and (mymu+mytau+mybjet1T+mybjet2T).M()>=120) acc->Fill(21.5);
if (nbtag15T==1 and (mymu+mytau+mybjet1T).M()<90) acc->Fill(22.5);
if (nbtag15T==1 and (mymu+mytau+mybjet1T).M()>=90) acc->Fill(23.5);

if (nbtagT>=2 and (mymu+mytau+mybjet1T+mybjet2T).M()<120) acc->Fill(25.5);
if (nbtagT>=2 and (mymu+mytau+mybjet1T+mybjet2T).M()>=120) acc->Fill(26.5);
if (nbtagT==1 and (mymu+mytau+mybjet1T).M()<90) acc->Fill(27.5);
if (nbtagT==1 and (mymu+mytau+mybjet1T).M()>=90) acc->Fill(28.5);

	    if (is_all){
                if (signalRegion && q_1*q_2<0){
                    h0_OS[k]->Fill(var,weight2*aweight);
		}
                if (signalRegion && q_1*q_2>0)
                    h0_SS[k]->Fill(var,weight2*aweight);
                if (wRegion && q_1*q_2<0)
                    h0_WOS[k]->Fill(var,weight2*aweight);
                if (wRegion && q_1*q_2>0)
                    h0_WSS[k]->Fill(var,weight2*aweight);
                if (qcdRegion && q_1*q_2>0)
                    h0_QCD[k]->Fill(var,weight2*aweight);
	    }

            if (is_low){
                if (signalRegion && q_1*q_2<0){
                    h1_OS[k]->Fill(var,weight2*aweight);
		}
                if (signalRegion && q_1*q_2>0)
                    h1_SS[k]->Fill(var,weight2*aweight);
                if (wRegion && q_1*q_2<0)
                    h1_WOS[k]->Fill(var,weight2*aweight);
                if (wRegion && q_1*q_2>0)
                    h1_WSS[k]->Fill(var,weight2*aweight);
                if (qcdRegion && q_1*q_2>0)
                    h1_QCD[k]->Fill(var,weight2*aweight);
            }
	}
				
    } // end of loop over events

    for (int k=0; k<nbhist; ++k){
cout<<h0_WOS[k]->Integral()<<endl;
       h0_WOS[k]->Scale(h0_OS[k]->Integral()/h0_WOS[k]->Integral());
       h1_WOS[k]->Scale(h1_OS[k]->Integral()/h1_WOS[k]->Integral());
       h0_WSS[k]->Scale(h0_SS[k]->Integral()/h0_WSS[k]->Integral());
       h1_WSS[k]->Scale(h1_SS[k]->Integral()/h1_WSS[k]->Integral());
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    hincl->Write();
acc->Write();
masse->Write();

    TString postfix="";
    if (tes==1)
	postfix="_CMS_scale_t_mt_13TeVUp";
    if (tes==-1)
        postfix="_CMS_scale_t_mt_13TeVDown";
    if (tes==15)
        postfix="_CMS_htt_ZLShape_mt_13TeVUp";
    if (tes==-15)
        postfix="_CMS_htt_ZLShape_mt_13TeVDown";
    if (tes==3)
        postfix="_CMS_scale_met_13TeVUp";
    if (tes==-3)
        postfix="_CMS_scale_met_13TeVDown";
    if (tes==100)
        postfix="_CMS_scale_j_13TeVUp";
    if (tes==-100)
        postfix="_CMS_scale_j_13TeVDown";
    if (tes==12)
        postfix="_CMS_scale_gg_13TeVUp";
    if (tes==-12)
        postfix="_CMS_scale_gg_13TeVDown";
    if (tes==22)
        postfix="_TopMassTreatment_13TeVUp";
    if (tes==-22)
        postfix="_TopMassTreatment_13TeVDown";
    if (tes==11)
        postfix="_CMS_htt_ttbarShape_13TeVUp";
    if (tes==-11)
        postfix="_CMS_htt_ttbarShape_13TeVDown";
    if (tes==-13)
        postfix="_CMS_htt_zmumuShape_VBF_13TeVDown";
    if (tes==13)
        postfix="_CMS_htt_zmumuShape_VBF_13TeVUp";
    if (tes==10)
        postfix="_CMS_htt_dyShape_13TeVUp";
    if (tes==-10)
        postfix="_CMS_htt_dyShape_13TeVDown";
    if (tes==-14)
        postfix="_CMS_htt_jetToTauFake_13TeVDown";
    if (tes==14)
        postfix="_CMS_htt_jetToTauFake_13TeVUp";

    TDirectory *OS0jet =fout->mkdir("mt_all");
    TDirectory *SS0jet =fout->mkdir("SSall");
    TDirectory *QCD0jet =fout->mkdir("QCDall");
    TDirectory *OS1jet =fout->mkdir("mt_low");
    TDirectory *SS1jet =fout->mkdir("SSlow");
    TDirectory *QCD1jet =fout->mkdir("QCDlow");

    if (nbhist==1) postfixJES[0]=postfix;

    for (int k=0; k<nbhist; ++k){

        if (tes==100) postfix=postfixJES[k];
        if (tes==1) postfix=postfixTES[k];
        if (tes==16) postfix=postfixDM[k];
        if (tes==17) postfix=postfixZLshape[k];
        if (tes==18) postfix=postfixZLnorm[k];
        if (tes==19) postfix=postfixFakeDM[k];

        fout->cd();
        n70[k]->SetName("n70"+postfix);
        n70[k]->Write();
        n70SS[k]->SetName("n70SS"+postfix);
        n70SS[k]->Write();
    }

    for (int k=0; k<nbhist; ++k){

       if (tes==100) postfix=postfixJES[k];
       if (tes==1) postfix=postfixTES[k];
       if (tes==16) postfix=postfixDM[k];
       if (tes==17) postfix=postfixZLshape[k];
       if (tes==18) postfix=postfixZLnorm[k];
       if (tes==19) postfix=postfixFakeDM[k];

       for (int nn=1; nn<h0_OS[k]->GetSize()-1; ++nn){
           if (h0_OS[k]->GetBinContent(nn)<0) h0_OS[k]->SetBinContent(nn,0.00001);
           if (h0_SS[k]->GetBinContent(nn)<0) h0_SS[k]->SetBinContent(nn,0.00001);
           if (h0_QCD[k]->GetBinContent(nn)<0) h0_QCD[k]->SetBinContent(nn,0.00001);
           if (h0_WOS[k]->GetBinContent(nn)<0) h0_WOS[k]->SetBinContent(nn,0.00001);
           if (h0_WSS[k]->GetBinContent(nn)<0) h0_WSS[k]->SetBinContent(nn,0.00001);
           if (h1_OS[k]->GetBinContent(nn)<0) h1_OS[k]->SetBinContent(nn,0.00001);
           if (h1_SS[k]->GetBinContent(nn)<0) h1_SS[k]->SetBinContent(nn,0.00001);
           if (h1_QCD[k]->GetBinContent(nn)<0) h1_QCD[k]->SetBinContent(nn,0.00001);
           if (h1_WOS[k]->GetBinContent(nn)<0) h1_WOS[k]->SetBinContent(nn,0.00001);
           if (h1_WSS[k]->GetBinContent(nn)<0) h1_WSS[k]->SetBinContent(nn,0.00001);
       }

       OS0jet->cd();
       h0_OS[k]->SetName(name.c_str()+postfix);
       h0_WOS[k]->SetName(name.c_str()+postfix);
       h0_OS[k]->Write();

       SS0jet->cd();
       h0_SS[k]->SetName(name.c_str()+postfix);
       h0_WSS[k]->SetName(name.c_str()+postfix);
       h0_SS[k]->Write();

       QCD0jet->cd();
       h0_QCD[k]->SetName(name.c_str()+postfix);
       h0_QCD[k]->Write();

       OS1jet->cd();
       h1_OS[k]->SetName(name.c_str()+postfix);
       h1_WOS[k]->SetName(name.c_str()+postfix);
       if (sample=="W")
          h1_WOS[k]->Write();
       else
          h1_OS[k]->Write();

       SS1jet->cd();
       h1_SS[k]->SetName(name.c_str()+postfix);
       h1_WSS[k]->SetName(name.c_str()+postfix);
       if (sample=="W")
          h1_WSS[k]->Write();
       else
          h1_SS[k]->Write();

       QCD1jet->cd();
       h1_QCD[k]->SetName(name.c_str()+postfix);
       h1_QCD[k]->Write();

    }
cout<<h0_OS[0]->Integral()<<" "<<h1_OS[0]->Integral()<<endl;
    fout->Close();
} 


