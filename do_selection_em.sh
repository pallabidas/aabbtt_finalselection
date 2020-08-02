./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/DY.root outputs/DY.root DY background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/DY1.root outputs/DY1.root DY1 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/DY2.root outputs/DY2.root DY2 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/DY3.root outputs/DY3.root DY3 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/DY4.root outputs/DY4.root DY4 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/GGHTT.root outputs/GGHTT.root GGHTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/GGZHLLTT.root outputs/GGZHLLTT.root GGZHLLTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/GGZHNNTT.root outputs/GGZHNNTT.root GGZHNNTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/GGZHQQTT.root outputs/GGZHQQTT.root GGZHQQTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ST_tW_antitop.root outputs/ST_tW_antitop.root ST_tW_antitop background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ST_tW_top.root outputs/ST_tW_top.root ST_tW_top background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ST_t_antitop.root outputs/ST_t_antitop.root ST_t_antitop background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ST_t_top.root outputs/ST_t_top.root ST_t_top background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/TTTo2L2Nu.root outputs/TTTo2L2Nu.root TTTo2L2Nu background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/TTToHadronic.root outputs/TTToHadronic.root TTToHadronic background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/TTToSemiLeptonic.root outputs/TTToSemiLeptonic.root TTToSemiLeptonic background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/VBFHTT.root outputs/VBFHTT.root VBFHTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/VV2L2Nu.root outputs/VV2L2Nu.root VV2L2Nu background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/W.root outputs/W.root W background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/W1.root outputs/W1.root W1 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/W2.root outputs/W2.root W2 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/W3.root outputs/W3.root W3 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/W4.root outputs/W4.root W4 background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/WZ2L2Q.root outputs/WZ2L2Q.root WZ2L2Q background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/WZ3LNu.root outputs/WZ3LNu.root WZ3LNu background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/WminusHTT.root outputs/WminusHTT.root WminusHTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/WplusHTT.root outputs/WplusHTT.root WplusHTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ZHTT.root outputs/ZHTT.root ZHTT background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ZZ2L2Q.root outputs/ZZ2L2Q.root ZZ2L2Q background
./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/ZZ4L.root outputs/ZZ4L.root ZZ4L background

hadd -f outputs/background.root outputs/*.root

./selection_em.exe /nfs_scratch/htsoi/haabbtt_em2018_1jul/data_obs.root outputs/data_obs.root data_obs data_obs
