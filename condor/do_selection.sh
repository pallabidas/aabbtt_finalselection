#!/bin/bash
set -x
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
scram project CMSSW CMSSW_9_4_0
cd CMSSW_9_4_0
eval `scram runtime -sh`
cd ..

##############sh do_selection.sh channel year sample

channel=$1
year=$2
INsample=$3
sample=$4
name=$5

##############

cd inputs_forCondor
./Make.sh selection_${channel}_allyears.cc
exe="selection_${channel}_allyears.exe"
mv ../${INsample}.root ./

##############./$exe $inpath/infile.root $outpath/outfile.root sample name year

./$exe "./${INsample}.root" "../${sample}.root" $sample $name $year
