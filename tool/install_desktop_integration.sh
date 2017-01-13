#!/bin/sh

tool_dir="`dirname "$0"`"
inexor_dir="`realpath "${tool_dir}/.."`"
flex_path="`realpath "${inexor_dir}/flex/inexor"`"

cp ${inexor_dir}/dist/linux/inexor.desktop /tmp
sed -i -- "s+\${flex}+${flex_path}+g" /tmp/inexor.desktop
wget https://raw.githubusercontent.com/inexor-game/artwork/master/logo/logo_thick.svg -O /tmp/inexor.svg
sudo cp /tmp/inexor.svg /usr/share/pixmaps

sudo xdg-desktop-menu install --novendor /tmp/inexor.desktop
sudo xdg-desktop-menu forceupdate
