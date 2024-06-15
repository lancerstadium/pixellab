
#include "sob.inc"
#include "sob.h"


ArgParser_def_fn(default_fn) {
    printf("Hello World\n");
}

ArgParser_def_args(default_args) = {
    ArgParser_arg_INPUT,
    ArgParser_arg_OUTPUT,
    ArgParser_arg_END
};

int main(int argc, char *argv[], char *envp[]) {
    ArgParser_init("Sob - Super Nobuild Toolkit with only .h file", NULL);
    ArgParser_add_cmd("all", "run all", "This is usage", default_fn, default_args);
    ArgParser_add_cmd("test", "run test", "This is usage", default_fn, default_args);
    ArgParser_run(argc, argv, envp);
    return 0;
}