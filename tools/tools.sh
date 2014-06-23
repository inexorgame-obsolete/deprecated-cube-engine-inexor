#! /bin/sh

repo_type() {
  local git svn r=0 e=""

  test -d "$1/".git && git=1
  test -d "$1/".svn && svn=1

  if test -n "$git" -a -n "$svn"; then
    r=101
    e="Confusing. Found both git and svn dir!"
  elif test -n "$git"; then
    echo git
  elif test "$svn"; then
    echo svn
  else
    r=102
    e="Confusing. Found neither git nor svn dir!"
  fi

  test "$e" && (echo >&2 "$e -- $1"; return "$r")
}

repo_up_git() {
  cd "$1"
  git remote update && git reset --hard origin/master
  cd -
}
repo_up_svn() {
  cd "$1"
  svn up
  cd -
}

repo_clone_git() {
  git clone "$2" "$1" --depth 1
}
repo_clone_svn() {
  svn co "$2" "$1"
}

repo() {
  local cmd="$2" path="$3" type="$1"
  shift; shift; shift

  test "$type" = "xxx" && type="`repo_type "$path"`"

  repo_"$cmd"_"$type" "$path" "$@"
}

github_fetch() {
  local notouch="$3 exists but is not a repo. Not touching."
	if test -d "$3"; then
    test -z "$NOUPGIT" && repo xxx up "$3"
  elif test -e "$3"; then
    echo >&2 "$notouch"
  else
    # Not existing; check out
    url="https://github.com/$2"
    repo svn clone "$3" "$url/trunk" || repo git clone "$3" "$url"
  fi

}

# TODO: Support Win? Mac?
jobno() {
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

  echo >2 "$s Compiling using $j jobs."
  echo "$j"
  return 0
}

"$1" "$@"
