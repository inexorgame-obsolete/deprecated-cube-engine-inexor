#!/bin/sh

inexor_dir="`dirname "$0"`"
flex_path="`realpath "${inexor_dir}/../flex/inexor"`"
echo "${flex_path}"

sudo cp dist/linux/inexor.desktop /usr/share/applications
sudo sed -i -- "s+flex+${flex_path}+g" /usr/share/applications/inexor.desktop
wget https://raw.githubusercontent.com/inexor-game/artwork/master/logo/logo_thick.svg -O /tmp/inexor.svg
sudo cp /tmp/inexor.svg /usr/share/pixmaps
