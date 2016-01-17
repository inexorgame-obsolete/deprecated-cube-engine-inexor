inexor_basedir = ../..

CXX=clang++
CXXFLAGS+=-std=c++14 -Wall -Wextra -Wpedantic -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -pthread -I"$(inexor_basedir)"
LDFLAGS+=-std=c++14 -pthread

ifdef DEBUG
  CFLAGS += -O0 -g
  CXXFLAGS += -O0 -g
	LDFLAGS += -O0 -g
else
  CFLAGS += -O2 -march=native -mtune=native
  CXXFLAGS += -O2 -march=native -mtune=native
	LDFLAGS += -O2
endif

libs = \
	-Wl,-Bstatic \
		-lclangRewrite \
		-lclangTooling \
		-lboost_program_options \
		-lboost_regex \
	-Wl,-Bdynamic \
		-llldb # TODO: Link statically

objs = $(shell \
	find \
	    -regextype posix-extended \
	    -iregex '^.*\.(cc|cpp|cxx|c)$$' \
		| grep -v './out/' \
		| sed -r 's@\.(cc|cpp|cxx|c)$$@.o@')

exe = gluegen

ifdef GDB
	run_exe = gdb --args ./$(exe)
else
	run_exe = ./$(exe)
endif

sdl_cflags = $(shell sdl2-config --cflags)

.PHONY: clean run



$(exe): $(objs)
	$(CXX) $(LDFLAGS) -o "$(exe)" $(objs) $(libs)

run: $(exe)
	mkdir -p ./out
	$(run_exe) \
		-H ./out/tree_adapter.hpp \
		-S ./out/tree_adapter.cpp \
		-P ./out/tree_definition.proto \
		-N inexor::tree \
				-- -D_FILE_OFFSET_BITS=64 -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -fomit-frame-pointer -fno-strict-aliasing -fsigned-char -pipe -Wall -Wno-switch -Wno-deprecated-declarations -Wno-missing-braces -fdiagnostics-show-option  -m64 -march=x86-64 -fno-threadsafe-statics -std=c++14  -O0 -g -D_DEBUG -I/usr/lib/clang/3.7.0/include/ -I"$(inexor_basedir)" -I$(inexor_basedir)/inexor/platform/include/linux-x86_64 -I"$(inexor_basedir)"/inexor/platform/include/linux -I"$(inexor_basedir)"/code/inexor/platform/include/all $(sdl_cflags) \
				-- $(inexor_basedir)/inexor/{fpsgame,engine}/*.cpp

clean:
	rm -vf $(objs) "$(exe)"
