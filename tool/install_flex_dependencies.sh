#!/bin/sh

inexor_dir="`dirname "$0"`"
flex_dir="`realpath "${inexor_dir}/../flex"`"

cd $flex_dir
npm install
cd -
