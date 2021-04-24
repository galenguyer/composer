#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>

#define COMMAND "docker-compose"

int main(int argc, char** argv) {
    // TODO: Support docker-compose.yaml too
    if (access("docker-compose.yaml", R_OK) < 0) {
        fprintf(stderr, "No 'docker-compose.yaml' file found\n");
        exit(1);
    }

    glob_t glob_buf;
    glob("docker-compose.*.yaml", 0, NULL, &glob_buf);

    char* args[argc+2+(2*glob_buf.gl_pathc)];
    args[0] = COMMAND;
    args[1] = "-f";
    args[2] = "docker-compose.yaml";
    for(size_t i = 0; i < glob_buf.gl_pathc; i++) {
        args[(2*i)+3] = "-f";
        args[(2*i)+4] = glob_buf.gl_pathv[i];
    }
    for (int i = 1; i < argc; i++) {
        args[2+(2*glob_buf.gl_pathc)+i] = argv[i];
    }
    args[argc+2+(2*glob_buf.gl_pathc)] = NULL;

    int result = execvp(COMMAND, args);
    if (result < 0) {
        perror(COMMAND);
    }
}