import argparse
import ROOT

parser = argparse.ArgumentParser()
parser.add_argument('--channel', '-c', default=None, choices=['et','mt','em'], help='channel')
parser.add_argument('--year', '-y', default=None, choices=['2018','2017','2016'], help='year')
args = parser.parse_args()

file=ROOT.TFile(args.channel+"_"+args.year+"/final_"+args.channel+"_"+args.year+".root","update")

if args.channel=="et" or args.channel=="mt":
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
            
        ########## lepton ES
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
            data_fake_syst_down.Add(mc_fake_syst_down,-1)
            data_fake_syst_down.SetName("fake_CMS_"+syst_name[j]+"_"+args.year+"Down")
            data_fake_syst_down.Write()
         
if args.channel=="em":# do normalization on cloned histogram if it should be used multiple times (doing e.g. Integral() in loop will keep modifying along the way)
    dir=["pt_1_1b","pt_2_1b","m_tt_1b","m_btt_1b","pt_1_2b","pt_2_2b","m_tt_2b","m_btt_2b","m_bbtt_2b"]
    for i in range(len(dir)):
        file.cd(dir[i])
        ########### nominal qcd
        mc_ss=file.Get(dir[i]).Get("MC_ss")
        mc_ssloose=file.Get(dir[i]).Get("MC_ssloose")
        data_ss=file.Get(dir[i]).Get("data_obs_ss")
        data_ssloose=file.Get(dir[i]).Get("data_obs_ssloose")
        qcd_ss=data_ss.Clone()
        qcd_ss.Add(mc_ss,-1)
        qcd_ssloose=data_ssloose.Clone()
        qcd_ssloose.Add(mc_ssloose,-1)
        scale=qcd_ss.Integral()/qcd_ssloose.Integral()
        qcd=qcd_ssloose
        qcd.Scale(scale)
        qcd.SetName("qcd")
        qcd.Write()
        
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
            qcd_ss_syst_up=data_ss.Clone()
            qcd_ss_syst_up.Add(mc_ss_syst_up,-1)
            qcd_ssloose_syst_up=data_ssloose.Clone()
            qcd_ssloose_syst_up.Add(mc_ssloose_syst_up,-1)
            scale=qcd_ss_syst_up.Integral()/qcd_ssloose_syst_up.Integral()
            qcd_syst_up=qcd_ssloose_syst_up
            qcd_syst_up.Scale(scale)
            qcd_syst_up.SetName("qcd_CMS_"+syst_name[j]+"_"+args.year+"Up")
            qcd_syst_up.Write()
            
            mc_ss_syst_down=file.Get(dir[i]).Get("MC_ss_CMS_"+syst_name[j]+"_"+args.year+"Down")
            mc_ssloose_syst_down=file.Get(dir[i]).Get("MC_ssloose_CMS_"+syst_name[j]+"_"+args.year+"Down")
            qcd_ss_syst_down=data_ss.Clone()
            qcd_ss_syst_down.Add(mc_ss_syst_down,-1)
            qcd_ssloose_syst_down=data_ssloose.Clone()
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
            

