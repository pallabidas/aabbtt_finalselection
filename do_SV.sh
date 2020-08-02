./Make.sh CheckSV.cc
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt15.root files_nominal/bbtt15.root bbtt15 ggH_haa_bbtt15 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt20.root files_nominal/bbtt20.root bbtt20 ggH_haa_bbtt20 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt25.root files_nominal/bbtt25.root bbtt25 ggH_haa_bbtt25 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt30.root files_nominal/bbtt30.root bbtt30 ggH_haa_bbtt30 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt35.root files_nominal/bbtt35.root bbtt35 ggH_haa_bbtt35 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt40.root files_nominal/bbtt40.root bbtt40 ggH_haa_bbtt40 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt45.root files_nominal/bbtt45.root bbtt45 ggH_haa_bbtt45 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt50.root files_nominal/bbtt50.root bbtt50 ggH_haa_bbtt50 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt55.root files_nominal/bbtt55.root bbtt55 ggH_haa_bbtt55 0
./CheckSV.exe /data/ccaillol/bbtt_mt_svfitted_12jan/bbtt60.root files_nominal/bbtt60.root bbtt60 ggH_haa_bbtt60 0
hadd -f mvis_signal_mt.root files_nominal/bbtt15.root files_nominal/bbtt20.root files_nominal/bbtt25.root files_nominal/bbtt30.root files_nominal/bbtt35.root files_nominal/bbtt40.root files_nominal/bbtt45.root files_nominal/bbtt50.root files_nominal/bbtt55.root files_nominal/bbtt60.root 
