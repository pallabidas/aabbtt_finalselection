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
#include "btagSF_2017.h"
#include "btagSF_2016.h"
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
    std::string year = *(argv + 5);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("mutau_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    std::string sample_name = sample.c_str();
    std::string dnnfile = "/hdfs/store/user/htsoi/dnn/mt18/" + sample_name + ".root";
    if (year=="2017") dnnfile = "/hdfs/store/user/htsoi/dnn/mt17/" + sample_name + ".root";
    if (year=="2016") dnnfile = "/hdfs/store/user/htsoi/dnn/mt16/" + sample_name + ".root";
    TFile * dnn = new TFile(dnnfile.c_str());
    TTree * tree_dnn = (TTree*) dnn->Get("mutau_tree_dnn");
    
    //sample weights
    float xs, weight;
    float luminosity = 59740.0;
    if (year=="2017") luminosity = 41530.0;
    if (year=="2016") luminosity = 35920.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt12"){xs = 0.01*48.58*0.0380; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt15"){xs = 0.01*48.58*0.0367; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58*0.0355; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt25"){xs = 0.01*48.58*0.0346; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58*0.0336; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt35"){xs = 0.01*48.58*0.0327; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58*0.0321; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt45"){xs = 0.01*48.58*0.0319; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58*0.0329; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt55"){xs = 0.01*48.58*0.0352; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58*0.0403; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt12"){xs = 0.01*3.782*0.0785; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt15"){xs = 0.01*3.782*0.0769; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt20"){xs = 0.01*3.782*0.0749; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt25"){xs = 0.01*3.782*0.0735; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt30"){xs = 0.01*3.782*0.0717; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt35"){xs = 0.01*3.782*0.0702; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt40"){xs = 0.01*3.782*0.0682; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt45"){xs = 0.01*3.782*0.0670; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt50"){xs = 0.01*3.782*0.0661; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt55"){xs = 0.01*3.782*0.0662; weight = luminosity*xs/N;}
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
    else if(sample == "ST_tW_antitop"){xs = 35.85; if(year=="2016") xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_tW_top"){xs = 35.85; if(year=="2016") xs = 35.6; weight = luminosity*xs/N;}
    else if(sample == "ST_t_antitop"){xs = 80.94; if(year=="2016") xs = 26.23; weight = luminosity*xs/N;}
    else if(sample == "ST_t_top"){xs = 136.02; if(year=="2016") xs = 44.07; weight = luminosity*xs/N;}
    else if(sample == "TTTo2L2Nu"){xs = 88.29; weight = luminosity*xs/N;}
    else if(sample == "TTToHadronic"){xs = 377.96; weight = luminosity*xs/N;}
    else if(sample == "TTToSemiLeptonic"){xs = 365.35; weight = luminosity*xs/N;}
    else if(sample == "TT"){xs = 831.76; weight = luminosity*xs/N;}//for 2016 only
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VBFHWW"){xs = 3.782*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 13.84; weight = luminosity*xs/N;}//11.95
    //else if(sample == "W"){weight = 1.0;}
    //else if(sample == "W1"){weight = 1.0;}
    //else if(sample == "W2"){weight = 1.0;}
    //else if(sample == "W3"){weight = 1.0;}
    //else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.52; weight = luminosity*xs/N;}//5.595
    else if(sample == "WZ3LNu"){xs = 4.43; weight = luminosity*xs/N;}//4.708
    else if(sample == "WZ3L1Nu"){xs = 4.43; weight = luminosity*xs/N;}
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
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_2017_1", &matchEmbFilter_Mu20Tau27_2017_1);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
    tree->SetBranchAddress("passMu20HPSTau27", &passMu20HPSTau27);
    tree->SetBranchAddress("matchMu20HPSTau27_1", &matchMu20HPSTau27_1);
    tree->SetBranchAddress("filterMu20HPSTau27_1", &filterMu20HPSTau27_1);
    tree->SetBranchAddress("matchMu20HPSTau27_2", &matchMu20HPSTau27_2);
    tree->SetBranchAddress("filterMu20HPSTau27_2", &filterMu20HPSTau27_2);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_1", &matchEmbFilter_Mu20Tau27_1);
    tree->SetBranchAddress("matchEmbFilter_Mu20Tau27_2", &matchEmbFilter_Mu20Tau27_2);
    tree->SetBranchAddress("matchEmbFilter_Mu20HPSTau27_2", &matchEmbFilter_Mu20HPSTau27_2);
    tree->SetBranchAddress("passMu22eta2p1", &passMu22eta2p1);
    tree->SetBranchAddress("matchMu22eta2p1_1", &matchMu22eta2p1_1);
    tree->SetBranchAddress("filterMu22eta2p1_1", &filterMu22eta2p1_1);
    tree->SetBranchAddress("passTkMu22eta2p1", &passTkMu22eta2p1);
    tree->SetBranchAddress("matchTkMu22eta2p1_1", &matchTkMu22eta2p1_1);
    tree->SetBranchAddress("filterTkMu22eta2p1_1", &filterTkMu22eta2p1_1);
    tree->SetBranchAddress("passMu22", &passMu22);
    tree->SetBranchAddress("matchMu22_1", &matchMu22_1);
    tree->SetBranchAddress("filterMu22_1", &filterMu22_1);
    tree->SetBranchAddress("passTkMu22", &passTkMu22);
    tree->SetBranchAddress("matchTkMu22_1", &matchTkMu22_1);
    tree->SetBranchAddress("filterTkMu22_1", &filterTkMu22_1);
    tree->SetBranchAddress("passMu19Tau20", &passMu19Tau20);
    tree->SetBranchAddress("matchMu19Tau20_1", &matchMu19Tau20_1);
    tree->SetBranchAddress("matchMu19Tau20_2", &matchMu19Tau20_2);
    tree->SetBranchAddress("filterMu19Tau20_1", &filterMu19Tau20_1);
    tree->SetBranchAddress("filterMu19Tau20_2", &filterMu19Tau20_2);
    tree->SetBranchAddress("passMu19Tau20SingleL1", &passMu19Tau20SingleL1);
    tree->SetBranchAddress("matchMu19Tau20SingleL1_1", &matchMu19Tau20SingleL1_1);
    tree->SetBranchAddress("matchMu19Tau20SingleL1_2", &matchMu19Tau20SingleL1_2);
    tree->SetBranchAddress("filterMu19Tau20SingleL1_1", &filterMu19Tau20SingleL1_1);
    tree->SetBranchAddress("filterMu19Tau20SingleL1_2", &filterMu19Tau20SingleL1_2);
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
    tree->SetBranchAddress("njets", &njets);
    tree->SetBranchAddress("genweight", &genweight);
    tree->SetBranchAddress("mjj", &mjj);
    tree->SetBranchAddress("gen_match_1",&gen_match_1);
    tree->SetBranchAddress("gen_match_2",&gen_match_2);
    tree->SetBranchAddress("met", &met);
    tree->SetBranchAddress("met_UESUp", &met_UESUp);
    tree->SetBranchAddress("met_UESDown", &met_UESDown);
    tree->SetBranchAddress("met_JERUp", &met_JERUp);
    tree->SetBranchAddress("met_JERDown", &met_JERDown);
    tree->SetBranchAddress("met_JetAbsoluteUp", &met_JetAbsoluteUp);
    tree->SetBranchAddress("met_JetAbsoluteDown", &met_JetAbsoluteDown);
    tree->SetBranchAddress("met_JetAbsoluteyearUp", &met_JetAbsoluteyearUp);
    tree->SetBranchAddress("met_JetAbsoluteyearDown", &met_JetAbsoluteyearDown);
    tree->SetBranchAddress("met_JetBBEC1Up", &met_JetBBEC1Up);
    tree->SetBranchAddress("met_JetBBEC1Down", &met_JetBBEC1Down);
    tree->SetBranchAddress("met_JetBBEC1yearUp", &met_JetBBEC1yearUp);
    tree->SetBranchAddress("met_JetBBEC1yearDown", &met_JetBBEC1yearDown);
    tree->SetBranchAddress("met_JetEC2Up", &met_JetEC2Up);
    tree->SetBranchAddress("met_JetEC2Down", &met_JetEC2Down);
    tree->SetBranchAddress("met_JetEC2yearUp", &met_JetEC2yearUp);
    tree->SetBranchAddress("met_JetEC2yearDown", &met_JetEC2yearDown);
    tree->SetBranchAddress("met_JetFlavorQCDUp", &met_JetFlavorQCDUp);
    tree->SetBranchAddress("met_JetFlavorQCDDown", &met_JetFlavorQCDDown);
    tree->SetBranchAddress("met_JetHFUp", &met_JetHFUp);
    tree->SetBranchAddress("met_JetHFDown", &met_JetHFDown);
    tree->SetBranchAddress("met_JetHFyearUp", &met_JetHFyearUp);
    tree->SetBranchAddress("met_JetHFyearDown", &met_JetHFyearDown);
    tree->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    tree->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    tree->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    tree->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    tree->SetBranchAddress("met_responseUp", &met_responseUp);
    tree->SetBranchAddress("met_responseDown", &met_responseDown);
    tree->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
    tree->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
    tree->SetBranchAddress("metphi", &metphi);
    tree->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    tree->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    tree->SetBranchAddress("metphi_JERUp", &metphi_JERUp);
    tree->SetBranchAddress("metphi_JERDown", &metphi_JERDown);
    tree->SetBranchAddress("metphi_JetAbsoluteUp", &metphi_JetAbsoluteUp);
    tree->SetBranchAddress("metphi_JetAbsoluteDown", &metphi_JetAbsoluteDown);
    tree->SetBranchAddress("metphi_JetAbsoluteyearUp", &metphi_JetAbsoluteyearUp);
    tree->SetBranchAddress("metphi_JetAbsoluteyearDown", &metphi_JetAbsoluteyearDown);
    tree->SetBranchAddress("metphi_JetBBEC1Up", &metphi_JetBBEC1Up);
    tree->SetBranchAddress("metphi_JetBBEC1Down", &metphi_JetBBEC1Down);
    tree->SetBranchAddress("metphi_JetBBEC1yearUp", &metphi_JetBBEC1yearUp);
    tree->SetBranchAddress("metphi_JetBBEC1yearDown", &metphi_JetBBEC1yearDown);
    tree->SetBranchAddress("metphi_JetEC2Up", &metphi_JetEC2Up);
    tree->SetBranchAddress("metphi_JetEC2Down", &metphi_JetEC2Down);
    tree->SetBranchAddress("metphi_JetEC2yearUp", &metphi_JetEC2yearUp);
    tree->SetBranchAddress("metphi_JetEC2yearDown", &metphi_JetEC2yearDown);
    tree->SetBranchAddress("metphi_JetFlavorQCDUp", &metphi_JetFlavorQCDUp);
    tree->SetBranchAddress("metphi_JetFlavorQCDDown", &metphi_JetFlavorQCDDown);
    tree->SetBranchAddress("metphi_JetHFUp", &metphi_JetHFUp);
    tree->SetBranchAddress("metphi_JetHFDown", &metphi_JetHFDown);
    tree->SetBranchAddress("metphi_JetHFyearUp", &metphi_JetHFyearUp);
    tree->SetBranchAddress("metphi_JetHFyearDown", &metphi_JetHFyearDown);
    tree->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    tree->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    tree->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    tree->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
    tree->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
    tree->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
    tree->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
    tree->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
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
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_mutau_ratio_up", &t_trg_pog_deeptau_medium_mutau_ratio_up);
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_mutau_ratio_down", &t_trg_pog_deeptau_medium_mutau_ratio_down);
    tree->SetBranchAddress("m_trg_MuTau_Mu20Leg_desy_ratio", &m_trg_MuTau_Mu20Leg_desy_ratio);
    tree->SetBranchAddress("m_trg_19_ic_ratio", &m_trg_19_ic_ratio);
    tree->SetBranchAddress("m_trk_ratio", &m_trk_ratio);
    tree->SetBranchAddress("m_idiso_ic_ratio", &m_idiso_ic_ratio);
    tree->SetBranchAddress("zptmass_weight_nom", &zptmass_weight_nom);
    tree->SetBranchAddress("m_trg_ic_embed_ratio", &m_trg_ic_embed_ratio);
    tree->SetBranchAddress("m_trg_20_ic_embed_ratio", &m_trg_20_ic_embed_ratio);
    tree->SetBranchAddress("m_trg_19_ic_embed_ratio", &m_trg_19_ic_embed_ratio);
    tree->SetBranchAddress("t_trg_mediumDeepTau_mutau_embed_ratio", &t_trg_mediumDeepTau_mutau_embed_ratio);
    tree->SetBranchAddress("t_trg_mediumDeepTau_mutau_embed_ratio_up", &t_trg_mediumDeepTau_mutau_embed_ratio_up);
    tree->SetBranchAddress("t_trg_mediumDeepTau_mutau_embed_ratio_down", &t_trg_mediumDeepTau_mutau_embed_ratio_down);
    tree->SetBranchAddress("m_idiso_ic_embed_ratio", &m_idiso_ic_embed_ratio);
    tree->SetBranchAddress("m_sel_trg_ic_ratio", &m_sel_trg_ic_ratio);
    tree->SetBranchAddress("m_sel_id_ic_ratio_1", &m_sel_id_ic_ratio_1);
    tree->SetBranchAddress("m_sel_id_ic_ratio_2", &m_sel_id_ic_ratio_2);
    tree->SetBranchAddress("prefiring_weight", &prefiring_weight);
    tree->SetBranchAddress("m_sv", &m_sv);
    tree->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    tree->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    tree->SetBranchAddress("m_sv_JERUp", &m_sv_JERUp);
    tree->SetBranchAddress("m_sv_JERDown", &m_sv_JERDown);
    tree->SetBranchAddress("m_sv_UP", &m_sv_UP);
    tree->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    tree->SetBranchAddress("m_sv_muonESUp", &m_sv_muonESUp);
    tree->SetBranchAddress("m_sv_muonESDown", &m_sv_muonESDown);
    tree->SetBranchAddress("m_sv_JetAbsoluteUp", &m_sv_JetAbsoluteUp);
    tree->SetBranchAddress("m_sv_JetAbsoluteDown", &m_sv_JetAbsoluteDown);
    tree->SetBranchAddress("m_sv_JetAbsoluteyearUp", &m_sv_JetAbsoluteyearUp);
    tree->SetBranchAddress("m_sv_JetAbsoluteyearDown", &m_sv_JetAbsoluteyearDown);
    tree->SetBranchAddress("m_sv_JetBBEC1Up", &m_sv_JetBBEC1Up);
    tree->SetBranchAddress("m_sv_JetBBEC1Down", &m_sv_JetBBEC1Down);
    tree->SetBranchAddress("m_sv_JetBBEC1yearUp", &m_sv_JetBBEC1yearUp);
    tree->SetBranchAddress("m_sv_JetBBEC1yearDown", &m_sv_JetBBEC1yearDown);
    tree->SetBranchAddress("m_sv_JetEC2Up", &m_sv_JetEC2Up);
    tree->SetBranchAddress("m_sv_JetEC2Down", &m_sv_JetEC2Down);
    tree->SetBranchAddress("m_sv_JetEC2yearUp", &m_sv_JetEC2yearUp);
    tree->SetBranchAddress("m_sv_JetEC2yearDown", &m_sv_JetEC2yearDown);
    tree->SetBranchAddress("m_sv_JetFlavorQCDUp", &m_sv_JetFlavorQCDUp);
    tree->SetBranchAddress("m_sv_JetFlavorQCDDown", &m_sv_JetFlavorQCDDown);
    tree->SetBranchAddress("m_sv_JetHFUp", &m_sv_JetHFUp);
    tree->SetBranchAddress("m_sv_JetHFDown", &m_sv_JetHFDown);
    tree->SetBranchAddress("m_sv_JetHFyearUp", &m_sv_JetHFyearUp);
    tree->SetBranchAddress("m_sv_JetHFyearDown", &m_sv_JetHFyearDown);
    tree->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    tree->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    tree->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    tree->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    tree->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    tree->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    tree->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    tree->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    
    tree_dnn->SetBranchAddress("dnn_1b", &dnn_1b);//wider binning in intermediate region, narrower in low and high regions//blind signal for data
    /*
    tree_dnn->SetBranchAddress("dnn_1b_Up", &dnn_1b_Up);
    tree_dnn->SetBranchAddress("dnn_1b_Down", &dnn_1b_Down);
    tree_dnn->SetBranchAddress("dnn_1b_UESUp", &dnn_1b_UESUp);
    tree_dnn->SetBranchAddress("dnn_1b_UESDown", &dnn_1b_UESDown);
    tree_dnn->SetBranchAddress("dnn_1b_JERUp", &dnn_1b_JERUp);
    tree_dnn->SetBranchAddress("dnn_1b_JERDown", &dnn_1b_JERDown);
    tree_dnn->SetBranchAddress("dnn_1b_muonESUp", &dnn_1b_muonESUp);
    tree_dnn->SetBranchAddress("dnn_1b_muonESDown", &dnn_1b_muonESDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetAbsoluteUp", &dnn_1b_JetAbsoluteUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetAbsoluteDown", &dnn_1b_JetAbsoluteDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetAbsoluteyearUp", &dnn_1b_JetAbsoluteyearUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetAbsoluteyearDown", &dnn_1b_JetAbsoluteyearDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetBBEC1Up", &dnn_1b_JetBBEC1Up);
    tree_dnn->SetBranchAddress("dnn_1b_JetBBEC1Down", &dnn_1b_JetBBEC1Down);
    tree_dnn->SetBranchAddress("dnn_1b_JetBBEC1yearUp", &dnn_1b_JetBBEC1yearUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetBBEC1yearDown", &dnn_1b_JetBBEC1yearDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetEC2Up", &dnn_1b_JetEC2Up);
    tree_dnn->SetBranchAddress("dnn_1b_JetEC2Down", &dnn_1b_JetEC2Down);
    tree_dnn->SetBranchAddress("dnn_1b_JetEC2yearUp", &dnn_1b_JetEC2yearUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetEC2yearDown", &dnn_1b_JetEC2yearDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetFlavorQCDUp", &dnn_1b_JetFlavorQCDUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetFlavorQCDDown", &dnn_1b_JetFlavorQCDDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetHFUp", &dnn_1b_JetHFUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetHFDown", &dnn_1b_JetHFDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetHFyearUp", &dnn_1b_JetHFyearUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetHFyearDown", &dnn_1b_JetHFyearDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetRelativeBalUp", &dnn_1b_JetRelativeBalUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetRelativeBalDown", &dnn_1b_JetRelativeBalDown);
    tree_dnn->SetBranchAddress("dnn_1b_JetRelativeSampleUp", &dnn_1b_JetRelativeSampleUp);
    tree_dnn->SetBranchAddress("dnn_1b_JetRelativeSampleDown", &dnn_1b_JetRelativeSampleDown);
    tree_dnn->SetBranchAddress("dnn_1b_ResponseUp", &dnn_1b_ResponseUp);
    tree_dnn->SetBranchAddress("dnn_1b_ResponseDown", &dnn_1b_ResponseDown);
    tree_dnn->SetBranchAddress("dnn_1b_ResolutionUp", &dnn_1b_ResolutionUp);
    tree_dnn->SetBranchAddress("dnn_1b_ResolutionDown", &dnn_1b_ResolutionDown);*/
    tree_dnn->SetBranchAddress("dnn_2b", &dnn_2b);
    /*
    tree_dnn->SetBranchAddress("dnn_2b_Up", &dnn_2b_Up);
    tree_dnn->SetBranchAddress("dnn_2b_Down", &dnn_2b_Down);
    tree_dnn->SetBranchAddress("dnn_2b_UESUp", &dnn_2b_UESUp);
    tree_dnn->SetBranchAddress("dnn_2b_UESDown", &dnn_2b_UESDown);
    tree_dnn->SetBranchAddress("dnn_2b_JERUp", &dnn_2b_JERUp);
    tree_dnn->SetBranchAddress("dnn_2b_JERDown", &dnn_2b_JERDown);
    tree_dnn->SetBranchAddress("dnn_2b_muonESUp", &dnn_2b_muonESUp);
    tree_dnn->SetBranchAddress("dnn_2b_muonESDown", &dnn_2b_muonESDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetAbsoluteUp", &dnn_2b_JetAbsoluteUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetAbsoluteDown", &dnn_2b_JetAbsoluteDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetAbsoluteyearUp", &dnn_2b_JetAbsoluteyearUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetAbsoluteyearDown", &dnn_2b_JetAbsoluteyearDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetBBEC1Up", &dnn_2b_JetBBEC1Up);
    tree_dnn->SetBranchAddress("dnn_2b_JetBBEC1Down", &dnn_2b_JetBBEC1Down);
    tree_dnn->SetBranchAddress("dnn_2b_JetBBEC1yearUp", &dnn_2b_JetBBEC1yearUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetBBEC1yearDown", &dnn_2b_JetBBEC1yearDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetEC2Up", &dnn_2b_JetEC2Up);
    tree_dnn->SetBranchAddress("dnn_2b_JetEC2Down", &dnn_2b_JetEC2Down);
    tree_dnn->SetBranchAddress("dnn_2b_JetEC2yearUp", &dnn_2b_JetEC2yearUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetEC2yearDown", &dnn_2b_JetEC2yearDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetFlavorQCDUp", &dnn_2b_JetFlavorQCDUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetFlavorQCDDown", &dnn_2b_JetFlavorQCDDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetHFUp", &dnn_2b_JetHFUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetHFDown", &dnn_2b_JetHFDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetHFyearUp", &dnn_2b_JetHFyearUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetHFyearDown", &dnn_2b_JetHFyearDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetRelativeBalUp", &dnn_2b_JetRelativeBalUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetRelativeBalDown", &dnn_2b_JetRelativeBalDown);
    tree_dnn->SetBranchAddress("dnn_2b_JetRelativeSampleUp", &dnn_2b_JetRelativeSampleUp);
    tree_dnn->SetBranchAddress("dnn_2b_JetRelativeSampleDown", &dnn_2b_JetRelativeSampleDown);
    tree_dnn->SetBranchAddress("dnn_2b_ResponseUp", &dnn_2b_ResponseUp);
    tree_dnn->SetBranchAddress("dnn_2b_ResponseDown", &dnn_2b_ResponseDown);
    tree_dnn->SetBranchAddress("dnn_2b_ResolutionUp", &dnn_2b_ResolutionUp);
    tree_dnn->SetBranchAddress("dnn_2b_ResolutionDown", &dnn_2b_ResolutionDown);*/
    
    std::string shape_year = year.c_str();
    //for MC but not emb (still done on emb but without "emb" tag, these will not be used at all)
    TString shape_tauideff[14] = {"_CMS_tauideff_pt20to25_"+shape_year+"Up","_CMS_tauideff_pt20to25_"+shape_year+"Down","_CMS_tauideff_pt25to30_"+shape_year+"Up","_CMS_tauideff_pt25to30_"+shape_year+"Down","_CMS_tauideff_pt30to35_"+shape_year+"Up","_CMS_tauideff_pt30to35_"+shape_year+"Down","_CMS_tauideff_pt35to40_"+shape_year+"Up","_CMS_tauideff_pt35to40_"+shape_year+"Down","_CMS_tauideff_pt40to500_"+shape_year+"Up","_CMS_tauideff_pt40to500_"+shape_year+"Down","_CMS_tauideff_pt500to1000_"+shape_year+"Up","_CMS_tauideff_pt500to1000_"+shape_year+"Down","_CMS_tauideff_ptgt1000_"+shape_year+"Up","_CMS_tauideff_ptgt1000_"+shape_year+"Down"};
    TString shape_tauES[8] = {"_CMS_tauES_dm0_"+shape_year+"Up","_CMS_tauES_dm0_"+shape_year+"Down","_CMS_tauES_dm1_"+shape_year+"Up","_CMS_tauES_dm1_"+shape_year+"Down","_CMS_tauES_dm10_"+shape_year+"Up","_CMS_tauES_dm10_"+shape_year+"Down","_CMS_tauES_dm11_"+shape_year+"Up","_CMS_tauES_dm11_"+shape_year+"Down"};
    TString shape_jet[22] = {"_CMS_JetAbsolute_"+shape_year+"Up","_CMS_JetAbsolute_"+shape_year+"Down","_CMS_JetAbsoluteyear_"+shape_year+"Up","_CMS_JetAbsoluteyear_"+shape_year+"Down","_CMS_JetBBEC1_"+shape_year+"Up","_CMS_JetBBEC1_"+shape_year+"Down","_CMS_JetBBEC1year_"+shape_year+"Up","_CMS_JetBBEC1year_"+shape_year+"Down","_CMS_JetEC2_"+shape_year+"Up","_CMS_JetEC2_"+shape_year+"Down","_CMS_JetEC2year_"+shape_year+"Up","_CMS_JetEC2year_"+shape_year+"Down","_CMS_JetFlavorQCD_"+shape_year+"Up","_CMS_JetFlavorQCD_"+shape_year+"Down","_CMS_JetHF_"+shape_year+"Up","_CMS_JetHF_"+shape_year+"Down","_CMS_JetHFyear_"+shape_year+"Up","_CMS_JetHFyear_"+shape_year+"Down","_CMS_JetRelativeBal_"+shape_year+"Up","_CMS_JetRelativeBal_"+shape_year+"Down","_CMS_JetRelativeSample_"+shape_year+"Up","_CMS_JetRelativeSample_"+shape_year+"Down"};
    TString shape_mufaketauES[2] = {"_CMS_muonfaketauES_"+shape_year+"Up","_CMS_muonfaketauES_"+shape_year+"Down"};
    TString shape_elefaketauES[8] = {"_CMS_elefaketauES_dm0_barrel_"+shape_year+"Up","_CMS_elefaketauES_dm0_barrel_"+shape_year+"Down","_CMS_elefaketauES_dm0_endcap_"+shape_year+"Up","_CMS_elefaketauES_dm0_endcap_"+shape_year+"Down","_CMS_elefaketauES_dm1_barrel_"+shape_year+"Up","_CMS_elefaketauES_dm1_barrel_"+shape_year+"Down","_CMS_elefaketauES_dm1_endcap_"+shape_year+"Up","_CMS_elefaketauES_dm1_endcap_"+shape_year+"Down"};
    TString shape_trgeff[4] = {"_CMS_trgeff_singleMu_"+shape_year+"Up","_CMS_trgeff_singleMu_"+shape_year+"Down","_CMS_trgeff_crossMuTau_"+shape_year+"Up","_CMS_trgeff_crossMuTau_"+shape_year+"Down"};
    TString shape_muonES[6] = {"_CMS_muonES_eta0to1p4_"+shape_year+"Up","_CMS_muonES_eta0to1p4_"+shape_year+"Down","_CMS_muonES_eta1p4to2p1_"+shape_year+"Up","_CMS_muonES_eta1p4to2p1_"+shape_year+"Down","_CMS_muonES_eta2p1to2p4_"+shape_year+"Up","_CMS_muonES_eta2p1to2p4_"+shape_year+"Down"};
    //for DY MC only
    TString shape_DY_zpt[2] = {"_CMS_Zpt_reweight_"+shape_year+"Up","_CMS_Zpt_reweight_"+shape_year+"Down"};
    //for ttbar only
    TString shape_ttbar_toppt[2] = {"_CMS_ttbar_toppt_reweight_"+shape_year+"Up","_CMS_ttbar_toppt_reweight_"+shape_year+"Down"};
    //for all MC except diboson, ttbar, single top
    TString shape_recoil[12] = {"_CMS_0jet_resolution_"+shape_year+"Up","_CMS_0jet_resolution_"+shape_year+"Down","_CMS_0jet_response_"+shape_year+"Up","_CMS_0jet_response_"+shape_year+"Down","_CMS_1jet_resolution_"+shape_year+"Up","_CMS_1jet_resolution_"+shape_year+"Down","_CMS_1jet_response_"+shape_year+"Up","_CMS_1jet_response_"+shape_year+"Down","_CMS_gt1jet_resolution_"+shape_year+"Up","_CMS_gt1jet_resolution_"+shape_year+"Down","_CMS_gt1jet_response_"+shape_year+"Up","_CMS_gt1jet_response_"+shape_year+"Down"};
    //only diboson, ttbar, single top
    TString shape_unclusteredES[2] = {"_CMS_unclusteredES_"+shape_year+"Up","_CMS_unclusteredES_"+shape_year+"Down"};
    //jet resolution
    TString shape_jer[2] = {"_CMS_res_j_"+shape_year+"Up","_CMS_res_j_"+shape_year+"Down"};
    //fake cross trigger factor uncertainties
    TString shape_fake_crosstrg[2] = {"_CMS_crosstrg_fakefactor_"+shape_year+"Up","_CMS_crosstrg_fakefactor_"+shape_year+"Down"};
    //fake rate uncertainties
    TString shape_fakerate[14] = {"_CMS_fakerate_alldm_pt0to25_"+shape_year+"Up","_CMS_fakerate_alldm_pt0to25_"+shape_year+"Down","_CMS_fakerate_alldm_pt25to30_"+shape_year+"Up","_CMS_fakerate_alldm_pt25to30_"+shape_year+"Down","_CMS_fakerate_alldm_pt30to35_"+shape_year+"Up","_CMS_fakerate_alldm_pt30to35_"+shape_year+"Down","_CMS_fakerate_alldm_pt35to40_"+shape_year+"Up","_CMS_fakerate_alldm_pt35to40_"+shape_year+"Down","_CMS_fakerate_alldm_pt40to50_"+shape_year+"Up","_CMS_fakerate_alldm_pt40to50_"+shape_year+"Down","_CMS_fakerate_alldm_pt50to60_"+shape_year+"Up","_CMS_fakerate_alldm_pt50to60_"+shape_year+"Down","_CMS_fakerate_alldm_ptgt60_"+shape_year+"Up","_CMS_fakerate_alldm_ptgt60_"+shape_year+"Down"};
    
    //for emb only
    TString embshape_tauideff[14] = {"_CMS_embedding_tauideff_pt20to25_"+shape_year+"Up","_CMS_embedding_tauideff_pt20to25_"+shape_year+"Down","_CMS_embedding_tauideff_pt25to30_"+shape_year+"Up","_CMS_embedding_tauideff_pt25to30_"+shape_year+"Down","_CMS_embedding_tauideff_pt30to35_"+shape_year+"Up","_CMS_embedding_tauideff_pt30to35_"+shape_year+"Down","_CMS_embedding_tauideff_pt35to40_"+shape_year+"Up","_CMS_embedding_tauideff_pt35to40_"+shape_year+"Down","_CMS_embedding_tauideff_pt40to500_"+shape_year+"Up","_CMS_embedding_tauideff_pt40to500_"+shape_year+"Down","_CMS_embedding_tauideff_pt500to1000_"+shape_year+"Up","_CMS_embedding_tauideff_pt500to1000_"+shape_year+"Down","_CMS_embedding_tauideff_ptgt1000_"+shape_year+"Up","_CMS_embedding_tauideff_ptgt1000_"+shape_year+"Down"};
    TString embshape_tauES[8] = {"_CMS_embedding_tauES_dm0_"+shape_year+"Up","_CMS_embedding_tauES_dm0_"+shape_year+"Down","_CMS_embedding_tauES_dm1_"+shape_year+"Up","_CMS_embedding_tauES_dm1_"+shape_year+"Down","_CMS_embedding_tauES_dm10_"+shape_year+"Up","_CMS_embedding_tauES_dm10_"+shape_year+"Down","_CMS_embedding_tauES_dm11_"+shape_year+"Up","_CMS_embedding_tauES_dm11_"+shape_year+"Down"};
    TString embshape_trgeff[4] = {"_CMS_embedding_trgeff_singleMu_"+shape_year+"Up","_CMS_embedding_trgeff_singleMu_"+shape_year+"Down","_CMS_embedding_trgeff_crossMuTau_"+shape_year+"Up","_CMS_embedding_trgeff_crossMuTau_"+shape_year+"Down"};
    TString embshape_muonES[6] = {"_CMS_embedding_muonES_eta0to1p4_"+shape_year+"Up","_CMS_embedding_muonES_eta0to1p4_"+shape_year+"Down","_CMS_embedding_muonES_eta1p4to2p1_"+shape_year+"Up","_CMS_embedding_muonES_eta1p4to2p1_"+shape_year+"Down","_CMS_embedding_muonES_eta2p1to2p4_"+shape_year+"Up","_CMS_embedding_muonES_eta2p1to2p4_"+shape_year+"Down"};
    TString embshape_tautracking[6] = {"_CMS_embedding_tautrack_dm0dm10_"+shape_year+"Up","_CMS_embedding_tautrack_dm0dm10_"+shape_year+"Down","_CMS_embedding_tautrack_dm1_"+shape_year+"Up","_CMS_embedding_tautrack_dm1_"+shape_year+"Down","_CMS_embedding_tautrack_dm11_"+shape_year+"Up","_CMS_embedding_tautrack_dm11_"+shape_year+"Down"};
    if (sample=="embedded"){
        for (int i = 0; i < 14; i++) shape_tauideff[i] = embshape_tauideff[i];
        for (int i = 0; i < 8; i++) shape_tauES[i] = embshape_tauES[i];
        for (int i = 0; i < 4; i++) shape_trgeff[i] = embshape_trgeff[i];
        for (int i = 0; i < 6; i++) shape_muonES[i] = embshape_muonES[i];
    }
    //comtamination to emb: all non-DY MC with gen tautau
    TString shape_nonDY[1] = {"_nonDY"};
    
    std::vector<std::vector<TH1F*>> h_iso;
    std::vector<std::vector<TH1F*>> h_anti;
    for (int i = 0; i < 4; i++){
        h_iso.push_back(std::vector<TH1F*>());
        h_anti.push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 92; i++){//i=0 for nominal, 1-14 tauIDeff, 15-22 tauES, 23-44 jet, 45-46 muon->tauhES, 47-54 ele->tauhES, 55-58 trgeff, 59-64 muonES, 65-70 tau tracking, 71-72 (only DY MC) zpt, 73-74 (only ttbar) toppt, 75-86 recoil, 87-88 met unclustered ES, 89 nonDY, 90-91 jer
        h_iso[0].push_back(new TH1F("","",70,10,150));//pt_1
        h_iso[1].push_back(new TH1F("","",45,10,100));//pt_2
        h_iso[2].push_back(new TH1F("","",40,0,400));//m_tt
        h_iso[3].push_back(new TH1F("","",40,60,460));//m_btt
    }
    for (int i = 0; i < 69; i++){//anti-isolated region, no tau related shifts, no ele/mu->tau shifts since tau is mostly jet //i=0 for nominal, 1-22 jet, 23-26 trgeff, 27-32 muonES, 33-34 (only DY MC) zpt, 35-36 (only ttbar) toppt, 37-48 recoil, 49-50 met unclustered ES, 51-52 jer, 53-54 fake cross trg factor, 55-68 fake rate dmall by pt
        h_anti[0].push_back(new TH1F("","",70,10,150));//pt_1
        h_anti[1].push_back(new TH1F("","",45,10,100));//pt_2
        h_anti[2].push_back(new TH1F("","",40,0,400));//m_tt
        h_anti[3].push_back(new TH1F("","",40,60,460));//m_btt
    }
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    if (year=="2017"){
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
    }
    if (year=="2016") LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");
    
    //Tau id sf files for MC and embedded
    TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
    if (year=="2017") ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco.root");
    if (year=="2016") ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2016Legacy.root");
    TF1 *fct_tauid_nominal = (TF1*) ftauid->Get("Medium_cent");
    TF1 *fct_tauid_up = (TF1*) ftauid->Get("Medium_up");
    TF1 *fct_tauid_down = (TF1*) ftauid->Get("Medium_down");
    if (sample=="embedded"){
        ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco_EMB.root");
        if (year=="2017") ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco_EMB.root");
        if (year=="2016") ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2016Legacy_EMB.root");
        fct_tauid_nominal = (TF1*) ftauid->Get("Medium_cent");
        fct_tauid_up = (TF1*) ftauid->Get("Medium_up");
        fct_tauid_down = (TF1*) ftauid->Get("Medium_down");
    }
    
    //access graphs for the tau fake rates
    TFile *f_taufr = new TFile("FitHistograms_tauFR_2018.root");
    if (year=="2017") f_taufr = new TFile("FitHistograms_tauFR_2017.root");
    if (year=="2016") f_taufr = new TFile("FitHistograms_tauFR_2016.root");
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
        tree_dnn->GetEntry(i);
        
        //MET filters
        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;
        
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        //mutau selection
        /*
        bool trigger24OR27 = ((passMu24 && matchMu24_1 && filterMu24_1) or (passMu27 && matchMu27_1 && filterMu27_1));//keep 25 not 28
        bool trigger2027 = (passMu20Tau27 && matchMu20Tau27_1 && filterMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_2 && fabs(eta_2)<2.1);
        bool trigger2027HPS = (passMu20HPSTau27 && matchMu20HPSTau27_1 && filterMu20HPSTau27_1 && matchMu20HPSTau27_2 && filterMu20HPSTau27_2 && fabs(eta_2)<2.1);
        if (sample=="embedded"){
            trigger2027HPS = (matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20HPSTau27_2 && fabs(eta_2)<2.1);
            trigger24OR27 = ((passMu24 && matchMu24_1) or (passMu27 && matchMu27_1));
        }*/
        
        bool isSingleTrigger = false;
        bool isCrossTrigger = false;
        if (year=="2018"){
            isSingleTrigger = (passMu24 && matchMu24_1 && filterMu24_1) or (passMu27 && matchMu27_1 && filterMu27_1);
            isCrossTrigger = (passMu20HPSTau27 && matchMu20HPSTau27_1 && filterMu20HPSTau27_1 && matchMu20HPSTau27_2 && filterMu20HPSTau27_2 && fabs(eta_2)<2.1);
            if (sample=="data_obs" && run<317509){
                isCrossTrigger = (passMu20Tau27 && matchMu20Tau27_1 && filterMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_2 && fabs(eta_2)<2.1);
            }
            if (sample=="embedded"){
                isSingleTrigger = (passMu24 && matchMu24_1) or (passMu27 && matchMu27_1);
                isCrossTrigger = (matchEmbFilter_Mu20Tau27_1 && matchEmbFilter_Mu20HPSTau27_2 && fabs(eta_2)<2.1);
            }
        }
        if (year=="2017"){
            isSingleTrigger = (passMu24 && matchMu24_1 && filterMu24_1) or (passMu27 && matchMu27_1 && filterMu27_1);
            isCrossTrigger = (passMu20Tau27 && matchMu20Tau27_1 && filterMu20Tau27_1 && matchMu20Tau27_2 && filterMu20Tau27_2 && fabs(eta_2)<2.1);
            if (sample=="embedded"){
                isSingleTrigger = (passMu24 && matchMu24_1) or (passMu27 && matchMu27_1);
                isCrossTrigger = (matchEmbFilter_Mu20Tau27_2017_1 && matchEmbFilter_Mu20Tau27_2 && fabs(eta_2)<2.1);
            }
        }
        if (year=="2016"){
            isSingleTrigger = (passMu22eta2p1 && matchMu22eta2p1_1 && filterMu22eta2p1_1) or (passTkMu22eta2p1 && matchTkMu22eta2p1_1 && filterTkMu22eta2p1_1) or (passMu22 && matchMu22_1 && filterMu22_1) or (passTkMu22 && matchTkMu22_1 && filterTkMu22_1);
            isCrossTrigger = (passMu19Tau20 && matchMu19Tau20_1 && matchMu19Tau20_2 && filterMu19Tau20_1 && filterMu19Tau20_2 && fabs(eta_2)<2.1) or (passMu19Tau20SingleL1 && matchMu19Tau20SingleL1_1 && matchMu19Tau20SingleL1_2 && filterMu19Tau20SingleL1_1 && filterMu19Tau20SingleL1_2 && fabs(eta_2)<2.1);
        }
        
        if (!isSingleTrigger && !isCrossTrigger) continue;
        
        //if (sample=="data_obs" && run<317509 && !trigger2027 && !trigger24OR27) continue;
        //if (sample=="data_obs" && run>=317509 && !trigger2027HPS && !trigger24OR27) continue;
        //if (sample!="data_obs" && sample!="embedded" && !trigger24OR27 && !trigger2027HPS) continue;
        //if (sample=="embedded" && !trigger24OR27 && !trigger2027HPS) continue;
        //trigger var only, add pt requirements later when doing systematics
        //if (!(pt_2>20)) continue;
        if (!(fabs(eta_1)<2.1 && fabs(eta_2)<2.3)) continue;
        if (!(iso_1<0.15)) continue;
        if (q_1*q_2>0) continue;
        
        //discriminators for e/mu faking tau_h (many Z->mumu so tight for mu; rare e+mu so loose for e)
        if (!(byVLooseDeepVSe_2 && byTightDeepVSmu_2)) continue;
        
        if (!(mymu.DeltaR(mytau)>0.4)) continue;
        
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
            if (numGenJets==0){
                weight = 3.630;
                if (year=="2017") weight = 2.575;
                if (year=="2016") weight = 1.491;
            }
            else if (numGenJets==1){
                weight = 0.6304;
                if (year=="2017") weight = 0.7084;
                if (year=="2016") weight = 0.4757;
            }
            else if (numGenJets==2){
                weight = 0.5528;
                if (year=="2017") weight = 0.9192;
                if (year=="2016") weight = 0.4952;
            }
            else if (numGenJets==3){
                weight = 0.6009;
                if (year=="2017") weight = 1.648;
                if (year=="2016") weight = 0.5052;
            }
            else if (numGenJets==4){
                weight = 0.8314;
                if (year=="2017") weight = 0.2192;
                if (year=="2016") weight = 0.4144;
            }
        }
        
        if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"){
            if (numGenJets==0){
                weight = 51.81;
                if (year=="2017") weight = 23.67;
                if (year=="2016") weight = 25.46;
            }
            else if (numGenJets==1){
                weight = 9.091;
                if (year=="2017") weight = 3.106;
                if (year=="2016") weight = 5.773;
            }
            else if (numGenJets==2){
                weight = 4.516;
                if (year=="2017") weight = 3.014;
                if (year=="2016") weight = 1.792;
            }
            else if (numGenJets==3){
                weight = 3.090;
                if (year=="2017") weight = 2.202;
                if (year=="2016") weight = 0.6829;
            }
            else if (numGenJets==4){
                weight = 3.227;
                if (year=="2017") weight = 2.150;
                if (year=="2016") weight = 0.7365;
            }
        }
        
        float sf_MC = 1.0;
        float topfactor = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            //reject MC with a jet faking tau_h as duplicated in fake background estimation
            if (gen_match_2==6) continue;
            
            //reject MC with 2 taus as duplicated in embedded sample except for signal/Higgs
            //if (sample!="data_obs" && sample!="embedded" && sample!="gghbbtt12" && sample!="gghbbtt20" && sample!="gghbbtt30" && sample!="gghbbtt40" && sample!="gghbbtt50" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt20" && sample!="vbfbbtt30" && sample!="vbfbbtt40" && sample!="vbfbbtt50" && sample!="vbfbbtt60" && name!="HTT" && name!="ttHnonbb" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            /*
            //trigger scale factor
            if (isSingleTrigger && pt_1>25){//this cut is valid only when mu is nominal, need re-apply mu pt cut later when shifting mu ES
                sf_MC *= m_trg_ic_ratio;
            }
            else{
                sf_MC *= m_trg_20_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
            }*/
            
            //muon ID/iso/tracking scale factors
            sf_MC *= m_trk_ratio * m_idiso_ic_ratio;
            
            //re-weigh Z pT spectrum for DY samples
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                sf_MC *= zptmass_weight_nom;
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){
                float pttop1=pt_top1;
                if (pttop1>472) pttop1=472;
                float pttop2=pt_top2;
                if (pttop2>472) pttop2=472;
                topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
            }
            
            //re-weigh pileup distribution
            sf_MC *= LumiWeights_12->weight(npu);
            
            //generator weight
            sf_MC *= genweight;
            
            float taufakesf = 1.0;
            //ele->tauh and muon->tauh sf
            if (gen_match_2==1 or gen_match_2==3){
                if (fabs(eta_2)<1.448){
                    taufakesf = 0.95;
                    if (year=="2017") taufakesf = 0.93;
                    if (year=="2016") taufakesf = 1.22;
                }
                else {
                    taufakesf = 0.86;
                    if (year=="2017") taufakesf = 1.00;
                    if (year=="2016") taufakesf = 1.13;
                }
            }
            if (gen_match_2==2 or gen_match_2==4){
                if (fabs(eta_2)<0.4){
                    taufakesf = 0.936*0.820;
                    if (year=="2017") taufakesf = 0.979*0.991;
                    if (year=="2016") taufakesf = 0.978*1.463;
                }
                else if (fabs(eta_2)<0.8){
                    taufakesf = 0.874*1.436;
                    if (year=="2017") taufakesf = 0.953*0.675;
                    if (year=="2016") taufakesf = 1.003*0.722;
                }
                else if (fabs(eta_2)<1.2){
                    taufakesf = 0.912*0.989;
                    if (year=="2017") taufakesf = 0.983*0.675;
                    if (year=="2016") taufakesf = 0.992*1.337;
                }
                else if (fabs(eta_2)<1.7){
                    taufakesf = 0.953*0.875;
                    if (year=="2017") taufakesf = 0.988*1.098;
                    if (year=="2016") taufakesf = 1.003*0.966;
                }
                else {
                    taufakesf = 0.936*4.739;
                    if (year=="2017") taufakesf = 1.004*4.175;
                    if (year=="2016") taufakesf = 0.966*5.451;
                }
            }
            sf_MC *= taufakesf;
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
            /*
            //trigger scale factor
            if (isSingleTrigger && pt_1>25){//this cut is valid only when mu is nominal, need re-apply mu pt cut later when shifting mu ES
                sf_MC *= m_trg_ic_embed_ratio;
            }
            else{
                sf_MC *= m_trg_20_ic_embed_ratio * t_trg_mediumDeepTau_mutau_embed_ratio;
            }//t_trg_pog_deeptau_medium_mutau_ratio
            */
            //muon ID/iso/tracking scale factors
            sf_embed *= m_trk_ratio * m_idiso_ic_embed_ratio;
            
            //efficiency of selecting Z->mumu data
            sf_embed *= m_sel_trg_ic_ratio * m_sel_id_ic_ratio_1 * m_sel_id_ic_ratio_2;
            
            //generator weight
            sf_embed *= genweight;
        }
        
        float weight_corr = weight * sf_MC * sf_embed;//end of applying fixed (no shifted systematics) scale factors to MC
        
        //counting reconstructed btagged jets
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        float bscore_thres = 0.4184;
        if (year=="2017") bscore_thres = 0.4941;
        if (year=="2016") bscore_thres = 0.6321;
        if (bpt_deepcsv_1>20 && bscore_deepcsv_1>bscore_thres && fabs(beta_deepcsv_1)<2.4){
            bMpt_1 = bpt_deepcsv_1;
            bMflavor_1 = bflavour_deepcsv_1;
            nbtag20++;
        }
        if (bpt_deepcsv_2>20 && bscore_deepcsv_2>bscore_thres && fabs(beta_deepcsv_2)<2.4){
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
            //0 bjet
            weight_btag_0b = bTagEventWeight2018(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
            if (year=="2017") weight_btag_0b = bTagEventWeight2017(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
            if (year=="2016") weight_btag_0b = bTagEventWeight2016(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
            //1 bjet
            weight_btag_1b = GetSF2018(1, bMpt_1, bMflavor_1, 0);
            if (year=="2017") weight_btag_1b = GetSF2017(1, bMpt_1, bMflavor_1, 0);
            if (year=="2016") weight_btag_1b = GetSF2016(1, bMpt_1, bMflavor_1, 0);
            //2 bjets
            weight_btag_2b = GetSF2018(1, bMpt_1, bMflavor_1, 0)*GetSF2018(1, bMpt_2, bMflavor_2, 0);
            if (year=="2017") weight_btag_2b = GetSF2017(1, bMpt_1, bMflavor_1, 0)*GetSF2017(1, bMpt_2, bMflavor_2, 0);
            if (year=="2016") weight_btag_2b = GetSF2016(1, bMpt_1, bMflavor_1, 0)*GetSF2016(1, bMpt_2, bMflavor_2, 0);
        }
        if (nbtag20==0) weight_corr *= weight_btag_0b;
        else if (nbtag20==1) weight_corr *= weight_btag_1b;
        else weight_corr *= weight_btag_2b;
        
        //nominal var
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        TLorentzVector mytt;
        mytt.SetPtEtaPhiM((mymu+mytau+mymet).Pt(),(mymu+mytau+mymet).Eta(),(mymu+mytau+mymet).Phi(),m_sv);
        
        float m_btt = (mytt + myb1).M();
        float m_bbtt = (mytt + myb1 + myb2).M();
        
        float mt_tau1=TMass_F((mymu).Pt(),mymet.Pt(),(mymu).Px(),mymet.Px(),(mymu).Py(),mymet.Py());
        float mt_tau2=TMass_F((mytau).Pt(),mymet.Pt(),(mytau).Px(),mymet.Px(),(mytau).Py(),mymet.Py());
        
        float norm_zeta=norm_F(mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt(),mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (mymu.Px()/mymu.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (mymu.Py()/mymu.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(mymu.Px()+mytau.Px())*x_zeta+(mymu.Py()+mytau.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        //#####################tau ES shifting: mytau, mymet, mytt###########################
        std::vector<TLorentzVector> myshiftedtau;
        std::vector<TLorentzVector> mymet_shiftedtau;
        std::vector<TLorentzVector> mytt_shiftedtau;
        std::vector<float> m_btt_shiftedtau;
        for (int j = 0; j < 8; j++){//define their default values (untouched when not gentau or DM not matched)
            myshiftedtau.push_back(mytau);
            mymet_shiftedtau.push_back(mymet);
            mytt_shiftedtau.push_back(mytt);
            m_btt_shiftedtau.push_back(m_btt);
        }
        float taudecaymode[4] = {0,1,10,11};
        float tauES_updowntonom_bymode[8] = {(0.984+0.009)/0.984,(0.984-0.009)/0.984,(0.996+0.006)/0.996,(0.996-0.006)/0.996,(0.988+0.007)/0.988,(0.988-0.007)/0.988,(0.996+0.012)/0.996,(0.996-0.012)/0.996};//=(ES_nom+/-uncert)/ES_nom, mytau already had nominal tes correction applied at skimming levle; ordered by: mode0up, mode0down, mode1up, mode1down,...
        float tauES_updowntonom_bymode2017[8] = {(0.984+0.009)/0.984,(0.984-0.009)/0.984,(0.996+0.006)/0.996,(0.996-0.006)/0.996,(0.988+0.007)/0.988,(0.988-0.007)/0.988,(0.996+0.012)/0.996,(0.996-0.012)/0.996};
        float tauES_updowntonom_bymode2016[8] = {(0.984+0.009)/0.984,(0.984-0.009)/0.984,(0.996+0.006)/0.996,(0.996-0.006)/0.996,(0.988+0.007)/0.988,(0.988-0.007)/0.988,(0.996+0.012)/0.996,(0.996-0.012)/0.996};
        if (year=="2017"){
            for (int j = 0; j < 8; j++) tauES_updowntonom_bymode[j] = tauES_updowntonom_bymode2017[j];
        }
        if (year=="2016"){
            for (int j = 0; j < 8; j++) tauES_updowntonom_bymode[j] = tauES_updowntonom_bymode2016[j];
        }
        float tauES_updowntonom_bymode_emb[8] = {1.0039,0.9961,1.0037,0.9969,1.0032,0.9968,1.0032,0.9968};
        if (sample=="embedded"){
            for (int j = 0; j < 8; j++){
                tauES_updowntonom_bymode[j] = tauES_updowntonom_bymode_emb[j];
            }
        }
        for (int j = 0; j < 4; j++){
            if (gen_match_2==5 && l2_decayMode==taudecaymode[j]){//shift only when tau is real and DM is matched
                //[0]dm0up, [1]dm0down, [2]dm1up, [3]dm1down, [4]dm10up, [5]dm10down, [6]dm11up, [7]dm11down
                myshiftedtau[2*j] *= tauES_updowntonom_bymode[2*j];
                myshiftedtau[2*j+1] *= tauES_updowntonom_bymode[2*j+1];
                //after tau is shifted, shift the met
                mymet_shiftedtau[2*j] = mymet + mytau - myshiftedtau[2*j];
                mymet_shiftedtau[2*j+1] = mymet + mytau - myshiftedtau[2*j+1];
                //after tau and met are shifted, shift the ditau system
                mytt_shiftedtau[2*j].SetPtEtaPhiM((mymu+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Pt(),(mymu+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Eta(),(mymu+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Phi(),m_sv_UP);
                mytt_shiftedtau[2*j+1].SetPtEtaPhiM((mymu+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Pt(),(mymu+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Eta(),(mymu+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Phi(),m_sv_DOWN);
                //after mytt is shifted, shift the mass m_btt
                m_btt_shiftedtau[2*j] = (mytt_shiftedtau[2*j]+myb1).M();
                m_btt_shiftedtau[2*j+1] = (mytt_shiftedtau[2*j+1]+myb1).M();
            }//everything is nominal if not gentau or DM not matched, by default
        }
        
        //###################tauId scale factors (shifted sf by pt bins or shifted tau with nom sf)####################
        std::vector<float> sf_tauid;
        for (int j = 0; j < 23; ++j){//j=0 nominal, 1-14 shifted sf, 15-22 shifted tau
            sf_tauid.push_back(1.0);
        }//they are all 1.0 for data_obs/not real tau/anti-isolated tau
        //evaluate tauId scale factor, on real tau
        if (sample!="data_obs" && byMediumDeepVSjet_2 && gen_match_2==5){
            //nominal
            sf_tauid[0] = fct_tauid_nominal->Eval(pt_2);
            //shifted tauID scale factors evaluated with nominal tau pt bins
            float tauid_ptbins[8] = {20,25,30,35,40,500,1000,10000};
            for (int j = 0; j < 7; j++){
                if (pt_2>tauid_ptbins[j] && pt_2<=tauid_ptbins[j+1]){
                    //sf_tauid[1]: sf up only in 20<nominal_tau_pt<25, sf nominal otherwise
                    //sf_tauid[2]: sf down only in 20<nominal_tau_pt<25, sf nominal otherwise
                    //sf_tauid[3]: sf up only in 25<nominal_tau_pt<30, sf nominal otherwise
                    //sf_tauid[4]: sf down only in 25<nominal_tau_pt<30, sf nominal otherwise...
                    sf_tauid[2*j+1] = fct_tauid_up->Eval(pt_2);
                    sf_tauid[2*j+2] = fct_tauid_down->Eval(pt_2);
                }
                else{
                    sf_tauid[2*j+1] = fct_tauid_nominal->Eval(pt_2);
                    sf_tauid[2*j+2] = fct_tauid_nominal->Eval(pt_2);
                }
            }
            //nominal tauID scale factors evaluated with shifted tau
            for (int j = 0; j < 8; j++){
                //sf_tauid[15]: nominal tauid sf evaluated with tau shifted up for mode 0 only
                //sf_tauid[16]: nominal tauid sf evaluated with tau shifted down for mode 0 only
                //sf_tauid[17]: nominal tauid sf evaluated with tau shifted up for mode 1 only
                //sf_tauid[18]: nominal tauid sf evaluated with tau shifted down for mode 1 only...
                sf_tauid[15+j] = fct_tauid_nominal->Eval(myshiftedtau[j].Pt());
            }
        }
        
        //########################muon faking tau ES shifting: mytau, mymet, mytt, m_btt##########################
        std::vector<TLorentzVector> mytau_isgenmu;
        std::vector<TLorentzVector> mymet_isgenmu;
        std::vector<TLorentzVector> mytt_isgenmu;
        std::vector<float> m_btt_isgenmu;
        for (int j = 0; j < 2; j++){
            mytau_isgenmu.push_back(mytau);
            mymet_isgenmu.push_back(mymet);
            mytt_isgenmu.push_back(mytt);
            m_btt_isgenmu.push_back(m_btt);
        }
        float tauES_mufake[2] = {1.01,0.99};//nominal ES correction for muon->tau = 1.0
        for (int j = 0; j < 1; j++){
            if (gen_match_2==2 or gen_match_2==4){
                //mytau
                mytau_isgenmu[2*j] *= tauES_mufake[2*j];
                mytau_isgenmu[2*j+1] *= tauES_mufake[2*j+1];
                //mymet
                mymet_isgenmu[2*j] = mymet + mytau - mytau_isgenmu[2*j];
                mymet_isgenmu[2*j+1] = mymet + mytau - mytau_isgenmu[2*j+1];
                //mytt
                mytt_isgenmu[2*j].SetPtEtaPhiM((mymu+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Pt(),(mymu+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Eta(),(mymu+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Phi(),m_sv_UP);
                mytt_isgenmu[2*j+1].SetPtEtaPhiM((mymu+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Pt(),(mymu+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Eta(),(mymu+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Phi(),m_sv_DOWN);
                m_btt_isgenmu[2*j] = (mytt_isgenmu[2*j]+myb1).M();
                m_btt_isgenmu[2*j+1] = (mytt_isgenmu[2*j+1]+myb1).M();
            }
        }
        
        //########################electron faking tauh ES shifting, mytau, mymet, mytt, m_btt#######################
        std::vector<TLorentzVector> mytau_isgenele;
        std::vector<TLorentzVector> mymet_isgenele;
        std::vector<TLorentzVector> mytt_isgenele;
        std::vector<float> m_btt_isgenele;
        for (int j = 0; j < 8; j++){
            mytau_isgenele.push_back(mytau);
            mymet_isgenele.push_back(mymet);
            mytt_isgenele.push_back(mytt);
            m_btt_isgenele.push_back(m_btt);
        }//ordering: dm0barup, dm0bardown, dm0endup, dm0enddown, dm1barup, dm1bardown, dm1endup, dm1enddown
        float tauES_elefake[8] = {1.02266/1.01362,1.00888/1.01362,1.00307/0.96903,0.95653/0.96903,1.03171/1.01945,1.00347/1.01945,1.03999/0.985,0.94191/0.985};
        float tauES_elefake2017[8] = {1.02266/1.01362,1.00888/1.01362,1.00307/0.96903,0.95653/0.96903,1.03171/1.01945,1.00347/1.01945,1.03999/0.985,0.94191/0.985};
        float tauES_elefake2016[8] = {1.02266/1.01362,1.00888/1.01362,1.00307/0.96903,0.95653/0.96903,1.03171/1.01945,1.00347/1.01945,1.03999/0.985,0.94191/0.985};
        if (year=="2017"){
            for (int j = 0; j < 8; j++) tauES_elefake[j] = tauES_elefake2017[j];
        }
        if (year=="2016"){
            for (int j = 0; j < 8; j++) tauES_elefake[j] = tauES_elefake2016[j];
        }
        if (gen_match_2==1 or gen_match_2==3){
            for (int j = 0; j < 2; j++){
                if (l2_decayMode==taudecaymode[j]){//j=0 DM=0, j=1 DM=1
                    //barrel
                    if (fabs(eta_2)<1.5){
                        //mytau
                        mytau_isgenele[4*j] *= tauES_elefake[4*j];
                        mytau_isgenele[4*j+1] *= tauES_elefake[4*j+1];
                        //mymet
                        mymet_isgenele[4*j] = mymet + mytau - mytau_isgenele[4*j];
                        mymet_isgenele[4*j+1] = mymet + mytau - mytau_isgenele[4*j+1];
                        //mytt
                        mytt_isgenele[4*j].SetPtEtaPhiM((mymu+mytau_isgenele[4*j]+mymet_isgenele[4*j]).Pt(),(mymu+mytau_isgenele[4*j]+mymet_isgenele[4*j]).Eta(),(mymu+mytau_isgenele[4*j]+mymet_isgenele[4*j]).Phi(),m_sv_UP);
                        mytt_isgenele[4*j+1].SetPtEtaPhiM((mymu+mytau_isgenele[4*j+1]+mymet_isgenele[4*j+1]).Pt(),(mymu+mytau_isgenele[4*j+1]+mymet_isgenele[4*j+1]).Eta(),(mymu+mytau_isgenele[4*j+1]+mymet_isgenele[4*j+1]).Phi(),m_sv_DOWN);
                        //m_btt
                        m_btt_isgenele[4*j] = (mytt_isgenele[4*j]+myb1).M();
                        m_btt_isgenele[4*j+1] = (mytt_isgenele[4*j+1]+myb1).M();
                    }
                    //endcaps
                    else {
                        //mytau
                        mytau_isgenele[4*j+2] *= tauES_elefake[4*j+2];
                        mytau_isgenele[4*j+3] *= tauES_elefake[4*j+3];
                        //mymet
                        mymet_isgenele[4*j+2] = mymet + mytau - mytau_isgenele[4*j+2];
                        mymet_isgenele[4*j+3] = mymet + mytau - mytau_isgenele[4*j+3];
                        //mytt
                        mytt_isgenele[4*j+2].SetPtEtaPhiM((mymu+mytau_isgenele[4*j+2]+mymet_isgenele[4*j+2]).Pt(),(mymu+mytau_isgenele[4*j+2]+mymet_isgenele[4*j+2]).Eta(),(mymu+mytau_isgenele[4*j+2]+mymet_isgenele[4*j+2]).Phi(),m_sv_UP);
                        mytt_isgenele[4*j+3].SetPtEtaPhiM((mymu+mytau_isgenele[4*j+3]+mymet_isgenele[4*j+3]).Pt(),(mymu+mytau_isgenele[4*j+3]+mymet_isgenele[4*j+3]).Eta(),(mymu+mytau_isgenele[4*j+3]+mymet_isgenele[4*j+3]).Phi(),m_sv_DOWN);
                        //m_btt
                        m_btt_isgenele[4*j+2] = (mytt_isgenele[4*j+2]+myb1).M();
                        m_btt_isgenele[4*j+3] = (mytt_isgenele[4*j+3]+myb1).M();
                    }
                }
            }
        }
        
        //#####################muon ES shifting##############################
        std::vector<TLorentzVector> myshiftedmu;
        std::vector<TLorentzVector> mymet_shiftedmu;
        std::vector<TLorentzVector> mytt_shiftedmu;
        std::vector<float> m_btt_shiftedmu;
        for (int j = 0; j < 6; j++){
            myshiftedmu.push_back(mymu);
            mymet_shiftedmu.push_back(mymet);
            mytt_shiftedmu.push_back(mytt);
            m_btt_shiftedmu.push_back(m_btt);
        }
        float muonESetabins[4] = {0,1.4,2.1,2.4};
        float muonES_updowntonom_byeta[6] = {1.004,0.996,1.009,0.991,1.027,0.973};//correction on top of nominal already applied; ordered by: eta1.4updown, 1.4eta2.1updown, 2.1eta2.4updown; same for both MC and emb
        for (int j = 0; j < 3; j++){
            if ((gen_match_1==2 or gen_match_1==4) && fabs(eta_1)>muonESetabins[j] && fabs(eta_1)<muonESetabins[j+1]){
                //mymu
                myshiftedmu[2*j] *= muonES_updowntonom_byeta[2*j];
                myshiftedmu[2*j+1] *= muonES_updowntonom_byeta[2*j+1];
                //mymet
                mymet_shiftedmu[2*j] = mymet + mymu - myshiftedmu[2*j];
                mymet_shiftedmu[2*j+1] = mymet + mymu - myshiftedmu[2*j+1];;
                //mytt
                mytt_shiftedmu[2*j].SetPtEtaPhiM((myshiftedmu[2*j]+mytau+mymet_shiftedmu[2*j]).Pt(),(myshiftedmu[2*j]+mytau+mymet_shiftedmu[2*j]).Eta(),(myshiftedmu[2*j]+mytau+mymet_shiftedmu[2*j]).Phi(),m_sv_muonESUp);
                mytt_shiftedmu[2*j+1].SetPtEtaPhiM((myshiftedmu[2*j+1]+mytau+mymet_shiftedmu[2*j+1]).Pt(),(myshiftedmu[2*j+1]+mytau+mymet_shiftedmu[2*j+1]).Eta(),(myshiftedmu[2*j+1]+mytau+mymet_shiftedmu[2*j+1]).Phi(),m_sv_muonESDown);
                //m_btt
                m_btt_shiftedmu[2*j] = (mytt_shiftedmu[2*j]+myb1).M();
                m_btt_shiftedmu[2*j+1] = (mytt_shiftedmu[2*j+1]+myb1).M();
            }
        }
        
        //define trigger pt thresholds for different years
        float single_mupt_thres = 25;
        float single_taupt_thres = 20;
        float cross_mupt_thres = 21;
        float cross_taupt_thres = 32;
        if (year=="2016"){
            single_mupt_thres = 23;
            single_taupt_thres = 20;
            cross_mupt_thres = 20;
            cross_taupt_thres = 25;
        }
        //###################re-apply trigger scale factor for re-defined single/cross trigger regions due to shifted muon####################
        //define trigger sf with nominal muon ES (the usual weights)
        float trgsf = 1.0;
        float trgsf_single = 1.0;
        float trgsf_cross = 1.0;
        if (sample!="data_obs"){
            if (year=="2018"){
                if (sample!="embedded"){
                    trgsf_single = m_trg_ic_ratio;
                    trgsf_cross = m_trg_20_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
                }
                if (sample=="embedded"){
                    trgsf_single = m_trg_ic_embed_ratio;
                    trgsf_cross = m_trg_20_ic_embed_ratio * t_trg_mediumDeepTau_mutau_embed_ratio;
                }
            }
            if (year=="2017"){
                if (sample!="embedded"){
                    trgsf_single = m_trg_ic_ratio;
                    trgsf_cross = m_trg_MuTau_Mu20Leg_desy_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
                }
                if (sample=="embedded"){
                    trgsf_single = m_trg_ic_embed_ratio;
                    trgsf_cross = m_trg_20_ic_embed_ratio * t_trg_mediumDeepTau_mutau_embed_ratio;
                }
            }
            if (year=="2016"){
                if (sample!="embedded"){
                    trgsf_single = m_trg_ic_ratio;
                    trgsf_cross = m_trg_19_ic_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
                }
                if (sample=="embedded"){
                    trgsf_single = m_trg_ic_embed_ratio;
                    trgsf_cross = m_trg_19_ic_embed_ratio * t_trg_pog_deeptau_medium_mutau_ratio;
                }
            }
        }
        if (isSingleTrigger && pt_1>single_mupt_thres) trgsf = trgsf_single;
        if (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres) trgsf = trgsf_cross;
        
        //for shifted trigger regions due to shifted muon ES
        std::vector<float> trgsf_shiftedmu;
        for (int j = 0; j < 6; j++){
            trgsf_shiftedmu.push_back(1.0);
            if (isSingleTrigger && myshiftedmu[j].Pt()>single_mupt_thres) trgsf_shiftedmu[j] = trgsf_single;
            if (isCrossTrigger && myshiftedmu[j].Pt()<single_mupt_thres && myshiftedmu[j].Pt()>cross_mupt_thres) trgsf_shiftedmu[j] = trgsf_cross;
        }
        
        //#######################jet uncertainties shifting########################
        float met_jetvar[22] = {met_JetAbsoluteUp,met_JetAbsoluteDown,met_JetAbsoluteyearUp,met_JetAbsoluteyearDown,met_JetBBEC1Up,met_JetBBEC1Down,met_JetBBEC1yearUp,met_JetBBEC1yearDown,met_JetEC2Up,met_JetEC2Down,met_JetEC2yearUp,met_JetEC2yearDown,met_JetFlavorQCDUp,met_JetFlavorQCDDown,met_JetHFUp,met_JetHFDown,met_JetHFyearUp,met_JetHFyearDown,met_JetRelativeBalUp,met_JetRelativeBalDown,met_JetRelativeSampleUp,met_JetRelativeSampleDown};
        float metphi_jetvar[22] = {metphi_JetAbsoluteUp,metphi_JetAbsoluteDown,metphi_JetAbsoluteyearUp,metphi_JetAbsoluteyearDown,metphi_JetBBEC1Up,metphi_JetBBEC1Down,metphi_JetBBEC1yearUp,metphi_JetBBEC1yearDown,metphi_JetEC2Up,metphi_JetEC2Down,metphi_JetEC2yearUp,metphi_JetEC2yearDown,metphi_JetFlavorQCDUp,metphi_JetFlavorQCDDown,metphi_JetHFUp,metphi_JetHFDown,metphi_JetHFyearUp,metphi_JetHFyearDown,metphi_JetRelativeBalUp,metphi_JetRelativeBalDown,metphi_JetRelativeSampleUp,metphi_JetRelativeSampleDown};
        float m_sv_jetvar[22] = {m_sv_JetAbsoluteUp,m_sv_JetAbsoluteDown,m_sv_JetAbsoluteyearUp,m_sv_JetAbsoluteyearDown,m_sv_JetBBEC1Up,m_sv_JetBBEC1Down,m_sv_JetBBEC1yearUp,m_sv_JetBBEC1yearDown,m_sv_JetEC2Up,m_sv_JetEC2Down,m_sv_JetEC2yearUp,m_sv_JetEC2yearDown,m_sv_JetFlavorQCDUp,m_sv_JetFlavorQCDDown,m_sv_JetHFUp,m_sv_JetHFDown,m_sv_JetHFyearUp,m_sv_JetHFyearDown,m_sv_JetRelativeBalUp,m_sv_JetRelativeBalDown,m_sv_JetRelativeSampleUp,m_sv_JetRelativeSampleDown};
        std::vector<TLorentzVector> mymet_jet;
        std::vector<TLorentzVector> mytt_jet;
        std::vector<float> m_btt_jet;
        for (int j = 0; j < 22; j++){
            mymet_jet.push_back(mymet);
            mytt_jet.push_back(mytt);
            mymet_jet[j].SetPtEtaPhiM(met_jetvar[j],0,metphi_jetvar[j],0);
            mytt_jet[j].SetPtEtaPhiM((mymu+mytau+mymet_jet[j]).Pt(),(mymu+mytau+mymet_jet[j]).Eta(),(mymu+mytau+mymet_jet[j]).Phi(),m_sv_jetvar[j]);
            m_btt_jet.push_back((mytt_jet[j]+myb1).M());
        }
        
        //##########################tau tracking uncertainties####################################
        std::vector<float> tau_tracking_shifting;
        for (int j = 0; j < 6; j++){//ordered by: dm0dm10up, dm0dm10down, dm1up, dm1down, dm11up, dm11down
            tau_tracking_shifting.push_back(1);
        }
        if (gen_match_2==5){
            if (l2_decayMode==0){//+/-1%
                tau_tracking_shifting[0] = 1.01;
                tau_tracking_shifting[1] = 0.99;
            }
            if (l2_decayMode==10){//+/-3%
                tau_tracking_shifting[0] = 1.03;
                tau_tracking_shifting[1] = 0.97;
            }
            if (l2_decayMode==1){//+/-2.5%
                tau_tracking_shifting[2] = 1.025;
                tau_tracking_shifting[3] = 0.975;
            }
            if (l2_decayMode==11){//+/-6%
                tau_tracking_shifting[4] = 1.06;
                tau_tracking_shifting[5] = 0.94;
            }
        }
        
        //#########################DY MC Z pt reweight uncertainties################################
        std::vector<float> zptmass_weight_shifting;
        for (int j = 0; j < 2; j++){
            zptmass_weight_shifting.push_back(1);
        }
        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){//+/-10% of correction i.e. 1.5 -> 1.55/1.45
            if (zptmass_weight_nom>1){
                zptmass_weight_shifting[0] = 1 + (1 - 1/zptmass_weight_nom)*0.1;
                zptmass_weight_shifting[1] = 1 - (1 - 1/zptmass_weight_nom)*0.1;
            }
            if (zptmass_weight_nom<1){
                zptmass_weight_shifting[0] = 1 + (1/zptmass_weight_nom - 1)*0.1;//down/up?
                zptmass_weight_shifting[1] = 1 - (1/zptmass_weight_nom - 1)*0.1;
            }
        }
        
        //##########################ttbar top pt reweight uncertainties##############################
        std::vector<float> topfactor_shifting;
        for (int j = 0; j < 2; j++){
            topfactor_shifting.push_back(1);
        }
        if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){//apply twice for up and not at all for down
            topfactor_shifting[0] = topfactor;
            topfactor_shifting[1] = 1/topfactor;
        }
        
        //#######################recoil uncertainties########################
        float met_recoilvar[4] = {met_resolutionUp,met_resolutionDown,met_responseUp,met_responseDown};
        float metphi_recoilvar[4] = {metphi_resolutionUp,metphi_resolutionDown,metphi_responseUp,metphi_responseDown};
        float m_sv_recoilvar[4] = {m_sv_ResolutionUp,m_sv_ResolutionDown,m_sv_ResponseUp,m_sv_ResponseDown};
        std::vector<TLorentzVector> mymet_recoil;
        std::vector<TLorentzVector> mytt_recoil;
        std::vector<float> m_btt_recoil;
        for (int j = 0; j < 12; j++){//ordered by: 0jet resolutionUp/Down, responseUp/Down, 1jet resolutionUp/Down, responseUp/Down, 2jetsmore resolutionUp/Down, responseUp/Down
            mymet_recoil.push_back(mymet);
            mytt_recoil.push_back(mytt);
            m_btt_recoil.push_back(m_btt);
        }
        float njetsbins[4] = {0,1,2,10};
        for (int j = 0; j < 3; j++){
            if (njets>=njetsbins[j] && njets<njetsbins[j+1]){
                for (int k = 0; k < 4; k++){
                    mymet_recoil[4*j+k].SetPtEtaPhiM(met_recoilvar[k],0,metphi_recoilvar[k],0);
                    mytt_recoil[4*j+k].SetPtEtaPhiM((mymu+mytau+mymet_recoil[4*j+k]).Pt(),(mymu+mytau+mymet_recoil[4*j+k]).Eta(),(mymu+mytau+mymet_recoil[4*j+k]).Phi(),m_sv_recoilvar[k]);
                    m_btt_recoil[4*j+k] = (mytt_recoil[4*j+k]+myb1).M();
                }
            }
        }
        
        //#######################met unclustered ES########################
        float met_UESvar[2] = {met_UESUp,met_UESDown};
        float metphi_UESvar[2] = {metphi_UESUp,metphi_UESDown};
        float m_sv_UESvar[2] = {m_sv_UESUp,m_sv_UESDown};
        std::vector<TLorentzVector> mymet_UES;
        std::vector<TLorentzVector> mytt_UES;
        std::vector<float> m_btt_UES;
        for (int j = 0; j < 2; j++){//ordered by: UES Up/Down
            mymet_UES.push_back(mymet);
            mytt_UES.push_back(mytt);
            m_btt_UES.push_back(m_btt);
            
            mymet_UES[j].SetPtEtaPhiM(met_UESvar[j],0,metphi_UESvar[j],0);
            mytt_UES[j].SetPtEtaPhiM((mymu+mytau+mymet_UES[j]).Pt(),(mymu+mytau+mymet_UES[j]).Eta(),(mymu+mytau+mymet_UES[j]).Phi(),m_sv_UESvar[j]);
            m_btt_UES[j] = (mytt_UES[j]+myb1).M();
        }
        
        //#######################jer uncertainties########################
        float met_jervar[2] = {met_JERUp,met_JERDown};
        float metphi_jervar[2] = {metphi_JERUp,metphi_JERDown};
        float m_sv_jervar[2] = {m_sv_JERUp,m_sv_JERDown};
        std::vector<TLorentzVector> mymet_jer;
        std::vector<TLorentzVector> mytt_jer;
        std::vector<float> m_btt_jer;
        for (int j = 0; j < 2; j++){
            mymet_jer.push_back(mymet);
            mytt_jer.push_back(mytt);
            mymet_jer[j].SetPtEtaPhiM(met_jervar[j],0,metphi_jervar[j],0);
            mytt_jer[j].SetPtEtaPhiM((mymu+mytau+mymet_jer[j]).Pt(),(mymu+mytau+mymet_jer[j]).Eta(),(mymu+mytau+mymet_jer[j]).Phi(),m_sv_jervar[j]);
            m_btt_jer.push_back((mytt_jer[j]+myb1).M());
        }
        
        //##########################trigger regions with nominal/shifted ES###########################
        //nominal
        bool trigger_region_nominal = (isSingleTrigger && pt_1>single_mupt_thres && pt_2>single_taupt_thres) or (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres && pt_2>cross_taupt_thres);
        //shifted tau ES
        std::vector<bool> trigger_region_shiftedtau;
        for (int j = 0; j < 8; j++){
            trigger_region_shiftedtau.push_back(0);
            trigger_region_shiftedtau[j] = (isSingleTrigger && pt_1>single_mupt_thres && myshiftedtau[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres && myshiftedtau[j].Pt()>cross_taupt_thres);
        }
        //muon->tauh fake ES
        std::vector<bool> trigger_region_tauisgenmu;
        for (int j = 0; j < 2; j++){
            trigger_region_tauisgenmu.push_back(0);
            trigger_region_tauisgenmu[j] = (isSingleTrigger && pt_1>single_mupt_thres && mytau_isgenmu[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres && mytau_isgenmu[j].Pt()>cross_taupt_thres);
        }
        //electron->tauh fake ES
        std::vector<bool> trigger_region_tauisgenele;
        for (int j = 0; j < 8; j++){
            trigger_region_tauisgenele.push_back(0);
            trigger_region_tauisgenele[j] = (isSingleTrigger && pt_1>single_mupt_thres && mytau_isgenele[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres && mytau_isgenele[j].Pt()>cross_taupt_thres);
        }
        //shifted muon ES
        std::vector<bool> trigger_region_shiftedmu;
        for (int j = 0; j < 6; j++){
            trigger_region_shiftedmu.push_back(0);
            trigger_region_shiftedmu[j] = (isSingleTrigger && myshiftedmu[j].Pt()>single_mupt_thres && pt_2>single_taupt_thres) or (isCrossTrigger && myshiftedmu[j].Pt()<single_mupt_thres && myshiftedmu[j].Pt()>cross_mupt_thres && pt_2>cross_taupt_thres);
        }
        
        //############################trigger sf shifting################################
        std::vector<float> trigger_shiftedsf;
        for (int j = 0; j < 4; j++){
            trigger_shiftedsf.push_back(1.0);//=1.0 do not shift by default
        }//[0]:single_up, [1]:single_down, [2]:cross_up, [3]:cross_down
        if (sample!="data_obs"){
            if (isSingleTrigger && pt_1>single_mupt_thres){//single lepton, same updown 2% for both MC and emb
                trigger_shiftedsf[0] = 1.02;
                trigger_shiftedsf[1] = 0.98;
            }
            if (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres){
                if (sample!="embedded"){//MC
                    trigger_shiftedsf[2] = t_trg_pog_deeptau_medium_mutau_ratio_up/t_trg_pog_deeptau_medium_mutau_ratio;
                    trigger_shiftedsf[3] = t_trg_pog_deeptau_medium_mutau_ratio_down/t_trg_pog_deeptau_medium_mutau_ratio;
                }
                else {//embedded
                    trigger_shiftedsf[2] = t_trg_mediumDeepTau_mutau_embed_ratio_up/t_trg_mediumDeepTau_mutau_embed_ratio;
                    trigger_shiftedsf[3] = t_trg_mediumDeepTau_mutau_embed_ratio_down/t_trg_mediumDeepTau_mutau_embed_ratio;
                    if (year=="2016"){
                        trigger_shiftedsf[2] = t_trg_pog_deeptau_medium_mutau_ratio_up/t_trg_pog_deeptau_medium_mutau_ratio;
                        trigger_shiftedsf[3] = t_trg_pog_deeptau_medium_mutau_ratio_down/t_trg_pog_deeptau_medium_mutau_ratio;
                    }
                }
            }
        }
        //##############################histograms filling###################################
        bool isnonSignal = (sample!="gghbbtt12" && sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt15" && sample!="vbfbbtt20" && sample!="vbfbbtt25" && sample!="vbfbbtt30" && sample!="vbfbbtt35" && sample!="vbfbbtt40" && sample!="vbfbbtt45" && sample!="vbfbbtt50" && sample!="vbfbbtt55" && sample!="vbfbbtt60");
        bool isnonHiggsMC = (sample!="data_obs" && sample!="embedded" && isnonSignal && name!="HTT" && name!="ttHnonbb");
        //do not fill for MC tautau events (duplicating emb) as normal
        if (!isnonHiggsMC or (isnonHiggsMC && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6))){
            //tau isolated region (to be failed in fake)
            if (byMediumDeepVSjet_2){
                if (nbtag20==1){//1 bjet category
                    if (trigger_region_nominal){//nominal trigger region
                        for (int k = 0; k < 15; k++){//[0] all nominal, [1-14] tauID shifted
                            h_iso[0][k]->Fill(pt_1,weight_corr*trgsf*sf_tauid[k]);
                            h_iso[1][k]->Fill(pt_2,weight_corr*trgsf*sf_tauid[k]);
                            h_iso[2][k]->Fill(m_sv,weight_corr*trgsf*sf_tauid[k]);
                            h_iso[3][k]->Fill(m_btt,weight_corr*trgsf*sf_tauid[k]);
                        }
                        for (int k = 0; k < 22; k++){//[23-44] jet uncertainties
                            h_iso[0][k+23]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]);
                            h_iso[1][k+23]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]);
                            h_iso[2][k+23]->Fill(mytt_jet[k].M(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[3][k+23]->Fill(m_btt_jet[k],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++){
                            h_iso[0][k+55]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                            h_iso[1][k+55]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                            h_iso[2][k+55]->Fill(m_sv,weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                            h_iso[3][k+55]->Fill(m_btt,weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                        }
                        //tau tracking uncertainties, emb only
                        if (sample=="embedded"){
                            for (int k = 0; k < 6; k++){
                                h_iso[0][k+65]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                                h_iso[1][k+65]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                                h_iso[2][k+65]->Fill(m_sv,weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                                h_iso[3][k+65]->Fill(m_btt,weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                            }
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                            for (int k = 0; k < 2; k++){
                                h_iso[0][k+71]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                                h_iso[1][k+71]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                                h_iso[2][k+71]->Fill(m_sv,weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                                h_iso[3][k+71]->Fill(m_btt,weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="TT"){
                            for (int k = 0; k < 2; k++){
                                h_iso[0][k+73]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                                h_iso[1][k+73]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                                h_iso[2][k+73]->Fill(m_sv,weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                                h_iso[3][k+73]->Fill(m_btt,weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                            }
                        }
                        //recoil uncertainties
                        if (sample!="data_obs" && sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                            for (int k = 0; k < 12; k++){
                                h_iso[0][k+75]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]);
                                h_iso[1][k+75]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]);
                                h_iso[2][k+75]->Fill(mytt_recoil[k].M(),weight_corr*trgsf*sf_tauid[0]);
                                h_iso[3][k+75]->Fill(m_btt_recoil[k],weight_corr*trgsf*sf_tauid[0]);
                            }
                        }
                        //met unclustered ES
                        if (name=="TT" or name=="VV" or name=="ST"){
                            for (int k = 0; k < 2; k++){
                                h_iso[0][k+87]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]);
                                h_iso[1][k+87]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]);
                                h_iso[2][k+87]->Fill(mytt_UES[k].M(),weight_corr*trgsf*sf_tauid[0]);
                                h_iso[3][k+87]->Fill(m_btt_UES[k],weight_corr*trgsf*sf_tauid[0]);
                            }
                        }
                        for (int k = 0; k < 2; k++){//[90-91] JER uncertainties
                            h_iso[0][k+90]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]);
                            h_iso[1][k+90]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]);
                            h_iso[2][k+90]->Fill(mytt_jer[k].M(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[3][k+90]->Fill(m_btt_jer[k],weight_corr*trgsf*sf_tauid[0]);
                        }
                    }
                    //loop over trigger regions with shifted tau
                    for (int k = 0; k < 8; k++){//h_OS[15-22] tau energy scale
                        if (trigger_region_shiftedtau[k]){
                            h_iso[0][k+15]->Fill(pt_1,weight_corr*trgsf*sf_tauid[k+15]);
                            h_iso[1][k+15]->Fill(myshiftedtau[k].Pt(),weight_corr*trgsf*sf_tauid[k+15]);
                            h_iso[2][k+15]->Fill(mytt_shiftedtau[k].M(),weight_corr*trgsf*sf_tauid[k+15]);
                            h_iso[3][k+15]->Fill(m_btt_shiftedtau[k],weight_corr*trgsf*sf_tauid[k+15]);//nominal tauID sf evaluated at shifted tau pt
                        }
                    }
                    //loop over trigger regions with muon->tau fake shifted
                    for (int k = 0; k < 2; k++){
                        if (trigger_region_tauisgenmu[k]){
                            h_iso[0][k+45]->Fill(pt_1,weight_corr*trgsf);
                            h_iso[1][k+45]->Fill(mytau_isgenmu[k].Pt(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[2][k+45]->Fill(mytt_isgenmu[k].M(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[3][k+45]->Fill(m_btt_isgenmu[k],weight_corr*trgsf*sf_tauid[0]);
                        }
                    }
                    //loop over trigger regions with electron->tau fake shifted
                    for (int k = 0; k < 8; k++){
                        if (trigger_region_tauisgenele[k]){
                            h_iso[0][k+47]->Fill(pt_1,weight_corr*trgsf);
                            h_iso[1][k+47]->Fill(mytau_isgenele[k].Pt(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[2][k+47]->Fill(mytt_isgenele[k].M(),weight_corr*trgsf*sf_tauid[0]);
                            h_iso[3][k+47]->Fill(m_btt_isgenele[k],weight_corr*trgsf*sf_tauid[0]);
                        }
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (trigger_region_shiftedmu[k]){
                            h_iso[0][k+59]->Fill(myshiftedmu[k].Pt(),weight_corr*trgsf_shiftedmu[k]*sf_tauid[0]);
                            h_iso[1][k+59]->Fill(pt_2,weight_corr*trgsf_shiftedmu[k]*sf_tauid[0]);
                            h_iso[2][k+59]->Fill(mytt_shiftedmu[k].M(),weight_corr*trgsf_shiftedmu[k]*sf_tauid[0]);
                            h_iso[3][k+59]->Fill(m_btt_shiftedmu[k],weight_corr*trgsf_shiftedmu[k]*sf_tauid[0]);
                        }
                    }
                }
            }
            
            //anti-isolated tau region for fake background
            if (isnonSignal && byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2){//fake taus, do not need tau energy scale shifting, or tauid sf
                //fake rates
                float fr = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dm0M,g_taufr_dm1M,g_taufr_dm10M,g_taufr_dm11M,0);
                //calculated with bjet
                float fr_bjet = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,0);
                
                float weight_fake = 1.0;
                if (nbtag20==0) weight_fake = fr/(1-fr);
                else weight_fake = fr_bjet/(1-fr_bjet);
                
                float xtrgfakefactor = 1.0;//tighter cuts applied at cross trigger level -> less yields -> scale up to compensate
                float xtrgfakefactor_updown[2] = {1.0,1.0};
                if (isCrossTrigger && pt_1<single_mupt_thres && pt_1>cross_mupt_thres){
                    xtrgfakefactor = 1.5;//nominal
                    xtrgfakefactor_updown[0] = 1.6;//+/-20%
                    xtrgfakefactor_updown[1] = 1.4;
                }
                
                std::vector<float> xtrgfakefactor_shiftedmu;
                //for shifted mu (re-defined single/cross)
                for (int k = 0; k < 6; k++){
                    xtrgfakefactor_shiftedmu.push_back(1.0);
                    if (isCrossTrigger && myshiftedmu[k].Pt()<single_mupt_thres && myshiftedmu[k].Pt()>cross_mupt_thres) xtrgfakefactor_shiftedmu[k] = 1.5;
                }
                
                //############################fake rate uncertainties for alldm by pt bins###########################
                std::vector<float> fr_bjet_shifted;//only for nbjet>0; when nbjet==0 it is split by DM also..
                std::vector<float> weight_fake_shifted;
                for (int k = 0; k < 14; k++){
                    fr_bjet_shifted.push_back(0);
                    fr_bjet_shifted[k] = GetTauFR(mytau.Pt(),0,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,k+1);//see GetTauFR.h
                    weight_fake_shifted.push_back(0);
                    weight_fake_shifted[k] = fr_bjet_shifted[k]/(1-fr_bjet_shifted[k]);
                }//ordered by: pt0to25up/down, pt25to30up/down,...
                
                if (nbtag20==1){
                    if (trigger_region_nominal){
                        //nominal
                        h_anti[0][0]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        h_anti[1][0]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        h_anti[2][0]->Fill(m_sv,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        h_anti[3][0]->Fill(m_btt,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        //jet uncertainties
                        for (int k = 0; k < 22; k++){
                            h_anti[0][k+1]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[1][k+1]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[2][k+1]->Fill(mytt_jet[k].M(),weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[3][k+1]->Fill(m_btt_jet[k],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++){
                            h_anti[0][k+23]->Fill(pt_1,weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                            h_anti[1][k+23]->Fill(pt_2,weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                            h_anti[2][k+23]->Fill(m_sv,weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                            h_anti[3][k+23]->Fill(m_btt,weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                            for (int k = 0; k < 2; k++){
                                h_anti[0][k+33]->Fill(pt_1,weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                                h_anti[1][k+33]->Fill(pt_2,weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                                h_anti[2][k+33]->Fill(m_sv,weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                                h_anti[3][k+33]->Fill(m_btt,weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){
                            for (int k = 0; k < 2; k++){
                                h_anti[0][k+35]->Fill(pt_1,weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                                h_anti[1][k+35]->Fill(pt_2,weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                                h_anti[2][k+35]->Fill(m_sv,weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                                h_anti[3][k+35]->Fill(m_btt,weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                            }
                        }
                        //recoil uncertainties
                        if (sample!="data_obs" && sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                            for (int k = 0; k < 12; k++){
                                h_anti[0][k+37]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[1][k+37]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[2][k+37]->Fill(mytt_recoil[k].M(),weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[3][k+37]->Fill(m_btt_recoil[k],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            }
                        }
                        //met unclustered ES
                        if (name=="TT" or name=="VV" or name=="ST"){
                            for (int k = 0; k < 2; k++){
                                h_anti[0][k+49]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[1][k+49]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[2][k+49]->Fill(mytt_UES[k].M(),weight_corr*weight_fake*trgsf*xtrgfakefactor);
                                h_anti[3][k+49]->Fill(m_btt_UES[k],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            }
                        }
                        //JER uncertainties
                        for (int k = 0; k < 2; k++){
                            h_anti[0][k+51]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[1][k+51]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[2][k+51]->Fill(mytt_jer[k].M(),weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            h_anti[3][k+51]->Fill(m_btt_jer[k],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //uncertainties in xtrgup factor
                        for (int k = 0; k < 2; k++){
                            h_anti[0][k+53]->Fill(pt_1,weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                            h_anti[1][k+53]->Fill(pt_2,weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                            h_anti[2][k+53]->Fill(m_sv,weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                            h_anti[3][k+53]->Fill(m_btt,weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                        }
                        //fake rate uncertainties for alldm by pt bins
                        for (int k = 0; k < 14; k++){
                            h_anti[0][k+55]->Fill(pt_1,weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                            h_anti[1][k+55]->Fill(pt_2,weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                            h_anti[2][k+55]->Fill(m_sv,weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                            h_anti[3][k+55]->Fill(m_btt,weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                        }
                    }//end of trigger_region_nominal
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (trigger_region_shiftedmu[k]){
                            h_anti[0][k+27]->Fill(myshiftedmu[k].Pt(),weight_corr*weight_fake*trgsf_shiftedmu[k]*xtrgfakefactor_shiftedmu[k]);
                            h_anti[1][k+27]->Fill(pt_2,weight_corr*weight_fake*trgsf_shiftedmu[k]*xtrgfakefactor_shiftedmu[k]);
                            h_anti[2][k+27]->Fill(mytt_shiftedmu[k].M(),weight_corr*weight_fake*trgsf_shiftedmu[k]*xtrgfakefactor_shiftedmu[k]);
                            h_anti[3][k+27]->Fill(m_btt_shiftedmu[k],weight_corr*weight_fake*trgsf_shiftedmu[k]*xtrgfakefactor_shiftedmu[k]);
                        }
                    }
                }//end of nbtag==1
            }//end of anti-isolated region
        }//end of (!isnonHiggsMC or (isnonHiggsMC && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6)))
        
        //nonDY MC contamination to embedded (all nonHiggs MC events with two taus previously rejected)
        if (isnonHiggsMC && name!="Z" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (byMediumDeepVSjet_2){
                if (nbtag20==1){
                    if (trigger_region_nominal){
                        h_iso[0][89]->Fill(pt_1,weight_corr*trgsf*sf_tauid[0]*0.1);//+/-10% on top of emb
                        h_iso[1][89]->Fill(pt_2,weight_corr*trgsf*sf_tauid[0]*0.1);
                        h_iso[2][89]->Fill(m_sv,weight_corr*trgsf*sf_tauid[0]*0.1);
                        h_iso[3][89]->Fill(m_btt,weight_corr*trgsf*sf_tauid[0]*0.1);
                    }
                }
            }
        }
    }//end of event loop
    
    TFile * fout = TFile::Open(output.c_str(), "UPDATE");
    
    TString dir[4] = {"pt_1","pt_2","m_tt","m_btt"};
    TString fake = "_fake";
    TString MC = "MC";
    
    bool isnonSignal = (sample!="gghbbtt12" && sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt15" && sample!="vbfbbtt20" && sample!="vbfbbtt25" && sample!="vbfbbtt30" && sample!="vbfbbtt35" && sample!="vbfbbtt40" && sample!="vbfbbtt45" && sample!="vbfbbtt50" && sample!="vbfbbtt55" && sample!="vbfbbtt60");
    bool isnonHiggsMC = (sample!="data_obs" && sample!="embedded" && isnonSignal && name!="HTT" && name!="ttHnonbb");
    
    std::vector<TDirectory*> td;
    for (int j = 0; j < 4; j++){//loop over histogram variables
        td.push_back(fout->mkdir(dir[j]));
        td[j]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_iso[j][0]->SetName(name.c_str());
            h_iso[j][0]->Write();
            if (isnonSignal){
                h_anti[j][0]->SetName(name.c_str()+fake);
                h_anti[j][0]->Write();
            }
            //shifted
            for (int i = 0; i < 14; ++i){
                h_iso[j][i+1]->SetName(name.c_str()+shape_tauideff[i]);
                h_iso[j][i+1]->Write();
            }
            for (int i = 0; i < 8; ++i){
                h_iso[j][i+15]->SetName(name.c_str()+shape_tauES[i]);
                h_iso[j][i+15]->Write();
            }
            if (sample!="embedded"){
                for (int i = 0; i < 22; ++i){
                    h_iso[j][i+23]->SetName(name.c_str()+shape_jet[i]);
                    h_iso[j][i+23]->Write();
                    if (isnonSignal){
                        h_anti[j][i+1]->SetName(name.c_str()+fake+shape_jet[i]);
                        h_anti[j][i+1]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    h_iso[j][i+45]->SetName(name.c_str()+shape_mufaketauES[i]);
                    h_iso[j][i+45]->Write();
                }
                for (int i = 0; i < 8; ++i){
                    h_iso[j][i+47]->SetName(name.c_str()+shape_elefaketauES[i]);
                    h_iso[j][i+47]->Write();
                }
            }
            for (int i = 0; i < 4; ++i){
                h_iso[j][i+55]->SetName(name.c_str()+shape_trgeff[i]);
                h_iso[j][i+55]->Write();
                if (isnonSignal){
                    h_anti[j][i+23]->SetName(name.c_str()+fake+shape_trgeff[i]);
                    h_anti[j][i+23]->Write();
                }
            }
            for (int i = 0; i < 6; ++i){
                h_iso[j][i+59]->SetName(name.c_str()+shape_muonES[i]);
                h_iso[j][i+59]->Write();
                if (isnonSignal){
                    h_anti[j][i+27]->SetName(name.c_str()+fake+shape_muonES[i]);
                    h_anti[j][i+27]->Write();
                }
            }
            //emb only
            if (sample=="embedded"){
                for (int i = 0; i < 6; ++i){
                    h_iso[j][i+65]->SetName(name.c_str()+embshape_tautracking[i]);
                    h_iso[j][i+65]->Write();
                }
            }
            //DY MC only
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                for (int i = 0; i < 2; ++i){
                    h_iso[j][i+71]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_iso[j][i+71]->Write();
                    h_anti[j][i+33]->SetName(name.c_str()+fake+shape_DY_zpt[i]);
                    h_anti[j][i+33]->Write();
                }
            }
            //ttbar only
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){
                for (int i = 0; i < 2; ++i){
                    h_iso[j][i+73]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_iso[j][i+73]->Write();
                    h_anti[j][i+35]->SetName(name.c_str()+fake+shape_ttbar_toppt[i]);
                    h_anti[j][i+35]->Write();
                }
            }
            //recoil: MC except ttbar diboson singletop
            if (sample!="data_obs" && sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                for (int i = 0; i < 12; ++i){
                    h_iso[j][i+75]->SetName(name.c_str()+shape_recoil[i]);
                    h_iso[j][i+75]->Write();
                    if (isnonSignal){
                        h_anti[j][i+37]->SetName(name.c_str()+fake+shape_recoil[i]);
                        h_anti[j][i+37]->Write();
                    }
                }
            }
            //met unclustered ES: only on ttbar diboson singletop
            if (name=="TT" or name=="VV" or name=="ST"){
                for (int i = 0; i < 2; ++i){
                    h_iso[j][i+87]->SetName(name.c_str()+shape_unclusteredES[i]);
                    h_iso[j][i+87]->Write();
                    h_anti[j][i+49]->SetName(name.c_str()+fake+shape_unclusteredES[i]);
                    h_anti[j][i+49]->Write();
                }
            }
            //nonDY
            if (isnonHiggsMC && name!="Z"){
                TString nonDYMC = "nonDYMC";
                h_iso[j][89]->SetName(nonDYMC+shape_nonDY[0]);
                h_iso[j][89]->Write();
            }
            //JER
            for (int i = 0; i < 2; ++i){
                h_iso[j][i+90]->SetName(name.c_str()+shape_jer[i]);
                h_iso[j][i+90]->Write();
                if (isnonSignal){
                    h_anti[j][i+51]->SetName(name.c_str()+fake+shape_jer[i]);
                    h_anti[j][i+51]->Write();
                }
            }
            //fake cross trg scale up uncertainties
            if (isnonSignal){
                for (int i = 0; i < 2; ++i){
                    h_anti[j][i+53]->SetName(MC+fake+shape_fake_crosstrg[i]);
                    h_anti[j][i+53]->Write();
                }
            }
            //fake rate uncertainties by pt bins
            if (isnonSignal){
                for (int i = 0; i < 14; ++i){
                    h_anti[j][i+55]->SetName(MC+fake+shape_fakerate[i]);
                    h_anti[j][i+55]->Write();
                }
            }
        }//end of (sample!="data_obs)
        if (sample=="data_obs"){
            h_iso[j][0]->SetName(name.c_str());
            h_iso[j][0]->Write();
            h_anti[j][0]->SetName(name.c_str()+fake);
            h_anti[j][0]->Write();
            //fake cross trg scale up uncertainties
            for (int i = 0; i < 2; ++i){
                h_anti[j][i+53]->SetName(name.c_str()+fake+shape_fake_crosstrg[i]);
                h_anti[j][i+53]->Write();
            }
            //fake rate uncertainties by pt bins
            for (int i = 0; i < 14; ++i){
                h_anti[j][i+55]->SetName(name.c_str()+fake+shape_fakerate[i]);
                h_anti[j][i+55]->Write();
            }
        }
    }
    
    fout->Close();
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}




