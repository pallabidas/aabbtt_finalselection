import ROOT

file=ROOT.TFile("final_mt_2018.root","update")

dir=["p_1b","p_2b","p_1b_z","p_2b_z","m_tt_1","m_tt_2","m_tt_3","m_tt_4","m_tt_5","m_tt_6","m_tt_7","m_tt_CB_1","m_tt_CB_2","m_tt_CB_3","m_tt_CB_4","m_tt_CB_5"]

for i in range (0,16):
    Data_SS=file.Get(dir[i]).Get("data_obs_SS")
    HTT_SS=file.Get(dir[i]).Get("HTT_SS")
    HWW_SS=file.Get(dir[i]).Get("HWW_SS")
    Z_SS=file.Get(dir[i]).Get("Z_SS")
#    W_SS=file.Get(dir[i]).Get("W_SS")
    TT_SS=file.Get(dir[i]).Get("TT_SS")
    VV_SS=file.Get(dir[i]).Get("VV_SS")
    ZTT_SS=file.Get(dir[i]).Get("ZTT_SS")
    ST_SS=file.Get(dir[i]).Get("ST_SS")
    ttHnonbb_SS=file.Get(dir[i]).Get("ttHnonbb_SS")

    blinded=file.Get(dir[i]).Get("gghbbtt40_SS")
    blinded.Scale(0)

    qcd=Data_SS
    qcd.Add(HTT_SS,-1)
    qcd.Add(HWW_SS,-1)
    qcd.Add(Z_SS,-1)
#    qcd.Add(W_SS,-1)
    qcd.Add(TT_SS,-1)
    qcd.Add(VV_SS,-1)
    qcd.Add(ZTT_SS,-1)
    qcd.Add(ST_SS,-1)
    qcd.Add(ttHnonbb_SS,-1)
    
    
    file.cd(dir[i])
    qcd.SetName("QCD")
    qcd.Write()
    
    blinded.SetName("blinded")
    blinded.Write()




