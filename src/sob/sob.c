#include "sob.h"



#ifndef SOB_APP_OFF

ArgParser_def_fn(all) {
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
    ArgParser_use_cmd(NULL, "run all" , "This is usage", all  , default_args);
    ArgParser_use_cmd(NULL, "run test", "This is usage", hello, default_args);
    ArgParser_sys_cmd(CStrArray_new("uname", "-a", "help"));
    ArgParser_sys_cmd(CStrArray_new("ls", "-l"));
    
    char* test;
    Cstr* ss = CStrArray_new("ls", "-l", "hello");
    CStrArray_join(ss, test, ", ");
    printf("%s\n", test);
    ArgParser_run(argc, argv, envp);
    return 0;
}

#endif