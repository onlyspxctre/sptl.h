#include "sptl.h"
#include <cmocka.h>

Sp_Queue(int) Sp_Queue_Int;

static void sptl_test_queue_push_peek_pop(void **state) {
    (void) state;

    Sp_Queue_Int queue = {0};

    sp_queue_push(&queue, 1);
    sp_queue_push(&queue, 2);
    sp_queue_push(&queue, 3);

    int expected[] = { 1, 2, 3 };

    size_t i = 0;
    while (queue.count > 0) {
        assert_true(expected[i++] == sp_queue_peek(&queue));
        sp_queue_pop(&queue);
    }

    sp_queue_free(&queue);
}

static const struct CMUnitTest tests[] = {
    cmocka_unit_test(sptl_test_queue_push_peek_pop),
};

int main(void) {
    return cmocka_run_group_tests(tests, NULL, NULL);
}
