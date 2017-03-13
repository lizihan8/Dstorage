#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<fcntl.h>
#include<sys/wait.h>

#include "make_log.h"

int main(int argc, const char* argv[])
{
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid >0)
    {
        close(fd[1]);
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        read(fd[0], buf, sizeof(buf));
        LOG("2222","uploadfile","%s,%s",argv[1],buf);
        wait(NULL);
    }
    if(pid==0)
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("fdfs_upload_file","fdfs_upload_file","./conf/client.conf",argv[1],NULL);

    }
    LOG("1111","2222","%s,%d","123123",100);
    return 0;
}
