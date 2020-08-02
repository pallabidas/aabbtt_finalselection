if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown','allJES','allTES','fakeES'], help="Which TES?")

    nbhist=1

    options = parser.parse_args()
    postfix=""

    fDY=ROOT.TFile("files_"+options.scale+"/ZTT.root","r")
    fDYL=ROOT.TFile("files_"+options.scale+"/ZL.root","r")
    fW=ROOT.TFile("files_"+options.scale+"/W.root","r")
    fTT=ROOT.TFile("files_"+options.scale+"/TTT.root","r")
    fTTL=ROOT.TFile("files_"+options.scale+"/TTL.root","r")
    fVV=ROOT.TFile("files_"+options.scale+"/VV.root","r")
    fST=ROOT.TFile("files_"+options.scale+"/ST.root","r")
    fData=ROOT.TFile("files_nominal/Data.root","r")
    fout=ROOT.TFile("files_"+options.scale+"/Fake.root","recreate")


    dir0jet=fout.mkdir("mt_incl_2b")
    dir1jet=fout.mkdir("mt_2b")
    dir2jet=fout.mkdir("mt_incl_1b")
    dir3jet=fout.mkdir("mt_1b")
    dir4jet=fout.mkdir("mt_1b_lt80")
    dir5jet=fout.mkdir("mt_1b_80to100")
    dir6jet=fout.mkdir("mt_1b_100to120")

    postfixData=""
    mypostfix=[""]
    if options.scale=="allTES":
        nbhist=18
        mypostfix=["_CMS_scale_t_13TeVDown","_CMS_scale_t_13TeVUp","_CMS_scale_t_1prong_13TeVDown","_CMS_scale_t_1prong_13TeVUp","_CMS_scale_t_1prong1pizero_13TeVDown","_CMS_scale_t_1prong1pizero_13TeVUp","_CMS_scale_t_3prong_13TeVDown","_CMS_scale_t_3prong_13TeVUp","_CMS_scale_m_13TeVUp","_CMS_scale_m_13TeVDown","_CMS_btag_heavy_13TeVUp","_CMS_btag_heavy_13TeVDown","_CMS_btag_light_13TeVUp","_CMS_btag_light_13TeVDown","_CMS_scale_met_unclustered_13TeVDown","_CMS_scale_met_unclustered_13TeVUp","_CMS_scale_j_13TeVDown","_CMS_scale_j_13TeVUp"]

    if options.scale=="fakeES":
        nbhist=12
        fData=ROOT.TFile("files_fakeES/Data.root","r")
        mypostfix=["_CMS_fakeRate10_var1_13TeVUp","_CMS_fakeRate10_var1_13TeVDown","_CMS_fakeRate10_var2_13TeVUp","_CMS_fakeRate10_var2_13TeVDown","_CMS_fakeRate1_var1_13TeVUp","_CMS_fakeRate1_var1_13TeVDown","_CMS_fakeRate1_var2_13TeVUp","_CMS_fakeRate1_var2_13TeVDown","_CMS_fakeRate0_var1_13TeVUp","_CMS_fakeRate0_var1_13TeVDown","_CMS_fakeRate0_var2_13TeVUp","_CMS_fakeRate0_var2_13TeVDown"]


    for k in range(0,nbhist):
	if nbhist!=1:
	    postfix=mypostfix[k]
        if options.scale=="fakeES":
           postfixData=postfix
        h_0jet=fData.Get("AIincl_2b/data_obs"+postfixData)
        h_0jet.Add(fDY.Get("AIincl_2b/ZTT"+postfix),-1)
        h_0jet.Add(fDYL.Get("AIincl_2b/ZL"+postfix),-1)
        h_0jet.Add(fW.Get("AIincl_2b/W"+postfix),-1)
        h_0jet.Add(fTT.Get("AIincl_2b/TTT"+postfix),-1)
        h_0jet.Add(fTTL.Get("AIincl_2b/TTL"+postfix),-1)
        h_0jet.Add(fVV.Get("AIincl_2b/VV"+postfix),-1)
        h_0jet.Add(fST.Get("AIincl_2b/ST"+postfix),-1)
        print "inclusive 2b, ",fData.Get("AIincl_2b/data_obs"+postfixData).Integral(),(fDY.Get("AIincl_2b/ZTT"+postfix)).Integral()+fDYL.Get("AIincl_2b/ZL"+postfix).Integral()+fW.Get("AIincl_2b/W"+postfix).Integral()+fTT.Get("AIincl_2b/TTT"+postfix).Integral()+fVV.Get("AIincl_2b/VV"+postfix).Integral()+fST.Get("AIincl_2b/ST"+postfix).Integral()
        for i in range(0,h_0jet.GetSize()-2):
            if h_0jet.GetBinContent(i)<=0:
                h_0jet.SetBinError(i,max(0,h_0jet.GetBinError(i)+h_0jet.GetBinError(i)))
                h_0jet.SetBinContent(i,0.00001)

        h_1jet=fData.Get("AI2b/data_obs"+postfixData)
        h_1jet.Add(fDY.Get("AI2b/ZTT"+postfix),-1)
        h_1jet.Add(fDYL.Get("AI2b/ZL"+postfix),-1)
        h_1jet.Add(fW.Get("AI2b/W"+postfix),-1)
        h_1jet.Add(fTT.Get("AI2b/TTT"+postfix),-1)
        h_1jet.Add(fTTL.Get("AI2b/TTL"+postfix),-1)
        h_1jet.Add(fVV.Get("AI2b/VV"+postfix),-1)
        h_1jet.Add(fST.Get("AI2b/ST"+postfix),-1)
        print "2b, ",fData.Get("AI2b/data_obs"+postfixData).Integral(),(fDY.Get("AI2b/ZTT"+postfix)).Integral()+fDYL.Get("AI2b/ZL"+postfix).Integral()+fW.Get("AI2b/W"+postfix).Integral()+fTT.Get("AI2b/TTT"+postfix).Integral()+fVV.Get("AI2b/VV"+postfix).Integral()+fST.Get("AI2b/ST"+postfix).Integral()
        for i in range(0,h_1jet.GetSize()-2):
            if h_1jet.GetBinContent(i)<=0:
                h_1jet.SetBinError(i,max(0,h_1jet.GetBinError(i)+h_1jet.GetBinError(i)))
                h_1jet.SetBinContent(i,0.00001)

        h_2jet=fData.Get("AIincl_1b/data_obs"+postfixData)
        h_2jet.Add(fDY.Get("AIincl_1b/ZTT"+postfix),-1)
        h_2jet.Add(fDYL.Get("AIincl_1b/ZL"+postfix),-1)
        h_2jet.Add(fW.Get("AIincl_1b/W"+postfix),-1)
        h_2jet.Add(fTT.Get("AIincl_1b/TTT"+postfix),-1)
        h_2jet.Add(fTTL.Get("AIincl_1b/TTL"+postfix),-1)
        h_2jet.Add(fVV.Get("AIincl_1b/VV"+postfix),-1)
        h_2jet.Add(fST.Get("AIincl_1b/ST"+postfix),-1)
        print "inclusive 1b, ",fData.Get("AI1b/data_obs"+postfixData).Integral(),(fDY.Get("AI1b/ZTT"+postfix)).Integral()+fDYL.Get("AI1b/ZL"+postfix).Integral()+fW.Get("AI1b/W"+postfix).Integral()+fTT.Get("AI1b/TTT"+postfix).Integral()+fVV.Get("AI1b/VV"+postfix).Integral()+fST.Get("AI1b/ST"+postfix).Integral()
        for i in range(0,h_2jet.GetSize()-2):
            if h_2jet.GetBinContent(i)<=0:
                h_2jet.SetBinError(i,max(0,h_2jet.GetBinError(i)+h_2jet.GetBinError(i)))
                h_2jet.SetBinContent(i,0.00001)

        h_3jet=fData.Get("AI1b/data_obs"+postfixData)
        h_3jet.Add(fDY.Get("AI1b/ZTT"+postfix),-1)
        h_3jet.Add(fDYL.Get("AI1b/ZL"+postfix),-1)
        h_3jet.Add(fW.Get("AI1b/W"+postfix),-1)
        h_3jet.Add(fTT.Get("AI1b/TTT"+postfix),-1)
        h_3jet.Add(fTTL.Get("AI1b/TTL"+postfix),-1)
        h_3jet.Add(fVV.Get("AI1b/VV"+postfix),-1)
        h_3jet.Add(fST.Get("AI1b/ST"+postfix),-1)
        print "1b, ",fData.Get("AI1b/data_obs"+postfixData).Integral(),(fDY.Get("AI1b/ZTT"+postfix)).Integral()+fDYL.Get("AI1b/ZL"+postfix).Integral()+fW.Get("AI1b/W"+postfix).Integral()+fTT.Get("AI1b/TTT"+postfix).Integral()+fVV.Get("AI1b/VV"+postfix).Integral()+fST.Get("AI1b/ST"+postfix).Integral()
        for i in range(0,h_3jet.GetSize()-2):
            if h_3jet.GetBinContent(i)<=0:
                h_3jet.SetBinError(i,max(0,h_3jet.GetBinError(i)+h_3jet.GetBinError(i)))
                h_3jet.SetBinContent(i,0.00001)

        h_4jet=fData.Get("AI1b_lt80/data_obs"+postfixData)
        h_4jet.Add(fDY.Get("AI1b_lt80/ZTT"+postfix),-1)
        h_4jet.Add(fDYL.Get("AI1b_lt80/ZL"+postfix),-1)
        h_4jet.Add(fW.Get("AI1b_lt80/W"+postfix),-1)
        h_4jet.Add(fTT.Get("AI1b_lt80/TTT"+postfix),-1)
        h_4jet.Add(fTTL.Get("AI1b_lt80/TTL"+postfix),-1)
        h_4jet.Add(fVV.Get("AI1b_lt80/VV"+postfix),-1)
        h_4jet.Add(fST.Get("AI1b_lt80/ST"+postfix),-1)
        print "1b lt80, ",fData.Get("AI1b_lt80/data_obs"+postfixData).Integral(),(fDY.Get("AI1b_lt80/ZTT"+postfix)).Integral()+fDYL.Get("AI1b_lt80/ZL"+postfix).Integral()+fW.Get("AI1b_lt80/W"+postfix).Integral()+fTT.Get("AI1b_lt80/TTT"+postfix).Integral()+fVV.Get("AI1b_lt80/VV"+postfix).Integral()+fST.Get("AI1b_lt80/ST"+postfix).Integral()
        for i in range(0,h_4jet.GetSize()-2):
            if h_4jet.GetBinContent(i)<=0:
                h_4jet.SetBinError(i,max(0,h_4jet.GetBinError(i)+h_4jet.GetBinError(i)))
                h_4jet.SetBinContent(i,0.00001)

        h_5jet=fData.Get("AI1b_80to100/data_obs"+postfixData)
        h_5jet.Add(fDY.Get("AI1b_80to100/ZTT"+postfix),-1)
        h_5jet.Add(fDYL.Get("AI1b_80to100/ZL"+postfix),-1)
        h_5jet.Add(fW.Get("AI1b_80to100/W"+postfix),-1)
        h_5jet.Add(fTT.Get("AI1b_80to100/TTT"+postfix),-1)
        h_5jet.Add(fTTL.Get("AI1b_80to100/TTL"+postfix),-1)
        h_5jet.Add(fVV.Get("AI1b_80to100/VV"+postfix),-1)
        h_5jet.Add(fST.Get("AI1b_80to100/ST"+postfix),-1)
        print "1b, 80to100, ",fData.Get("AI1b_80to100/data_obs"+postfixData).Integral(),(fDY.Get("AI1b_80to100/ZTT"+postfix)).Integral()+fDYL.Get("AI1b_80to100/ZL"+postfix).Integral()+fW.Get("AI1b_80to100/W"+postfix).Integral()+fTT.Get("AI1b_80to100/TTT"+postfix).Integral()+fVV.Get("AI1b_80to100/VV"+postfix).Integral()+fST.Get("AI1b_80to100/ST"+postfix).Integral()
        for i in range(0,h_5jet.GetSize()-2):
            if h_5jet.GetBinContent(i)<=0:
                h_5jet.SetBinError(i,max(0,h_5jet.GetBinError(i)+h_5jet.GetBinError(i)))
                h_5jet.SetBinContent(i,0.00001)

        h_6jet=fData.Get("AI1b_100to120/data_obs"+postfixData)
        h_6jet.Add(fDY.Get("AI1b_100to120/ZTT"+postfix),-1)
        h_6jet.Add(fDYL.Get("AI1b_100to120/ZL"+postfix),-1)
        h_6jet.Add(fW.Get("AI1b_100to120/W"+postfix),-1)
        h_6jet.Add(fTT.Get("AI1b_100to120/TTT"+postfix),-1)
        h_6jet.Add(fTTL.Get("AI1b_100to120/TTL"+postfix),-1)
        h_6jet.Add(fVV.Get("AI1b_100to120/VV"+postfix),-1)
        h_6jet.Add(fST.Get("AI1b_100to120/ST"+postfix),-1)
        print "1b, 100to120, ",fData.Get("AI1b_100to120/data_obs"+postfixData).Integral(),(fDY.Get("AI1b_100to120/ZTT"+postfix)).Integral()+fDYL.Get("AI1b_100to120/ZL"+postfix).Integral()+fW.Get("AI1b_100to120/W"+postfix).Integral()+fTT.Get("AI1b_100to120/TTT"+postfix).Integral()+fVV.Get("AI1b_100to120/VV"+postfix).Integral()+fST.Get("AI1b_100to120/ST"+postfix).Integral()
        for i in range(0,h_6jet.GetSize()-2):
            if h_6jet.GetBinContent(i)<=0:
                h_6jet.SetBinError(i,max(0,h_6jet.GetBinError(i)+h_6jet.GetBinError(i)))
                h_6jet.SetBinContent(i,0.00001)

        fout.cd()
        dir0jet.cd()
        h_0jet.SetName("jetFakes"+postfix)
        h_0jet.Write()

        dir1jet.cd()
        h_1jet.SetName("jetFakes"+postfix)
        h_1jet.Write()

        dir2jet.cd()
        h_2jet.SetName("jetFakes"+postfix)
        h_2jet.Write()

        dir3jet.cd()
        h_3jet.SetName("jetFakes"+postfix)
        h_3jet.Write()

        dir4jet.cd()
        h_4jet.SetName("jetFakes"+postfix)
        h_4jet.Write()

        dir5jet.cd()
        h_5jet.SetName("jetFakes"+postfix)
        h_5jet.Write()

        dir6jet.cd()
        h_6jet.SetName("jetFakes"+postfix)
        h_6jet.Write()

