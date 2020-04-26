#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void show_help()
{
    printf("Usage:\n");
    printf("./cp file1 file2\n");
}

/**
 * 实现cp的功能
 */
int main(int argc, char **argv)
{
    int fd_old = -1, fd_new = -1;
    char buf[1024] = {0};
    int ret = 0;

    if (argc != 3) {
        show_help();
        return -EINVAL;
    }

    fd_old = open(argv[1], O_RDONLY);
    if (-1 == fd_old) {
        printf("open %s fail\n", argv[1]);
        return -1;
    }

    fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (-1 == fd_new) {
        printf("create %s fail\n", argv[2]);
        return -1;
    }

    while ((ret = read(fd_old, buf, 1024)) > 0) {
        if (write(fd_new, buf, ret) != ret) {
            printf("write %s fail, errno(%d)\n", argv[2], errno);
            return -1;
        }
    }

    if (-1 == ret) {
        printf("read %s fail, errno(%d)\n", argv[2], errno);
        return -1;
    }

    return 0;
}

