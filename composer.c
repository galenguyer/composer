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

    // Get all files matching the given pattern in the current directory
    glob_t glob_buf;
    glob("docker-compose.*.yaml", 0, NULL, &glob_buf);

    // Create the char* args array for all the arguments we'll be passing in
    char* args[argc+2+(2*glob_buf.gl_pathc)];

    // Set the base command and file
    args[0] = COMMAND;
    args[1] = "-f";
    args[2] = "docker-compose.yaml";

    // For each path found by glob, append -f [PATH] to args
    for(size_t i = 0; i < glob_buf.gl_pathc; i++) {
        args[(2*i)+3] = "-f";
        args[(2*i)+4] = glob_buf.gl_pathv[i];
    }

    // Append all command line arguments passed into composer
    for (int i = 1; i < argc; i++) {
        args[2+(2*glob_buf.gl_pathc)+i] = argv[i];
    }

    // Set the final arg to NULL as expected by execvp
    args[argc+2+(2*glob_buf.gl_pathc)] = NULL;

    // Run the command and print an error if it fails
    int result = execvp(COMMAND, args);
    if (result < 0) {
        perror(COMMAND);
    }
}