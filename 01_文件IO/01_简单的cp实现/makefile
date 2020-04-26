CC=arm-linux-gnueabihf-gcc
TARGETS := cp cp_mmap

all: $(TARGETS)

cp: copy.o
	$(CC) -o $@ $^

cp_mmap: copy_mmap.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm -rf $(shell find . -name *.o)
	rm -rf $(TARGETS)

install:
	@cp -rf $(wildcard $(TARGETS)) /home/book/nfs_rootfs/

