#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>

void print_usage();

int main(int argc, char **argv) {
    if (argc < 3) {
        print_usage();
        return 1;
    }
    int interval = atoi(argv[1]);
    if (interval == 0) {
        print_usage();
        return 2;
    }

    pid_t pid = atoi(argv[2]);
    if (pid == 0) {
        pid = fork();
    }
    if (pid == 0) {
        execvp(argv[2], argv+2);
    } else if (pid < 0) {
        return pid;
    } else {
        char filename[20];
        char content[150];
        sprintf(filename, "/proc/%d/statm", pid);
        FILE *statm;
        FILE *record = fopen("memstat.data", "wt");
        if (record == NULL) {
            printf("failed to open memstat.data\n");
            return 3;
        }
        while ((statm=fopen(filename, "rt"))) {
            // 读取并记录内存使用
            fgets(content, 150, statm);
            fclose(statm);
            fwrite(content, strlen(content), 1, record);
            // 占用内存为0表示进程变成僵尸
            if (content[0] == '0') {
                wait(NULL);
                break;
            }
            usleep(interval);
        }
        fclose(record);
        return 0;
    }
}

void print_usage() {
    puts(
        "Usage:\n"
        "memstat <interval_us> <command/pid> <arguments>\n"
        "\tinterval_us: the interval of samples in microseconds\n"
        "\tcommand: the program to be measured\n"
        "\tpid: the pid of the process to attach\n"
        "\targuments: the arguments passed to the program to be measured\n"
    );
}
