import ROOT

file=ROOT.TFile("final_et_2016.root","update")

dir=["m_et_1","m_et_2","m_et_3","m_et_4","m_et","m_etb","m_etbb","pt_e","pt_t"]

for i in range (0,9):
    Data_qcd=file.Get(dir[i]).Get("data_obs_qcd")
    HTT_qcd=file.Get(dir[i]).Get("HTT_qcd")
    HWW_qcd=file.Get(dir[i]).Get("HWW_qcd")
    W_qcd=file.Get(dir[i]).Get("W_qcd")
    TT_qcd=file.Get(dir[i]).Get("TT_qcd")
    VV_qcd=file.Get(dir[i]).Get("VV_qcd")
    Z_qcd=file.Get(dir[i]).Get("Z_qcd")
    ST_qcd=file.Get(dir[i]).Get("ST_qcd")
    ttHnonbb_qcd=file.Get(dir[i]).Get("ttHnonbb_qcd")

    qcd=Data_qcd
    qcd.Add(HTT_qcd,-1)
    qcd.Add(HWW_qcd,-1)
    qcd.Add(W_qcd,-1)
    qcd.Add(TT_qcd,-1)
    qcd.Add(VV_qcd,-1)
    qcd.Add(Z_qcd,-1)
    qcd.Add(ST_qcd,-1)
    qcd.Add(ttHnonbb_qcd,-1)

    file.cd(dir[i])
    qcd.SetName("QCD")
    qcd.Write()

