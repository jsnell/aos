CFLAGS=-g2 -O2 -Wall -Werror -Isrc -Igen -fno-strict-aliasing
# -std=c++0x
LDFLAGS=`pkg-config --cflags --libs protobuf` -lgflags -lglog -lctemplate
CC=g++
# CC=clang

vpath %.proto proto/
vpath %.o out/

all: bin/aos bin/test-aos bin/render-test bin/pprint-test

OBJ=aos.pb.o dispatch.o loans.o auction.o powers.o build.o move.o render.o map_util.o

bin/aos: main.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

bin/test-aos: test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

bin/render-test: render-test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

bin/pprint-test: pprint-test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $+

out/%.o: src/%.cc Makefile
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $<

gen/aos.pb.cc: proto/aos.proto
	@mkdir -p gen
	(cd proto && protoc --cpp_out ../gen aos.proto)

out/aos.pb.o: gen/aos.pb.cc
	$(CC) $(CFLAGS) -o $@ -c $<

test: bin/test-aos
	@for i in testdata/*; do X="$< --test_pb_paths=$$i"; echo "$$X"; eval "$$X"; done

clean:
	rm -rf gen out bin

out/%.d: %.cc
	echo dep
	$(CC) -M -o out/$*.d $(CFLAGS) $<

out/dep: gen/aos.pb.cc Makefile
	@mkdir -p out
	@$(CC) -M $(CFLAGS) src/*.cc | perl -i -pe 's{^(.*:)}{out/$$1}' > out/dep

dep: out/dep

-include out/dep
