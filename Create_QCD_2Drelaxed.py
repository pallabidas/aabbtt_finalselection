if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'allJES','up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown','allTES'], help="Which TES?")
    options = parser.parse_args()

    factor=1.06


    postfix=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_JetAbsoluteFlavMap_13TeVDown","_CMS_scale_j_JetAbsoluteFlavMap_13TeVUp","_CMS_scale_j_JetAbsoluteMPFBias_13TeVDown","_CMS_scale_j_JetAbsoluteMPFBias_13TeVUp","_CMS_scale_j_JetAbsoluteScale_13TeVDown","_CMS_scale_j_JetAbsoluteScale_13TeVUp","_CMS_scale_j_JetAbsoluteStat_13TeVDown","_CMS_scale_j_JetAbsoluteStat_13TeVUp","_CMS_scale_j_JetFlavorQCD_13TeVDown","_CMS_scale_j_JetFlavorQCD_13TeVUp","_CMS_scale_j_JetFragmentation_13TeVDown","_CMS_scale_j_JetFragmentation_13TeVUp","_CMS_scale_j_JetPileUpDataMC_13TeVDown","_CMS_scale_j_JetPileUpDataMC_13TeVUp","_CMS_scale_j_JetPileUpPtBB_13TeVDown","_CMS_scale_j_JetPileUpPtBB_13TeVUp","_CMS_scale_j_JetPileUpPtEC1_13TeVDown","_CMS_scale_j_JetPileUpPtEC1_13TeVUp","_CMS_scale_j_JetPileUpPtEC2_13TeVDown","_CMS_scale_j_JetPileUpPtEC2_13TeVUp","_CMS_scale_j_JetPileUpPtHF_13TeVDown","_CMS_scale_j_JetPileUpPtHF_13TeVUp","_CMS_scale_j_JetPileUpPtRef_13TeVDown","_CMS_scale_j_JetPileUpPtRef_13TeVUp","_CMS_scale_j_JetRelativeBal_13TeVDown","_CMS_scale_j_JetRelativeBal_13TeVUp","_CMS_scale_j_JetRelativeFSR_13TeVDown","_CMS_scale_j_JetRelativeFSR_13TeVUp","_CMS_scale_j_JetRelativeJEREC1_13TeVDown","_CMS_scale_j_JetRelativeJEREC1_13TeVUp","_CMS_scale_j_JetRelativeJEREC2_13TeVDown","_CMS_scale_j_JetRelativeJEREC2_13TeVUp","_CMS_scale_j_JetRelativeJERHF_13TeVDown","_CMS_scale_j_JetRelativeJERHF_13TeVUp","_CMS_scale_j_JetRelativePtBB_13TeVDown","_CMS_scale_j_JetRelativePtBB_13TeVUp","_CMS_scale_j_JetRelativePtEC1_13TeVDown","_CMS_scale_j_JetRelativePtEC1_13TeVUp","_CMS_scale_j_JetRelativePtEC2_13TeVDown","_CMS_scale_j_JetRelativePtEC2_13TeVUp","_CMS_scale_j_JetRelativePtHF_13TeVDown","_CMS_scale_j_JetRelativePtHF_13TeVUp","_CMS_scale_j_JetRelativeStatEC_13TeVDown","_CMS_scale_j_JetRelativeStatEC_13TeVUp","_CMS_scale_j_JetRelativeStatFSR_13TeVDown","_CMS_scale_j_JetRelativeStatFSR_13TeVUp","_CMS_scale_j_JetRelativeStatHF_13TeVDown","_CMS_scale_j_JetRelativeStatHF_13TeVUp","_CMS_scale_j_JetSinglePionECAL_13TeVDown","_CMS_scale_j_JetSinglePionECAL_13TeVUp","_CMS_scale_j_JetSinglePionHCAL_13TeVDown","_CMS_scale_j_JetSinglePionHCAL_13TeVUp","_CMS_scale_j_JetTimePtEta_13TeVDown","_CMS_scale_j_JetTimePtEta_13TeVUp"]
    post2=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfix0=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfix1=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfix2=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfixTES=["_CMS_scale_t_13TeVDown","_CMS_scale_t_13TeVUp","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_btag_13TeVUp","_CMS_btag_13TeVDown","_CMS_misbtag_13TeVUp","_CMS_misbtag_13TeVDown","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_scale_jet_13TeVDown","_CMS_scale_jet_13TeVUp"]

    if options.scale!="allJES":
        postfix[0]=""

    if (options.scale!='allJES'):
       postfix0[0]=""
       postfix1[0]=""
       postfix2[0]=""
    if (options.scale=="up"):
        postfix0[0]="_CMS_scale_t_mt_13TeVUp"
        postfix1[0]="_CMS_scale_t_mt_13TeVUp"
        postfix2[0]="_CMS_scale_t_mt_13TeVUp"
    if (options.scale=="down"):
        postfix0[0]="_CMS_scale_t_mt_13TeVDown"
        postfix1[0]="_CMS_scale_t_mt_13TeVDown"
        postfix2[0]="_CMS_scale_t_mt_13TeVDown"
    if (options.scale=="JESup"):
        postfix0[0]="_CMS_scale_j_13TeVUp"
        postfix1[0]="_CMS_scale_j_13TeVUp"
        postfix2[0]="_CMS_scale_j_13TeVUp"
    if (options.scale=="JESdown"):
        postfix0[0]="_CMS_scale_j_13TeVDown"
        postfix1[0]="_CMS_scale_j_13TeVDown"
        postfix2[0]="_CMS_scale_j_13TeVDown"
    if (options.scale=="qcdup"):
        postfix0[0]="_QCDSFUncert_mt_all_13TeVUp"
        postfix1[0]="_QCDSFUncert_mt_low_13TeVUp"
        postfix2[0]="_QCDSFUncert_mt_vbf_13TeVUp"
    if (options.scale=="qcddown"):
        postfix0[0]="_QCDSFUncert_mt_all_13TeVDown"
        postfix1[0]="_QCDSFUncert_mt_low_13TeVDown"
        postfix2[0]="_QCDSFUncert_mt_vbf_13TeVDown"
    if (options.scale=="wup"):
        postfix0[0]="_WSFUncert_mt_all_13TeVUp"
        postfix1[0]="_WSFUncert_mt_low_13TeVUp"
        postfix2[0]="_WSFUncert_mt_vbf_13TeVUp"
    if (options.scale=="wdown"):
        postfix0[0]="_WSFUncert_mt_all_13TeVDown"
        postfix1[0]="_WSFUncert_mt_low_13TeVDown"
        postfix2[0]="_WSFUncert_mt_vbf_13TeVDown"

    if (options.scale=="JESup"):
        post2[0]="_CMS_scale_j_13TeVUp"
    if (options.scale=="JESdown"):
        post2[0]="_CMS_scale_j_13TeVDown"
    if (options.scale=="up"):
        post2[0]="_CMS_scale_t_mt_13TeVUp"
    if (options.scale=="down"):
        post2[0]="_CMS_scale_t_mt_13TeVDown"
    if (options.scale=="qcdup"):
        post2[0]=""
    if (options.scale=="qcddown"):
        post2[0]=""
    if (options.scale=="wup"):
        post2[0]=""
    if (options.scale=="wdown"):
        post2[0]=""
    if (options.scale=="nominal"):
        post2[0]=""
        postfix0[0]=""
        postfix1[0]=""
        postfix2[0]=""

    facteur=1.0

    if options.scale=="allTES":
      for j in range(0,14):
         post2[j]=postfixTES[j]
         postfix0[j]=postfixTES[j]
         postfix1[j]=postfixTES[j]
         postfix2[j]=postfixTES[j]

    mydir=options.scale
    if options.scale=="allJES":
       mydir="JESup"
    if options.scale=="nominal":
       mydir="nominal"

    if options.scale=="up" or options.scale=="down" or options.scale=="JESup" or options.scale=="JESdown" or options.scale=="allJES" or options.scale=="allTES":
       fDYJ=ROOT.TFile("files_nominal/ZJ.root","r")
       fDYL=ROOT.TFile("files_nominal/ZL.root","r")
       fDYS=ROOT.TFile("files_"+mydir+"/ZTT.root","r")
       fW=ROOT.TFile("files_"+mydir+"/W.root","r")
       fTTJ=ROOT.TFile("files_"+mydir+"/TTJ.root","r")
       fTTT=ROOT.TFile("files_"+mydir+"/TTT.root","r")
       fTTL=ROOT.TFile("files_"+mydir+"/TTL.root","r")
       fVV=ROOT.TFile("files_"+mydir+"/VV.root","r")
       fST=ROOT.TFile("files_"+mydir+"/ST.root","r")
       fData=ROOT.TFile("files_nominal/Data.root","r")
       fout=ROOT.TFile("files_"+mydir+"/QCD.root","recreate")
    else:
       fDYJ=ROOT.TFile("files_nominal/ZJ.root","r")
       fDYL=ROOT.TFile("files_nominal/ZL.root","r")
       fDYS=ROOT.TFile("files_nominal/ZTT.root","r")
       fW=ROOT.TFile("files_nominal/W.root","r")
       fTTJ=ROOT.TFile("files_nominal/TTJ.root","r")
       fTTT=ROOT.TFile("files_nominal/TTT.root","r")
       fTTL=ROOT.TFile("files_nominal/TTL.root","r")
       fVV=ROOT.TFile("files_nominal/VV.root","r")
       fST=ROOT.TFile("files_nominal/ST.root","r")
       fData=ROOT.TFile("files_nominal/Data.root","r")
       fout=ROOT.TFile("files_nominal/QCD.root","recreate")

    fout.cd()
    dir_incl_1b=fout.mkdir("mt_incl_1b")
    dir_1b=fout.mkdir("mt_1b")
    dir_1b_lt80=fout.mkdir("mt_1b_lt80")
    dir_1b_80to100=fout.mkdir("mt_1b_80to100")
    dir_1b_100to120=fout.mkdir("mt_1b_100to120")
    dir_incl_2b=fout.mkdir("mt_incl_2b")
    dir_2b=fout.mkdir("mt_2b")

    nbhist=1
    if options.scale=="allJES":
       nbhist=56
    if options.scale=="allTES":
       nbhist=18

    for k in range(0,nbhist):
        hSS_incl_2b=fData.Get("SSincl_2b/data_obs")
        hSS_incl_2b.Add(fDYJ.Get("SSincl_2b/ZJ"),-1)
        hSS_incl_2b.Add(fDYL.Get("SSincl_2b/ZL"),-1)
        hSS_incl_2b.Add(fTTJ.Get("SSincl_2b/TTJ"+post2[k]),-1)
        hSS_incl_2b.Add(fTTT.Get("SSincl_2b/TTT"+post2[k]),-1)
        hSS_incl_2b.Add(fTTL.Get("SSincl_2b/TTL"+post2[k]),-1)
        hSS_incl_2b.Add(fW.Get("SSincl_2b/W"+postfix0[k]),-1)
        hSS_incl_2b.Add(fVV.Get("SSincl_2b/VV"+post2[k]),-1)
        hSS_incl_2b.Add(fST.Get("SSincl_2b/ST"+post2[k]),-1)
        hSS_incl_2b.Add(fDYS.Get("SSincl_2b/ZTT"+post2[k]),-1)
        hSS_incl_2b.SetName("QCD"+postfix0[k])
        hSS_incl_2b.Scale(factor)
        for i in range(0,hSS_incl_2b.GetSize()-2):
            if hSS_incl_2b.GetBinContent(i)<0:
                hSS_incl_2b.SetBinError(i,max(0,hSS_incl_2b.GetBinError(i)+hSS_incl_2b.GetBinError(i)))
                hSS_incl_2b.SetBinContent(i,0)

        hSS_incl_1b=fData.Get("SSincl_1b/data_obs")
        hSS_incl_1b.Add(fDYJ.Get("SSincl_1b/ZJ"),-1)
        hSS_incl_1b.Add(fDYL.Get("SSincl_1b/ZL"),-1)
        hSS_incl_1b.Add(fTTJ.Get("SSincl_1b/TTJ"+post2[k]),-1)
        hSS_incl_1b.Add(fTTT.Get("SSincl_1b/TTT"+post2[k]),-1)
        hSS_incl_1b.Add(fTTL.Get("SSincl_1b/TTL"+post2[k]),-1)
        hSS_incl_1b.Add(fW.Get("SSincl_1b/W"+postfix0[k]),-1)
        hSS_incl_1b.Add(fVV.Get("SSincl_1b/VV"+post2[k]),-1)
        hSS_incl_1b.Add(fST.Get("SSincl_1b/ST"+post2[k]),-1)
        hSS_incl_1b.Add(fDYS.Get("SSincl_1b/ZTT"+post2[k]),-1)
        hSS_incl_1b.SetName("QCD"+postfix0[k])
        hSS_incl_1b.Scale(factor)
        for i in range(0,hSS_incl_1b.GetSize()-2):
            if hSS_incl_1b.GetBinContent(i)<0:
                hSS_incl_1b.SetBinError(i,max(0,hSS_incl_1b.GetBinError(i)+hSS_incl_1b.GetBinError(i)))
                hSS_incl_1b.SetBinContent(i,0)

        hSS_incl_1b_lt80=fData.Get("SS1b_lt80/data_obs")
        hSS_incl_1b_lt80.Add(fDYJ.Get("SS1b_lt80/ZJ"),-1)
        hSS_incl_1b_lt80.Add(fDYL.Get("SS1b_lt80/ZL"),-1)
        hSS_incl_1b_lt80.Add(fTTJ.Get("SS1b_lt80/TTJ"+post2[k]),-1)
        hSS_incl_1b_lt80.Add(fTTT.Get("SS1b_lt80/TTT"+post2[k]),-1)
        hSS_incl_1b_lt80.Add(fTTL.Get("SS1b_lt80/TTL"+post2[k]),-1)
        hSS_incl_1b_lt80.Add(fW.Get("SS1b_lt80/W"+postfix0[k]),-1)
        hSS_incl_1b_lt80.Add(fVV.Get("SS1b_lt80/VV"+post2[k]),-1)
        hSS_incl_1b_lt80.Add(fST.Get("SS1b_lt80/ST"+post2[k]),-1)
        hSS_incl_1b_lt80.Add(fDYS.Get("SS1b_lt80/ZTT"+post2[k]),-1)
        hSS_incl_1b_lt80.SetName("QCD"+postfix0[k])
        hSS_incl_1b_lt80.Scale(factor)
        for i in range(0,hSS_incl_1b_lt80.GetSize()-2):
            if hSS_incl_1b_lt80.GetBinContent(i)<0:
                hSS_incl_1b_lt80.SetBinError(i,max(0,hSS_incl_1b_lt80.GetBinError(i)+hSS_incl_1b_lt80.GetBinError(i)))
                hSS_incl_1b_lt80.SetBinContent(i,0)

        hSS_incl_1b_80to100=fData.Get("SS1b_80to100/data_obs")
        hSS_incl_1b_80to100.Add(fDYJ.Get("SS1b_80to100/ZJ"),-1)
        hSS_incl_1b_80to100.Add(fDYL.Get("SS1b_80to100/ZL"),-1)
        hSS_incl_1b_80to100.Add(fTTJ.Get("SS1b_80to100/TTJ"+post2[k]),-1)
        hSS_incl_1b_80to100.Add(fTTT.Get("SS1b_80to100/TTT"+post2[k]),-1)
        hSS_incl_1b_80to100.Add(fTTL.Get("SS1b_80to100/TTL"+post2[k]),-1)
        hSS_incl_1b_80to100.Add(fW.Get("SS1b_80to100/W"+postfix0[k]),-1)
        hSS_incl_1b_80to100.Add(fVV.Get("SS1b_80to100/VV"+post2[k]),-1)
        hSS_incl_1b_80to100.Add(fST.Get("SS1b_80to100/ST"+post2[k]),-1)
        hSS_incl_1b_80to100.Add(fDYS.Get("SS1b_80to100/ZTT"+post2[k]),-1)
        hSS_incl_1b_80to100.SetName("QCD"+postfix0[k])
        hSS_incl_1b_80to100.Scale(factor)
        for i in range(0,hSS_incl_1b_80to100.GetSize()-2):
            if hSS_incl_1b_80to100.GetBinContent(i)<0:
                hSS_incl_1b_80to100.SetBinError(i,max(0,hSS_incl_1b_80to100.GetBinError(i)+hSS_incl_1b_80to100.GetBinError(i)))
                hSS_incl_1b_80to100.SetBinContent(i,0)

        hSS_incl_1b_100to120=fData.Get("SS1b_100to120/data_obs")
        hSS_incl_1b_100to120.Add(fDYJ.Get("SS1b_100to120/ZJ"),-1)
        hSS_incl_1b_100to120.Add(fDYL.Get("SS1b_100to120/ZL"),-1)
        hSS_incl_1b_100to120.Add(fTTJ.Get("SS1b_100to120/TTJ"+post2[k]),-1)
        hSS_incl_1b_100to120.Add(fTTT.Get("SS1b_100to120/TTT"+post2[k]),-1)
        hSS_incl_1b_100to120.Add(fTTL.Get("SS1b_100to120/TTL"+post2[k]),-1)
        hSS_incl_1b_100to120.Add(fW.Get("SS1b_100to120/W"+postfix0[k]),-1)
        hSS_incl_1b_100to120.Add(fVV.Get("SS1b_100to120/VV"+post2[k]),-1)
        hSS_incl_1b_100to120.Add(fST.Get("SS1b_100to120/ST"+post2[k]),-1)
        hSS_incl_1b_100to120.Add(fDYS.Get("SS1b_100to120/ZTT"+post2[k]),-1)
        hSS_incl_1b_100to120.SetName("QCD"+postfix0[k])
        hSS_incl_1b_100to120.Scale(factor)
        for i in range(0,hSS_incl_1b_100to120.GetSize()-2):
            if hSS_incl_1b_100to120.GetBinContent(i)<0:
                hSS_incl_1b_100to120.SetBinError(i,max(0,hSS_incl_1b_100to120.GetBinError(i)+hSS_incl_1b_100to120.GetBinError(i)))
                hSS_incl_1b_100to120.SetBinContent(i,0)

        hQCD_incl_2b=fData.Get("QCDincl_2b/data_obs")
        hQCD_incl_2b.Add(fDYJ.Get("QCDincl_2b/ZJ"),-1)
        hQCD_incl_2b.Add(fDYL.Get("QCDincl_2b/ZL"),-1)
        hQCD_incl_2b.Add(fTTJ.Get("QCDincl_2b/TTJ"+post2[k]),-1)
        hQCD_incl_2b.Add(fTTT.Get("QCDincl_2b/TTT"+post2[k]),-1)
        hQCD_incl_2b.Add(fTTL.Get("QCDincl_2b/TTL"+post2[k]),-1)
        hQCD_incl_2b.Add(fW.Get("QCDincl_2b/W"+postfix0[k]),-1)
        hQCD_incl_2b.Add(fVV.Get("QCDincl_2b/VV"+post2[k]),-1)
        hQCD_incl_2b.Add(fST.Get("QCDincl_2b/ST"+post2[k]),-1)
        hQCD_incl_2b.Add(fDYS.Get("QCDincl_2b/ZTT"+post2[k]),-1)
        hQCD_incl_2b.SetName("QCD"+postfix0[k])
        hQCD_incl_2b.Scale(factor)
        for i in range(0,hQCD_incl_2b.GetSize()-2):
            if hQCD_incl_2b.GetBinContent(i)<0:
                hQCD_incl_2b.SetBinError(i,max(0,hQCD_incl_2b.GetBinError(i)+hQCD_incl_2b.GetBinError(i)))
                hQCD_incl_2b.SetBinContent(i,0)

        hQCD_incl_1b=fData.Get("QCDincl_1b/data_obs")
        hQCD_incl_1b.Add(fDYJ.Get("QCDincl_1b/ZJ"),-1)
        hQCD_incl_1b.Add(fDYL.Get("QCDincl_1b/ZL"),-1)
        hQCD_incl_1b.Add(fTTJ.Get("QCDincl_1b/TTJ"+post2[k]),-1)
        hQCD_incl_1b.Add(fTTT.Get("QCDincl_1b/TTT"+post2[k]),-1)
        hQCD_incl_1b.Add(fTTL.Get("QCDincl_1b/TTL"+post2[k]),-1)
        hQCD_incl_1b.Add(fW.Get("QCDincl_1b/W"+postfix0[k]),-1)
        hQCD_incl_1b.Add(fVV.Get("QCDincl_1b/VV"+post2[k]),-1)
        hQCD_incl_1b.Add(fST.Get("QCDincl_1b/ST"+post2[k]),-1)
        hQCD_incl_1b.Add(fDYS.Get("QCDincl_1b/ZTT"+post2[k]),-1)
        hQCD_incl_1b.SetName("QCD"+postfix0[k])
        hQCD_incl_1b.Scale(factor)
        for i in range(0,hQCD_incl_1b.GetSize()-2):
            if hQCD_incl_1b.GetBinContent(i)<0:
                hQCD_incl_1b.SetBinError(i,max(0,hQCD_incl_1b.GetBinError(i)+hQCD_incl_1b.GetBinError(i)))
                hQCD_incl_1b.SetBinContent(i,0)

        hSS_2b=fData.Get("SS2b/data_obs")
        hSS_2b.Add(fDYJ.Get("SS2b/ZJ"),-1)
        hSS_2b.Add(fDYL.Get("SS2b/ZL"),-1)
        hSS_2b.Add(fTTJ.Get("SS2b/TTJ"+post2[k]),-1)
        hSS_2b.Add(fTTT.Get("SS2b/TTT"+post2[k]),-1)
        hSS_2b.Add(fTTL.Get("SS2b/TTL"+post2[k]),-1)
        hSS_2b.Add(fW.Get("SS2b/W"+postfix1[k]),-1)
        hSS_2b.Add(fVV.Get("SS2b/VV"+post2[k]),-1)
        hSS_2b.Add(fST.Get("SS2b/ST"+post2[k]),-1)
        hSS_2b.Add(fDYS.Get("SS2b/ZTT"+post2[k]),-1)
        hSS_2b.SetName("QCD"+postfix1[k])
        hSS_2b.Scale(factor)
        for i in range(0,hSS_2b.GetSize()-2):
            if hSS_2b.GetBinContent(i)<0:
                hSS_2b.SetBinError(i,max(0,hSS_2b.GetBinError(i)+hSS_2b.GetBinError(i)))
                hSS_2b.SetBinContent(i,0)

        hSS_1b=fData.Get("SS1b/data_obs")
        hSS_1b.Add(fDYJ.Get("SS1b/ZJ"),-1)
        hSS_1b.Add(fDYL.Get("SS1b/ZL"),-1)
        hSS_1b.Add(fTTJ.Get("SS1b/TTJ"+post2[k]),-1)
        hSS_1b.Add(fTTT.Get("SS1b/TTT"+post2[k]),-1)
        hSS_1b.Add(fTTL.Get("SS1b/TTL"+post2[k]),-1)
        hSS_1b.Add(fW.Get("SS1b/W"+postfix1[k]),-1)
        hSS_1b.Add(fVV.Get("SS1b/VV"+post2[k]),-1)
        hSS_1b.Add(fST.Get("SS1b/ST"+post2[k]),-1)
        hSS_1b.Add(fDYS.Get("SS1b/ZTT"+post2[k]),-1)
        hSS_1b.SetName("QCD"+postfix1[k])
        hSS_1b.Scale(factor)
        for i in range(0,hSS_1b.GetSize()-2):
            if hSS_1b.GetBinContent(i)<0:
                hSS_1b.SetBinError(i,max(0,hSS_1b.GetBinError(i)+hSS_1b.GetBinError(i)))
                hSS_1b.SetBinContent(i,0)

        hQCD2b=fData.Get("QCD2b/data_obs")
        hQCD2b.Add(fDYJ.Get("QCD2b/ZJ"),-1)
        hQCD2b.Add(fDYL.Get("QCD2b/ZL"),-1)
        hQCD2b.Add(fTTJ.Get("QCD2b/TTJ"+post2[k]),-1)
        hQCD2b.Add(fTTT.Get("QCD2b/TTT"+post2[k]),-1)
        hQCD2b.Add(fTTL.Get("QCD2b/TTL"+post2[k]),-1)
        hQCD2b.Add(fW.Get("QCD2b/W"+postfix1[k]),-1)
        hQCD2b.Add(fVV.Get("QCD2b/VV"+post2[k]),-1)
        hQCD2b.Add(fST.Get("QCD2b/ST"+post2[k]),-1)
        hQCD2b.Add(fDYS.Get("QCD2b/ZTT"+post2[k]),-1)
        hQCD2b.SetName("QCD"+postfix1[k])
        hQCD2b.Scale(factor)
        for i in range(0,hQCD2b.GetSize()-2):
            if hQCD2b.GetBinContent(i)<0:
                hQCD2b.SetBinError(i,max(0,hQCD2b.GetBinError(i)+hQCD2b.GetBinError(i)))
                hQCD2b.SetBinContent(i,0)

        hQCD1b=fData.Get("QCD1b/data_obs")
        hQCD1b.Add(fDYJ.Get("QCD1b/ZJ"),-1)
        hQCD1b.Add(fDYL.Get("QCD1b/ZL"),-1)
        hQCD1b.Add(fTTJ.Get("QCD1b/TTJ"+post2[k]),-1)
        hQCD1b.Add(fTTT.Get("QCD1b/TTT"+post2[k]),-1)
        hQCD1b.Add(fTTL.Get("QCD1b/TTL"+post2[k]),-1)
        hQCD1b.Add(fW.Get("QCD1b/W"+postfix1[k]),-1)
        hQCD1b.Add(fVV.Get("QCD1b/VV"+post2[k]),-1)
        hQCD1b.Add(fST.Get("QCD1b/ST"+post2[k]),-1)
        hQCD1b.Add(fDYS.Get("QCD1b/ZTT"+post2[k]),-1)
        hQCD1b.SetName("QCD"+postfix1[k])
        hQCD1b.Scale(factor)
        for i in range(0,hQCD1b.GetSize()-2):
            if hQCD1b.GetBinContent(i)<0:
                hQCD1b.SetBinError(i,max(0,hQCD1b.GetBinError(i)+hQCD1b.GetBinError(i)))
                hQCD1b.SetBinContent(i,0)

        hQCD1b_lt80=fData.Get("QCD1b_lt80/data_obs")
        hQCD1b_lt80.Add(fDYJ.Get("QCD1b_lt80/ZJ"),-1)
        hQCD1b_lt80.Add(fDYL.Get("QCD1b_lt80/ZL"),-1)
        hQCD1b_lt80.Add(fTTJ.Get("QCD1b_lt80/TTJ"+post2[k]),-1)
        hQCD1b_lt80.Add(fTTT.Get("QCD1b_lt80/TTT"+post2[k]),-1)
        hQCD1b_lt80.Add(fTTL.Get("QCD1b_lt80/TTL"+post2[k]),-1)
        hQCD1b_lt80.Add(fW.Get("QCD1b_lt80/W"+postfix1[k]),-1)
        hQCD1b_lt80.Add(fVV.Get("QCD1b_lt80/VV"+post2[k]),-1)
        hQCD1b_lt80.Add(fST.Get("QCD1b_lt80/ST"+post2[k]),-1)
        hQCD1b_lt80.Add(fDYS.Get("QCD1b_lt80/ZTT"+post2[k]),-1)
        hQCD1b_lt80.SetName("QCD"+postfix1[k])
        hQCD1b_lt80.Scale(factor)
        for i in range(0,hQCD1b_lt80.GetSize()-2):
            if hQCD1b_lt80.GetBinContent(i)<0:
                hQCD1b_lt80.SetBinError(i,max(0,hQCD1b_lt80.GetBinError(i)+hQCD1b_lt80.GetBinError(i)))
                hQCD1b_lt80.SetBinContent(i,0)

        hQCD1b_80to100=fData.Get("QCD1b_80to100/data_obs")
        hQCD1b_80to100.Add(fDYJ.Get("QCD1b_80to100/ZJ"),-1)
        hQCD1b_80to100.Add(fDYL.Get("QCD1b_80to100/ZL"),-1)
        hQCD1b_80to100.Add(fTTJ.Get("QCD1b_80to100/TTJ"+post2[k]),-1)
        hQCD1b_80to100.Add(fTTT.Get("QCD1b_80to100/TTT"+post2[k]),-1)
        hQCD1b_80to100.Add(fTTL.Get("QCD1b_80to100/TTL"+post2[k]),-1)
        hQCD1b_80to100.Add(fW.Get("QCD1b_80to100/W"+postfix1[k]),-1)
        hQCD1b_80to100.Add(fVV.Get("QCD1b_80to100/VV"+post2[k]),-1)
        hQCD1b_80to100.Add(fST.Get("QCD1b_80to100/ST"+post2[k]),-1)
        hQCD1b_80to100.Add(fDYS.Get("QCD1b_80to100/ZTT"+post2[k]),-1)
        hQCD1b_80to100.SetName("QCD"+postfix1[k])
        hQCD1b_80to100.Scale(factor)
        for i in range(0,hQCD1b_80to100.GetSize()-2):
            if hQCD1b_80to100.GetBinContent(i)<0:
                hQCD1b_80to100.SetBinError(i,max(0,hQCD1b_80to100.GetBinError(i)+hQCD1b_80to100.GetBinError(i)))
                hQCD1b_80to100.SetBinContent(i,0)

        hQCD1b_100to120=fData.Get("QCD1b_100to120/data_obs")
        hQCD1b_100to120.Add(fDYJ.Get("QCD1b_100to120/ZJ"),-1)
        hQCD1b_100to120.Add(fDYL.Get("QCD1b_100to120/ZL"),-1)
        hQCD1b_100to120.Add(fTTJ.Get("QCD1b_100to120/TTJ"+post2[k]),-1)
        hQCD1b_100to120.Add(fTTT.Get("QCD1b_100to120/TTT"+post2[k]),-1)
        hQCD1b_100to120.Add(fTTL.Get("QCD1b_100to120/TTL"+post2[k]),-1)
        hQCD1b_100to120.Add(fW.Get("QCD1b_100to120/W"+postfix1[k]),-1)
        hQCD1b_100to120.Add(fVV.Get("QCD1b_100to120/VV"+post2[k]),-1)
        hQCD1b_100to120.Add(fST.Get("QCD1b_100to120/ST"+post2[k]),-1)
        hQCD1b_100to120.Add(fDYS.Get("QCD1b_100to120/ZTT"+post2[k]),-1)
        hQCD1b_100to120.SetName("QCD"+postfix1[k])
        hQCD1b_100to120.Scale(factor)
        for i in range(0,hQCD1b_100to120.GetSize()-2):
            if hQCD1b_100to120.GetBinContent(i)<0:
                hQCD1b_100to120.SetBinError(i,max(0,hQCD1b_100to120.GetBinError(i)+hQCD1b_100to120.GetBinError(i)))
                hQCD1b_100to120.SetBinContent(i,0)

        fout.cd()
        dir_incl_1b.cd()
        hQCD_incl_1b.Scale(hSS_incl_1b.Integral()/(hQCD_incl_1b.Integral()+0.0000001))
        hQCD_incl_1b.Write()

        dir_1b.cd()
        hQCD1b.Scale(hSS_1b.Integral()/(hQCD1b.Integral()+0.0000001))
        hQCD1b.Write()

        dir_1b_lt80.cd()
        hQCD1b_lt80.Scale(hSS_incl_1b_lt80.Integral()/(hQCD1b_lt80.Integral()+0.0000001))
        hQCD1b_lt80.Write()

        dir_1b_80to100.cd()
        hQCD1b_80to100.Scale(hSS_incl_1b_80to100.Integral()/(hQCD1b_80to100.Integral()+0.0000001))
        hQCD1b_80to100.Write()

        dir_1b_100to120.cd()
        hQCD1b_100to120.Scale(hSS_incl_1b_100to120.Integral()/(hQCD1b_100to120.Integral()+0.0000001))
        hQCD1b_100to120.Write()

        dir_incl_2b.cd()
        hQCD_incl_2b.Scale(hSS_incl_2b.Integral()/(hQCD_incl_2b.Integral()+0.0000001))
        hQCD_incl_2b.Write()

        dir_2b.cd()
        hQCD2b.Scale(hSS_2b.Integral()/(hQCD2b.Integral()+0.000001))
        hQCD2b.Write()
