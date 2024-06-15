#include "sob.inc"
#include "sob.h"

ArgParser_def_fn(lla) {
    printf("Hello World\n");
}

ArgParser_def_fn(hello) {
    printf("Hello World\n");
}

ArgParser_def_args(default_args) = {
    ArgParser_arg_INPUT,
    ArgParser_arg_OUTPUT,
    ArgParser_arg_END
};

int main(int argc, char *argv[], char *envp[]) {
    ArgParser_init("Sob - Super Nobuild Toolkit with only .h file", NULL);
    ArgParser_add_cmd(NULL, "run all" , "This is usage", lla  , default_args);
    ArgParser_add_cmd(NULL, "run test", "This is usage", hello, default_args);
    ArgParser_run(argc, argv, envp);
    return 0;
}