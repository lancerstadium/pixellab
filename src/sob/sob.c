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
    
    CStr* cmd1, *cmd2, *cmd3;
    CStr* cmd4;
    CStr* cmd5 = (CStr[]) {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", NULL};
    CStrArray_new(cmd1, "uname", "-a", "help");
    CStrArray_new(cmd2, "ls", "-l");
    CStrArray_new(cmd3, "make", "all");
    CStrArray_new(cmd4, "make", "clean", "watermelon");
    CStrArray_push(cmd2, "isam");
    CStrArray_pushn(cmd2, cmd5);
    CStr mm;
    CStrArray_pop(cmd2, mm);
    printf("mm: %s\n", mm);

    bool b = IS_DIR("./docs");
    printf("%s\n", b ? "true" : "false");

    // Sob_rename(mm, "hello");

    /// TODO: CStrArray_copy memory leak
    // CStr* cmd2_copy;
    // CStrArray_copy(cmd2, cmd2_copy);
    // CStrArray_prefix(cmd2_copy, "-L");
    CStrArray_forauto(cmd2, i, s,
        printf("copy: %s\n", s);
    );

    char* cc;
    CStrArray_path(cmd3, cc);
    printf("%s\n", cc);

    ECHO("hello", "world", _BLUE("Machine"));
    MKDIR("demo01", "demo02", "demo03");

    RM("demo01", "demo02", "demo03");

    // printf("%s\n", STR_BOOL(IS_MODIFIED_AFTER("./demo01", "./demo02")));

    ArgParser_sys_cmd(cmd1);
    ArgParser_sys_cmd(cmd2);
    ArgParser_sys_cmd(cmd3);
    ArgParser_sys_cmd(cmd4);

    ArgParser_run(argc, argv, envp);
    return 0;
}

#endif