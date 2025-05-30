#!/bin/bash
#
# Automate generation a new release
#

. ./VERSION

version=${PACKAGE_MAJOR}.${PACKAGE_MINOR}.${PACKAGE_REVISION}
date=`date +"%-d %B %Y"`

echo "Cleaning up"
make realclean

echo "Updating CHANGES"
sed -e "s/${version}.*/${version} (${date})/" doc/CHANGES > doc/CHANGES.tmp && \
	mv doc/CHANGES.tmp doc/CHANGES

echo "Commiting CHANGES update to git"
git commit -s -a -m "${version} release"

echo "Tagging git repository"
git tag -s -a -m "${version} release" v${version}

echo "Making source tarball"
make dist

echo "Sign the source tarball"
gpg --detach-sign xfstests-${version}.tar.gz

echo "Done.  Please remember to push out tags using \"git push --tags\""
