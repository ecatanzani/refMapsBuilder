#!/bin/sh

export USER="$(whoami)"

#ENV="${HOME}/.bash_profile"
#if [[ ! -f $ENV ]]; then echo "$ENV does not exist" >&2; exit 1; fi

ENV_FILE=".bash_profile"
ENV_PATH="${HOME}/${ENV_FILE}"
if [[ ! -f ${ENV_PATH} ]]; then echo "$ENV_PATH does not exist" >&2; exit 1; fi

export WORKDIR="/storage/gpfs_data/dampe/users/ecatanzani/MyRepos/DAMPE/Salomon/SubmitJobs/Local"
if [[ ! -d $WORKDIR ]]; then echo "$WORKDIR does not exist" >&2; exit 1; fi

export EXEC="${WORKDIR}/ExeSW/Release/JSalomon"
if [[ ! -e $EXEC ]]; then echo "$EXEC does not exist" >&2 ; exit 1; fi

export SUBMITDIR="${WORKDIR}/SHs"
if [[ ! -d $SUBMITDIR ]]; then echo "$SUBMITDIR does not exist" >&2; exit 1; fi

export OUTDIR="${WORKDIR}/JobResults"
if [[ ! -d $OUTDIR ]]; then mkdir -pv ${OUTDIR}
else echo "output dir will be $OUTDIR"; fi

export FILES=$@

echo "Copying ENVIRONMENT variable to storage dierctory: "
export SETVAR=${WORKDIR}/
cp -v ${ENV_PATH} ${SETVAR}
SETVAR+=$ENV_FILE

sh ./template.sh
