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
#include "LumiReweightingStandAlone.h"
#include "btagSF_deepflavour.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "NN_transform.h"

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
    std::string NNfile = "/hdfs/store/user/htsoi/NN/em18/" + sample_name + ".root";
    if (year=="2017") NNfile = "/hdfs/store/user/htsoi/NN/em17/" + sample_name + ".root";
    if (year=="2016") NNfile = "/hdfs/store/user/htsoi/NN/em16/" + sample_name + ".root";
    TFile * NN = new TFile(NNfile.c_str());
    TTree * tree_NN = (TTree*) NN->Get("emu_tree_NN");
    
    //sample weights
    float xs, weight;
    float luminosity = 59740.0;
    if (year=="2017") luminosity = 41530.0;
    if (year=="2016") luminosity = 36330.0;
    
    if (sample == "data_obs"){weight = 1.0;}
    else if(sample == "gghbbtt12"){xs = 0.01*48.58*0.0378; if(year=="2017") xs = 0.01*48.58*0.0378; if(year=="2016") xs = 0.01*48.58*0.0381; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt15"){xs = 0.01*48.58*0.0349; if(year=="2017") xs = 0.01*48.58*0.0355; if(year=="2016") xs = 0.01*48.58*0.0354; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt20"){xs = 0.01*48.58*0.0336; if(year=="2017") xs = 0.01*48.58*0.0340; if(year=="2016") xs = 0.01*48.58*0.0337; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt25"){xs = 0.01*48.58*0.0346; if(year=="2017") xs = 0.01*48.58*0.0332; if(year=="2016") xs = 0.01*48.58*0.0356; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt30"){xs = 0.01*48.58*0.0318; if(year=="2017") xs = 0.01*48.58*0.0336; if(year=="2016") xs = 0.01*48.58*0.0316; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt35"){xs = 0.01*48.58*0.0328; if(year=="2017") xs = 0.01*48.58*0.0327; if(year=="2016") xs = 0.01*48.58*0.0330; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt40"){xs = 0.01*48.58*0.0310; if(year=="2017") xs = 0.01*48.58*0.0303; if(year=="2016") xs = 0.01*48.58*0.0330; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt45"){xs = 0.01*48.58*0.0321; if(year=="2017") xs = 0.01*48.58*0.0303; if(year=="2016") xs = 0.01*48.58*0.0323; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt50"){xs = 0.01*48.58*0.0314; if(year=="2017") xs = 0.01*48.58*0.0331; if(year=="2016") xs = 0.01*48.58*0.0342; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt55"){xs = 0.01*48.58*0.0356; if(year=="2017") xs = 0.01*48.58*0.0356; if(year=="2016") xs = 0.01*48.58*0.0365; weight = luminosity*xs/N;}
    else if(sample == "gghbbtt60"){xs = 0.01*48.58*0.0338; if(year=="2017") xs = 0.01*48.58*0.0395; if(year=="2016") xs = 0.01*48.58*0.0373; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt12"){xs = 0.01*3.782*0.0778; if(year=="2017") xs = 0.01*3.782*0.0773; if(year=="2016") xs = 0.01*3.782*0.0794; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt15"){xs = 0.01*3.782*0.0752; if(year=="2017") xs = 0.01*3.782*0.0735; if(year=="2016") xs = 0.01*3.782*0.0738; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt20"){xs = 0.01*3.782*0.0687; if(year=="2017") xs = 0.01*3.782*0.0733; if(year=="2016") xs = 0.01*3.782*0.0727; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt25"){xs = 0.01*3.782*0.0721; if(year=="2017") xs = 0.01*3.782*0.0723; if(year=="2016") xs = 0.01*3.782*0.0721; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt30"){xs = 0.01*3.782*0.0651; if(year=="2017") xs = 0.01*3.782*0.0684; if(year=="2016") xs = 0.01*3.782*0.0687; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt35"){xs = 0.01*3.782*0.0695; if(year=="2017") xs = 0.01*3.782*0.0697; if(year=="2016") xs = 0.01*3.782*0.0680; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt40"){xs = 0.01*3.782*0.0681; if(year=="2017") xs = 0.01*3.782*0.0617; if(year=="2016") xs = 0.01*3.782*0.0678; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt45"){xs = 0.01*3.782*0.0662; if(year=="2017") xs = 0.01*3.782*0.0667; if(year=="2016") xs = 0.01*3.782*0.0656; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt50"){xs = 0.01*3.782*0.0656; if(year=="2017") xs = 0.01*3.782*0.0661; if(year=="2016") xs = 0.01*3.782*0.0640; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt55"){xs = 0.01*3.782*0.0664; if(year=="2017") xs = 0.01*3.782*0.0651; if(year=="2016") xs = 0.01*3.782*0.0654; weight = luminosity*xs/N;}
    else if(sample == "vbfbbtt60"){xs = 0.01*3.782*0.0675; if(year=="2017") xs = 0.01*3.782*0.0671; if(year=="2016") xs = 0.01*3.782*0.0655; weight = luminosity*xs/N;}
    else if(sample == "embedded"){weight = 1.0;}
    else if(sample == "DY"){weight = 1.0;}
    else if(sample == "DY1"){weight = 1.0;}
    else if(sample == "DY2"){weight = 1.0;}
    else if(sample == "DY3"){weight = 1.0;}
    else if(sample == "DY4"){weight = 1.0;}
    else if(sample == "DYlow"){weight = 1.0;}
    else if(sample == "DY1low"){weight = 1.0;}
    else if(sample == "DY2low"){weight = 1.0;}
    else if(sample == "DY3low"){weight = 1.0;}
    else if(sample == "DY4low"){weight = 1.0;}
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
    else if(sample == "VBFHTT"){xs = 3.782*0.0627; weight = luminosity*xs/N;}
    else if(sample == "VBFHWW"){xs = 3.782*0.2137*0.3258*0.3258; weight = luminosity*xs/N;}
    else if(sample == "VV2L2Nu"){xs = 13.84; weight = luminosity*xs/N;}//11.95
    else if(sample == "W"){weight = 1.0;}
    else if(sample == "W1"){weight = 1.0;}
    else if(sample == "W2"){weight = 1.0;}
    else if(sample == "W3"){weight = 1.0;}
    else if(sample == "W4"){weight = 1.0;}
    else if(sample == "WZ2L2Q"){xs = 5.52; weight = luminosity*xs/N;}//5.595
    else if(sample == "WZ3L1Nu"){xs = 4.43; weight = luminosity*xs/N;}//4.708
    else if(sample == "WminusHTT"){xs = 0.5328*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WminusHWW"){xs = 0.5328*0.2137; weight = luminosity*xs/N;}
    else if(sample == "WplusHTT"){xs = 0.840*0.0627; weight = luminosity*xs/N;}
    else if(sample == "WplusHWW"){xs = 0.840*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZHTT"){xs = 0.7612*0.0627; weight = luminosity*xs/N;}
    else if(sample == "ZHWW"){xs = 0.7612*0.2137; weight = luminosity*xs/N;}
    else if(sample == "ZZ2L2Q"){xs = 3.38; weight = luminosity*xs/N;}//3.22
    else if(sample == "ZZ4L"){xs = 1.212; weight = luminosity*xs/N;}
    else if(sample == "ttHnonbb"){xs = 0.5071*(1-0.5824); weight = luminosity*xs/N;}
    else if(sample == "ttHbb"){xs = 0.5071*0.5824; weight = luminosity*xs/N;}
    else {cout << "Missing sample cross section!!!" << endl; return 0;}
    
    bool isSignal = (sample=="gghbbtt12" or sample=="gghbbtt15" or sample=="gghbbtt20" or sample=="gghbbtt25" or sample=="gghbbtt30" or sample=="gghbbtt35" or sample=="gghbbtt40" or sample=="gghbbtt45" or sample=="gghbbtt50" or sample=="gghbbtt55" or sample=="gghbbtt60" or sample=="vbfbbtt12" or sample=="vbfbbtt15" or sample=="vbfbbtt20" or sample=="vbfbbtt25" or sample=="vbfbbtt30" or sample=="vbfbbtt35" or sample=="vbfbbtt40" or sample=="vbfbbtt45" or sample=="vbfbbtt50" or sample=="vbfbbtt55" or sample=="vbfbbtt60");
    bool isMCnonHiggs = (sample!="data_obs" && sample!="embedded" && !isSignal && name!="ggh_htt" && name!="ggh_hww" && name!="qqh_htt" && name!="qqh_hww" && name!="Zh_htt" && name!="Zh_hww" && name!="Wh_htt" && name!="Wh_hww" && name!="tth");
    bool isRecoilMC = (isSignal or name=="ZJ" or name=="WJ" or name=="ggh_htt" or name=="ggh_hww" or name=="qqh_htt" or name=="qqh_hww");
    bool isnonRecoilMC = (sample!="data_obs" && sample!="embedded" && !isRecoilMC);
    
    tree->SetBranchAddress("run", &run);
    tree->SetBranchAddress("pt_1", &pt_1);
    tree->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    tree->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);
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
    tree->SetBranchAddress("bpt_deepflavour_1", &bpt_deepflavour_1);
    tree->SetBranchAddress("bflavour_deepflavour_1", &bflavour_deepflavour_1);
    tree->SetBranchAddress("beta_deepflavour_1", &beta_deepflavour_1);
    tree->SetBranchAddress("bphi_deepflavour_1", &bphi_deepflavour_1);
    tree->SetBranchAddress("bm_deepflavour_1", &bm_deepflavour_1);
    tree->SetBranchAddress("bscore_deepflavour_1", &bscore_deepflavour_1);
    tree->SetBranchAddress("bpt_deepflavour_2", &bpt_deepflavour_2);
    tree->SetBranchAddress("bflavour_deepflavour_2", &bflavour_deepflavour_2);
    tree->SetBranchAddress("beta_deepflavour_2", &beta_deepflavour_2);
    tree->SetBranchAddress("bphi_deepflavour_2", &bphi_deepflavour_2);
    tree->SetBranchAddress("bm_deepflavour_2", &bm_deepflavour_2);
    tree->SetBranchAddress("bscore_deepflavour_2", &bscore_deepflavour_2);
    tree->SetBranchAddress("bpt_deepflavour_JERUp_1", &bpt_deepflavour_JERUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JERDown_1", &bpt_deepflavour_JERDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteUp_1", &bpt_deepflavour_JetAbsoluteUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteDown_1", &bpt_deepflavour_JetAbsoluteDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteyearUp_1", &bpt_deepflavour_JetAbsoluteyearUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteyearDown_1", &bpt_deepflavour_JetAbsoluteyearDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1Up_1", &bpt_deepflavour_JetBBEC1Up_1);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1Down_1", &bpt_deepflavour_JetBBEC1Down_1);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1yearUp_1", &bpt_deepflavour_JetBBEC1yearUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1yearDown_1", &bpt_deepflavour_JetBBEC1yearDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2Up_1", &bpt_deepflavour_JetEC2Up_1);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2Down_1", &bpt_deepflavour_JetEC2Down_1);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2yearUp_1", &bpt_deepflavour_JetEC2yearUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2yearDown_1", &bpt_deepflavour_JetEC2yearDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetFlavorQCDUp_1", &bpt_deepflavour_JetFlavorQCDUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetFlavorQCDDown_1", &bpt_deepflavour_JetFlavorQCDDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetHFUp_1", &bpt_deepflavour_JetHFUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetHFDown_1", &bpt_deepflavour_JetHFDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetHFyearUp_1", &bpt_deepflavour_JetHFyearUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetHFyearDown_1", &bpt_deepflavour_JetHFyearDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeBalUp_1", &bpt_deepflavour_JetRelativeBalUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeBalDown_1", &bpt_deepflavour_JetRelativeBalDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeSampleUp_1", &bpt_deepflavour_JetRelativeSampleUp_1);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeSampleDown_1", &bpt_deepflavour_JetRelativeSampleDown_1);
    tree->SetBranchAddress("bpt_deepflavour_JERUp_2", &bpt_deepflavour_JERUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JERDown_2", &bpt_deepflavour_JERDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteUp_2", &bpt_deepflavour_JetAbsoluteUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteDown_2", &bpt_deepflavour_JetAbsoluteDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteyearUp_2", &bpt_deepflavour_JetAbsoluteyearUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetAbsoluteyearDown_2", &bpt_deepflavour_JetAbsoluteyearDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1Up_2", &bpt_deepflavour_JetBBEC1Up_2);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1Down_2", &bpt_deepflavour_JetBBEC1Down_2);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1yearUp_2", &bpt_deepflavour_JetBBEC1yearUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetBBEC1yearDown_2", &bpt_deepflavour_JetBBEC1yearDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2Up_2", &bpt_deepflavour_JetEC2Up_2);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2Down_2", &bpt_deepflavour_JetEC2Down_2);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2yearUp_2", &bpt_deepflavour_JetEC2yearUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetEC2yearDown_2", &bpt_deepflavour_JetEC2yearDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetFlavorQCDUp_2", &bpt_deepflavour_JetFlavorQCDUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetFlavorQCDDown_2", &bpt_deepflavour_JetFlavorQCDDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetHFUp_2", &bpt_deepflavour_JetHFUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetHFDown_2", &bpt_deepflavour_JetHFDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetHFyearUp_2", &bpt_deepflavour_JetHFyearUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetHFyearDown_2", &bpt_deepflavour_JetHFyearDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeBalUp_2", &bpt_deepflavour_JetRelativeBalUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeBalDown_2", &bpt_deepflavour_JetRelativeBalDown_2);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeSampleUp_2", &bpt_deepflavour_JetRelativeSampleUp_2);
    tree->SetBranchAddress("bpt_deepflavour_JetRelativeSampleDown_2", &bpt_deepflavour_JetRelativeSampleDown_2);
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
    tree->SetBranchAddress("prefiring_weight_up", &prefiring_weight_up);
    tree->SetBranchAddress("prefiring_weight_down", &prefiring_weight_down);
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
    
    tree_NN->SetBranchAddress("NN1b", &NN1b);
    tree_NN->SetBranchAddress("NN1b_muonESUp", &NN1b_muonESUp);
    tree_NN->SetBranchAddress("NN1b_muonESDown", &NN1b_muonESDown);
    tree_NN->SetBranchAddress("NN1b_UESUp", &NN1b_UESUp);
    tree_NN->SetBranchAddress("NN1b_UESDown", &NN1b_UESDown);
    tree_NN->SetBranchAddress("NN1b_JERUp", &NN1b_JERUp);
    tree_NN->SetBranchAddress("NN1b_JERDown", &NN1b_JERDown);
    tree_NN->SetBranchAddress("NN1b_ESCALEUP", &NN1b_ESCALEUP);
    tree_NN->SetBranchAddress("NN1b_ESCALEDOWN", &NN1b_ESCALEDOWN);
    tree_NN->SetBranchAddress("NN1b_JetAbsoluteUp", &NN1b_JetAbsoluteUp);
    tree_NN->SetBranchAddress("NN1b_JetAbsoluteDown", &NN1b_JetAbsoluteDown);
    tree_NN->SetBranchAddress("NN1b_JetAbsoluteyearUp", &NN1b_JetAbsoluteyearUp);
    tree_NN->SetBranchAddress("NN1b_JetAbsoluteyearDown", &NN1b_JetAbsoluteyearDown);
    tree_NN->SetBranchAddress("NN1b_JetBBEC1Up", &NN1b_JetBBEC1Up);
    tree_NN->SetBranchAddress("NN1b_JetBBEC1Down", &NN1b_JetBBEC1Down);
    tree_NN->SetBranchAddress("NN1b_JetBBEC1yearUp", &NN1b_JetBBEC1yearUp);
    tree_NN->SetBranchAddress("NN1b_JetBBEC1yearDown", &NN1b_JetBBEC1yearDown);
    tree_NN->SetBranchAddress("NN1b_JetEC2Up", &NN1b_JetEC2Up);
    tree_NN->SetBranchAddress("NN1b_JetEC2Down", &NN1b_JetEC2Down);
    tree_NN->SetBranchAddress("NN1b_JetEC2yearUp", &NN1b_JetEC2yearUp);
    tree_NN->SetBranchAddress("NN1b_JetEC2yearDown", &NN1b_JetEC2yearDown);
    tree_NN->SetBranchAddress("NN1b_JetFlavorQCDUp", &NN1b_JetFlavorQCDUp);
    tree_NN->SetBranchAddress("NN1b_JetFlavorQCDDown", &NN1b_JetFlavorQCDDown);
    tree_NN->SetBranchAddress("NN1b_JetHFUp", &NN1b_JetHFUp);
    tree_NN->SetBranchAddress("NN1b_JetHFDown", &NN1b_JetHFDown);
    tree_NN->SetBranchAddress("NN1b_JetHFyearUp", &NN1b_JetHFyearUp);
    tree_NN->SetBranchAddress("NN1b_JetHFyearDown", &NN1b_JetHFyearDown);
    tree_NN->SetBranchAddress("NN1b_JetRelativeBalUp", &NN1b_JetRelativeBalUp);
    tree_NN->SetBranchAddress("NN1b_JetRelativeBalDown", &NN1b_JetRelativeBalDown);
    tree_NN->SetBranchAddress("NN1b_JetRelativeSampleUp", &NN1b_JetRelativeSampleUp);
    tree_NN->SetBranchAddress("NN1b_JetRelativeSampleDown", &NN1b_JetRelativeSampleDown);
    tree_NN->SetBranchAddress("NN1b_ResponseUp", &NN1b_ResponseUp);
    tree_NN->SetBranchAddress("NN1b_ResponseDown", &NN1b_ResponseDown);
    tree_NN->SetBranchAddress("NN1b_ResolutionUp", &NN1b_ResolutionUp);
    tree_NN->SetBranchAddress("NN1b_ResolutionDown", &NN1b_ResolutionDown);
    tree_NN->SetBranchAddress("NN2b", &NN2b);
    tree_NN->SetBranchAddress("NN2b_muonESUp", &NN2b_muonESUp);
    tree_NN->SetBranchAddress("NN2b_muonESDown", &NN2b_muonESDown);
    tree_NN->SetBranchAddress("NN2b_UESUp", &NN2b_UESUp);
    tree_NN->SetBranchAddress("NN2b_UESDown", &NN2b_UESDown);
    tree_NN->SetBranchAddress("NN2b_JERUp", &NN2b_JERUp);
    tree_NN->SetBranchAddress("NN2b_JERDown", &NN2b_JERDown);
    tree_NN->SetBranchAddress("NN2b_ESCALEUP", &NN2b_ESCALEUP);
    tree_NN->SetBranchAddress("NN2b_ESCALEDOWN", &NN2b_ESCALEDOWN);
    tree_NN->SetBranchAddress("NN2b_JetAbsoluteUp", &NN2b_JetAbsoluteUp);
    tree_NN->SetBranchAddress("NN2b_JetAbsoluteDown", &NN2b_JetAbsoluteDown);
    tree_NN->SetBranchAddress("NN2b_JetAbsoluteyearUp", &NN2b_JetAbsoluteyearUp);
    tree_NN->SetBranchAddress("NN2b_JetAbsoluteyearDown", &NN2b_JetAbsoluteyearDown);
    tree_NN->SetBranchAddress("NN2b_JetBBEC1Up", &NN2b_JetBBEC1Up);
    tree_NN->SetBranchAddress("NN2b_JetBBEC1Down", &NN2b_JetBBEC1Down);
    tree_NN->SetBranchAddress("NN2b_JetBBEC1yearUp", &NN2b_JetBBEC1yearUp);
    tree_NN->SetBranchAddress("NN2b_JetBBEC1yearDown", &NN2b_JetBBEC1yearDown);
    tree_NN->SetBranchAddress("NN2b_JetEC2Up", &NN2b_JetEC2Up);
    tree_NN->SetBranchAddress("NN2b_JetEC2Down", &NN2b_JetEC2Down);
    tree_NN->SetBranchAddress("NN2b_JetEC2yearUp", &NN2b_JetEC2yearUp);
    tree_NN->SetBranchAddress("NN2b_JetEC2yearDown", &NN2b_JetEC2yearDown);
    tree_NN->SetBranchAddress("NN2b_JetFlavorQCDUp", &NN2b_JetFlavorQCDUp);
    tree_NN->SetBranchAddress("NN2b_JetFlavorQCDDown", &NN2b_JetFlavorQCDDown);
    tree_NN->SetBranchAddress("NN2b_JetHFUp", &NN2b_JetHFUp);
    tree_NN->SetBranchAddress("NN2b_JetHFDown", &NN2b_JetHFDown);
    tree_NN->SetBranchAddress("NN2b_JetHFyearUp", &NN2b_JetHFyearUp);
    tree_NN->SetBranchAddress("NN2b_JetHFyearDown", &NN2b_JetHFyearDown);
    tree_NN->SetBranchAddress("NN2b_JetRelativeBalUp", &NN2b_JetRelativeBalUp);
    tree_NN->SetBranchAddress("NN2b_JetRelativeBalDown", &NN2b_JetRelativeBalDown);
    tree_NN->SetBranchAddress("NN2b_JetRelativeSampleUp", &NN2b_JetRelativeSampleUp);
    tree_NN->SetBranchAddress("NN2b_JetRelativeSampleDown", &NN2b_JetRelativeSampleDown);
    tree_NN->SetBranchAddress("NN2b_ResponseUp", &NN2b_ResponseUp);
    tree_NN->SetBranchAddress("NN2b_ResponseDown", &NN2b_ResponseDown);
    tree_NN->SetBranchAddress("NN2b_ResolutionUp", &NN2b_ResolutionUp);
    tree_NN->SetBranchAddress("NN2b_ResolutionDown", &NN2b_ResolutionDown);
    
    TString shape_eleES[4] = {"_CMS_eleES_bar_"+year+"Up","_CMS_eleES_bar_"+year+"Down","_CMS_eleES_end_"+year+"Up","_CMS_eleES_end_"+year+"Down"};
    TString shape_muonES[6] = {"_CMS_muES_eta0to1p2_"+year+"Up","_CMS_muES_eta0to1p2_"+year+"Down","_CMS_muES_eta1p2to2p1_"+year+"Up","_CMS_muES_eta1p2to2p1_"+year+"Down","_CMS_muES_eta2p1to2p4_"+year+"Up","_CMS_muES_eta2p1to2p4_"+year+"Down"};
    TString shape_trgeff[6] = {"_CMS_trgeff_Mu8E23_em_"+year+"Up","_CMS_trgeff_Mu8E23_em_"+year+"Down","_CMS_trgeff_Mu23E12_em_"+year+"Up","_CMS_trgeff_Mu23E12_em_"+year+"Down","_CMS_trgeff_both_em_"+year+"Up","_CMS_trgeff_both_em_"+year+"Down"};
    TString shape_btagsf[4] = {"_CMS_btagsf_heavy_"+year+"Up","_CMS_btagsf_heavy_"+year+"Down","_CMS_btagsf_light_"+year+"Up","_CMS_btagsf_light_"+year+"Down"};
    TString shape_jet[24] = {"_CMS_JetAbsoluteUp","_CMS_JetAbsoluteDown","_CMS_JetAbsolute_"+year+"Up","_CMS_JetAbsolute_"+year+"Down","_CMS_JetBBEC1Up","_CMS_JetBBEC1Down","_CMS_JetBBEC1_"+year+"Up","_CMS_JetBBEC1_"+year+"Down","_CMS_JetEC2Up","_CMS_JetEC2Down","_CMS_JetEC2_"+year+"Up","_CMS_JetEC2_"+year+"Down","_CMS_JetFlavorQCDUp","_CMS_JetFlavorQCDDown","_CMS_JetHFUp","_CMS_JetHFDown","_CMS_JetHF_"+year+"Up","_CMS_JetHF_"+year+"Down","_CMS_JetRelativeBalUp","_CMS_JetRelativeBalDown","_CMS_JetRelativeSampleUp","_CMS_JetRelativeSampleDown","_CMS_JERUp","_CMS_JERDown"};
    //Z+jets, W+jets, ggH, qqH
    TString shape_recoil[12] = {"_CMS_0j_resolution_"+year+"Up","_CMS_0j_resolution_"+year+"Down","_CMS_0j_response_"+year+"Up","_CMS_0j_response_"+year+"Down","_CMS_1j_resolution_"+year+"Up","_CMS_1j_resolution_"+year+"Down","_CMS_1j_response_"+year+"Up","_CMS_1j_response_"+year+"Down","_CMS_gt1j_resolution_"+year+"Up","_CMS_gt1j_resolution_"+year+"Down","_CMS_gt1j_response_"+year+"Up","_CMS_gt1j_response_"+year+"Down"};
    //those without recoil
    TString shape_UES[2] = {"_CMS_UES_"+year+"Up","_CMS_UES_"+year+"Down"};
    //for DY MC only
    TString shape_DY_zpt[2] = {"_CMS_Zpt_"+year+"Up","_CMS_Zpt_"+year+"Down"};
    //for ttbar only
    TString shape_ttbar_toppt[2] = {"_CMS_toppt_"+year+"Up","_CMS_toppt_"+year+"Down"};
    //SS 2d correction/closure
    TString shape_ss[8] = {"_CMS_SScorrection_"+year+"Up","_CMS_SScorrection_"+year+"Down","_CMS_SSclosure_"+year+"Up","_CMS_SSclosure_"+year+"Down","_CMS_SSboth2D_"+year+"Up","_CMS_SSboth2D_"+year+"Down","_CMS_osss_"+year+"Up","_CMS_osss_"+year+"Down"};
    //prefiring
    TString shape_prefiring[2] = {"_CMS_prefiring_"+year+"Up","_CMS_prefiring_"+year+"Down"};// only 2016 and 2017
    
    //give different names for embedded
    TString embshape_trgeff[6] = {"_CMS_EMB_trgeff_Mu8E23_em_"+year+"Up","_CMS_EMB_trgeff_Mu8E23_em_"+year+"Down","_CMS_EMB_trgeff_Mu23E12_em_"+year+"Up","_CMS_EMB_trgeff_Mu23E12_em_"+year+"Down","_CMS_EMB_trgeff_both_em_"+year+"Up","_CMS_EMB_trgeff_both_em_"+year+"Down"};
    TString embshape_eleES[4] = {"_CMS_EMB_eleES_bar_"+year+"Up","_CMS_EMB_eleES_bar_"+year+"Down","_CMS_EMB_eleES_end_"+year+"Up","_CMS_EMB_eleES_end_"+year+"Down"};
    TString embshape_muonES[6] = {"_CMS_EMB_muES_eta0to1p2_"+year+"Up","_CMS_EMB_muES_eta0to1p2_"+year+"Down","_CMS_EMB_muES_eta1p2to2p1_"+year+"Up","_CMS_EMB_muES_eta1p2to2p1_"+year+"Down","_CMS_EMB_muES_eta2p1to2p4_"+year+"Up","_CMS_EMB_muES_eta2p1to2p4_"+year+"Down"};
    
    //comtamination to emb: all non-DY MC with gen tautau
    TString shape_nonDY[1] = {"nonDYMC"};
    
    //h[i][j][k]: (i=0: 1bjet, i=1: 2bjets), (j=filling variable), (k=systematics type)
    std::vector<std::vector<std::vector<TH1F*>>> h_os;
    std::vector<std::vector<std::vector<TH1F*>>> h_ss;
    std::vector<std::vector<std::vector<TH1F*>>> h_ssloose;
    for (int i = 0; i < 3; i++){
        h_os.push_back(std::vector<std::vector<TH1F*>>());
        h_ss.push_back(std::vector<std::vector<TH1F*>>());
        h_ssloose.push_back(std::vector<std::vector<TH1F*>>());
    }
    for (int i = 0; i < 7; i++){//no. of variables for 1 bjet category
        h_os[0].push_back(std::vector<TH1F*>());
        h_ss[0].push_back(std::vector<TH1F*>());
        h_ssloose[0].push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 8; i++){//no. of variables for 2 bjets category
        h_os[1].push_back(std::vector<TH1F*>());
        h_ss[1].push_back(std::vector<TH1F*>());
        h_ssloose[1].push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 7; i++){//no. of final mtt categories
        h_os[2].push_back(std::vector<TH1F*>());
        h_ss[2].push_back(std::vector<TH1F*>());
        h_ssloose[2].push_back(std::vector<TH1F*>());
    }
    /*
    float bins_p_1b[] = {0.,0.02,0.04,0.06,0.08,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.85,0.9,0.92,0.94,0.96,0.98,1.};
    float bins_p_2b[] = {0.,0.05,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,1.};
    int nbins_p_1b = sizeof(bins_p_1b)/sizeof(Float_t)-1;
    int nbins_p_2b = sizeof(bins_p_2b)/sizeof(Float_t)-1;*/
    
    for (int i = 0; i < 66; i++){
        //i=0 nominal, 1-4 eleES, 5-10 muES, 11-16 trgsf, 17-20 btagsf, 21-44 jet, 45-56 recoil, 57-58 UES, 59-60 DY zpt, 61-62 ttbar toppt, 63 nonDY, 64-65 prefiring (2016-17)
        //1 bjet
        h_os[0][0].push_back(new TH1F("","",40,0.,1.));//p
        h_os[0][1].push_back(new TH1F("","",40,0.,1.));//p2
        h_os[0][2].push_back(new TH1F("","",20,0.8,1.));//p2_z
        h_os[0][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_os[0][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_os[0][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_os[0][6].push_back(new TH1F("","",42,40,460));//m_btt
        //2 bjets
        h_os[1][0].push_back(new TH1F("","",20,0.,1.));//p
        h_os[1][1].push_back(new TH1F("","",20,0.,1.));//p2
        h_os[1][2].push_back(new TH1F("","",40,0.8,1.));//p2_z
        h_os[1][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_os[1][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_os[1][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_os[1][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_os[1][7].push_back(new TH1F("","",54,60,600));//m_bbtt
        //final mtt categories
        h_os[2][0].push_back(new TH1F("","",13,0,104));//m_tt_1
        h_os[2][1].push_back(new TH1F("","",13,0,104));//m_tt_2
        h_os[2][2].push_back(new TH1F("","",13,0,104));//m_tt_3
        h_os[2][3].push_back(new TH1F("","",15,0,300));//m_tt_4
        h_os[2][4].push_back(new TH1F("","",9,0,108));//m_tt_5
        h_os[2][5].push_back(new TH1F("","",9,0,108));//m_tt_6
        h_os[2][6].push_back(new TH1F("","",15,0,300));//m_tt_7
    }
    for (int i = 0; i < 73; i++){
        //SS region; 1-4 eleES, 5-10 muES, 11-16 trgsf, 17-20 btagsf, 21-44 jet, 45-56 recoil, 57-58 UES, 59-60 DY zpt, 61-62 ttbar toppt, 63-70 SS correction/closure/osss, 71-72 prefiring (2016-17)
        //1 bjet
        h_ss[0][0].push_back(new TH1F("","",40,0.,1.));//p
        h_ss[0][1].push_back(new TH1F("","",40,0.,1.));//p2
        h_ss[0][2].push_back(new TH1F("","",20,0.8,1.));//p2_z
        h_ss[0][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_ss[0][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_ss[0][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_ss[0][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_ssloose[0][0].push_back(new TH1F("","",40,0.,1.));//p
        h_ssloose[0][1].push_back(new TH1F("","",40,0.,1.));//p2
        h_ssloose[0][2].push_back(new TH1F("","",20,0.8,1.));//p2_z
        h_ssloose[0][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_ssloose[0][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_ssloose[0][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_ssloose[0][6].push_back(new TH1F("","",42,40,460));//m_btt
        //2 bjets
        h_ss[1][0].push_back(new TH1F("","",20,0.,1.));//p
        h_ss[1][1].push_back(new TH1F("","",20,0.,1.));//p2
        h_ss[1][2].push_back(new TH1F("","",40,0.8,1.));//p2_z
        h_ss[1][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_ss[1][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_ss[1][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_ss[1][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_ss[1][7].push_back(new TH1F("","",54,60,600));//m_bbtt
        h_ssloose[1][0].push_back(new TH1F("","",20,0.,1.));//p
        h_ssloose[1][1].push_back(new TH1F("","",20,0.,1.));//p2
        h_ssloose[1][2].push_back(new TH1F("","",40,0.8,1.));//p2_z
        h_ssloose[1][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_ssloose[1][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_ssloose[1][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_ssloose[1][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_ssloose[1][7].push_back(new TH1F("","",54,60,600));//m_bbtt
        //final mtt categories
        h_ss[2][0].push_back(new TH1F("","",13,0,104));//m_tt_1
        h_ss[2][1].push_back(new TH1F("","",13,0,104));//m_tt_2
        h_ss[2][2].push_back(new TH1F("","",13,0,104));//m_tt_3
        h_ss[2][3].push_back(new TH1F("","",15,0,300));//m_tt_4
        h_ss[2][4].push_back(new TH1F("","",9,0,108));//m_tt_5
        h_ss[2][5].push_back(new TH1F("","",9,0,108));//m_tt_6
        h_ss[2][6].push_back(new TH1F("","",15,0,300));//m_tt_7
        h_ssloose[2][0].push_back(new TH1F("","",13,0,104));//m_tt_1
        h_ssloose[2][1].push_back(new TH1F("","",13,0,104));//m_tt_2
        h_ssloose[2][2].push_back(new TH1F("","",13,0,104));//m_tt_3
        h_ssloose[2][3].push_back(new TH1F("","",15,0,300));//m_tt_4
        h_ssloose[2][4].push_back(new TH1F("","",9,0,108));//m_tt_5
        h_ssloose[2][5].push_back(new TH1F("","",9,0,108));//m_tt_6
        h_ssloose[2][6].push_back(new TH1F("","",15,0,300));//m_tt_7
    }
    
    //access pileup distributions in data/MC
    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");
    if (year=="2017"){
        LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        if (sample=="W1") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
        else if (sample=="W2") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5#MINIAODSIM", "pileup");
        else if (sample=="ST_t_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="W") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM", "pileup");
        else if (sample=="DY") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WW") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WplusHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="WZ") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="DY4") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ST_tW_top") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="WminusHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ST_tW_antitop") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM", "pileup");
        else if (sample=="W3") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="ZHTT") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="TTToSemiLeptonic")  LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
        else if (sample=="TTTo2L2Nu") LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root", "pua/#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM", "pileup");
    }
    if (year=="2016") LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");
    
    //OS-to-SS qcd correction files
    std::string closurefile = "closure_em_2016.root";
    if (year=="2017") closurefile = "closure_em_2017.root";
    if (year=="2018") closurefile = "closure_em_2018.root";
    TFile *fclosure = new TFile(closurefile.c_str(),"r");
    TH2F *correction = (TH2F*) fclosure->Get("correction");
    TH2F *closureOS = (TH2F*) fclosure->Get("closureOS");
    
    std::string osssfile = "osss_em_2016.root";
    if (year=="2017") osssfile = "osss_em_2017.root";
    if (year=="2018") osssfile = "osss_em_2018.root";
    TFile *fosss = new TFile(osssfile.c_str(),"r");
    TF1 *osss_0bjet = (TF1*) fosss->Get("OSSS_qcd_0bjet");
    TF1 *osss_bjet = (TF1*) fosss->Get("OSSS_qcd_bjet");
    TF1 *osss_0bjet_up = (TF1*) fosss->Get("OSSS_qcd_0bjet_up");
    TF1 *osss_bjet_up = (TF1*) fosss->Get("OSSS_qcd_bjet_up");
    TF1 *osss_0bjet_down = (TF1*) fosss->Get("OSSS_qcd_0bjet_down");
    TF1 *osss_bjet_down = (TF1*) fosss->Get("OSSS_qcd_bjet_down");
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for (int i = 0; i < n; i++){
        tree->GetEntry(i);
        if (i % 100 == 0) fprintf(stdout, "\r Processed events: %d of %d...", i, n);
        fflush(stdout);
        
        tree_NN->GetEntry(i);
        float p_N = 2.5;
        
        //MET filters
        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if ((year=="2017" or year=="2018") && Flag_ecalBadCalibReducedMINIAODFilter) continue;
        
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymu;
        mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepflavour_1,beta_deepflavour_1,bphi_deepflavour_1,bm_deepflavour_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepflavour_2,beta_deepflavour_2,bphi_deepflavour_2,bm_deepflavour_2);
        
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
        float Mu8E23_elept_thres = 24;
        float Mu8E23_mupt_thres = 13;
        float Mu23E12_elept_thres = 13;
        float Mu23E12_mupt_thres = 24;
        
        if (!isMu8E23 && !isMu23E12) continue;
        
        if (!(fabs(eta_1)<2.4 && fabs(eta_2)<2.4)) continue;
        //if (!(iso_1<0.10 && iso_2<0.15)) continue;//normal region
        if (!(iso_1<0.3 && iso_2<0.3)) continue;//loose region
        
        if (!(myele.DeltaR(mymu)>0.3)) continue;//both isolation cones have size 0.4, but at skimming level the other leptons are removed from the cones to remove overlapping
        
        if (name=="ZJ"){
            if (sample=="DY" or sample=="DY1" or sample=="DY2" or sample=="DY3" or sample=="DY4"){
                if (numGenJets==0){
                    weight = 3.630;
                    if (year=="2017") weight = 2.583;
                    if (year=="2016") weight = 1.509;
                }
                else if (numGenJets==1){
                    weight = 0.6304;
                    if (year=="2017") weight = 0.3269;
                    if (year=="2016") weight = 0.4814;
                }
                else if (numGenJets==2){
                    weight = 0.5528;
                    if (year=="2017") weight = 0.5667;
                    if (year=="2016") weight = 0.4987;
                }
                else if (numGenJets==3){
                    weight = 0.6009;
                    if (year=="2017") weight = 0.5228;
                    if (year=="2016") weight = 0.5113;
                }
                else if (numGenJets==4){
                    weight = 0.8314;
                    if (year=="2017") weight = 0.2199;
                    if (year=="2016") weight = 0.4194;
                }
            }
            if (sample=="DYlow" or sample=="DY1low" or sample=="DY2low" or sample=="DY3low" or sample=="DY4low"){
                if (year=="2016"){
                    if (numGenJets==0) weight = 20.64;
                    else if (numGenJets==1) weight = 0.7822;
                    else if (numGenJets==2) weight = 0.8491;
                    else if (numGenJets==3) weight = 0.8178;
                    else if (numGenJets==4) weight = 0.7536;
                }
                if (year=="2017") weight = 9.416;
                if (year=="2018") weight = 12.45;
            }
        }
        
        if (name=="WJ"){
            if (numGenJets==0){
                weight = 51.81;
                if (year=="2017") weight = 23.74;
                if (year=="2016") weight = 25.72;
            }
            else if (numGenJets==1){
                weight = 9.091;
                if (year=="2017") weight = 3.116;
                if (year=="2016") weight = 5.840;
            }
            else if (numGenJets==2){
                weight = 4.516;
                if (year=="2017") weight = 3.024;
                if (year=="2016") weight = 1.814;
            }
            else if (numGenJets==3){
                weight = 3.090;
                if (year=="2017") weight = 1.355;
                if (year=="2016") weight = 0.6878;
            }
            else if (numGenJets==4){
                weight = 3.227;
                if (year=="2017") weight = 1.119;
                if (year=="2016") weight = 0.7453;
            }
        }
        
        float sf_MC = 1.0;
        float topfactor = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            //e,mu ID/iso/tracking scale factors
            sf_MC *= e_trk_ratio * e_idiso_ic_ratio * m_trk_ratio * m_idiso_ic_ratio;
            
            //re-weigh Z pT spectrum for DY samples
            if (name=="ZJ"){
                sf_MC *= zptmass_weight_nom;
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (name=="ttbar"){
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
        
        float weight_corr = weight * sf_MC * sf_embed;
        
        //count btagged jets (deepflavour)
        int nbtag20 = 0;
        float bMpt_1 = 0;
        float bMflavor_1 = 0;
        float bMpt_2 = 0;
        float bMflavor_2 = 0;
        float bscore_thres = 0.2770;
        if (year=="2017") bscore_thres = 0.3033;
        if (year=="2016") bscore_thres = 0.3093;
        if (bpt_deepflavour_1>20 && bscore_deepflavour_1>bscore_thres && fabs(beta_deepflavour_1)<2.4){
            bMpt_1 = bpt_deepflavour_1;
            bMflavor_1 = bflavour_deepflavour_1;
            nbtag20++;
        }
        if (bpt_deepflavour_2>20 && bscore_deepflavour_2>bscore_thres && fabs(beta_deepflavour_2)<2.4){
            bMpt_2 = bpt_deepflavour_2;
            bMflavor_2 = bflavour_deepflavour_2;
            nbtag20++;
        }
        //btag weights for MC only
        float weight_btag_1b = 1.0;
        float weight_btag_2b = 1.0;
        if (sample!="data_obs" && sample!="embedded"){
            weight_btag_1b = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, 0);
            weight_btag_2b = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, 0)*GetbtagSF(stoi(year.c_str()), bMpt_2, bMflavor_2, 0);
        }
        if (nbtag20==1) weight_corr *= weight_btag_1b;
        if (nbtag20==2) weight_corr *= weight_btag_2b;
        
        //######################btag sf shifts#######################
        std::vector<float> btagsf_syst;
        for (int j = 0; j < 4; j++){
            btagsf_syst.push_back(1.0);
            if (sample!="data_obs" && sample!="embedded" && nbtag20==1) btagsf_syst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, j+1)/weight_btag_1b;
            if (sample!="data_obs" && sample!="embedded" && nbtag20==2) btagsf_syst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, j+1)*GetbtagSF(stoi(year.c_str()), bMpt_2, bMflavor_2, j+1)/weight_btag_2b;
        }
        
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
        
        std::vector<std::vector<std::vector<float>>> var;
        for (int j = 0; j < 2; j++) var.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < 7; j++) var[0].push_back(std::vector<float>());
        for (int j = 0; j < 8; j++) var[1].push_back(std::vector<float>());
        for (int j = 0; j < 49; j++){//i=0 nominal, 1-4 eleES, 5-10 muES, 11-34 jet, 35-46 recoil, 47-48 UES
            //1 bjet
            var[0][0].push_back(NN1b);
            var[0][1].push_back(p_n(NN1b,p_N));
            var[0][2].push_back(p_n(NN1b,p_N));
            var[0][3].push_back(pt_1);
            var[0][4].push_back(pt_2);
            var[0][5].push_back(m_sv);
            var[0][6].push_back(m_btt);
            //2 bjets
            var[1][0].push_back(NN2b);
            var[1][1].push_back(p_n(NN2b,p_N));
            var[1][2].push_back(p_n(NN2b,p_N));
            var[1][3].push_back(pt_1);
            var[1][4].push_back(pt_2);
            var[1][5].push_back(m_sv);
            var[1][6].push_back(m_btt);
            var[1][7].push_back(m_bbtt);
        }
        
        //#####################electron ES shifting##############################
        std::vector<TLorentzVector> myshiftedele;
        std::vector<TLorentzVector> mymet_shiftedele;
        std::vector<TLorentzVector> mytt_shiftedele;
        std::vector<float> m_btt_shiftedele;
        std::vector<float> m_bbtt_shiftedele;
        for (int j = 0; j < 4; j++){
            myshiftedele.push_back(myele);
            mymet_shiftedele.push_back(mymet);
            mytt_shiftedele.push_back(mytt);
            m_btt_shiftedele.push_back(m_btt);
            m_bbtt_shiftedele.push_back(m_bbtt);
        }
        float eleESetabins[3] = {0,1.479,2.4};
        float eleES[4] = {1.005,0.995,1.0125,0.9875};//ordering: barrel up/down, endcap up/down (for emb only)
        for (int j = 0; j < 2; j++){
            if (fabs(eta_1)>eleESetabins[j] && fabs(eta_1)<eleESetabins[j+1]){//don't need to check gen match, can shift anything that is reco ele
                //myele
                if (sample=="embedded"){
                    myshiftedele[2*j] *= eleES[2*j];
                    myshiftedele[2*j+1] *= eleES[2*j+1];
                }
                else {
                    myshiftedele[2*j].SetPtEtaPhiM(pt_1_ScaleUp,eta_1,phi_1,m_1);
                    myshiftedele[2*j+1].SetPtEtaPhiM(pt_1_ScaleDown,eta_1,phi_1,m_1);
                }
                //mymet
                mymet_shiftedele[2*j] = mymet + myele - myshiftedele[2*j];
                mymet_shiftedele[2*j+1] = mymet + myele - myshiftedele[2*j+1];;
                //mytt
                mytt_shiftedele[2*j].SetPtEtaPhiM((myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Pt(),(myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Eta(),(myshiftedele[2*j]+mymu+mymet_shiftedele[2*j]).Phi(),m_sv_elescaleESUp);
                mytt_shiftedele[2*j+1].SetPtEtaPhiM((myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Pt(),(myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Eta(),(myshiftedele[2*j+1]+mymu+mymet_shiftedele[2*j+1]).Phi(),m_sv_elescaleESDown);
                
                m_btt_shiftedele[2*j] = (mytt_shiftedele[2*j]+myb1).M();
                m_btt_shiftedele[2*j+1] = (mytt_shiftedele[2*j+1]+myb1).M();
                
                m_bbtt_shiftedele[2*j] = (mytt_shiftedele[2*j]+myb1+myb2).M();
                m_bbtt_shiftedele[2*j+1] = (mytt_shiftedele[2*j+1]+myb1+myb2).M();
            }
        }
        float NN1b_eleES[4] = {NN1b_ESCALEUP,NN1b_ESCALEDOWN,NN1b_ESCALEUP,NN1b_ESCALEDOWN};
        float NN2b_eleES[4] = {NN2b_ESCALEUP,NN2b_ESCALEDOWN,NN2b_ESCALEUP,NN2b_ESCALEDOWN};
        for (int j = 0; j < 4; j++){
            var[0][0][j+1] = NN1b_eleES[j];
            var[0][1][j+1] = p_n(NN1b_eleES[j],p_N);
            var[0][2][j+1] = p_n(NN1b_eleES[j],p_N);
            var[0][3][j+1] = myshiftedele[j].Pt();
            var[0][5][j+1] = mytt_shiftedele[j].M();
            var[0][6][j+1] = m_btt_shiftedele[j];
            
            var[1][0][j+1] = NN2b_eleES[j];
            var[1][1][j+1] = p_n(NN2b_eleES[j],p_N);
            var[1][2][j+1] = p_n(NN2b_eleES[j],p_N);
            var[1][3][j+1] = myshiftedele[j].Pt();
            var[1][5][j+1] = mytt_shiftedele[j].M();
            var[1][6][j+1] = m_btt_shiftedele[j];
            var[1][7][j+1] = m_bbtt_shiftedele[j];
        }
        
        //#####################muon ES shifting##############################
        std::vector<TLorentzVector> myshiftedmu;
        std::vector<TLorentzVector> mymet_shiftedmu;
        std::vector<TLorentzVector> mytt_shiftedmu;
        std::vector<float> m_btt_shiftedmu;
        std::vector<float> m_bbtt_shiftedmu;
        for (int j = 0; j < 6; j++){
            myshiftedmu.push_back(mymu);
            mymet_shiftedmu.push_back(mymet);
            mytt_shiftedmu.push_back(mytt);
            m_btt_shiftedmu.push_back(m_btt);
            m_bbtt_shiftedmu.push_back(m_bbtt);
        }
        float muonESetabins[4] = {0,1.2,2.1,2.4};
        float muonES[6] = {1.004,0.996,1.009,0.991,1.027,0.973};//ordering: eta1.2updown, 1.2eta2.1updown, 2.1eta2.4updown; same for both MC and emb
        for (int j = 0; j < 3; j++){
            if ((gen_match_2==2 or gen_match_2==4) && fabs(eta_2)>muonESetabins[j] && fabs(eta_2)<muonESetabins[j+1]){
                //mymu
                myshiftedmu[2*j] *= muonES[2*j];
                myshiftedmu[2*j+1] *= muonES[2*j+1];
                //mymet
                mymet_shiftedmu[2*j] = mymet + mymu - myshiftedmu[2*j];
                mymet_shiftedmu[2*j+1] = mymet + mymu - myshiftedmu[2*j+1];;
                //mytt
                mytt_shiftedmu[2*j].SetPtEtaPhiM((myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Pt(),(myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Eta(),(myele+myshiftedmu[2*j]+mymet_shiftedmu[2*j]).Phi(),m_sv_muonESUp);
                mytt_shiftedmu[2*j+1].SetPtEtaPhiM((myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Pt(),(myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Eta(),(myele+myshiftedmu[2*j+1]+mymet_shiftedmu[2*j+1]).Phi(),m_sv_muonESDown);
                
                m_btt_shiftedmu[2*j] = (mytt_shiftedmu[2*j]+myb1).M();
                m_btt_shiftedmu[2*j+1] = (mytt_shiftedmu[2*j+1]+myb1).M();
                
                m_bbtt_shiftedmu[2*j] = (mytt_shiftedmu[2*j]+myb1+myb2).M();
                m_bbtt_shiftedmu[2*j+1] = (mytt_shiftedmu[2*j+1]+myb1+myb2).M();
            }
        }
        float NN1b_muES[6] = {NN1b_muonESUp,NN1b_muonESDown,NN1b_muonESUp,NN1b_muonESDown,NN1b_muonESUp,NN1b_muonESDown};
        float NN2b_muES[6] = {NN2b_muonESUp,NN2b_muonESDown,NN2b_muonESUp,NN2b_muonESDown,NN2b_muonESUp,NN2b_muonESDown};
        for (int j = 0; j < 6; j++){
            var[0][0][j+5] = NN1b_muES[j];
            var[0][1][j+5] = p_n(NN1b_muES[j],p_N);
            var[0][2][j+5] = p_n(NN1b_muES[j],p_N);
            var[0][4][j+5] = myshiftedmu[j].Pt();
            var[0][5][j+5] = mytt_shiftedmu[j].M();
            var[0][6][j+5] = m_btt_shiftedmu[j];
            
            var[1][0][j+5] = NN2b_muES[j];
            var[1][1][j+5] = p_n(NN2b_muES[j],p_N);
            var[1][2][j+5] = p_n(NN2b_muES[j],p_N);
            var[1][4][j+5] = myshiftedmu[j].Pt();
            var[1][5][j+5] = mytt_shiftedmu[j].M();
            var[1][6][j+5] = m_btt_shiftedmu[j];
            var[1][7][j+5] = m_bbtt_shiftedmu[j];
        }
        
        //#######################jet uncertainties shifting########################
        float met_jetvar[24] = {met_JetAbsoluteUp,met_JetAbsoluteDown,met_JetAbsoluteyearUp,met_JetAbsoluteyearDown,met_JetBBEC1Up,met_JetBBEC1Down,met_JetBBEC1yearUp,met_JetBBEC1yearDown,met_JetEC2Up,met_JetEC2Down,met_JetEC2yearUp,met_JetEC2yearDown,met_JetFlavorQCDUp,met_JetFlavorQCDDown,met_JetHFUp,met_JetHFDown,met_JetHFyearUp,met_JetHFyearDown,met_JetRelativeBalUp,met_JetRelativeBalDown,met_JetRelativeSampleUp,met_JetRelativeSampleDown,met_JERUp,met_JERDown};
        float metphi_jetvar[24] = {metphi_JetAbsoluteUp,metphi_JetAbsoluteDown,metphi_JetAbsoluteyearUp,metphi_JetAbsoluteyearDown,metphi_JetBBEC1Up,metphi_JetBBEC1Down,metphi_JetBBEC1yearUp,metphi_JetBBEC1yearDown,metphi_JetEC2Up,metphi_JetEC2Down,metphi_JetEC2yearUp,metphi_JetEC2yearDown,metphi_JetFlavorQCDUp,metphi_JetFlavorQCDDown,metphi_JetHFUp,metphi_JetHFDown,metphi_JetHFyearUp,metphi_JetHFyearDown,metphi_JetRelativeBalUp,metphi_JetRelativeBalDown,metphi_JetRelativeSampleUp,metphi_JetRelativeSampleDown,metphi_JERUp,metphi_JERDown};
        float m_sv_jetvar[24] = {m_sv_JetAbsoluteUp,m_sv_JetAbsoluteDown,m_sv_JetAbsoluteyearUp,m_sv_JetAbsoluteyearDown,m_sv_JetBBEC1Up,m_sv_JetBBEC1Down,m_sv_JetBBEC1yearUp,m_sv_JetBBEC1yearDown,m_sv_JetEC2Up,m_sv_JetEC2Down,m_sv_JetEC2yearUp,m_sv_JetEC2yearDown,m_sv_JetFlavorQCDUp,m_sv_JetFlavorQCDDown,m_sv_JetHFUp,m_sv_JetHFDown,m_sv_JetHFyearUp,m_sv_JetHFyearDown,m_sv_JetRelativeBalUp,m_sv_JetRelativeBalDown,m_sv_JetRelativeSampleUp,m_sv_JetRelativeSampleDown,m_sv_JERUp,m_sv_JERDown};
        float bpt_1_jetvar[24] = {bpt_deepflavour_JetAbsoluteUp_1,bpt_deepflavour_JetAbsoluteDown_1,bpt_deepflavour_JetAbsoluteyearUp_1,bpt_deepflavour_JetAbsoluteyearDown_1,bpt_deepflavour_JetBBEC1Up_1,bpt_deepflavour_JetBBEC1Down_1,bpt_deepflavour_JetBBEC1yearUp_1,bpt_deepflavour_JetBBEC1yearDown_1,bpt_deepflavour_JetEC2Up_1,bpt_deepflavour_JetEC2Down_1,bpt_deepflavour_JetEC2yearUp_1,bpt_deepflavour_JetEC2yearDown_1,bpt_deepflavour_JetFlavorQCDUp_1,bpt_deepflavour_JetFlavorQCDDown_1,bpt_deepflavour_JetHFUp_1,bpt_deepflavour_JetHFDown_1,bpt_deepflavour_JetHFyearUp_1,bpt_deepflavour_JetHFyearDown_1,bpt_deepflavour_JetRelativeBalUp_1,bpt_deepflavour_JetRelativeBalDown_1,bpt_deepflavour_JetRelativeSampleUp_1,bpt_deepflavour_JetRelativeSampleDown_1,bpt_deepflavour_JERUp_1,bpt_deepflavour_JERDown_1};
        float bpt_2_jetvar[24] = {bpt_deepflavour_JetAbsoluteUp_2,bpt_deepflavour_JetAbsoluteDown_2,bpt_deepflavour_JetAbsoluteyearUp_2,bpt_deepflavour_JetAbsoluteyearDown_2,bpt_deepflavour_JetBBEC1Up_2,bpt_deepflavour_JetBBEC1Down_2,bpt_deepflavour_JetBBEC1yearUp_2,bpt_deepflavour_JetBBEC1yearDown_2,bpt_deepflavour_JetEC2Up_2,bpt_deepflavour_JetEC2Down_2,bpt_deepflavour_JetEC2yearUp_2,bpt_deepflavour_JetEC2yearDown_2,bpt_deepflavour_JetFlavorQCDUp_2,bpt_deepflavour_JetFlavorQCDDown_2,bpt_deepflavour_JetHFUp_2,bpt_deepflavour_JetHFDown_2,bpt_deepflavour_JetHFyearUp_2,bpt_deepflavour_JetHFyearDown_2,bpt_deepflavour_JetRelativeBalUp_2,bpt_deepflavour_JetRelativeBalDown_2,bpt_deepflavour_JetRelativeSampleUp_2,bpt_deepflavour_JetRelativeSampleDown_2,bpt_deepflavour_JERUp_2,bpt_deepflavour_JERDown_2};
        float NN1b_jetvar[24] = {NN1b_JetAbsoluteUp,NN1b_JetAbsoluteDown,NN1b_JetAbsoluteyearUp,NN1b_JetAbsoluteyearDown,NN1b_JetBBEC1Up,NN1b_JetBBEC1Down,NN1b_JetBBEC1yearUp,NN1b_JetBBEC1yearDown,NN1b_JetEC2Up,NN1b_JetEC2Down,NN1b_JetEC2yearUp,NN1b_JetEC2yearDown,NN1b_JetFlavorQCDUp,NN1b_JetFlavorQCDDown,NN1b_JetHFUp,NN1b_JetHFDown,NN1b_JetHFyearUp,NN1b_JetHFyearDown,NN1b_JetRelativeBalUp,NN1b_JetRelativeBalDown,NN1b_JetRelativeSampleUp,NN1b_JetRelativeSampleDown,NN1b_JERUp,NN1b_JERDown};
        float NN2b_jetvar[24] = {NN2b_JetAbsoluteUp,NN2b_JetAbsoluteDown,NN2b_JetAbsoluteyearUp,NN2b_JetAbsoluteyearDown,NN2b_JetBBEC1Up,NN2b_JetBBEC1Down,NN2b_JetBBEC1yearUp,NN2b_JetBBEC1yearDown,NN2b_JetEC2Up,NN2b_JetEC2Down,NN2b_JetEC2yearUp,NN2b_JetEC2yearDown,NN2b_JetFlavorQCDUp,NN2b_JetFlavorQCDDown,NN2b_JetHFUp,NN2b_JetHFDown,NN2b_JetHFyearUp,NN2b_JetHFyearDown,NN2b_JetRelativeBalUp,NN2b_JetRelativeBalDown,NN2b_JetRelativeSampleUp,NN2b_JetRelativeSampleDown,NN2b_JERUp,NN2b_JERDown};
        std::vector<TLorentzVector> mymet_jet;
        std::vector<TLorentzVector> mytt_jet;
        std::vector<TLorentzVector> myb1_jet;
        std::vector<TLorentzVector> myb2_jet;
        std::vector<float> m_btt_jet;
        std::vector<float> m_bbtt_jet;
        for (int j = 0; j < 24; j++){
            mymet_jet.push_back(mymet);
            mytt_jet.push_back(mytt);
            myb1_jet.push_back(myb1);
            myb2_jet.push_back(myb2);
            mymet_jet[j].SetPtEtaPhiM(met_jetvar[j],0,metphi_jetvar[j],0);
            mytt_jet[j].SetPtEtaPhiM((myele+mymu+mymet_jet[j]).Pt(),(myele+mymu+mymet_jet[j]).Eta(),(myele+mymu+mymet_jet[j]).Phi(),m_sv_jetvar[j]);
            myb1_jet[j].SetPtEtaPhiM(bpt_1_jetvar[j],beta_deepflavour_1,bphi_deepflavour_1,bm_deepflavour_1);
            myb2_jet[j].SetPtEtaPhiM(bpt_2_jetvar[j],beta_deepflavour_2,bphi_deepflavour_2,bm_deepflavour_2);
            m_btt_jet.push_back((mytt_jet[j]+myb1_jet[j]).M());
            m_bbtt_jet.push_back((mytt_jet[j]+myb1_jet[j]+myb2_jet[j]).M());
        }
        for (int j = 0; j < 24; j++){
            var[0][0][j+11] = NN1b_jetvar[j];
            var[0][1][j+11] = p_n(NN1b_jetvar[j],p_N);
            var[0][2][j+11] = p_n(NN1b_jetvar[j],p_N);
            var[0][5][j+11] = mytt_jet[j].M();
            var[0][6][j+11] = m_btt_jet[j];
            
            var[1][0][j+11] = NN2b_jetvar[j];
            var[1][1][j+11] = p_n(NN2b_jetvar[j],p_N);
            var[1][2][j+11] = p_n(NN2b_jetvar[j],p_N);
            var[1][5][j+11] = mytt_jet[j].M();
            var[1][6][j+11] = m_btt_jet[j];
            var[1][7][j+11] = m_bbtt_jet[j];
        }
        
        //re-count nbtag20 and re-compute btag sf with shifted jet ES
        std::vector<int> nbtag20_jetsyst;
        std::vector<float> bMpt_1_jetsyst;
        std::vector<float> bMflavour_1_jetsyst;
        std::vector<float> bMpt_2_jetsyst;
        std::vector<float> bMflavour_2_jetsyst;
        std::vector<float> weight_btag_jetsyst;
        for (int j = 0; j < 24; j++){
            nbtag20_jetsyst.push_back(0);
            bMpt_1_jetsyst.push_back(0);
            bMflavour_1_jetsyst.push_back(0);
            bMpt_2_jetsyst.push_back(0);
            bMflavour_2_jetsyst.push_back(0);
            if (bpt_1_jetvar[j]>20 && bscore_deepflavour_1>bscore_thres && fabs(beta_deepflavour_1)<2.4){
                bMpt_1_jetsyst[j] = bpt_1_jetvar[j];
                bMflavour_1_jetsyst[j] = bflavour_deepflavour_1;
                nbtag20_jetsyst[j]++;
            }
            if (bpt_2_jetvar[j]>20 && bscore_deepflavour_2>bscore_thres && fabs(beta_deepflavour_2)<2.4){
                bMpt_2_jetsyst[j] = bpt_2_jetvar[j];
                bMflavour_2_jetsyst[j] = bflavour_deepflavour_2;
                nbtag20_jetsyst[j]++;
            }
            weight_btag_jetsyst.push_back(1);
            if (sample!="data_obs" && sample!="embedded"){
                if (nbtag20==1){
                    if (nbtag20_jetsyst[j]==1) weight_btag_jetsyst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1_jetsyst[j], bMflavour_1_jetsyst[j], 0)/weight_btag_1b;
                    if (nbtag20_jetsyst[j]==2) weight_btag_jetsyst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1_jetsyst[j], bMflavour_1_jetsyst[j], 0)*GetbtagSF(stoi(year.c_str()), bMpt_2_jetsyst[j], bMflavour_2_jetsyst[j], 0)/weight_btag_1b;
                }
                if (nbtag20==2){
                    if (nbtag20_jetsyst[j]==1) weight_btag_jetsyst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1_jetsyst[j], bMflavour_1_jetsyst[j], 0)/weight_btag_2b;
                    if (nbtag20_jetsyst[j]==2) weight_btag_jetsyst[j] = GetbtagSF(stoi(year.c_str()), bMpt_1_jetsyst[j], bMflavour_1_jetsyst[j], 0)*GetbtagSF(stoi(year.c_str()), bMpt_2_jetsyst[j], bMflavour_2_jetsyst[j], 0)/weight_btag_2b;
                }
            }
        }
        
        //#######################recoil uncertainties########################
        float met_recoilvar[4] = {met_resolutionUp,met_resolutionDown,met_responseUp,met_responseDown};
        float metphi_recoilvar[4] = {metphi_resolutionUp,metphi_resolutionDown,metphi_responseUp,metphi_responseDown};
        float m_sv_recoilvar[4] = {m_sv_ResolutionUp,m_sv_ResolutionDown,m_sv_ResponseUp,m_sv_ResponseDown};
        float NN1b_recoilvar[4] = {NN1b_ResolutionUp,NN1b_ResolutionDown,NN1b_ResponseUp,NN1b_ResponseDown};
        float NN2b_recoilvar[4] = {NN2b_ResolutionUp,NN2b_ResolutionDown,NN2b_ResponseUp,NN2b_ResponseDown};
        std::vector<TLorentzVector> mymet_recoil;
        std::vector<TLorentzVector> mytt_recoil;
        std::vector<float> m_btt_recoil;
        std::vector<float> m_bbtt_recoil;
        for (int j = 0; j < 12; j++){//ordered by: 0jet resolutionUp/Down, responseUp/Down, 1jet resolutionUp/Down, responseUp/Down, 2jetsmore resolutionUp/Down, responseUp/Down
            mymet_recoil.push_back(mymet);
            mytt_recoil.push_back(mytt);
            m_btt_recoil.push_back(m_btt);
            m_bbtt_recoil.push_back(m_bbtt);
        }
        float njetsbins[4] = {0,1,2,10};
        for (int j = 0; j < 3; j++){
            if (njets>=njetsbins[j] && njets<njetsbins[j+1]){
                for (int k = 0; k < 4; k++){
                    mymet_recoil[4*j+k].SetPtEtaPhiM(met_recoilvar[k],0,metphi_recoilvar[k],0);
                    mytt_recoil[4*j+k].SetPtEtaPhiM((myele+mymu+mymet_recoil[4*j+k]).Pt(),(myele+mymu+mymet_recoil[4*j+k]).Eta(),(myele+mymu+mymet_recoil[4*j+k]).Phi(),m_sv_recoilvar[k]);
                    m_btt_recoil[4*j+k] = (mytt_recoil[4*j+k]+myb1).M();
                    m_bbtt_recoil[4*j+k] = (mytt_recoil[4*j+k]+myb1+myb2).M();
                }
            }
        }
        for (int j = 0; j < 12; j++){
            var[0][0][j+35] = NN1b_recoilvar[j];
            var[0][1][j+35] = p_n(NN1b_recoilvar[j],p_N);
            var[0][2][j+35] = p_n(NN1b_recoilvar[j],p_N);
            var[0][5][j+35] = mytt_recoil[j].M();
            var[0][6][j+35] = m_btt_recoil[j];
            
            var[1][0][j+35] = NN2b_recoilvar[j];
            var[1][1][j+35] = p_n(NN2b_recoilvar[j],p_N);
            var[1][2][j+35] = p_n(NN2b_recoilvar[j],p_N);
            var[1][5][j+35] = mytt_recoil[j].M();
            var[1][6][j+35] = m_btt_recoil[j];
            var[1][7][j+35] = m_bbtt_recoil[j];
        }
        
        //#######################met unclustered ES########################
        float met_UESvar[2] = {met_UESUp,met_UESDown};
        float metphi_UESvar[2] = {metphi_UESUp,metphi_UESDown};
        float m_sv_UESvar[2] = {m_sv_UESUp,m_sv_UESDown};
        float NN1b_UESvar[2] = {NN1b_UESUp,NN1b_UESDown};
        float NN2b_UESvar[2] = {NN2b_UESUp,NN2b_UESDown};
        std::vector<TLorentzVector> mymet_UES;
        std::vector<TLorentzVector> mytt_UES;
        std::vector<float> m_btt_UES;
        std::vector<float> m_bbtt_UES;
        for (int j = 0; j < 2; j++){//ordered by: UES Up/Down
            mymet_UES.push_back(mymet);
            mytt_UES.push_back(mytt);
            m_btt_UES.push_back(m_btt);
            m_bbtt_UES.push_back(m_bbtt);
            
            mymet_UES[j].SetPtEtaPhiM(met_UESvar[j],0,metphi_UESvar[j],0);
            mytt_UES[j].SetPtEtaPhiM((myele+mymu+mymet_UES[j]).Pt(),(myele+mymu+mymet_UES[j]).Eta(),(myele+mymu+mymet_UES[j]).Phi(),m_sv_UESvar[j]);
            m_btt_UES[j] = (mytt_UES[j]+myb1).M();
            m_bbtt_UES[j] = (mytt_UES[j]+myb1+myb2).M();
        }
        for (int j = 0; j < 2; j++){
            var[0][0][j+47] = NN1b_UESvar[j];
            var[0][1][j+47] = p_n(NN1b_UESvar[j],p_N);
            var[0][2][j+47] = p_n(NN1b_UESvar[j],p_N);
            var[0][5][j+47] = mytt_UES[j].M();
            var[0][6][j+47] = m_btt_UES[j];
            
            var[1][0][j+47] = NN2b_UESvar[j];
            var[1][1][j+47] = p_n(NN2b_UESvar[j],p_N);
            var[1][2][j+47] = p_n(NN2b_UESvar[j],p_N);
            var[1][5][j+47] = mytt_UES[j].M();
            var[1][6][j+47] = m_btt_UES[j];
            var[1][7][j+47] = m_bbtt_UES[j];
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
        }
        
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
        if (name=="ZJ"){//+/-10% of correction i.e. 1.5 -> 1.55/1.45
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
        if (name=="ttbar"){//apply twice for up and not at all for down
            topfactor_shifting[0] = topfactor;
            topfactor_shifting[1] = 1/topfactor;
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
        
        //############################prefiring weight (only for 2016-17 not 2018)################################
        float prefiring[2] = {1.0,1.0};
        if ((year=="2016" or year=="2017") && sample!="data_obs" && sample!="embedded"){
            weight_corr *= prefiring_weight;
            prefiring[0] = prefiring_weight_up/prefiring_weight;
            prefiring[1] = prefiring_weight_down/prefiring_weight;
        }
        /*
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~cut-based selection criteria
        std::vector<bool> mtt_region;
        for (int j = 0; j < 5; j++) mtt_region.push_back(0);
        mtt_region[0] = nbtag20==1 && m_btt<80 && mt_tau1<50 && mt_tau2<50;
        mtt_region[1] = nbtag20==1 && m_btt>80 && m_btt<95 && mt_tau1<50 && mt_tau2<50;
        mtt_region[2] = nbtag20==1 && m_btt>95 && mt_tau1<50 && mt_tau2<50;
        mtt_region[3] = nbtag20==2 && m_bbtt<150 && mt_tau1<50 && mt_tau2<50;
        mtt_region[4] = nbtag20==2 && m_bbtt>150 && mt_tau1<50 && mt_tau2<50;
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
        */
        
        //##############################categories definition##############################
        std::vector<std::vector<bool>> ctg;
        for (int j = 0; j < 7; j++) ctg.push_back(std::vector<bool>());//7 categories (4 for 1b, 3 for 2b)
        for (int j = 0; j < 49; j++){//61 shifted systematics
            //1b
            ctg[0].push_back(var[0][1][j]>0.99);
            ctg[1].push_back(var[0][1][j]<0.99 && var[0][1][j]>0.95);
            ctg[2].push_back(var[0][1][j]<0.95 && var[0][1][j]>0.85);
            ctg[3].push_back(var[0][1][j]<0.85);
            //2b
            ctg[4].push_back(var[1][1][j]>0.98);
            ctg[5].push_back(var[1][1][j]<0.98 && var[1][1][j]>0.93);
            ctg[6].push_back(var[1][1][j]<0.93);
        }
        
        //##############################histograms filling###################################
        bool rejectEMBduplicate = !isMCnonHiggs or (isMCnonHiggs && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6));
        
        bool iso_default = iso_1<0.10 && iso_2<0.15;
        bool iso_loose = iso_1>0.05 or iso_2>0.05;
        
        //nonDY MC contamination to embedded (all nonHiggs MC events with two taus previously rejected)
        if (isMCnonHiggs && name!="ZJ" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (q_1*q_2<0 && iso_default && trigger_region_nominal){
                if (nbtag20==1){
                    for (int m = 3; m < 7; m++){
                        h_os[0][m][63]->Fill(var[0][m][0],weight_corr*trgsf*0.1);//+/-10% on top of emb
                    }
                }
                if (nbtag20==2){
                    for (int m = 3; m < 8; m++){
                        h_os[1][m][63]->Fill(var[1][m][0],weight_corr*trgsf*0.1);//+/-10% on top of emb
                    }
                }
            }
        }
        /*
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
        if (isMCnonHiggs && name!="ZJ" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (q_1*q_2<0 && iso_default && trigger_region_nominal){
                for (int m = 0; m < 5; m++){
                    if (mtt_region[m]==1) h_os[2][m][63]->Fill(var[0][5][0],weight_corr*trgsf*0.1);
                }
            }
        }
        if (q_1*q_2<0 && iso_default && rejectEMBduplicate){
            for (int m = 0; m < 5; m++){
                if (mtt_region[m]==1){
                    if (trigger_region_nominal) h_os[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf);
                    if (sample!="data_obs"){
                        if (trigger_region_nominal){
                            for (int k = 0; k < 6; k++) h_os[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]);
                            if (sample!="embedded"){
                                for (int k = 0; k < 4; k++) h_os[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]);
                            }
                            if (isRecoilMC){
                                for (int k = 0; k < 12; k++) h_os[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf);
                            }
                            if (isnonRecoilMC){
                                for (int k = 0; k < 2; k++) h_os[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf);
                            }
                            if (name=="ZJ"){
                                for (int k = 0; k < 2; k++) h_os[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]);
                            }
                            if (name=="ttbar"){
                                for (int k = 0; k < 2; k++) h_os[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]);
                            }
                            if (year!="2018" && sample!="embedded"){
                                for (int k = 0; k < 2; k++) h_os[2][m][k+64]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]);
                            }
                        }
                        for (int k = 0; k < 24; k++){
                            if (trigger_region_nominal && sample!="embedded") h_os[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]);
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]) h_os[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]);
                        }
                        for (int k = 0; k < 6; k++){
                            if (trigger_region_shiftedmu[k]) h_os[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]);
                        }
                    }
                }
            }
        }
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
         */
        
        //do not fill for MC tautau events (duplicating emb) as normal
        if (q_1*q_2<0 && iso_default && rejectEMBduplicate){
            //loop over variables to fill ###############1b################
            for (int m = 0; m < 7; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) h_os[0][m][0]->Fill(var[0][m][0],weight_corr*trgsf);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++) h_os[0][m][k+11]->Fill(var[0][m][0],weight_corr*trgsf*trigger_shiftedsf[k]);
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++) h_os[0][m][k+17]->Fill(var[0][m][0],weight_corr*trgsf*btagsf_syst[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_os[0][m][k+45]->Fill(var[0][m][k+35],weight_corr*trgsf);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_os[0][m][k+57]->Fill(var[0][m][k+47],weight_corr*trgsf);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_os[0][m][k+59]->Fill(var[0][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_os[0][m][k+61]->Fill(var[0][m][0],weight_corr*trgsf*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_os[0][m][k+64]->Fill(var[0][m][0],weight_corr*trgsf*prefiring[k]);
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") h_os[0][m][k+21]->Fill(var[0][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) h_os[0][m][k+1]->Fill(var[0][m][k+1],weight_corr*trgsf_shiftedele[k]);
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==1 && trigger_region_shiftedmu[k]) h_os[0][m][k+5]->Fill(var[0][m][k+5],weight_corr*trgsf_shiftedmu[k]);
                    }
                }//end of sample!="data_obs"
            }//end of loop of variables to fill ###############1b################
            
            //loop over variables to fill ###############2b################
            for (int m = 0; m < 8; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) h_os[1][m][0]->Fill(var[1][m][0],weight_corr*trgsf);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++) h_os[1][m][k+11]->Fill(var[1][m][0],weight_corr*trgsf*trigger_shiftedsf[k]);
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++) h_os[1][m][k+17]->Fill(var[1][m][0],weight_corr*trgsf*btagsf_syst[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_os[1][m][k+45]->Fill(var[1][m][k+35],weight_corr*trgsf);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_os[1][m][k+57]->Fill(var[1][m][k+47],weight_corr*trgsf);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_os[1][m][k+59]->Fill(var[1][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_os[1][m][k+61]->Fill(var[1][m][0],weight_corr*trgsf*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_os[1][m][k+64]->Fill(var[1][m][0],weight_corr*trgsf*prefiring[k]);
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") h_os[1][m][k+21]->Fill(var[1][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) h_os[1][m][k+1]->Fill(var[1][m][k+1],weight_corr*trgsf_shiftedele[k]);
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==2 && trigger_region_shiftedmu[k]) h_os[1][m][k+5]->Fill(var[1][m][k+5],weight_corr*trgsf_shiftedmu[k]);
                    }
                }//end of sample!="data_obs"
            }//end of loop of variables to fill ###############2b################
            
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>fill final m_tt categories
            //~~~~~~~~~~~~~~~~~~~1bNN
            for (int m = 0; m < 4; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) if (ctg[m][0]) h_os[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++) if (ctg[m][0]) h_os[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]);
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++) if (ctg[m][0]) h_os[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+35]) h_os[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+47]) h_os[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+64]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]);
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+11]) h_os[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) if (ctg[m][k+1]) h_os[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]);
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==1 && trigger_region_shiftedmu[k]) if (ctg[m][k+5]) h_os[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]);
                    }
                }//end of sample!="data_obs"
            }//~~~~~~~~~~~~~~~~~~~1bNN
            
            //~~~~~~~~~~~~~~~~~~~2bNN
            for (int m = 4; m < 7; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) if (ctg[m][0]) h_os[2][m][0]->Fill(var[1][5][0],weight_corr*trgsf);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++) if (ctg[m][0]) h_os[2][m][k+11]->Fill(var[1][5][0],weight_corr*trgsf*trigger_shiftedsf[k]);
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++) if (ctg[m][0]) h_os[2][m][k+17]->Fill(var[1][5][0],weight_corr*trgsf*btagsf_syst[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+35]) h_os[2][m][k+45]->Fill(var[1][5][k+35],weight_corr*trgsf);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+47]) h_os[2][m][k+57]->Fill(var[1][5][k+47],weight_corr*trgsf);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+59]->Fill(var[1][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+61]->Fill(var[1][5][0],weight_corr*trgsf*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_os[2][m][k+64]->Fill(var[1][5][0],weight_corr*trgsf*prefiring[k]);
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+11]) h_os[2][m][k+21]->Fill(var[1][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) if (ctg[m][k+1]) h_os[2][m][k+1]->Fill(var[1][5][k+1],weight_corr*trgsf_shiftedele[k]);
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==2 && trigger_region_shiftedmu[k]) if (ctg[m][k+5]) h_os[2][m][k+5]->Fill(var[1][5][k+5],weight_corr*trgsf_shiftedmu[k]);
                    }
                }//end of sample!="data_obs"
            }//~~~~~~~~~~~~~~~~~~~2bNN
            
            //><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>end of fill final m_tt categories
            
        }//end of opposite-sign region, nominal e/mu iso
        
        //same-sign region
        if (!isSignal && rejectEMBduplicate && q_1*q_2>0){
            //SS weight
            float osss_weight = 1.0;
            float correction_weight = 1.0;
            float closure_weight = 1.0;
            
            float DR = myele.DeltaR(mymu);
            if (DR>4.9) DR = 4.9;
            
            osss_weight = osss_bjet->Eval(DR);
            
            //correction/closure with nominal electron/muon ES
            float ept = pt_1;
            float mupt = pt_2;
            if (ept>60) ept = 59;
            if (mupt>60) mupt = 59;
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
                if (ept_shiftedele[j]>60) ept_shiftedele[j] = 59;
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
                if (mupt_shiftedmu[j]>60) mupt_shiftedmu[j] = 59;
                correction_weight_shiftedmu.push_back(correction->GetBinContent(correction->GetXaxis()->FindBin(mupt_shiftedmu[j]),correction->GetYaxis()->FindBin(ept)));
                closure_weight_shiftedmu.push_back(closureOS->GetBinContent(closureOS->GetXaxis()->FindBin(mupt_shiftedmu[j]),closureOS->GetYaxis()->FindBin(ept)));
                ssweight_shiftedmu.push_back(osss_weight*correction_weight_shiftedmu[j]*closure_weight_shiftedmu[j]);
            }
            
            //ss weight with shifted osss/correction/closure
            std::vector<float> ssweight_shifted;
            for (int j = 0; j < 8; j++){
                ssweight_shifted.push_back(1.0);
            }//ordered by: [0,1]:correction up/down [2,3]closure up/down [4,5]both up/down, [6,7]osss up/down
            ssweight_shifted[0] *= osss_weight * correction_weight * correction_weight * closure_weight;
            ssweight_shifted[1] *= osss_weight * closure_weight;
            ssweight_shifted[2] *= osss_weight * correction_weight * closure_weight * closure_weight;
            ssweight_shifted[3] *= osss_weight * correction_weight;
            ssweight_shifted[4] *= osss_weight * correction_weight * correction_weight * closure_weight * closure_weight;
            ssweight_shifted[5] *= osss_weight;
            ssweight_shifted[6] *= osss_bjet_up->Eval(DR) * correction_weight * closure_weight;
            ssweight_shifted[7] *= osss_bjet_down->Eval(DR) * correction_weight * closure_weight;
            
            /*
            //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
            for (int m = 0; m < 5; m++){
                if (mtt_region[m]==1){
                    if (trigger_region_nominal){
                        if (iso_default) h_ss[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*ssweight);
                        if (iso_loose) h_ssloose[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*ssweight);
                    }
                    if (sample!="data_obs"){
                        if (trigger_region_nominal){
                            for (int k = 0; k < 6; k++){
                                if (iso_default) h_ss[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                                if (iso_loose) h_ssloose[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                            }
                            if (sample!="embedded"){
                                for (int k = 0; k < 4; k++){
                                    if (iso_default) h_ss[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                }
                            }
                            if (isRecoilMC){
                                for (int k = 0; k < 12; k++){
                                    if (iso_default) h_ss[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf*ssweight);
                                }
                            }
                            if (isnonRecoilMC){
                                for (int k = 0; k < 2; k++){
                                    if (iso_default) h_ss[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf*ssweight);
                                }
                            }
                            if (name=="ZJ"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_default) h_ss[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                }
                            }
                            if (name=="ttbar"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_default) h_ss[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                }
                            }
                            if (year!="2018" && sample!="embedded"){
                                for (int k = 0; k < 2; k++){
                                    if (iso_default) h_ss[2][m][k+71]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                    if (iso_loose) h_ssloose[2][m][k+71]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                }
                            }
                        }
                        for (int k = 0; k < 24; k++){
                            if (trigger_region_nominal && sample!="embedded"){
                                if (iso_default) h_ss[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                                if (iso_loose) h_ssloose[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                            }
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]){
                                if (iso_default) h_ss[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                                if (iso_loose) h_ssloose[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                            }
                        }
                        for (int k = 0; k < 6; k++){
                            if (trigger_region_shiftedmu[k]){
                                if (iso_default) h_ss[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                                if (iso_loose) h_ssloose[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                            }
                        }
                    }
                    for (int k = 0; k < 8; k++){
                        if (trigger_region_nominal){
                            if (iso_default) h_ss[2][m][k+63]->Fill(var[0][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                            if (iso_loose) h_ssloose[2][m][k+63]->Fill(var[0][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                        }
                    }
                }
            }
            //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
             */
            
            //loop over variables to fill ###############1b################
            for (int m = 0; m < 7; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal){
                    if (iso_default) h_ss[0][m][0]->Fill(var[0][m][0],weight_corr*trgsf*ssweight);
                    if (iso_loose) h_ssloose[0][m][0]->Fill(var[0][m][0],weight_corr*trgsf*ssweight);
                }
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++){
                            if (iso_default) h_ss[0][m][k+11]->Fill(var[0][m][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                            if (iso_loose) h_ssloose[0][m][k+11]->Fill(var[0][m][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                        }
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++){
                                if (iso_default) h_ss[0][m][k+17]->Fill(var[0][m][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+17]->Fill(var[0][m][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                            }
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++){
                                if (iso_default) h_ss[0][m][k+45]->Fill(var[0][m][k+35],weight_corr*trgsf*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+45]->Fill(var[0][m][k+35],weight_corr*trgsf*ssweight);
                            }
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[0][m][k+57]->Fill(var[0][m][k+47],weight_corr*trgsf*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+57]->Fill(var[0][m][k+47],weight_corr*trgsf*ssweight);
                            }
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[0][m][k+59]->Fill(var[0][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+59]->Fill(var[0][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[0][m][k+61]->Fill(var[0][m][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+61]->Fill(var[0][m][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                            }
                        }
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[0][m][k+71]->Fill(var[0][m][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                if (iso_loose) h_ssloose[0][m][k+71]->Fill(var[0][m][0],weight_corr*trgsf*prefiring[k]*ssweight);
                            }
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded"){
                            if (iso_default) h_ss[0][m][k+21]->Fill(var[0][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                            if (iso_loose) h_ssloose[0][m][k+21]->Fill(var[0][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                        }
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]){
                            if (iso_default) h_ss[0][m][k+1]->Fill(var[0][m][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                            if (iso_loose) h_ssloose[0][m][k+1]->Fill(var[0][m][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                        }
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==1 && trigger_region_shiftedmu[k]){
                            if (iso_default) h_ss[0][m][k+5]->Fill(var[0][m][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                            if (iso_loose) h_ssloose[0][m][k+5]->Fill(var[0][m][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                        }
                    }
                }//end of sample!="data_obs"
                //SS uncertainties
                for (int k = 0; k < 8; k++){
                    if (nbtag20==1 && trigger_region_nominal){
                        if (iso_default) h_ss[0][m][k+63]->Fill(var[0][m][0],weight_corr*trgsf*ssweight_shifted[k]);
                        if (iso_loose) h_ssloose[0][m][k+63]->Fill(var[0][m][0],weight_corr*trgsf*ssweight_shifted[k]);
                    }
                }
            }//end of loop of variables to fill ###############1b################
            
            //loop over variables to fill ###############2b################
            for (int m = 0; m < 8; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal){
                    if (iso_default) h_ss[1][m][0]->Fill(var[1][m][0],weight_corr*trgsf*ssweight);
                    if (iso_loose) h_ssloose[1][m][0]->Fill(var[1][m][0],weight_corr*trgsf*ssweight);
                }
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++){
                            if (iso_default) h_ss[1][m][k+11]->Fill(var[1][m][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                            if (iso_loose) h_ssloose[1][m][k+11]->Fill(var[1][m][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                        }
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++){
                                if (iso_default) h_ss[1][m][k+17]->Fill(var[1][m][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+17]->Fill(var[1][m][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                            }
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++){
                                if (iso_default) h_ss[1][m][k+45]->Fill(var[1][m][k+35],weight_corr*trgsf*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+45]->Fill(var[1][m][k+35],weight_corr*trgsf*ssweight);
                            }
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[1][m][k+57]->Fill(var[1][m][k+47],weight_corr*trgsf*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+57]->Fill(var[1][m][k+47],weight_corr*trgsf*ssweight);
                            }
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[1][m][k+59]->Fill(var[1][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+59]->Fill(var[1][m][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[1][m][k+61]->Fill(var[1][m][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+61]->Fill(var[1][m][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                            }
                        }
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) h_ss[1][m][k+71]->Fill(var[1][m][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                if (iso_loose) h_ssloose[1][m][k+71]->Fill(var[1][m][0],weight_corr*trgsf*prefiring[k]*ssweight);
                            }
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded"){
                            if (iso_default) h_ss[1][m][k+21]->Fill(var[1][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                            if (iso_loose) h_ssloose[1][m][k+21]->Fill(var[1][m][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                        }
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]){
                            if (iso_default) h_ss[1][m][k+1]->Fill(var[1][m][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                            if (iso_loose) h_ssloose[1][m][k+1]->Fill(var[1][m][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                        }
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==2 && trigger_region_shiftedmu[k]){
                            if (iso_default) h_ss[1][m][k+5]->Fill(var[1][m][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                            if (iso_loose) h_ssloose[1][m][k+5]->Fill(var[1][m][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                        }
                    }
                }//end of sample!="data_obs"
                //SS uncertainties
                for (int k = 0; k < 8; k++){
                    if (nbtag20==2 && trigger_region_nominal){
                        if (iso_default) h_ss[1][m][k+63]->Fill(var[1][m][0],weight_corr*trgsf*ssweight_shifted[k]);
                        if (iso_loose) h_ssloose[1][m][k+63]->Fill(var[1][m][0],weight_corr*trgsf*ssweight_shifted[k]);
                    }
                }
            }//end of loop of variables to fill ###############2b################
            
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>fill final m_tt categories
            //~~~~~~~~~~~~~~~~~~~1bNN
            for (int m = 0; m < 4; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal){
                    if (iso_default) if (ctg[m][0]) h_ss[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*ssweight);
                    if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*ssweight);
                }
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++){
                            if (iso_default) if (ctg[m][0]) h_ss[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                            if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+11]->Fill(var[0][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                        }
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+17]->Fill(var[0][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                            }
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++){
                                if (iso_default) if (ctg[m][k+35]) h_ss[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf*ssweight);
                                if (iso_loose) if (ctg[m][k+35]) h_ssloose[2][m][k+45]->Fill(var[0][5][k+35],weight_corr*trgsf*ssweight);
                            }
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][k+47]) h_ss[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf*ssweight);
                                if (iso_loose) if (ctg[m][k+47]) h_ssloose[2][m][k+57]->Fill(var[0][5][k+47],weight_corr*trgsf*ssweight);
                            }
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+59]->Fill(var[0][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+61]->Fill(var[0][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                            }
                        }
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+71]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+71]->Fill(var[0][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                            }
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded"){
                            if (iso_default) if (ctg[m][k+11]) h_ss[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                            if (iso_loose) if (ctg[m][k+11]) h_ssloose[2][m][k+21]->Fill(var[0][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                        }
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]){
                            if (iso_default) if (ctg[m][k+1]) h_ss[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                            if (iso_loose) if (ctg[m][k+1]) h_ssloose[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                        }
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==1 && trigger_region_shiftedmu[k]){
                            if (iso_default) if (ctg[m][k+5]) h_ss[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                            if (iso_loose) if (ctg[m][k+5]) h_ssloose[2][m][k+5]->Fill(var[0][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                        }
                    }
                }//end of sample!="data_obs"
                //SS uncertainties
                for (int k = 0; k < 8; k++){
                    if (nbtag20==1 && trigger_region_nominal){
                        if (iso_default) if (ctg[m][0]) h_ss[2][m][k+63]->Fill(var[0][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                        if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+63]->Fill(var[0][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                    }
                }
            }//~~~~~~~~~~~~~~~~~~~1bNN
            
            //~~~~~~~~~~~~~~~~~~~2bNN
            for (int m = 4; m < 7; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal){
                    if (iso_default) if (ctg[m][0]) h_ss[2][m][0]->Fill(var[1][5][0],weight_corr*trgsf*ssweight);
                    if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][0]->Fill(var[1][5][0],weight_corr*trgsf*ssweight);
                }
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 6; k++){
                            if (iso_default) if (ctg[m][0]) h_ss[2][m][k+11]->Fill(var[1][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                            if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+11]->Fill(var[1][5][0],weight_corr*trgsf*trigger_shiftedsf[k]*ssweight);
                        }
                        //btageff
                        if (sample!="embedded"){
                            for (int k = 0; k < 4; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+17]->Fill(var[1][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+17]->Fill(var[1][5][0],weight_corr*trgsf*btagsf_syst[k]*ssweight);
                            }
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++){
                                if (iso_default) if (ctg[m][k+35]) h_ss[2][m][k+45]->Fill(var[1][5][k+35],weight_corr*trgsf*ssweight);
                                if (iso_loose) if (ctg[m][k+35]) h_ssloose[2][m][k+45]->Fill(var[1][5][k+35],weight_corr*trgsf*ssweight);
                            }
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][k+47]) h_ss[2][m][k+57]->Fill(var[1][5][k+47],weight_corr*trgsf*ssweight);
                                if (iso_loose) if (ctg[m][k+47]) h_ssloose[2][m][k+57]->Fill(var[1][5][k+47],weight_corr*trgsf*ssweight);
                            }
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+59]->Fill(var[1][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+59]->Fill(var[1][5][0],weight_corr*trgsf*zptmass_weight_shifting[k]*ssweight);
                            }
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+61]->Fill(var[1][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+61]->Fill(var[1][5][0],weight_corr*trgsf*topfactor_shifting[k]*ssweight);
                            }
                        }
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++){
                                if (iso_default) if (ctg[m][0]) h_ss[2][m][k+71]->Fill(var[1][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                                if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+71]->Fill(var[1][5][0],weight_corr*trgsf*prefiring[k]*ssweight);
                            }
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded"){
                            if (iso_default) if (ctg[m][k+11]) h_ss[2][m][k+21]->Fill(var[1][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                            if (iso_loose) if (ctg[m][k+11]) h_ssloose[2][m][k+21]->Fill(var[1][5][k+11],weight_corr*trgsf*weight_btag_jetsyst[k]*ssweight);
                        }
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]){
                            if (iso_default) if (ctg[m][k+1]) h_ss[2][m][k+1]->Fill(var[1][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                            if (iso_loose) if (ctg[m][k+1]) h_ssloose[2][m][k+1]->Fill(var[1][5][k+1],weight_corr*trgsf_shiftedele[k]*ssweight_shiftedele[k]);
                        }
                    }
                    //loop over trigger regions with shifted muon
                    for (int k = 0; k < 6; k++){
                        if (nbtag20==2 && trigger_region_shiftedmu[k]){
                            if (iso_default) if (ctg[m][k+5]) h_ss[2][m][k+5]->Fill(var[1][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                            if (iso_loose) if (ctg[m][k+5]) h_ssloose[2][m][k+5]->Fill(var[1][5][k+5],weight_corr*trgsf_shiftedmu[k]*ssweight_shiftedmu[k]);
                        }
                    }
                }//end of sample!="data_obs"
                //SS uncertainties
                for (int k = 0; k < 8; k++){
                    if (nbtag20==2 && trigger_region_nominal){
                        if (iso_default) if (ctg[m][0]) h_ss[2][m][k+63]->Fill(var[1][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                        if (iso_loose) if (ctg[m][0]) h_ssloose[2][m][k+63]->Fill(var[1][5][0],weight_corr*trgsf*ssweight_shifted[k]);
                    }
                }
            }//~~~~~~~~~~~~~~~~~~~2bNN
            
        }//end of SS region
        
    }//end of event loop
    
    TFile * fout = TFile::Open(output.c_str(), "UPDATE");
    
    TString dir1b[7] = {"p_1b","p2_1b","p2_z_1b","pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b"};
    TString dir2b[8] = {"p_2b","p2_2b","p2_z_2b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"};
    TString dirmtt[7] = {"1","2","3","4","5","6","7"};
    TString ss = "_ss";
    TString ssloose = "_ssloose";
    TString MC = "MC";
    
    std::vector<TDirectory*> td;
    for (int j = 0; j < 7; j++){//loop over histogram variables ##############1b##############
        td.push_back(fout->mkdir(dir1b[j]));
        td[j]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_os[0][j][0]->SetName(name.c_str());
            h_os[0][j][0]->Write();
            //shifted
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_os[0][j][i+1]->SetName(name.c_str()+shape_eleES[i]);
                else h_os[0][j][i+1]->SetName(name.c_str()+embshape_eleES[i]);
                h_os[0][j][i+1]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[0][j][i+5]->SetName(name.c_str()+shape_muonES[i]);
                else h_os[0][j][i+5]->SetName(name.c_str()+embshape_muonES[i]);
                h_os[0][j][i+5]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[0][j][i+11]->SetName(name.c_str()+shape_trgeff[i]);
                else h_os[0][j][i+11]->SetName(name.c_str()+embshape_trgeff[i]);
                h_os[0][j][i+11]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded"){
                    h_os[0][j][i+17]->SetName(name.c_str()+shape_btagsf[i]);
                    h_os[0][j][i+17]->Write();
                }
            }
            for (int i = 0; i < 24; ++i){
                if (sample!="embedded"){
                    h_os[0][j][i+21]->SetName(name.c_str()+shape_jet[i]);
                    h_os[0][j][i+21]->Write();
                }
            }
            for (int i = 0; i < 12; ++i){
                if (isRecoilMC){
                    h_os[0][j][i+45]->SetName(name.c_str()+shape_recoil[i]);
                    h_os[0][j][i+45]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (isnonRecoilMC){
                    h_os[0][j][i+57]->SetName(name.c_str()+shape_UES[i]);
                    h_os[0][j][i+57]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ZJ"){
                    h_os[0][j][i+59]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_os[0][j][i+59]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ttbar"){
                    h_os[0][j][i+61]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_os[0][j][i+61]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (year!="2018" && sample!="embedded"){
                    h_os[0][j][i+64]->SetName(name.c_str()+shape_prefiring[i]);
                    h_os[0][j][i+64]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_os[0][j][63]->SetName(shape_nonDY[0]);
                h_os[0][j][63]->Write();
            }
            //shifted in ss region
            if (!isSignal){
                h_ss[0][j][0]->SetName(MC+ss);
                h_ss[0][j][0]->Write();
                h_ssloose[0][j][0]->SetName(MC+ssloose);
                h_ssloose[0][j][0]->Write();
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[0][j][i+1]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[0][j][i+1]->Write();
                        h_ssloose[0][j][i+1]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[0][j][i+1]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[0][j][i+5]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[0][j][i+5]->Write();
                        h_ssloose[0][j][i+5]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[0][j][i+5]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[0][j][i+11]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[0][j][i+11]->Write();
                        h_ssloose[0][j][i+11]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[0][j][i+11]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[0][j][i+17]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[0][j][i+17]->Write();
                        h_ssloose[0][j][i+17]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[0][j][i+17]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_ss[0][j][i+21]->SetName(MC+ss+shape_jet[i]);
                        h_ss[0][j][i+21]->Write();
                        h_ssloose[0][j][i+21]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[0][j][i+21]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_jet[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_ss[0][j][i+45]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[0][j][i+45]->Write();
                        h_ssloose[0][j][i+45]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[0][j][i+45]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_ss[0][j][i+57]->SetName(MC+ss+shape_UES[i]);
                        h_ss[0][j][i+57]->Write();
                        h_ssloose[0][j][i+57]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[0][j][i+57]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_UES[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_ss[0][j][i+59]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[0][j][i+59]->Write();
                        h_ssloose[0][j][i+59]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[0][j][i+59]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_ss[0][j][i+61]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[0][j][i+61]->Write();
                        h_ssloose[0][j][i+61]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[0][j][i+61]->Write();
                    }
                    else {
                        h_ss[0][j][0]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[0][j][0]->Write();
                        h_ssloose[0][j][0]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (year!="2018"){
                        if (sample!="embedded"){
                            h_ss[0][j][i+71]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[0][j][i+71]->Write();
                            h_ssloose[0][j][i+71]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[0][j][i+71]->Write();
                        }
                        else {
                            h_ss[0][j][0]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[0][j][0]->Write();
                            h_ssloose[0][j][0]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[0][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 8; i++){
                    h_ss[0][j][i+63]->SetName(MC+ss+shape_ss[i]);
                    h_ss[0][j][i+63]->Write();
                    h_ssloose[0][j][i+63]->SetName(MC+ssloose+shape_ss[i]);
                    h_ssloose[0][j][i+63]->Write();
                }
            }
        }//end of sample!="data_obs"
        if (sample=="data_obs"){
            h_os[0][j][0]->SetName(name.c_str());
            h_os[0][j][0]->Write();
            h_ss[0][j][0]->SetName(name.c_str()+ss);
            h_ss[0][j][0]->Write();
            h_ssloose[0][j][0]->SetName(name.c_str()+ssloose);
            h_ssloose[0][j][0]->Write();
            for (int i = 0; i < 8; i++){
                h_ss[0][j][i+63]->SetName(name.c_str()+ss+shape_ss[i]);
                h_ss[0][j][i+63]->Write();
                h_ssloose[0][j][i+63]->SetName(name.c_str()+ssloose+shape_ss[i]);
                h_ssloose[0][j][i+63]->Write();
            }
        }
    }//end of 1b
    
    for (int j = 0; j < 8; j++){//loop over histogram variables ##############2b##############
        td.push_back(fout->mkdir(dir2b[j]));
        td[j+7]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_os[1][j][0]->SetName(name.c_str());
            h_os[1][j][0]->Write();
            //shifted
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_os[1][j][i+1]->SetName(name.c_str()+shape_eleES[i]);
                else h_os[1][j][i+1]->SetName(name.c_str()+embshape_eleES[i]);
                h_os[1][j][i+1]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[1][j][i+5]->SetName(name.c_str()+shape_muonES[i]);
                else h_os[1][j][i+5]->SetName(name.c_str()+embshape_muonES[i]);
                h_os[1][j][i+5]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[1][j][i+11]->SetName(name.c_str()+shape_trgeff[i]);
                else h_os[1][j][i+11]->SetName(name.c_str()+embshape_trgeff[i]);
                h_os[1][j][i+11]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded"){
                    h_os[1][j][i+17]->SetName(name.c_str()+shape_btagsf[i]);
                    h_os[1][j][i+17]->Write();
                }
            }
            for (int i = 0; i < 24; ++i){
                if (sample!="embedded"){
                    h_os[1][j][i+21]->SetName(name.c_str()+shape_jet[i]);
                    h_os[1][j][i+21]->Write();
                }
            }
            for (int i = 0; i < 12; ++i){
                if (isRecoilMC){
                    h_os[1][j][i+45]->SetName(name.c_str()+shape_recoil[i]);
                    h_os[1][j][i+45]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (isnonRecoilMC){
                    h_os[1][j][i+57]->SetName(name.c_str()+shape_UES[i]);
                    h_os[1][j][i+57]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ZJ"){
                    h_os[1][j][i+59]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_os[1][j][i+59]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ttbar"){
                    h_os[1][j][i+61]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_os[1][j][i+61]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (year!="2018" && sample!="embedded"){
                    h_os[1][j][i+64]->SetName(name.c_str()+shape_prefiring[i]);
                    h_os[1][j][i+64]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_os[1][j][63]->SetName(shape_nonDY[0]);
                h_os[1][j][63]->Write();
            }
            //shifted in ss region
            if (!isSignal){
                h_ss[1][j][0]->SetName(MC+ss);
                h_ss[1][j][0]->Write();
                h_ssloose[1][j][0]->SetName(MC+ssloose);
                h_ssloose[1][j][0]->Write();
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[1][j][i+1]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[1][j][i+1]->Write();
                        h_ssloose[1][j][i+1]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[1][j][i+1]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[1][j][i+5]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[1][j][i+5]->Write();
                        h_ssloose[1][j][i+5]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[1][j][i+5]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[1][j][i+11]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[1][j][i+11]->Write();
                        h_ssloose[1][j][i+11]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[1][j][i+11]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[1][j][i+17]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[1][j][i+17]->Write();
                        h_ssloose[1][j][i+17]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[1][j][i+17]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_ss[1][j][i+21]->SetName(MC+ss+shape_jet[i]);
                        h_ss[1][j][i+21]->Write();
                        h_ssloose[1][j][i+21]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[1][j][i+21]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_jet[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_ss[1][j][i+45]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[1][j][i+45]->Write();
                        h_ssloose[1][j][i+45]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[1][j][i+45]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_ss[1][j][i+57]->SetName(MC+ss+shape_UES[i]);
                        h_ss[1][j][i+57]->Write();
                        h_ssloose[1][j][i+57]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[1][j][i+57]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_UES[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_ss[1][j][i+59]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[1][j][i+59]->Write();
                        h_ssloose[1][j][i+59]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[1][j][i+59]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_ss[1][j][i+61]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[1][j][i+61]->Write();
                        h_ssloose[1][j][i+61]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[1][j][i+61]->Write();
                    }
                    else {
                        h_ss[1][j][0]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[1][j][0]->Write();
                        h_ssloose[1][j][0]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (year!="2018"){
                        if (sample!="embedded"){
                            h_ss[1][j][i+71]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[1][j][i+71]->Write();
                            h_ssloose[1][j][i+71]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[1][j][i+71]->Write();
                        }
                        else {
                            h_ss[1][j][0]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[1][j][0]->Write();
                            h_ssloose[1][j][0]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[1][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 8; i++){
                    h_ss[1][j][i+63]->SetName(MC+ss+shape_ss[i]);
                    h_ss[1][j][i+63]->Write();
                    h_ssloose[1][j][i+63]->SetName(MC+ssloose+shape_ss[i]);
                    h_ssloose[1][j][i+63]->Write();
                }
            }
        }//end of sample!="data_obs"
        if (sample=="data_obs"){
            h_os[1][j][0]->SetName(name.c_str());
            h_os[1][j][0]->Write();
            h_ss[1][j][0]->SetName(name.c_str()+ss);
            h_ss[1][j][0]->Write();
            h_ssloose[1][j][0]->SetName(name.c_str()+ssloose);
            h_ssloose[1][j][0]->Write();
            for (int i = 0; i < 8; i++){
                h_ss[1][j][i+63]->SetName(name.c_str()+ss+shape_ss[i]);
                h_ss[1][j][i+63]->Write();
                h_ssloose[1][j][i+63]->SetName(name.c_str()+ssloose+shape_ss[i]);
                h_ssloose[1][j][i+63]->Write();
            }
        }
    }
    
    //~~~~~~~~~~~~~~~final m_tt
    for (int j = 0; j < 7; j++){
        td.push_back(fout->mkdir(dirmtt[j]));
        td[j+15]->cd();
        if (sample!="data_obs"){
            //nominal
            h_os[2][j][0]->SetName(name.c_str());
            h_os[2][j][0]->Write();
            //shifted
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_os[2][j][i+1]->SetName(name.c_str()+shape_eleES[i]);
                else h_os[2][j][i+1]->SetName(name.c_str()+embshape_eleES[i]);
                h_os[2][j][i+1]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[2][j][i+5]->SetName(name.c_str()+shape_muonES[i]);
                else h_os[2][j][i+5]->SetName(name.c_str()+embshape_muonES[i]);
                h_os[2][j][i+5]->Write();
            }
            for (int i = 0; i < 6; ++i){
                if (sample!="embedded") h_os[2][j][i+11]->SetName(name.c_str()+shape_trgeff[i]);
                else h_os[2][j][i+11]->SetName(name.c_str()+embshape_trgeff[i]);
                h_os[2][j][i+11]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded"){
                    h_os[2][j][i+17]->SetName(name.c_str()+shape_btagsf[i]);
                    h_os[2][j][i+17]->Write();
                }
            }
            for (int i = 0; i < 24; ++i){
                if (sample!="embedded"){
                    h_os[2][j][i+21]->SetName(name.c_str()+shape_jet[i]);
                    h_os[2][j][i+21]->Write();
                }
            }
            for (int i = 0; i < 12; ++i){
                if (isRecoilMC){
                    h_os[2][j][i+45]->SetName(name.c_str()+shape_recoil[i]);
                    h_os[2][j][i+45]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (isnonRecoilMC){
                    h_os[2][j][i+57]->SetName(name.c_str()+shape_UES[i]);
                    h_os[2][j][i+57]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ZJ"){
                    h_os[2][j][i+59]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_os[2][j][i+59]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (name=="ttbar"){
                    h_os[2][j][i+61]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_os[2][j][i+61]->Write();
                }
            }
            for (int i = 0; i < 2; ++i){
                if (year!="2018" && sample!="embedded"){
                    h_os[2][j][i+64]->SetName(name.c_str()+shape_prefiring[i]);
                    h_os[2][j][i+64]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_os[2][j][63]->SetName(shape_nonDY[0]);
                h_os[2][j][63]->Write();
            }
            //shifted in ss region
            if (!isSignal){
                h_ss[2][j][0]->SetName(MC+ss);
                h_ss[2][j][0]->Write();
                h_ssloose[2][j][0]->SetName(MC+ssloose);
                h_ssloose[2][j][0]->Write();
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[2][j][i+1]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[2][j][i+1]->Write();
                        h_ssloose[2][j][i+1]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[2][j][i+1]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_eleES[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_eleES[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[2][j][i+5]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[2][j][i+5]->Write();
                        h_ssloose[2][j][i+5]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[2][j][i+5]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_muonES[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_muonES[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 6; ++i){
                    if (sample!="embedded"){
                        h_ss[2][j][i+11]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[2][j][i+11]->Write();
                        h_ssloose[2][j][i+11]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[2][j][i+11]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_trgeff[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_trgeff[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_ss[2][j][i+17]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[2][j][i+17]->Write();
                        h_ssloose[2][j][i+17]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[2][j][i+17]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_btagsf[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_btagsf[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_ss[2][j][i+21]->SetName(MC+ss+shape_jet[i]);
                        h_ss[2][j][i+21]->Write();
                        h_ssloose[2][j][i+21]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[2][j][i+21]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_jet[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_jet[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_ss[2][j][i+45]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[2][j][i+45]->Write();
                        h_ssloose[2][j][i+45]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[2][j][i+45]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_recoil[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_recoil[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_ss[2][j][i+57]->SetName(MC+ss+shape_UES[i]);
                        h_ss[2][j][i+57]->Write();
                        h_ssloose[2][j][i+57]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[2][j][i+57]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_UES[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_UES[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_ss[2][j][i+59]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[2][j][i+59]->Write();
                        h_ssloose[2][j][i+59]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[2][j][i+59]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_DY_zpt[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_DY_zpt[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_ss[2][j][i+61]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[2][j][i+61]->Write();
                        h_ssloose[2][j][i+61]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[2][j][i+61]->Write();
                    }
                    else {
                        h_ss[2][j][0]->SetName(MC+ss+shape_ttbar_toppt[i]);
                        h_ss[2][j][0]->Write();
                        h_ssloose[2][j][0]->SetName(MC+ssloose+shape_ttbar_toppt[i]);
                        h_ssloose[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (year!="2018"){
                        if (sample!="embedded"){
                            h_ss[2][j][i+71]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[2][j][i+71]->Write();
                            h_ssloose[2][j][i+71]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[2][j][i+71]->Write();
                        }
                        else {
                            h_ss[2][j][0]->SetName(MC+ss+shape_prefiring[i]);
                            h_ss[2][j][0]->Write();
                            h_ssloose[2][j][0]->SetName(MC+ssloose+shape_prefiring[i]);
                            h_ssloose[2][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 8; i++){
                    h_ss[2][j][i+63]->SetName(MC+ss+shape_ss[i]);
                    h_ss[2][j][i+63]->Write();
                    h_ssloose[2][j][i+63]->SetName(MC+ssloose+shape_ss[i]);
                    h_ssloose[2][j][i+63]->Write();
                }
            }
        }//end of sample!="data_obs"
        if (sample=="data_obs"){
            h_os[2][j][0]->SetName(name.c_str());
            h_os[2][j][0]->Write();
            h_ss[2][j][0]->SetName(name.c_str()+ss);
            h_ss[2][j][0]->Write();
            h_ssloose[2][j][0]->SetName(name.c_str()+ssloose);
            h_ssloose[2][j][0]->Write();
            for (int i = 0; i < 8; i++){
                h_ss[2][j][i+63]->SetName(name.c_str()+ss+shape_ss[i]);
                h_ss[2][j][i+63]->Write();
                h_ssloose[2][j][i+63]->SetName(name.c_str()+ssloose+shape_ss[i]);
                h_ssloose[2][j][i+63]->Write();
            }
        }
    }
    //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
    
    fout->Close();
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}




