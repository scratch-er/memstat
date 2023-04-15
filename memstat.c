#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int interval = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[2], argv+3);
    } else if (pid < 0) {
        return pid;
    } else {
        char filename[20];
        char content[150];
        printf("%s\n", filename);
        FILE *statm;
        FILE *record = fopen("memstat.data", "wt");
        if (record == NULL) {
            printf("failed to open memstat.data\n");
            return -1;
        }
        while ((statm=fopen(filename, "rt"))) {
            // 读取并记录内存使用
            fgets(content, 150, statm);
            fclose(statm);
            fwrite(content, strlen(content), 1, record);
            // 占用内存为0表示进程变成僵尸
            if (content[0] == '0') {
                break;
            }
            usleep(interval);
        }
        fclose(record);
        return 0;
    }
}
