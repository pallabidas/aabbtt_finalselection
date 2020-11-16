import ROOT

file=ROOT.TFile("final_et_2018.root","update")

#dir=["m_btt_atleast1b","m_btt_1b","m_bbtt_2b","mt_tau1_atleast1b","mt_tau2_atleast1b","mt_tau1_1b","mt_tau2_1b","mt_tau1_2b","mt_tau2_2b","dz_atleast1b","dz_1b","dz_2b"]
dir=["m_tt_b1","m_tt_b2","m_tt_b3","m_tt_b4","m_tt_b5","m_tt_b6","m_tt_c1","m_tt_c2","m_tt_c3","m_tt_c4","m_tt_c5"]
#dir=["mt_tau1_b1","mt_tau2_b1","dz_b1","mt_tau1_b2","mt_tau2_b2","dz_b2","mt_tau1_b3","mt_tau2_b3","dz_b3","mt_tau1_b4","mt_tau2_b4","dz_b4","mt_tau1_b5","mt_tau2_b5","dz_b5","mt_tau1_b6","mt_tau2_b6","dz_b6"]
#dir=["m_tt_0b","pt_t1_0b","pt_t2_0b","m_tt_1b","m_btt_1b","pt_t1_1b","pt_t2_1b","m_tt_2b","m_btt_2b","m_bbtt_2b","pt_t1_2b","pt_t2_2b"]

for i in range (0,11):
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


