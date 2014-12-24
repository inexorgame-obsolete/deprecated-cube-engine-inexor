#!/bin/bash

# Do globbing case-insensitively; Stop on error

shopt -s nocaseglob
set -e

# Declare some Platform specific settings

declare -A PacUp
declare -A Pkg
declare -A Submodules

PacUp[arch]="pacman -S --needed"
PacUp[debian]="apt-get install"

Pkg[debian]="cmake build-essential zlib1g-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl1.2-dev"
Pkg[arch]="cmake base-devel sdl sdl_image sdl_mixer glu"

Pkg[eclipse_arch]="eclipse eclipse-cdt"
Pkg[eclipse_debian]="eclipse-egit eclipse eclipse-cdt"

Pkg[codeblocks_arch]="codeblocks"
Pkg[codeblocks_debian]="codeblocks codeblocks-contrib"

Submodules[arch]="src/libraries/enet"
Submodules[debian]="src/libraries/enet"
Submodules[darwin]="src/libraries/enet ../src/platform_osx"
Submodules[mingw]="src/libraries/enet ../src/platform_windows"
Submodules[unknown]="src/libraries/enet ../src/platform_windows ../src/platform_osx"

declare -A Targets

Targets[arch]="eclipse codeblocks compile"
Targets[debian]="eclipse codeblocks compile"
Targets[darwin]="xcode compile codeblocks eclipse"
Targets[mingw]="eclipse codeblocks compile vstudio12 vstudio11 vstudo10 vstudio9 vstudio8 vstudio7 vstudio6"
Targets[unknows]="eclipse codeblocks compile vstudio12 vstudio11 vstudio10 vstudio9 vstudio8 vstudio7 vstudio6"

declare -A Generators

Generators[compile_arch]="Unix Makefiles"
Generators[compile_debian]="Unix Makefiles"
Generators[compile_darwin]="Unix Makefiles"
Generators[compile_mingw]="MinGW Makefiles"
Generators[compile_unkwonw]="Unix Makefiles"

Generators[eclipse_arch]="Eclipse CDT4 - Unix Makefiles"
Generators[eclipse_debian]="Eclipse CDT4 - Unix Makefiles"
Generators[eclipse_darwin]="Eclipse CDT4 - Unix Makefiles"
Generators[eclipse_mingw]="Eclipse CDT4 - MinGW Makefiles"
Generators[eclipse_unkwonw]="Eclipse CDT4 - Unix Makefiles"

Generators[codeblocks_arch]="Eclipse CDT4 - Unix Makefiles"
Generators[codeblocks_debian]="Eclipse CDT4 - Unix Makefiles"
Generators[codeblocks_darwin]="Eclipse CDT4 - Unix Makefiles"
Generators[codeblocks_mingw]="Eclipse CDT4 - MinGW Makefiles"
Generators[codeblocks_unkwonw]="Eclipse CDT4 - Unix Makefiles"

Generators[xcode-darwin]="Xcode"

Generators[vstudio12-mingw]="Visual Studio 12 2013"
Generators[vstudio11-mingw]="Visual Studio 11 2012"
Generators[vstudio10-mingw]="Visual Studio 10 2010"
Generators[vstudio9-mingw]="Visual Studio 9 2008"
Generators[vstudio8-mingw]="Visual Studio 8 2005"
Generators[vstudio6-mingw]="Visual Studio 6"

# FUNCTIONS

# Newline character
CR="
"

# We _need_ tput to work on stderr. Otherwise it will fuck
# using STDOUT for stuff
__tput="`which tput`"
tput() {
  test -n "$__tput" || return
  "$__tput" "$@" >&2
}

# Print something to stderr in bold with the color defined in $0
# You can use printf  with `ECHO=printf RGB fnord`
RGB() {
  test -n "$ECHO" || local ECHO=echo

  tput bold
  tput setaf "$1"
  shift
  "$ECHO" >&2 "$@"
  tput setaf 7
  tput sgr0
}

# Echo for debug output
dbg() {
  RGB 5 "# $@"
}

# Ask the user a yes/no question.
# exit status is successful if yes, >0 otherwise
# $1 – The question
ask() {
  RGB 11 "$@"
  while true; do
    ECHO=printf RGB 6 "[ yes, no ] > "
    read resp
    if [[ "$resp" == yes ]]; then
      return 0
    elif [[ "$resp" == no ]]; then
      return 1
    fi
  done
}

# Query the user for information.
# $1 – The text of the query
# ... - Any allowed answers
# If no answer white list is given, any answer is allowed
# The response of the user is printed to stdout
query() {
  local question="$1"
  shift

  local opts="$@"

  typeset -A V
  for k in "$@"; do V["$k"]="1"; done

  RGB 11 "$question"
  while true; do
    ECHO=printf RGB 6 "[ ${opts// /, } ] > "
    read resp
    if [[ "$@" == "" ]] || [[ "${V[$resp]}" != '' ]]; then
      echo "$resp"
      return
    fi
  done
}

# Echo an error message and exit with 23
err() {
  RGB 1 "$@"
  ask "Try to continue despite this?" || exit 23
}

# Execute a command printing it
ev() {
   RGB 2 "\$ $@"

  "$@"
}

# Change to a directory printing it
evcd() {
  RGB 2 "\$ cd $@"
  cd "$@"
}

# Do something as root
root() {
  if [[ "$ROOT_CACHE" != "" ]]; then
    eval "";
  elif [[ "`id -u`" == 0 ]]; then
    ROOT_CACHE=""
    dbg "Wow, we are already root."
  elif which sudo >/dev/null; then
    ROOT_CACHE=sudo
    dbg "Gaining root using sudo!"
  elif which su >/dev/null; then
    ROOT_CACHE=su
    dbg "Gaining root with su!"
  else
    err "Don't know how to get root! Nothing requiring root will be done!"
    ROOT_CACHE="null"
  fi

  RGB 5 "# $@"
  test "$ROOT_CACHE" != "null" && "$ROOT_CACHE" "$@"
}

# Detect how many cpus this system has
detect_cpus() {
  local j=0 s=""

  if test -n "$JOBS"; then
    s="$$JOBS variable found."
    j="$JOBS"
  elif test -e /proc/cpuinfo; then
    s="/proc/cpuinfo exists."
    j="`</proc/cpuinfo grep processor | wc -l`"
  else
    s="Could not determine number of cores"
    j="4"
  fi

  dbg "$s Compiling using $j jobs."
  CPUNO=4
}

# Detect which os we are on. Valid outputs are
# arch, debian, ubuntu, mingw and darwin
#
# The result is saved in $OS
detect_os() {
  # Already defined; skip
  test -n "$OS" && exit

  local uname="$(uname -a)"

  if [[ "$uname" =~ linux ]]; then
    if [[ -f /etc/debian_version ]]; then
      OS=debian
    elif [[ -f /etc/arch-release ]]; then
      OS=arch
    elif [[ -f /etc/debian_version ]]; then
      OS=debian
    else
      err "Could not detect Linux distribution. Define manually with os=arch|debian|ubuntu|darwin|mingw"
      OS="unknown"
    fi
  elif [[ "$uname" =~ darwin ]]; then
    OS=darwin
  elif [[ "$uname" =~ mingw ]]; then
    err "Could not detect operating system. Define manually with os=arch|debian|ubuntu|darwin|mingw"
    OS="unknown"
  fi

  dbg "Detected OS: $OS"
}

# Download a file using aria2c/wget/curl/manually.
# The files are usually stored under /tmp
# The path to the file that has been downloaded is printed
# to stdout.
download() {
  if test -n "$DOWNLOAD_CACHE"; then
    eval;
  elif which aria2c >/dev/null && false; then
    DOWNLOAD_CACHE="aria2c"
  elif which wget >/dev/null && false; then
    DOWNLOAD_CACHE="wget"
  elif which curl >/dev/null && false; then
    DOWNLOAD_CACHE="curl"
  else
    DOWNLOAD_CACHE="manual"
  fi

  evcd /tmp
  local f="$(readlink -f "`date +%s`-$(basename "$1")")"
  dbg "Downloading $1 to $f using $DOWNLOAD_CACHE"

  if [[ $DOWNLOAD_CACHE == aria2c ]]; then
    aria2c -o "$f" "$1"
  elif [[ $DOWNLOAD_CACHE == wget ]]; then
    wget -O "$f" "$1"
  elif [[ $DOWNLOAD_CACHE == curl ]]; then
    curl -o "$f" "$1"
  else
    f=""
    while true; do
      f="$(query "Don't know how to download a file on this system. Please download $1 yourself and insert the path below:")"
      test -e "$f" || true && break
    done
  fi

  echo "$f"
  evcd -
}

# The filter missing functions are all plattform specific
# versions of this: They take a space separated list of packages
# and drop every package from the list.
# The result is printed to stdout.
# This allows us to skip the package-installing step on systems
# that have all the dependencies already installed.
filter_missing_debian() {
  local l pkg state=next
  apt-cache policy $1 | while read l; do
    case "$state"  in
      'next')
        test "${1:0:1}" != " " || continue
        pkg="${1:0:-1}"
        state=in
        ;;
      'in')
        [[ "$l" =~ "Installed" ]] || continue
        state=next
        [[ "$l" =~ "(none)" ]] || printf "$pkg "
        ;;
    esac
  done
}
filter_missing_arch() {
  S="  $1  "

  # Explicitly filter base-devel
  if (which gcc && which make)>/dev/null; then
    S="${S/ base-devel / }"
  fi

  # Find all the packages that are already installed
  local d w
  d="$(
    pacman -Q $1 2>/dev/null | while read l; do
      for w in $l; do echo "$w"; break; done
    done
  )"

  # Drop those from S
  for w in $d; do
    S="${S/ $w / }"
  done

  # Now output all the values in the assoc array
  echo "$S"
}

# Installs the dependencies.
# $1 is the program to use
# $2 is the list of packages
depend() {
  local pkg="$(filter_missing_"$OS" "$1")"
  if test -n "${pkg// /}"; then
    root ${PacUp[$OS]} ${pkg} || true
  fi
}

# Fetch submodules
# $0 is the list of submodules
fetch_submodules() {
  for sm in ${1}; do
    ev git submodule init "$sm"
    ev git submodule update --recursive "$sm"
  done
}

# Takes the standard input, puts it in a box, prints on stderr.
# $1 – Color of the text (default=7)
# $2 – Color of the box (default=$1)
# $3 - Box character (default="#")
boxxy() {
  # ARGS
  local ct="$1" cb="$2" chr="$3"
  test -n "$ct"  || ct=7
  test -n "$cb"  || cb="$ct"
  test -n "$chr" || chr="#"

  # Read
  local i="" l="" buf="" width=0 # There's probably a better way
  while read l; do
    (( ${#l} > $width )) && width="${#l}"
    buf="$buf$l$CR"
  done

  # Top border
  tput setaf "$cb"
  printf "$CR$CR"
  for ((i=$width; i > -4; i-- )); do
    printf "$chr"
  done
  printf "$CR"
  # Body, top and bottom margin
  while read l; do
    # left border & margin
    printf "$chr "
    # text
    tput setaf "$ct"
    printf "$l"
    # padding
    tput setaf "$cb"
    for ((i=$width; i > ${#l}; i--)); do
      printf " "
    done
    # right margin & border
    printf " $chr$CR"
  done <<< "$CR$buf$CR"
  #  Bottom border
  for ((i=$width; i > -4; i-- )); do
    printf "$chr"
  done
  printf "$CR$CR"

  tput setaf 7
}

# Main Routines ############################################

installer() {
  clear
  boxxy 2 4 <<< "
    Hello. Let me introduce you to the inexor setup homunculus.

    The homunculus Will guide you through creating your initial development
    setup. She will work on debian and derivatives (e.g. Ubuntu),
    Arch Linux Mac OS X and MinGW.

    If your computer does not run one of these platforms, please
    reference https://github.com/inexor/code/wiki/Build
    on how to create the compilation setup manually. It's really easy.

    If you are using mingw, you will need to install git and
    cmake manually. Please consider using the install homunculus
    for windows. See https://github.com/inexor/code/wiki/Build.

    On linux and mac this homunculus possesses the ability to
    fetch and install some dependencies automatically. On mac
    some installers may be run, on linux the package manager
    is used.

    Installing the dependencies normally requires administrator
    privileges. In these cases you will be prompted for a password.
    Please respond with the password you use when logging on
    to your computer.

    This homunculus will always ask before installing other
    software. You can deny that, but there is a high probabilizy
    that the homunculus will not be able to finish the job then.

    In a few cases you will be asked to respond to a question,
    but not any answer is allowed. The questions always provide
    a list of which answers can be undestood:

      What is your spirit animal?
      [mote/tiger/fast food] >

    In this case you can answer mote, tiger of fast food.
  "
  dbg "Let's go!"

  # Basic system detection

  detect_os
  detect_cpus

  targ="$(query "What do you want to do? Compile it, create a project for your IDE? Type one of the answers bleow!" ${Targets[$OS]} )"

  # Fetch missing dependencies

  k="${targ}_${OS}"
  dbg "NEED ${Pkg[$OS]} ($OS) and ${Pkg[$k]} ($k)"
  depend "${Pkg[$OS]}"
  depend "${Pkg[$k]}"

  if [[ "$OS" == "darwin" ]]; then
    if which git >/dev/null                                \
        || ask "Git could not be found on your system. Do you want to install it?"\
        || true && false; then
      f="$(download 'https://code.google.com/p/git-osx-installer/downloads/detail?name=git-1.7.10.3-intel-universal-snow-leopard.dmg')"
      open "$f"
      query "Please install the application we just downloaded. Press enter as soon as you are ready."
    fi

    if which cmake >/dev/null                              \
        || ask "Cmake could not be found on your system. Do you want to install it?"\
        || true && false; then
      f="$(download 'http://www.cmake.org/files/v3.0/cmake-3.0.0-Darwin64-universal.dmg')"
      open "$f"
      query "Please install the application we just downloaded. Press enter as soon as you are ready."
    fi
  fi

  repo="${HOME}/inexor-`date +%s`"
  dbg "Inexor will be put into $repo"
  git clone "https://github.com/inexor/code.git" "$repo"

  evcd "$repo"

  fetch_submodules "${Submodules[$OS]}"

  test -n "$build" || build="${repo}/$targ/"

  dbg "Compiling into ${build}"

  if [[ -d "$build" ]] && ask "Going to remove $build"; then
    rm -Rv "$build"
  fi


  ev mkdir -p "${build}"
  evcd "${build}"
  k="${targ}_${OS}"
  ev cmake .. -G "${Generators[$k]}"
  [[ "$targ" == "compile" ]] && ev make -j"$CPUNO" || true

  boxxy 2 4 <<< "
    There you go! Your binaries should be in:

    ${build}

    If you want to rerun this homunculus, too generate more
    projects for example, just run ${repo}/tool/clickme.command
  "
}

# Where are we

repo="$(git rev-parse --show-toplevel)"

# Main entry

if test -v "$@"; then
  installer
else
  "$@"
fi
