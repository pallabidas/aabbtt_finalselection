import ROOT

file=ROOT.TFile("final_em_2018.root","update")

dir=["p_1b","p_2b","p_1b_z","p_2b_z","m_tt_1","m_tt_2","m_tt_3","m_tt_4","m_tt_5","m_tt_6","m_tt_7","m_tt_CB_1","m_tt_CB_2","m_tt_CB_3","m_tt_CB_4","m_tt_CB_5"]

for i in range (0,16):
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
    
    Data_loose_SS=file.Get(dir[i]).Get("data_obs_loose_SS")
    HTT_loose_SS=file.Get(dir[i]).Get("HTT_loose_SS")
    HWW_loose_SS=file.Get(dir[i]).Get("HWW_loose_SS")
    Z_loose_SS=file.Get(dir[i]).Get("Z_loose_SS")
    W_loose_SS=file.Get(dir[i]).Get("W_loose_SS")
    TT_loose_SS=file.Get(dir[i]).Get("TT_loose_SS")
    VV_loose_SS=file.Get(dir[i]).Get("VV_loose_SS")
    ZTT_loose_SS=file.Get(dir[i]).Get("ZTT_loose_SS")
    ST_loose_SS=file.Get(dir[i]).Get("ST_loose_SS")
    ttHnonbb_loose_SS=file.Get(dir[i]).Get("ttHnonbb_loose_SS")

    blinded=file.Get(dir[i]).Get("gghbbtt40_SS")
    blinded.Scale(0)

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
    
    qcd_loose=Data_loose_SS
    qcd_loose.Add(HTT_loose_SS,-1)
    qcd_loose.Add(HWW_loose_SS,-1)
    qcd_loose.Add(Z_loose_SS,-1)
    qcd_loose.Add(W_loose_SS,-1)
    qcd_loose.Add(TT_loose_SS,-1)
    qcd_loose.Add(VV_loose_SS,-1)
    qcd_loose.Add(ZTT_loose_SS,-1)
    qcd_loose.Add(ST_loose_SS,-1)
    qcd_loose.Add(ttHnonbb_loose_SS,-1)
    
    scale=qcd.Integral()/qcd_loose.Integral()
    qcd_loose.Scale(scale)

    file.cd(dir[i])
    qcd_loose.SetName("QCD")
    qcd_loose.Write()

    blinded.SetName("blinded")
    blinded.Write()


