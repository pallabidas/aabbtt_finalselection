if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal','allJES','qcdup','qcddown','wup','wdown','up', 'down','JESup','JESdown','allTES'], help="Which TES?")
    parser.add_argument('--anti', default="iso", choices=['iso', 'anti'], help="Which TES?")
    options = parser.parse_args()

    nbhist=1
    if options.scale=="allJES":
      nbhist=56
    if options.scale=="allTES":
      nbhist=12

    factorwall=1.0
    factorwlow=1.0

    factorwall_u=1.10
    factorwlow_u=1.10

    factorwall_d=0.90
    factorwlow_d=0.90

    if (options.scale=="wup"):
        factorwall=factorwall_u
        factorwlow=factorwlow_u
    if (options.scale=="wdown"):
        factorwall=factorwall_d
        factorwlow=factorwlow_d

    factorall=1.07
    factorlow=1.06

    factorall_u=1.11
    factorlow_u=1.12

    factorall_d=1.03
    factorlow_d=1.00

    if (options.scale=="qcdup"):
        factorall=factorall_u
        factorlow=factorlow_u
    if (options.scale=="qcddown"):
        factorall=factorall_d
        factorlow=factorlow_d

    postfix=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfix0=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfix1=["_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp","_CMS_scale_j_AbsoluteFlavMap_13TeVDown","_CMS_scale_j_AbsoluteFlavMap_13TeVUp","_CMS_scale_j_AbsoluteMPFBias_13TeVDown","_CMS_scale_j_AbsoluteMPFBias_13TeVUp","_CMS_scale_j_AbsoluteScale_13TeVDown","_CMS_scale_j_AbsoluteScale_13TeVUp","_CMS_scale_j_AbsoluteStat_13TeVDown","_CMS_scale_j_AbsoluteStat_13TeVUp","_CMS_scale_j_FlavorQCD_13TeVDown","_CMS_scale_j_FlavorQCD_13TeVUp","_CMS_scale_j_Fragmentation_13TeVDown","_CMS_scale_j_Fragmentation_13TeVUp","_CMS_scale_j_PileUpDataMC_13TeVDown","_CMS_scale_j_PileUpDataMC_13TeVUp","_CMS_scale_j_PileUpPtBB_13TeVDown","_CMS_scale_j_PileUpPtBB_13TeVUp","_CMS_scale_j_PileUpPtEC1_13TeVDown","_CMS_scale_j_PileUpPtEC1_13TeVUp","_CMS_scale_j_PileUpPtEC2_13TeVDown","_CMS_scale_j_PileUpPtEC2_13TeVUp","_CMS_scale_j_PileUpPtHF_13TeVDown","_CMS_scale_j_PileUpPtHF_13TeVUp","_CMS_scale_j_PileUpPtRef_13TeVDown","_CMS_scale_j_PileUpPtRef_13TeVUp","_CMS_scale_j_RelativeBal_13TeVDown","_CMS_scale_j_RelativeBal_13TeVUp","_CMS_scale_j_RelativeFSR_13TeVDown","_CMS_scale_j_RelativeFSR_13TeVUp","_CMS_scale_j_RelativeJEREC1_13TeVDown","_CMS_scale_j_RelativeJEREC1_13TeVUp","_CMS_scale_j_RelativeJEREC2_13TeVDown","_CMS_scale_j_RelativeJEREC2_13TeVUp","_CMS_scale_j_RelativeJERHF_13TeVDown","_CMS_scale_j_RelativeJERHF_13TeVUp","_CMS_scale_j_RelativePtBB_13TeVDown","_CMS_scale_j_RelativePtBB_13TeVUp","_CMS_scale_j_RelativePtEC1_13TeVDown","_CMS_scale_j_RelativePtEC1_13TeVUp","_CMS_scale_j_RelativePtEC2_13TeVDown","_CMS_scale_j_RelativePtEC2_13TeVUp","_CMS_scale_j_RelativePtHF_13TeVDown","_CMS_scale_j_RelativePtHF_13TeVUp","_CMS_scale_j_RelativeStatEC_13TeVDown","_CMS_scale_j_RelativeStatEC_13TeVUp","_CMS_scale_j_RelativeStatFSR_13TeVDown","_CMS_scale_j_RelativeStatFSR_13TeVUp","_CMS_scale_j_RelativeStatHF_13TeVDown","_CMS_scale_j_RelativeStatHF_13TeVUp","_CMS_scale_j_SinglePionECAL_13TeVDown","_CMS_scale_j_SinglePionECAL_13TeVUp","_CMS_scale_j_SinglePionHCAL_13TeVDown","_CMS_scale_j_SinglePionHCAL_13TeVUp","_CMS_scale_j_TimePtEta_13TeVDown","_CMS_scale_j_TimePtEta_13TeVUp"]
    postfixTES=["_CMS_scale_t_13TeVDown","_CMS_scale_t_13TeVUp","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_scale_jet_13TeVDown","_CMS_scale_jet_13TeVUp"]
    if (options.scale!="allJES"):
        postfix[0]=""
        postfix0[0]=""
        postfix1[0]=""
    if (options.scale=="up"):
        postfix[0]="_CMS_scale_t_mt_13TeVUp"
        postfix0[0]="_CMS_scale_t_mt_13TeVUp"
        postfix1[0]="_CMS_scale_t_mt_13TeVUp"
    if (options.scale=="down"):
        postfix[0]="_CMS_scale_t_mt_13TeVDown"
        postfix0[0]="_CMS_scale_t_mt_13TeVDown"
        postfix1[0]="_CMS_scale_t_mt_13TeVDown"
    if (options.scale=="JESup"):
        postfix[0]="_CMS_scale_j_13TeVUp"
        postfix0[0]="_CMS_scale_j_13TeVUp"
        postfix1[0]="_CMS_scale_j_13TeVUp"
    if (options.scale=="JESdown"):
        postfix[0]="_CMS_scale_j_13TeVDown"
        postfix0[0]="_CMS_scale_j_13TeVDown"
        postfix1[0]="_CMS_scale_j_13TeVDown"
    if (options.scale=="qcdup"):
        postfix0[0]="_QCDSFUncert_mt_all_13TeVUp"
        postfix1[0]="_QCDSFUncert_mt_low_13TeVUp"
    if (options.scale=="qcddown"):
        postfix0[0]="_QCDSFUncert_mt_all_13TeVDown"
        postfix1[0]="_QCDSFUncert_mt_low_13TeVDown"
    if (options.scale=="wup"):
        postfix0[0]="_WSFUncert_mt_all_13TeVUp"
        postfix1[0]="_WSFUncert_mt_low_13TeVUp"
    if (options.scale=="wdown"):
        postfix0[0]="_WSFUncert_mt_all_13TeVDown"
        postfix1[0]="_WSFUncert_mt_low_13TeVDown"

    post2=postfix
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

    if options.scale=="allTES":
      for j in range(0,nbhist):
	 post2[j]=postfixTES[j]
         postfix0[j]=postfixTES[j]
         postfix1[j]=postfixTES[j]

    fDYS=ROOT.TFile("files_nominal/ZTT.root","r")
    fDYJ=ROOT.TFile("files_nominal/ZJ.root","r")
    fDYL=ROOT.TFile("files_nominal/ZL.root","r")
    fW=ROOT.TFile("files_nominal/Wunscaled.root","r")
    fTTJ=ROOT.TFile("files_nominal/TTJ.root","r")
    fTTT=ROOT.TFile("files_nominal/TTT.root","r")
    fVV=ROOT.TFile("files_nominal/VV.root","r")
    fData=ROOT.TFile("files_nominal/Data.root","r")
    #fout=ROOT.TFile("files_"+options.scale+"/W.root","recreate")

    mydir=options.scale
    if (options.scale=="allJES"):
         mydir="JESup"

    if (options.scale=="wdown"):
       fout=ROOT.TFile("files_nominal/W_wdown.root","recreate")
    elif (options.scale=="wup"):
       fout=ROOT.TFile("files_nominal/W_wup.root","recreate")
    elif (options.scale=="qcddown"):
       fout=ROOT.TFile("files_nominal/W_qcddown.root","recreate")
    elif (options.scale=="qcdup"):
       fout=ROOT.TFile("files_nominal/W_qcdup.root","recreate")
    elif (options.scale=="up" or options.scale=="down" or options.scale=="JESdown" or options.scale=="JESup" or options.scale=="nominal" or options.scale=="allJES" or options.scale=="allTES"):
       fDYS=ROOT.TFile("files_"+mydir+"/ZTT.root","r")
       fDYJ=ROOT.TFile("files_"+mydir+"/ZJ.root","r")
       fDYL=ROOT.TFile("files_"+mydir+"/ZL.root","r")
       fW=ROOT.TFile("files_"+mydir+"/Wunscaled.root","r")
       fTTT=ROOT.TFile("files_"+mydir+"/TTT.root","r")
       fTTJ=ROOT.TFile("files_"+mydir+"/TTJ.root","r")
       fVV=ROOT.TFile("files_"+mydir+"/VV.root","r")
       fData=ROOT.TFile("files_nominal/Data.root","r")
       fout=ROOT.TFile("files_"+mydir+"/W.root","recreate")

    fout.cd()
    dir0OS=fout.mkdir("mt_all")
    dir1OS=fout.mkdir("mt_low")
    dir0SS=fout.mkdir("SSall")
    dir1SS=fout.mkdir("SSlow")
    dir0QCD=fout.mkdir("QCDall")
    dir1QCD=fout.mkdir("QCDlow")

    nbhist=1
    if options.scale=="allJES":
      nbhist=56
    if options.scale=="allTES":
      nbhist=12
    for k in range(0,nbhist):
        print fDYS.Get("n70"+post2[k]).GetBinContent(4)
        QCDpassSS0=(fData.Get("n70SS").GetBinContent(2)-fDYJ.Get("n70SS"+post2[k]).GetBinContent(2)-fDYL.Get("n70SS"+post2[k]).GetBinContent(2)-fDYS.Get("n70SS"+post2[k]).GetBinContent(2)-fTTJ.Get("n70SS"+post2[k]).GetBinContent(2)-fTTT.Get("n70SS"+post2[k]).GetBinContent(2)-fW.Get("n70SS"+post2[k]).GetBinContent(2)-fVV.Get("n70SS"+post2[k]).GetBinContent(2))
        SFpassOS0=((fData.Get("n70").GetBinContent(2)-fDYJ.Get("n70"+post2[k]).GetBinContent(2)-fDYL.Get("n70"+post2[k]).GetBinContent(2)-fDYS.Get("n70"+post2[k]).GetBinContent(2)-fTTJ.Get("n70"+post2[k]).GetBinContent(2)-fTTT.Get("n70"+post2[k]).GetBinContent(2)-fVV.Get("n70"+post2[k]).GetBinContent(2)-factorall*QCDpassSS0)/(0.000001+fW.Get("n70"+post2[k]).GetBinContent(2)))
        QCDpassSS1=(fData.Get("n70SS").GetBinContent(3)-fDYJ.Get("n70SS"+post2[k]).GetBinContent(3)-fDYL.Get("n70SS"+post2[k]).GetBinContent(3)-fDYS.Get("n70SS"+post2[k]).GetBinContent(3)-fTTJ.Get("n70SS"+post2[k]).GetBinContent(3)-fTTT.Get("n70SS"+post2[k]).GetBinContent(3)-fW.Get("n70SS"+post2[k]).GetBinContent(3)-fVV.Get("n70SS"+post2[k]).GetBinContent(3))
        SFpassOS1=((fData.Get("n70").GetBinContent(3)-fDYJ.Get("n70"+post2[k]).GetBinContent(3)-fDYL.Get("n70"+post2[k]).GetBinContent(3)-fDYS.Get("n70"+post2[k]).GetBinContent(3)-fTTJ.Get("n70"+post2[k]).GetBinContent(3)-fTTT.Get("n70"+post2[k]).GetBinContent(3)-fVV.Get("n70"+post2[k]).GetBinContent(3)-factorlow*QCDpassSS1)/(0.000001+fW.Get("n70"+post2[k]).GetBinContent(3)))

	SFpassOS0=1.0
        SFpassOS1=1.0
        hWall=fW.Get("mt_all/W"+post2[k])
        hWall.Scale(SFpassOS0*factorwall)
        hWlow=fW.Get("mt_low/W"+post2[k])
        hWlow.Scale(SFpassOS1*factorwlow)
        hWall_SS=fW.Get("SSall/W"+post2[k])
        hWall_SS.Scale(SFpassOS0*factorwall)
        hWlow_SS=fW.Get("SSlow/W"+post2[k])
        hWlow_SS.Scale(SFpassOS1*factorwlow)
        hWall_QCD=fW.Get("QCDall/W"+post2[k])
        hWall_QCD.Scale(SFpassOS0*factorwall)
        hWlow_QCD=fW.Get("QCDlow/W"+post2[k])
        hWlow_QCD.Scale(SFpassOS1*factorwlow)

        fout.cd()
        dir0OS.cd()
        hWall.SetName("W"+postfix0[k])
        hWall.Write()
        dir1OS.cd()
        hWlow.SetName("W"+postfix1[k])
        hWlow.Write()

        dir0SS.cd()
        hWall_SS.SetName("W"+postfix0[k])
        hWall_SS.Write()
        dir1SS.cd()
        hWlow_SS.SetName("W"+postfix1[k])
        hWlow_SS.Write()

        dir0QCD.cd()
        hWall_QCD.SetName("W"+postfix0[k])
        hWall_QCD.Write()
        dir1QCD.cd()
        hWlow_QCD.SetName("W"+postfix1[k])
        hWlow_QCD.Write()

