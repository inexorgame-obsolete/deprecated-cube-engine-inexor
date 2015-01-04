CPPFLAGS += -I"$(shell readlink -f ..)" -std=c++11 -Wall -Wextra -g -O0
LDFLAGS +=  -lstdc++ -lbsd -luuid -lboost_regex -lboost_system -lprotobuf -lm

.PHONY: all gcc clang clang-analyze compile
all: gcc clang analyze
	echo -e "\n\n"
	./test.gcc
	echo -e "\n\n"
	./test.clang

gcc:
	$(MAKE) clean_obj
	EXE=gcc CC=gcc CXX=g++ LD=gcc $(MAKE) testapp

clang:
	$(MAKE) clean_obj
	EXE=clang CC=clang CXX=clang++ LD=clang $(MAKE) testapp

analyze:
	$(MAKE) clean_obj
	EXE=analyze CC=clang CXX=clang++ LD=clang scan-build $(MAKE) testapp

objs = $(shell find ../net ../rpc ../util . | grep -Pi '\.c(c|pp|\+\+)$$' | grep -Piv '\.pb.cc' | sed 's@\.[^\.]*$$@.o@') ../rpc/inexor_service.pb.o
compile: ../rpc/inexor_service.pb.h $(objs)

link: compile
	$(LD) $(LDFLAGS) -o "test.$(EXE)" $(objs)

testapp: compile link

%.pb.cc: %.proto
	protoc --proto_path=.. --cpp_out=.. $<

%.pb.h: %.proto
	protoc --proto_path=.. --cpp_out=.. $<

.PHONY: clean clean_obj
clean_obj:
	rm -f $(objs)

clean: clean_obj
	rm -f ./test.clang test.gcc test.analyze \
		../rpc/inexor_service.pb.h ../rpc/inexor_service.pb.cc
