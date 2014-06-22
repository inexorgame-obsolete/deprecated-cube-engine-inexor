JOBS=$(shell sh tools/tools.sh jobno)

BUILDDIR=./build
DATADIR=./data
BINDIR=./bin/$(OUT)
OUTDIR=$(BUILDDIR)/target/$(OUT)

SRC_REF=./src/
ENET_REF=$(BUILDDIR)/enet
SDEPS_REF=$(BUILDDIR)/sdeps

OUT_SRC=$(OUTDIR)/src
OUT_ENET=$(OUT_SRC)/enet

ENV=

ifdef OSXCROSS
override ENV=$(shell ("$(OSXCROSS)"/bin/osxcross-conf && "$(OSXCROSS)"/bin/osxcross-env) | sed 's/^export //' | tr '\n' ' ')
endif

# Default entry ############################################

help:
	cat readme.md

# Distributions ############################################

native:
	make cpexe OUT=native

linux32:
	make cpexe OUT=linux32 PLATFORM=Linux-32

linux64:
	make cpexe OUT=linux64 PLATFORM=Linux-64

win32:
	make cpexe OUT=win32 PLATFORM=MINGW-CROSS EXE_SUFF=.exe

win64:
	make cpexe OUT=win64 PLATFORM=MINGW-CROSS-64 EXE_SUFF=.exe

osx32:
	make cpexe OUT=osx32 PLATFORM=DARWIN-CROSS $(ENV)

osx64:
	make cpexe OUT=osx64 PLATFORM=DARWIN-CROSS-64 $(ENV)

all-win: win32 win64
all-osx: osx32 osx64
all-linux: linux32 linux64
all-os: all-win all-osx all-linux

# Download #################################################

fetch-enet: build-dir
	sh tools/tools.sh github_fetch lsalzman/enet "$(ENET_REF)"

fetch-static-deps: build-dir
	sh tools/tools.sh github_fetch sauerbraten-fork/sauerbraten-fork-build-deps "$(SDEPS_REF)"

fetch-sauerbraten-fork-data: data-dir
	sh tools/tools.sh github_fetch sauerbraten-fork/sauerbraten-fork-data "$(DATADIR)"/sauerbraten-fork-data

fetch-sauerbraten: data-dir
	sh tools/tools.sh github_fetch sauerbraten-fork/sauerbraten "$(DATADIR)"/sauerbraten

fetch-data: fetch-sauerbraten-fork-data fetch-sauerbraten

# Dependency Management ####################################

install-debian-packets:
	apt-get install libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl1.2-dev libenet-dev libsdl-image1.2 libsdl-mixer1.2 g++ g++-4.4 autoconf2.13 libtool

# File Management ##########################################

build-dir:
	mkdir -p "$(BUILDDIR)"

data-dir:
	mkdir -p "$(DATADIR)"

out-dir:
	mkdir -p "$(OUTDIR)"

bin-dir:
	mkdir -p "$(BINDIR)"

link-enet: fetch-enet link-src
	cp -Rl "$(ENET_REF)" "$(OUT_ENET)"

link-static-deps: fetch-static-deps link-src
	test -d "$(SDEPS_REF)"/"$(OUT)" && cp -Rl "$(SDEPS_REF)"/"$(OUT)"/* "$(OUT_SRC)" || true

link-src: out-dir
	cp -Rl "$(SRC_REF)" "$(OUT_SRC)"

clean:
	rm -Rv "$(BUILDDIR)" "$(BINDIR)"

# Compilation ##############################################

compile: link-src link-enet link-static-deps
	$(MAKE) -C $(OUT_SRC) -j $(JOBS)

cpexe: compile bin-dir
	cp "$(OUT_SRC)/"*client"$(EXE_SUFF)" "$(BINDIR)/client$(EXE_SUFF)" -rv
	cp "$(OUT_SRC)/"*server"$(EXE_SUFF)" "$(BINDIR)/server$(EXE_SUFF)" -rv
	cp "$(OUT_SRC)/"*master"$(EXE_SUFF)" "$(BINDIR)/master$(EXE_SUFF)" -rv || true
	test -d "$(SDEPS_REF)"/"$(OUT)"/bin && cp -Rl "$(SDEPS_REF)"/"$(OUT)"/bin/* "$(BINDIR)" || true
	cp -R "$(OUT_SRC)"/enet/.libs/* "$(BINDIR)" || true

