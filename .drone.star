# Use, modification, and distribution are
# subject to the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt)
#
# Copyright Rene Rivera 2020.

# For Drone CI we use the Starlark scripting language to reduce duplication.
# As the yaml syntax for Drone CI is rather limited.
#
#
globalenv={}
linuxglobalimage="cppalliance/droneubuntu1604:1"
windowsglobalimage="cppalliance/dronevs2019"

def main(ctx):
  return [
  linux_cxx("Job 0", "g++", packages="gcc-4.8 g++-4.8 clang", buildtype="boost", image=linuxglobalimage, environment={'CXXSTD': '-std=c++0x', 'DRONE_JOB_UUID': 'b6589fc6ab'}, globalenv=globalenv),
  osx_cxx("Job 1", "g++", packages="gcc-4.8 g++-4.8 clang", buildtype="boost", environment={'CXXSTD': '-std=c++0x', 'DRONE_JOB_OS_NAME': 'osx', 'DRONE_JOB_UUID': '356a192b79'}, globalenv=globalenv),
  ]

# from https://github.com/boostorg/boost-ci
load("@boost_ci//ci/drone/:functions.star", "linux_cxx","windows_cxx","osx_cxx","freebsd_cxx")
