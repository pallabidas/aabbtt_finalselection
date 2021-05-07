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

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    std::string year = *(argv + 5);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("emu_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    std::string sample_name = sample.c_str();
    std::string dnnfile = "/hdfs/store/user/htsoi/dnn/em18/" + sample_name + ".root";
    if (year=="2017") dnnfile = "/hdfs/store/user/htsoi/dnn/em17/" + sample_name + ".root";
    if (year=="2016") dnnfile = "/hdfs/store/user/htsoi/dnn/em16/" + sample_name + ".root";
    TFile * dnn = new TFile(dnnfile.c_str());
    TTree * tree_dnn = (TTree*) dnn->Get("emu_tree_dnn");
    
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
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
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
    tree->SetBranchAddress("passMu23E12", &passMu23E12);
    tree->SetBranchAddress("passMu8E23", &passMu8E23);
    tree->SetBranchAddress("matchMu23E12_1", &matchMu23E12_1);
    tree->SetBranchAddress("matchMu8E23_1", &matchMu8E23_1);
    tree->SetBranchAddress("filterMu23E12_1", &filterMu23E12_1);
    tree->SetBranchAddress("filterMu8E23_1", &filterMu8E23_1);
    tree->SetBranchAddress("matchMu23E12_2", &matchMu23E12_2);
    tree->SetBranchAddress("matchMu8E23_2", &matchMu8E23_2);
    tree->SetBranchAddress("filterMu23E12_2", &filterMu23E12_2);
    tree->SetBranchAddress("filterMu8E23_2", &filterMu8E23_2);
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
    tree->SetBranchAddress("m_trg_8_ic_data", &m_trg_8_ic_data);
    tree->SetBranchAddress("e_trg_23_ic_data", &e_trg_23_ic_data);
    tree->SetBranchAddress("m_trg_23_ic_data", &m_trg_23_ic_data);
    tree->SetBranchAddress("e_trg_12_ic_data", &e_trg_12_ic_data);
    tree->SetBranchAddress("m_trg_8_ic_mc", &m_trg_8_ic_mc);
    tree->SetBranchAddress("e_trg_23_ic_mc", &e_trg_23_ic_mc);
    tree->SetBranchAddress("m_trg_23_ic_mc", &m_trg_23_ic_mc);
    tree->SetBranchAddress("e_trg_12_ic_mc", &e_trg_12_ic_mc);
    tree->SetBranchAddress("m_trk_ratio", &m_trk_ratio);
    tree->SetBranchAddress("m_idiso_ic_ratio", &m_idiso_ic_ratio);
    tree->SetBranchAddress("e_trk_ratio", &e_trk_ratio);
    tree->SetBranchAddress("e_idiso_ic_ratio", &e_idiso_ic_ratio);
    tree->SetBranchAddress("m_trg_8_ic_embed", &m_trg_8_ic_embed);
    tree->SetBranchAddress("e_trg_23_ic_embed", &e_trg_23_ic_embed);
    tree->SetBranchAddress("m_trg_23_ic_embed", &m_trg_23_ic_embed);
    tree->SetBranchAddress("e_trg_12_ic_embed", &e_trg_12_ic_embed);
    tree->SetBranchAddress("m_idiso_ic_embed_ratio", &m_idiso_ic_embed_ratio);
    tree->SetBranchAddress("e_trk_embed_ratio", &e_trk_embed_ratio);
    tree->SetBranchAddress("e_idiso_ic_embed_ratio", &e_idiso_ic_embed_ratio);
    tree->SetBranchAddress("zptmass_weight_nom", &zptmass_weight_nom);
    tree->SetBranchAddress("m_sel_trg_ic_ratio", &m_sel_trg_ic_ratio);
    tree->SetBranchAddress("m_sel_id_ic_ratio_1", &m_sel_id_ic_ratio_1);
    tree->SetBranchAddress("m_sel_id_ic_ratio_2", &m_sel_id_ic_ratio_2);
    tree->SetBranchAddress("prefiring_weight", &prefiring_weight);
    tree->SetBranchAddress("m_sv", &m_sv);
    tree->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    tree->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    tree->SetBranchAddress("m_sv_JERUp", &m_sv_JERUp);
    tree->SetBranchAddress("m_sv_JERDown", &m_sv_JERDown);
    tree->SetBranchAddress("m_sv_elescaleESUp", &m_sv_elescaleESUp);
    tree->SetBranchAddress("m_sv_elescaleESDown", &m_sv_elescaleESDown);
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
    tree_dnn->SetBranchAddress("dnn_1b_UESUp", &dnn_1b_UESUp);
    tree_dnn->SetBranchAddress("dnn_1b_UESDown", &dnn_1b_UESDown);
    tree_dnn->SetBranchAddress("dnn_1b_JERUp", &dnn_1b_JERUp);
    tree_dnn->SetBranchAddress("dnn_1b_JERDown", &dnn_1b_JERDown);
    tree_dnn->SetBranchAddress("dnn_1b_elescaleESUp", &dnn_1b_elescaleESUp);
    tree_dnn->SetBranchAddress("dnn_1b_elescaleESDown", &dnn_1b_elescaleESDown);
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
    tree_dnn->SetBranchAddress("dnn_2b_UESUp", &dnn_2b_UESUp);
    tree_dnn->SetBranchAddress("dnn_2b_UESDown", &dnn_2b_UESDown);
    tree_dnn->SetBranchAddress("dnn_2b_JERUp", &dnn_2b_JERUp);
    tree_dnn->SetBranchAddress("dnn_2b_JERDown", &dnn_2b_JERDown);
    tree_dnn->SetBranchAddress("dnn_2b_elescaleESUp", &dnn_2b_elescaleESUp);
    tree_dnn->SetBranchAddress("dnn_2b_elescaleESDown", &dnn_2b_elescaleESDown);
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
    
    TString shape_eleES[4] = {"_CMS_eleES_barrel_"+shape_year+"Up","_CMS_eleES_barrel_"+shape_year+"Down","_CMS_eleES_endcap_"+shape_year+"Up","_CMS_eleES_endcap_"+shape_year+"Down"};
    TString shape_muonES[6] = {"_CMS_muonES_eta0to1p4_"+shape_year+"Up","_CMS_muonES_eta0to1p4_"+shape_year+"Down","_CMS_muonES_eta1p4to2p1_"+shape_year+"Up","_CMS_muonES_eta1p4to2p1_"+shape_year+"Down","_CMS_muonES_eta2p1to2p4_"+shape_year+"Up","_CMS_muonES_eta2p1to2p4_"+shape_year+"Down"};
    TString shape_jet[22] = {"_CMS_JetAbsolute_"+shape_year+"Up","_CMS_JetAbsolute_"+shape_year+"Down","_CMS_JetAbsoluteyear_"+shape_year+"Up","_CMS_JetAbsoluteyear_"+shape_year+"Down","_CMS_JetBBEC1_"+shape_year+"Up","_CMS_JetBBEC1_"+shape_year+"Down","_CMS_JetBBEC1year_"+shape_year+"Up","_CMS_JetBBEC1year_"+shape_year+"Down","_CMS_JetEC2_"+shape_year+"Up","_CMS_JetEC2_"+shape_year+"Down","_CMS_JetEC2year_"+shape_year+"Up","_CMS_JetEC2year_"+shape_year+"Down","_CMS_JetFlavorQCD_"+shape_year+"Up","_CMS_JetFlavorQCD_"+shape_year+"Down","_CMS_JetHF_"+shape_year+"Up","_CMS_JetHF_"+shape_year+"Down","_CMS_JetHFyear_"+shape_year+"Up","_CMS_JetHFyear_"+shape_year+"Down","_CMS_JetRelativeBal_"+shape_year+"Up","_CMS_JetRelativeBal_"+shape_year+"Down","_CMS_JetRelativeSample_"+shape_year+"Up","_CMS_JetRelativeSample_"+shape_year+"Down"};
    TString shape_trgeff[6] = {"_CMS_trgeff_Mu8E23_"+shape_year+"Up","_CMS_trgeff_Mu8E23_"+shape_year+"Down","_CMS_trgeff_Mu23E12_"+shape_year+"Up","_CMS_trgeff_Mu23E12_"+shape_year+"Down","_CMS_trgeff_both_"+shape_year+"Up","_CMS_trgeff_both_"+shape_year+"Down"};
    //for DY MC only
    TString shape_DY_zpt[2] = {"_CMS_Zpt_reweight_"+shape_year+"Up","_CMS_Zpt_reweight_"+shape_year+"Down"};
    //for ttbar only
    TString shape_ttbar_toppt[2] = {"_CMS_toppt_reweight_"+shape_year+"Up","_CMS_toppt_reweight_"+shape_year+"Down"};
    //for all MC except diboson, ttbar, single top
    TString shape_recoil[12] = {"_CMS_0jet_resolution_"+shape_year+"Up","_CMS_0jet_resolution_"+shape_year+"Down","_CMS_0jet_response_"+shape_year+"Up","_CMS_0jet_response_"+shape_year+"Down","_CMS_1jet_resolution_"+shape_year+"Up","_CMS_1jet_resolution_"+shape_year+"Down","_CMS_1jet_response_"+shape_year+"Up","_CMS_1jet_response_"+shape_year+"Down","_CMS_gt1jet_resolution_"+shape_year+"Up","_CMS_gt1jet_resolution_"+shape_year+"Down","_CMS_gt1jet_response_"+shape_year+"Up","_CMS_gt1jet_response_"+shape_year+"Down"};
    //only diboson, ttbar, single top
    TString shape_unclusteredES[2] = {"_CMS_unclusteredES_"+shape_year+"Up","_CMS_unclusteredES_"+shape_year+"Down"};
    //jet resolution
    TString shape_jer[2] = {"_CMS_res_j_"+shape_year+"Up","_CMS_res_j_"+shape_year+"Down"};
    //SS 2d correction/closure
    TString shape_ss2d[6] = {"_CMS_SScorrection_"+shape_year+"Up","_CMS_SScorrection_"+shape_year+"Down","_CMS_SSclosure_"+shape_year+"Up","_CMS_SSclosure_"+shape_year+"Down","_CMS_SSboth2D_"+shape_year+"Up","_CMS_SSboth2D_"+shape_year+"Down"};
    
    //for emb only
    TString embshape_eleES[4] = {"_CMS_emb_eleES_barrel_"+shape_year+"Up","_CMS_emb_eleES_barrel_"+shape_year+"Down","_CMS_emb_eleES_endcap_"+shape_year+"Up","_CMS_emb_eleES_endcap_"+shape_year+"Down"};
    TString embshape_muonES[6] = {"_CMS_emb_muonES_eta0to1p4_"+shape_year+"Up","_CMS_emb_muonES_eta0to1p4_"+shape_year+"Down","_CMS_emb_muonES_eta1p4to2p1_"+shape_year+"Up","_CMS_emb_muonES_eta1p4to2p1_"+shape_year+"Down","_CMS_emb_muonES_eta2p1to2p4_"+shape_year+"Up","_CMS_emb_muonES_eta2p1to2p4_"+shape_year+"Down"};
    TString embshape_trgeff[6] = {"_CMS_emb_trgeff_Mu8E23_"+shape_year+"Up","_CMS_emb_trgeff_Mu8E23_"+shape_year+"Down","_CMS_emb_trgeff_Mu23E12_"+shape_year+"Up","_CMS_emb_trgeff_Mu23E12_"+shape_year+"Down","_CMS_emb_trgeff_both_"+shape_year+"Up","_CMS_emb_trgeff_both_"+shape_year+"Down"};
    if (sample=="embedded"){
        for (int i = 0; i < 4; i++) shape_eleES[i] = embshape_eleES[i];
        for (int i = 0; i < 6; i++) shape_muonES[i] = embshape_muonES[i];
        for (int i = 0; i < 6; i++) shape_trgeff[i] = embshape_trgeff[i];
    }
    //comtamination to emb: all non-DY MC with gen tautau
    TString shape_nonDY[1] = {"_nonDY"};
    
    std::vector<std::vector<TH1F*>> h_OS;
    std::vector<std::vector<TH1F*>> h_SS;
    std::vector<std::vector<TH1F*>> h_SSloose;
    for (int i = 0; i < 4; i++){
        h_OS.push_back(std::vector<TH1F*>());
        h_SS.push_back(std::vector<TH1F*>());
        h_SSloose.push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 60; i++){//i=0 for nominal, 1-4 eleES, 5-10 muonES, 11-32 jet, 33-38 trgeff, 39-40 (only DY MC) zpt, 41-42 (only ttbar) toppt, 43-54 recoil, 55-56 met unclustered ES, 57-58 jer, 59 nonDY
        h_OS[0].push_back(new TH1F("","",70,10,150));//pt_1
        h_OS[1].push_back(new TH1F("","",70,10,150));//pt_2
        h_OS[2].push_back(new TH1F("","",40,0,400));//m_tt
        h_OS[3].push_back(new TH1F("","",50,60,560));//m_btt
    }
    for (int i = 0; i < 65; i++){//same-sign region //i=0 for nominal, 1-4 eleES, 5-10 muonES, 11-32 jet, 33-38 trgeff, 39-40 (only DY MC) zpt, 41-42 (only ttbar) toppt, 43-54 recoil, 55-56 met unclustered ES, 57-58 jer, 59-64 SS correction/closure
        h_SS[0].push_back(new TH1F("","",70,10,150));//pt_1
        h_SS[1].push_back(new TH1F("","",70,10,150));//pt_2
        h_SS[2].push_back(new TH1F("","",40,0,400));//m_tt
        h_SS[3].push_back(new TH1F("","",50,60,560));//m_btt
        h_SSloose[0].push_back(new TH1F("","",70,10,150));//pt_1
        h_SSloose[1].push_back(new TH1F("","",70,10,150));//pt_2
        h_SSloose[2].push_back(new TH1F("","",40,0,400));//m_tt
        h_SSloose[3].push_back(new TH1F("","",50,60,560));//m_btt
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
    
    //OS-to-SS qcd correction files
    TFile *fclosure = new TFile("closure_em_2018.root","r");
    if (year=="2017") fclosure = new TFile("closure_em_2017.root","r");
    if (year=="2016") fclosure = new TFile("closure_em_2016.root","r");
    TH2F *correction = (TH2F*) fclosure->Get("correction");
    TH2F *closureOS = (TH2F*) fclosure->Get("closureOS");
    
    TFile *fosss = new TFile("osss_em_2018.root","r");
    if (year=="2017") fosss = new TFile("osss_em_2017.root","r");
    if (year=="2016") fosss = new TFile("osss_em_2016.root","r");
    TF1 *osss_0bjet = (TF1*) fosss->Get("OSSS_qcd_0bjet");
    TF1 *osss_bjet = (TF1*) fosss->Get("OSSS_qcd_bjet");
    
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
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepcsv_1,beta_deepcsv_1,bphi_deepcsv_1,bm_deepcsv_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepcsv_2,beta_deepcsv_2,bphi_deepcsv_2,bm_deepcsv_2);
        
        bool isMu8E23 = false;
        bool isMu23E12 = false;
        if (year=="2018"){
            isMu8E23 = (passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2);
            isMu23E12 = (passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2);
        }
        if (year=="2017"){
            isMu8E23 = (passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2);
            isMu23E12 = (passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2);
        }
        if (year=="2016"){
            isMu8E23 = (passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2);
            isMu23E12 = (passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2);
            if (sample=="data_obs" && run>=278820){
                isMu8E23 = (passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2);
                isMu23E12 = (passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2);
            }
        }
        
        if (!isMu8E23 && !isMu23E12) continue;
        
        //trigger var only, add pt requirements later when doing systematics
        if (!(fabs(eta_1)<2.4 && fabs(eta_2)<2.4)) continue;
        //if (!(iso_1<0.10 && iso_2<0.15)) continue;//normal region
        if (!(iso_1<0.3 && iso_2<0.3)) continue;//loose region
        
        if (!(myele.DeltaR(mymu)>0.3)) continue;
        
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
            
            //reject MC with 2 taus as duplicated in embedded sample except for signal/Higgs
            //if (sample!="data_obs" && sample!="embedded" && sample!="gghbbtt12" && sample!="gghbbtt20" && sample!="gghbbtt30" && sample!="gghbbtt40" && sample!="gghbbtt50" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt20" && sample!="vbfbbtt30" && sample!="vbfbbtt40" && sample!="vbfbbtt50" && sample!="vbfbbtt60" && name!="HTT" && name!="ttHnonbb" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) continue;
            
            //e,mu ID/iso/tracking scale factors
            sf_MC *= e_trk_ratio * e_idiso_ic_ratio * m_trk_ratio * m_idiso_ic_ratio;
            
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
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            //rejecting buggy events
            if (year=="2016" && genweight>1.0) continue;
            
            //e,mu ID/iso/tracking scale factors
            sf_embed *= e_trk_embed_ratio * e_idiso_ic_embed_ratio * m_trk_ratio * m_idiso_ic_embed_ratio;
            
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
        mytt.SetPtEtaPhiM((myele+mymu+mymet).Pt(),(myele+mymu+mymet).Eta(),(myele+mymu+mymet).Phi(),m_sv);
        
        float m_btt = (mytt + myb1).M();
        float m_bbtt = (mytt + myb1 + myb2).M();
        
        float mt_tau1=TMass_F((myele).Pt(),mymet.Pt(),(myele).Px(),mymet.Px(),(myele).Py(),mymet.Py());
        float mt_tau2=TMass_F((mymu).Pt(),mymet.Pt(),(mymu).Px(),mymet.Px(),(mymu).Py(),mymet.Py());
        
        float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
        float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
        float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        //#####################electron ES shifting##############################
        std::vector<TLorentzVector> myshiftedele;
        std::vector<TLorentzVector> mymet_shiftedele;
        std::vector<TLorentzVector> mytt_shiftedele;
        std::vector<float> m_btt_shiftedele;
        for (int j = 0; j < 4; j++){
            myshiftedele.push_back(myele);
            mymet_shiftedele.push_back(mymet);
            mytt_shiftedele.push_back(mytt);
            m_btt_shiftedele.push_back(m_btt);
        }
        float eleESetabins[3] = {0,1.5,2.4};
        float eleES_updowntonom_byeta[4] = {1.005,0.995,1.0125,0.9875};//correction on top of nominal already applied; ordered by: barrel up/down, endcap up/down
        for (int j = 0; j < 2; j++){
            if (fabs(eta_1)>eleESetabins[j] && fabs(eta_1)<eleESetabins[j+1]){//don't need to check gen match, can shift anything that is reco ele
                //myele
                myshiftedele[2*j] *= eleES_updowntonom_byeta[2*j];
                myshiftedele[2*j+1] *= eleES_updowntonom_byeta[2*j+1];
                //mymet
                mymet_shiftedele[2*j] = mymet + myele - myshiftedele[2*j];
                mymet_shiftedele[2*j+1] = mymet + myele - myshiftedele[2*j+1];;
                //mytt
                mytt_shiftedele[2*j].SetPtEtaPhiM((myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Pt(),(myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Eta(),(myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Phi(),m_sv_elescaleESUp);
                mytt_shiftedele[2*j+1].SetPtEtaPhiM((myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Pt(),(myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Eta(),(myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Phi(),m_sv_elescaleESDown);
                //m_btt
                m_btt_shiftedele[2*j] = (mytt_shiftedele[2*j]+myb1).M();
                m_btt_shiftedele[2*j+1] = (mytt_shiftedele[2*j+1]+myb1).M();
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
            if ((gen_match_2==2 or gen_match_2==4) && fabs(eta_2)>muonESetabins[j] && fabs(eta_2)<muonESetabins[j+1]){
                //mymu
                myshiftedmu[2*j] *= muonES_updowntonom_byeta[2*j];
                myshiftedmu[2*j+1] *= muonES_updowntonom_byeta[2*j+1];
                //mymet
                mymet_shiftedmu[2*j] = mymet + mymu - myshiftedmu[2*j];
                mymet_shiftedmu[2*j+1] = mymet + mymu - myshiftedmu[2*j+1];;
                //mytt
                mytt_shiftedmu[2*j].SetPtEtaPhiM((myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Pt(),(myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Eta(),(myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Phi(),m_sv_muonESUp);
                mytt_shiftedmu[2*j+1].SetPtEtaPhiM((myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Pt(),(myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Eta(),(myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Phi(),m_sv_muonESDown);
                //m_btt
                m_btt_shiftedmu[2*j] = (mytt_shiftedmu[2*j]+myb1).M();
                m_btt_shiftedmu[2*j+1] = (mytt_shiftedmu[2*j+1]+myb1).M();
            }
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
            mytt_jet[j].SetPtEtaPhiM((myele+mymu+mymet_jet[j]).Pt(),(myele+mymu+mymet_jet[j]).Eta(),(myele+mymu+mymet_jet[j]).Phi(),m_sv_jetvar[j]);
            m_btt_jet.push_back((mytt_jet[j]+myb1).M());
        }
        
        //###################re-apply trigger scale factor for re-defined single/cross trigger regions due to shifted muon####################
        //define trigger sf with nominal ele ES (the usual weights)
        float trgsf = 1.0;
        float trgsf_Mu8E23only_num = 1.0;
        float trgsf_Mu8E23only_den = 1.0;
        float trgsf_Mu23E12only_num = 1.0;
        float trgsf_Mu23E12only_den = 1.0;
        float trgsf_both_num = 1.0;
        float trgsf_both_den = 1.0;
        if (sample!="data_obs"){
            if (year=="2018"){//already had (!isMu8E23 && !isMu23E12) vetoed
                if (sample!="embedded"){
                    trgsf_Mu8E23only_num = m_trg_8_ic_data * e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = m_trg_8_ic_mc * e_trg_23_ic_mc;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_mc * e_trg_12_ic_mc;
                    trgsf_both_num = m_trg_8_ic_data * e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = m_trg_8_ic_mc * e_trg_23_ic_mc + m_trg_23_ic_mc * e_trg_12_ic_mc - e_trg_23_ic_mc * m_trg_23_ic_mc;
                }
                if (sample=="embedded"){
                    trgsf_Mu8E23only_num = e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = e_trg_23_ic_embed;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_embed * e_trg_12_ic_embed;
                    trgsf_both_num = e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = e_trg_23_ic_embed + m_trg_23_ic_embed * e_trg_12_ic_embed - e_trg_23_ic_embed * m_trg_23_ic_embed;
                }
            }
            if (year=="2017"){
                if (sample!="embedded"){
                    trgsf_Mu8E23only_num = m_trg_8_ic_data * e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = m_trg_8_ic_mc * e_trg_23_ic_mc;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_mc * e_trg_12_ic_mc;
                    trgsf_both_num = m_trg_8_ic_data * e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = m_trg_8_ic_mc * e_trg_23_ic_mc + m_trg_23_ic_mc * e_trg_12_ic_mc - e_trg_23_ic_mc * m_trg_23_ic_mc;
                }
                if (sample=="embedded"){
                    trgsf_Mu8E23only_num = m_trg_8_ic_data * e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = m_trg_8_ic_embed * e_trg_23_ic_embed;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_embed * e_trg_12_ic_embed;
                    trgsf_both_num = m_trg_8_ic_data * e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = m_trg_8_ic_embed * e_trg_23_ic_embed + m_trg_23_ic_embed * e_trg_12_ic_embed - e_trg_23_ic_embed * m_trg_23_ic_embed;
                }
            }
            if (year=="2016"){
                if (sample!="embedded"){
                    trgsf_Mu8E23only_num = m_trg_8_ic_data * e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = m_trg_8_ic_mc * e_trg_23_ic_mc;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_mc * e_trg_12_ic_mc;
                    trgsf_both_num = m_trg_8_ic_data * e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = m_trg_8_ic_mc * e_trg_23_ic_mc + m_trg_23_ic_mc * e_trg_12_ic_mc - e_trg_23_ic_mc * m_trg_23_ic_mc;
                }
                if (sample=="embedded"){
                    trgsf_Mu8E23only_num = m_trg_8_ic_data * e_trg_23_ic_data;
                    trgsf_Mu8E23only_den = m_trg_8_ic_embed * e_trg_23_ic_embed;
                    trgsf_Mu23E12only_num = m_trg_23_ic_data * e_trg_12_ic_data;
                    trgsf_Mu23E12only_den = m_trg_23_ic_embed * e_trg_12_ic_embed;
                    trgsf_both_num = m_trg_8_ic_data * e_trg_23_ic_data + m_trg_23_ic_data * e_trg_12_ic_data - e_trg_23_ic_data * m_trg_23_ic_data;
                    trgsf_both_den = m_trg_8_ic_embed * e_trg_23_ic_embed + m_trg_23_ic_embed * e_trg_12_ic_embed - e_trg_23_ic_embed * m_trg_23_ic_embed;
                }
            }
        }//nominal
        //define trigger pt thresholds for different years
        float Mu8E23_elept_thres = 24;
        float Mu8E23_mupt_thres = 13;
        float Mu23E12_elept_thres = 13;
        float Mu23E12_mupt_thres = 24;
        
        //apply trgger sf with nominal ele/mu ES
        if ((isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && !(isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf = trgsf_Mu8E23only_num / trgsf_Mu8E23only_den;
        if (!(isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf = trgsf_Mu23E12only_num / trgsf_Mu23E12only_den;
        if ((isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf = trgsf_both_num / trgsf_both_den;
        
        //apply trgger sf with shifted electron ES
        std::vector<float> trgsf_shiftedele;
        for (int j = 0; j < 4; j++){
            trgsf_shiftedele.push_back(1.0);
            if ((isMu8E23 && myshiftedele[j].Pt()>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && !(isMu23E12 && myshiftedele[j].Pt()>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf_shiftedele[j] = trgsf_Mu8E23only_num / trgsf_Mu8E23only_den;
            if (!(isMu8E23 && myshiftedele[j].Pt()>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && myshiftedele[j].Pt()>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf_shiftedele[j] = trgsf_Mu23E12only_num / trgsf_Mu23E12only_den;
            if ((isMu8E23 && myshiftedele[j].Pt()>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && myshiftedele[j].Pt()>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)) trgsf_shiftedele[j] = trgsf_both_num / trgsf_both_den;
        }
        
        //apply trgger sf with shifted muon ES
        std::vector<float> trgsf_shiftedmu;
        for (int j = 0; j < 6; j++){
            trgsf_shiftedmu.push_back(1.0);
            if ((isMu8E23 && pt_1>Mu8E23_elept_thres && myshiftedmu[j].Pt()>Mu8E23_mupt_thres) && !(isMu23E12 && pt_1>Mu23E12_elept_thres && myshiftedmu[j].Pt()>Mu23E12_mupt_thres)) trgsf_shiftedmu[j] = trgsf_Mu8E23only_num / trgsf_Mu8E23only_den;
            if (!(isMu8E23 && pt_1>Mu8E23_elept_thres && myshiftedmu[j].Pt()>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && myshiftedmu[j].Pt()>Mu23E12_mupt_thres)) trgsf_shiftedmu[j] = trgsf_Mu23E12only_num / trgsf_Mu23E12only_den;
            if ((isMu8E23 && pt_1>Mu8E23_elept_thres && myshiftedmu[j].Pt()>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && myshiftedmu[j].Pt()>Mu23E12_mupt_thres)) trgsf_shiftedmu[j] = trgsf_both_num / trgsf_both_den;
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
                zptmass_weight_shifting[0] = 1 + (1/zptmass_weight_nom - 1)*0.1;
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
                    mytt_recoil[4*j+k].SetPtEtaPhiM((myele+mymu+mymet_recoil[4*j+k]).Pt(),(myele+mymu+mymet_recoil[4*j+k]).Eta(),(myele+mymu+mymet_recoil[4*j+k]).Phi(),m_sv_recoilvar[k]);
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
            mytt_UES[j].SetPtEtaPhiM((myele+mymu+mymet_UES[j]).Pt(),(myele+mymu+mymet_UES[j]).Eta(),(myele+mymu+mymet_UES[j]).Phi(),m_sv_UESvar[j]);
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
            mytt_jer[j].SetPtEtaPhiM((myele+mymu+mymet_jer[j]).Pt(),(myele+mymu+mymet_jer[j]).Eta(),(myele+mymu+mymet_jer[j]).Phi(),m_sv_jervar[j]);
            m_btt_jer.push_back((mytt_jer[j]+myb1).M());
        }
        
        //##########################trigger regions with nominal/shifted ES###########################
        //nominal
        bool trigger_region_nominal = (isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) or (isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres);
        //shifted electron ES
        std::vector<bool> trigger_region_shiftedele;
        for (int j = 0; j < 4; j++){
            trigger_region_shiftedele.push_back(0);
            trigger_region_shiftedele[j] = (isMu8E23 && myshiftedele[j].Pt()>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) or (isMu23E12 && myshiftedele[j].Pt()>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres);
        }
        //shifted muon ES
        std::vector<bool> trigger_region_shiftedmu;
        for (int j = 0; j < 6; j++){
            trigger_region_shiftedmu.push_back(0);
            trigger_region_shiftedmu[j] = (isMu8E23 && pt_1>Mu8E23_elept_thres && myshiftedmu[j].Pt()>Mu8E23_mupt_thres) or (isMu23E12 && pt_1>Mu23E12_elept_thres && myshiftedmu[j].Pt()>Mu23E12_mupt_thres);
        }
        
        //############################trigger sf shifting################################
        std::vector<float> trigger_shiftedsf;
        for (int j = 0; j < 6; j++){
            trigger_shiftedsf.push_back(1.0);//=1.0 do not shift by default
        }//[0]:isMu8E23only_up, [1]:isMu8E23only_down, [2]:isMu23E12only_up, [3]:isMu23E12only_down, [4]:both_up, [5]:both_down
        if (sample!="data_obs"){//apply +/-2% on top of nominal trigger sf
            if ((isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && !(isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)){
                trigger_shiftedsf[0] = 1.02;
                trigger_shiftedsf[1] = 0.98;
            }
            if (!(isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)){
                trigger_shiftedsf[2] = 1.02;
                trigger_shiftedsf[3] = 0.98;
            }
            if ((isMu8E23 && pt_1>Mu8E23_elept_thres && pt_2>Mu8E23_mupt_thres) && (isMu23E12 && pt_1>Mu23E12_elept_thres && pt_2>Mu23E12_mupt_thres)){
                trigger_shiftedsf[4] = 1.02;
                trigger_shiftedsf[5] = 0.98;
            }
        }
        
        //##############################histograms filling###################################
        bool isnonSignal = (sample!="gghbbtt12" && sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt15" && sample!="vbfbbtt20" && sample!="vbfbbtt25" && sample!="vbfbbtt30" && sample!="vbfbbtt35" && sample!="vbfbbtt40" && sample!="vbfbbtt45" && sample!="vbfbbtt50" && sample!="vbfbbtt55" && sample!="vbfbbtt60");
        bool isnonHiggsMC = (sample!="data_obs" && sample!="embedded" && isnonSignal && name!="HTT" && name!="ttHnonbb");
        //do not fill for MC tautau events (duplicating emb) as normal
        if (!isnonHiggsMC or (isnonHiggsMC && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6))){
            //opposite-sign region, nominal e/mu iso
            if (q_1*q_2<0 && iso_1<0.10 && iso_2<0.15){
                if (nbtag20==1){//1 bjet category
                    if (trigger_region_nominal){//nominal trigger region
                        h_OS[0][0]->Fill(pt_1,weight_corr*trgsf);
                        h_OS[1][0]->Fill(pt_2,weight_corr*trgsf);
                        h_OS[2][0]->Fill(m_sv,weight_corr*trgsf);
                        h_OS[3][0]->Fill(m_btt,weight_corr*trgsf);
                        
                        if (sample!="data_obs"){
                            for (int k = 0; k < 22; k++){
                                h_OS[0][k+11]->Fill(pt_1,weight_corr*trgsf);
                                h_OS[1][k+11]->Fill(pt_2,weight_corr*trgsf);
                                h_OS[2][k+11]->Fill(mytt_jet[k].M(),weight_corr*trgsf);
                                h_OS[3][k+11]->Fill(m_btt_jet[k],weight_corr*trgsf);
                            }
                            //trigger sf shifting
                            for (int k = 0; k < 6; k++){
                                h_OS[0][k+33]->Fill(pt_1,weight_corr*trgsf*trigger_shiftedsf[k]);
                                h_OS[1][k+33]->Fill(pt_2,weight_corr*trgsf*trigger_shiftedsf[k]);
                                h_OS[2][k+33]->Fill(m_sv,weight_corr*trgsf*trigger_shiftedsf[k]);
                                h_OS[3][k+33]->Fill(m_btt,weight_corr*trgsf*trigger_shiftedsf[k]);
                            }
                            //Zpt reweight uncertainties for DY MC only
                            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                                for (int k = 0; k < 2; k++){
                                    h_OS[0][k+39]->Fill(pt_1,weight_corr*trgsf*zptmass_weight_shifting[k]);
                                    h_OS[1][k+39]->Fill(pt_2,weight_corr*trgsf*zptmass_weight_shifting[k]);
                                    h_OS[2][k+39]->Fill(m_sv,weight_corr*trgsf*zptmass_weight_shifting[k]);
                                    h_OS[3][k+39]->Fill(m_btt,weight_corr*trgsf*zptmass_weight_shifting[k]);
                                }
                            }
                            //top pt reweight uncertainties for ttbar only
                            if (name=="TT"){
                                for (int k = 0; k < 2; k++){
                                    h_OS[0][k+41]->Fill(pt_1,weight_corr*trgsf*topfactor_shifting[k]);
                                    h_OS[1][k+41]->Fill(pt_2,weight_corr*trgsf*topfactor_shifting[k]);
                                    h_OS[2][k+41]->Fill(m_sv,weight_corr*trgsf*topfactor_shifting[k]);
                                    h_OS[3][k+41]->Fill(m_btt,weight_corr*trgsf*topfactor_shifting[k]);
                                }
                            }
                            //recoil uncertainties
                            if (sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                                for (int k = 0; k < 12; k++){
                                    h_OS[0][k+43]->Fill(pt_1,weight_corr*trgsf);
                                    h_OS[1][k+43]->Fill(pt_2,weight_corr*trgsf);
                                    h_OS[2][k+43]->Fill(mytt_recoil[k].M(),weight_corr*trgsf);
                                    h_OS[3][k+43]->Fill(m_btt_recoil[k],weight_corr*trgsf);
                                }
                            }
                            //met unclustered ES
                            if (name=="TT" or name=="VV" or name=="ST"){
                                for (int k = 0; k < 2; k++){
                                    h_OS[0][k+55]->Fill(pt_1,weight_corr*trgsf);
                                    h_OS[1][k+55]->Fill(pt_2,weight_corr*trgsf);
                                    h_OS[2][k+55]->Fill(mytt_UES[k].M(),weight_corr*trgsf);
                                    h_OS[3][k+55]->Fill(m_btt_UES[k],weight_corr*trgsf);
                                }
                            }
                            for (int k = 0; k < 2; k++){//JER uncertainties
                                h_OS[0][k+57]->Fill(pt_1,weight_corr*trgsf);
                                h_OS[1][k+57]->Fill(pt_2,weight_corr*trgsf);
                                h_OS[2][k+57]->Fill(mytt_jer[k].M(),weight_corr*trgsf);
                                h_OS[3][k+57]->Fill(m_btt_jer[k],weight_corr*trgsf);
                            }
                        }//end of sample!="data_obs"
                    }//end of nominal trigger region
                    if (sample!="data_obs"){
                        //loop over trigger regions with shifted electron
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]){
                                h_OS[0][k+1]->Fill(myshiftedele[k].Pt(),weight_corr*trgsf_shiftedele[k]);
                                h_OS[1][k+1]->Fill(pt_2,weight_corr*trgsf_shiftedele[k]);
                                h_OS[2][k+1]->Fill(mytt_shiftedele[k].M(),weight_corr*trgsf_shiftedele[k]);
                                h_OS[3][k+1]->Fill(m_btt_shiftedele[k],weight_corr*trgsf_shiftedele[k]);
                            }
                        }
                        //loop over trigger regions with shifted mu
                        for (int k = 0; k < 6; k++){
                            if (trigger_region_shiftedmu[k]){
                                h_OS[0][k+5]->Fill(pt_1,weight_corr*trgsf_shiftedmu[k]);
                                h_OS[1][k+5]->Fill(myshiftedmu[k].Pt(),weight_corr*trgsf_shiftedmu[k]);
                                h_OS[2][k+5]->Fill(mytt_shiftedmu[k].M(),weight_corr*trgsf_shiftedmu[k]);
                                h_OS[3][k+5]->Fill(m_btt_shiftedmu[k],weight_corr*trgsf_shiftedmu[k]);
                            }
                        }
                    }//end of sample!="data_obs"
                }//end of 1 bjet
            }//end of opposite-sign region, nominal e/mu iso
            
            //same-sign region
            if (isnonSignal && q_1*q_2>0){
                //SS weight
                float osss_weight = 1.0;
                float correction_weight = 1.0;
                float closure_weight = 1.0;
                
                float DR = myele.DeltaR(mymu);
                if (DR>6) DR = 5.99;
                
                if (nbtag20==0) osss_weight = osss_0bjet->Eval(DR);
                else osss_weight = osss_bjet->Eval(DR);
                
                //correction/closure with nominal electron/muon ES
                float ept = pt_1;
                float mupt = pt_2;
                if (ept>100) ept = 99;
                if (mupt>100) mupt = 99;
                correction_weight = correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept));
                closure_weight = closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt),closureOS->GetYaxis()->FindBin(ept));
                //total ss weight with nominal electron/muon ES
                float ssweight = osss_weight * correction_weight * closure_weight;
                
                //correction/closure with shifted electron ES
                std::vector<float> ept_shiftedele;
                std::vector<float> correction_weight_shiftedele;
                std::vector<float> closure_weight_shiftedele;
                std::vector<float> ssweight_shiftedele;
                for (int j = 0; j < 4; j++){
                    ept_shiftedele.push_back(myshiftedele[j].Pt());
                    if (ept_shiftedele[j]>100) ept_shiftedele[j] = 99;
                    correction_weight_shiftedele.push_back(correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept_shiftedele[j])));
                    closure_weight_shiftedele.push_back(closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt),closureOS->GetYaxis()->FindBin(ept_shiftedele[j])));
                    ssweight_shiftedele.push_back(osss_weight*correction_weight_shiftedele[j]*closure_weight_shiftedele[j]);
                }
                
                //correction/closure with shifted muon ES
                std::vector<float> mupt_shiftedmu;
                std::vector<float> correction_weight_shiftedmu;
                std::vector<float> closure_weight_shiftedmu;
                std::vector<float> ssweight_shiftedmu;
                for (int j = 0; j < 6; j++){
                    mupt_shiftedmu.push_back(myshiftedmu[j].Pt());
                    if (mupt_shiftedmu[j]>100) mupt_shiftedmu[j] = 99;
                    correction_weight_shiftedmu.push_back(correction->GetBinContent(correction->GetXaxis()->FindBin(mupt_shiftedmu[j]),correction->GetYaxis()->FindBin(ept)));
                    closure_weight_shiftedmu.push_back(closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt_shiftedmu[j]),closureOS->GetYaxis()->FindBin(ept)));
                    ssweight_shiftedmu.push_back(osss_weight*correction_weight_shiftedmu[j]*closure_weight_shiftedmu[j]);
                }
                
                //ss weight with shifted correction/closure
                std::vector<float> ssweight_shifted2d;
                for (int j = 0; j < 6; j++){
                    ssweight_shifted2d.push_back(osss_weight);
                }//ordered by: [0,1]:correction up/down [2,3]closure up/down [4,5]both up/down
                ssweight_shifted2d[0] *= correction_weight * correction_weight * closure_weight;
                ssweight_shifted2d[1] *= closure_weight;
                ssweight_shifted2d[2] *= correction_weight * closure_weight * closure_weight;
                ssweight_shifted2d[3] *= correction_weight;
                ssweight_shifted2d[4] *= correction_weight * correction_weight * closure_weight * closure_weight;
                ssweight_shifted2d[5] *= 1.0;
                
                if (nbtag20==1){
                    if (trigger_region_nominal){
                        //nominal
                        if (iso_1<0.10 && iso_2<0.15){
                            h_SS[0][0]->Fill(pt_1,weight_corr*trgsf*ssweight);
                            h_SS[1][0]->Fill(pt_2,weight_corr*trgsf*ssweight);
                            h_SS[2][0]->Fill(m_sv,weight_corr*trgsf*ssweight);
                            h_SS[3][0]->Fill(m_btt,weight_corr*trgsf*ssweight);
                        }
                        if (iso_1>0.05 or iso_2>0.05){
                            h_SSloose[0][0]->Fill(pt_1,weight_corr*trgsf*ssweight);
                            h_SSloose[1][0]->Fill(pt_2,weight_corr*trgsf*ssweight);
                            h_SSloose[2][0]->Fill(m_sv,weight_corr*trgsf*ssweight);
                            h_SSloose[3][0]->Fill(m_btt,weight_corr*trgsf*ssweight);
                        }
                        if (sample!="data_obs"){
                            //jet uncertainties
                            for (int k = 0; k < 22; k++){
                                if (iso_1<0.10 && iso_2<0.15){
                                    h_SS[0][k+11]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                    h_SS[1][k+11]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                    h_SS[2][k+11]->Fill(mytt_jet[k].M(),weight_corr*trgsf*ssweight);
                                    h_SS[3][k+11]->Fill(m_btt_jet[k],weight_corr*trgsf*ssweight);
                                }
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SSloose[0][k+11]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                    h_SSloose[1][k+11]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                    h_SSloose[2][k+11]->Fill(mytt_jet[k].M(),weight_corr*trgsf*ssweight);
                                    h_SSloose[3][k+11]->Fill(m_btt_jet[k],weight_corr*trgsf*ssweight);
                                }
                            }
                            //trigger sf shifting
                            for (int k = 0; k < 6; k++){
                                if (iso_1<0.10 && iso_2<0.15){
                                    h_SS[0][k+33]->Fill(pt_1,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SS[1][k+33]->Fill(pt_2,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SS[2][k+33]->Fill(m_sv,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SS[3][k+33]->Fill(m_btt,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                }
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SSloose[0][k+33]->Fill(pt_1,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SSloose[1][k+33]->Fill(pt_2,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SSloose[2][k+33]->Fill(m_sv,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                    h_SSloose[3][k+33]->Fill(m_btt,weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                }
                            }
                            //Zpt reweight uncertainties for DY MC only
                            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_1<0.10 && iso_2<0.15){
                                        h_SS[0][k+39]->Fill(pt_1,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SS[1][k+39]->Fill(pt_2,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SS[2][k+39]->Fill(m_sv,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SS[3][k+39]->Fill(m_btt,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                    }
                                    if (iso_1>0.05 or iso_2>0.05){
                                        h_SSloose[0][k+39]->Fill(pt_1,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SSloose[1][k+39]->Fill(pt_2,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SSloose[2][k+39]->Fill(m_sv,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                        h_SSloose[3][k+39]->Fill(m_btt,weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                    }
                                }
                            }
                            //top pt reweight uncertainties for ttbar only
                            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_1<0.10 && iso_2<0.15){
                                        h_SS[0][k+41]->Fill(pt_1,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SS[1][k+41]->Fill(pt_2,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SS[2][k+41]->Fill(m_sv,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SS[3][k+41]->Fill(m_btt,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                    }
                                    if (iso_1>0.05 or iso_2>0.05){
                                        h_SSloose[0][k+41]->Fill(pt_1,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SSloose[1][k+41]->Fill(pt_2,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SSloose[2][k+41]->Fill(m_sv,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                        h_SSloose[3][k+41]->Fill(m_btt,weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                    }
                                }
                            }
                            //recoil uncertainties
                            if (sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                                for (int k = 0; k < 12; k++){
                                    if (iso_1<0.10 && iso_2<0.15){
                                        h_SS[0][k+43]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                        h_SS[1][k+43]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                        h_SS[2][k+43]->Fill(mytt_recoil[k].M(),weight_corr*trgsf*ssweight);
                                        h_SS[3][k+43]->Fill(m_btt_recoil[k],weight_corr*trgsf*ssweight);
                                    }
                                    if (iso_1>0.05 or iso_2>0.05){
                                        h_SSloose[0][k+43]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                        h_SSloose[1][k+43]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                        h_SSloose[2][k+43]->Fill(mytt_recoil[k].M(),weight_corr*trgsf*ssweight);
                                        h_SSloose[3][k+43]->Fill(m_btt_recoil[k],weight_corr*trgsf*ssweight);
                                    }
                                }
                            }
                            //met unclustered ES
                            if (name=="TT" or name=="VV" or name=="ST"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_1<0.10 && iso_2<0.15){
                                        h_SS[0][k+55]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                        h_SS[1][k+55]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                        h_SS[2][k+55]->Fill(mytt_UES[k].M(),weight_corr*trgsf*ssweight);
                                        h_SS[3][k+55]->Fill(m_btt_UES[k],weight_corr*trgsf*ssweight);
                                    }
                                    if (iso_1>0.05 or iso_2>0.05){
                                        h_SSloose[0][k+55]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                        h_SSloose[1][k+55]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                        h_SSloose[2][k+55]->Fill(mytt_UES[k].M(),weight_corr*trgsf*ssweight);
                                        h_SSloose[3][k+55]->Fill(m_btt_UES[k],weight_corr*trgsf*ssweight);
                                    }
                                }
                            }
                            //JER uncertainties
                            for (int k = 0; k < 2; k++){
                                if (iso_1<0.10 && iso_2<0.15){
                                    h_SS[0][k+57]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                    h_SS[1][k+57]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                    h_SS[2][k+57]->Fill(mytt_jer[k].M(),weight_corr*trgsf*ssweight);
                                    h_SS[3][k+57]->Fill(m_btt_jer[k],weight_corr*trgsf*ssweight);
                                }
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SSloose[0][k+57]->Fill(pt_1,weight_corr*trgsf*ssweight);
                                    h_SSloose[1][k+57]->Fill(pt_2,weight_corr*trgsf*ssweight);
                                    h_SSloose[2][k+57]->Fill(mytt_jer[k].M(),weight_corr*trgsf*ssweight);
                                    h_SSloose[3][k+57]->Fill(m_btt_jer[k],weight_corr*trgsf*ssweight);
                                }
                            }
                        }//end of sample!="data_obs"
                        //correction/closure uncertainties
                        for (int k = 0; k < 6; k++){
                            if (iso_1<0.10 && iso_2<0.15){
                                h_SS[0][k+59]->Fill(pt_1,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SS[1][k+59]->Fill(pt_2,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SS[2][k+59]->Fill(m_sv,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SS[3][k+59]->Fill(m_btt,weight_corr*trgsf*ssweight_shifted2d[k]);
                            }
                            if (iso_1>0.05 or iso_2>0.05){
                                h_SSloose[0][k+59]->Fill(pt_1,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SSloose[1][k+59]->Fill(pt_2,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SSloose[2][k+59]->Fill(m_sv,weight_corr*trgsf*ssweight_shifted2d[k]);
                                h_SSloose[3][k+59]->Fill(m_btt,weight_corr*trgsf*ssweight_shifted2d[k]);
                            }
                        }
                    }//end of trigger_region_nominal
                    
                    if (sample!="data_obs"){
                        //loop over trigger regions with shifted electron
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]){
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SS[0][k+1]->Fill(myshiftedele[k].Pt(),weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SS[1][k+1]->Fill(pt_2,weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SS[2][k+1]->Fill(mytt_shiftedele[k].M(),weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SS[3][k+1]->Fill(m_btt_shiftedele[k],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                }
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SSloose[0][k+1]->Fill(myshiftedele[k].Pt(),weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SSloose[1][k+1]->Fill(pt_2,weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SSloose[2][k+1]->Fill(mytt_shiftedele[k].M(),weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                    h_SSloose[3][k+1]->Fill(m_btt_shiftedele[k],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                }
                            }
                        }
                        //loop over trigger regions with shifted muon
                        for (int k = 0; k < 6; k++){
                            if (trigger_region_shiftedmu[k]){
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SS[0][k+5]->Fill(pt_1,weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SS[1][k+5]->Fill(myshiftedmu[k].Pt(),weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SS[2][k+5]->Fill(mytt_shiftedmu[k].M(),weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SS[3][k+5]->Fill(m_btt_shiftedmu[k],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                }
                                if (iso_1>0.05 or iso_2>0.05){
                                    h_SSloose[0][k+5]->Fill(pt_1,weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SSloose[1][k+5]->Fill(myshiftedmu[k].Pt(),weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SSloose[2][k+5]->Fill(mytt_shiftedmu[k].M(),weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                    h_SSloose[3][k+5]->Fill(m_btt_shiftedmu[k],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                }
                            }
                        }
                    }//end of sample!="data_obs"
                }//end of nbtag==1
            }//end of SS region
        }//end of (!isnonHiggsMC or (isnonHiggsMC && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6)))
        
        //nonDY MC contamination to embedded (all nonHiggs MC events with two taus previously rejected)
        if (isnonHiggsMC && name!="Z" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (q_1*q_2<0){
                if (nbtag20==1){
                    if (trigger_region_nominal){
                        h_OS[0][59]->Fill(pt_1,weight_corr*trgsf*0.1);//+/-10% on top of emb
                        h_OS[1][59]->Fill(pt_2,weight_corr*trgsf*0.1);
                        h_OS[2][59]->Fill(m_sv,weight_corr*trgsf*0.1);
                        h_OS[3][59]->Fill(m_btt,weight_corr*trgsf*0.1);
                    }
                }
            }
        }
    }//end of event loop
    
    TFile * fout = TFile::Open(output.c_str(), "UPDATE");
    
    TString dir[4] = {"pt_1","pt_2","m_tt","m_btt"};
    TString SS = "_SS";
    TString SSloose = "_SSloose";
    TString MC = "MC";
    
    bool isnonSignal = (sample!="gghbbtt12" && sample!="gghbbtt15" && sample!="gghbbtt20" && sample!="gghbbtt25" && sample!="gghbbtt30" && sample!="gghbbtt35" && sample!="gghbbtt40" && sample!="gghbbtt45" && sample!="gghbbtt50" && sample!="gghbbtt55" && sample!="gghbbtt60" && sample!="vbfbbtt12" && sample!="vbfbbtt15" && sample!="vbfbbtt20" && sample!="vbfbbtt25" && sample!="vbfbbtt30" && sample!="vbfbbtt35" && sample!="vbfbbtt40" && sample!="vbfbbtt45" && sample!="vbfbbtt50" && sample!="vbfbbtt55" && sample!="vbfbbtt60");
    bool isnonHiggsMC = (sample!="data_obs" && sample!="embedded" && isnonSignal && name!="HTT" && name!="ttHnonbb");
    
    std::vector<TDirectory*> td;
    for (int j = 0; j < 4; j++){//loop over histogram variables
        td.push_back(fout->mkdir(dir[j]));
        td[j]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_OS[j][0]->SetName(name.c_str());
            h_OS[j][0]->Write();
            if (isnonSignal){
                h_SS[j][0]->SetName(name.c_str()+SS);
                h_SS[j][0]->Write();
                h_SSloose[j][0]->SetName(name.c_str()+SSloose);
                h_SSloose[j][0]->Write();
            }
            //shifted
            for (int i = 0; i < 4; ++i){
                h_OS[j][i+1]->SetName(name.c_str()+shape_eleES[i]);
                h_OS[j][i+1]->Write();
                if (isnonSignal){
                    h_SS[j][i+1]->SetName(name.c_str()+SS+shape_eleES[i]);
                    h_SS[j][i+1]->Write();
                    h_SSloose[j][i+1]->SetName(name.c_str()+SSloose+shape_eleES[i]);
                    h_SSloose[j][i+1]->Write();
                }
            }
            for (int i = 0; i < 6; ++i){
                h_OS[j][i+5]->SetName(name.c_str()+shape_muonES[i]);
                h_OS[j][i+5]->Write();
                if (isnonSignal){
                    h_SS[j][i+5]->SetName(name.c_str()+SS+shape_muonES[i]);
                    h_SS[j][i+5]->Write();
                    h_SSloose[j][i+5]->SetName(name.c_str()+SSloose+shape_muonES[i]);
                    h_SSloose[j][i+5]->Write();
                }
            }
            if (sample!="embedded"){
                for (int i = 0; i < 22; ++i){
                    h_OS[j][i+11]->SetName(name.c_str()+shape_jet[i]);
                    h_OS[j][i+11]->Write();
                    if (isnonSignal){
                        h_SS[j][i+11]->SetName(name.c_str()+SS+shape_jet[i]);
                        h_SS[j][i+11]->Write();
                        h_SSloose[j][i+11]->SetName(name.c_str()+SSloose+shape_jet[i]);
                        h_SSloose[j][i+11]->Write();
                    }
                }
            }
            for (int i = 0; i < 6; ++i){
                h_OS[j][i+33]->SetName(name.c_str()+shape_trgeff[i]);
                h_OS[j][i+33]->Write();
                if (isnonSignal){
                    h_SS[j][i+33]->SetName(name.c_str()+SS+shape_trgeff[i]);
                    h_SS[j][i+33]->Write();
                    h_SSloose[j][i+33]->SetName(name.c_str()+SSloose+shape_trgeff[i]);
                    h_SSloose[j][i+33]->Write();
                }
            }
            //DY MC only
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                for (int i = 0; i < 2; ++i){
                    h_OS[j][i+39]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_OS[j][i+39]->Write();
                    if (isnonSignal){
                        h_SS[j][i+39]->SetName(name.c_str()+SS+shape_DY_zpt[i]);
                        h_SS[j][i+39]->Write();
                        h_SSloose[j][i+39]->SetName(name.c_str()+SSloose+shape_DY_zpt[i]);
                        h_SSloose[j][i+39]->Write();
                    }
                }
            }
            //ttbar only
            if (sample=="TTTo2L2Nu" or sample=="TTToHadronic" or sample=="TTToSemiLeptonic" or name=="TT"){
                for (int i = 0; i < 2; ++i){
                    h_OS[j][i+41]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_OS[j][i+41]->Write();
                    if (isnonSignal){
                        h_SS[j][i+41]->SetName(name.c_str()+SS+shape_ttbar_toppt[i]);
                        h_SS[j][i+41]->Write();
                        h_SSloose[j][i+41]->SetName(name.c_str()+SSloose+shape_ttbar_toppt[i]);
                        h_SSloose[j][i+41]->Write();
                    }
                }
            }
            //recoil: MC except ttbar diboson singletop
            if (sample!="embedded" && name!="TT" && name!="VV" && name!="ST"){
                for (int i = 0; i < 12; ++i){
                    h_OS[j][i+43]->SetName(name.c_str()+shape_recoil[i]);
                    h_OS[j][i+43]->Write();
                    if (isnonSignal){
                        h_SS[j][i+43]->SetName(name.c_str()+SS+shape_recoil[i]);
                        h_SS[j][i+43]->Write();
                        h_SSloose[j][i+43]->SetName(name.c_str()+SSloose+shape_recoil[i]);
                        h_SSloose[j][i+43]->Write();
                    }
                }
            }
            //met unclustered ES: only on ttbar diboson singletop
            if (name=="TT" or name=="VV" or name=="ST"){
                for (int i = 0; i < 2; ++i){
                    h_OS[j][i+55]->SetName(name.c_str()+shape_unclusteredES[i]);
                    h_OS[j][i+55]->Write();
                    if (isnonSignal){
                        h_SS[j][i+55]->SetName(name.c_str()+SS+shape_unclusteredES[i]);
                        h_SS[j][i+55]->Write();
                        h_SSloose[j][i+55]->SetName(name.c_str()+SSloose+shape_unclusteredES[i]);
                        h_SSloose[j][i+55]->Write();
                    }
                }
            }
            //JER
            if (sample!="embedded"){
                for (int i = 0; i < 2; ++i){
                    h_OS[j][i+57]->SetName(name.c_str()+shape_jer[i]);
                    h_OS[j][i+57]->Write();
                    if (isnonSignal){
                        h_SS[j][i+57]->SetName(name.c_str()+SS+shape_jer[i]);
                        h_SS[j][i+57]->Write();
                        h_SSloose[j][i+57]->SetName(name.c_str()+SSloose+shape_jer[i]);
                        h_SSloose[j][i+57]->Write();
                    }
                }
            }
            //nonDY
            if (isnonHiggsMC && name!="Z"){
                TString nonDYMC = "nonDYMC";
                h_OS[j][59]->SetName(nonDYMC+shape_nonDY[0]);
                h_OS[j][59]->Write();
            }
            //SS correction/closure
            if (isnonSignal){
                for (int i = 0; i < 6; ++i){
                    h_SS[j][i+59]->SetName(name.c_str()+SS+shape_ss2d[i]);
                    h_SS[j][i+59]->Write();
                    h_SSloose[j][i+59]->SetName(name.c_str()+SSloose+shape_ss2d[i]);
                    h_SSloose[j][i+59]->Write();
                }
            }
        }//end of (sample!="data_obs)
        if (sample=="data_obs"){
            h_OS[j][0]->SetName(name.c_str());
            h_OS[j][0]->Write();
            h_SS[j][0]->SetName(name.c_str()+SS);
            h_SS[j][0]->Write();
            h_SSloose[j][0]->SetName(name.c_str()+SSloose);
            h_SSloose[j][0]->Write();
            //SS correction/closure
            for (int i = 0; i < 6; ++i){
                h_SS[j][i+59]->SetName(name.c_str()+SS+shape_ss2d[i]);
                h_SS[j][i+59]->Write();
                h_SSloose[j][i+59]->SetName(name.c_str()+SSloose+shape_ss2d[i]);
                h_SSloose[j][i+59]->Write();
            }
        }
    }
    
    fout->Close();
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}




