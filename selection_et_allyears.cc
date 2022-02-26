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
#include "GetTauFR.h"
#include "NN_transform.h"
#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"

using namespace std;

int main(int argc, char** argv){
    
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);
    std::string year = *(argv + 5);
    
    cout << "************* input: " << input.c_str() << " *************" << endl;
    
    TFile * skimmed = new TFile(input.c_str());
    TTree * tree = (TTree*) skimmed->Get("etau_tree");
    TH1F * nevents = (TH1F*) skimmed->Get("nevents");
    float N = nevents->GetBinContent(2); //no. of generated events (before skimming) with genweight
    
    std::string sample_name = sample.c_str();
    std::string NNfile = "/hdfs/store/user/htsoi/NN/et18/" + sample_name + ".root";
    if (year=="2017") NNfile = "/hdfs/store/user/htsoi/NN/et17/" + sample_name + ".root";
    if (year=="2016") NNfile = "/hdfs/store/user/htsoi/NN/et16/" + sample_name + ".root";
    TFile * NN = new TFile(NNfile.c_str());
    TTree * tree_NN = (TTree*) NN->Get("etau_tree_NN");
    
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
    //else if(sample == "W"){weight = 1.0;}
    //else if(sample == "W1"){weight = 1.0;}
    //else if(sample == "W2"){weight = 1.0;}
    //else if(sample == "W3"){weight = 1.0;}
    //else if(sample == "W4"){weight = 1.0;}
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
    tree->SetBranchAddress("l2_decayMode", &l2_decayMode);
    tree->SetBranchAddress("passEle35", &passEle35);
    tree->SetBranchAddress("matchEle35_1", &matchEle35_1);
    tree->SetBranchAddress("filterEle35_1", &filterEle35_1);
    tree->SetBranchAddress("passEle32", &passEle32);
    tree->SetBranchAddress("matchEle32_1", &matchEle32_1);
    tree->SetBranchAddress("filterEle32_1", &filterEle32_1);
    tree->SetBranchAddress("passEle24Tau30", &passEle24Tau30);
    tree->SetBranchAddress("matchEle24Tau30_1", &matchEle24Tau30_1);
    tree->SetBranchAddress("filterEle24Tau30_1", &filterEle24Tau30_1);
    tree->SetBranchAddress("matchEle24Tau30_2", &matchEle24Tau30_2);
    tree->SetBranchAddress("filterEle24Tau30_2", &filterEle24Tau30_2);
    tree->SetBranchAddress("passEle24HPSTau30", &passEle24HPSTau30);
    tree->SetBranchAddress("matchEle24HPSTau30_1", &matchEle24HPSTau30_1);
    tree->SetBranchAddress("filterEle24HPSTau30_1", &filterEle24HPSTau30_1);
    tree->SetBranchAddress("matchEle24HPSTau30_2", &matchEle24HPSTau30_2);
    tree->SetBranchAddress("filterEle24HPSTau30_2", &filterEle24HPSTau30_2);
    tree->SetBranchAddress("matchEmbFilter_Ele24Tau30_1", &matchEmbFilter_Ele24Tau30_1);
    tree->SetBranchAddress("matchEmbFilter_Ele24Tau30_2", &matchEmbFilter_Ele24Tau30_2);
    tree->SetBranchAddress("passEle27", &passEle27);
    tree->SetBranchAddress("matchEle27_1", &matchEle27_1);
    tree->SetBranchAddress("filterEle27_1", &filterEle27_1);
    tree->SetBranchAddress("passEle25", &passEle25);
    tree->SetBranchAddress("matchEle25_1", &matchEle25_1);
    tree->SetBranchAddress("filterEle25_1", &filterEle25_1);
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
    tree->SetBranchAddress("byTightDeepVSe_2", &byTightDeepVSe_2);
    tree->SetBranchAddress("byVLooseDeepVSmu_2", &byVLooseDeepVSmu_2);
    tree->SetBranchAddress("byMediumDeepVSjet_2", &byMediumDeepVSjet_2);
    tree->SetBranchAddress("byVVVLooseDeepVSjet_2", &byVVVLooseDeepVSjet_2);
    tree->SetBranchAddress("byVLooseDeepVSe_2", &byVLooseDeepVSe_2);
    tree->SetBranchAddress("byTightDeepVSmu_2", &byTightDeepVSmu_2);
    tree->SetBranchAddress("zptmass_weight_nom", &zptmass_weight_nom);
    tree->SetBranchAddress("e_trg_ic_ratio", &e_trg_ic_ratio);
    tree->SetBranchAddress("e_trg_24_ic_ratio", &e_trg_24_ic_ratio);
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_etau_ratio", &t_trg_pog_deeptau_medium_etau_ratio);
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_etau_ratio_up", &t_trg_pog_deeptau_medium_etau_ratio_up);
    tree->SetBranchAddress("t_trg_pog_deeptau_medium_etau_ratio_down", &t_trg_pog_deeptau_medium_etau_ratio_down);
    tree->SetBranchAddress("e_trk_ratio", &e_trk_ratio);
    tree->SetBranchAddress("e_idiso_ic_ratio", &e_idiso_ic_ratio);
    tree->SetBranchAddress("e_trg_24_ic_embed_ratio", &e_trg_24_ic_embed_ratio);
    tree->SetBranchAddress("t_trg_mediumDeepTau_etau_embed_ratio", &t_trg_mediumDeepTau_etau_embed_ratio);
    tree->SetBranchAddress("t_trg_mediumDeepTau_etau_embed_ratio_up", &t_trg_mediumDeepTau_etau_embed_ratio_up);
    tree->SetBranchAddress("t_trg_mediumDeepTau_etau_embed_ratio_down", &t_trg_mediumDeepTau_etau_embed_ratio_down);
    tree->SetBranchAddress("e_trg_ic_embed_ratio", &e_trg_ic_embed_ratio);
    tree->SetBranchAddress("e_trk_embed_ratio", &e_trk_embed_ratio);
    tree->SetBranchAddress("e_idiso_ic_embed_ratio", &e_idiso_ic_embed_ratio);
    tree->SetBranchAddress("et_emb_LooseChargedIsoPFTau30_kit_ratio", &et_emb_LooseChargedIsoPFTau30_kit_ratio);
    tree->SetBranchAddress("e_trg_ic_data", &e_trg_ic_data);
    tree->SetBranchAddress("e_trg_24_ic_data", &e_trg_24_ic_data);
    tree->SetBranchAddress("t_trg_mediumDeepTau_etau_data", &t_trg_mediumDeepTau_etau_data);
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
    tree->SetBranchAddress("m_sv_UP", &m_sv_UP);
    tree->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    tree->SetBranchAddress("m_sv_ESCALEUP", &m_sv_ESCALEUP);
    tree->SetBranchAddress("m_sv_ESCALEDOWN", &m_sv_ESCALEDOWN);
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
    tree_NN->SetBranchAddress("NN1b_Up", &NN1b_Up);
    tree_NN->SetBranchAddress("NN1b_Down", &NN1b_Down);
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
    tree_NN->SetBranchAddress("NN2b_Up", &NN2b_Up);
    tree_NN->SetBranchAddress("NN2b_Down", &NN2b_Down);
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
    
    TString shape_tauideff[14] = {"_CMS_tauideff_pt20to25_"+year+"Up","_CMS_tauideff_pt20to25_"+year+"Down","_CMS_tauideff_pt25to30_"+year+"Up","_CMS_tauideff_pt25to30_"+year+"Down","_CMS_tauideff_pt30to35_"+year+"Up","_CMS_tauideff_pt30to35_"+year+"Down","_CMS_tauideff_pt35to40_"+year+"Up","_CMS_tauideff_pt35to40_"+year+"Down","_CMS_tauideff_pt40to500_"+year+"Up","_CMS_tauideff_pt40to500_"+year+"Down","_CMS_tauideff_pt500to1000_"+year+"Up","_CMS_tauideff_pt500to1000_"+year+"Down","_CMS_tauideff_ptgt1000_"+year+"Up","_CMS_tauideff_ptgt1000_"+year+"Down"};
    TString shape_tauidWP[2] = {"_CMS_tauidWP_et_"+year+"Up","_CMS_tauidWP_et_"+year+"Down"};
    TString shape_tauideff_efake[4] = {"_CMS_tauideff_VSe_bar_"+year+"Up","_CMS_tauideff_VSe_bar_"+year+"Down","_CMS_tauideff_VSe_end_"+year+"Up","_CMS_tauideff_VSe_end_"+year+"Down"};
    TString shape_tauideff_mufake[10] = {"_CMS_tauideff_VSmu_eta0to0p4_"+year+"Up","_CMS_tauideff_VSmu_eta0to0p4_"+year+"Down","_CMS_tauideff_VSmu_eta0p4to0p8_"+year+"Up","_CMS_tauideff_VSmu_eta0p4to0p8_"+year+"Down","_CMS_tauideff_VSmu_eta0p8to1p2_"+year+"Up","_CMS_tauideff_VSmu_eta0p8to1p2_"+year+"Down","_CMS_tauideff_VSmu_eta1p2to1p7_"+year+"Up","_CMS_tauideff_VSmu_eta1p2to1p7_"+year+"Down","_CMS_tauideff_VSmu_eta1p7to2p3_"+year+"Up","_CMS_tauideff_VSmu_eta1p7to2p3_"+year+"Down"};
    TString shape_trgeff[4] = {"_CMS_trgeff_single_et_"+year+"Up","_CMS_trgeff_single_et_"+year+"Down","_CMS_trgeff_cross_et_"+year+"Up","_CMS_trgeff_cross_et_"+year+"Down"};
    //TString shape_btagsf[4] = {"_CMS_btagsf_heavy_"+year+"Up","_CMS_btagsf_heavy_"+year+"Down","_CMS_btagsf_light_"+year+"Up","_CMS_btagsf_light_"+year+"Down"};
    TString shape_btagsf[16] = {"_CMS_btagsf_hfUp","_CMS_btagsf_hfDown","_CMS_btagsf_lfUp","_CMS_btagsf_lfDown","_CMS_btagsf_hfstats1_"+year+"Up","_CMS_btagsf_hfstats1_"+year+"Down","_CMS_btagsf_hfstats2_"+year+"Up","_CMS_btagsf_hfstats2_"+year+"Down","_CMS_btagsf_lfstats1_"+year+"Up","_CMS_btagsf_lfstats1_"+year+"Down","_CMS_btagsf_lfstats2_"+year+"Up","_CMS_btagsf_lfstats2_"+year+"Down","_CMS_btagsf_cferr1Up","_CMS_btagsf_cferr1Down","_CMS_btagsf_cferr2Up","_CMS_btagsf_cferr2Down"};
    TString shape_tauES[8] = {"_CMS_TES_dm0_"+year+"Up","_CMS_TES_dm0_"+year+"Down","_CMS_TES_dm1_"+year+"Up","_CMS_TES_dm1_"+year+"Down","_CMS_TES_dm10_"+year+"Up","_CMS_TES_dm10_"+year+"Down","_CMS_TES_dm11_"+year+"Up","_CMS_TES_dm11_"+year+"Down"};
    TString shape_mufaketauES[4] = {"_CMS_muTES_dm0_"+year+"Up","_CMS_muTES_dm0_"+year+"Down","_CMS_muTES_dm1_"+year+"Up","_CMS_muTES_dm1_"+year+"Down"};
    TString shape_elefaketauES[4] = {"_CMS_eleTES_dm0_"+year+"Up","_CMS_eleTES_dm0_"+year+"Down","_CMS_eleTES_dm1_"+year+"Up","_CMS_eleTES_dm1_"+year+"Down"};
    TString shape_eleES[4] = {"_CMS_eleES_bar_"+year+"Up","_CMS_eleES_bar_"+year+"Down","_CMS_eleES_end_"+year+"Up","_CMS_eleES_end_"+year+"Down"};
    TString shape_jet[24] = {"_CMS_JetAbsoluteUp","_CMS_JetAbsoluteDown","_CMS_JetAbsolute_"+year+"Up","_CMS_JetAbsolute_"+year+"Down","_CMS_JetBBEC1Up","_CMS_JetBBEC1Down","_CMS_JetBBEC1_"+year+"Up","_CMS_JetBBEC1_"+year+"Down","_CMS_JetEC2Up","_CMS_JetEC2Down","_CMS_JetEC2_"+year+"Up","_CMS_JetEC2_"+year+"Down","_CMS_JetFlavorQCDUp","_CMS_JetFlavorQCDDown","_CMS_JetHFUp","_CMS_JetHFDown","_CMS_JetHF_"+year+"Up","_CMS_JetHF_"+year+"Down","_CMS_JetRelativeBalUp","_CMS_JetRelativeBalDown","_CMS_JetRelativeSample_"+year+"Up","_CMS_JetRelativeSample_"+year+"Down","_CMS_JERUp","_CMS_JERDown"};
    //Z+jets, W+jets, ggH, qqH
    TString shape_recoil[12] = {"_CMS_0j_resolution_"+year+"Up","_CMS_0j_resolution_"+year+"Down","_CMS_0j_response_"+year+"Up","_CMS_0j_response_"+year+"Down","_CMS_1j_resolution_"+year+"Up","_CMS_1j_resolution_"+year+"Down","_CMS_1j_response_"+year+"Up","_CMS_1j_response_"+year+"Down","_CMS_gt1j_resolution_"+year+"Up","_CMS_gt1j_resolution_"+year+"Down","_CMS_gt1j_response_"+year+"Up","_CMS_gt1j_response_"+year+"Down"};
    //those without recoil
    TString shape_UES[2] = {"_CMS_UES_"+year+"Up","_CMS_UES_"+year+"Down"};
    //for DY MC only
    TString shape_DY_zpt[2] = {"_CMS_Zpt_"+year+"Up","_CMS_Zpt_"+year+"Down"};
    //for ttbar only
    TString shape_ttbar_toppt[2] = {"_CMS_toppt_"+year+"Up","_CMS_toppt_"+year+"Down"};
    //fake cross trigger factor uncertainties
    TString shape_fake_crosstrg[2] = {"_CMS_crosstrg_fakefactor_"+year+"Up","_CMS_crosstrg_fakefactor_"+year+"Down"};
    //fake rate uncertainties
    TString shape_fakerate[14] = {"_CMS_jetFR_pt0to25_"+year+"Up","_CMS_jetFR_pt0to25_"+year+"Down","_CMS_jetFR_pt25to30_"+year+"Up","_CMS_jetFR_pt25to30_"+year+"Down","_CMS_jetFR_pt30to35_"+year+"Up","_CMS_jetFR_pt30to35_"+year+"Down","_CMS_jetFR_pt35to40_"+year+"Up","_CMS_jetFR_pt35to40_"+year+"Down","_CMS_jetFR_pt40to50_"+year+"Up","_CMS_jetFR_pt40to50_"+year+"Down","_CMS_jetFR_pt50to60_"+year+"Up","_CMS_jetFR_pt50to60_"+year+"Down","_CMS_jetFR_ptgt60_"+year+"Up","_CMS_jetFR_ptgt60_"+year+"Down"};
    //prefiring
    TString shape_prefiring[2] = {"_CMS_prefiring_"+year+"Up","_CMS_prefiring_"+year+"Down"};// only 2016 and 2017
    
    //give different names for embedded
    TString embshape_tauideff[14] = {"_CMS_EMB_tauideff_pt20to25_"+year+"Up","_CMS_EMB_tauideff_pt20to25_"+year+"Down","_CMS_EMB_tauideff_pt25to30_"+year+"Up","_CMS_EMB_tauideff_pt25to30_"+year+"Down","_CMS_EMB_tauideff_pt30to35_"+year+"Up","_CMS_EMB_tauideff_pt30to35_"+year+"Down","_CMS_EMB_tauideff_pt35to40_"+year+"Up","_CMS_EMB_tauideff_pt35to40_"+year+"Down","_CMS_EMB_tauideff_pt40to500_"+year+"Up","_CMS_EMB_tauideff_pt40to500_"+year+"Down","_CMS_EMB_tauideff_pt500to1000_"+year+"Up","_CMS_EMB_tauideff_pt500to1000_"+year+"Down","_CMS_EMB_tauideff_ptgt1000_"+year+"Up","_CMS_EMB_tauideff_ptgt1000_"+year+"Down"};
    TString embshape_tauidWP[2] = {"_CMS_EMB_tauidWP_et_"+year+"Up","_CMS_EMB_tauidWP_et_"+year+"Down"};
    TString embshape_trgeff[4] = {"_CMS_EMB_trgeff_single_et_"+year+"Up","_CMS_EMB_trgeff_single_et_"+year+"Down","_CMS_EMB_trgeff_cross_et_"+year+"Up","_CMS_EMB_trgeff_cross_et_"+year+"Down"};
    TString embshape_tauES[8] = {"_CMS_EMB_TES_dm0_"+year+"Up","_CMS_EMB_TES_dm0_"+year+"Down","_CMS_EMB_TES_dm1_"+year+"Up","_CMS_EMB_TES_dm1_"+year+"Down","_CMS_EMB_TES_dm10_"+year+"Up","_CMS_EMB_TES_dm10_"+year+"Down","_CMS_EMB_TES_dm11_"+year+"Up","_CMS_EMB_TES_dm11_"+year+"Down"};
    TString embshape_tautracking[6] = {"_CMS_EMB_tautrack_dm0dm10_"+year+"Up","_CMS_EMB_tautrack_dm0dm10_"+year+"Down","_CMS_EMB_tautrack_dm1_"+year+"Up","_CMS_EMB_tautrack_dm1_"+year+"Down","_CMS_EMB_tautrack_dm11_"+year+"Up","_CMS_EMB_tautrack_dm11_"+year+"Down"};
    TString embshape_eleES[4] = {"_CMS_EMB_eleES_bar_"+year+"Up","_CMS_EMB_eleES_bar_"+year+"Down","_CMS_EMB_eleES_end_"+year+"Up","_CMS_EMB_eleES_end_"+year+"Down"};
    
    //comtamination to emb: all non-DY MC with gen tautau
    TString shape_nonDY[1] = {"nonDYMC"};
    
    //h[i][j][k]: (i=0: 1bjet, i=1: 2bjets, i=2: final mtt categories), (j=filling variable), (k=systematics type)
    std::vector<std::vector<std::vector<TH1F*>>> h_iso;
    std::vector<std::vector<std::vector<TH1F*>>> h_anti;
    for (int i = 0; i < 3; i++){
        h_iso.push_back(std::vector<std::vector<TH1F*>>());
        h_anti.push_back(std::vector<std::vector<TH1F*>>());
    }
    for (int i = 0; i < 7; i++){//no. of variables for 1 bjet category
        h_iso[0].push_back(std::vector<TH1F*>());
        h_anti[0].push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 8; i++){//no. of variables for 2 bjets category
        h_iso[1].push_back(std::vector<TH1F*>());
        h_anti[1].push_back(std::vector<TH1F*>());
    }
    for (int i = 0; i < 6; i++){//no. of final mtt categories
        h_iso[2].push_back(std::vector<TH1F*>());
        h_anti[2].push_back(std::vector<TH1F*>());
    }
    /*
    float bins_p_1b[] = {0.,0.02,0.04,0.06,0.08,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.85,0.9,0.92,0.94,0.96,0.98,1.};
    float bins_p_2b[] = {0.,0.05,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.95,1.};
    int nbins_p_1b = sizeof(bins_p_1b)/sizeof(Float_t)-1;
    int nbins_p_2b = sizeof(bins_p_2b)/sizeof(Float_t)-1;*/
    
    for (int i = 0; i < 126; i++){
        //i=0 nominal, 1-8 TES, 9-22 tauIDeff, 23-26 efaketauIDeff, 27-36 mufaketauIDeff, 37-40 muTES, 41-44 eleTES, 45-48 eleES, 49-52 trgsf, 53-56 btagsf (deprecated btag SF method 1c), 57-80 jet, 81-92 recoil, 93-94 UES, 95-100 emb tautracking, 101-102 DY zpt, 103-104 ttbar toppt, 105 nonDY, 106-107 tauidWP, 108-109 prefiring, 110-125 btagsf (method 1d)
        //1 bjet
        h_iso[0][0].push_back(new TH1F("","",40,0.,1.));//p
        h_iso[0][1].push_back(new TH1F("","",40,0.,1.));//p2
        h_iso[0][2].push_back(new TH1F("","",20,0.8,1.));//p2_z
        h_iso[0][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_iso[0][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_iso[0][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_iso[0][6].push_back(new TH1F("","",42,40,460));//m_btt
        //2 bjets
        h_iso[1][0].push_back(new TH1F("","",20,0.,1.));//p
        h_iso[1][1].push_back(new TH1F("","",20,0.,1.));//p2
        h_iso[1][2].push_back(new TH1F("","",40,0.8,1.));//p2_z
        h_iso[1][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_iso[1][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_iso[1][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_iso[1][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_iso[1][7].push_back(new TH1F("","",54,60,600));//m_bbtt
        //final mtt categories
        h_iso[2][0].push_back(new TH1F("","",13,0,104));//m_tt_1
        h_iso[2][1].push_back(new TH1F("","",13,0,104));//m_tt_2
        h_iso[2][2].push_back(new TH1F("","",20,0,100));//m_tt_3
        h_iso[2][3].push_back(new TH1F("","",15,0,300));//m_tt_4
        h_iso[2][4].push_back(new TH1F("","",9,0,108));//m_tt_5
        h_iso[2][5].push_back(new TH1F("","",15,0,300));//m_tt_6
    }
    for (int i = 0; i < 89; i++){
        //tau anti-isolated region; i=0 nominal, 1-4 eleES, 5-8 trgsf, 9-12 btagsf (deprecated btag SF method 1c), 13-36 jet, 37-48 recoil, 49-50 UES, 51-52 DY zpt, 53-54 ttbar toppt, 55-56 crosstrg fakefactor, 57-70 fake rate, 71-72 prefiring, 73-88 btagsf (method 1d)
        //1 bjet
        h_anti[0][0].push_back(new TH1F("","",40,0.,1.));//p
        h_anti[0][1].push_back(new TH1F("","",40,0.,1.));//p2
        h_anti[0][2].push_back(new TH1F("","",20,0.8,1.));//p2_z
        h_anti[0][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_anti[0][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_anti[0][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_anti[0][6].push_back(new TH1F("","",42,40,460));//m_btt
        //2 bjets
        h_anti[1][0].push_back(new TH1F("","",20,0.,1.));//p
        h_anti[1][1].push_back(new TH1F("","",20,0.,1.));//p2
        h_anti[1][2].push_back(new TH1F("","",40,0.8,1.));//p2_z
        h_anti[1][3].push_back(new TH1F("","",70,10,150));//pt_1
        h_anti[1][4].push_back(new TH1F("","",45,10,100));//pt_2
        h_anti[1][5].push_back(new TH1F("","",40,0,400));//m_tt
        h_anti[1][6].push_back(new TH1F("","",42,40,460));//m_btt
        h_anti[1][7].push_back(new TH1F("","",54,60,600));//m_bbtt
        //final mtt categories
        h_anti[2][0].push_back(new TH1F("","",13,0,104));//m_tt_1
        h_anti[2][1].push_back(new TH1F("","",13,0,104));//m_tt_2
        h_anti[2][2].push_back(new TH1F("","",20,0,100));//m_tt_3
        h_anti[2][3].push_back(new TH1F("","",15,0,300));//m_tt_4
        h_anti[2][4].push_back(new TH1F("","",9,0,108));//m_tt_5
        h_anti[2][5].push_back(new TH1F("","",15,0,300));//m_tt_6
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
    /*
    TGraphAsymmErrors *g_taufr_dm0M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm0_Te_VLmu_deepmedium_hpt_dm0_Te_VLmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm1M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm1_Te_VLmu_deepmedium_hpt_dm1_Te_VLmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm10M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm10_Te_VLmu_deepmedium_hpt_dm10_Te_VLmu_deepveryveryveryloose");
    TGraphAsymmErrors *g_taufr_dm11M = (TGraphAsymmErrors*) f_taufr->Get("hpt_dm11_Te_VLmu_deepmedium_hpt_dm11_Te_VLmu_deepveryveryveryloose");*/
    
    TGraphAsymmErrors *g_taufr_dmall = (TGraphAsymmErrors*) f_taufr->Get("hpt_dmall_Te_VLmu_1jet_deepmedium_hpt_dmall_Te_VLmu_1jet_deepveryveryveryloose");
    
    //btagging SF reader
    std::string btagSFfile = "DeepJet_102XSF_V2_JESreduced";
    if (year=="2017") btagSFfile = "DeepFlavour_94XSF_V4_B_F_JESreduced";
    if (year=="2016") btagSFfile = "DeepJet_2016LegacySF_V1_TuneCP5_JESreduced";
    std::string btagSFfilecsv = btagSFfile + ".csv";
    
    BTagCalibration calib(btagSFfile, btagSFfilecsv);
    //list of btag SF variations to take from the csv
    std::vector<std::string> btagSFvariations = {
        //all syst except cferr1/2 (jes, hf, lf, hfstats1/2, lfstats1/2) are applied to both b and udsg flavours
        //cferr1/2 is applied to c flavour jets only
        //hfstats1/2 and lfstats1/2 are statistical in nature -> uncorrelated across years
        //other SF-related syst (hf, lf, cferr1/2) are correlated across years
        //jes-varied SFs are to be applied with corresponding jes-varied jets (not nominal jets)
        "up_hf",                        "down_hf",
        "up_lf",                        "down_lf",
        "up_hfstats1",                  "down_hfstats1",
        "up_hfstats2",                  "down_hfstats2",
        "up_lfstats1",                  "down_lfstats1",
        "up_lfstats2",                  "down_lfstats2",
        "up_cferr1",                    "down_cferr1",
        "up_cferr2",                    "down_cferr2",
        "up_jesAbsolute",               "down_jesAbsolute",
        "up_jesAbsolute_"+year,         "down_jesAbsolute_"+year,
        "up_jesBBEC1",                  "down_jesBBEC1",
        "up_jesBBEC1_"+year,            "down_jesBBEC1_"+year,
        "up_jesEC2",                    "down_jesEC2",
        "up_jesEC2_"+year,              "down_jesEC2_"+year,
        "up_jesFlavorQCD",              "down_jesFlavorQCD",
        "up_jesHF",                     "down_jesHF",
        "up_jesHF_"+year,               "down_jesHF_"+year,
        "up_jesRelativeBal",            "down_jesRelativeBal",
        "up_jesRelativeSample_"+year,   "down_jesRelativeSample_"+year
    };
    BTagCalibrationReader reader(BTagEntry::OP_RESHAPING, "central", btagSFvariations);
    reader.load(calib, BTagEntry::FLAV_B, "iterativefit");
    reader.load(calib, BTagEntry::FLAV_C, "iterativefit");
    reader.load(calib, BTagEntry::FLAV_UDSG, "iterativefit");
    
    
    //loop over events
    int n = tree->GetEntries(); //no. of events after skimming
    for(int i = 0; i < n; i++){
        tree->GetEntry(i);
        if (i % 100 == 0) fprintf(stdout, "\r Processed events: %d of %d...", i, n);
        fflush(stdout);
        
        tree_NN->GetEntry(i);
        float p_N = 1.5;
        
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
        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myb1;
        myb1.SetPtEtaPhiM(bpt_deepflavour_1,beta_deepflavour_1,bphi_deepflavour_1,bm_deepflavour_1);
        TLorentzVector myb2;
        myb2.SetPtEtaPhiM(bpt_deepflavour_2,beta_deepflavour_2,bphi_deepflavour_2,bm_deepflavour_2);
        
        bool isSingleTrigger = false;
        bool isCrossTrigger = false;
        if (year=="2018"){
            isSingleTrigger = (passEle32 && matchEle32_1 && filterEle32_1) or (passEle35 && matchEle35_1 && filterEle35_1);
            isCrossTrigger = (passEle24HPSTau30 && matchEle24HPSTau30_1 && filterEle24HPSTau30_1 && matchEle24HPSTau30_2 && filterEle24HPSTau30_2 && fabs(eta_2)<2.1);
            if (sample=="embedded") isCrossTrigger = (matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2 && fabs(eta_2)<2.1);
            if (sample=="data_obs" && run<317509) isCrossTrigger = (passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && fabs(eta_2)<2.1);
        }
        if (year=="2017"){
            isSingleTrigger = (passEle32 && matchEle32_1 && filterEle32_1) or (passEle27 && matchEle27_1 && filterEle27_1);
            isCrossTrigger = (passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && fabs(eta_2)<2.1);
            if (sample=="embedded" && fabs(eta_1)<1.479) isCrossTrigger = (passEle24Tau30 && fabs(eta_2)<2.1);
            if (sample=="embedded" && fabs(eta_1)>1.479 && pt_1<40){//for emb with fabs(eta_1)>1.479 && pt_1<40, there are only pt reqirements w/o trigger variables to pass
                isSingleTrigger = true;
                isCrossTrigger = fabs(eta_2)<2.1;
            }
        }
        if (year=="2016"){
            isSingleTrigger = (passEle25 && matchEle25_1 && filterEle25_1);//no cross trigger in 2016
        }
        float single_elept_thres = 33;
        float single_taupt_thres = 20;
        float cross_elept_thres = 25;
        float cross_taupt_thres = 35;
        if (year=="2017"){
            single_elept_thres = 28;
            single_taupt_thres = 20;
            cross_elept_thres = 25;
            cross_taupt_thres = 35;
        }
        if (year=="2016"){//no cross trigger in 2016
            single_elept_thres = 26;
            single_taupt_thres = 20;
        }
        
        if (!isSingleTrigger && !isCrossTrigger) continue;
        
        if (!(fabs(eta_1)<2.1 && fabs(eta_2)<2.3)) continue;
        if (!(iso_1<0.15)) continue;
        if (q_1*q_2>0) continue;
        
        //discriminators for e/mu faking tau_h (many Z->ee so tight for e; rare e+mu so loose for mu)
        if (!(byTightDeepVSe_2 && byVLooseDeepVSmu_2)) continue;
        
        if (!(myele.DeltaR(mytau)>0.4)) continue;
        
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
        float taufakesf = 1.0;
        
        //scale factors for MC and corrections
        if (sample!="data_obs" && sample!="embedded"){
            
            //reject MC with a jet faking tau_h as duplicated in fake background estimation
            if (gen_match_2==6) continue;
            
            //electron ID/iso/tracking scale factors
            sf_MC *= e_trk_ratio * e_idiso_ic_ratio;
            
            //re-weigh Z pT spectrum for DY samples
            if (name=="ZJ"){
                sf_MC *= zptmass_weight_nom;
            }
            
            //re-weigh top pT spectrum for ttbar samples
            if (name=="ttbar"){
                float pttop1=pt_top1;
                if (pttop1>500) pttop1=500;
                float pttop2=pt_top2;
                if (pttop2>500) pttop2=500;
                topfactor = sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
                sf_MC *= topfactor;
            }
            
            //re-weigh pileup distribution
            sf_MC *= LumiWeights_12->weight(npu);
            
            //generator weight
            sf_MC *= genweight;
            
            //ele->tauh and muon->tauh sf
            if (gen_match_2==1 or gen_match_2==3){
                if (fabs(eta_2)<1.46){
                    taufakesf = 1.470;
                    if (year=="2017") taufakesf = 1.220;
                    if (year=="2016") taufakesf = 1.220;
                }
                if (fabs(eta_2)>1.56) {
                    taufakesf = 0.660;
                    if (year=="2017") taufakesf = 0.930;
                    if (year=="2016") taufakesf = 1.470;
                }
            }
            if (gen_match_2==2 or gen_match_2==4){
                if (fabs(eta_2)<0.4){
                    taufakesf = 0.954;
                    if (year=="2017") taufakesf = 1.094;
                    if (year=="2016") taufakesf = 1.282;
                }
                else if (fabs(eta_2)<0.8){
                    taufakesf = 1.009;
                    if (year=="2017") taufakesf = 0.907;
                    if (year=="2016") taufakesf = 0.998;
                }
                else if (fabs(eta_2)<1.2){
                    taufakesf = 1.029;
                    if (year=="2017") taufakesf = 0.936;
                    if (year=="2016") taufakesf = 1.265;
                }
                else if (fabs(eta_2)<1.7){
                    taufakesf = 0.928;
                    if (year=="2017") taufakesf = 0.735;
                    if (year=="2016") taufakesf = 0.895;
                }
                else {
                    taufakesf = 5.000;
                    if (year=="2017") taufakesf = 4.610;
                    if (year=="2016") taufakesf = 4.937;
                }
            }
            sf_MC *= taufakesf;
        }
        
        float sf_embed = 1.0;
        
        //scale factors for embedded Z->tautau and corrections
        if (sample=="embedded"){
            
            if (l2_decayMode==0) sf_embed *= 0.975;//1prong
            else if (l2_decayMode==1) sf_embed *= 0.975*1.051;//1prong+1strip
            else if (l2_decayMode==10) sf_embed *= 0.975*0.975*0.975;//3prongs
            else sf_embed *= 0.975*0.975*0.975*1.051;//3prongs+1strip
            
            if (gen_match_2==6) continue;
            
            //rejecting buggy events
            if (genweight>1.0) continue;
            
            //electron ID/iso/tracking scale factors
            sf_embed *= e_trk_embed_ratio * e_idiso_ic_embed_ratio;
            
            //efficiency of selecting Z->mumu data
            sf_embed *= m_sel_trg_ic_ratio * m_sel_id_ic_ratio_1 * m_sel_id_ic_ratio_2;
            
            //generator weight
            sf_embed *= genweight;
        }
        
        float weight_corr = weight * sf_MC * sf_embed;
        
        //count btagged jets (deepflavour)
        int nbtag20 = 0;
        float bscore_thres = 0.2770;
        if (year=="2017") bscore_thres = 0.3033;
        if (year=="2016") bscore_thres = 0.3093;
        if (bpt_deepflavour_1>20 && bscore_deepflavour_1>bscore_thres && fabs(beta_deepflavour_1)<2.4){
            nbtag20++;
        }
        if (bpt_deepflavour_2>20 && bscore_deepflavour_2>bscore_thres && fabs(beta_deepflavour_2)<2.4){
            nbtag20++;
        }
        //b-tagged jet true flavour to be passed to btag SF reader
        auto btagflavour_1 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_1==5) btagflavour_1 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_1==4) btagflavour_1 = BTagEntry::FLAV_C;
        if (bflavour_deepflavour_1==0) btagflavour_1 = BTagEntry::FLAV_UDSG;
        auto btagflavour_2 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_2==5) btagflavour_2 = BTagEntry::FLAV_B;
        if (bflavour_deepflavour_2==4) btagflavour_2 = BTagEntry::FLAV_C;
        if (bflavour_deepflavour_2==0) btagflavour_2 = BTagEntry::FLAV_UDSG;
        
        //btag weights for MC only
        float weight_btag_1b = 1.0;
        float weight_btag_2b = 1.0;
        if (sample!="data_obs" && sample!="embedded"){
            //weight_btag_1b = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, 0);
            //weight_btag_2b = GetbtagSF(stoi(year.c_str()), bMpt_1, bMflavor_1, 0)*GetbtagSF(stoi(year.c_str()), bMpt_2, bMflavor_2, 0);
            if (nbtag20==1) weight_btag_1b = reader.eval_auto_bounds("central", btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1);
            if (nbtag20==2) weight_btag_2b = reader.eval_auto_bounds("central", btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*reader.eval_auto_bounds("central", btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2);
        }
        if (nbtag20==1) weight_corr *= weight_btag_1b;
        if (nbtag20==2) weight_corr *= weight_btag_2b;
        
        //######################btag SF-related shifts (use nominal jet templates in the shifted SF)#######################
        std::vector<float> btagsf_syst;
        for (int j = 0; j < 16; j++){
            //ordering: hf updown, lf updown, hfstats1 updown, hfstats2 updown, lfstats1 updown, lfstats2 updown, cferr1 updown, cferr2 updown
            //NOTE: variations due to "jes", "lf", "hf", "hfstats1/2", and "lfstats1/2" are applied to both b and udsg jets. For c-flavored jets, only "cferr1/2" is applied
            btagsf_syst.push_back(1.0);
            if (sample!="data_obs" && sample!="embedded"){
                if (j < 12){//{hf, lf, hfstats1/2, lfstats1/2} applied to both b and udsg jets only (use central for c jets, which is flat 1.0)
                    if (nbtag20==1){
                        if (btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)/weight_btag_1b;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_C){
                            btagsf_syst[j] = 1.0;
                        }
                    }
                    if (nbtag20==2){
                        if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*reader.eval_auto_bounds(btagSFvariations[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2)/weight_btag_2b;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_C and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                            btagsf_syst[j] = 1.0*reader.eval_auto_bounds(btagSFvariations[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2)/weight_btag_2b;
                        }
                        else if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and btagflavour_2==BTagEntry::FLAV_C){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*1.0/weight_btag_2b;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_C and btagflavour_2==BTagEntry::FLAV_C){
                            btagsf_syst[j] = 1.0;
                        }
                    }
                }
                else{//{cferr1/2} applied to c jets only (use central for both b and udsg jets)
                    if (nbtag20==1){
                        if (btagflavour_1==BTagEntry::FLAV_C){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)/weight_btag_1b;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG){
                            btagsf_syst[j] = 1.0;
                        }
                    }
                    if (nbtag20==2){
                        if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                            btagsf_syst[j] = 1.0;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_C and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*reader.eval_auto_bounds("central", btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2)/weight_btag_2b;
                        }
                        else if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and btagflavour_2==BTagEntry::FLAV_C){
                            btagsf_syst[j] = reader.eval_auto_bounds("central", btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*reader.eval_auto_bounds(btagSFvariations[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2)/weight_btag_2b;
                        }
                        else if (btagflavour_1==BTagEntry::FLAV_C and btagflavour_2==BTagEntry::FLAV_C){
                            btagsf_syst[j] = reader.eval_auto_bounds(btagSFvariations[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_deepflavour_1, bscore_deepflavour_1)*reader.eval_auto_bounds(btagSFvariations[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_deepflavour_2, bscore_deepflavour_2)/weight_btag_2b;
                        }
                    }
                }
            }
        }
        
        //nominal var
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);
        TLorentzVector mytt;
        mytt.SetPtEtaPhiM((myele+mytau+mymet).Pt(),(myele+mytau+mymet).Eta(),(myele+mytau+mymet).Phi(),m_sv);
        float m_btt = (mytt + myb1).M();
        float m_bbtt = (mytt + myb1 + myb2).M();
        float mt_tau1=TMass_F((myele).Pt(),mymet.Pt(),(myele).Px(),mymet.Px(),(myele).Py(),mymet.Py());
        float mt_tau2=TMass_F((mytau).Pt(),mymet.Pt(),(mytau).Px(),mymet.Px(),(mytau).Py(),mymet.Py());
        float norm_zeta=norm_F(myele.Px()/myele.Pt()+mytau.Px()/mytau.Pt(),myele.Py()/myele.Pt()+mytau.Py()/mytau.Pt());
        float x_zeta= (myele.Px()/myele.Pt()+mytau.Px()/mytau.Pt())/norm_zeta;
        float y_zeta= (myele.Py()/myele.Pt()+mytau.Py()/mytau.Pt())/norm_zeta;
        float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
        float pzeta_vis=(myele.Px()+mytau.Px())*x_zeta+(myele.Py()+mytau.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;
        
        std::vector<std::vector<std::vector<float>>> var;
        for (int j = 0; j < 2; j++) var.push_back(std::vector<std::vector<float>>());
        for (int j = 0; j < 7; j++) var[0].push_back(std::vector<float>());
        for (int j = 0; j < 8; j++) var[1].push_back(std::vector<float>());
        for (int j = 0; j < 59; j++){//i=0 nominal, 1-8 TES, 9-12 muTES, 13-16 eleTES, 17-20 eleES, 21-44 jet, 45-56 recoil, 57-58 UES
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
        
        //#####################TES###########################
        std::vector<TLorentzVector> myshiftedtau;
        std::vector<TLorentzVector> mymet_shiftedtau;
        std::vector<TLorentzVector> mytt_shiftedtau;
        std::vector<float> m_btt_shiftedtau;
        std::vector<float> m_bbtt_shiftedtau;
        for (int j = 0; j < 8; j++){
            myshiftedtau.push_back(mytau);
            mymet_shiftedtau.push_back(mymet);
            mytt_shiftedtau.push_back(mytt);
            m_btt_shiftedtau.push_back(m_btt);
            m_bbtt_shiftedtau.push_back(m_bbtt);
        }
        //define TES central and uncert values by DM and low/high pt
        float tes_dm0_cent = 0.984;
        float tes_dm1_cent = 0.996;
        float tes_dm10_cent = 0.988;
        float tes_dm11_cent = 0.996;
        float tes_dm0_lowpt_uncer = 0.009;
        float tes_dm1_lowpt_uncer = 0.006;
        float tes_dm10_lowpt_uncer = 0.007;
        float tes_dm11_lowpt_uncer = 0.012;
        float tes_dm0_highpt_uncer = 0.03;
        float tes_dm1_highpt_uncer = 0.02;
        float tes_dm10_highpt_uncer = 0.011;
        float tes_dm11_highpt_uncer = 0.039;
        if (year=="2017"){
            tes_dm0_cent = 1.004;
            tes_dm1_cent = 1.002;
            tes_dm10_cent = 1.001;
            tes_dm11_cent = 0.987;
            tes_dm0_lowpt_uncer = 0.01;
            tes_dm1_lowpt_uncer = 0.006;
            tes_dm10_lowpt_uncer = 0.007;
            tes_dm11_lowpt_uncer = 0.014;
            tes_dm0_highpt_uncer = 0.03;
            tes_dm1_highpt_uncer = 0.027;
            tes_dm10_highpt_uncer = 0.017;
            tes_dm11_highpt_uncer = 0.04;
        }
        if (year=="2016"){
            tes_dm0_cent = 0.991;
            tes_dm1_cent = 0.999;
            tes_dm10_cent = 1.003;
            tes_dm11_cent = 0.998;
            tes_dm0_lowpt_uncer = 0.008;
            tes_dm1_lowpt_uncer = 0.006;
            tes_dm10_lowpt_uncer = 0.008;
            tes_dm11_lowpt_uncer = 0.011;
            tes_dm0_highpt_uncer = 0.03;
            tes_dm1_highpt_uncer = 0.02;
            tes_dm10_highpt_uncer = 0.012;
            tes_dm11_highpt_uncer = 0.027;
        }
        //define TES factors to apply, which uncorrect central and recorrect with shifted tes, split by DM and 3 pt bins
        //dm0
        float tes_dm0_lowpt_up = 1.0 + tes_dm0_lowpt_uncer/tes_dm0_cent;//for pt_2<34
        float tes_dm0_highpt_up = 1.0 + tes_dm0_highpt_uncer/tes_dm0_cent;//for pt_2>170
        float tes_dm0_midpt_up = 1.0 + (tes_dm0_lowpt_uncer+(tes_dm0_highpt_uncer-tes_dm0_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm0_cent;//interpolated in between
        float tes_dm0_lowpt_down = 1.0 - tes_dm0_lowpt_uncer/tes_dm0_cent;
        float tes_dm0_highpt_down = 1.0 - tes_dm0_highpt_uncer/tes_dm0_cent;
        float tes_dm0_midpt_down = 1.0 - (tes_dm0_lowpt_uncer+(tes_dm0_highpt_uncer-tes_dm0_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm0_cent;
        //dm1
        float tes_dm1_lowpt_up = 1.0 + tes_dm1_lowpt_uncer/tes_dm1_cent;//for pt_2<34
        float tes_dm1_highpt_up = 1.0 + tes_dm1_highpt_uncer/tes_dm1_cent;//for pt_2>170
        float tes_dm1_midpt_up = 1.0 + (tes_dm1_lowpt_uncer+(tes_dm1_highpt_uncer-tes_dm1_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm1_cent;//interpolated in between
        float tes_dm1_lowpt_down = 1.0 - tes_dm1_lowpt_uncer/tes_dm1_cent;
        float tes_dm1_highpt_down = 1.0 - tes_dm1_highpt_uncer/tes_dm1_cent;
        float tes_dm1_midpt_down = 1.0 - (tes_dm1_lowpt_uncer+(tes_dm1_highpt_uncer-tes_dm1_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm1_cent;
        //dm10
        float tes_dm10_lowpt_up = 1.0 + tes_dm10_lowpt_uncer/tes_dm10_cent;//for pt_2<34
        float tes_dm10_highpt_up = 1.0 + tes_dm10_highpt_uncer/tes_dm10_cent;//for pt_2>170
        float tes_dm10_midpt_up = 1.0 + (tes_dm10_lowpt_uncer+(tes_dm10_highpt_uncer-tes_dm10_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm10_cent;//interpolated in between
        float tes_dm10_lowpt_down = 1.0 - tes_dm10_lowpt_uncer/tes_dm10_cent;
        float tes_dm10_highpt_down = 1.0 - tes_dm10_highpt_uncer/tes_dm10_cent;
        float tes_dm10_midpt_down = 1.0 - (tes_dm10_lowpt_uncer+(tes_dm10_highpt_uncer-tes_dm10_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm10_cent;
        //dm11
        float tes_dm11_lowpt_up = 1.0 + tes_dm11_lowpt_uncer/tes_dm11_cent;//for pt_2<34
        float tes_dm11_highpt_up = 1.0 + tes_dm11_highpt_uncer/tes_dm11_cent;//for pt_2>170
        float tes_dm11_midpt_up = 1.0 + (tes_dm11_lowpt_uncer+(tes_dm11_highpt_uncer-tes_dm11_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm11_cent;//interpolated in between
        float tes_dm11_lowpt_down = 1.0 - tes_dm11_lowpt_uncer/tes_dm11_cent;
        float tes_dm11_highpt_down = 1.0 - tes_dm11_highpt_uncer/tes_dm11_cent;
        float tes_dm11_midpt_down = 1.0 - (tes_dm11_lowpt_uncer+(tes_dm11_highpt_uncer-tes_dm11_lowpt_uncer)*(pt_2-34.0)/(170.0-34.0))/tes_dm11_cent;
        
        float tes_dm0_up = tes_dm0_lowpt_up;
        float tes_dm0_down = tes_dm0_lowpt_down;
        float tes_dm1_up = tes_dm1_lowpt_up;
        float tes_dm1_down = tes_dm1_lowpt_down;
        float tes_dm10_up = tes_dm10_lowpt_up;
        float tes_dm10_down = tes_dm10_lowpt_down;
        float tes_dm11_up = tes_dm11_lowpt_up;
        float tes_dm11_down = tes_dm11_lowpt_down;
        if (pt_2>34.0 && pt_2<=170.0){
            tes_dm0_up = tes_dm0_midpt_up;
            tes_dm0_down = tes_dm0_midpt_down;
            tes_dm1_up = tes_dm1_midpt_up;
            tes_dm1_down = tes_dm1_midpt_down;
            tes_dm10_up = tes_dm10_midpt_up;
            tes_dm10_down = tes_dm10_midpt_down;
            tes_dm11_up = tes_dm11_midpt_up;
            tes_dm11_down = tes_dm11_midpt_down;
        }
        if (pt_2>170.0){
            tes_dm0_up = tes_dm0_highpt_up;
            tes_dm0_down = tes_dm0_highpt_down;
            tes_dm1_up = tes_dm1_highpt_up;
            tes_dm1_down = tes_dm1_highpt_down;
            tes_dm10_up = tes_dm10_highpt_up;
            tes_dm10_down = tes_dm10_highpt_down;
            tes_dm11_up = tes_dm11_highpt_up;
            tes_dm11_down = tes_dm11_highpt_down;
        }
        if (sample=="embedded" && year=="2018"){
            tes_dm0_up = 1.0039;
            tes_dm0_down = 0.9961;
            tes_dm1_up = 1.0037;
            tes_dm1_down = 0.9969;
            tes_dm10_up = 1.0032;
            tes_dm10_down = 0.9968;
            tes_dm11_up = 1.0032;
            tes_dm11_down = 0.9968;
        }
        if (sample=="embedded" && year=="2017"){
            tes_dm0_up = 1.0041;
            tes_dm0_down = 0.9958;
            tes_dm1_up = 1.0052;
            tes_dm1_down = 0.9979;
            tes_dm10_up = 1.0044;
            tes_dm10_down = 0.9954;
            tes_dm11_up = 1.0044;
            tes_dm11_down = 0.9954;
        }
        if (sample=="embedded" && year=="2016"){
            tes_dm0_up = 1.0046;
            tes_dm0_down = 0.9954;
            tes_dm1_up = 1.0022;
            tes_dm1_down = 0.9975;
            tes_dm10_up = 1.0033;
            tes_dm10_down = 0.9949;
            tes_dm11_up = 1.0033;
            tes_dm11_down = 0.9949;
        }
        float tauES_real[8] = {tes_dm0_up,tes_dm0_down,tes_dm1_up,tes_dm1_down,tes_dm10_up,tes_dm10_down,tes_dm11_up,tes_dm11_down};//mytau already had nominal tes correction applied at skimming level
        float taudecaymode[4] = {0,1,10,11};
        for (int j = 0; j < 4; j++){
            if (gen_match_2==5 && l2_decayMode==taudecaymode[j]){
                //[0]dm0up, [1]dm0down, [2]dm1up, [3]dm1down, [4]dm10up, [5]dm10down, [6]dm11up, [7]dm11down
                myshiftedtau[2*j] *= tauES_real[2*j];
                myshiftedtau[2*j+1] *= tauES_real[2*j+1];
                
                mymet_shiftedtau[2*j] = mymet + mytau - myshiftedtau[2*j];
                mymet_shiftedtau[2*j+1] = mymet + mytau - myshiftedtau[2*j+1];
                
                mytt_shiftedtau[2*j].SetPtEtaPhiM((myele+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Pt(),(myele+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Eta(),(myele+myshiftedtau[2*j]+mymet_shiftedtau[2*j]).Phi(),m_sv_UP);
                mytt_shiftedtau[2*j+1].SetPtEtaPhiM((myele+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Pt(),(myele+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Eta(),(myele+myshiftedtau[2*j+1]+mymet_shiftedtau[2*j+1]).Phi(),m_sv_DOWN);
                
                m_btt_shiftedtau[2*j] = (mytt_shiftedtau[2*j]+myb1).M();
                m_btt_shiftedtau[2*j+1] = (mytt_shiftedtau[2*j+1]+myb1).M();
                
                m_bbtt_shiftedtau[2*j] = (mytt_shiftedtau[2*j]+myb1+myb2).M();
                m_bbtt_shiftedtau[2*j+1] = (mytt_shiftedtau[2*j+1]+myb1+myb2).M();
            }
        }
        float NN1b_tes[8] = {NN1b_Up,NN1b_Down,NN1b_Up,NN1b_Down,NN1b_Up,NN1b_Down,NN1b_Up,NN1b_Down};
        float NN2b_tes[8] = {NN2b_Up,NN2b_Down,NN2b_Up,NN2b_Down,NN2b_Up,NN2b_Down,NN2b_Up,NN2b_Down};
        for (int j = 0; j < 8; j++){
            var[0][0][j+1] = NN1b_tes[j];
            var[0][1][j+1] = p_n(NN1b_tes[j],p_N);
            var[0][2][j+1] = p_n(NN1b_tes[j],p_N);
            var[0][4][j+1] = myshiftedtau[j].Pt();
            var[0][5][j+1] = mytt_shiftedtau[j].M();
            var[0][6][j+1] = m_btt_shiftedtau[j];
            
            var[1][0][j+1] = NN2b_tes[j];
            var[1][1][j+1] = p_n(NN2b_tes[j],p_N);
            var[1][2][j+1] = p_n(NN2b_tes[j],p_N);
            var[1][4][j+1] = myshiftedtau[j].Pt();
            var[1][5][j+1] = mytt_shiftedtau[j].M();
            var[1][6][j+1] = m_btt_shiftedtau[j];
            var[1][7][j+1] = m_bbtt_shiftedtau[j];
        }
        
        //###################tauId scale factors#######################
        std::vector<float> sf_tauid;
        for (int j = 0; j < 23; ++j){//j=0 nominal, 1-14 shifted sf, 15-22 shifted tau
            sf_tauid.push_back(1.0);
        }
        if (sample!="data_obs" && byMediumDeepVSjet_2 && gen_match_2==5){
            //nominal
            sf_tauid[0] = fct_tauid_nominal->Eval(pt_2);
            //shifted tauID scale factors evaluated at nominal tau pt
            float tauid_ptbins[8] = {20,25,30,35,40,500,1000,10000};
            for (int j = 0; j < 7; j++){
                if (pt_2>tauid_ptbins[j] && pt_2<=tauid_ptbins[j+1]){
                    sf_tauid[2*j+1] = fct_tauid_up->Eval(pt_2);
                    sf_tauid[2*j+2] = fct_tauid_down->Eval(pt_2);
                }
                else{
                    sf_tauid[2*j+1] = fct_tauid_nominal->Eval(pt_2);
                    sf_tauid[2*j+2] = fct_tauid_nominal->Eval(pt_2);
                }
            }
            //nominal tauID scale factors evaluated with shifted tau ES
            for (int j = 0; j < 8; j++){
                sf_tauid[15+j] = fct_tauid_nominal->Eval(myshiftedtau[j].Pt());
            }
        }
        //different WP than used in measurement
        float tauidWP[2] = {1.0,1.0};
        if (sample!="data_obs" && byMediumDeepVSjet_2 && gen_match_2==5 && pt_2<100){
            tauidWP[0] = 1.03;
            tauidWP[1] = 0.97;
            if (sample=="embedded"){
                tauidWP[0] = 1.05;
                tauidWP[1] = 0.95;
            }
        }
        
        //####################tauID SF anti-lepton#####################
        //e faking tauh SF
        std::vector<float> sf_tauid_efake;
        for (int j = 0; j < 4; j++){
            sf_tauid_efake.push_back(1.0);
        }//[0/1]:fabs(eta_2)<1.46 up/down, [2,3]:fabs(eta_2)>1.56 up/down
        if (sample!="data_obs" && sample!="embedded" && (gen_match_2==1 or gen_match_2==3)){
            if (fabs(eta_2)<1.46){
                //up
                sf_tauid_efake[0] = 1.0 + 0.27/taufakesf;
                if (year=="2017") sf_tauid_efake[0] = 1.0 + 0.32/taufakesf;
                if (year=="2016") sf_tauid_efake[0] = 1.0 + 0.38/taufakesf;
                //down
                sf_tauid_efake[1] = 1.0 - 0.27/taufakesf;
                if (year=="2017") sf_tauid_efake[1] = 1.0 - 0.32/taufakesf;
                if (year=="2016") sf_tauid_efake[1] = 1.0 - 0.38/taufakesf;
            }
            if (fabs(eta_2)>1.56){
                //up
                sf_tauid_efake[2] = 1.0 + 0.2/taufakesf;
                if (year=="2017") sf_tauid_efake[2] = 1.0 + 0.38/taufakesf;
                if (year=="2016") sf_tauid_efake[2] = 1.0 + 0.32/taufakesf;
                //down
                sf_tauid_efake[3] = 1.0 - 0.2/taufakesf;
                if (year=="2017") sf_tauid_efake[3] = 1.0 - 0.38/taufakesf;
                if (year=="2016") sf_tauid_efake[3] = 1.0 - 0.32/taufakesf;
            }
        }
        //mu faking tauh SF
        std::vector<float> sf_tauid_mufake;
        for (int j = 0; j < 10; j++){
            sf_tauid_mufake.push_back(1.0);
        }
        if (sample!="data_obs" && sample!="embedded" && (gen_match_2==2 or gen_match_2==4)){
            if (fabs(eta_2)<0.4){
                //up
                sf_tauid_mufake[0] = 1.0 + 0.069/taufakesf;
                if (year=="2017") sf_tauid_mufake[0] = 1.0 + 0.075/taufakesf;
                if (year=="2016") sf_tauid_mufake[0] = 1.0 + 0.067/taufakesf;
                //down
                sf_tauid_mufake[1] = 1.0 - 0.069/taufakesf;
                if (year=="2017") sf_tauid_mufake[1] = 1.0 - 0.075/taufakesf;
                if (year=="2016") sf_tauid_mufake[1] = 1.0 - 0.067/taufakesf;
            }
            else if (fabs(eta_2)<0.8){
                //up
                sf_tauid_mufake[2] = 1.0 + 0.098/taufakesf;
                if (year=="2017") sf_tauid_mufake[2] = 1.0 + 0.074/taufakesf;
                if (year=="2016") sf_tauid_mufake[2] = 1.0 + 0.122/taufakesf;
                //down
                sf_tauid_mufake[3] = 1.0 - 0.098/taufakesf;
                if (year=="2017") sf_tauid_mufake[3] = 1.0 - 0.074/taufakesf;
                if (year=="2016") sf_tauid_mufake[3] = 1.0 - 0.122/taufakesf;
            }
            else if (fabs(eta_2)<1.2){
                //up
                sf_tauid_mufake[4] = 1.0 + 0.075/taufakesf;
                if (year=="2017") sf_tauid_mufake[4] = 1.0 + 0.077/taufakesf;
                if (year=="2016") sf_tauid_mufake[4] = 1.0 + 0.104/taufakesf;
                //down
                sf_tauid_mufake[5] = 1.0 - 0.075/taufakesf;
                if (year=="2017") sf_tauid_mufake[5] = 1.0 - 0.077/taufakesf;
                if (year=="2016") sf_tauid_mufake[5] = 1.0 - 0.104/taufakesf;
            }
            else if (fabs(eta_2)<1.7){
                //up
                sf_tauid_mufake[6] = 1.0 + 0.145/taufakesf;
                if (year=="2017") sf_tauid_mufake[6] = 1.0 + 0.128/taufakesf;
                if (year=="2016") sf_tauid_mufake[6] = 1.0 + 0.160/taufakesf;
                //down
                sf_tauid_mufake[7] = 1.0 - 0.145/taufakesf;
                if (year=="2017") sf_tauid_mufake[7] = 1.0 - 0.128/taufakesf;
                if (year=="2016") sf_tauid_mufake[7] = 1.0 - 0.160/taufakesf;
            }
            else {
                //up
                sf_tauid_mufake[8] = 1.0 + 0.377/taufakesf;
                if (year=="2017") sf_tauid_mufake[8] = 1.0 + 0.344/taufakesf;
                if (year=="2016") sf_tauid_mufake[8] = 1.0 + 0.341/taufakesf;
                //down
                sf_tauid_mufake[9] = 1.0 - 0.377/taufakesf;
                if (year=="2017") sf_tauid_mufake[9] = 1.0 - 0.344/taufakesf;
                if (year=="2016") sf_tauid_mufake[9] = 1.0 - 0.341/taufakesf;
            }
        }
        
        //########################muon faking tau ES shifting##########################
        std::vector<TLorentzVector> mytau_isgenmu;
        std::vector<TLorentzVector> mymet_isgenmu;
        std::vector<TLorentzVector> mytt_isgenmu;
        std::vector<float> m_btt_isgenmu;
        std::vector<float> m_bbtt_isgenmu;
        for (int j = 0; j < 4; j++){
            mytau_isgenmu.push_back(mytau);
            mymet_isgenmu.push_back(mymet);
            mytt_isgenmu.push_back(mytt);
            m_btt_isgenmu.push_back(m_btt);
            m_bbtt_isgenmu.push_back(m_bbtt);
        }//ordered by: dm0up, dm0down, dm1up, dm1down
        float tauES_mufake[4] = {1.01,0.99,1.01,0.99};//nominal ES correction for muon->tau = 1.0
        if (gen_match_2==2 or gen_match_2==4){
            for (int j = 0; j < 2; j++){
                if (l2_decayMode==taudecaymode[j]){
                    //mytau
                    mytau_isgenmu[2*j] *= tauES_mufake[2*j];
                    mytau_isgenmu[2*j+1] *= tauES_mufake[2*j+1];
                    //mymet
                    mymet_isgenmu[2*j] = mymet + mytau - mytau_isgenmu[2*j];
                    mymet_isgenmu[2*j+1] = mymet + mytau - mytau_isgenmu[2*j+1];
                    //mytt
                    mytt_isgenmu[2*j].SetPtEtaPhiM((myele+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Pt(),(myele+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Eta(),(myele+mytau_isgenmu[2*j]+mymet_isgenmu[2*j]).Phi(),m_sv_UP);
                    mytt_isgenmu[2*j+1].SetPtEtaPhiM((myele+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Pt(),(myele+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Eta(),(myele+mytau_isgenmu[2*j+1]+mymet_isgenmu[2*j+1]).Phi(),m_sv_DOWN);
                    m_btt_isgenmu[2*j] = (mytt_isgenmu[2*j]+myb1).M();
                    m_btt_isgenmu[2*j+1] = (mytt_isgenmu[2*j+1]+myb1).M();
                    m_bbtt_isgenmu[2*j] = (mytt_isgenmu[2*j]+myb1+myb2).M();
                    m_bbtt_isgenmu[2*j+1] = (mytt_isgenmu[2*j+1]+myb1+myb2).M();
                }
            }
        }
        for (int j = 0; j < 4; j++){
            var[0][0][j+9] = NN1b_tes[j];
            var[0][1][j+9] = p_n(NN1b_tes[j],p_N);
            var[0][2][j+9] = p_n(NN1b_tes[j],p_N);
            var[0][4][j+9] = mytau_isgenmu[j].Pt();
            var[0][5][j+9] = mytt_isgenmu[j].M();
            var[0][6][j+9] = m_btt_isgenmu[j];
            
            var[1][0][j+9] = NN2b_tes[j];
            var[1][1][j+9] = p_n(NN2b_tes[j],p_N);
            var[1][2][j+9] = p_n(NN2b_tes[j],p_N);
            var[1][4][j+9] = mytau_isgenmu[j].Pt();
            var[1][5][j+9] = mytt_isgenmu[j].M();
            var[1][6][j+9] = m_btt_isgenmu[j];
            var[1][7][j+9] = m_bbtt_isgenmu[j];
        }
        
        //########################electron faking tauh ES shifting#######################
        std::vector<TLorentzVector> mytau_isgenele;
        std::vector<TLorentzVector> mymet_isgenele;
        std::vector<TLorentzVector> mytt_isgenele;
        std::vector<float> m_btt_isgenele;
        std::vector<float> m_bbtt_isgenele;
        for (int j = 0; j < 4; j++){
            mytau_isgenele.push_back(mytau);
            mymet_isgenele.push_back(mymet);
            mytt_isgenele.push_back(mytt);
            m_btt_isgenele.push_back(m_btt);
            m_bbtt_isgenele.push_back(m_bbtt);
        }//ordering: dm0up, dm0down, dm1up, dm1down
        float tauES_elefake[8] = {1.02266/1.01362,1.00888/1.01362,1.00307/0.96903,0.95653/0.96903,1.03171/1.01945,1.00347/1.01945,1.03999/0.985,0.94191/0.985};
        float tauES_elefake2017[8] = {1.02254/1.00911,1.00029/1.00911,0.99645/0.97396,0.95966/0.97396,1.03316/1.01154,1.00181/1.01154,1.07961/1.015,0.96531/1.015};
        float tauES_elefake2016[8] = {1.01485/1.00679,0.99697/1.00679,0.98308/0.965,0.95398/0.965,1.04557/1.03389,1.00914/1.03389,1.1157/1.05,0.99306/1.05};//ordering: dm0barup, dm0bardown, dm0endup, dm0enddown, dm1barup, dm1bardown, dm1endup, dm1enddown
        for (int j = 0; j < 8; j++){
            if (year=="2017") tauES_elefake[j] = tauES_elefake2017[j];
            if (year=="2016") tauES_elefake[j] = tauES_elefake2016[j];
        }
        if (gen_match_2==1 or gen_match_2==3){
            for (int j = 0; j < 2; j++){
                if (l2_decayMode==taudecaymode[j]){//j=0 DM=0, j=1 DM=1
                    if (fabs(eta_2)<1.5){//barrel
                        //mytau
                        mytau_isgenele[2*j] *= tauES_elefake[4*j];
                        mytau_isgenele[2*j+1] *= tauES_elefake[4*j+1];
                    }
                    else {//endcap
                        //mytau
                        mytau_isgenele[2*j] *= tauES_elefake[4*j+2];
                        mytau_isgenele[2*j+1] *= tauES_elefake[4*j+3];
                    }
                    //mymet
                    mymet_isgenele[2*j] = mymet + mytau - mytau_isgenele[2*j];
                    mymet_isgenele[2*j+1] = mymet + mytau - mytau_isgenele[2*j+1];
                    //mytt
                    mytt_isgenele[2*j].SetPtEtaPhiM((myele+mytau_isgenele[2*j]+mymet_isgenele[2*j]).Pt(),(myele+mytau_isgenele[2*j]+mymet_isgenele[2*j]).Eta(),(myele+mytau_isgenele[2*j]+mymet_isgenele[2*j]).Phi(),m_sv_UP);
                    mytt_isgenele[2*j+1].SetPtEtaPhiM((myele+mytau_isgenele[2*j+1]+mymet_isgenele[2*j+1]).Pt(),(myele+mytau_isgenele[2*j+1]+mymet_isgenele[2*j+1]).Eta(),(myele+mytau_isgenele[2*j+1]+mymet_isgenele[2*j+1]).Phi(),m_sv_DOWN);
                    
                    m_btt_isgenele[2*j] = (mytt_isgenele[2*j]+myb1).M();
                    m_btt_isgenele[2*j+1] = (mytt_isgenele[2*j+1]+myb1).M();
                    
                    m_bbtt_isgenele[2*j] = (mytt_isgenele[2*j]+myb1+myb2).M();
                    m_bbtt_isgenele[2*j+1] = (mytt_isgenele[2*j+1]+myb1+myb2).M();
                }
            }
        }
        for (int j = 0; j < 4; j++){
            var[0][0][j+13] = NN1b_tes[j];
            var[0][1][j+13] = p_n(NN1b_tes[j],p_N);
            var[0][2][j+13] = p_n(NN1b_tes[j],p_N);
            var[0][4][j+13] = mytau_isgenele[j].Pt();
            var[0][5][j+13] = mytt_isgenele[j].M();
            var[0][6][j+13] = m_btt_isgenele[j];
            
            var[1][0][j+13] = NN2b_tes[j];
            var[1][1][j+13] = p_n(NN2b_tes[j],p_N);
            var[1][2][j+13] = p_n(NN2b_tes[j],p_N);
            var[1][4][j+13] = mytau_isgenele[j].Pt();
            var[1][5][j+13] = mytt_isgenele[j].M();
            var[1][6][j+13] = m_btt_isgenele[j];
            var[1][7][j+13] = m_bbtt_isgenele[j];
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
        float eleES[4] = {1.005,0.995,1.0125,0.9875};//ordering: barrel up/down, endcap up/down (only for emb)
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
                mytt_shiftedele[2*j].SetPtEtaPhiM((myshiftedele[2*j]+mytau+mymet_shiftedele[2*j]).Pt(),(myshiftedele[2*j]+mytau+mymet_shiftedele[2*j]).Eta(),(myshiftedele[2*j]+mytau+mymet_shiftedele[2*j]).Phi(),m_sv_ESCALEUP);
                mytt_shiftedele[2*j+1].SetPtEtaPhiM((myshiftedele[2*j+1]+mytau+mymet_shiftedele[2*j+1]).Pt(),(myshiftedele[2*j+1]+mytau+mymet_shiftedele[2*j+1]).Eta(),(myshiftedele[2*j+1]+mytau+mymet_shiftedele[2*j+1]).Phi(),m_sv_ESCALEDOWN);
                
                m_btt_shiftedele[2*j] = (mytt_shiftedele[2*j]+myb1).M();
                m_btt_shiftedele[2*j+1] = (mytt_shiftedele[2*j+1]+myb1).M();
                
                m_bbtt_shiftedele[2*j] = (mytt_shiftedele[2*j]+myb1+myb2).M();
                m_bbtt_shiftedele[2*j+1] = (mytt_shiftedele[2*j+1]+myb1+myb2).M();
            }
        }
        float NN1b_eleES[4] = {NN1b_ESCALEUP,NN1b_ESCALEDOWN,NN1b_ESCALEUP,NN1b_ESCALEDOWN};
        float NN2b_eleES[4] = {NN2b_ESCALEUP,NN2b_ESCALEDOWN,NN2b_ESCALEUP,NN2b_ESCALEDOWN};
        for (int j = 0; j < 4; j++){
            var[0][0][j+17] = NN1b_eleES[j];
            var[0][1][j+17] = p_n(NN1b_eleES[j],p_N);
            var[0][2][j+17] = p_n(NN1b_eleES[j],p_N);
            var[0][3][j+17] = myshiftedele[j].Pt();
            var[0][5][j+17] = mytt_shiftedele[j].M();
            var[0][6][j+17] = m_btt_shiftedele[j];
            
            var[1][0][j+17] = NN2b_eleES[j];
            var[1][1][j+17] = p_n(NN2b_eleES[j],p_N);
            var[1][2][j+17] = p_n(NN2b_eleES[j],p_N);
            var[1][3][j+17] = myshiftedele[j].Pt();
            var[1][5][j+17] = mytt_shiftedele[j].M();
            var[1][6][j+17] = m_btt_shiftedele[j];
            var[1][7][j+17] = m_bbtt_shiftedele[j];
        }
        
        //###################re-apply trigger scale factor for re-defined single/cross trigger regions due to shifted muon####################
        //define trigger sf with nominal ele ES (the usual weights)
        float trgsf = 1.0;
        float trgsf_single = 1.0;
        float trgsf_cross = 1.0;
        float trgsf_17emb_single1 = 1.0;
        float trgsf_17emb_single2 = 1.0;
        float trgsf_17emb_cross1 = 1.0;
        float trgsf_17emb_cross2 = 1.0;
        if (sample!="data_obs"){
            if (year=="2018"){
                if (sample!="embedded"){
                    trgsf_single = e_trg_ic_ratio;
                    trgsf_cross = e_trg_24_ic_ratio * t_trg_pog_deeptau_medium_etau_ratio;
                }
                if (sample=="embedded"){
                    trgsf_single = e_trg_ic_embed_ratio;
                    trgsf_cross = e_trg_24_ic_embed_ratio * t_trg_mediumDeepTau_etau_embed_ratio;
                }
            }
            if (year=="2017"){
                if (sample!="embedded"){
                    trgsf_single = e_trg_ic_ratio;
                    trgsf_cross = e_trg_24_ic_ratio * t_trg_pog_deeptau_medium_etau_ratio;
                }
                if (sample=="embedded"){
                    trgsf_17emb_single1 = e_trg_ic_embed_ratio;
                    trgsf_17emb_single2 = e_trg_ic_data;
                    trgsf_17emb_cross1 = e_trg_24_ic_embed_ratio * et_emb_LooseChargedIsoPFTau30_kit_ratio;
                    trgsf_17emb_cross2 = e_trg_24_ic_data * t_trg_mediumDeepTau_etau_data;
                }
            }
            if (year=="2016"){
                if (sample!="embedded"){
                    trgsf_single = e_trg_ic_ratio;
                }
                if (sample=="embedded"){
                    trgsf_single = e_trg_ic_embed_ratio;
                }
            }
        }
        if (isSingleTrigger && pt_1>single_elept_thres) trgsf = trgsf_single;
        if (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres) trgsf = trgsf_cross;
        if (year=="2017" && sample=="embedded"){
            if (fabs(eta_1)<1.479 or (fabs(eta_1)>1.479 && pt_1>40)){
                if (isSingleTrigger && pt_1>single_elept_thres) trgsf = trgsf_17emb_single1;
                if (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres) trgsf = trgsf_17emb_cross1;
            }
            if (fabs(eta_1)>1.479 && pt_1<40){
                if (isSingleTrigger && pt_1>single_elept_thres) trgsf = trgsf_17emb_single2;
                if (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres) trgsf = trgsf_17emb_cross2;
            }
        }
        
        //for shifted trigger regions due to shifted electron ES
        std::vector<float> trgsf_shiftedele;
        for (int j = 0; j < 4; j++){
            trgsf_shiftedele.push_back(1.0);
            if (isSingleTrigger && myshiftedele[j].Pt()>single_elept_thres) trgsf_shiftedele[j] = trgsf_single;
            if (isCrossTrigger && myshiftedele[j].Pt()<single_elept_thres && myshiftedele[j].Pt()>cross_elept_thres) trgsf_shiftedele[j] = trgsf_cross;
            if (year=="2017" && sample=="embedded"){
                if (fabs(eta_1)<1.479 or (fabs(eta_1)>1.479 && myshiftedele[j].Pt()>40)){
                    if (isSingleTrigger && myshiftedele[j].Pt()>single_elept_thres) trgsf_shiftedele[j] = trgsf_17emb_single1;
                    if (isCrossTrigger && myshiftedele[j].Pt()<single_elept_thres && myshiftedele[j].Pt()>cross_elept_thres) trgsf_shiftedele[j] = trgsf_17emb_cross1;
                }
                if (fabs(eta_1)>1.479 && myshiftedele[j].Pt()<40){
                    if (isSingleTrigger && myshiftedele[j].Pt()>single_elept_thres) trgsf_shiftedele[j] = trgsf_17emb_single2;
                    if (isCrossTrigger && myshiftedele[j].Pt()<single_elept_thres && myshiftedele[j].Pt()>cross_elept_thres) trgsf_shiftedele[j] = trgsf_17emb_cross2;
                }
            }
        }
        
        //############################trigger sf shifting################################
        std::vector<float> trigger_shiftedsf;
        for (int j = 0; j < 4; j++){
            trigger_shiftedsf.push_back(1.0);//=1.0 do not shift by default
        }//[0]:single_up, [1]:single_down, [2]:cross_up, [3]:cross_down
        if (sample!="data_obs"){
            if (isSingleTrigger && pt_1>single_elept_thres){//single lepton, same updown 2% for both MC and emb
                trigger_shiftedsf[0] = 1.02;
                trigger_shiftedsf[1] = 0.98;
            }
            if (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres){
                if (sample!="embedded"){//MC
                    trigger_shiftedsf[2] = t_trg_pog_deeptau_medium_etau_ratio_up/t_trg_pog_deeptau_medium_etau_ratio;
                    trigger_shiftedsf[3] = t_trg_pog_deeptau_medium_etau_ratio_down/t_trg_pog_deeptau_medium_etau_ratio;
                }
                if (sample=="embedded"){
                    if (year!="2017"){
                        trigger_shiftedsf[2] = t_trg_mediumDeepTau_etau_embed_ratio_up/t_trg_mediumDeepTau_etau_embed_ratio;
                        trigger_shiftedsf[3] = t_trg_mediumDeepTau_etau_embed_ratio_down/t_trg_mediumDeepTau_etau_embed_ratio;
                    }
                    if (year=="2017"){
                        if (fabs(eta_1)<1.479){
                            trigger_shiftedsf[2] = 1;
                            trigger_shiftedsf[3] = 1;
                        }
                        else {
                            trigger_shiftedsf[2] = 1;
                            trigger_shiftedsf[3] = 1;
                        }
                    }
                }
            }
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
            mytt_jet[j].SetPtEtaPhiM((myele+mytau+mymet_jet[j]).Pt(),(myele+mytau+mymet_jet[j]).Eta(),(myele+mytau+mymet_jet[j]).Phi(),m_sv_jetvar[j]);
            myb1_jet[j].SetPtEtaPhiM(bpt_1_jetvar[j],beta_deepflavour_1,bphi_deepflavour_1,bm_deepflavour_1);
            myb2_jet[j].SetPtEtaPhiM(bpt_2_jetvar[j],beta_deepflavour_2,bphi_deepflavour_2,bm_deepflavour_2);
            m_btt_jet.push_back((mytt_jet[j]+myb1_jet[j]).M());
            m_bbtt_jet.push_back((mytt_jet[j]+myb1_jet[j]+myb2_jet[j]).M());
        }
        for (int j = 0; j < 24; j++){
            var[0][0][j+21] = NN1b_jetvar[j];
            var[0][1][j+21] = p_n(NN1b_jetvar[j],p_N);
            var[0][2][j+21] = p_n(NN1b_jetvar[j],p_N);
            //var[0][0][j+21] = NN1b;
            //var[0][1][j+21] = p_n(NN1b,p_N);
            //var[0][2][j+21] = p_n(NN1b,p_N);
            var[0][5][j+21] = mytt_jet[j].M();
            var[0][6][j+21] = m_btt_jet[j];
            
            var[1][0][j+21] = NN2b_jetvar[j];
            var[1][1][j+21] = p_n(NN2b_jetvar[j],p_N);
            var[1][2][j+21] = p_n(NN2b_jetvar[j],p_N);
            //var[1][0][j+21] = NN2b;
            //var[1][1][j+21] = p_n(NN2b,p_N);
            //var[1][2][j+21] = p_n(NN2b,p_N);
            var[1][5][j+21] = mytt_jet[j].M();
            var[1][6][j+21] = m_btt_jet[j];
            var[1][7][j+21] = m_bbtt_jet[j];
        }
        
        //re-count nbtag20 and re-compute btag sf with shifted jet ES
        std::vector<int> nbtag20_jetsyst;
        std::vector<float> weight_btag_jetsyst;
        std::vector<std::string> btagSFvariations_JESandJERonly = {//11 JES-varied SFs provided, not including JER (use central instead), to be applied to both b and udsg jets with the JES/JER-varied jet templates
            "up_jesAbsolute",               "down_jesAbsolute",
            "up_jesAbsolute_"+year,         "down_jesAbsolute_"+year,
            "up_jesBBEC1",                  "down_jesBBEC1",
            "up_jesBBEC1_"+year,            "down_jesBBEC1_"+year,
            "up_jesEC2",                    "down_jesEC2",
            "up_jesEC2_"+year,              "down_jesEC2_"+year,
            "up_jesFlavorQCD",              "down_jesFlavorQCD",
            "up_jesHF",                     "down_jesHF",
            "up_jesHF_"+year,               "down_jesHF_"+year,
            "up_jesRelativeBal",            "down_jesRelativeBal",
            "up_jesRelativeSample_"+year,   "down_jesRelativeSample_"+year,
            "central",                      "central"//for JER
        };
        for (int j = 0; j < 24; j++){
            nbtag20_jetsyst.push_back(0);
            if (bpt_1_jetvar[j]>20 && bscore_deepflavour_1>bscore_thres && fabs(beta_deepflavour_1)<2.4){
                nbtag20_jetsyst[j]++;
            }
            if (bpt_2_jetvar[j]>20 && bscore_deepflavour_2>bscore_thres && fabs(beta_deepflavour_2)<2.4){
                nbtag20_jetsyst[j]++;
            }
            weight_btag_jetsyst.push_back(1);//apply jes-varied SFs (only for b and udsg jets; for c jets use central which is flat 1.0) to jes-varied jet templates (not to nominal jet templates)
            if (sample!="data_obs" && sample!="embedded"){
                if (nbtag20_jetsyst[j]==1){
                    if (btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG){
                        weight_btag_jetsyst[j] = reader.eval_auto_bounds(btagSFvariations_JESandJERonly[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_1_jetvar[j], bscore_deepflavour_1);
                    }
                    else if (btagflavour_1==BTagEntry::FLAV_C){
                        weight_btag_jetsyst[j] = 1.0;
                    }
                }
                if (nbtag20_jetsyst[j]==2){
                    if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                        weight_btag_jetsyst[j] = reader.eval_auto_bounds(btagSFvariations_JESandJERonly[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_1_jetvar[j], bscore_deepflavour_1)*reader.eval_auto_bounds(btagSFvariations_JESandJERonly[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_2_jetvar[j], bscore_deepflavour_2);
                    }
                    else if ((btagflavour_1==BTagEntry::FLAV_B or btagflavour_1==BTagEntry::FLAV_UDSG) and btagflavour_2==BTagEntry::FLAV_C){
                        weight_btag_jetsyst[j] = reader.eval_auto_bounds(btagSFvariations_JESandJERonly[j], btagflavour_1, fabs(beta_deepflavour_1), bpt_1_jetvar[j], bscore_deepflavour_1)*1.0;
                    }
                    else if (btagflavour_1==BTagEntry::FLAV_C and (btagflavour_2==BTagEntry::FLAV_B or btagflavour_2==BTagEntry::FLAV_UDSG)){
                        weight_btag_jetsyst[j] = 1.0*reader.eval_auto_bounds(btagSFvariations_JESandJERonly[j], btagflavour_2, fabs(beta_deepflavour_2), bpt_2_jetvar[j], bscore_deepflavour_2);
                    }
                    else if (btagflavour_1==BTagEntry::FLAV_C and btagflavour_2==BTagEntry::FLAV_C){
                        weight_btag_jetsyst[j] = 1.0;
                    }
                }
                if (nbtag20==0) weight_btag_jetsyst[j] *= 1.0;
                if (nbtag20==1) weight_btag_jetsyst[j] *= 1.0/weight_btag_1b;
                if (nbtag20==2) weight_btag_jetsyst[j] *= 1.0/weight_btag_2b;
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
        std::vector<float> NN1b_recoil;
        std::vector<float> NN2b_recoil;
        for (int j = 0; j < 12; j++){//ordering: 0jet resolutionUp/Down, responseUp/Down, 1jet resolutionUp/Down, responseUp/Down, 2jetsmore resolutionUp/Down, responseUp/Down
            mymet_recoil.push_back(mymet);
            mytt_recoil.push_back(mytt);
            m_btt_recoil.push_back(m_btt);
            m_bbtt_recoil.push_back(m_bbtt);
            NN1b_recoil.push_back(NN1b);
            NN2b_recoil.push_back(NN2b);
        }
        float njetsbins[4] = {0,1,2,20};
        for (int j = 0; j < 3; j++){
            if (njets>=njetsbins[j] && njets<njetsbins[j+1]){
                for (int k = 0; k < 4; k++){
                    mymet_recoil[4*j+k].SetPtEtaPhiM(met_recoilvar[k],0,metphi_recoilvar[k],0);
                    mytt_recoil[4*j+k].SetPtEtaPhiM((myele+mytau+mymet_recoil[4*j+k]).Pt(),(myele+mytau+mymet_recoil[4*j+k]).Eta(),(myele+mytau+mymet_recoil[4*j+k]).Phi(),m_sv_recoilvar[k]);
                    m_btt_recoil[4*j+k] = (mytt_recoil[4*j+k]+myb1).M();
                    m_bbtt_recoil[4*j+k] = (mytt_recoil[4*j+k]+myb1+myb2).M();
                    NN1b_recoil[4*j+k] = NN1b_recoilvar[k];
                    NN2b_recoil[4*j+k] = NN2b_recoilvar[k];
                }
            }
        }
        for (int j = 0; j < 12; j++){
            var[0][0][j+45] = NN1b_recoil[j];
            var[0][1][j+45] = p_n(NN1b_recoil[j],p_N);
            var[0][2][j+45] = p_n(NN1b_recoil[j],p_N);
            var[0][5][j+45] = mytt_recoil[j].M();
            var[0][6][j+45] = m_btt_recoil[j];
            
            var[1][0][j+45] = NN2b_recoil[j];
            var[1][1][j+45] = p_n(NN2b_recoil[j],p_N);
            var[1][2][j+45] = p_n(NN2b_recoil[j],p_N);
            var[1][5][j+45] = mytt_recoil[j].M();
            var[1][6][j+45] = m_btt_recoil[j];
            var[1][7][j+45] = m_bbtt_recoil[j];
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
        for (int j = 0; j < 2; j++){
            mymet_UES.push_back(mymet);
            mytt_UES.push_back(mytt);
            m_btt_UES.push_back(m_btt);
            m_bbtt_UES.push_back(m_bbtt);
            
            mymet_UES[j].SetPtEtaPhiM(met_UESvar[j],0,metphi_UESvar[j],0);
            mytt_UES[j].SetPtEtaPhiM((myele+mytau+mymet_UES[j]).Pt(),(myele+mytau+mymet_UES[j]).Eta(),(myele+mytau+mymet_UES[j]).Phi(),m_sv_UESvar[j]);
            m_btt_UES[j] = (mytt_UES[j]+myb1).M();
            m_bbtt_UES[j] = (mytt_UES[j]+myb1+myb2).M();
        }
        for (int j = 0; j < 2; j++){
            var[0][0][j+57] = NN1b_UESvar[j];
            var[0][1][j+57] = p_n(NN1b_UESvar[j],p_N);
            var[0][2][j+57] = p_n(NN1b_UESvar[j],p_N);
            var[0][5][j+57] = mytt_UES[j].M();
            var[0][6][j+57] = m_btt_UES[j];
            
            var[1][0][j+57] = NN2b_UESvar[j];
            var[1][1][j+57] = p_n(NN2b_UESvar[j],p_N);
            var[1][2][j+57] = p_n(NN2b_UESvar[j],p_N);
            var[1][5][j+57] = mytt_UES[j].M();
            var[1][6][j+57] = m_btt_UES[j];
            var[1][7][j+57] = m_bbtt_UES[j];
        }
        
        //##########################tau tracking uncertainties####################################
        std::vector<float> tau_tracking_shifting;
        for (int j = 0; j < 6; j++){//ordering: dm0dm10up, dm0dm10down, dm1up, dm1down, dm11up, dm11down
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
        if (name=="ZJ"){//+/-10% of correction i.e. 1.5 -> 1.55/1.45
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
        if (name=="ttbar"){//apply twice for up and not at all for down
            topfactor_shifting[0] = topfactor;
            topfactor_shifting[1] = 1/topfactor;
        }
        
        //##########################trigger regions with nominal/shifted ES###########################
        //nominal
        bool trigger_region_nominal = (isSingleTrigger && pt_1>single_elept_thres && pt_2>single_taupt_thres) or (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres && pt_2>cross_taupt_thres);
        //shifted tau ES
        std::vector<bool> trigger_region_shiftedtau;
        for (int j = 0; j < 8; j++){
            trigger_region_shiftedtau.push_back(0);
            trigger_region_shiftedtau[j] = (isSingleTrigger && pt_1>single_elept_thres && myshiftedtau[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres && myshiftedtau[j].Pt()>cross_taupt_thres);
        }
        //muon->tauh fake ES
        std::vector<bool> trigger_region_tauisgenmu;
        for (int j = 0; j < 4; j++){
            trigger_region_tauisgenmu.push_back(0);
            trigger_region_tauisgenmu[j] = (isSingleTrigger && pt_1>single_elept_thres && mytau_isgenmu[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres && mytau_isgenmu[j].Pt()>cross_taupt_thres);
        }
        //electron->tauh fake ES
        std::vector<bool> trigger_region_tauisgenele;
        for (int j = 0; j < 4; j++){
            trigger_region_tauisgenele.push_back(0);
            trigger_region_tauisgenele[j] = (isSingleTrigger && pt_1>single_elept_thres && mytau_isgenele[j].Pt()>single_taupt_thres) or (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres && mytau_isgenele[j].Pt()>cross_taupt_thres);
        }
        //shifted electron ES
        std::vector<bool> trigger_region_shiftedele;
        for (int j = 0; j < 4; j++){
            trigger_region_shiftedele.push_back(0);
            trigger_region_shiftedele[j] = (isSingleTrigger && myshiftedele[j].Pt()>single_elept_thres && pt_2>single_taupt_thres) or (isCrossTrigger && myshiftedele[j].Pt()<single_elept_thres && myshiftedele[j].Pt()>cross_elept_thres && pt_2>cross_taupt_thres);
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
        mtt_region[0] = nbtag20==1 && m_btt<90 && mt_tau1<50 && mt_tau2<60;
        mtt_region[1] = nbtag20==1 && m_btt>90 && m_btt<105 && mt_tau1<50 && mt_tau2<60;
        mtt_region[2] = nbtag20==1 && m_btt>105 && mt_tau1<50 && mt_tau2<60;
        mtt_region[3] = nbtag20==2 && m_bbtt<150 && mt_tau1<50 && mt_tau2<60;
        mtt_region[4] = nbtag20==2 && m_bbtt>150 && mt_tau1<50 && mt_tau2<60;
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
        */
        
        //##############################categories definition##############################
        float cat1bthres1 = 0.97;//0.99 -a> 0.985 -d> 0.98 -f> 0.975 -g> 0.97
        float cat1bthres2 = 0.945;//0.975 -a> 0.965 -d> 0.96 -e> 0.95 -g> 0.945
        float cat1bthres3 = 0.9;//0.93 -e> 0.92 -g> 0.9
        float cat2bthres1 = 0.96;//0.99 -a> 0.985 -b> 0.98 -c> 0.975 -d> 0.97 -e> 0.96
        if (year=="2017"){
            cat1bthres1 = 0.985;//0.99 -a> 0.985
            cat1bthres2 = 0.965;//0.975 -a> 0.965
            cat1bthres3 = 0.93;
            cat2bthres1 = 0.985;//0.99 -a> 0.985
        }
        if (year=="2016"){
            cat1bthres1 = 0.985;//0.99 -a> 0.985
            cat1bthres2 = 0.965;//0.975 -a> 0.965
            cat1bthres3 = 0.93;
            cat2bthres1 = 0.96;//0.99 -a> 0.98 -b> 0.975 -c> 0.97 -d> 0.96
        }
        
        std::vector<std::vector<bool>> ctg;
        for (int j = 0; j < 6; j++) ctg.push_back(std::vector<bool>());//6 categories (4 for 1b, 2 for 2b)
        for (int j = 0; j < 59; j++){//59 shifted systematics
            //1b
            ctg[0].push_back(var[0][1][j]>cat1bthres1);
            ctg[1].push_back(var[0][1][j]<cat1bthres1 && var[0][1][j]>cat1bthres2);
            ctg[2].push_back(var[0][1][j]<cat1bthres2 && var[0][1][j]>cat1bthres3);
            ctg[3].push_back(var[0][1][j]<cat1bthres3);
            //2b
            ctg[4].push_back(var[1][1][j]>cat2bthres1);
            ctg[5].push_back(var[1][1][j]<cat2bthres1);
        }
        
        //##############################histograms filling###################################
        bool rejectEMBduplicate = !isMCnonHiggs or (isMCnonHiggs && !(gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6));
        
        //nonDY MC contamination to embedded (all nonHiggs MC events with two taus previously rejected)
        if (isMCnonHiggs && name!="ZJ" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (byMediumDeepVSjet_2 && trigger_region_nominal){
                if (nbtag20==1){
                    for (int m = 3; m < 7; m++){
                        h_iso[0][m][105]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*0.1);//+/-10% on top of emb
                    }
                    //final m_tt
                    for (int m = 0; m < 4; m++){
                        if (ctg[m][0]) h_iso[2][m][105]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*0.1);
                    }
                }
                if (nbtag20==2){
                    for (int m = 3; m < 8; m++){
                        h_iso[1][m][105]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*0.1);//+/-10% on top of emb
                    }
                    //final m_tt
                    for (int m = 4; m < 6; m++){
                        if (ctg[m][0]) h_iso[2][m][105]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*0.1);
                    }
                }
            }
        }
        /*
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
        if (isMCnonHiggs && name!="ZJ" && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6){
            if (byMediumDeepVSjet_2 && trigger_region_nominal){
                for (int m = 0; m < 5; m++){
                    if (mtt_region[m]==1) h_iso[2][m][105]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*0.1);
                }
            }
        }
        if (byMediumDeepVSjet_2 && rejectEMBduplicate){
            for (int m = 0; m < 5; m++){
                if (mtt_region[m]==1){
                    if (trigger_region_nominal) h_iso[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]);
                    if (sample!="data_obs"){
                        if (trigger_region_nominal){
                            for (int k = 0; k < 14; k++) h_iso[2][m][k+9]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[k+1]);
                            for (int k = 0; k < 2; k++) h_iso[2][m][k+106]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*tauidWP[k]);
                            if (sample!="embedded"){
                                for (int k = 0; k < 4; k++) h_iso[2][m][k+23]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_efake[k]);
                                for (int k = 0; k < 10; k++) h_iso[2][m][k+27]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_mufake[k]);
                                for (int k = 0; k < 4; k++) h_iso[2][m][k+53]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*btagsf_syst[k]);
                            }
                            for (int k = 0; k < 4; k++) h_iso[2][m][k+49]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                            if (sample=="embedded"){
                                for (int k = 0; k < 6; k++) h_iso[2][m][k+95]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                            }
                            if (isRecoilMC){
                                for (int k = 0; k < 12; k++) h_iso[2][m][k+81]->Fill(var[0][5][k+45],weight_corr*trgsf*sf_tauid[0]);
                            }
                            if (isnonRecoilMC){
                                for (int k = 0; k < 2; k++) h_iso[2][m][k+93]->Fill(var[0][5][k+57],weight_corr*trgsf*sf_tauid[0]);
                            }
                            if (name=="ZJ"){
                                for (int k = 0; k < 2; k++) h_iso[2][m][k+101]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                            }
                            if (name=="ttbar"){
                                for (int k = 0; k < 2; k++) h_iso[2][m][k+103]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                            }
                            if (year!="2018" && sample!="embedded"){
                                for (int k = 0; k < 2; k++) h_iso[2][m][k+108]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*prefiring[k]);
                            }
                        }
                        for (int k = 0; k < 24; k++){
                            if (trigger_region_nominal && sample!="embedded") h_iso[2][m][k+57]->Fill(var[0][5][k+21],weight_corr*trgsf*sf_tauid[0]*weight_btag_jetsyst[k]);
                        }
                        for (int k = 0; k < 8; k++){
                            if (trigger_region_shiftedtau[k]) h_iso[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf*sf_tauid[k+15]);
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_tauisgenmu[k] && sample!="embedded") h_iso[2][m][k+37]->Fill(var[0][5][k+9],weight_corr*trgsf*sf_tauid[0]);
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_tauisgenele[k] && sample!="embedded") h_iso[2][m][k+41]->Fill(var[0][5][k+13],weight_corr*trgsf*sf_tauid[0]);
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]) h_iso[2][m][k+45]->Fill(var[0][5][k+17],weight_corr*trgsf_shiftedele[k]*sf_tauid[0]);
                        }
                    }
                }
            }
        }
        //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
         */
        
        //do not fill for MC tautau events (duplicating emb) as normal
        if (byMediumDeepVSjet_2 && rejectEMBduplicate){
            //loop over variables to fill ###############1b################
            for (int m = 0; m < 7; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) h_iso[0][m][0]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //tauID eff
                        for (int k = 0; k < 14; k++) h_iso[0][m][k+9]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[k+1]);
                        //tauID WP
                        for (int k = 0; k < 2; k++) h_iso[0][m][k+106]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*tauidWP[k]);
                        //e,mu fake tau sf
                        if (sample!="embedded"){
                            //tauIDeff elefake
                            for (int k = 0; k < 4; k++) h_iso[0][m][k+23]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_efake[k]);
                            //tauIDeff mufake
                            for (int k = 0; k < 10; k++) h_iso[0][m][k+27]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_mufake[k]);
                            //btageff
                            for (int k = 0; k < 16; k++) h_iso[0][m][k+110]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*btagsf_syst[k]);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) h_iso[0][m][k+49]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                        //tau tracking, emb only
                        if (sample=="embedded"){
                            for (int k = 0; k < 6; k++) h_iso[0][m][k+95]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_iso[0][m][k+81]->Fill(var[0][m][k+45],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_iso[0][m][k+93]->Fill(var[0][m][k+57],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_iso[0][m][k+101]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_iso[0][m][k+103]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_iso[0][m][k+108]->Fill(var[0][m][0],weight_corr*trgsf*sf_tauid[0]*prefiring[k]);
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") h_iso[0][m][k+57]->Fill(var[0][m][k+21],weight_corr*trgsf*sf_tauid[0]*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted tau
                    for (int k = 0; k < 8; k++){
                        if (nbtag20==1 && trigger_region_shiftedtau[k]) h_iso[0][m][k+1]->Fill(var[0][m][k+1],weight_corr*trgsf*sf_tauid[k+15]);
                    }
                    //loop over trigger regions with muon->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_tauisgenmu[k] && sample!="embedded") h_iso[0][m][k+37]->Fill(var[0][m][k+9],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with electron->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_tauisgenele[k] && sample!="embedded") h_iso[0][m][k+41]->Fill(var[0][m][k+13],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) h_iso[0][m][k+45]->Fill(var[0][m][k+17],weight_corr*trgsf_shiftedele[k]*sf_tauid[0]);
                    }
                }//end of sample!="data_obs"
            }//end of loop of variables to fill ###############1b################
            
            //loop over variables to fill ###############2b################
            for (int m = 0; m < 8; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) h_iso[1][m][0]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //tauID eff
                        for (int k = 0; k < 14; k++) h_iso[1][m][k+9]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[k+1]);
                        //tauID WP
                        for (int k = 0; k < 2; k++) h_iso[1][m][k+106]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*tauidWP[k]);
                        //e,mu fake tau sf
                        if (sample!="embedded"){
                            //tauIDeff elefake
                            for (int k = 0; k < 4; k++) h_iso[1][m][k+23]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_efake[k]);
                            //tauIDeff mufake
                            for (int k = 0; k < 10; k++) h_iso[1][m][k+27]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_mufake[k]);
                            //btageff
                            for (int k = 0; k < 16; k++) h_iso[1][m][k+110]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*btagsf_syst[k]);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) h_iso[1][m][k+49]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                        //tau tracking, emb only
                        if (sample=="embedded"){
                            for (int k = 0; k < 6; k++) h_iso[1][m][k+95]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_iso[1][m][k+81]->Fill(var[1][m][k+45],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_iso[1][m][k+93]->Fill(var[1][m][k+57],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_iso[1][m][k+101]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_iso[1][m][k+103]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_iso[1][m][k+108]->Fill(var[1][m][0],weight_corr*trgsf*sf_tauid[0]*prefiring[k]);
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") h_iso[1][m][k+57]->Fill(var[1][m][k+21],weight_corr*trgsf*sf_tauid[0]*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted tau
                    for (int k = 0; k < 8; k++){
                        if (nbtag20==2 && trigger_region_shiftedtau[k]) h_iso[1][m][k+1]->Fill(var[1][m][k+1],weight_corr*trgsf*sf_tauid[k+15]);
                    }
                    //loop over trigger regions with muon->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_tauisgenmu[k] && sample!="embedded") h_iso[1][m][k+37]->Fill(var[1][m][k+9],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with electron->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_tauisgenele[k] && sample!="embedded") h_iso[1][m][k+41]->Fill(var[1][m][k+13],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) h_iso[1][m][k+45]->Fill(var[1][m][k+17],weight_corr*trgsf_shiftedele[k]*sf_tauid[0]);
                    }
                }//end of sample!="data_obs"
            }//end of loop of variables to fill ###############2b################
            
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>fill final m_tt categories
            //~~~~~~~~~~~~~~~~~~~1bNN
            for (int m = 0; m < 4; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) if (ctg[m][0]) h_iso[2][m][0]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //tauID eff
                        for (int k = 0; k < 14; k++) if (ctg[m][0]) h_iso[2][m][k+9]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[k+1]);
                        //tauID WP
                        for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+106]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*tauidWP[k]);
                        //e,mu fake tau sf
                        if (sample!="embedded"){
                            //tauIDeff elefake
                            for (int k = 0; k < 4; k++) if (ctg[m][0]) h_iso[2][m][k+23]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_efake[k]);
                            //tauIDeff mufake
                            for (int k = 0; k < 10; k++) if (ctg[m][0]) h_iso[2][m][k+27]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_mufake[k]);
                            //btageff
                            for (int k = 0; k < 16; k++) if (ctg[m][0]) h_iso[2][m][k+110]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*btagsf_syst[k]);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) if (ctg[m][0]) h_iso[2][m][k+49]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                        //tau tracking, emb only
                        if (sample=="embedded"){
                            for (int k = 0; k < 6; k++) if (ctg[m][0]) h_iso[2][m][k+95]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+45]) h_iso[2][m][k+81]->Fill(var[0][5][k+45],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+57]) h_iso[2][m][k+93]->Fill(var[0][5][k+57],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+101]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+103]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+108]->Fill(var[0][5][0],weight_corr*trgsf*sf_tauid[0]*prefiring[k]);
                        }
                    }//end of nbtag20==1 and nominal trigger region
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+21]) h_iso[2][m][k+57]->Fill(var[0][5][k+21],weight_corr*trgsf*sf_tauid[0]*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted tau
                    for (int k = 0; k < 8; k++){
                        if (nbtag20==1 && trigger_region_shiftedtau[k]) if (ctg[m][k+1]) h_iso[2][m][k+1]->Fill(var[0][5][k+1],weight_corr*trgsf*sf_tauid[k+15]);
                    }
                    //loop over trigger regions with muon->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_tauisgenmu[k] && sample!="embedded") if (ctg[m][k+9]) h_iso[2][m][k+37]->Fill(var[0][5][k+9],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with electron->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_tauisgenele[k] && sample!="embedded") if (ctg[m][k+13]) h_iso[2][m][k+41]->Fill(var[0][5][k+13],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) if (ctg[m][k+17]) h_iso[2][m][k+45]->Fill(var[0][5][k+17],weight_corr*trgsf_shiftedele[k]*sf_tauid[0]);
                    }
                }//end of sample!="data_obs"
            }//~~~~~~~~~~~~~~~~~~~1bNN
            
            //~~~~~~~~~~~~~~~~~~~2bNN
            for (int m = 4; m < 6; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) if (ctg[m][0]) h_iso[2][m][0]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //tauID eff
                        for (int k = 0; k < 14; k++) if (ctg[m][0]) h_iso[2][m][k+9]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[k+1]);
                        //tauID WP
                        for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+106]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*tauidWP[k]);
                        //e,mu fake tau sf
                        if (sample!="embedded"){
                            //tauIDeff elefake
                            for (int k = 0; k < 4; k++) if (ctg[m][0]) h_iso[2][m][k+23]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_efake[k]);
                            //tauIDeff mufake
                            for (int k = 0; k < 10; k++) if (ctg[m][0]) h_iso[2][m][k+27]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*sf_tauid_mufake[k]);
                            //btageff
                            for (int k = 0; k < 16; k++) if (ctg[m][0]) h_iso[2][m][k+110]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*btagsf_syst[k]);
                        }
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) if (ctg[m][0]) h_iso[2][m][k+49]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*trigger_shiftedsf[k]);
                        //tau tracking, emb only
                        if (sample=="embedded"){
                            for (int k = 0; k < 6; k++) if (ctg[m][0]) h_iso[2][m][k+95]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*tau_tracking_shifting[k]);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+45]) h_iso[2][m][k+81]->Fill(var[1][5][k+45],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+57]) h_iso[2][m][k+93]->Fill(var[1][5][k+57],weight_corr*trgsf*sf_tauid[0]);
                        }
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+101]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*zptmass_weight_shifting[k]);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+103]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*topfactor_shifting[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_iso[2][m][k+108]->Fill(var[1][5][0],weight_corr*trgsf*sf_tauid[0]*prefiring[k]);
                        }
                    }//end of nbtag20==2 and nominal trigger region
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+21]) h_iso[2][m][k+57]->Fill(var[1][5][k+21],weight_corr*trgsf*sf_tauid[0]*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted tau
                    for (int k = 0; k < 8; k++){
                        if (nbtag20==2 && trigger_region_shiftedtau[k]) if (ctg[m][k+1]) h_iso[2][m][k+1]->Fill(var[1][5][k+1],weight_corr*trgsf*sf_tauid[k+15]);
                    }
                    //loop over trigger regions with muon->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_tauisgenmu[k] && sample!="embedded") if (ctg[m][k+9]) h_iso[2][m][k+37]->Fill(var[1][5][k+9],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with electron->tau fake shifted
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_tauisgenele[k] && sample!="embedded") if (ctg[m][k+13]) h_iso[2][m][k+41]->Fill(var[1][5][k+13],weight_corr*trgsf*sf_tauid[0]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) if (ctg[m][k+17]) h_iso[2][m][k+45]->Fill(var[1][5][k+17],weight_corr*trgsf_shiftedele[k]*sf_tauid[0]);
                    }
                }//end of sample!="data_obs"
            }//~~~~~~~~~~~~~~~~~~~2bNN
            
            //><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>end of fill final m_tt categories
        }//end of isolated region
        
        //anti-isolated tau region for fake background
        if (byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2 && !isSignal && rejectEMBduplicate){//fake taus, do not need tau energy scale shifting, or tauid sf
            
            //FR calculated for bjet categories
            float fr_bjet = GetTauFR(mytau.Pt(),l2_decayMode,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,0);
            float weight_fake = fr_bjet/(1-fr_bjet);
            
            float xtrgfakefactor = 1.0;//tighter cuts applied at cross trigger level -> less yields -> scale up to compensate
            float xtrgfakefactor_updown[2] = {1.0,1.0};
            if (isCrossTrigger && pt_1<single_elept_thres && pt_1>cross_elept_thres){
                xtrgfakefactor = 1.5;//nominal
                xtrgfakefactor_updown[0] = 1.6;//+/-20%
                xtrgfakefactor_updown[1] = 1.4;
            }
            
            std::vector<float> xtrgfakefactor_shiftedele;
            //for shifted mu (re-defined single/cross)
            for (int k = 0; k < 4; k++){
                xtrgfakefactor_shiftedele.push_back(1.0);
                if (isCrossTrigger && myshiftedele[k].Pt()<single_elept_thres && myshiftedele[k].Pt()>cross_elept_thres) xtrgfakefactor_shiftedele[k] = 1.5;
            }
            
            //############################fake rate uncertainties for alldm by pt bins###########################
            std::vector<float> fr_bjet_shifted;
            std::vector<float> weight_fake_shifted;
            for (int k = 0; k < 14; k++){
                fr_bjet_shifted.push_back(GetTauFR(mytau.Pt(),0,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,g_taufr_dmall,k+1));//see GetTauFR.h
                weight_fake_shifted.push_back(fr_bjet_shifted[k]/(1-fr_bjet_shifted[k]));
            }//ordering: pt0to25up/down, pt25to30up/down,...
            
            /*
            //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
            for (int m = 0; m < 5; m++){
                if (mtt_region[m]==1){
                    if (trigger_region_nominal) h_anti[2][m][0]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                    if (sample!="data_obs"){
                        if (trigger_region_nominal){
                            for (int k = 0; k < 4; k++) h_anti[2][m][k+5]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                            if (name=="ZJ"){
                                for (int k = 0; k < 2; k++) h_anti[2][m][k+51]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                            }
                            if (name=="ttbar"){
                                for (int k = 0; k < 2; k++) h_anti[2][m][k+53]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                            }
                            if (isRecoilMC){
                                for (int k = 0; k < 12; k++) h_anti[2][m][k+37]->Fill(var[0][5][k+45],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            }
                            if (isnonRecoilMC){
                                for (int k = 0; k < 2; k++) h_anti[2][m][k+49]->Fill(var[0][5][k+57],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                            }
                            if (sample!="embedded"){
                                for (int k = 0; k < 4; k++) h_anti[2][m][k+9]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor*btagsf_syst[k]);
                            }
                            if (year!="2018" && sample!="embedded"){
                                for (int k = 0; k < 2; k++) h_anti[2][m][k+71]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*prefiring[k]*xtrgfakefactor);
                            }
                        }
                        for (int k = 0; k < 24; k++){
                            if (trigger_region_nominal && sample!="embedded") h_anti[2][m][k+13]->Fill(var[0][5][k+21],weight_corr*weight_fake*trgsf*xtrgfakefactor*weight_btag_jetsyst[k]);
                        }
                        for (int k = 0; k < 4; k++){
                            if (trigger_region_shiftedele[k]) h_anti[2][m][k+1]->Fill(var[0][5][k+17],weight_corr*weight_fake*trgsf_shiftedele[k]*xtrgfakefactor_shiftedele[k]);
                        }
                    }
                    if (trigger_region_nominal){
                        for (int k = 0; k < 2; k++) h_anti[2][m][k+55]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                        for (int k = 0; k < 14; k++) h_anti[2][m][k+57]->Fill(var[0][5][0],weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                    }
                }
            }
            //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
             */
            
            //loop over variables to fill ###############1b################
            for (int m = 0; m < 7; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) h_anti[0][m][0]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) h_anti[0][m][k+5]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_anti[0][m][k+51]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_anti[0][m][k+53]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_anti[0][m][k+37]->Fill(var[0][m][k+45],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_anti[0][m][k+49]->Fill(var[0][m][k+57],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //btag sf
                        if (sample!="embedded"){
                            for (int k = 0; k < 16; k++) h_anti[0][m][k+73]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor*btagsf_syst[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_anti[0][m][k+71]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*prefiring[k]*xtrgfakefactor);
                        }
                    }//end of nbtag20==1 && trigger_region_nominal
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") h_anti[0][m][k+13]->Fill(var[0][m][k+21],weight_corr*weight_fake*trgsf*xtrgfakefactor*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) h_anti[0][m][k+1]->Fill(var[0][m][k+17],weight_corr*weight_fake*trgsf_shiftedele[k]*xtrgfakefactor_shiftedele[k]);
                    }
                }//end of sample!="data_obs"
                if (nbtag20==1 && trigger_region_nominal){
                    //uncertainties in xtrgup factor
                    for (int k = 0; k < 2; k++) h_anti[0][m][k+55]->Fill(var[0][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                    //fake rate uncertainties for alldm by pt bins
                    for (int k = 0; k < 14; k++) h_anti[0][m][k+57]->Fill(var[0][m][0],weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                }
            }//end of loop over variables to fill ###############1b################
            
            //loop over variables to fill ###############2b################
            for (int m = 0; m < 8; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) h_anti[1][m][0]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) h_anti[1][m][k+5]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) h_anti[1][m][k+51]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) h_anti[1][m][k+53]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) h_anti[1][m][k+37]->Fill(var[1][m][k+45],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) h_anti[1][m][k+49]->Fill(var[1][m][k+57],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //btag sf
                        if (sample!="embedded"){
                            for (int k = 0; k < 16; k++) h_anti[1][m][k+73]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor*btagsf_syst[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) h_anti[1][m][k+71]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*prefiring[k]*xtrgfakefactor);
                        }
                    }//end of nbtag20==2 && trigger_region_nominal
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") h_anti[1][m][k+13]->Fill(var[1][m][k+21],weight_corr*weight_fake*trgsf*xtrgfakefactor*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) h_anti[1][m][k+1]->Fill(var[1][m][k+17],weight_corr*weight_fake*trgsf_shiftedele[k]*xtrgfakefactor_shiftedele[k]);
                    }
                }//end of sample!="data_obs"
                if (nbtag20==2 && trigger_region_nominal){
                    //uncertainties in xtrgup factor
                    for (int k = 0; k < 2; k++) h_anti[1][m][k+55]->Fill(var[1][m][0],weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                    //fake rate uncertainties for alldm by pt bins
                    for (int k = 0; k < 14; k++) h_anti[1][m][k+57]->Fill(var[1][m][0],weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                }
            }//end of loop over variables to fill ###############2b################
            
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>><><><><><><><><><><><><><><><><><><><><><>fill final m_tt categories
            //~~~~~~~~~~~~~~~~~~~1bNN
            for (int m = 0; m < 4; m++){
                //fill nominal for 1 bjet, all samples
                if (nbtag20==1 && trigger_region_nominal) if (ctg[m][0]) h_anti[2][m][0]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==1 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) if (ctg[m][0]) h_anti[2][m][k+5]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+51]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+53]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+45]) h_anti[2][m][k+37]->Fill(var[0][5][k+45],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+57]) h_anti[2][m][k+49]->Fill(var[0][5][k+57],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //btag sf
                        if (sample!="embedded"){
                            for (int k = 0; k < 16; k++) if (ctg[m][0]) h_anti[2][m][k+73]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor*btagsf_syst[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+71]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*prefiring[k]*xtrgfakefactor);
                        }
                    }//end of nbtag20==1 && trigger_region_nominal
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==1 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+21]) h_anti[2][m][k+13]->Fill(var[0][5][k+21],weight_corr*weight_fake*trgsf*xtrgfakefactor*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==1 && trigger_region_shiftedele[k]) if (ctg[m][k+17]) h_anti[2][m][k+1]->Fill(var[0][5][k+17],weight_corr*weight_fake*trgsf_shiftedele[k]*xtrgfakefactor_shiftedele[k]);
                    }
                }//end of sample!="data_obs"
                if (nbtag20==1 && trigger_region_nominal){
                    //uncertainties in xtrgup factor
                    for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+55]->Fill(var[0][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                    //fake rate uncertainties for alldm by pt bins
                    for (int k = 0; k < 14; k++) if (ctg[m][0]) h_anti[2][m][k+57]->Fill(var[0][5][0],weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                }
            }//~~~~~~~~~~~~~~~~~~~1bNN
            //~~~~~~~~~~~~~~~~~~~2bNN
            for (int m = 4; m < 6; m++){
                //fill nominal for 2 bjet, all samples
                if (nbtag20==2 && trigger_region_nominal) if (ctg[m][0]) h_anti[2][m][0]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                //fill shifted, non data
                if (sample!="data_obs"){
                    if (nbtag20==2 && trigger_region_nominal){
                        //trigger sf shifting
                        for (int k = 0; k < 4; k++) if (ctg[m][0]) h_anti[2][m][k+5]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*trigger_shiftedsf[k]*xtrgfakefactor);
                        //Zpt reweight uncertainties for DY MC only
                        if (name=="ZJ"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+51]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*zptmass_weight_shifting[k]*xtrgfakefactor);
                        }
                        //top pt reweight uncertainties for ttbar only
                        if (name=="ttbar"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+53]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*topfactor_shifting[k]*xtrgfakefactor);
                        }
                        //recoil uncertainties
                        if (isRecoilMC){
                            for (int k = 0; k < 12; k++) if (ctg[m][k+45]) h_anti[2][m][k+37]->Fill(var[1][5][k+45],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //met unclustered ES
                        if (isnonRecoilMC){
                            for (int k = 0; k < 2; k++) if (ctg[m][k+57]) h_anti[2][m][k+49]->Fill(var[1][5][k+57],weight_corr*weight_fake*trgsf*xtrgfakefactor);
                        }
                        //btag sf
                        if (sample!="embedded"){
                            for (int k = 0; k < 16; k++) if (ctg[m][0]) h_anti[2][m][k+73]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor*btagsf_syst[k]);
                        }
                        //prefiring
                        if (year!="2018" && sample!="embedded"){
                            for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+71]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*prefiring[k]*xtrgfakefactor);
                        }
                    }//end of nbtag20==2 && trigger_region_nominal
                    
                    //jet uncertainties, shifted nbtag and sf
                    for (int k = 0; k < 24; k++){
                        if (nbtag20_jetsyst[k]==2 && trigger_region_nominal && sample!="embedded") if (ctg[m][k+21]) h_anti[2][m][k+13]->Fill(var[1][5][k+21],weight_corr*weight_fake*trgsf*xtrgfakefactor*weight_btag_jetsyst[k]);
                    }
                    //loop over trigger regions with shifted electron
                    for (int k = 0; k < 4; k++){
                        if (nbtag20==2 && trigger_region_shiftedele[k]) if (ctg[m][k+17]) h_anti[2][m][k+1]->Fill(var[1][5][k+17],weight_corr*weight_fake*trgsf_shiftedele[k]*xtrgfakefactor_shiftedele[k]);
                    }
                }//end of sample!="data_obs"
                if (nbtag20==2 && trigger_region_nominal){
                    //uncertainties in xtrgup factor
                    for (int k = 0; k < 2; k++) if (ctg[m][0]) h_anti[2][m][k+55]->Fill(var[1][5][0],weight_corr*weight_fake*trgsf*xtrgfakefactor_updown[k]);
                    //fake rate uncertainties for alldm by pt bins
                    for (int k = 0; k < 14; k++) if (ctg[m][0]) h_anti[2][m][k+57]->Fill(var[1][5][0],weight_corr*weight_fake_shifted[k]*trgsf*xtrgfakefactor);
                }
            }//~~~~~~~~~~~~~~~~~~~2bNN
            
        }//end of anti-isolated region
        
    }//end of event loop
    
    TFile * fout = TFile::Open(output.c_str(), "UPDATE");
    
    TString dir1b[7] = {"p_1b","p2_1b","p2_z_1b","pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b"};
    TString dir2b[8] = {"p_2b","p2_2b","p2_z_2b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"};
    TString dirmtt[6] = {"1","2","3","4","5","6"};
    TString fake = "_fake";
    TString MC = "MC";
    
    std::vector<TDirectory*> td;
    for (int j = 0; j < 7; j++){//loop over histogram variables ##############1b##############
        td.push_back(fout->mkdir(dir1b[j]));
        td[j]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_iso[0][j][0]->SetName(name.c_str());
            h_iso[0][j][0]->Write();
            //shifted in isolated
            for (int i = 0; i < 14; ++i){
                if (sample!="embedded") h_iso[0][j][i+9]->SetName(name.c_str()+shape_tauideff[i]);
                else h_iso[0][j][i+9]->SetName(name.c_str()+embshape_tauideff[i]);
                h_iso[0][j][i+9]->Write();
            }
            for (int i = 0; i < 2; ++i){
                if (sample!="embedded") h_iso[0][j][i+106]->SetName(name.c_str()+shape_tauidWP[i]);
                else h_iso[0][j][i+106]->SetName(name.c_str()+embshape_tauidWP[i]);
                h_iso[0][j][i+106]->Write();
            }
            for (int i = 0; i < 8; ++i){
                if (sample!="embedded") h_iso[0][j][i+1]->SetName(name.c_str()+shape_tauES[i]);
                else h_iso[0][j][i+1]->SetName(name.c_str()+embshape_tauES[i]);
                h_iso[0][j][i+1]->Write();
            }
            if (sample!="embedded"){
                for (int i = 0; i < 24; ++i){
                    h_iso[0][j][i+57]->SetName(name.c_str()+shape_jet[i]);
                    h_iso[0][j][i+57]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[0][j][i+37]->SetName(name.c_str()+shape_mufaketauES[i]);
                    h_iso[0][j][i+37]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[0][j][i+41]->SetName(name.c_str()+shape_elefaketauES[i]);
                    h_iso[0][j][i+41]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[0][j][i+23]->SetName(name.c_str()+shape_tauideff_efake[i]);
                    h_iso[0][j][i+23]->Write();
                }
                for (int i = 0; i < 10; ++i){
                    h_iso[0][j][i+27]->SetName(name.c_str()+shape_tauideff_mufake[i]);
                    h_iso[0][j][i+27]->Write();
                }
                for (int i = 0; i < 16; ++i){
                    h_iso[0][j][i+110]->SetName(name.c_str()+shape_btagsf[i]);
                    h_iso[0][j][i+110]->Write();
                }
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[0][j][i+49]->SetName(name.c_str()+shape_trgeff[i]);
                else h_iso[0][j][i+49]->SetName(name.c_str()+embshape_trgeff[i]);
                h_iso[0][j][i+49]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[0][j][i+45]->SetName(name.c_str()+shape_eleES[i]);
                else h_iso[0][j][i+45]->SetName(name.c_str()+embshape_eleES[i]);
                h_iso[0][j][i+45]->Write();
            }
            if (sample=="embedded"){
                for (int i = 0; i < 6; ++i){
                    h_iso[0][j][i+95]->SetName(name.c_str()+embshape_tautracking[i]);
                    h_iso[0][j][i+95]->Write();
                }
            }
            if (name=="ZJ"){
                for (int i = 0; i < 2; ++i){
                    h_iso[0][j][i+101]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_iso[0][j][i+101]->Write();
                }
            }
            if (name=="ttbar"){
                for (int i = 0; i < 2; ++i){
                    h_iso[0][j][i+103]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_iso[0][j][i+103]->Write();
                }
            }
            if (year!="2018" && sample!="embedded"){
                for (int i = 0; i < 2; ++i){
                    h_iso[0][j][i+108]->SetName(name.c_str()+shape_prefiring[i]);
                    h_iso[0][j][i+108]->Write();
                }
            }
            if (isRecoilMC){
                for (int i = 0; i < 12; ++i){
                    h_iso[0][j][i+81]->SetName(name.c_str()+shape_recoil[i]);
                    h_iso[0][j][i+81]->Write();
                }
            }
            if (isnonRecoilMC){
                for (int i = 0; i < 2; ++i){
                    h_iso[0][j][i+93]->SetName(name.c_str()+shape_UES[i]);
                    h_iso[0][j][i+93]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_iso[0][j][105]->SetName(shape_nonDY[0]);
                h_iso[0][j][105]->Write();
            }
            
            //shifted in anti-isolated
            if (!isSignal){
                h_anti[0][j][0]->SetName(MC+fake);
                h_anti[0][j][0]->Write();
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_anti[0][j][i+13]->SetName(MC+fake+shape_jet[i]);
                        h_anti[0][j][i+13]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_jet[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 16; ++i){
                    if (sample!="embedded"){
                        h_anti[0][j][i+73]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[0][j][i+73]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[0][j][i+5]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[0][j][i+5]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[0][j][i+1]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[0][j][i+1]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_anti[0][j][i+51]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[0][j][i+51]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_anti[0][j][i+53]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[0][j][i+53]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                if (year!="2018"){
                    for (int i = 0; i < 2; ++i){
                        if (sample!="embedded"){
                            h_anti[0][j][i+71]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[0][j][i+71]->Write();
                        }
                        else {
                            h_anti[0][j][0]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[0][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_anti[0][j][i+37]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[0][j][i+37]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_anti[0][j][i+49]->SetName(MC+fake+shape_UES[i]);
                        h_anti[0][j][i+49]->Write();
                    }
                    else {
                        h_anti[0][j][0]->SetName(MC+fake+shape_UES[i]);
                        h_anti[0][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    h_anti[0][j][i+55]->SetName(MC+fake+shape_fake_crosstrg[i]);
                    h_anti[0][j][i+55]->Write();
                }
                for (int i = 0; i < 14; ++i){
                    h_anti[0][j][i+57]->SetName(MC+fake+shape_fakerate[i]);
                    h_anti[0][j][i+57]->Write();
                }
            }//end of anti-isolated
        }//end of (sample!="data_obs)
        if (sample=="data_obs"){
            h_iso[0][j][0]->SetName(name.c_str());
            h_iso[0][j][0]->Write();
            h_anti[0][j][0]->SetName(name.c_str()+fake);
            h_anti[0][j][0]->Write();
            for (int i = 0; i < 2; ++i){
                h_anti[0][j][i+55]->SetName(name.c_str()+fake+shape_fake_crosstrg[i]);
                h_anti[0][j][i+55]->Write();
            }
            for (int i = 0; i < 14; ++i){
                h_anti[0][j][i+57]->SetName(name.c_str()+fake+shape_fakerate[i]);
                h_anti[0][j][i+57]->Write();
            }
        }
    }
    
    for (int j = 0; j < 8; j++){//loop over histogram variables ##############2b##############
        td.push_back(fout->mkdir(dir2b[j]));
        td[j+7]->cd();
        
        if (sample!="data_obs"){
            //nominal
            h_iso[1][j][0]->SetName(name.c_str());
            h_iso[1][j][0]->Write();
            //shifted in isolated
            for (int i = 0; i < 14; ++i){
                if (sample!="embedded") h_iso[1][j][i+9]->SetName(name.c_str()+shape_tauideff[i]);
                else h_iso[1][j][i+9]->SetName(name.c_str()+embshape_tauideff[i]);
                h_iso[1][j][i+9]->Write();
            }
            for (int i = 0; i < 2; ++i){
                if (sample!="embedded") h_iso[1][j][i+106]->SetName(name.c_str()+shape_tauidWP[i]);
                else h_iso[1][j][i+106]->SetName(name.c_str()+embshape_tauidWP[i]);
                h_iso[1][j][i+106]->Write();
            }
            for (int i = 0; i < 8; ++i){
                if (sample!="embedded") h_iso[1][j][i+1]->SetName(name.c_str()+shape_tauES[i]);
                else h_iso[1][j][i+1]->SetName(name.c_str()+embshape_tauES[i]);
                h_iso[1][j][i+1]->Write();
            }
            if (sample!="embedded"){
                for (int i = 0; i < 24; ++i){
                    h_iso[1][j][i+57]->SetName(name.c_str()+shape_jet[i]);
                    h_iso[1][j][i+57]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[1][j][i+37]->SetName(name.c_str()+shape_mufaketauES[i]);
                    h_iso[1][j][i+37]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[1][j][i+41]->SetName(name.c_str()+shape_elefaketauES[i]);
                    h_iso[1][j][i+41]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[1][j][i+23]->SetName(name.c_str()+shape_tauideff_efake[i]);
                    h_iso[1][j][i+23]->Write();
                }
                for (int i = 0; i < 10; ++i){
                    h_iso[1][j][i+27]->SetName(name.c_str()+shape_tauideff_mufake[i]);
                    h_iso[1][j][i+27]->Write();
                }
                for (int i = 0; i < 16; ++i){
                    h_iso[1][j][i+110]->SetName(name.c_str()+shape_btagsf[i]);
                    h_iso[1][j][i+110]->Write();
                }
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[1][j][i+49]->SetName(name.c_str()+shape_trgeff[i]);
                else h_iso[1][j][i+49]->SetName(name.c_str()+embshape_trgeff[i]);
                h_iso[1][j][i+49]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[1][j][i+45]->SetName(name.c_str()+shape_eleES[i]);
                else h_iso[1][j][i+45]->SetName(name.c_str()+embshape_eleES[i]);
                h_iso[1][j][i+45]->Write();
            }
            if (sample=="embedded"){
                for (int i = 0; i < 6; ++i){
                    h_iso[1][j][i+95]->SetName(name.c_str()+embshape_tautracking[i]);
                    h_iso[1][j][i+95]->Write();
                }
            }
            if (name=="ZJ"){
                for (int i = 0; i < 2; ++i){
                    h_iso[1][j][i+101]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_iso[1][j][i+101]->Write();
                }
            }
            if (name=="ttbar"){
                for (int i = 0; i < 2; ++i){
                    h_iso[1][j][i+103]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_iso[1][j][i+103]->Write();
                }
            }
            if (year!="2018" && sample!="embedded"){
                for (int i = 0; i < 2; ++i){
                    h_iso[1][j][i+108]->SetName(name.c_str()+shape_prefiring[i]);
                    h_iso[1][j][i+108]->Write();
                }
            }
            if (isRecoilMC){
                for (int i = 0; i < 12; ++i){
                    h_iso[1][j][i+81]->SetName(name.c_str()+shape_recoil[i]);
                    h_iso[1][j][i+81]->Write();
                }
            }
            if (isnonRecoilMC){
                for (int i = 0; i < 2; ++i){
                    h_iso[1][j][i+93]->SetName(name.c_str()+shape_UES[i]);
                    h_iso[1][j][i+93]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_iso[1][j][105]->SetName(shape_nonDY[0]);
                h_iso[1][j][105]->Write();
            }
            
            //shifted in anti-isolated
            if (!isSignal){
                h_anti[1][j][0]->SetName(MC+fake);
                h_anti[1][j][0]->Write();
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_anti[1][j][i+13]->SetName(MC+fake+shape_jet[i]);
                        h_anti[1][j][i+13]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_jet[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 16; ++i){
                    if (sample!="embedded"){
                        h_anti[1][j][i+73]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[1][j][i+73]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[1][j][i+5]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[1][j][i+5]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[1][j][i+1]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[1][j][i+1]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_anti[1][j][i+51]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[1][j][i+51]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_anti[1][j][i+53]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[1][j][i+53]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                if (year!="2018"){
                    for (int i = 0; i < 2; ++i){
                        if (sample!="embedded"){
                            h_anti[1][j][i+71]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[1][j][i+71]->Write();
                        }
                        else {
                            h_anti[1][j][0]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[1][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_anti[1][j][i+37]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[1][j][i+37]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_anti[1][j][i+49]->SetName(MC+fake+shape_UES[i]);
                        h_anti[1][j][i+49]->Write();
                    }
                    else {
                        h_anti[1][j][0]->SetName(MC+fake+shape_UES[i]);
                        h_anti[1][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    h_anti[1][j][i+55]->SetName(MC+fake+shape_fake_crosstrg[i]);
                    h_anti[1][j][i+55]->Write();
                }
                for (int i = 0; i < 14; ++i){
                    h_anti[1][j][i+57]->SetName(MC+fake+shape_fakerate[i]);
                    h_anti[1][j][i+57]->Write();
                }
            }//end of anti-isolated
        }//end of (sample!="data_obs)
        if (sample=="data_obs"){
            h_iso[1][j][0]->SetName(name.c_str());
            h_iso[1][j][0]->Write();
            h_anti[1][j][0]->SetName(name.c_str()+fake);
            h_anti[1][j][0]->Write();
            for (int i = 0; i < 2; ++i){
                h_anti[1][j][i+55]->SetName(name.c_str()+fake+shape_fake_crosstrg[i]);
                h_anti[1][j][i+55]->Write();
            }
            for (int i = 0; i < 14; ++i){
                h_anti[1][j][i+57]->SetName(name.c_str()+fake+shape_fakerate[i]);
                h_anti[1][j][i+57]->Write();
            }
        }
    }
    
    //~~~~~~~~~~~~~~~final m_tt
    for (int j = 0; j < 6; j++){
        td.push_back(fout->mkdir(dirmtt[j]));
        td[j+15]->cd();
        if (sample!="data_obs"){
            h_iso[2][j][0]->SetName(name.c_str());
            h_iso[2][j][0]->Write();
            for (int i = 0; i < 14; ++i){
                if (sample!="embedded") h_iso[2][j][i+9]->SetName(name.c_str()+shape_tauideff[i]);
                else h_iso[2][j][i+9]->SetName(name.c_str()+embshape_tauideff[i]);
                h_iso[2][j][i+9]->Write();
            }
            for (int i = 0; i < 2; ++i){
                if (sample!="embedded") h_iso[2][j][i+106]->SetName(name.c_str()+shape_tauidWP[i]);
                else h_iso[2][j][i+106]->SetName(name.c_str()+embshape_tauidWP[i]);
                h_iso[2][j][i+106]->Write();
            }
            for (int i = 0; i < 8; ++i){
                if (sample!="embedded") h_iso[2][j][i+1]->SetName(name.c_str()+shape_tauES[i]);
                else h_iso[2][j][i+1]->SetName(name.c_str()+embshape_tauES[i]);
                h_iso[2][j][i+1]->Write();
            }
            if (sample!="embedded"){
                for (int i = 0; i < 24; ++i){
                    h_iso[2][j][i+57]->SetName(name.c_str()+shape_jet[i]);
                    h_iso[2][j][i+57]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[2][j][i+37]->SetName(name.c_str()+shape_mufaketauES[i]);
                    h_iso[2][j][i+37]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[2][j][i+41]->SetName(name.c_str()+shape_elefaketauES[i]);
                    h_iso[2][j][i+41]->Write();
                }
                for (int i = 0; i < 4; ++i){
                    h_iso[2][j][i+23]->SetName(name.c_str()+shape_tauideff_efake[i]);
                    h_iso[2][j][i+23]->Write();
                }
                for (int i = 0; i < 10; ++i){
                    h_iso[2][j][i+27]->SetName(name.c_str()+shape_tauideff_mufake[i]);
                    h_iso[2][j][i+27]->Write();
                }
                for (int i = 0; i < 16; ++i){
                    h_iso[2][j][i+110]->SetName(name.c_str()+shape_btagsf[i]);
                    h_iso[2][j][i+110]->Write();
                }
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[2][j][i+49]->SetName(name.c_str()+shape_trgeff[i]);
                else h_iso[2][j][i+49]->SetName(name.c_str()+embshape_trgeff[i]);
                h_iso[2][j][i+49]->Write();
            }
            for (int i = 0; i < 4; ++i){
                if (sample!="embedded") h_iso[2][j][i+45]->SetName(name.c_str()+shape_eleES[i]);
                else h_iso[2][j][i+45]->SetName(name.c_str()+embshape_eleES[i]);
                h_iso[2][j][i+45]->Write();
            }
            if (sample=="embedded"){
                for (int i = 0; i < 6; ++i){
                    h_iso[2][j][i+95]->SetName(name.c_str()+embshape_tautracking[i]);
                    h_iso[2][j][i+95]->Write();
                }
            }
            if (name=="ZJ"){
                for (int i = 0; i < 2; ++i){
                    h_iso[2][j][i+101]->SetName(name.c_str()+shape_DY_zpt[i]);
                    h_iso[2][j][i+101]->Write();
                }
            }
            if (name=="ttbar"){
                for (int i = 0; i < 2; ++i){
                    h_iso[2][j][i+103]->SetName(name.c_str()+shape_ttbar_toppt[i]);
                    h_iso[2][j][i+103]->Write();
                }
            }
            if (year!="2018" && sample!="embedded"){
                for (int i = 0; i < 2; ++i){
                    h_iso[2][j][i+108]->SetName(name.c_str()+shape_prefiring[i]);
                    h_iso[2][j][i+108]->Write();
                }
            }
            if (isRecoilMC){
                for (int i = 0; i < 12; ++i){
                    h_iso[2][j][i+81]->SetName(name.c_str()+shape_recoil[i]);
                    h_iso[2][j][i+81]->Write();
                }
            }
            if (isnonRecoilMC){
                for (int i = 0; i < 2; ++i){
                    h_iso[2][j][i+93]->SetName(name.c_str()+shape_UES[i]);
                    h_iso[2][j][i+93]->Write();
                }
            }
            if (isMCnonHiggs && name!="ZJ"){
                h_iso[2][j][105]->SetName(shape_nonDY[0]);
                h_iso[2][j][105]->Write();
            }
            //shifted in anti-isolated
            if (!isSignal){
                h_anti[2][j][0]->SetName(MC+fake);
                h_anti[2][j][0]->Write();
                for (int i = 0; i < 24; ++i){
                    if (sample!="embedded"){
                        h_anti[2][j][i+13]->SetName(MC+fake+shape_jet[i]);
                        h_anti[2][j][i+13]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_jet[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 16; ++i){
                    if (sample!="embedded"){
                        h_anti[2][j][i+73]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[2][j][i+73]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_btagsf[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[2][j][i+5]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[2][j][i+5]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_trgeff[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 4; ++i){
                    if (sample!="embedded"){
                        h_anti[2][j][i+1]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[2][j][i+1]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_eleES[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ZJ"){
                        h_anti[2][j][i+51]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[2][j][i+51]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_DY_zpt[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (name=="ttbar"){
                        h_anti[2][j][i+53]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[2][j][i+53]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_ttbar_toppt[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                if (year!="2018"){
                    for (int i = 0; i < 2; ++i){
                        if (sample!="embedded"){
                            h_anti[2][j][i+71]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[2][j][i+71]->Write();
                        }
                        else {
                            h_anti[2][j][0]->SetName(MC+fake+shape_prefiring[i]);
                            h_anti[2][j][0]->Write();
                        }
                    }
                }
                for (int i = 0; i < 12; ++i){
                    if (isRecoilMC){
                        h_anti[2][j][i+37]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[2][j][i+37]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_recoil[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    if (isnonRecoilMC){
                        h_anti[2][j][i+49]->SetName(MC+fake+shape_UES[i]);
                        h_anti[2][j][i+49]->Write();
                    }
                    else {
                        h_anti[2][j][0]->SetName(MC+fake+shape_UES[i]);
                        h_anti[2][j][0]->Write();
                    }
                }
                for (int i = 0; i < 2; ++i){
                    h_anti[2][j][i+55]->SetName(MC+fake+shape_fake_crosstrg[i]);
                    h_anti[2][j][i+55]->Write();
                }
                for (int i = 0; i < 14; ++i){
                    h_anti[2][j][i+57]->SetName(MC+fake+shape_fakerate[i]);
                    h_anti[2][j][i+57]->Write();
                }
            }//end of anti-isolated
        }//end of (sample!="data_obs)
        if (sample=="data_obs"){
            h_iso[2][j][0]->SetName(name.c_str());
            h_iso[2][j][0]->Write();
            h_anti[2][j][0]->SetName(name.c_str()+fake);
            h_anti[2][j][0]->Write();
            for (int i = 0; i < 2; ++i){
                h_anti[2][j][i+55]->SetName(name.c_str()+fake+shape_fake_crosstrg[i]);
                h_anti[2][j][i+55]->Write();
            }
            for (int i = 0; i < 14; ++i){
                h_anti[2][j][i+57]->SetName(name.c_str()+fake+shape_fakerate[i]);
                h_anti[2][j][i+57]->Write();
            }
        }
    }
    //~~~~~~~~~~~~~~~(can be deleted later)~~~~~~~~~~~~~~
    
    fout->Close();
    
    cout << "************* output: " << output.c_str() << " *************" << endl;
    
}




