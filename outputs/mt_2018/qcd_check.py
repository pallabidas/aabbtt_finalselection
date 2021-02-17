import ROOT

file=ROOT.TFile("final_mt_2018.root","update")

dir=["pt_t1_1b","pt_t2_1b","m_btt_1b","m_bt1_1b","m_bt2_1b","dr_tt_1b","dr_bt1_1b","dr_bt2_1b","dr_btt_1b","pt_tt_1b","eta_tt_1b","mt_t1_1b","mt_t2_1b","mt_b_1b","normzeta_1b","dzeta_1b","pt_b_1b","met_1b","njets_1b","pt_t1_2b","pt_t2_2b","m_b1tt_2b","m_b1t1_2b","m_b1t2_2b","dr_tt_2b","dr_b1t1_2b","dr_b1t2_2b","dr_b1tt_2b","pt_tt_2b","eta_tt_2b","mt_t1_2b","mt_t2_2b","mt_b1_2b","normzeta_2b","dzeta_2b","pt_b1_2b","met_2b","njets_2b","m_b2tt_2b","m_bbt1_2b","m_bbt2_2b","m_bbtt_2b","m_bb_2b","m_b2t1_2b","m_b2t2_2b","dr_b2t1_2b","dr_b2t2_2b","dr_bb_2b","dr_b2tt_2b","dr_bbtt_2b","dr_bbt1_2b","dr_bbt2_2b","mt_b2_2b","pt_b2_2b","dma_2b"]

for i in range (0,55):
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





