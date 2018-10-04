#!/bin/sh

run_exec () {
FILELIST=$1
echo $FILELIST
CMD="$EXEC $FILELIST"; echo ${CMD}; ${CMD};
}

echo "`whoami` @ `hostname` : `pwd`"

CMD="source $SETVAR"; echo ${CMD}; ${CMD};

echo " ------------------------ "
echo " ---------- ENVS -------- "
echo " ------------------------ "
echo ""
env
echo ""
echo " ------------------------ "
echo " ------------------------ "
echo ""

HOME=`pwd`
UNIQUE="$$_$RANDOM"
SANDBOX=$HOME/../SandBox/$UNIQUE
while [[ -d $SANDBOX ]]; do
UNIQUE="$$_$RANDOM"
SANDBOX=$HOME/../SandBox/$UNIQUE
echo "Searching for a free SandBox dir!"
done
mkdir -vp $SANDBOX
cd $SANDBOX
pwd

FILES="$FILES"
cat <<< $FILES >> ./lista.dat
run_exec lista.dat
rm -fv lista.dat

ls -altrh
mv -v *.root *.txt ${OUTDIR}
rm -rfv "$SANDBOX"
