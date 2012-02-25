#!/bin/sh

CODE_DIR=code
PROJ_DIR=.
AUTOMAKE_DIR=automake

cp -r $PROJ_DIR $1/MAPIL
cd $1/MAPIL
cp $AUTOMAKE_DIR/Makefile.am $CODE_DIR/Makefile.am
cp $AUTOMAKE_DIR/configure.ac $CODE_DIR/configure.ac
cp $AUTOMAKE_DIR/Include/Makefile.am $CODE_DIR/Include/Makefile.am
cp -r $AUTOMAKE_DIR/Lib $CODE_DIR/Lib
cd code
autoheader
aclocal
automake --add-missing --copy
autoconf
cd ..
./make_doc.sh release
mv code mapil
tar zcvf mapil.tar.gz mapil
