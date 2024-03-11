#include <stdio.h>
#include <unistd.h>

int main() {
    char hostname[256];
    
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hello World! I am running on %s\n", hostname);
    } else {
        perror("Error getting hostname");
    }

    return 0;
}

