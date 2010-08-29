CFLAGS=-g3 -O2 -Wall -Werror
LDFLAGS=`pkg-config --cflags --libs protobuf` -lgflags -lglog
CC=clang

vpath %.o out/

all: bin/aos

OBJ=out/gen/aos.pb.o out/dispatch.o out/loans.o out/auction.o

bin/aos: out/main.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

bin/test-aos: out/test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

out/%.o: %.cc
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $(CFLAGS) $<

%.o: %.cc
	@echo "Bad dependency $@"
	@exit 1

gen/%.pb.cc: %.proto
	@mkdir -p gen
	protoc --cpp_out gen $<

run-tests: bin/test-aos
	@for i in testdata/*; do echo $$i; $< --test_pb_paths=$$i; done

clean:
	rm -rf gen out bin

out/%.d: %.cc
	$(CC) -M -o out/$*.d $(CFLAGS) $<

out/dep: gen/aos.pb.cc
	@mkdir -p out
	@$(CC) -M $(CFLAGS) *.cc > out/dep

dep: out/dep

-include out/dep