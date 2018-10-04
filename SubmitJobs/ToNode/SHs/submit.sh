#!/bin/sh      

FILELIST="/storage/gpfs_data/dampe/users/ecatanzani/MyRepos/DAMPE/Salomon/SubmitJobs/ToNode/ExeSW/full_SBI_list.txt"
#FILELIST="/storage/gpfs_data/dampe/users/ecatanzani/MyRepos/DAMPE/Salomon/SubmitJobs/ToNode/ExeSW/shortList.txt"
BATCH=500

compute_free() {
    FREE=$MAXPEND
    compute_jobs
    let FREE-=$JOBS
}

compute_jobs() {
    JOBS=`qstat $QUEUE 2>&1 | egrep "WAIT|RUN" | wc -l`
}

compute_maxpend() {
    THRESHOLD_FILE=".THRESHOLD_PENDING"
    SHARPNESS=10
    echo "1000" > $THRESHOLD_FILE 
    MAXPEND=1000
    MAXPENDL=$MAXPEND
    MAXPENDDEC=$MAXPEND
    let MAXPENDDEC/=$SHARPNESS
    let MAXPENDL-=MAXPENDDEC
}

compute_maxpend

SUBMITTED=0
compute_free
compute_jobs

########## Checking SEED file existance

SEED_FILE=1
SEED_PATH=`pwd`
SEED_PATH="${SEED_PATH}/../seeds.txt"
FILE_RAW=0
if [ ! -f ${SEED_PATH} ]; then
    SEED_FILE=0
    touch "${SEED_PATH}"
fi

#######################################

files=""
nfiles=0

while read FILE
  do
    if [[ $SUBMITTED -gt $FREE ]]; then
        while [ $JOBS -gt $MAXPENDL ]; do                                # MAXPENDL (MAXPEND-20%) to avoid to "release" the 'wait' just for one event
            echo "$JOBS job waiting..."
            sleep 10
            compute_jobs
            compute_maxpend
        done
        SUBMITTED=0
        compute_free
        echo "s=$SUBMITTED l=$FREE"
    fi
    files="$files $FILE"
    let nfiles+=1
    if [[ $nfiles -ge $BATCH ]]; then
        echo "Launching $I ..."
        let SUBMITTED+=1

        if [[ SEED_FILE -eq 1 ]]; then
            FILE_RAW=$((FILE_RAW + 1))
            SEED=$(sed "${FILE_RAW}q;d" ${SEED_PATH})
        else
            SEED="$RANDOM"
            cat <<< "$SEED" >> "$SEED_PATH"
        fi

        ./submit_one_job.sh $files $SEED
        files=""
        nfiles=0
    fi
done <${FILELIST}

#launch last batch

echo $nfiles
if [[ $nfiles -ge 1 ]]; then

    if [[ SEED_FILE -eq 1 ]]; then
        FILE_RAW=$((FILE_RAW + 1))
        SEED=$(sed "${FILE_RAW}q;d" ${SEED_PATH})
    else
        SEED="$RANDOM"
        cat <<< "$SEED" >> "$SEED_PATH"
    fi

    ./submit_one_job.sh $files $SEED
fi
