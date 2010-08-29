CFLAGS=-g3 -O2 -Wall
LDFLAGS=`pkg-config --cflags --libs protobuf` -lgflags -lglog
CC=clang

all: bin/aos

bin/aos: out/main.o out/libaos.a
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

bin/test-aos: out/test.o out/libaos.a 
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

out/libaos.a: out/gen/aos.pb.o out/main.o out/loans.o out/auction.o out/dispatch.o
	@$(AR) r $@ $^

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
	rm -rf gen out aos
