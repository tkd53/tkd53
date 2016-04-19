#!/bin/bash

BASEDIR=$(cd $(dirname $0)/../; pwd)

cd $BASEDIR/src/dictionary && make
cd $BASEDIR/src/converter && make
cd $BASEDIR/src/engine && make
cd $BASEDIR/src/server && make
