#!/bin/bash -f

ROOTVER=5.34-10
kernel=`uname --kernel-release`
arch=''
if [[ $kernel == *el6.x86_64 ]]; then
    arch=Linux26SL6_x86_64_gcc447
elif [[ $kernel == *el6.i686 ]]; then
    arch=Linux26SL6_i386_gcc446
elif [[ $kernel == *el5 ]]; then
    arch=Linux26SL5_i386_gcc412
else
    echo Unknown system `uname -a`
    exit
fi

ROOTSYS=/afs/slac.stanford.edu/g/babar/package/root/${ROOTVER}/${arch}
PYTHONPATH=${ROOTSYS}/lib:${PYTHONPATH}
LD_LIBRARY_PATH=.:/usr/lib:${ROOTSYS}/lib

export ROOTSYS
echo ROOTSYS=${ROOTSYS}
export LD_LIBRARY_PATH
#echo LD_LIBRARY_PATH=${LD_LIBRARY_PATH}
export PYTHONPATH
#echo PYTHONPATH=${PYTHONPATH}
PYTHONUNBUFFERED=1
export PYTHONUNBUFFERED
export PATH=${PATH}:${ROOTSYS}/bin
