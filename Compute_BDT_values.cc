#include "mvaXXX.h"

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    using namespace std;

    std::string uncert = *(argv + 2);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[3]); //0: nominal, 1: TES up, -1: TES down, 2: EES up, -2: EES down, 3: UES up, -3: UES down, 4: JES up, -4: JES down
    }

    TFile *f_Double = new TFile(input.c_str(),"update");
    TTree *Run_Tree = (TTree*) f_Double->Get("RLE_tree");
    float bdt_all;

        ostringstream HNh0R1; HNh0R1 << "bdt_all_" << uncert;

    TBranch *bbdt = Run_Tree->Branch(HNh0R1.str().c_str(),&bdt_all,"bdt_all/F");
    Run_Tree->SetBranchAddress("pt_1", &pt_1);
    Run_Tree->SetBranchAddress("pt_1_EResPhiDown", &pt_1_EResPhiDown);
    Run_Tree->SetBranchAddress("pt_1_EResRhoDown", &pt_1_EResRhoDown);
    Run_Tree->SetBranchAddress("pt_1_EResRhoUp", &pt_1_EResRhoUp);
    Run_Tree->SetBranchAddress("pt_1_EScaleDown", &pt_1_EScaleDown);
    Run_Tree->SetBranchAddress("pt_1_EScaleUp", &pt_1_EScaleUp);
    Run_Tree->SetBranchAddress("pt_2", &pt_2);
    Run_Tree->SetBranchAddress("dphi_12", &dphi_12);
    Run_Tree->SetBranchAddress("dphi_taumet", &dphi_taumet);
    Run_Tree->SetBranchAddress("dphi_emet", &dphi_emet);
    Run_Tree->SetBranchAddress("mjj_JESDown", &mjj_JESDown);
    Run_Tree->SetBranchAddress("njets_JESDown", &njets_JESDown);
    Run_Tree->SetBranchAddress("jdeta_JESDown", &jdeta_JESDown);
    Run_Tree->SetBranchAddress("mjj_JESUp", &mjj_JESUp);
    Run_Tree->SetBranchAddress("njets_JESUp", &njets_JESUp);
    Run_Tree->SetBranchAddress("jdeta_JESUp", &jdeta_JESUp);
    Run_Tree->SetBranchAddress("met", &met);
    Run_Tree->SetBranchAddress("metphi", &metphi);
    Run_Tree->SetBranchAddress("met_ChargedUESDown", &met_ChargedUESDown);
    Run_Tree->SetBranchAddress("metphi_ChargedUESDown", &metphi_ChargedUESDown);
    Run_Tree->SetBranchAddress("met_ChargedUESUp", &met_ChargedUESUp);
    Run_Tree->SetBranchAddress("metphi_ChargedUESUp", &metphi_ChargedUESUp);
    Run_Tree->SetBranchAddress("met_ECALUESDown", &met_ECALUESDown);
    Run_Tree->SetBranchAddress("metphi_ECALUESDown", &metphi_ECALUESDown);
    Run_Tree->SetBranchAddress("met_ECALUESUp", &met_ECALUESUp);
    Run_Tree->SetBranchAddress("metphi_ECALUESUp", &metphi_ECALUESUp);
    Run_Tree->SetBranchAddress("met_HCALUESDown", &met_HCALUESDown);
    Run_Tree->SetBranchAddress("metphi_HCALUESDown", &metphi_HCALUESDown);
    Run_Tree->SetBranchAddress("met_HCALUESUp", &met_HCALUESUp);
    Run_Tree->SetBranchAddress("metphi_HCALUESUp", &metphi_HCALUESUp);
    Run_Tree->SetBranchAddress("met_HFUESDown", &met_HFUESDown);
    Run_Tree->SetBranchAddress("metphi_HFUESDown", &metphi_HFUESDown);
    Run_Tree->SetBranchAddress("met_HFUESUp", &met_HFUESUp);
    Run_Tree->SetBranchAddress("metphi_HFUESUp", &metphi_HFUESUp);
    Run_Tree->SetBranchAddress("met_ChargedUESDown", &met_ChargedUESDown);
    Run_Tree->SetBranchAddress("metphi_ChargedUESDown", &metphi_ChargedUESDown);
    Run_Tree->SetBranchAddress("met_ChargedUESUp", &met_ChargedUESUp);
    Run_Tree->SetBranchAddress("metphi_ChargedUESUp", &metphi_ChargedUESUp);
    Run_Tree->SetBranchAddress("met_JESDown", &met_JESDown);
    Run_Tree->SetBranchAddress("metphi_JESDown", &metphi_JESDown);
    Run_Tree->SetBranchAddress("met_JESUp", &met_JESUp);
    Run_Tree->SetBranchAddress("metphi_JESDown", &metphi_JESUp);
    Run_Tree->SetBranchAddress("mt_1", &mt_1);
    Run_Tree->SetBranchAddress("mt_2", &mt_2);
    Run_Tree->SetBranchAddress("mjj", &mjj);
    Run_Tree->SetBranchAddress("jdeta", &jdeta);
    Run_Tree->SetBranchAddress("njets", &njets);
    Run_Tree->SetBranchAddress("eta_2", &eta_2);
    Run_Tree->SetBranchAddress("eta_1", &eta_1);
    Run_Tree->SetBranchAddress("m_coll", &m_coll);
    Run_Tree->SetBranchAddress("phi_1", &phi_1);
    Run_Tree->SetBranchAddress("m_1", &m_1);
    Run_Tree->SetBranchAddress("phi_2", &phi_2);
    Run_Tree->SetBranchAddress("m_2", &m_2);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteFlavMapDown",&njets_JetAbsoluteFlavMapDown);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteFlavMapUp",&njets_JetAbsoluteFlavMapUp);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteMPFBiasDown",&njets_JetAbsoluteMPFBiasDown);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteMPFBiasUp",&njets_JetAbsoluteMPFBiasUp);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteScaleDown",&njets_JetAbsoluteScaleDown);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteScaleUp",&njets_JetAbsoluteScaleUp);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteStatDown",&njets_JetAbsoluteStatDown);
    Run_Tree->SetBranchAddress("njets_JetAbsoluteStatUp",&njets_JetAbsoluteStatUp);
    Run_Tree->SetBranchAddress("njets_JetFlavorQCDDown",&njets_JetFlavorQCDDown);
    Run_Tree->SetBranchAddress("njets_JetFlavorQCDUp",&njets_JetFlavorQCDUp);
    Run_Tree->SetBranchAddress("njets_JetFragmentationDown",&njets_JetFragmentationDown);
    Run_Tree->SetBranchAddress("njets_JetFragmentationUp",&njets_JetFragmentationUp);
    Run_Tree->SetBranchAddress("njets_JetPileUpDataMCDown",&njets_JetPileUpDataMCDown);
    Run_Tree->SetBranchAddress("njets_JetPileUpDataMCUp",&njets_JetPileUpDataMCUp);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtBBDown",&njets_JetPileUpPtBBDown);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtBBUp",&njets_JetPileUpPtBBUp);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtEC1Down",&njets_JetPileUpPtEC1Down);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtEC1Up",&njets_JetPileUpPtEC1Up);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtEC2Down",&njets_JetPileUpPtEC2Down);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtEC2Up",&njets_JetPileUpPtEC2Up);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtHFDown",&njets_JetPileUpPtHFDown);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtHFUp",&njets_JetPileUpPtHFUp);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtRefDown",&njets_JetPileUpPtRefDown);
    Run_Tree->SetBranchAddress("njets_JetPileUpPtRefUp",&njets_JetPileUpPtRefUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeBalDown",&njets_JetRelativeBalDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeBalUp",&njets_JetRelativeBalUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeFSRDown",&njets_JetRelativeFSRDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeFSRUp",&njets_JetRelativeFSRUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeJEREC1Down",&njets_JetRelativeJEREC1Down);
    Run_Tree->SetBranchAddress("njets_JetRelativeJEREC1Up",&njets_JetRelativeJEREC1Up);
    Run_Tree->SetBranchAddress("njets_JetRelativeJEREC2Down",&njets_JetRelativeJEREC2Down);
    Run_Tree->SetBranchAddress("njets_JetRelativeJEREC2Up",&njets_JetRelativeJEREC2Up);
    Run_Tree->SetBranchAddress("njets_JetRelativeJERHFDown",&njets_JetRelativeJERHFDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeJERHFUp",&njets_JetRelativeJERHFUp);
    Run_Tree->SetBranchAddress("njets_JetRelativePtBBDown",&njets_JetRelativePtBBDown);
    Run_Tree->SetBranchAddress("njets_JetRelativePtBBUp",&njets_JetRelativePtBBUp);
    Run_Tree->SetBranchAddress("njets_JetRelativePtEC1Down",&njets_JetRelativePtEC1Down);
    Run_Tree->SetBranchAddress("njets_JetRelativePtEC1Up",&njets_JetRelativePtEC1Up);
    Run_Tree->SetBranchAddress("njets_JetRelativePtEC2Down",&njets_JetRelativePtEC2Down);
    Run_Tree->SetBranchAddress("njets_JetRelativePtEC2Up",&njets_JetRelativePtEC2Up);
    Run_Tree->SetBranchAddress("njets_JetRelativePtHFDown",&njets_JetRelativePtHFDown);
    Run_Tree->SetBranchAddress("njets_JetRelativePtHFUp",&njets_JetRelativePtHFUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatECDown",&njets_JetRelativeStatECDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatECUp",&njets_JetRelativeStatECUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatFSRDown",&njets_JetRelativeStatFSRDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatFSRUp",&njets_JetRelativeStatFSRUp);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatHFDown",&njets_JetRelativeStatHFDown);
    Run_Tree->SetBranchAddress("njets_JetRelativeStatHFUp",&njets_JetRelativeStatHFUp);
    Run_Tree->SetBranchAddress("njets_JetSinglePionECALDown",&njets_JetSinglePionECALDown);
    Run_Tree->SetBranchAddress("njets_JetSinglePionECALUp",&njets_JetSinglePionECALUp);
    Run_Tree->SetBranchAddress("njets_JetSinglePionHCALDown",&njets_JetSinglePionHCALDown);
    Run_Tree->SetBranchAddress("njets_JetSinglePionHCALUp",&njets_JetSinglePionHCALUp);
    Run_Tree->SetBranchAddress("njets_JetTimePtEtaDown",&njets_JetTimePtEtaDown);
    Run_Tree->SetBranchAddress("njets_JetTimePtEtaUp",&njets_JetTimePtEtaUp);

    Run_Tree->SetBranchAddress("mjj_JetAbsoluteFlavMapDown",&mjj_JetAbsoluteFlavMapDown);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteFlavMapUp",&mjj_JetAbsoluteFlavMapUp);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteMPFBiasDown",&mjj_JetAbsoluteMPFBiasDown);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteMPFBiasUp",&mjj_JetAbsoluteMPFBiasUp);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteScaleDown",&mjj_JetAbsoluteScaleDown);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteScaleUp",&mjj_JetAbsoluteScaleUp);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteStatDown",&mjj_JetAbsoluteStatDown);
    Run_Tree->SetBranchAddress("mjj_JetAbsoluteStatUp",&mjj_JetAbsoluteStatUp);
    Run_Tree->SetBranchAddress("mjj_JetFlavorQCDDown",&mjj_JetFlavorQCDDown);
    Run_Tree->SetBranchAddress("mjj_JetFlavorQCDUp",&mjj_JetFlavorQCDUp);
    Run_Tree->SetBranchAddress("mjj_JetFragmentationDown",&mjj_JetFragmentationDown);
    Run_Tree->SetBranchAddress("mjj_JetFragmentationUp",&mjj_JetFragmentationUp);
    Run_Tree->SetBranchAddress("mjj_JetPileUpDataMCDown",&mjj_JetPileUpDataMCDown);
    Run_Tree->SetBranchAddress("mjj_JetPileUpDataMCUp",&mjj_JetPileUpDataMCUp);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtBBDown",&mjj_JetPileUpPtBBDown);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtBBUp",&mjj_JetPileUpPtBBUp);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtEC1Down",&mjj_JetPileUpPtEC1Down);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtEC1Up",&mjj_JetPileUpPtEC1Up);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtEC2Down",&mjj_JetPileUpPtEC2Down);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtEC2Up",&mjj_JetPileUpPtEC2Up);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtHFDown",&mjj_JetPileUpPtHFDown);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtHFUp",&mjj_JetPileUpPtHFUp);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtRefDown",&mjj_JetPileUpPtRefDown);
    Run_Tree->SetBranchAddress("mjj_JetPileUpPtRefUp",&mjj_JetPileUpPtRefUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeBalDown",&mjj_JetRelativeBalDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeBalUp",&mjj_JetRelativeBalUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeFSRDown",&mjj_JetRelativeFSRDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeFSRUp",&mjj_JetRelativeFSRUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJEREC1Down",&mjj_JetRelativeJEREC1Down);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJEREC1Up",&mjj_JetRelativeJEREC1Up);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJEREC2Down",&mjj_JetRelativeJEREC2Down);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJEREC2Up",&mjj_JetRelativeJEREC2Up);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJERHFDown",&mjj_JetRelativeJERHFDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeJERHFUp",&mjj_JetRelativeJERHFUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtBBDown",&mjj_JetRelativePtBBDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtBBUp",&mjj_JetRelativePtBBUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtEC1Down",&mjj_JetRelativePtEC1Down);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtEC1Up",&mjj_JetRelativePtEC1Up);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtEC2Down",&mjj_JetRelativePtEC2Down);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtEC2Up",&mjj_JetRelativePtEC2Up);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtHFDown",&mjj_JetRelativePtHFDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativePtHFUp",&mjj_JetRelativePtHFUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatECDown",&mjj_JetRelativeStatECDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatECUp",&mjj_JetRelativeStatECUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatFSRDown",&mjj_JetRelativeStatFSRDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatFSRUp",&mjj_JetRelativeStatFSRUp);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatHFDown",&mjj_JetRelativeStatHFDown);
    Run_Tree->SetBranchAddress("mjj_JetRelativeStatHFUp",&mjj_JetRelativeStatHFUp);
    Run_Tree->SetBranchAddress("mjj_JetSinglePionECALDown",&mjj_JetSinglePionECALDown);
    Run_Tree->SetBranchAddress("mjj_JetSinglePionECALUp",&mjj_JetSinglePionECALUp);
    Run_Tree->SetBranchAddress("mjj_JetSinglePionHCALDown",&mjj_JetSinglePionHCALDown);
    Run_Tree->SetBranchAddress("mjj_JetSinglePionHCALUp",&mjj_JetSinglePionHCALUp);
    Run_Tree->SetBranchAddress("mjj_JetTimePtEtaDown",&mjj_JetTimePtEtaDown);
    Run_Tree->SetBranchAddress("mjj_JetTimePtEtaUp",&mjj_JetTimePtEtaUp);

    Run_Tree->SetBranchAddress("metphi_JetAbsoluteFlavMapDown",&metphi_JetAbsoluteFlavMapDown);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteFlavMapUp",&metphi_JetAbsoluteFlavMapUp);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteMPFBiasDown",&metphi_JetAbsoluteMPFBiasDown);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteMPFBiasUp",&metphi_JetAbsoluteMPFBiasUp);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteScaleDown",&metphi_JetAbsoluteScaleDown);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteScaleUp",&metphi_JetAbsoluteScaleUp);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteStatDown",&metphi_JetAbsoluteStatDown);
    Run_Tree->SetBranchAddress("metphi_JetAbsoluteStatUp",&metphi_JetAbsoluteStatUp);
    Run_Tree->SetBranchAddress("metphi_JetFlavorQCDDown",&metphi_JetFlavorQCDDown);
    Run_Tree->SetBranchAddress("metphi_JetFlavorQCDUp",&metphi_JetFlavorQCDUp);
    Run_Tree->SetBranchAddress("metphi_JetFragmentationDown",&metphi_JetFragmentationDown);
    Run_Tree->SetBranchAddress("metphi_JetFragmentationUp",&metphi_JetFragmentationUp);
    Run_Tree->SetBranchAddress("metphi_JetPileUpDataMCDown",&metphi_JetPileUpDataMCDown);
    Run_Tree->SetBranchAddress("metphi_JetPileUpDataMCUp",&metphi_JetPileUpDataMCUp);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtBBDown",&metphi_JetPileUpPtBBDown);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtBBUp",&metphi_JetPileUpPtBBUp);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtEC1Down",&metphi_JetPileUpPtEC1Down);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtEC1Up",&metphi_JetPileUpPtEC1Up);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtEC2Down",&metphi_JetPileUpPtEC2Down);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtEC2Up",&metphi_JetPileUpPtEC2Up);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtHFDown",&metphi_JetPileUpPtHFDown);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtHFUp",&metphi_JetPileUpPtHFUp);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtRefDown",&metphi_JetPileUpPtRefDown);
    Run_Tree->SetBranchAddress("metphi_JetPileUpPtRefUp",&metphi_JetPileUpPtRefUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeBalDown",&metphi_JetRelativeBalDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeBalUp",&metphi_JetRelativeBalUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeFSRDown",&metphi_JetRelativeFSRDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeFSRUp",&metphi_JetRelativeFSRUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJEREC1Down",&metphi_JetRelativeJEREC1Down);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJEREC1Up",&metphi_JetRelativeJEREC1Up);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJEREC2Down",&metphi_JetRelativeJEREC2Down);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJEREC2Up",&metphi_JetRelativeJEREC2Up);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJERHFDown",&metphi_JetRelativeJERHFDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeJERHFUp",&metphi_JetRelativeJERHFUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtBBDown",&metphi_JetRelativePtBBDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtBBUp",&metphi_JetRelativePtBBUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtEC1Down",&metphi_JetRelativePtEC1Down);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtEC1Up",&metphi_JetRelativePtEC1Up);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtEC2Down",&metphi_JetRelativePtEC2Down);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtEC2Up",&metphi_JetRelativePtEC2Up);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtHFDown",&metphi_JetRelativePtHFDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativePtHFUp",&metphi_JetRelativePtHFUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatECDown",&metphi_JetRelativeStatECDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatECUp",&metphi_JetRelativeStatECUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatFSRDown",&metphi_JetRelativeStatFSRDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatFSRUp",&metphi_JetRelativeStatFSRUp);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatHFDown",&metphi_JetRelativeStatHFDown);
    Run_Tree->SetBranchAddress("metphi_JetRelativeStatHFUp",&metphi_JetRelativeStatHFUp);
    Run_Tree->SetBranchAddress("metphi_JetSinglePionECALDown",&metphi_JetSinglePionECALDown);
    Run_Tree->SetBranchAddress("metphi_JetSinglePionECALUp",&metphi_JetSinglePionECALUp);
    Run_Tree->SetBranchAddress("metphi_JetSinglePionHCALDown",&metphi_JetSinglePionHCALDown);
    Run_Tree->SetBranchAddress("metphi_JetSinglePionHCALUp",&metphi_JetSinglePionHCALUp);
    Run_Tree->SetBranchAddress("metphi_JetTimePtEtaDown",&metphi_JetTimePtEtaDown);
    Run_Tree->SetBranchAddress("metphi_JetTimePtEtaUp",&metphi_JetTimePtEtaUp);

    Run_Tree->SetBranchAddress("met_JetAbsoluteFlavMapDown",&met_JetAbsoluteFlavMapDown);
    Run_Tree->SetBranchAddress("met_JetAbsoluteFlavMapUp",&met_JetAbsoluteFlavMapUp);
    Run_Tree->SetBranchAddress("met_JetAbsoluteMPFBiasDown",&met_JetAbsoluteMPFBiasDown);
    Run_Tree->SetBranchAddress("met_JetAbsoluteMPFBiasUp",&met_JetAbsoluteMPFBiasUp);
    Run_Tree->SetBranchAddress("met_JetAbsoluteScaleDown",&met_JetAbsoluteScaleDown);
    Run_Tree->SetBranchAddress("met_JetAbsoluteScaleUp",&met_JetAbsoluteScaleUp);
    Run_Tree->SetBranchAddress("met_JetAbsoluteStatDown",&met_JetAbsoluteStatDown);
    Run_Tree->SetBranchAddress("met_JetAbsoluteStatUp",&met_JetAbsoluteStatUp);
    Run_Tree->SetBranchAddress("met_JetFlavorQCDDown",&met_JetFlavorQCDDown);
    Run_Tree->SetBranchAddress("met_JetFlavorQCDUp",&met_JetFlavorQCDUp);
    Run_Tree->SetBranchAddress("met_JetFragmentationDown",&met_JetFragmentationDown);
    Run_Tree->SetBranchAddress("met_JetFragmentationUp",&met_JetFragmentationUp);
    Run_Tree->SetBranchAddress("met_JetPileUpDataMCDown",&met_JetPileUpDataMCDown);
    Run_Tree->SetBranchAddress("met_JetPileUpDataMCUp",&met_JetPileUpDataMCUp);
    Run_Tree->SetBranchAddress("met_JetPileUpPtBBDown",&met_JetPileUpPtBBDown);
    Run_Tree->SetBranchAddress("met_JetPileUpPtBBUp",&met_JetPileUpPtBBUp);
    Run_Tree->SetBranchAddress("met_JetPileUpPtEC1Down",&met_JetPileUpPtEC1Down);
    Run_Tree->SetBranchAddress("met_JetPileUpPtEC1Up",&met_JetPileUpPtEC1Up);
    Run_Tree->SetBranchAddress("met_JetPileUpPtEC2Down",&met_JetPileUpPtEC2Down);
    Run_Tree->SetBranchAddress("met_JetPileUpPtEC2Up",&met_JetPileUpPtEC2Up);
    Run_Tree->SetBranchAddress("met_JetPileUpPtHFDown",&met_JetPileUpPtHFDown);
    Run_Tree->SetBranchAddress("met_JetPileUpPtHFUp",&met_JetPileUpPtHFUp);
    Run_Tree->SetBranchAddress("met_JetPileUpPtRefDown",&met_JetPileUpPtRefDown);
    Run_Tree->SetBranchAddress("met_JetPileUpPtRefUp",&met_JetPileUpPtRefUp);
    Run_Tree->SetBranchAddress("met_JetRelativeBalDown",&met_JetRelativeBalDown);
    Run_Tree->SetBranchAddress("met_JetRelativeBalUp",&met_JetRelativeBalUp);
    Run_Tree->SetBranchAddress("met_JetRelativeFSRDown",&met_JetRelativeFSRDown);
    Run_Tree->SetBranchAddress("met_JetRelativeFSRUp",&met_JetRelativeFSRUp);
    Run_Tree->SetBranchAddress("met_JetRelativeJEREC1Down",&met_JetRelativeJEREC1Down);
    Run_Tree->SetBranchAddress("met_JetRelativeJEREC1Up",&met_JetRelativeJEREC1Up);
    Run_Tree->SetBranchAddress("met_JetRelativeJEREC2Down",&met_JetRelativeJEREC2Down);
    Run_Tree->SetBranchAddress("met_JetRelativeJEREC2Up",&met_JetRelativeJEREC2Up);
    Run_Tree->SetBranchAddress("met_JetRelativeJERHFDown",&met_JetRelativeJERHFDown);
    Run_Tree->SetBranchAddress("met_JetRelativeJERHFUp",&met_JetRelativeJERHFUp);
    Run_Tree->SetBranchAddress("met_JetRelativePtBBDown",&met_JetRelativePtBBDown);
    Run_Tree->SetBranchAddress("met_JetRelativePtBBUp",&met_JetRelativePtBBUp);
    Run_Tree->SetBranchAddress("met_JetRelativePtEC1Down",&met_JetRelativePtEC1Down);
    Run_Tree->SetBranchAddress("met_JetRelativePtEC1Up",&met_JetRelativePtEC1Up);
    Run_Tree->SetBranchAddress("met_JetRelativePtEC2Down",&met_JetRelativePtEC2Down);
    Run_Tree->SetBranchAddress("met_JetRelativePtEC2Up",&met_JetRelativePtEC2Up);
    Run_Tree->SetBranchAddress("met_JetRelativePtHFDown",&met_JetRelativePtHFDown);
    Run_Tree->SetBranchAddress("met_JetRelativePtHFUp",&met_JetRelativePtHFUp);
    Run_Tree->SetBranchAddress("met_JetRelativeStatECDown",&met_JetRelativeStatECDown);
    Run_Tree->SetBranchAddress("met_JetRelativeStatECUp",&met_JetRelativeStatECUp);
    Run_Tree->SetBranchAddress("met_JetRelativeStatFSRDown",&met_JetRelativeStatFSRDown);
    Run_Tree->SetBranchAddress("met_JetRelativeStatFSRUp",&met_JetRelativeStatFSRUp);
    Run_Tree->SetBranchAddress("met_JetRelativeStatHFDown",&met_JetRelativeStatHFDown);
    Run_Tree->SetBranchAddress("met_JetRelativeStatHFUp",&met_JetRelativeStatHFUp);
    Run_Tree->SetBranchAddress("met_JetSinglePionECALDown",&met_JetSinglePionECALDown);
    Run_Tree->SetBranchAddress("met_JetSinglePionECALUp",&met_JetSinglePionECALUp);
    Run_Tree->SetBranchAddress("met_JetSinglePionHCALDown",&met_JetSinglePionHCALDown);
    Run_Tree->SetBranchAddress("met_JetSinglePionHCALUp",&met_JetSinglePionHCALUp);
    Run_Tree->SetBranchAddress("met_JetTimePtEtaDown",&met_JetTimePtEtaDown);
    Run_Tree->SetBranchAddress("met_JetTimePtEtaUp",&met_JetTimePtEtaUp);

    Run_Tree->SetBranchAddress("l2_decayMode",&l2_decayMode);
    Run_Tree->SetBranchAddress("gen_match_2",&gen_match_2);

cout<<"test2"<<endl;
     //######################################################
    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
    reader->AddVariable("pt_1_", &pt_1);
    reader->AddVariable("pt_2_", &pt_2);
    reader->AddVariable("fabs(dphi_12_)", &dphi_12);
    reader->AddVariable("met_", &met);
    ////reader->AddVariable("mt_1_", &mt_1);
    reader->AddVariable("mt_2_", &mt_2);
    ////reader->AddVariable("dphi_taumet_", &dphi_taumet);
    ////reader->AddVariable("njets_", &njets);
    ////reader->AddVariable("vbfmass_", &vbfmass);
    ////reader->AddVariable("vbfeta_", &vbfeta);
    ////reader->AddVariable("pt_1_/pt_2_", &ptrat);
    reader->AddVariable("fabs(eta_1_-eta_2_)", &deltaeta_12);
    reader->AddVariable("fabs(dphi_taumet_)", &dphi_taumet);
    reader->AddVariable("m_coll_", &m_coll);
    reader->AddVariable("mvis_", &mvis);

cout<<"test"<<endl;
    TString weightfile = "weights/TMVAClassification_BDT.weights.xml";
    TString methodName= TString("BDT") + TString(" method");
    reader->BookMVA(methodName, weightfile);

    //#########################################################
    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        float mass_jj=mjj;
        float number_jets=njets;

        int nombrejets[56]={njets_JESDown,njets_JESUp,njets_JetAbsoluteFlavMapDown,njets_JetAbsoluteFlavMapUp,njets_JetAbsoluteMPFBiasDown,njets_JetAbsoluteMPFBiasUp,njets_JetAbsoluteScaleDown,njets_JetAbsoluteScaleUp,njets_JetAbsoluteStatDown,njets_JetAbsoluteStatUp,njets_JetFlavorQCDDown,njets_JetFlavorQCDUp,njets_JetFragmentationDown,njets_JetFragmentationUp,njets_JetPileUpDataMCDown,njets_JetPileUpDataMCUp,njets_JetPileUpPtBBDown,njets_JetPileUpPtBBUp,njets_JetPileUpPtEC1Down,njets_JetPileUpPtEC1Up,njets_JetPileUpPtEC2Down,njets_JetPileUpPtEC2Up,njets_JetPileUpPtHFDown,njets_JetPileUpPtHFUp,njets_JetPileUpPtRefDown,njets_JetPileUpPtRefUp,njets_JetRelativeBalDown,njets_JetRelativeBalUp,njets_JetRelativeFSRDown,njets_JetRelativeFSRUp,njets_JetRelativeJEREC1Down,njets_JetRelativeJEREC1Up,njets_JetRelativeJEREC2Down,njets_JetRelativeJEREC2Up,njets_JetRelativeJERHFDown,njets_JetRelativeJERHFUp,njets_JetRelativePtBBDown,njets_JetRelativePtBBUp,njets_JetRelativePtEC1Down,njets_JetRelativePtEC1Up,njets_JetRelativePtEC2Down,njets_JetRelativePtEC2Up,njets_JetRelativePtHFDown,njets_JetRelativePtHFUp,njets_JetRelativeStatECDown,njets_JetRelativeStatECUp,njets_JetRelativeStatFSRDown,njets_JetRelativeStatFSRUp,njets_JetRelativeStatHFDown,njets_JetRelativeStatHFUp,njets_JetSinglePionECALDown,njets_JetSinglePionECALUp,njets_JetSinglePionHCALDown,njets_JetSinglePionHCALUp,njets_JetTimePtEtaDown,njets_JetTimePtEtaUp};

        float massejets[56]={mjj_JESDown,mjj_JESUp,mjj_JetAbsoluteFlavMapDown,mjj_JetAbsoluteFlavMapUp,mjj_JetAbsoluteMPFBiasDown,mjj_JetAbsoluteMPFBiasUp,mjj_JetAbsoluteScaleDown,mjj_JetAbsoluteScaleUp,mjj_JetAbsoluteStatDown,mjj_JetAbsoluteStatUp,mjj_JetFlavorQCDDown,mjj_JetFlavorQCDUp,mjj_JetFragmentationDown,mjj_JetFragmentationUp,mjj_JetPileUpDataMCDown,mjj_JetPileUpDataMCUp,mjj_JetPileUpPtBBDown,mjj_JetPileUpPtBBUp,mjj_JetPileUpPtEC1Down,mjj_JetPileUpPtEC1Up,mjj_JetPileUpPtEC2Down,mjj_JetPileUpPtEC2Up,mjj_JetPileUpPtHFDown,mjj_JetPileUpPtHFUp,mjj_JetPileUpPtRefDown,mjj_JetPileUpPtRefUp,mjj_JetRelativeBalDown,mjj_JetRelativeBalUp,mjj_JetRelativeFSRDown,mjj_JetRelativeFSRUp,mjj_JetRelativeJEREC1Down,mjj_JetRelativeJEREC1Up,mjj_JetRelativeJEREC2Down,mjj_JetRelativeJEREC2Up,mjj_JetRelativeJERHFDown,mjj_JetRelativeJERHFUp,mjj_JetRelativePtBBDown,mjj_JetRelativePtBBUp,mjj_JetRelativePtEC1Down,mjj_JetRelativePtEC1Up,mjj_JetRelativePtEC2Down,mjj_JetRelativePtEC2Up,mjj_JetRelativePtHFDown,mjj_JetRelativePtHFUp,mjj_JetRelativeStatECDown,mjj_JetRelativeStatECUp,mjj_JetRelativeStatFSRDown,mjj_JetRelativeStatFSRUp,mjj_JetRelativeStatHFDown,mjj_JetRelativeStatHFUp,mjj_JetSinglePionECALDown,mjj_JetSinglePionECALUp,mjj_JetSinglePionHCALDown,mjj_JetSinglePionHCALUp,mjj_JetTimePtEtaDown,mjj_JetTimePtEtaUp};

        float metenergie[56]={met_JESDown,met_JESUp,met_JetAbsoluteFlavMapDown,met_JetAbsoluteFlavMapUp,met_JetAbsoluteMPFBiasDown,met_JetAbsoluteMPFBiasUp,met_JetAbsoluteScaleDown,met_JetAbsoluteScaleUp,met_JetAbsoluteStatDown,met_JetAbsoluteStatUp,met_JetFlavorQCDDown,met_JetFlavorQCDUp,met_JetFragmentationDown,met_JetFragmentationUp,met_JetPileUpDataMCDown,met_JetPileUpDataMCUp,met_JetPileUpPtBBDown,met_JetPileUpPtBBUp,met_JetPileUpPtEC1Down,met_JetPileUpPtEC1Up,met_JetPileUpPtEC2Down,met_JetPileUpPtEC2Up,met_JetPileUpPtHFDown,met_JetPileUpPtHFUp,met_JetPileUpPtRefDown,met_JetPileUpPtRefUp,met_JetRelativeBalDown,met_JetRelativeBalUp,met_JetRelativeFSRDown,met_JetRelativeFSRUp,met_JetRelativeJEREC1Down,met_JetRelativeJEREC1Up,met_JetRelativeJEREC2Down,met_JetRelativeJEREC2Up,met_JetRelativeJERHFDown,met_JetRelativeJERHFUp,met_JetRelativePtBBDown,met_JetRelativePtBBUp,met_JetRelativePtEC1Down,met_JetRelativePtEC1Up,met_JetRelativePtEC2Down,met_JetRelativePtEC2Up,met_JetRelativePtHFDown,met_JetRelativePtHFUp,met_JetRelativeStatECDown,met_JetRelativeStatECUp,met_JetRelativeStatFSRDown,met_JetRelativeStatFSRUp,met_JetRelativeStatHFDown,met_JetRelativeStatHFUp,met_JetSinglePionECALDown,met_JetSinglePionECALUp,met_JetSinglePionHCALDown,met_JetSinglePionHCALUp,met_JetTimePtEtaDown,met_JetTimePtEtaUp};

        float metangle[56]={metphi_JESDown,metphi_JESUp,metphi_JetAbsoluteFlavMapDown,metphi_JetAbsoluteFlavMapUp,metphi_JetAbsoluteMPFBiasDown,metphi_JetAbsoluteMPFBiasUp,metphi_JetAbsoluteScaleDown,metphi_JetAbsoluteScaleUp,metphi_JetAbsoluteStatDown,metphi_JetAbsoluteStatUp,metphi_JetFlavorQCDDown,metphi_JetFlavorQCDUp,metphi_JetFragmentationDown,metphi_JetFragmentationUp,metphi_JetPileUpDataMCDown,metphi_JetPileUpDataMCUp,metphi_JetPileUpPtBBDown,metphi_JetPileUpPtBBUp,metphi_JetPileUpPtEC1Down,metphi_JetPileUpPtEC1Up,metphi_JetPileUpPtEC2Down,metphi_JetPileUpPtEC2Up,metphi_JetPileUpPtHFDown,metphi_JetPileUpPtHFUp,metphi_JetPileUpPtRefDown,metphi_JetPileUpPtRefUp,metphi_JetRelativeBalDown,metphi_JetRelativeBalUp,metphi_JetRelativeFSRDown,metphi_JetRelativeFSRUp,metphi_JetRelativeJEREC1Down,metphi_JetRelativeJEREC1Up,metphi_JetRelativeJEREC2Down,metphi_JetRelativeJEREC2Up,metphi_JetRelativeJERHFDown,metphi_JetRelativeJERHFUp,metphi_JetRelativePtBBDown,metphi_JetRelativePtBBUp,metphi_JetRelativePtEC1Down,metphi_JetRelativePtEC1Up,metphi_JetRelativePtEC2Down,metphi_JetRelativePtEC2Up,metphi_JetRelativePtHFDown,metphi_JetRelativePtHFUp,metphi_JetRelativeStatECDown,metphi_JetRelativeStatECUp,metphi_JetRelativeStatFSRDown,metphi_JetRelativeStatFSRUp,metphi_JetRelativeStatHFDown,metphi_JetRelativeStatHFUp,metphi_JetSinglePionECALDown,metphi_JetSinglePionECALUp,metphi_JetSinglePionHCALDown,metphi_JetSinglePionHCALUp,metphi_JetTimePtEtaDown,metphi_JetTimePtEtaUp};


        TLorentzVector mytau;
        mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
        TLorentzVector mymet;
        mymet.SetPtEtaPhiM(met,0,metphi,0);

        if (tes==30){
            mymet.SetPtEtaPhiM(met_UESUp,0,metphi_UESUp,0);
        }
        else if (tes==31){
            mymet.SetPtEtaPhiM(met_UESDown,0,metphi_UESDown,0);
        }
        else if (tes==32){
            mymet.SetPtEtaPhiM(met_ChargedUESUp,0,metphi_ChargedUESUp,0);
        }
        else if (tes==33){
            mymet.SetPtEtaPhiM(met_ChargedUESDown,0,metphi_ChargedUESDown,0);
        }
        else if (tes==34){
            mymet.SetPtEtaPhiM(met_HFUESUp,0,metphi_HFUESUp,0);
        }
        else if (tes==35){
            mymet.SetPtEtaPhiM(met_HFUESDown,0,metphi_HFUESDown,0);
        }
        else if (tes==36){
            mymet.SetPtEtaPhiM(met_ECALUESUp,0,metphi_ECALUESUp,0);
        }
        else if (tes==37){
            mymet.SetPtEtaPhiM(met_ECALUESDown,0,metphi_ECALUESDown,0);
        }
        else if (tes==38){
            mymet.SetPtEtaPhiM(met_HCALUESUp,0,metphi_HCALUESUp,0);
        }
        else if (tes==39){
            mymet.SetPtEtaPhiM(met_HCALUESDown,0,metphi_HCALUESDown,0);
        }
        else if (tes>=100){
            mass_jj=massejets[int(tes-100)];
            number_jets=nombrejets[int(tes-100)];
            mymet.SetPtEtaPhiM(metenergie[int(tes-100)],0,metangle[int(tes-100)],0);
        }


        if (input!="Data.root" && gen_match_2==5 && l2_decayMode==0){
           mymet=mymet+0.018*mytau;
           mytau=0.982*mytau;
        }
        if (input!="Data.root" && gen_match_2==5 && l2_decayMode==1){
           mymet=mymet-0.010*mytau;
           mytau=1.010*mytau;
        }
        if (input!="Data.root" && gen_match_2==5 && l2_decayMode==10){
           mymet=mymet-0.004*mytau;
           mytau=1.004*mytau;
        }
        if (input!="Data.root" && gen_match_2<5 && l2_decayMode==1){
           mymet=mymet-0.10*mytau;
           mytau=1.10*mytau;
        }

        if (tes==10 && gen_match_2==5){
            mytau=1.012*mytau;
            float mex = mymet.Px()-0.012*(mytau.Px()/1.012);
            float mey = mymet.Py()-0.012*(mytau.Py()/1.012);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==-10  && gen_match_2==5){
            mytau=0.988*mytau;
            float mex = mymet.Px()+0.012*(mytau.Px()/0.988);
            float mey = mymet.Py()+0.012*(mytau.Py()/0.988);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==11 && gen_match_2==5 && l2_decayMode==0){
            mytau=1.012*mytau;
            float mex = mymet.Px()-0.012*(mytau.Px()/1.012);
            float mey = mymet.Py()-0.012*(mytau.Py()/1.012);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==-11  && gen_match_2==5 && l2_decayMode==0){
            mytau=0.988*mytau;
            float mex = mymet.Px()+0.012*(mytau.Px()/0.988);
            float mey = mymet.Py()+0.012*(mytau.Py()/0.988);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==12 && gen_match_2==5 && l2_decayMode==1){
            mytau=1.012*mytau;
            float mex = mymet.Px()-0.012*(mytau.Px()/1.012);
            float mey = mymet.Py()-0.012*(mytau.Py()/1.012);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==-12 && gen_match_2==5 && l2_decayMode==1){
            mytau=0.988*mytau;
            float mex = mymet.Px()+0.012*(mytau.Px()/0.988);
            float mey = mymet.Py()+0.012*(mytau.Py()/0.988);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==13 && gen_match_2==5 && l2_decayMode==10){
            mytau=1.012*mytau;
            float mex = mymet.Px()-0.012*(mytau.Px()/1.012);
            float mey = mymet.Py()-0.012*(mytau.Py()/1.012);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==-13 && gen_match_2==5 && l2_decayMode==10){
            mytau=0.988*mytau;
            float mex = mymet.Px()+0.012*(mytau.Px()/0.988);
            float mey = mymet.Py()+0.012*(mytau.Py()/0.988);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==20){
	    myele.SetPtEtaPhiM(pt_1_EScaleUp,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1_EScaleUp)/myele.Pt())*myele;
	}
        else if (tes==21){
            myele.SetPtEtaPhiM(pt_1_EScaleDown,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1_EScaleDown)/myele.Pt())*myele;
        }
        else if (tes==22){
            myele.SetPtEtaPhiM(pt_1_EResRhoUp,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1_EResRhoUp)/myele.Pt())*myele;
        }
        else if (tes==23){
            myele.SetPtEtaPhiM(pt_1_EResRhoDown,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1_EResRhoDown)/myele.Pt())*myele;
        }
        else if (tes==24){
            myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1)/myele.Pt())*myele;
        }
        else if (tes==25){
            myele.SetPtEtaPhiM(pt_1_EResPhiDown,eta_1,phi_1,m_1);
            mymet=mymet+((pt_1-pt_1_EResPhiDown)/myele.Pt())*myele;
        }
        else if (tes==40 && gen_match_2<5 && l2_decayMode==0){
            mytau=1.03*mytau;
            float mex = mymet.Px()-0.030*(mytau.Px()/1.03);
            float mey = mymet.Py()-0.030*(mytau.Py()/1.03);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==41 && gen_match_2<5 && l2_decayMode==0){
            mytau=0.97*mytau;
            float mex = mymet.Px()+0.030*(mytau.Px()/0.97);
            float mey = mymet.Py()+0.030*(mytau.Py()/0.97);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==42 && gen_match_2<5 && l2_decayMode==1){
            mytau=1.03*mytau;
            float mex = mymet.Px()-0.030*(mytau.Px()/1.03);
            float mey = mymet.Py()-0.030*(mytau.Py()/1.03);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }
        else if (tes==43 && gen_match_2<5 && l2_decayMode==1){
            mytau=0.97*mytau;
            float mex = mymet.Px()+0.030*(mytau.Px()/0.97);
            float mey = mymet.Py()+0.030*(mytau.Py()/0.97);
            mymet.SetPxPyPzE(mex,mey,0,sqrt(mex*mex+mey*mey));
        }

        float collinear_mass=1.0;;
        float mt_emet=1.0;//TMass_F(myele.Pt(),myele.Px(),myele.Py(),mymet.Pt(),mymet.Phi());
        float mt_taumet=1.0;//TMass_F(mytau.Pt(),mytau.Px(),mytau.Py(),mymet.Pt(),mymet.Phi());
        if (fabs(dphi_taumet)<0.005) mt_taumet=0;
	float visible_mass=(myele+mytau).M();

        //bdt_all = KNNforETau(reader, pt_1, pt_2, mt_1, mt_2, dphi_12, dphi_taumet, met, njets, mjj, jdeta, eta_1, eta_2, m_coll);
        //cout<<myele.Pt()<<" "<<mytau.Pt()<<" "<<mt_emet<<" "<<mt_taumet<<" "<<dphi_12<<" "<<dphi_taumet<<" "<<mymet.Pt()<<" "<<number_jets<<" "<<mass_jj<<" "<<jdeta<<" "<<myele.Eta()<<" "<<mytau.Eta()<<" "<<collinear_mass<<" "<<visible_mass<<endl;
        bdt_all = KNNforETau(reader, myele.Pt(), mytau.Pt(), mt_emet, mt_taumet, dphi_12, dphi_taumet, mymet.Pt(), number_jets, mass_jj, jdeta, myele.Eta(), mytau.Eta(), collinear_mass, visible_mass);
        bbdt->Fill();
    }

    Run_Tree->Write();
    delete f_Double;
}

