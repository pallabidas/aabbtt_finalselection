#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/embedded.root outputs/embedded.root embedded Z
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/DY.root outputs/DY.root DY Z
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/DY1.root outputs/DY1.root DY1 Z
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/DY2.root outputs/DY2.root DY2 Z
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/DY3.root outputs/DY3.root DY3 Z
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/DY4.root outputs/DY4.root DY4 Z
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/GGHTT.root outputs/GGHTT.root GGHTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/GGZHLLTT.root outputs/GGZHLLTT.root GGZHLLTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/GGZHNNTT.root outputs/GGZHNNTT.root GGZHNNTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/GGZHQQTT.root outputs/GGZHQQTT.root GGZHQQTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ST_tW_antitop.root outputs/ST_tW_antitop.root ST_tW_antitop ST
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ST_tW_top.root outputs/ST_tW_top.root ST_tW_top ST
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ST_t_antitop.root outputs/ST_t_antitop.root ST_t_antitop ST
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ST_t_top.root outputs/ST_t_top.root ST_t_top ST
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/TTTo2L2Nu.root outputs/TTTo2L2Nu.root TTTo2L2Nu TT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/TTToHadronic.root outputs/TTToHadronic.root TTToHadronic TT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/TTToSemiLeptonic.root outputs/TTToSemiLeptonic.root TTToSemiLeptonic TT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/VBFHTT.root outputs/VBFHTT.root VBFHTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/VV2L2Nu.root outputs/VV2L2Nu.root VV2L2Nu VV
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/W.root outputs/W.root W W
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/W1.root outputs/W1.root W1 W
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/W2.root outputs/W2.root W2 W
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/W3.root outputs/W3.root W3 W
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/W4.root outputs/W4.root W4 W
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/WZ2L2Q.root outputs/WZ2L2Q.root WZ2L2Q VV
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/WZ3LNu.root outputs/WZ3LNu.root WZ3LNu VV
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/WminusHTT.root outputs/WminusHTT.root WminusHTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/WplusHTT.root outputs/WplusHTT.root WplusHTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ZHTT.root outputs/ZHTT.root ZHTT HTT
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ZZ2L2Q.root outputs/ZZ2L2Q.root ZZ2L2Q VV
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/ZZ4L.root outputs/ZZ4L.root ZZ4L VV
./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/data_obs.root outputs/data_obs.root data_obs data_obs
#./selection_em_2018.exe /nfs_scratch/htsoi/haabbtt_em2018_14aug/bbtt60.root outputs/bbtt60.root bbtt60 bbtt60

#hadd -f outputs/final_em.root outputs/*.root
