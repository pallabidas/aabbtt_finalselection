import argparse
import ROOT

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='year')
args = parser.parse_args()

file=ROOT.TFile("em_"+args.year+"/final_em_"+args.year+".root","update")

dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
for i in range(len(dir)):
    file.cd(dir[i])
    ########### nominal qcd
    mc_ss=file.Get(dir[i]).Get("MC_ss")
    mc_ssloose=file.Get(dir[i]).Get("MC_ssloose")
    
    qcd_ss=file.Get(dir[i]).Get("data_obs_ss")
    qcd_ss.Add(mc_ss,-1)
    qcd_ssloose=file.Get(dir[i]).Get("data_obs_ssloose")
    qcd_ssloose.Add(mc_ssloose,-1)
    
    scale=qcd_ss.Integral()/qcd_ssloose.Integral()
    qcd_nominal=qcd_ssloose
    qcd_nominal.Scale(scale)
    
    qcd_nominal.SetName("qcd")
    qcd_nominal.Write()
    
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
    
    ########### JES/recoil/UES/btag/trgeff/Z_pt/toppt/eleES/muES/EMB_trgeff
    syst_name=["JetAbsolute","JetAbsoluteyear","JetBBEC1","JetBBEC1year","JetEC2","JetEC2year","JetFlavorQCD","JetHF","JetHFyear","JetRelativeBal","JetRelativeSample","JER","0j_resolution","0j_response","1j_resolution","1j_response","gt1j_resolution","gt1j_response","UES","btagsf_heavy","btagsf_light","trgeff_Mu8E23","trgeff_Mu23E12","trgeff_both","Zpt","toppt","eleES_bar","eleES_end","muES_eta0to1p2","muES_eta1p2to2p1","muES_eta2p1to2p4","EMB_trgeff_Mu8E23","EMB_trgeff_Mu23E12","EMB_trgeff_both"]
    
    for j in range(len(syst_name)):
        mc_ss_syst_up=file.Get(dir[i]).Get("MC_ss_CMS_"+syst_name[j]+"_"+args.year+"Up")
        mc_ssloose_syst_up=file.Get(dir[i]).Get("MC_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_ss_syst_up=file.Get(dir[i]).Get("data_obs_ss")
        qcd_ss_syst_up.Add(mc_ss_syst_up,-1)
        qcd_ssloose_syst_up=file.Get(dir[i]).Get("data_obs_ssloose")
        qcd_ssloose_syst_up.Add(mc_ssloose_syst_up,-1)
        scale=qcd_ss_syst_up.Integral()/qcd_ssloose_syst_up.Integral()
        qcd_syst_up=qcd_ssloose_syst_up
        qcd_syst_up.Scale(scale)
        qcd_syst_up.SetName("qcd_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_syst_up.Write()
        
        mc_ss_syst_down=file.Get(dir[i]).Get("MC_ss_CMS_"+syst_name[j]+"_"+args.year+"Down")
        mc_ssloose_syst_down=file.Get(dir[i]).Get("MC_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_ss_syst_down=file.Get(dir[i]).Get("data_obs_ss")
        qcd_ss_syst_down.Add(mc_ss_syst_down,-1)
        qcd_ssloose_syst_down=file.Get(dir[i]).Get("data_obs_ssloose")
        qcd_ssloose_syst_down.Add(mc_ssloose_syst_down,-1)
        scale=qcd_ss_syst_down.Integral()/qcd_ssloose_syst_down.Integral()
        qcd_syst_down=qcd_ssloose_syst_down
        qcd_syst_down.Scale(scale)
        qcd_syst_down.SetName("qcd_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_syst_down.Write()
        
    ########### qcd estimation uncertainties: ss2d
    syst_name=["SScorrection","SSclosure","SSboth2D"]
    
    for j in range(len(syst_name)):
        mc_ss_syst_up=file.Get(dir[i]).Get("MC_ss_CMS_"+syst_name[j]+"_"+args.year+"Up")
        mc_ssloose_syst_up=file.Get(dir[i]).Get("MC_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_ss_syst_up=file.Get(dir[i]).Get("data_obs_ss_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_ss_syst_up.Add(mc_ss_syst_up,-1)
        qcd_ssloose_syst_up=file.Get(dir[i]).Get("data_obs_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_ssloose_syst_up.Add(mc_ssloose_syst_up,-1)
        scale=qcd_ss_syst_up.Integral()/qcd_ssloose_syst_up.Integral()
        qcd_syst_up=qcd_ssloose_syst_up
        qcd_syst_up.Scale(scale)
        qcd_syst_up.SetName("qcd_CMS_"+syst_name[j]+"_"+args.year+"Up")
        qcd_syst_up.Write()
        
        mc_ss_syst_down=file.Get(dir[i]).Get("MC_ss_CMS_"+syst_name[j]+"_"+args.year+"Down")
        mc_ssloose_syst_down=file.Get(dir[i]).Get("MC_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_ss_syst_down=file.Get(dir[i]).Get("data_obs_ss_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_ss_syst_down.Add(mc_ss_syst_down,-1)
        qcd_ssloose_syst_down=file.Get(dir[i]).Get("data_obs_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_ssloose_syst_down.Add(mc_ssloose_syst_down,-1)
        scale=qcd_ss_syst_down.Integral()/qcd_ssloose_syst_down.Integral()
        qcd_syst_down=qcd_ssloose_syst_down
        qcd_syst_down.Scale(scale)
        qcd_syst_down.SetName("qcd_CMS_"+syst_name[j]+"_"+args.year+"Down")
        qcd_syst_down.Write()

