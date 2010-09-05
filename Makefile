CFLAGS=-g1 -O2 -Wall -Werror -Isrc -Igen
LDFLAGS=`pkg-config --cflags --libs protobuf` -lgflags -lglog
CC=clang

vpath %.proto proto/
vpath %.o out/

all: bin/aos

OBJ=aos.pb.o dispatch.o loans.o auction.o powers.o build.o

bin/aos: main.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

bin/test-aos: test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

out/%.o: src/%.cc
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $(CFLAGS) $<

gen/aos.pb.cc: proto/aos.proto
	@mkdir -p gen
	(cd proto && protoc --cpp_out ../gen aos.proto)

out/aos.pb.o: gen/aos.pb.cc
	$(CC) $(CFLAGS) -o $@ -c $(CFLAGS) $<

run-tests: bin/test-aos
	@for i in testdata/*; do echo $$i; $< --test_pb_paths=$$i; done

clean:
	rm -rf gen out bin

out/%.d: %.cc
	echo dep
	$(CC) -M -o out/$*.d $(CFLAGS) $<

out/dep: gen/aos.pb.cc
	@mkdir -p out
	@$(CC) -M $(CFLAGS) src/*.cc | perl -i -pe 's{^(.*:)}{out/$$1}' > out/dep

dep: out/dep

-include out/dep
