#include <sob/sob.h>
#include <util/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    ut_ast(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;

}


char *test_push_pop()
{
    List_push(list, test1);
    ut_ast(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    ut_ast(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    ut_ast(List_last(list) == test3, "Wrong last value.");
    ut_ast(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    ut_ast(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    ut_ast(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    ut_ast(val == test1, "Wrong value on pop.");
    ut_ast(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    ut_ast(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    ut_ast(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    ut_ast(List_first(list) == test3, "Wrong last value.");
    ut_ast(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    ut_ast(val == test2, "Wrong removed element.");
    ut_ast(List_count(list) == 2, "Wrong count after remove.");
    ut_ast(List_first(list) == test3, "Wrong first after remove.");
    ut_ast(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    ut_ast(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    ut_ast(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    ut_ast(val == test1, "Wrong value on shift.");
    ut_ast(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}



char *all_tests() {
    

    ut_add(test_create);
    ut_add(test_push_pop);
    ut_add(test_unshift);
    ut_add(test_remove);
    ut_add(test_shift);
    ut_add(test_destroy);

    return NULL;
}

ut_run(all_tests);