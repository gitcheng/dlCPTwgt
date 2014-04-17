#!/bin/sh -f
source setup.sh
[[ ! -d bin ]] && mkdir bin
g++ -o bin/dlCPTwgt dlCPTwgt.cc `root-config --cflags --glibs`
