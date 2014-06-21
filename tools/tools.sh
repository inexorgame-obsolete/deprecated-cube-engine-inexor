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

"$1" "$@"
