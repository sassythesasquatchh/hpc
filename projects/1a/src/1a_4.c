#include <stdio.h>
#include <unistd.h>
#include <string.h>

void printCPUInfo() {
   
        FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
        if (cpuinfo != NULL) {
            char line[256];
            while (fgets(line, sizeof(line), cpuinfo) != NULL) {
                if (strncmp(line, "model name", 10) == 0) {
                    printf("CPU: %s", &line[13]);
                    break;
                }
            }
            fclose(cpuinfo);
        } else {
            perror("Error reading CPU info");
        }
    
}

int main() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hello World! I am running on %s\n", hostname);
        printCPUInfo();
    } else {
        perror("Error getting hostname");
    }

    return 0;
}

