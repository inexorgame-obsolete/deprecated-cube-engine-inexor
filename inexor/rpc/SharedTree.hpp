#ifndef INEXOR_RPC_SHARED_VAR_HEADER
#define INEXOR_RPC_SHARED_VAR_HEADER

#include "inexor/util/Observe.hpp"

template<typename T> using SharedVar = inexor::util::Observe<T>;

#define INEXOR_CUSTOM_ANNOTATION(...) __attribute__((annotate( #__VA_ARGS__ )))
#define INEXOR_SHARED_TREE(...) INEXOR_CUSTOM_ANNOTATION(SharedTree=__VA_ARGS__)

#endif
