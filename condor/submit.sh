channel=$1
year=$2

mkdir -p ${channel}_${year}
cp condorSubmitter.sh ${channel}_${year}/
cp do_selection.sh ${channel}_${year}/
cd ${channel}_${year}

### sh condorSubmitter.sh channel year INsample sample name requestdisk

sh condorSubmitter.sh ${channel} ${year} data_obs data_obs data_obs 20G

sh condorSubmitter.sh ${channel} ${year} embedded embedded embedded 22G

sh condorSubmitter.sh ${channel} ${year} TTTo2L2Nu TTTo2L2Nu ttbar 20G
sh condorSubmitter.sh ${channel} ${year} TTToHadronic TTToHadronic ttbar 10G
sh condorSubmitter.sh ${channel} ${year} TTToSemiLeptonic TTToSemiLeptonic ttbar 32G

mass=(12 15 20 25 30 35 40 45 50 55 60)
for mass in "${mass[@]}"
do
  sh condorSubmitter.sh ${channel} ${year} ggH_bbtt${mass} gghbbtt${mass} gghbbtt${mass} 6G
  sh condorSubmitter.sh ${channel} ${year} vbf_bbtt${mass} vbfbbtt${mass} vbfbbtt${mass} 6G
done

sh condorSubmitter.sh ${channel} ${year} DY DY ZJ 7G
sh condorSubmitter.sh ${channel} ${year} DY1 DY1 ZJ 7G
sh condorSubmitter.sh ${channel} ${year} DY2 DY2 ZJ 7G
sh condorSubmitter.sh ${channel} ${year} DY3 DY3 ZJ 7G
sh condorSubmitter.sh ${channel} ${year} DY4 DY4 ZJ 7G
if [ $year == "2017" ] || [ $year == "2018" ]
then
  sh condorSubmitter.sh ${channel} ${year} DYlow DYlow ZJ 7G
fi
if [ $year == "2016" ]
then
  sh condorSubmitter.sh ${channel} ${year} DYlow DYlow ZJ 7G
  sh condorSubmitter.sh ${channel} ${year} DY1low DY1low ZJ 7G
  sh condorSubmitter.sh ${channel} ${year} DY2low DY2low ZJ 7G
  sh condorSubmitter.sh ${channel} ${year} DY3low DY3low ZJ 7G
  sh condorSubmitter.sh ${channel} ${year} DY4low DY4low ZJ 7G
fi
sh condorSubmitter.sh ${channel} ${year} GGHTT GGHTT ggh_htt 7G
sh condorSubmitter.sh ${channel} ${year} GGHWW GGHWW ggh_hww 7G
sh condorSubmitter.sh ${channel} ${year} GGZHLLTT GGZHLLTT Zh_htt 7G
sh condorSubmitter.sh ${channel} ${year} GGZHNNTT GGZHNNTT Zh_htt 7G
sh condorSubmitter.sh ${channel} ${year} GGZHQQTT GGZHQQTT Zh_htt 7G
sh condorSubmitter.sh ${channel} ${year} GGZHWW GGZHWW Zh_hww 7G
sh condorSubmitter.sh ${channel} ${year} ST_tW_antitop ST_tW_antitop ST 7G
sh condorSubmitter.sh ${channel} ${year} ST_tW_top ST_tW_top ST 7G
sh condorSubmitter.sh ${channel} ${year} ST_t_antitop ST_t_antitop ST 7G
sh condorSubmitter.sh ${channel} ${year} ST_t_top ST_t_top ST 7G
sh condorSubmitter.sh ${channel} ${year} VBFHTT VBFHTT qqh_htt 7G
sh condorSubmitter.sh ${channel} ${year} VBFHWW VBFHWW qqh_hww 7G
sh condorSubmitter.sh ${channel} ${year} VV2L2Nu VV2L2Nu VV 7G
sh condorSubmitter.sh ${channel} ${year} WZ2L2Q WZ2L2Q VV 7G
sh condorSubmitter.sh ${channel} ${year} WZ3L1Nu WZ3L1Nu VV 7G
sh condorSubmitter.sh ${channel} ${year} WminusHTT WminusHTT Wh_htt 7G
sh condorSubmitter.sh ${channel} ${year} WminusHWW WminusHWW Wh_hww 7G
sh condorSubmitter.sh ${channel} ${year} WplusHTT WplusHTT Wh_htt 7G
sh condorSubmitter.sh ${channel} ${year} WplusHWW WplusHWW Wh_hww 7G
sh condorSubmitter.sh ${channel} ${year} ZHTT ZHTT Zh_htt 7G
sh condorSubmitter.sh ${channel} ${year} ZHWW ZHWW Zh_hww 7G
sh condorSubmitter.sh ${channel} ${year} ZZ2L2Q ZZ2L2Q VV 7G
sh condorSubmitter.sh ${channel} ${year} ZZ4L ZZ4L VV 7G
sh condorSubmitter.sh ${channel} ${year} ttHnonbb ttHnonbb tth 7G
sh condorSubmitter.sh ${channel} ${year} ttHbb ttHbb tth 7G
if [ $channel == "em" ]
then
  sh condorSubmitter.sh ${channel} ${year} W W WJ 7G
  sh condorSubmitter.sh ${channel} ${year} W1 W1 WJ 7G
  sh condorSubmitter.sh ${channel} ${year} W2 W2 WJ 7G
  sh condorSubmitter.sh ${channel} ${year} W3 W3 WJ 7G
  sh condorSubmitter.sh ${channel} ${year} W4 W4 WJ 7G
fi

cd ..
