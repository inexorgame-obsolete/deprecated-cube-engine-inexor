JOBS=$(shell </proc/cpuinfo grep "processor" | wc -l)

BUILDDIR=./build/
DATADIR=./data/
BINDIR=./bin/
OUTDIR=$(BUILDDIR)/$(OUT)

SRC_REF=./src/
ENET_REF=$(BUILDDIR)/enet/

OUT_SRC=$(OUTDIR)/src/
OUT_ENET=$(OUT_SRC)/enet/

# Default entry ############################################

help:
	cat readme.md

# Distributions ############################################

native:
	make cpexe OUT=native

linux:
	make cpexe OUT=linux PLATFORM=linux

win32:
	make cpexe OUT=win32 PLATFORM=MINGW-CROSS

win64:
	make cpexe OUT=win64 PLATFORM=MINGW-CROSS-64

all-win: win32 win64
all-os: all-win linux

# Download #################################################

fetch-enet: build-dir
	sh tools/tools.sh github_fetch lsalzman/enet "$(ENET_REF)"

fetch-bomb-data: data-dir
	sh tools/tools.sh github_fetch  mobius-tempname/sauerbomber-data "$(DATADIR)"/sauerbomber

fetch-sauerbraten: data-dir
	sh tools/tools.sh github_fetch  mobius-tempname/sauerbraten "$(DATADIR)"/sauerbraten

fetch-data: fetch-bomb-data fetch-sauerbraten

# Dependency Management ####################################

install-debian-packets:
	apt-get install libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl1.2-dev libenet-dev libenet1-dev libenet0debian1 libsdl-image1.2 libsdl-mixer1.2 g++ g++-4.4

# File Management ##########################################

build-dir:
	mkdir -p "$(BUILDDIR)"

data-dir:
	mkdir -p "$(DATADIR)"

out-dir:
	mkdir -p "$(OUTDIR)"

bin-dir:
	mkdir -p "$(BINDIR)"

bin-dir:

link-enet: fetch-enet link-src
	cp -Rl "$(ENET_REF)" "$(OUT_ENET)"

link-src: out-dir
	cp -Rl "$(SRC_REF)" "$(OUT_SRC)"

clean:
	rm -Rv "$(BUILDDIR)" "$(BINDIR)"

# Compilation ##############################################

compile: link-src link-enet
	$(MAKE) -C $(OUT_SRC) -j $(JOBS)

cpexe: compile bin-dir
	cp "$(OUT_SRC)/"*client "$(BINDIR)/$(OUT)_client" -rv
	cp "$(OUT_SRC)/"*server "$(BINDIR)/$(OUT)_server" -rv
	cp "$(OUT_SRC)/"*master "$(BINDIR)/$(OUT)_master" -rv || true
