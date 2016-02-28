Summary: Inexor is a game based on Cube 2: Sauerbraten.
Name: inexor
Version: 0.5
Release: 1
Copyright: zlib
Group: Amusements/Games
Source: https://github.com/inexor-game/code/archive/0.5.0-alpha.tar.gz
BuildRoot: /tmp/%{name}-buildroot
BuildRequires:  Mesa-devel
BuildRequires:  fdupes
BuildRequires:  gcc-c++
BuildRequires:  pkg-config
BuildRequires:  pkgconfig(SDL2_image)
BuildRequires:  pkgconfig(SDL2_mixer)
BuildRequires:  pkgconfig(zlib)
BuildRequires:  pkgconfig(protobuf-c)
BuildRequires:  cmake
BuildRequires:  boost-devel

%description
Inexor is a fork of the open-source First-Person-Shooter Cube 2: Sauerbraten, a fast-paced shooting game featuring an ingame map editor.
In contrast to Sauerbraten, Inexor adds a lot of functionality and strives to stay open to improvements and suggestions.
The goal of this project is to be more flexible and create an environment where development is easy, fast and where creativity can prosper.

%setup -b
%build
mkdir build
cd build
cmake ..
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/inexor

install -s -m 755 inexor $RPM_BUILD_ROOT/usr/bin/inexor



%changelog
* delta1: Add the required stuff
- Add some more stuff required for build and also fix a wrong thing
- Finish up (:P)
