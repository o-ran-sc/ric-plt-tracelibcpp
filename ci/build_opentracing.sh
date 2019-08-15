#!/bin/bash
#
# Copyright (c) 2019 AT&T Intellectual Property.
# Copyright (c) 2018-2019 Nokia.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
set -e

REL=1.5.0

wget https://github.com/opentracing/opentracing-cpp/archive/v$REL.tar.gz -O opentracing-cpp-$REL.tar.gz
tar zxf opentracing-cpp-$REL.tar.gz
cd opentracing-cpp-$REL

cmake .
make package
cpack -G RPM -D CPACK_RPM_FILE_NAME=RPM-DEFAULT
alien opentracing-cpp-$REL-1.x86_64.rpm --keep-version
mv *.rpm *.deb ..
