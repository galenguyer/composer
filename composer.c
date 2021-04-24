#include <unistd.h>
#define COMMAND "echo"

int main(int argc, char** argv) {
    execvp(COMMAND, argv);
}