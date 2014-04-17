#!/bin/csh

set ROOTVER=5.34-10
set kernel=`uname --kernel-release`

if ( $kernel =~ *el6.x86_64 ) then
    set arch=Linux26SL6_x86_64_gcc447
else if ( $kernel =~ *el6.i686 ) then
    set arch=Linux26SL6_i386_gcc446
else if ( $kernel =~ *el5 ) then
    set arch=Linux26SL5_i386_gcc412
else
    echo Unknown system `uname -a`
    exit
endif

setenv ROOTSYS /afs/slac.stanford.edu/g/babar/package/root/${ROOTVER}/${arch}
setenv PYTHONPATH ${ROOTSYS}/lib:${PYTHONPATH}
setenv LD_LIBRARY_PATH .:/usr/lib:${ROOTSYS}/lib

echo ROOTSYS=${ROOTSYS}
#echo LD_LIBRARY_PATH=${LD_LIBRARY_PATH}
#echo PYTHONPATH=${PYTHONPATH}
setenv PYTHONUNBUFFERED 1

setenv PATH ${PATH}:${ROOTSYS}/bin
