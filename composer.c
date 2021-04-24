#include <stdio.h>
#include <unistd.h>
#define COMMAND "echo"

int main(int argc, char** argv) {
    int result = execvp(COMMAND, argv);
    if (result < 0) {
        perror(COMMAND);
    }
}