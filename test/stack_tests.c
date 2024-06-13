#include <util/sob.h>
#include <util/stack.h>
#include <assert.h>

static Stack *stack = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3


char *test_create()
{
    stack = Stack_create();
    ut_ast(stack != NULL, "Failed to create stack.");

    return NULL;
}

char *test_destroy()
{
    ut_ast(stack != NULL, "Failed to make stack #2");
    Stack_destroy(stack);

    return NULL;
}

char *test_push_pop()
{
    int i = 0;
    for(i = 0; i < NUM_TESTS; i++) {
        Stack_push(stack, tests[i]);
        ut_ast(Stack_peek(stack) == tests[i], "Wrong next value.");
    }

    ut_ast(Stack_count(stack) == NUM_TESTS, "Wrong count on push.");

    // STACK_FOREACH(stack, cur) {
    //     log_dbg("VAL: %s", (char *)cur->value);
    // }

    for(i = NUM_TESTS - 1; i >= 0; i--) {
        char *val = Stack_pop(stack);
        ut_ast(val == tests[i], "Wrong value on pop.");
    }

    ut_ast(Stack_count(stack) == 0, "Wrong count after pop.");

    return NULL;
}

char *all_tests() {
    

    ut_add(test_create);
    ut_add(test_push_pop);
    ut_add(test_destroy);

    return NULL;
}

ut_run(all_tests);