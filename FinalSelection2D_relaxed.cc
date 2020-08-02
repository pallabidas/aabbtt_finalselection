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


   float bins0[] = {0,20,40,60,80,100,120,140,160,180,200}; //gt120
   float bins1[] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,115};//100-120
   float bins2[] = {10,15,20,25,30,35,40,45,50,55,60,65,70,95};//80-100
   float bins3[] = {10,15,20,25,30,35,40,45,50,55,75};//lt80


/*   float bins0[] = {0,60,120,180}; //gt120
   float bins1[] = {10,15,20,25,30,35,40,45,50,55,60,115};//100-120
   float bins2[] = {10,15,20,25,30,35,40,45,50,55,60,95};//80-100
   float bins3[] = {10,15,20,25,30,35,40,45,50,55,60,75};//lt80
*/

   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum2 = sizeof(bins2)/sizeof(Float_t) - 1;
   int  binnum3 = sizeof(bins3)/sizeof(Float_t) - 1;

   TH1F *hincl=new TH1F ("hincl", "hincl", 16,0,160); hincl->Sumw2();
   TH1F *nlowhigh=new TH1F ("nlowhigh", "nlowhigh", 6,0,6);nlowhigh->Sumw2();

   std::vector<TH1F*> n70;
   std::vector<TH1F*> n70SS;

   std::vector<TH1F*> h0_OS;
   std::vector<TH1F*> h1_OS;
   std::vector<TH1F*> h0_SS;
   std::vector<TH1F*> h1_SS;
   std::vector<TH1F*> h0_AI;
   std::vector<TH1F*> h1_AI;
   std::vector<TH1F*> h0_QCD;
   std::vector<TH1F*> h1_QCD;
   std::vector<TH1F*> h0_WOS;
   std::vector<TH1F*> h1_WOS;
   std::vector<TH1F*> h0_WSS;
   std::vector<TH1F*> h1_WSS;

   std::vector<TH1F*> h2_OS;
   std::vector<TH1F*> h3_OS;
   std::vector<TH1F*> h2_SS;
   std::vector<TH1F*> h3_SS;
   std::vector<TH1F*> h2_AI;
   std::vector<TH1F*> h3_AI;
   std::vector<TH1F*> h2_QCD;
   std::vector<TH1F*> h3_QCD;
   std::vector<TH1F*> h2_WOS;
   std::vector<TH1F*> h3_WOS;
   std::vector<TH1F*> h2_WSS;
   std::vector<TH1F*> h3_WSS;

   std::vector<TH1F*> h4_OS;
   std::vector<TH1F*> h5_OS;
   std::vector<TH1F*> h4_SS;
   std::vector<TH1F*> h5_SS;
   std::vector<TH1F*> h4_AI;
   std::vector<TH1F*> h5_AI;
   std::vector<TH1F*> h4_QCD;
   std::vector<TH1F*> h5_QCD;
   std::vector<TH1F*> h4_WOS;
   std::vector<TH1F*> h5_WOS;
   std::vector<TH1F*> h4_WSS;
   std::vector<TH1F*> h5_WSS;
   std::vector<TH1F*> h6_OS;
   std::vector<TH1F*> h6_SS;
   std::vector<TH1F*> h6_AI;
   std::vector<TH1F*> h6_QCD;
   std::vector<TH1F*> h6_WOS;
   std::vector<TH1F*> h6_WSS;

   int nbhist=1;

   for (int k=0; k<nbhist; ++k){
        ostringstream HNn70; HNn70 << "n70" << k;
        ostringstream HNn70SS; HNn70SS << "n70SS" << k;
        n70.push_back(new TH1F (HNn70.str().c_str(),"InvMa",18,0,18)); n70[k]->Sumw2();
        n70SS.push_back(new TH1F (HNn70SS.str().c_str(),"InvMa",18,0,18)); n70SS[k]->Sumw2();

   }

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0OS; HNS0OS << "h0_OS" << k;
        ostringstream HNS1OS; HNS1OS << "h1_OS" << k;
        h0_OS.push_back(new TH1F (HNS0OS.str().c_str(),"InvMa",binnum0,bins0)); h0_OS[k]->Sumw2();
        h1_OS.push_back(new TH1F (HNS1OS.str().c_str(),"InvMa",binnum1,bins1)); h1_OS[k]->Sumw2();
        ostringstream HNS2OS; HNS2OS << "h2_OS" << k;
        ostringstream HNS3OS; HNS3OS << "h3_OS" << k;
        h2_OS.push_back(new TH1F (HNS2OS.str().c_str(),"InvMa",binnum0,bins0)); h2_OS[k]->Sumw2();
        h3_OS.push_back(new TH1F (HNS3OS.str().c_str(),"InvMa",binnum1,bins1)); h3_OS[k]->Sumw2();
        ostringstream HNS4OS; HNS4OS << "h4_OS" << k;
        ostringstream HNS5OS; HNS5OS << "h5_OS" << k;
        ostringstream HNS6OS; HNS6OS << "h6_OS" << k;
        h4_OS.push_back(new TH1F (HNS4OS.str().c_str(),"InvMa",binnum3,bins3)); h4_OS[k]->Sumw2();
        h5_OS.push_back(new TH1F (HNS5OS.str().c_str(),"InvMa",binnum2,bins2)); h5_OS[k]->Sumw2();
        h6_OS.push_back(new TH1F (HNS6OS.str().c_str(),"InvMa",binnum1,bins1)); h6_OS[k]->Sumw2();

        ostringstream HNS0SS; HNS0OS << "h0_SS" << k;
        ostringstream HNS1SS; HNS1OS << "h1_SS" << k;
        h0_SS.push_back(new TH1F (HNS0SS.str().c_str(),"InvMa",binnum0,bins0)); h0_SS[k]->Sumw2();
        h1_SS.push_back(new TH1F (HNS1SS.str().c_str(),"InvMa",binnum1,bins1)); h1_SS[k]->Sumw2();
        ostringstream HNS2SS; HNS2OS << "h2_SS" << k;
        ostringstream HNS3SS; HNS3OS << "h3_SS" << k;
        h2_SS.push_back(new TH1F (HNS2SS.str().c_str(),"InvMa",binnum0,bins0)); h2_SS[k]->Sumw2();
        h3_SS.push_back(new TH1F (HNS3SS.str().c_str(),"InvMa",binnum1,bins1)); h3_SS[k]->Sumw2();
        ostringstream HNS4SS; HNS4SS << "h4_SS" << k;
        ostringstream HNS5SS; HNS5SS << "h5_SS" << k;
        ostringstream HNS6SS; HNS6SS << "h6_SS" << k;
        h4_SS.push_back(new TH1F (HNS4SS.str().c_str(),"InvMa",binnum3,bins3)); h4_SS[k]->Sumw2();
        h5_SS.push_back(new TH1F (HNS5SS.str().c_str(),"InvMa",binnum2,bins2)); h5_SS[k]->Sumw2();
        h6_SS.push_back(new TH1F (HNS6SS.str().c_str(),"InvMa",binnum1,bins1)); h6_SS[k]->Sumw2();

        ostringstream HNS0AI; HNS0OS << "h0_AI" << k;
        ostringstream HNS1AI; HNS1OS << "h1_AI" << k;
        h0_AI.push_back(new TH1F (HNS0AI.str().c_str(),"InvMa",binnum0,bins0)); h0_AI[k]->Sumw2();
        h1_AI.push_back(new TH1F (HNS1AI.str().c_str(),"InvMa",binnum1,bins1)); h1_AI[k]->Sumw2();
        ostringstream HNS2AI; HNS2OS << "h2_AI" << k;
        ostringstream HNS3AI; HNS3OS << "h3_AI" << k;
        h2_AI.push_back(new TH1F (HNS2AI.str().c_str(),"InvMa",binnum0,bins0)); h2_AI[k]->Sumw2();
        h3_AI.push_back(new TH1F (HNS3AI.str().c_str(),"InvMa",binnum1,bins1)); h3_AI[k]->Sumw2();
        ostringstream HNS4AI; HNS4AI << "h4_AI" << k;
        ostringstream HNS5AI; HNS5AI << "h5_AI" << k;
        ostringstream HNS6AI; HNS6AI << "h6_AI" << k;
        h4_AI.push_back(new TH1F (HNS4AI.str().c_str(),"InvMa",binnum3,bins3)); h4_AI[k]->Sumw2();
        h5_AI.push_back(new TH1F (HNS5AI.str().c_str(),"InvMa",binnum2,bins2)); h5_AI[k]->Sumw2();
        h6_AI.push_back(new TH1F (HNS6AI.str().c_str(),"InvMa",binnum1,bins1)); h6_AI[k]->Sumw2();

        ostringstream HNS0QCD; HNS0QCD << "h0_QCD" << k;
        ostringstream HNS1QCD; HNS1QCD << "h1_QCD" << k;
        h0_QCD.push_back(new TH1F (HNS0QCD.str().c_str(),"InvMa",binnum0,bins0)); h0_QCD[k]->Sumw2();
        h1_QCD.push_back(new TH1F (HNS1QCD.str().c_str(),"InvMa",binnum1,bins1)); h1_QCD[k]->Sumw2();
        ostringstream HNS2QCD; HNS2QCD << "h2_QCD" << k;
        ostringstream HNS3QCD; HNS3QCD << "h3_QCD" << k;
        h2_QCD.push_back(new TH1F (HNS2QCD.str().c_str(),"InvMa",binnum0,bins0)); h2_QCD[k]->Sumw2();
        h3_QCD.push_back(new TH1F (HNS3QCD.str().c_str(),"InvMa",binnum1,bins1)); h3_QCD[k]->Sumw2();
        ostringstream HNS4QCD; HNS4QCD << "h4_QCD" << k;
        ostringstream HNS5QCD; HNS5QCD << "h5_QCD" << k;
        ostringstream HNS6QCD; HNS6QCD << "h6_QCD" << k;
        h4_QCD.push_back(new TH1F (HNS4QCD.str().c_str(),"InvMa",binnum3,bins3)); h4_QCD[k]->Sumw2();
        h5_QCD.push_back(new TH1F (HNS5QCD.str().c_str(),"InvMa",binnum2,bins2)); h5_QCD[k]->Sumw2();
        h6_QCD.push_back(new TH1F (HNS6QCD.str().c_str(),"InvMa",binnum1,bins1)); h6_QCD[k]->Sumw2();

        ostringstream HNS0WSS; HNS0WSS << "h0_WSS" << k;
        ostringstream HNS1WSS; HNS1WSS << "h1_WSS" << k;
        h0_WSS.push_back(new TH1F (HNS0WSS.str().c_str(),"InvMa",binnum0,bins0)); h0_WSS[k]->Sumw2();
        h1_WSS.push_back(new TH1F (HNS1WSS.str().c_str(),"InvMa",binnum1,bins1));h1_WSS[k]->Sumw2();
        ostringstream HNS2WSS; HNS2WSS << "h2_WSS" << k;
        ostringstream HNS3WSS; HNS3WSS << "h3_WSS" << k;
        h2_WSS.push_back(new TH1F (HNS2WSS.str().c_str(),"InvMa",binnum0,bins0)); h2_WSS[k]->Sumw2();
        h3_WSS.push_back(new TH1F (HNS3WSS.str().c_str(),"InvMa",binnum1,bins1));h3_WSS[k]->Sumw2();
        ostringstream HNS4WSS; HNS4WSS << "h4_WSS" << k;
        ostringstream HNS5WSS; HNS5WSS << "h5_WSS" << k;
        ostringstream HNS6WSS; HNS6WSS << "h6_WSS" << k;
        h4_WSS.push_back(new TH1F (HNS4WSS.str().c_str(),"InvMa",binnum3,bins3)); h4_WSS[k]->Sumw2();
        h5_WSS.push_back(new TH1F (HNS5WSS.str().c_str(),"InvMa",binnum2,bins2)); h5_WSS[k]->Sumw2();
        h6_WSS.push_back(new TH1F (HNS6WSS.str().c_str(),"InvMa",binnum1,bins1)); h6_WSS[k]->Sumw2();

        ostringstream HNS0WOS; HNS0WOS << "h0_WOS" << k;
        ostringstream HNS1WOS; HNS1WOS << "h1_WOS" << k;
        h0_WOS.push_back(new TH1F (HNS0WOS.str().c_str(),"InvMa",binnum0,bins0)); h0_WOS[k]->Sumw2();
        h1_WOS.push_back(new TH1F (HNS1WOS.str().c_str(),"InvMa",binnum1,bins1)); h1_WOS[k]->Sumw2();
        ostringstream HNS2WOS; HNS2WOS << "h2_WOS" << k;
        ostringstream HNS3WOS; HNS3WOS << "h3_WOS" << k;
        h2_WOS.push_back(new TH1F (HNS2WOS.str().c_str(),"InvMa",binnum0,bins0)); h2_WOS[k]->Sumw2();
        h3_WOS.push_back(new TH1F (HNS3WOS.str().c_str(),"InvMa",binnum1,bins1)); h3_WOS[k]->Sumw2();
        ostringstream HNS4WOS; HNS4WOS << "h4_WOS" << k;
        ostringstream HNS5WOS; HNS5WOS << "h5_WOS" << k;
        ostringstream HNS6WOS; HNS6WOS << "h6_WOS" << k;
        h4_WOS.push_back(new TH1F (HNS4WOS.str().c_str(),"InvMa",binnum3,bins3)); h4_WOS[k]->Sumw2();
        h5_WOS.push_back(new TH1F (HNS5WOS.str().c_str(),"InvMa",binnum2,bins2)); h5_WOS[k]->Sumw2();
        h6_WOS.push_back(new TH1F (HNS6WOS.str().c_str(),"InvMa",binnum1,bins1)); h6_WOS[k]->Sumw2();
   }

   // Scale factor files
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

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	// Trigger conditions
	bool isSingleLep = (passIsoMu22 && matchIsoMu22_1 && filterIsoMu22_1) or (passIsoTkMu22 && matchIsoTkMu22_1 && filterIsoTkMu22_1) or (passIsoMu22eta2p1 && matchIsoMu22eta2p1_1 && filterIsoMu22eta2p1_1) or (passIsoTkMu22eta2p1 && matchIsoTkMu22eta2p1_1 && filterIsoTkMu22eta2p1_1);
	bool isCrossTrigger = (passIsoMu19Tau20 && matchIsoMu19Tau20_1 && filterIsoMu19Tau20_1 && matchIsoMu19Tau20_2 && filterIsoMu19Tau20_2);

	// Muon ID requirements
        if (sample=="data_obs" && run<278820 && !id_m_medium2016_1) continue;
        if (sample=="data_obs" && run>=278820 && !id_m_medium_1) continue;

	// Trigger requirements
	if (pt_1<20) continue;
        if (fabs(eta_1)>2.1) continue;
	if (!isSingleLep && !isCrossTrigger) continue;
	if (!((isSingleLep && pt_1>23) or (isCrossTrigger && (pt_1<=23 or pt_2<22)))) continue;

        float sf_trg=1.0;
        float sf_id=1.0;
        float sf_id_anti=1.0;
	float sf_trg_anti=1.0;
	float eff_tau=1.0;
	float eff_tau_anti=1.0;

	if (sample!="data_obs"){ // Muon ID scale factor
           sf_id=myScaleFactor_id->get_ScaleFactor(pt_1,eta_1);
        }

	float signalRegion=(byTightIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15);
	float aiRegion=(byVLooseIsolationMVArun2v1DBoldDMwLT_2 && !byTightIsolationMVArun2v1DBoldDMwLT_2 && iso_1<0.15); // these events are reweighted with the tau fake rates to get the fake background
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

        if (sample=="W"){ //xs weights
            weight=25.446;
            if (numGenJets==1) weight=6.8176;
            else if (numGenJets==2) weight=2.1038;
            else if (numGenJets==3) weight=0.6889;
            else if (numGenJets==4) weight=0.6900;
        }

        if (sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ"){ //xs weights
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

        if (sample=="DYlow" or sample=="DYlowll" or sample=="DY1low" or sample=="DY1lowll" or sample=="DY2low" or sample=="DY2lowll"){ //DY low mass sample binned with njets, these are xs weights
            weight=0.0;
            if (numGenJets==1) weight=0.74;
            else if (numGenJets==2) weight=0.823;
        }

	float correction=sf_id;
	if (sample!="data_obs") correction=correction*LumiWeights_12->weight(npu);// pileup reweighting
	float aweight=amcatNLO_weight*weight*correction;

	//Scale factors for the reco tauh
        if (sample!="data_obs"){
           if (gen_match_2==5) aweight=aweight*0.95; //real tauh
           else if (gen_match_2==2 or gen_match_2==4){//mu->tauh fakes
               if (fabs(mytau.Eta())<0.4) aweight=aweight*1.012;
               else if (fabs(mytau.Eta())<0.8) aweight=aweight*1.007;
               else if (fabs(mytau.Eta())<1.2) aweight=aweight*0.870;
               else if (fabs(mytau.Eta())<1.7) aweight=aweight*1.154;
               else aweight=aweight*2.281;
           }
	   else if (gen_match_2==1 or gen_match_2==3){//e->tauh fakes
              if (fabs(eta_2)<1.460) aweight=aweight*1.213;
              else if (fabs(eta_2)>1.558) aweight=aweight*1.375;
           }
	   aweight=aweight*h_Trk->Eval(eta_1);
        }

	if (sample=="ZTT" or sample=="ZLL" or sample=="ZL" or sample=="ZJ" or sample=="DYlow" or sample=="DY1low" or sample=="DY2low"){ // Z pT correction for Drell-Yan events
	    float zpt_corr=histZ->GetBinContent(histZ->GetXaxis()->FindBin(90),histZ->GetYaxis()->FindBin(genpT));
	    aweight=aweight*zpt_corr;
	}

	// Separation between L, T and J # L means mu/e->tauh fake (genmatch 1, 2, 3, 4), T means real tauh (genmatch 5), J means j->tauh fake (genmatch 6)
        if (sample=="ZL" && gen_match_2>4) continue;
        if (sample=="ZTT" && gen_match_2!=5) continue;
        if (sample=="ZJ" && gen_match_2!=6) continue;
        if (sample=="TTJ" && gen_match_2!=6) continue;
        if (sample=="TTT" && gen_match_2!=5) continue;
	if (sample=="TTL" && gen_match_2>4) continue;
	if (name=="VV" && gen_match_2==6) continue;
        if (name=="ST" && gen_match_2==6) continue;

     	// Top pT reweighting, for ttbar MC only
	float pttop1=pt_top1;
        if (pttop1>400) pttop1=400;
        float pttop2=pt_top2;
        if (pttop2>400) pttop2=400;
        if ((sample=="TTJ" or sample=="TTT" or sample=="TT" or sample=="TTL")) aweight*=sqrt(exp(0.0615-0.0005*pttop1)*exp(0.0615-0.0005*pttop2));

	// Data events are unweighted
	if (sample=="data_obs") aweight=1.0;

	float weight_btag_1b=1.0;

        TLorentzVector myrawmet;
        myrawmet.SetPtEtaPhiM(met,0,metphi,0);
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawmu=mymu;
	TLorentzVector myrawbjet1=mybjet1;

	for (int k=0; k<nbhist; ++k){ // Loop over uncertainties (here nbhist=1)

	    float weight2=1.0;

	    //Reinitialize all objects before switching uncertainty
	    TLorentzVector mymet=myrawmet;
	    mytau=myrawtau;
            mymu=myrawmu;
   	    mybjet1=myrawbjet1;

            bool has_1b=nbtag>=1;
	    float dm_weight=1.0;

	    // pt cuts
	    if (mytau.Pt()<25.0) continue; // tau pt cut increased to reduce jet->tau fake background
	    if (mymu.Pt()<20.0) continue;

	    // Definition of the variables used in the selection or as observables
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

	    // Trigger scale factors
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

	    // jet -> tauh fake rate as a function of the tau pt and decay mode
	    float fr=1.0;
	    if (l2_decayMode==0) fr= 2.20179e-01 + 3.17084e-01*(TMath::Landau(mytau.Pt(),2.30233e+01,2.62218e+00,0));
            if (l2_decayMode==1) fr= 1.83924e-01 + 8.66271e+00*(TMath::Landau(mytau.Pt(),-2.56076e+01,4.12774e+00,0));
            if (l2_decayMode==10) fr= 6.27144e-02 + 7.25830e-01*(TMath::Landau(mytau.Pt(),6.37171e+01,3.38631e+01,0));

	    // Selection criteria for the different analysis categories (mostly based on mass of 2 taus and 1 b)
	    bool selection_1b =(mt1<50 and mt2<60); // (mt1<40 and mt2<50);//FIXME
	    bool selection_2b = (mymet.Pt()<75 and mt1<50 and mt12<60 and mt2<60 and pzeta>-70);
	    bool is_incl_2b=mbbtt>=160 and nbtagL>=2 and selection_2b;//160
	    bool is_2b=mbbtt<160 and nbtagL>=2 and selection_2b;//160
            bool is_incl_1b=mbtt>=90 and has_1b and nbtagL<2 and selection_1b;//90
            bool is_1b=mbtt<90 and nbtagL<2 and has_1b and selection_1b;//90
	    bool is_1b_lt80=mbtt<75 and has_1b and selection_1b;
	    bool is_1b_80to100=mbtt>=75 and mbtt<95 and has_1b and selection_1b;
	    bool is_1b_100to120=mbtt>=95 and mbtt<115 and has_1b and selection_1b;
	    bool is_1b_gt120=mbtt>=115 and has_1b and selection_1b;

	    float wfr=fr/(1-fr);
	    float weight_btag_2b=1.0;

	    //************************* Fill histograms **********************
	    if (is_incl_2b){
                if (signalRegion && q_1*q_2<0){
                    h0_OS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
		}
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h0_AI[k]->Fill(var_2b,weight2*aweight*weight_btag_2b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h0_SS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (wRegion && q_1*q_2<0)
                    h0_WOS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (wRegion && q_1*q_2>0)
                    h0_WSS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (qcdRegion && q_1*q_2>0)
                    h0_QCD[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
	    }

            if (is_2b){
                if (signalRegion && q_1*q_2<0){
                    h1_OS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
		}
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h1_AI[k]->Fill(var_2b,weight2*aweight*weight_btag_2b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h1_SS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (wRegion && q_1*q_2<0)
                    h1_WOS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (wRegion && q_1*q_2>0)
                    h1_WSS[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
                if (qcdRegion && q_1*q_2>0)
                    h1_QCD[k]->Fill(var_2b,weight2*aweight*weight_btag_2b);
            }

            if (is_1b_gt120 && mt1<40){
                if (signalRegion && q_1*q_2<0){
                    h2_OS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                }
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h2_AI[k]->Fill(var_1b,weight2*aweight*weight_btag_1b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h2_SS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2<0)
                    h2_WOS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2>0)
                    h2_WSS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (qcdRegion && q_1*q_2>0)
                    h2_QCD[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
            }

            if (is_1b && mt1<40){
                if (signalRegion && q_1*q_2<0){
                    h3_OS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                }
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h3_AI[k]->Fill(var_1b,weight2*aweight*weight_btag_1b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h3_SS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2<0)
                    h3_WOS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2>0)
                    h3_WSS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (qcdRegion && q_1*q_2>0)
                    h3_QCD[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
            }

            if (is_1b_lt80 and mt1<40 and mt2<60){
                if (signalRegion && q_1*q_2<0){
                    h4_OS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                }
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h4_AI[k]->Fill(var_1b,weight2*aweight*weight_btag_1b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h4_SS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2<0)
                    h4_WOS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2>0)
                    h4_WSS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (qcdRegion && q_1*q_2>0)
                    h4_QCD[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
            }

            if (is_1b_80to100 && pzeta<0 && mt1<50 && mt2<60){
                if (signalRegion && q_1*q_2<0){
                    h5_OS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                }
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h5_AI[k]->Fill(var_1b,weight2*aweight*weight_btag_1b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h5_SS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2<0)
                    h5_WOS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2>0)
                    h5_WSS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (qcdRegion && q_1*q_2>0)
                    h5_QCD[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
            }

            if (is_1b_100to120){
                if (signalRegion && q_1*q_2<0){
                    h6_OS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                }
                if (aiRegion && q_1*q_2<0 && (sample=="data_obs" or gen_match_2<=5)){
                    h6_AI[k]->Fill(var_1b,weight2*aweight*weight_btag_1b*wfr);
                }
                if (signalRegion && q_1*q_2>0)
                    h6_SS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2<0)
                    h6_WOS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (wRegion && q_1*q_2>0)
                    h6_WSS[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
                if (qcdRegion && q_1*q_2>0)
                    h6_QCD[k]->Fill(var_1b,weight2*aweight*weight_btag_1b);
            }
	}
				
    } // end of loop over events

    for (int k=0; k<nbhist; ++k){
       h0_WOS[k]->Scale(h0_OS[k]->Integral()/h0_WOS[k]->Integral());
       h1_WOS[k]->Scale(h1_OS[k]->Integral()/h1_WOS[k]->Integral());
       h0_WSS[k]->Scale(h0_SS[k]->Integral()/h0_WSS[k]->Integral());
       h1_WSS[k]->Scale(h1_SS[k]->Integral()/h1_WSS[k]->Integral());
       h2_WOS[k]->Scale(h2_OS[k]->Integral()/h2_WOS[k]->Integral());
       h3_WOS[k]->Scale(h3_OS[k]->Integral()/h3_WOS[k]->Integral());
       h2_WSS[k]->Scale(h2_SS[k]->Integral()/h2_WSS[k]->Integral());
       h3_WSS[k]->Scale(h3_SS[k]->Integral()/h3_WSS[k]->Integral());
       h4_WOS[k]->Scale(h4_OS[k]->Integral()/h4_WOS[k]->Integral());
       h5_WOS[k]->Scale(h5_OS[k]->Integral()/h5_WOS[k]->Integral());
       h6_WOS[k]->Scale(h6_OS[k]->Integral()/h6_WOS[k]->Integral());
       h4_WSS[k]->Scale(h4_SS[k]->Integral()/h4_WSS[k]->Integral());
       h5_WSS[k]->Scale(h5_SS[k]->Integral()/h5_WSS[k]->Integral());
       h6_WSS[k]->Scale(h6_SS[k]->Integral()/h6_WSS[k]->Integral());
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    hincl->Write();

    TString postfix="";

    TDirectory *OS0jet =fout->mkdir("mt_incl_2b");
    TDirectory *SS0jet =fout->mkdir("SSincl_2b");
    TDirectory *QCD0jet =fout->mkdir("QCDincl_2b");
    TDirectory *OS1jet =fout->mkdir("mt_2b");
    TDirectory *SS1jet =fout->mkdir("SS2b");
    TDirectory *QCD1jet =fout->mkdir("QCD2b");
    TDirectory *OS2jet =fout->mkdir("mt_incl_1b");
    TDirectory *SS2jet =fout->mkdir("SSincl_1b");
    TDirectory *QCD2jet =fout->mkdir("QCDincl_1b");
    TDirectory *OS3jet =fout->mkdir("mt_1b");
    TDirectory *SS3jet =fout->mkdir("SS1b");
    TDirectory *QCD3jet =fout->mkdir("QCD1b");
    TDirectory *AI0jet =fout->mkdir("AIincl_2b");
    TDirectory *AI1jet =fout->mkdir("AI2b");
    TDirectory *AI2jet =fout->mkdir("AIincl_1b");
    TDirectory *AI3jet =fout->mkdir("AI1b");

    TDirectory *OS4jet =fout->mkdir("mt_1b_lt80");
    TDirectory *SS4jet =fout->mkdir("SS1b_lt80");
    TDirectory *QCD4jet =fout->mkdir("QCD1b_lt80");
    TDirectory *AI4jet =fout->mkdir("AI1b_lt80");
    TDirectory *OS5jet =fout->mkdir("mt_1b_80to100");
    TDirectory *SS5jet =fout->mkdir("SS1b_80to100");
    TDirectory *QCD5jet =fout->mkdir("QCD1b_80to100");
    TDirectory *AI5jet =fout->mkdir("AI1b_80to100");
    TDirectory *OS6jet =fout->mkdir("mt_1b_100to120");
    TDirectory *SS6jet =fout->mkdir("SS1b_100to120");
    TDirectory *QCD6jet =fout->mkdir("QCD1b_100to120");
    TDirectory *AI6jet =fout->mkdir("AI1b_100to120");

//    if (nbhist==1) postfixJES[0]=postfix;

    for (int k=0; k<nbhist; ++k){

//        if (tes==100) postfix=postfixJES[k];
//        if (tes==1) postfix=postfixTES[k];
//        if (tes==16) postfix=postfixDM[k];
//        if (tes==17) postfix=postfixZLshape[k];
//        if (tes==18) postfix=postfixZLnorm[k];
//        if (tes==19) postfix=postfixFakeDM[k];

        fout->cd();
        n70[k]->SetName("n70"+postfix);
        n70[k]->Write();
        n70SS[k]->SetName("n70SS"+postfix);
        n70SS[k]->Write();
    }

    for (int k=0; k<nbhist; ++k){

//       if (tes==100) postfix=postfixJES[k];
//       if (tes==1) postfix=postfixTES[k];
//       if (tes==16) postfix=postfixDM[k];
//       if (tes==17) postfix=postfixZLshape[k];
//       if (tes==18) postfix=postfixZLnorm[k];
//       if (tes==19) postfix=postfixFakeDM[k];
//       if (tes==30) postfix=postfixFake[k];

       for (int nn=1; nn<h0_OS[k]->GetSize()-1; ++nn){
           if (h0_OS[k]->GetBinContent(nn)<0) h0_OS[k]->SetBinContent(nn,0.00001);
           if (h0_SS[k]->GetBinContent(nn)<0) h0_SS[k]->SetBinContent(nn,0.00001);
           if (h0_QCD[k]->GetBinContent(nn)<0) h0_QCD[k]->SetBinContent(nn,0.00001);
           if (h0_WOS[k]->GetBinContent(nn)<0) h0_WOS[k]->SetBinContent(nn,0.00001);
           if (h0_WSS[k]->GetBinContent(nn)<0) h0_WSS[k]->SetBinContent(nn,0.00001);
           if (h0_AI[k]->GetBinContent(nn)<0) h0_AI[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h1_OS[k]->GetSize()-1; ++nn){
           if (h1_OS[k]->GetBinContent(nn)<0) h1_OS[k]->SetBinContent(nn,0.00001);
           if (h1_SS[k]->GetBinContent(nn)<0) h1_SS[k]->SetBinContent(nn,0.00001);
           if (h1_QCD[k]->GetBinContent(nn)<0) h1_QCD[k]->SetBinContent(nn,0.00001);
           if (h1_WOS[k]->GetBinContent(nn)<0) h1_WOS[k]->SetBinContent(nn,0.00001);
           if (h1_WSS[k]->GetBinContent(nn)<0) h1_WSS[k]->SetBinContent(nn,0.00001);
           if (h1_AI[k]->GetBinContent(nn)<0) h1_AI[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h2_OS[k]->GetSize()-1; ++nn){
           if (h2_AI[k]->GetBinContent(nn)<0) h2_AI[k]->SetBinContent(nn,0.00001);
           if (h2_OS[k]->GetBinContent(nn)<0) h2_OS[k]->SetBinContent(nn,0.00001);
           if (h2_SS[k]->GetBinContent(nn)<0) h2_SS[k]->SetBinContent(nn,0.00001);
           if (h2_QCD[k]->GetBinContent(nn)<0) h2_QCD[k]->SetBinContent(nn,0.00001);
           if (h2_WOS[k]->GetBinContent(nn)<0) h2_WOS[k]->SetBinContent(nn,0.00001);
           if (h2_WSS[k]->GetBinContent(nn)<0) h2_WSS[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h3_OS[k]->GetSize()-1; ++nn){
           if (h3_OS[k]->GetBinContent(nn)<0) h3_OS[k]->SetBinContent(nn,0.00001);
           if (h3_SS[k]->GetBinContent(nn)<0) h3_SS[k]->SetBinContent(nn,0.00001);
           if (h3_QCD[k]->GetBinContent(nn)<0) h3_QCD[k]->SetBinContent(nn,0.00001);
           if (h3_WOS[k]->GetBinContent(nn)<0) h3_WOS[k]->SetBinContent(nn,0.00001);
           if (h3_WSS[k]->GetBinContent(nn)<0) h3_WSS[k]->SetBinContent(nn,0.00001);
           if (h3_AI[k]->GetBinContent(nn)<0) h3_AI[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h4_OS[k]->GetSize()-1; ++nn){
           if (h4_AI[k]->GetBinContent(nn)<0) h4_AI[k]->SetBinContent(nn,0.00001);
           if (h4_OS[k]->GetBinContent(nn)<0) h4_OS[k]->SetBinContent(nn,0.00001);
           if (h4_SS[k]->GetBinContent(nn)<0) h4_SS[k]->SetBinContent(nn,0.00001);
           if (h4_QCD[k]->GetBinContent(nn)<0) h4_QCD[k]->SetBinContent(nn,0.00001);
           if (h4_WOS[k]->GetBinContent(nn)<0) h4_WOS[k]->SetBinContent(nn,0.00001);
           if (h4_WSS[k]->GetBinContent(nn)<0) h4_WSS[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h5_OS[k]->GetSize()-1; ++nn){
           if (h5_AI[k]->GetBinContent(nn)<0) h5_AI[k]->SetBinContent(nn,0.00001);
           if (h5_OS[k]->GetBinContent(nn)<0) h5_OS[k]->SetBinContent(nn,0.00001);
           if (h5_SS[k]->GetBinContent(nn)<0) h5_SS[k]->SetBinContent(nn,0.00001);
           if (h5_QCD[k]->GetBinContent(nn)<0) h5_QCD[k]->SetBinContent(nn,0.00001);
           if (h5_WOS[k]->GetBinContent(nn)<0) h5_WOS[k]->SetBinContent(nn,0.00001);
           if (h5_WSS[k]->GetBinContent(nn)<0) h5_WSS[k]->SetBinContent(nn,0.00001);
       }
       for (int nn=1; nn<h6_OS[k]->GetSize()-1; ++nn){
           if (h6_AI[k]->GetBinContent(nn)<0) h6_AI[k]->SetBinContent(nn,0.00001);
           if (h6_OS[k]->GetBinContent(nn)<0) h6_OS[k]->SetBinContent(nn,0.00001);
           if (h6_SS[k]->GetBinContent(nn)<0) h6_SS[k]->SetBinContent(nn,0.00001);
           if (h6_QCD[k]->GetBinContent(nn)<0) h6_QCD[k]->SetBinContent(nn,0.00001);
           if (h6_WOS[k]->GetBinContent(nn)<0) h6_WOS[k]->SetBinContent(nn,0.00001);
           if (h6_WSS[k]->GetBinContent(nn)<0) h6_WSS[k]->SetBinContent(nn,0.00001);
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
       AI0jet->cd();
       h0_AI[k]->SetName(name.c_str()+postfix);
       h0_AI[k]->Write();

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
       AI1jet->cd();
       h1_AI[k]->SetName(name.c_str()+postfix);
       h1_AI[k]->Write();

       OS2jet->cd();
       h2_OS[k]->SetName(name.c_str()+postfix);
       h2_WOS[k]->SetName(name.c_str()+postfix);
       h2_OS[k]->Write();
       SS2jet->cd();
       h2_SS[k]->SetName(name.c_str()+postfix);
       h2_WSS[k]->SetName(name.c_str()+postfix);
       h2_SS[k]->Write();
       QCD2jet->cd();
       h2_QCD[k]->SetName(name.c_str()+postfix);
       h2_QCD[k]->Write();
       AI2jet->cd();
       h2_AI[k]->SetName(name.c_str()+postfix);
       h2_AI[k]->Write();

       OS3jet->cd();
       h3_OS[k]->SetName(name.c_str()+postfix);
       h3_WOS[k]->SetName(name.c_str()+postfix);
       if (sample=="W")
          h3_WOS[k]->Write();
       else
          h3_OS[k]->Write();
       SS3jet->cd();
       h3_SS[k]->SetName(name.c_str()+postfix);
       h3_WSS[k]->SetName(name.c_str()+postfix);
       if (sample=="W")
          h3_WSS[k]->Write();
       else
          h3_SS[k]->Write();
       QCD3jet->cd();
       h3_QCD[k]->SetName(name.c_str()+postfix);
       h3_QCD[k]->Write();
       AI3jet->cd();
       h3_AI[k]->SetName(name.c_str()+postfix);
       h3_AI[k]->Write();

        OS4jet->cd();
        h4_OS[k]->SetName(name.c_str()+postfix);
        h4_WOS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h4_WOS[k]->Write();
        else
           h4_OS[k]->Write();
        SS4jet->cd();
        h4_SS[k]->SetName(name.c_str()+postfix);
        h4_WSS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h4_WSS[k]->Write();
        else
           h4_SS[k]->Write();
        QCD4jet->cd();
        h4_QCD[k]->SetName(name.c_str()+postfix);
        h4_QCD[k]->Write();
        AI4jet->cd();
        h4_AI[k]->SetName(name.c_str()+postfix);
        h4_AI[k]->Write();

        OS5jet->cd();
        h5_OS[k]->SetName(name.c_str()+postfix);
        h5_WOS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h5_WOS[k]->Write();
        else
           h5_OS[k]->Write();
        SS5jet->cd();
        h5_SS[k]->SetName(name.c_str()+postfix);
        h5_WSS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h5_WSS[k]->Write();
        else
           h5_SS[k]->Write();
        QCD5jet->cd();
        h5_QCD[k]->SetName(name.c_str()+postfix);
        h5_QCD[k]->Write();
        AI5jet->cd();
        h5_AI[k]->SetName(name.c_str()+postfix);
        h5_AI[k]->Write();

        OS6jet->cd();
        h6_OS[k]->SetName(name.c_str()+postfix);
        h6_WOS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h6_WOS[k]->Write();
        else
           h6_OS[k]->Write();
        SS6jet->cd();
        h6_SS[k]->SetName(name.c_str()+postfix);
        h6_WSS[k]->SetName(name.c_str()+postfix);
        if (sample=="W")
           h6_WSS[k]->Write();
        else
           h6_SS[k]->Write();
        QCD6jet->cd();
        h6_QCD[k]->SetName(name.c_str()+postfix);
        h6_QCD[k]->Write();
        AI6jet->cd();
        h6_AI[k]->SetName(name.c_str()+postfix);
        h6_AI[k]->Write();

    }
cout<<h0_OS[0]->Integral()<<" "<<h1_OS[0]->Integral()<<endl;
    fout->Close();
} 


