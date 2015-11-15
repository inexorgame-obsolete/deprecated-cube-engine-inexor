CXX=clang++
CXXFLAGS=-std=c++11 -O2 -Wall -Wextra -Wpedantic -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -pthread
LDFLAGS=-std=c++11 -pthread

libs = -lclangRewrite -lclangTooling -llldb

objs = tree_gluecode_gen.o
exe = tree_gluecode_gen

inexor_basedir = ../../..

sdl_cflags = $(shell sdl2-config --cflags)

.PHONY: clean run

run: $(exe)
	./$(exe) $(inexor_basedir)/inexor/{fpsgame,engine}/*.cpp -- -D_FILE_OFFSET_BITS=64 -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -fomit-frame-pointer -fno-strict-aliasing -fsigned-char -pipe -Wall -Wno-switch -Wno-deprecated-declarations -Wno-missing-braces -fdiagnostics-show-option  -m64 -march=x86-64 -fno-threadsafe-statics -std=c++14  -O0 -g -D_DEBUG -I/usr/lib/clang/3.7.0/include/ -I"$(inexor_basedir)" -I$(inexor_basedir)/inexor/platform/include/linux-x86_64 -I"$(inexor_basedir)"/inexor/platform/include/linux -I"$(inexor_basedir)"/code/inexor/platform/include/all $(sdl_cflags)

$(exe): $(objs)
	$(CXX) $(LDFLAGS) -o "$(exe)" $(objs) $(libs)

clean:
	rm -vf $(objs) "$(exe)"
