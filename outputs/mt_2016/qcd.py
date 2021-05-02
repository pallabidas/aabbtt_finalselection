import ROOT

file=ROOT.TFile("final_mt_2016.root","update")

dir=["pt_1","pt_2","m_tt","m_btt"]

for i in range (0,4):
    Data_fake=file.Get(dir[i]).Get("data_obs_fake")
    HTT_fake=file.Get(dir[i]).Get("HTT_fake")
    HWW_fake=file.Get(dir[i]).Get("HWW_fake")
    Z_fake=file.Get(dir[i]).Get("Z_fake")
#    W_fake=file.Get(dir[i]).Get("W_fake")
    TT_fake=file.Get(dir[i]).Get("TT_fake")
    VV_fake=file.Get(dir[i]).Get("VV_fake")
    ZTT_fake=file.Get(dir[i]).Get("ZTT_fake")
    ST_fake=file.Get(dir[i]).Get("ST_fake")
    ttHnonbb_fake=file.Get(dir[i]).Get("ttHnonbb_fake")

#    TT=file.Get(dir[i]).Get("TT")
#    ZTT=file.Get(dir[i]).Get("ZTT")

    #blinded=file.Get(dir[i]).Get("gghbbtt40_fake")
    #blinded.Scale(0)

    qcd=Data_fake
    qcd.Add(HTT_fake,-1)
    qcd.Add(HWW_fake,-1)
    qcd.Add(Z_fake,-1)
#    qcd.Add(W_fake,-1)
    qcd.Add(TT_fake,-1)
    qcd.Add(VV_fake,-1)
    qcd.Add(ZTT_fake,-1)
    qcd.Add(ST_fake,-1)
    qcd.Add(ttHnonbb_fake,-1)
    
    
    file.cd(dir[i])
    qcd.SetName("fake")
    qcd.Write()
    
    #blinded.SetName("blinded")
    #blinded.Write()

    #nonDY contamination to emb
    nonDYMC=file.Get(dir[i]).Get("nonDYMC_nonDY")

    ZTT=file.Get(dir[i]).Get("ZTT")
    ZTT_nonDYUp=ZTT
    ZTT_nonDYUp.Add(nonDYMC)
    ZTT_nonDYUp.SetName("ZTT_CMS_embedding_nonDY_2016Up")
    ZTT_nonDYUp.Write()
    ZTT=file.Get(dir[i]).Get("ZTT")
    ZTT_nonDYDown=ZTT
    ZTT_nonDYDown.Add(nonDYMC,-1)
    ZTT_nonDYDown.SetName("ZTT_CMS_embedding_nonDY_2016Down")
    ZTT_nonDYDown.Write()

    data_fake_xtrgup=file.Get(dir[i]).Get("data_obs_fake_CMS_crosstrg_fakefactor_2016Up")
    data_fake_xtrgdown=file.Get(dir[i]).Get("data_obs_fake_CMS_crosstrg_fakefactor_2016Down")
    data_fake_fr_0up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt0to25_2016Up")
    data_fake_fr_0down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt0to25_2016Down")
    data_fake_fr_1up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt25to30_2016Up")
    data_fake_fr_1down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt25to30_2016Down")
    data_fake_fr_2up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt30to35_2016Up")
    data_fake_fr_2down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt30to35_2016Down")
    data_fake_fr_3up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt35to40_2016Up")
    data_fake_fr_3down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt35to40_2016Down")
    data_fake_fr_4up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt40to50_2016Up")
    data_fake_fr_4down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt40to50_2016Down")
    data_fake_fr_5up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt50to60_2016Up")
    data_fake_fr_5down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_pt50to60_2016Down")
    data_fake_fr_6up=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_ptgt60_2016Up")
    data_fake_fr_6down=file.Get(dir[i]).Get("data_obs_fake_CMS_fakerate_alldm_ptgt60_2016Down")

    mc_fake_xtrgup=file.Get(dir[i]).Get("MC_fake_CMS_crosstrg_fakefactor_2016Up")
    mc_fake_xtrgdown=file.Get(dir[i]).Get("MC_fake_CMS_crosstrg_fakefactor_2016Down")
    mc_fake_fr_0up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt0to25_2016Up")
    mc_fake_fr_0down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt0to25_2016Down")
    mc_fake_fr_1up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt25to30_2016Up")
    mc_fake_fr_1down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt25to30_2016Down")
    mc_fake_fr_2up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt30to35_2016Up")
    mc_fake_fr_2down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt30to35_2016Down")
    mc_fake_fr_3up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt35to40_2016Up")
    mc_fake_fr_3down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt35to40_2016Down")
    mc_fake_fr_4up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt40to50_2016Up")
    mc_fake_fr_4down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt40to50_2016Down")
    mc_fake_fr_5up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt50to60_2016Up")
    mc_fake_fr_5down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_pt50to60_2016Down")
    mc_fake_fr_6up=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_ptgt60_2016Up")
    mc_fake_fr_6down=file.Get(dir[i]).Get("MC_fake_CMS_fakerate_alldm_ptgt60_2016Down")

    fake_xtrgup=data_fake_xtrgup
    fake_xtrgup.Add(mc_fake_xtrgup,-1)
    fake_xtrgup.SetName("fake_CMS_crosstrg_fakefactor_2016Up")
    fake_xtrgup.Write()
    fake_xtrgdown=data_fake_xtrgdown
    fake_xtrgdown.Add(mc_fake_xtrgdown,-1)
    fake_xtrgdown.SetName("fake_CMS_crosstrg_fakefactor_2016Down")
    fake_xtrgdown.Write()
    fake_fr_0up=data_fake_fr_0up
    fake_fr_0up.Add(mc_fake_fr_0up,-1)
    fake_fr_0up.SetName("fake_CMS_fakerate_alldm_pt0to25_2016Up")
    fake_fr_0up.Write()
    fake_fr_0down=data_fake_fr_0down
    fake_fr_0down.Add(mc_fake_fr_0down,-1)
    fake_fr_0down.SetName("fake_CMS_fakerate_alldm_pt0to25_2016Down")
    fake_fr_0down.Write()
    fake_fr_1up=data_fake_fr_1up
    fake_fr_1up.Add(mc_fake_fr_1up,-1)
    fake_fr_1up.SetName("fake_CMS_fakerate_alldm_pt25to30_2016Up")
    fake_fr_1up.Write()
    fake_fr_1down=data_fake_fr_1down
    fake_fr_1down.Add(mc_fake_fr_1down,-1)
    fake_fr_1down.SetName("fake_CMS_fakerate_alldm_pt25to30_2016Down")
    fake_fr_1down.Write()
    fake_fr_2up=data_fake_fr_2up
    fake_fr_2up.Add(mc_fake_fr_2up,-1)
    fake_fr_2up.SetName("fake_CMS_fakerate_alldm_pt30to35_2016Up")
    fake_fr_2up.Write()
    fake_fr_2down=data_fake_fr_2down
    fake_fr_2down.Add(mc_fake_fr_2down,-1)
    fake_fr_2down.SetName("fake_CMS_fakerate_alldm_pt30to35_2016Down")
    fake_fr_2down.Write()
    fake_fr_3up=data_fake_fr_3up
    fake_fr_3up.Add(mc_fake_fr_3up,-1)
    fake_fr_3up.SetName("fake_CMS_fakerate_alldm_pt35to40_2016Up")
    fake_fr_3up.Write()
    fake_fr_3down=data_fake_fr_3down
    fake_fr_3down.Add(mc_fake_fr_3down,-1)
    fake_fr_3down.SetName("fake_CMS_fakerate_alldm_pt35to40_2016Down")
    fake_fr_3down.Write()
    fake_fr_4up=data_fake_fr_4up
    fake_fr_4up.Add(mc_fake_fr_4up,-1)
    fake_fr_4up.SetName("fake_CMS_fakerate_alldm_pt40to50_2016Up")
    fake_fr_4up.Write()
    fake_fr_4down=data_fake_fr_4down
    fake_fr_4down.Add(mc_fake_fr_4down,-1)
    fake_fr_4down.SetName("fake_CMS_fakerate_alldm_pt40to50_2016Down")
    fake_fr_4down.Write()
    fake_fr_5up=data_fake_fr_5up
    fake_fr_5up.Add(mc_fake_fr_5up,-1)
    fake_fr_5up.SetName("fake_CMS_fakerate_alldm_pt50to60_2016Up")
    fake_fr_5up.Write()
    fake_fr_5down=data_fake_fr_5down
    fake_fr_5down.Add(mc_fake_fr_5down,-1)
    fake_fr_5down.SetName("fake_CMS_fakerate_alldm_pt50to60_2016Down")
    fake_fr_5down.Write()
    fake_fr_6up=data_fake_fr_6up
    fake_fr_6up.Add(mc_fake_fr_6up,-1)
    fake_fr_6up.SetName("fake_CMS_fakerate_alldm_ptgt60_2016Up")
    fake_fr_6up.Write()
    fake_fr_6down=data_fake_fr_6down
    fake_fr_6down.Add(mc_fake_fr_6down,-1)
    fake_fr_6down.SetName("fake_CMS_fakerate_alldm_ptgt60_2016Down")
    fake_fr_6down.Write()
    

#    if dir[i]=='m_tt_1b':
#      print('TT:'+str(TT.Integral()))
#      print('ZTT:'+str(ZTT.Integral()))
#      print('qcd:'+str(qcd.Integral()))


