#! /bin/sh

github_fetch() {
  notouch="$3 exists but is not a SVN repo. Not touching."
	if cd "$3"; then
    if test -d .svn; then
      if test -z "$NOUPGIT"; then
        svn up
      fi
    else
      echo >&2 "$notouch"
    fi
  elif test -e "$3"; then
    echo >&2 "$notouch"
  else
    # Not existing; check out
		svn co https://github.com/"$2"/trunk "$3"
  fi

}

# TODO: Support Win? Mac?
jobno() {
  j=0
  s=""

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
