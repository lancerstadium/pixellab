#include <sob/sob.h>
#include <util/queue.h>
#include <assert.h>
// 附加题：使用DArray代替List实现Stack，并保持单元测试不变。这意味着你需要创建你自己的STACK_FOREACH。


static Queue *queue = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3


char *test_create()
{
    queue = Queue_create();
    UnitTest_ast(queue != NULL, "Failed to create queue.");

    return NULL;
}

char *test_destroy()
{
    UnitTest_ast(queue != NULL, "Failed to make queue #2");
    Queue_destroy(queue);

    return NULL;
}

char *test_send_recv()
{
    int i = 0;
    for(i = 0; i < NUM_TESTS; i++) {
        Queue_send(queue, tests[i]);
        UnitTest_ast(Queue_peek(queue) == tests[0], "Wrong next value.");
    }

    UnitTest_ast(Queue_count(queue) == NUM_TESTS, "Wrong count on send.");

    QUEUE_FOREACH(queue, cur) {
        Log_dbg("VAL: %s", (char *)cur->value);
    }

    for(i = 0; i < NUM_TESTS; i++) {
        char *val = Queue_recv(queue);
        UnitTest_ast(val == tests[i], "Wrong value on recv.");
    }

    UnitTest_ast(Queue_count(queue) == 0, "Wrong count after recv.");

    return NULL;
}

char *all_tests() {
    

    UnitTest_add(test_create);
    UnitTest_add(test_send_recv);
    UnitTest_add(test_destroy);

    return NULL;
}

UnitTest_run(all_tests);