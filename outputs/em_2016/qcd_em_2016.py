import ROOT

file=ROOT.TFile("final_em_2016.root","update")

dir=["m_em_1","m_em_2","m_em_3","m_em_4","m_em","m_emb","e_pt_1","e_pt_2","e_pt_3","e_pt_4","mu_pt_1","mu_pt_2","mu_pt_3","mu_pt_4","e_pt","mu_pt"]

for i in range (0,16):
    Data_SS=file.Get(dir[i]).Get("data_obs_SS")
    HTT_SS=file.Get(dir[i]).Get("HTT_SS")
    HWW_SS=file.Get(dir[i]).Get("HWW_SS")
    W_SS=file.Get(dir[i]).Get("W_SS")
    TT_SS=file.Get(dir[i]).Get("TT_SS")
    VV_SS=file.Get(dir[i]).Get("VV_SS")
    Z_SS=file.Get(dir[i]).Get("Z_SS")
    ST_SS=file.Get(dir[i]).Get("ST_SS")
    ttHnonbb_SS=file.Get(dir[i]).Get("ttHnonbb_SS")

    qcd=Data_SS
    qcd.Add(HTT_SS,-1)
    qcd.Add(HWW_SS,-1)
    qcd.Add(W_SS,-1)
    qcd.Add(TT_SS,-1)
    qcd.Add(VV_SS,-1)
    qcd.Add(Z_SS,-1)
    qcd.Add(ST_SS,-1)
    qcd.Add(ttHnonbb_SS,-1)

    file.cd(dir[i])
    qcd.SetName("QCD")
    qcd.Write()



