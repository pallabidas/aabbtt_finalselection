import argparse
import ROOT

parser = argparse.ArgumentParser()
parser.add_argument('--channel', '-c', default=None, help='channel')
parser.add_argument('--year', '-y', default=None, help='year')
args = parser.parse_args()

file=ROOT.TFile(args.channel+"_"+args.year+"/final_"+args.channel+"_"+args.year+".root","update")

dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
for i in range(len(dir)):
    file.cd(dir[i])
    ########### nominal fake
    mc_fake=file.Get(dir[i]).Get("MC_fake")
    
    fake_nominal=file.Get(dir[i]).Get("data_obs_fake")
    fake_nominal.Add(mc_fake,-1)
    
    fake_nominal.SetName("fake")
    fake_nominal.Write()
    
    ########### nonDY MC contamination to embedded sample
    nonDYMC=file.Get(dir[i]).Get("nonDYMC")
    
    nonDYMC_up=file.Get(dir[i]).Get("embedded")
    nonDYMC_up.Add(nonDYMC)
    nonDYMC_up.SetName("embedded_CMS_nonDY_"+args.year+"Up")
    nonDYMC_up.Write()
    
    nonDYMC_down=file.Get(dir[i]).Get("embedded")
    nonDYMC_down.Add(nonDYMC,-1)
    nonDYMC_down.SetName("embedded_CMS_nonDY_"+args.year+"Down")
    nonDYMC_down.Write()
    
    ########### JES/recoil/UES/btag/trgeff/Z_pt/toppt/EMB_trgeff
    syst_name=["JetAbsolute","JetAbsoluteyear","JetBBEC1","JetBBEC1year","JetEC2","JetEC2year","JetFlavorQCD","JetHF","JetHFyear","JetRelativeBal","JetRelativeSample","JER","0j_resolution","0j_response","1j_resolution","1j_response","gt1j_resolution","gt1j_response","UES","btagsf_heavy","btagsf_light","trgeff_single","trgeff_cross","Zpt","toppt","EMB_trgeff_single","EMB_trgeff_cross"]
    
    for j in range(len(syst_name)):
        mc_fake_syst_up=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
        fake_syst_up=file.Get(dir[i]).Get("data_obs_fake")
        fake_syst_up.Add(mc_fake_syst_up,-1)
        fake_syst_up.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
        fake_syst_up.Write()
        
        mc_fake_syst_down=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
        fake_syst_down=file.Get(dir[i]).Get("data_obs_fake")
        fake_syst_down.Add(mc_fake_syst_down,-1)
        fake_syst_down.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
        fake_syst_down.Write()
        
    ########### lepton ES
    if args.channel=="et":
        syst_name=["eleES_bar","eleES_end"]
        for j in range(len(syst_name)):
            mc_fake_syst_up=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
            fake_syst_up=file.Get(dir[i]).Get("data_obs_fake")
            fake_syst_up.Add(mc_fake_syst_up,-1)
            fake_syst_up.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
            fake_syst_up.Write()
            
            mc_fake_syst_down=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
            fake_syst_down=file.Get(dir[i]).Get("data_obs_fake")
            fake_syst_down.Add(mc_fake_syst_down,-1)
            fake_syst_down.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
            fake_syst_down.Write()
            
    if args.channel=="mt":
        syst_name=["muES_eta0to1p2","muES_eta1p2to2p1","muES_eta2p1to2p4"]
        for j in range(len(syst_name)):
            mc_fake_syst_up=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
            fake_syst_up=file.Get(dir[i]).Get("data_obs_fake")
            fake_syst_up.Add(mc_fake_syst_up,-1)
            fake_syst_up.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
            fake_syst_up.Write()
            
            mc_fake_syst_down=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
            fake_syst_down=file.Get(dir[i]).Get("data_obs_fake")
            fake_syst_down.Add(mc_fake_syst_down,-1)
            fake_syst_down.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
            fake_syst_down.Write()
            
    ########### fake method uncertainties: crosstrg fakefactor/jetFR
    syst_name=["crosstrg_fakefactor","jetFR_pt0to25","jetFR_pt25to30","jetFR_pt30to35","jetFR_pt35to40","jetFR_pt40to50","jetFR_pt50to60","jetFR_ptgt60"]
    
    for j in range(len(syst_name)):
        data_fake_syst_up=file.Get(dir[i]).Get("data_obs_fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
        mc_fake_syst_up=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
        data_fake_syst_up.Add(mc_fake_syst_up,-1)
        data_fake_syst_up.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Up")
        data_fake_syst_up.Write()
        
        data_fake_syst_down=file.Get(dir[i]).Get("data_obs_fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
        mc_fake_syst_down=file.Get(dir[i]).Get("MC_fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
        data_fake_syst_down=file.Get(dir[i]).Get("data_obs_fake")
        data_fake_syst_down.Add(mc_fake_syst_down,-1)
        data_fake_syst_down.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
        data_fake_syst_down.Write()

