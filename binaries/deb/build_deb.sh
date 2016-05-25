#!/bin/bash

if [ ! -f build/libsoter.a ];
then
    echo "do make before"
    exit 0
fi

ARCH=`arch`
if [ "$ARCH" == "x86_64" ]
then
    ARCH=amd64
fi
PACKAGE=libthemis-dev_0.9.3_$ARCH
PACKAGE_DIR=build/$PACKAGE

mkdir -p $PACKAGE_DIR/DEBIAN/
mkdir -p $PACKAGE_DIR/usr/include/soter
mkdir -p $PACKAGE_DIR/usr/include/themis
mkdir -p $PACKAGE_DIR/usr/lib



echo "Package: libthemis-dev
Version: 0.9.3-1
Maintainer: CossackLabs LTD <dev@cossacklabs.com> Package: libthemis-dev
Architecture: $ARCH
Section: libdevel
Description: Data security library for network communication and data storage.
 Themis is a data security library, providing users with high-quality security
 services for secure messaging of any kinds and flexible data storage. Themis
 is aimed at modern developers, with high level OOP wrappers for Ruby, Python,
 PHP, Java / Android and iOS / OSX. It is designed with ease of use in mind,
 high security and cross-platform availability.
Depends: libssl-dev
Priority: optional
Origin: http://cossacklabs.com
X-Source: https://github.com/cossacklabs/themis/archive/0.9.3.tar.gz" >$PACKAGE_DIR/DEBIAN/control

#echo "Format: http://dep.debian.net/deps/dep5
#Upstream-Name: themis
#Source: https://github.com/cossacklabs/themis/archive/0.9.3.tar.gz
#
#
#Files: *
#Copyright: 2015-2016 Cossack Labs Limited. All rights reserved.
#License: Limited Use Software License Agreement
# Licensed under the Apache License, Version 2.0 (the \"License\");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an \"AS IS\" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License." >$PACKAGE_DIR/DEBIAN/copyright

cd src/soter && find . -name \*.h -exec cp --parents {} ../../$PACKAGE_DIR/usr/include/soter \; && cd - >/dev/null
cd src/themis && find . -name \*.h -exec cp --parents {} ../../$PACKAGE_DIR/usr/include/themis \; && cd - >/dev/null

cp build/*.a $PACKAGE_DIR/usr/lib/
cp build/*.so $PACKAGE_DIR/usr/lib/

cd $PACKAGE_DIR/usr/lib/ && find . -name \*.so -exec strip -o {} {} \; && cd - >/dev/null

cd $PACKAGE_DIR && md5deep -r -l usr > DEBIAN/md5sums && cd - >/dev/null

cd build && fakeroot dpkg-deb --build $PACKAGE && cd - >/dev/null
