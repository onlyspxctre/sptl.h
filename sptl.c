#include "sptl.h"
#include <cmocka.h>

static void sptl_test_da_pop_overflow(void **state) {
    (void) state;

    Sp_Dynamic_Array(int) da = {0};

    sp_da_push(&da, 1);
    sp_da_push(&da, 2);
    sp_da_push(&da, 3);

    assert_true(da.count == 3);

    for (size_t i = 0; i < 100; ++i) {
        sp_da_pop(&da);
    }

    assert_true(da.count == 0);

    sp_da_free(&da);
}
static void sptl_test_queue_pop_overflow(void **state) {
    (void) state;

    Sp_Queue(int) queue = {0};

    sp_queue_push(&queue, 1);
    sp_queue_push(&queue, 2);
    sp_queue_push(&queue, 3);

    assert_true(sp_queue_peek(&queue) == 1);

    for (size_t i = 0; i < 100; ++i) {
        sp_queue_pop(&queue);
    }

    assert_true(queue.count == 0);
    assert_true(sp_queue_peek(&queue) == 0);

    sp_queue_free(&queue);
}

static void sptl_test_queue_push_peek_pop(void **state) {
    (void) state;

    Sp_Queue(int) queue = {0};

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

static const struct CMUnitTest sptl_tests[] = {
    cmocka_unit_test(sptl_test_da_pop_overflow),
    cmocka_unit_test(sptl_test_queue_pop_overflow),
    cmocka_unit_test(sptl_test_queue_push_peek_pop),
};

int main(void) {
    return cmocka_run_group_tests(sptl_tests, NULL, NULL);
}
