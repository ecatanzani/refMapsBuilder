################ ROOT Environment ##################

source /opt/exp_software/dampe/externals/root/5-34-34/bin/thisroot.sh
source /opt/exp_software/dampe/setup/setup.sh

#####################################################
################ Directory Aliases ##################

alias PersonalDir='cd /storage/gpfs_data/dampe/users/ecatanzani'
alias DataDir='/storage/gpfs_data/dampe/data' 

#####################################################
################      My bin       ##################

export PATH=$HOME/bin:$PATH
export LD_LIBRARY_PATH=/home/DAMPE/ecatanzani/bin/boost_1_67_0/stage/lib/:$LD_LIBRARY_PATH

#####################################################
