#!/bin/sh

CD=cd
DOXYGEN=doxygen
DOXYGEN_CONF_DIR=doxygen
DOXYGEN_RELEASE_CONF_FILE=doc_release.conf
DOXYGEN_DEV_CONF_FILE=doc_dev.conf

CURRENT_DIR=`pwd`

case $1 in
	release)
		$CD $DOXYGEN_CONF_DIR
		sed -e "s|{OUTPUT_DIR_ENTER_HERE}|\"$2\"|" $DOXYGEN_RELEASE_CONF_FILE > $DOXYGEN_RELEASE_CONF_FILE.tmp.1
		sed -e "s|{STRIP_PATH_ENTER_HERE}|\"$CURRENT_DIR\"|" $DOXYGEN_RELEASE_CONF_FILE.tmp.1 > $DOXYGEN_RELEASE_CONF_FILE.tmp.2
		$DOXYGEN $DOXYGEN_RELEASE_CONF_FILE.tmp.2
		rm $DOXYGEN_RELEASE_CONF_FILE.tmp.1
		rm $DOXYGEN_RELEASE_CONF_FILE.tmp.2
	;;
	dev)
		$CD $DOXYGEN_CONF_DIR
		sed -e "s|{OUTPUT_DIR_ENTER_HERE}|\"$2\"|" $DOXYGEN_DEV_CONF_FILE > $DOXYGEN_DEV_CONF_FILE.tmp.1
		sed -e "s|{STRIP_PATH_ENTER_HERE}|\"$CURRENT_DIR\"|" $DOXYGEN_DEV_CONF_FILE.tmp.1 > $DOXYGEN_DEV_CONF_FILE.tmp.2
		$DOXYGEN $DOXYGEN_DEV_CONF_FILE.tmp.2
		rm $DOXYGEN_DEV_CONF_FILE.tmp.1
		rm $DOXYGEN_DEV_CONF_FILE.tmp.2
	;;
	*)
		echo "Error : Usage isn't correct."
		echo "Usage : ./make_doc.sh {release|dev} dir"
		exit 1
	;;
esac
