CFLAGS=-g1 -O2 -Wall -Werror
LDFLAGS=`pkg-config --cflags --libs protobuf` -lgflags -lglog
CC=clang

vpath %.o out/

all: bin/aos

OBJ=gen/aos.pb.o dispatch.o loans.o auction.o

bin/aos: main.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $+

bin/test-aos: test.o $(OBJ)
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $+

out/%.o: %.cc
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $(CFLAGS) $<

gen/%.pb.cc: %.proto
	@mkdir -p gen
	protoc --cpp_out gen $<

run-tests: bin/test-aos
	@for i in testdata/*; do echo $$i; $< --test_pb_paths=$$i; done

clean:
	rm -rf gen out bin

out/%.d: %.cc
	echo dep
	$(CC) -M -o out/$*.d $(CFLAGS) $<

out/dep: gen/aos.pb.cc
	@mkdir -p out
	@$(CC) -M $(CFLAGS) *.cc | perl -i -pe 's{^(.*:)}{out/$$1}' > out/dep

dep: out/dep

-include out/dep
