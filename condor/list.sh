channel=$1
year=$2
cd ${channel}_${year}
ls data_obs.root
ls embedded.root
ls TTTo2L2Nu.root
ls TTToHadronic.root
ls TTToSemiLeptonic.root
mass=(12 15 20 25 30 35 40 45 50 55 60)
for mass in "${mass[@]}"
do
  ls gghbbtt${mass}.root
  ls vbfbbtt${mass}.root
done
ls DY.root
ls DY1.root
ls DY2.root
ls DY3.root
ls DY4.root
if [ $year == "2017" ] || [ $year == "2018" ]
then
  ls DYlow.root
fi
if [ $year == "2016" ]
then
  ls DYlow.root
  ls DY1low.root
  ls DY2low.root
  ls DY3low.root
  ls DY4low.root
fi
ls GGHTT.root
ls GGHWW.root
ls GGZHLLTT.root
ls GGZHNNTT.root
ls GGZHQQTT.root
ls GGZHWW.root
ls ST_tW_antitop.root
ls ST_tW_top.root
ls ST_t_antitop.root
ls ST_t_top.root
ls VBFHTT.root
ls VBFHWW.root
ls VV2L2Nu.root
ls WZ2L2Q.root
ls WZ3L1Nu.root
ls WminusHTT.root
ls WminusHWW.root
ls WplusHTT.root
ls WplusHWW.root
ls ZHTT.root
ls ZHWW.root
ls ZZ2L2Q.root
ls ZZ4L.root
ls ttHnonbb.root
ls ttHbb.root
if [ $channel == "em" ]
then
  ls W.root
  ls W1.root
  ls W2.root
  ls W3.root
  ls W4.root
fi
cd ..
