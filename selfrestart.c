#include <unistd.h>

void self_restart(const Arg *arg) {
    char *const argv[] = {"dwm", NULL};

    execvp(argv[0], argv);
}
