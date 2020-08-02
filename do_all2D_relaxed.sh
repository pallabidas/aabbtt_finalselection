./Make.sh FinalSelection2D_relaxed.cc
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/Data.root files_nominal/Data.root data_obs data_obs 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY.root files_nominal/ZTTall.root ZTT ZTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY.root files_nominal/ZLall.root ZL ZL 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY.root files_nominal/ZJall.root ZJ ZJ 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY1.root files_nominal/ZTT1.root ZTT ZTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY1.root files_nominal/ZL1.root ZL ZL 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY1.root files_nominal/ZJ1.root ZJ ZJ 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY2.root files_nominal/ZTT2.root ZTT ZTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY2.root files_nominal/ZL2.root ZL ZL 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY2.root files_nominal/ZJ2.root ZJ ZJ 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY3.root files_nominal/ZTT3.root ZTT ZTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY3.root files_nominal/ZL3.root ZL ZL 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY3.root files_nominal/ZJ3.root ZJ ZJ 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY4.root files_nominal/ZTT4.root ZTT ZTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY4.root files_nominal/ZL4.root ZL ZL 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY4.root files_nominal/ZJ4.root ZJ ZJ 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DYlow.root files_nominal/DYlow.root DYlow ZTT 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY1low.root files_nominal/DY1low.root DY1low ZTT 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/DY2low.root files_nominal/DY2low.root DY2low ZTT 0
hadd -f files_nominal/ZTT.root files_nominal/ZTTall.root files_nominal/ZTT1.root files_nominal/ZTT2.root files_nominal/ZTT3.root files_nominal/ZTT4.root files_nominal/DY1low.root files_nominal/DY2low.root  files_nominal/DYlow.root
hadd -f files_nominal/ZL.root files_nominal/ZLall.root files_nominal/ZL1.root files_nominal/ZL2.root files_nominal/ZL3.root files_nominal/ZL4.root 
hadd -f files_nominal/ZJ.root files_nominal/ZJall.root files_nominal/ZJ1.root files_nominal/ZJ2.root files_nominal/ZJ3.root files_nominal/ZJ4.root 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/TT.root files_nominal/TTT.root TTT TTT 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/TT.root files_nominal/TTL.root TTL TTL 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/TT.root files_nominal/TTJ.root TTJ TTJ 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/W.root files_nominal/Wincl.root W W 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/W1.root files_nominal/W1.root W W 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/W2.root files_nominal/W2.root W W 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/W3.root files_nominal/W3.root W W 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/W4.root files_nominal/W4.root W W 0 
hadd -f files_nominal/W.root files_nominal/W4.root files_nominal/W3.root files_nominal/W2.root files_nominal/W1.root files_nominal/Wincl.root
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WW1L1Nu2Q.root files_nominal/WW1L1Nu2Q.root WW1L1Nu2Q VV 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VV2L2Nu.root files_nominal/VV2L2Nu.root VV2L2Nu VV 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WZLLLNu.root files_nominal/WZLLLNu.root WZLLLNu VV 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ZZ2L2Q.root files_nominal/ZZ2L2Q.root ZZ2L2Q VV 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ZZ4L.root files_nominal/ZZ4L.root ZZ4L VV 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WZ2L2Q.root files_nominal/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WZ1L3Nu.root files_nominal/WZ1L3Nu.root WZ1L3Nu VV 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WZ1L1Nu2Q.root files_nominal/WZ1L1Nu2Q.root WZ1L1Nu2Q VV 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ST_t_top.root files_nominal/ST_t_top.root ST_t_top ST 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ST_t_antitop.root files_nominal/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ST_tW_top.root files_nominal/ST_tW_top.root ST_tW_top ST 0 
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ST_tW_antitop.root files_nominal/ST_tW_antitop.root ST_tW_antitop ST 0 
hadd -f files_nominal/VV.root files_nominal/WW1L1Nu2Q.root files_nominal/ZZ2L2Q.root files_nominal/WZ2L2Q.root files_nominal/WZ1L3Nu.root files_nominal/WZ1L1Nu2Q.root files_nominal/VV2L2Nu.root files_nominal/WZLLLNu.root files_nominal/ZZ4L.root
hadd -f files_nominal/ST.root files_nominal/ST_t_top.root files_nominal/ST_t_antitop.root files_nominal/ST_tW_top.root files_nominal/ST_tW_antitop.root
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt15.root files_nominal/bbtt15.root bbtt15 ggH_haa_bbtt15 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt20.root files_nominal/bbtt20.root bbtt20 ggH_haa_bbtt20 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt25.root files_nominal/bbtt25.root bbtt25 ggH_haa_bbtt25 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt30.root files_nominal/bbtt30.root bbtt30 ggH_haa_bbtt30 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt35.root files_nominal/bbtt35.root bbtt35 ggH_haa_bbtt35 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/bbtt40.root files_nominal/bbtt40.root bbtt40 ggH_haa_bbtt40 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt45.root files_nominal/bbtt45.root bbtt45 ggH_haa_bbtt45 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt50.root files_nominal/bbtt50.root bbtt50 ggH_haa_bbtt50 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt55.root files_nominal/bbtt55.root bbtt55 ggH_haa_bbtt55 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_7apr/bbtt60.root files_nominal/bbtt60.root bbtt60 ggH_haa_bbtt60 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VBFbbtt20.root files_nominal/VBFbbtt20.root VBFbbtt20 VBFbbtt20 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VBFbbtt40.root files_nominal/VBFbbtt40.root VBFbbtt40 VBFbbtt40 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VBFbbtt60.root files_nominal/VBFbbtt60.root VBFbbtt60 VBFbbtt60 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/WHbbtt40.root files_nominal/WHbbtt40.root WHbbtt40 WHbbtt40 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_15nov/ZHbbtt40.root files_nominal/ZHbbtt40.root ZHbbtt40 ZHbbtt40 0
hadd -f files_nominal/signal.root files_nominal/bbtt15.root files_nominal/bbtt20.root files_nominal/bbtt25.root files_nominal/bbtt30.root files_nominal/bbtt35.root files_nominal/bbtt40.root files_nominal/bbtt45.root files_nominal/bbtt50.root files_nominal/bbtt55.root files_nominal/bbtt60.root files_nominal/VBFbbtt20.root files_nominal/VBFbbtt40.root files_nominal/VBFbbtt60.root files_nominal/WHbbtt40.root files_nominal/ZHbbtt40.root
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ggH125.root files_nominal/ggH125.root ggH125 ggH_htt125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ggHWW125.root files_nominal/ggHWW125.root ggHWW125 ggH_hww125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VBF125.root files_nominal/VBFH125.root VBF125 qqH_htt125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/VBFWW125.root files_nominal/VBFHWW125.root VBFWW125 qqH_hww125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ZH125.root files_nominal/ZH125.root ZH125 ZH_htt125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ZHWW125.root files_nominal/ZHWW125.root ZHWW125 ZH_hww125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WplusH125.root files_nominal/WplusH125.root WplusH125 WH_htt125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WplusHWW125.root files_nominal/WplusHWW125.root WplusHWW125 WH_hww125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WminusH125.root files_nominal/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WminusHWW125.root files_nominal/WminusHWW125.root WminusHWW125 WH_hww125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ttHnonbb.root files_nominal/ttHnonbb.root ttHnonbb ttH_nonbb125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/ZH_LLBB.root files_nominal/ZH_LLBB.root ZH_LLBB ZH_hbb125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WminusH_LBB.root files_nominal/WminusH_LBB.root WminusH_LBB WH_hbb125 0
./FinalSelection2D_relaxed.exe /data/ccaillol/BBTT_mt_11august/WplusH_LBB.root files_nominal/WplusH_LBB.root WplusH_LBB WH_hbb125 0
hadd -f files_nominal/SMH.root files_nominal/ggH125.root files_nominal/ggHWW125.root files_nominal/VBFH125.root files_nominal/VBFHWW125.root files_nominal/ZH125.root files_nominal/ZHWW125.root files_nominal/WplusH125.root files_nominal/WplusHWW125.root files_nominal/WminusH125.root files_nominal/WminusHWW125.root files_nominal/ttHnonbb.root files_nominal/ZH_LLBB.root files_nominal/WminusH_LBB.root files_nominal/WplusH_LBB.root 

python Create_QCD_2Drelaxed.py --scale nominal 
python Create_fake.py
hadd -f final_nominal.root files_nominal/W.root files_nominal/Data.root files_nominal/ZL.root files_nominal/ZJ.root files_nominal/ZTT.root files_nominal/TTT.root files_nominal/TTJ.root files_nominal/QCD.root files_nominal/VV.root files_nominal/signal.root files_nominal/ST.root files_nominal/Fake.root

