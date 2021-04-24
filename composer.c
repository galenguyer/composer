#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define COMMAND "echo"

int main(int argc, char** argv) {
    // TODO: Support docker-compose.yaml too
    if (access("docker-compose.yaml", R_OK) < 0) {
        fprintf(stderr, "No 'docker-compose.yaml' file found\n");
        exit(1);
    }
    char* args[argc+2];
    args[0] = COMMAND;
    args[1] = "-f";
    args[2] = "docker-compose.yaml";
    for (int i = 2; i < argc; i++) {
        args[i] = argv[i-1];
    }
    args[argc+2] = NULL;
    for(int i = 0; i < argc+2; i++) {
        printf("%s ", args[i]);
    }
    puts("");
    int result = execvp(COMMAND, args);
    if (result < 0) {
        perror(COMMAND);
    }
}