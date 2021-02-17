import ROOT

file=ROOT.TFile("final_em_2018.root","r")

dir=["m_tt_1","m_tt_2","m_tt_3","m_tt_4","m_tt_5"]

for i in range (0,5):
    qcd = file.Get(dir[i]).Get("QCD")
    qcd_default = file.Get(dir[i]).Get("QCD_default")

    gof2 = ROOT.Math.GoFTest.GoFTest(1,2,1,2)
    ks = gof2.KolmogorovSmirnov2SamplesTest()
    print(ks)
