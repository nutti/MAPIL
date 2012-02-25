#!/bin/sh

CODE_DIR=code
PROJ_DIR=.
AUTOMAKE_DIR=automake

#if [ -d $1 ]; then
#	echo "Error : $1 already exists."
#	exit 1
#fi

mkdir -p $1/MAPIL
cp -r $PROJ_DIR/automake $1/MAPIL/automake
cp -r $PROJ_DIR/code $1/MAPIL/code
cp -r $PROJ_DIR/doxygen $1/MAPIL/doxygen
cp -r $PROJ_DIR/uml $1/MAPIL/uml
cp $PROJ_DIR/compile_test.sh $1/MAPIL/compile_test.sh
cp $PROJ_DIR/make_doc.sh $1/MAPIL/make_doc.sh
cp $PROJ_DIR/make_release.sh $1/MAPIL/make_release.sh
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
./configure
make
