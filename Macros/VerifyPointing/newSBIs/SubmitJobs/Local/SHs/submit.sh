#!/bin/sh      

FILELIST="/storage/gpfs_data/dampe/users/ecatanzani/MyRepos/DAMPE/Salomon/Macros/VerifyPointing/newSBIs/SubmitJobs/Local/ExeSW/shortList.txt"
BATCH=50

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
