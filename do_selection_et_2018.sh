#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/embedded.root outputs/et_2018/embedded.root embedded ZTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/DY.root outputs/et_2018/DY.root DY Z
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/DY1.root outputs/et_2018/DY1.root DY1 Z
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/DY2.root outputs/et_2018/DY2.root DY2 Z
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/DY3.root outputs/et_2018/DY3.root DY3 Z
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/DY4.root outputs/et_2018/DY4.root DY4 Z
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/GGHTT.root outputs/et_2018/GGHTT.root GGHTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/GGZHLLTT.root outputs/et_2018/GGZHLLTT.root GGZHLLTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/GGZHNNTT.root outputs/et_2018/GGZHNNTT.root GGZHNNTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/GGZHQQTT.root outputs/et_2018/GGZHQQTT.root GGZHQQTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ST_tW_antitop.root outputs/et_2018/ST_tW_antitop.root ST_tW_antitop ST
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ST_tW_top.root outputs/et_2018/ST_tW_top.root ST_tW_top ST
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ST_t_antitop.root outputs/et_2018/ST_t_antitop.root ST_t_antitop ST
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ST_t_top.root outputs/et_2018/ST_t_top.root ST_t_top ST
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/TTTo2L2Nu.root outputs/et_2018/TTTo2L2Nu.root TTTo2L2Nu TT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/TTToHadronic.root outputs/et_2018/TTToHadronic.root TTToHadronic TT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/TTToSemiLeptonic.root outputs/et_2018/TTToSemiLeptonic.root TTToSemiLeptonic TT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/VBFHTT.root outputs/et_2018/VBFHTT.root VBFHTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/VV2L2Nu.root outputs/et_2018/VV2L2Nu.root VV2L2Nu VV
#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/W.root outputs/et_2018/W.root W W
#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/W1.root outputs/et_2018/W1.root W1 W
#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/W2.root outputs/et_2018/W2.root W2 W
#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/W3.root outputs/et_2018/W3.root W3 W
#./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/W4.root outputs/et_2018/W4.root W4 W
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/WZ2L2Q.root outputs/et_2018/WZ2L2Q.root WZ2L2Q VV
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/WZ3LNu.root outputs/et_2018/WZ3LNu.root WZ3LNu VV
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/WminusHTT.root outputs/et_2018/WminusHTT.root WminusHTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/WplusHTT.root outputs/et_2018/WplusHTT.root WplusHTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ZHTT.root outputs/et_2018/ZHTT.root ZHTT HTT
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ZZ2L2Q.root outputs/et_2018/ZZ2L2Q.root ZZ2L2Q VV
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/ZZ4L.root outputs/et_2018/ZZ4L.root ZZ4L VV
./selection_et_2018.exe /nfs_scratch/htsoi/haabbtt_et2018_14aug/data_obs.root outputs/et_2018/data_obs.root data_obs data_obs
#./selection_et_2018.exe /nfs_scratch/htsoi/signal_haabbtt_et2018_4sep/gghbbtt40.root outputs/et_2018/gghbbtt40.root gghbbtt40 bbtt40
#./selection_et_2018.exe /nfs_scratch/htsoi/signal_haabbtt_et2018_4sep/VBFbbtt40.root outputs/et_2018/VBFbbtt40.root VBFbbtt40 bbtt40

#hadd -f outputs/et_2018/final_et_2018.root outputs/et_2018/*.root
