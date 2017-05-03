#pragma once
// Tiger Hash implementation, see crpyto.cpp
// AVOID USE!

#include "inexor/shared/cube_types.hpp"

/// Get the session hash.
/// Formats the sessionid, the cn and a password string together to give a session hash.
extern void hashpassword(int cn, int sessionid, const char *pwd, char *result, int maxlen = MAXSTRLEN);

/// Checks if the given session hash results from our pw or not.
/// It answers: is our hash valid for our password?
extern bool checkpassword(int cn, int sessionid, const char *wanted, const char *given);

