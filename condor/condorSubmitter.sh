channel=$1
year=$2
INsample=$3
sample=$4
name=$5
disk=$6

submitDir="submit/${sample}"
mkdir -p "${submitDir}"

srcDir="/afs/hep.wisc.edu/home/htsoi/selection/CMSSW_9_4_0/src/inputs_forCondor"

NN="/hdfs/store/user/htsoi/NN/NN_${channel}${year}"

in_root="/hdfs/store/user/htsoi/haabbtt_rerunBtag_selection/haabbtt_${channel}${year}_rerunBtag/${INsample}.root"

cat > "job_${channel}${year}${sample}.sub" << EOF
executable = do_selection.sh
arguments = ${channel} ${year} ${INsample} ${sample} ${name}
log = ${submitDir}/log.log
output = ${submitDir}/output.txt
error = ${submitDir}/error.txt
transfer_input_files = ${srcDir},${NN},${in_root}
requestdisk = ${disk}
requestmemory = 800M
queue
EOF

condor_submit job_${channel}${year}${sample}.sub
