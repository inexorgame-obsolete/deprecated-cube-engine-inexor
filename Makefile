JOBS=$(shell </proc/cpuinfo grep "processor" | wc -l)

compile=make -C src -j $(JOBS)

help:
	cat readme.md

native:
	$(compile)

linux:
	$(compile) PLATFORM=linux

win32:
	$(compile) PLATFORM=MINGW-CROSS

win64:
	$(compile) PLATFORM=MINGW-CROSS-64

all-win: win32 win64

all-os: all-win linux

clean:
	$(compile) clean

install-debian-packets:
	apt-get install libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl1.2-dev libenet-dev libenet1-dev libenet0debian1 libsdl-image1.2 libsdl-mixer1.2 g++ g++-4.4
