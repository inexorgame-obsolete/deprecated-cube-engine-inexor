#pragma once

#include "inexor/util/Observe.hpp"

template<typename T> using SharedVar = inexor::util::Observe<T>;

#define INEXOR_CUSTOM_ANNOTATION(...) __attribute__((annotate( #__VA_ARGS__ )))

#ifdef __REFLECTION_PASS__
#define INEXOR_SHARED_TREE(...) INEXOR_CUSTOM_ANNOTATION(SharedTree=__VA_ARGS__)
#else
#define INEXOR_SHARED_TREE(...)
#endif

