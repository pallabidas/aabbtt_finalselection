import ROOT

file=ROOT.TFile("final_mt_2018.root","update")

#dir=["m_btt_1b","m_bbtt_2b","mt_tau1","mt_tau2","dz"]

dir=["m_tt_c1","m_tt_c2","m_tt_c3","m_tt_c4","m_tt_c5"]

for i in range (0,5):
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

    blinded=file.Get(dir[i]).Get("bbtt40_SS")
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


