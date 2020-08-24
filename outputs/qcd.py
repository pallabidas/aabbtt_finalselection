import ROOT

file=ROOT.TFile("final_em.root","update")

dir=["m_em","m_emb","m_embb","e_pt","mu_pt","b1_pt","b2_pt","m_em_nobjet","e_pt_nobjet","mu_pt_nobjet","m_em_VBFenriched","m_emb_VBFenriched","m_embb_VBFenriched","e_pt_VBFenriched","mu_pt_VBFenriched"]

for i in range (0,15):
    Data_SS=file.Get(dir[i]).Get("data_obs_SS")
    HTT_SS=file.Get(dir[i]).Get("HTT_SS")
    W_SS=file.Get(dir[i]).Get("W_SS")
    TT_SS=file.Get(dir[i]).Get("TT_SS")
    VV_SS=file.Get(dir[i]).Get("VV_SS")
    Z_SS=file.Get(dir[i]).Get("Z_SS")
    ST_SS=file.Get(dir[i]).Get("ST_SS")

    qcd=Data_SS
    qcd.Add(HTT_SS,-1)
    qcd.Add(W_SS,-1)
    qcd.Add(TT_SS,-1)
    qcd.Add(VV_SS,-1)
    qcd.Add(Z_SS,-1)
    qcd.Add(ST_SS,-1)

    file.cd(dir[i])
    qcd.SetName("QCD")
    qcd.Write()


