import ROOT

file=ROOT.TFile("final_em_2016.root","update")

dir=["m_em_1","m_em_2","m_em_3","m_em_4","m_em","m_emb","m_embb","pt_e","pt_m","m_em_0b","pt_e_0b","pt_m_0b","m_em_1b","pt_e_1b","pt_m_1b","m_em_2b","pt_e_2b","pt_m_2b","m_em_vbf","pt_e_vbf","pt_m_vbf","m_em_vv","pt_e_vv","pt_m_vv"]

for i in range (0,24):
    Data_SS=file.Get(dir[i]).Get("data_obs_SS")
    HTT_SS=file.Get(dir[i]).Get("HTT_SS")
    HWW_SS=file.Get(dir[i]).Get("HWW_SS")
    Z_SS=file.Get(dir[i]).Get("Z_SS")
    W_SS=file.Get(dir[i]).Get("W_SS")
    TT_SS=file.Get(dir[i]).Get("TT_SS")
    VV_SS=file.Get(dir[i]).Get("VV_SS")
    ZTT_SS=file.Get(dir[i]).Get("ZTT_SS")
    ST_SS=file.Get(dir[i]).Get("ST_SS")
    ttHnonbb_SS=file.Get(dir[i]).Get("ttHnonbb_SS")

    qcd=Data_SS
    qcd.Add(HTT_SS,-1)
    qcd.Add(HWW_SS,-1)
    qcd.Add(Z_SS,-1)
    qcd.Add(W_SS,-1)
    qcd.Add(TT_SS,-1)
    qcd.Add(VV_SS,-1)
    qcd.Add(ZTT_SS,-1)
    qcd.Add(ST_SS,-1)
    qcd.Add(ttHnonbb_SS,-1)

    file.cd(dir[i])
    qcd.SetName("QCD")
    qcd.Write()



