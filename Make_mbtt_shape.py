

if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown','allJES','allTES','fakeES'], help="Which TES?")

    nbhist=1

    options = parser.parse_args()
    postfix=""

    fnom=ROOT.TFile("files_nominal/ZTT.root","r")
    fup=ROOT.TFile("files_nominal/DYtt_mbttup.root","r")
    fdown=ROOT.TFile("files_nominal/DYtt_mbttdown.root","r")
    fout=ROOT.TFile("files_nominal/ZTT_mbtt.root","recreate")

    mydir1=fout.mkdir("mt_incl_1b")
    mydir2=fout.mkdir("mt_1b_lt80")
    mydir3=fout.mkdir("mt_1b_80to100")
    mydir4=fout.mkdir("mt_1b_100to120")

    hist2up=fup.Get("mt_1b_lt80").Get("ZTT_CMS_mbttShape_13TeVUp").Clone()
    hist2down=fdown.Get("mt_1b_lt80").Get("ZTT_CMS_mbttShape_13TeVDown").Clone()
    hist1up=fnom.Get("mt_incl_1b").Get("ZTT").Clone()
    hist1down=fnom.Get("mt_incl_1b").Get("ZTT").Clone()
    hist1up.SetName("ZTT_CMS_mbttShape_13TeVUp")
    hist1down.SetName("ZTT_CMS_mbttShape_13TeVDown")
    for i in range(1,5):
       hist1up.SetBinContent(i,fup.Get("mt_incl_1b").Get("ZTT_CMS_mbttShape_13TeVUp").GetBinContent(i))
       hist1up.SetBinError(i,fup.Get("mt_incl_1b").Get("ZTT_CMS_mbttShape_13TeVUp").GetBinError(i))
       hist1down.SetBinContent(i,fdown.Get("mt_incl_1b").Get("ZTT_CMS_mbttShape_13TeVDown").GetBinContent(i))
       hist1down.SetBinError(i,fdown.Get("mt_incl_1b").Get("ZTT_CMS_mbttShape_13TeVDown").GetBinError(i))
    hist3up=fup.Get("mt_1b_80to100").Get("ZTT_CMS_mbttShape_13TeVUp").Clone()
    hist3down=fdown.Get("mt_1b_80to100").Get("ZTT_CMS_mbttShape_13TeVDown").Clone()
    hist4up=fup.Get("mt_1b_100to120").Get("ZTT_CMS_mbttShape_13TeVUp").Clone()
    hist4down=fdown.Get("mt_1b_100to120").Get("ZTT_CMS_mbttShape_13TeVDown").Clone()

    fout.cd()
    mydir1.cd()
    hist1up.Write()
    hist1down.Write()

    mydir2.cd()
    hist2up.Write()
    hist2down.Write()

    mydir3.cd()
    hist3up.Write()
    hist3down.Write()

    mydir4.cd()
    hist4up.Write()
    hist4down.Write()

