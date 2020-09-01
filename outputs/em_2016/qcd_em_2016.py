import ROOT

file=ROOT.TFile("final_em_2016.root","update")

dir=["m_em_nobjet","e_pt_nobjet","mu_pt_nobjet","m_em_1bjet","m_emb_1bjet","e_pt_1bjet","mu_pt_1bjet","b1_pt_1bjet","m_em_2bjet","m_emb_2bjet","m_embb_2bjet","e_pt_2bjet","mu_pt_2bjet","b1_pt_2bjet","b2_pt_2bjet","m_em_nobjet_VBFenriched","e_pt_nobjet_VBFenriched","mu_pt_nobjet_VBFenriched","m_em_atleast_1bjet_VBFenriched","m_emb_atleast_1bjet_VBFenriched","m_embb_atleast_1bjet_VBFenriched","e_pt_atleast_1bjet_VBFenriched","mu_pt_atleast_1bjet_VBFenriched","b1_pt_atleast_1bjet_VBFenriched","b2_pt_atleast_1bjet_VBFenriched","m_em_VV","e_pt_VV","mu_pt_VV","m_em_atleast_1bjet_QCD","m_emb_atleast_1bjet_QCD","m_embb_atleast_1bjet_QCD","e_pt_atleast_1bjet_QCD","mu_pt_atleast_1bjet_QCD","b1_pt_atleast_1bjet_QCD","b2_pt_atleast_1bjet_QCD"]

for i in range (0,35):
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



