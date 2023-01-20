#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *fmtname(char *path) {
    char *p = path;
    p = path + strlen(path);
    while (*p != '/')
        p --;
    p ++;
    return p;
}

void find(char *path, char *name) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[100];
    memset(buf, 0, 100);
    char *p;


    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: connot open %s\n", path);
        return ;
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: connot stat %s\n", path);
        close(fd);
        return ;
    }
    switch(st.type) {
        case T_FILE:
           printf("%s\n", fmtname(path));
           break;
        case T_DIR:
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p ++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) 
                    continue;
                if ((strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0))
                    continue;
                strcpy(p, de.name);
                find(buf, name); 
            }
            break;
    }
    return ;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "argc error\n");
	    exit(1);
    }

    char target[100];
    target[0] = '/';
    strcpy(target + 1, argv[2]);


    find(argv[1], target);


    exit(0);
}
