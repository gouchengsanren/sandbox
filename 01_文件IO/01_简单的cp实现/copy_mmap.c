#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void show_help()
{
    printf("Usage:\n");
    printf("./cp file1 file2\n");
}

/**
 * 实现cp的功能
 * 要求用mmap实现
 */
int main(int argc, char **argv)
{
    int fd_old = -1, fd_new = -1;
    char *buf = NULL;
    int ret = 0;
    struct stat stat;

    if (argc != 3) {
        show_help();
        return -EINVAL;
    }

    fd_old = open(argv[1], O_RDONLY);
    if (-1 == fd_old) {
        printf("open %s fail\n", argv[1]);
        return -1;
    }

    if (fstat(fd_old, &stat) == -1) {
        printf("get file(%s) stat fail\n", argv[1]);
        return -1;
    }

    buf = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd_old, 0);
    if (MAP_FAILED == buf) {
        printf("mmap file %s fail\n", argv[1]);
        return -1;
    }

    fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (-1 == fd_new) {
        printf("create %s fail\n", argv[2]);
        return -1;
    }

    if (write(fd_new, buf, stat.st_size) != stat.st_size) {
        printf("write %s fail\n", argv[2]);
        return -1;
    }

    return 0;
}

