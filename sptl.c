#include "sptl.h"
#include <cmocka.h>

static void sptl_test_da_resize(void **state) {
    (void) state;

    Sp_Dynamic_Array(int) da = {0};

    sp_da_reserve(&da, 16);
    memset(da.data, -1, da.capacity * sizeof(*da.data));
    sp_da_resize(&da, 6);

    assert_true(da.count == 6);
    for (size_t i = 0; i < da.capacity; ++i) {
        if (i < da.count) {
            assert_true(da.data[i] == 0);
        } else {
            assert_true(da.data[i] == -1);
        }
    }

    sp_da_free(&da);
    assert_true(da.data == NULL);
    assert_true(da.count == 0);
    assert_true(da.capacity == 0);
}
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
    assert_true(da.data == NULL);
    assert_true(da.count == 0);
    assert_true(da.capacity == 0);
}
static void sptl_test_ll_push_pop_back(void **state) {
    (void) state;

    Sp_Linked_List(int) ll = {0};

    sp_ll_push_back(&ll, 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 1);

    sp_ll_push_back(&ll, 2);
    assert_true(*(int *) ll.head->data == 1);
    assert_true(*(int *) ll.tail->data == 2);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 2);

    sp_ll_push_back(&ll, 3);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 3);

    sp_ll_pop_back(&ll);
    sp_ll_pop_back(&ll);
    sp_ll_pop_back(&ll);

    assert_true(ll.head == NULL);
    assert_true(ll.tail == NULL);

    sp_ll_free(&ll);
}
static void sptl_test_ll_push_pop_front(void **state) {
    (void) state;

    Sp_Linked_List(int) ll = {0};

    sp_ll_push_back(&ll, 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 1);

    sp_ll_push_back(&ll, 2);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 2);

    sp_ll_push_back(&ll, 3);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 1);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 3);

    sp_ll_pop_front(&ll);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 2);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 3);

    sp_ll_pop_front(&ll);
    assert_true(*sp_ll_node_unwrap(&ll, ll.head) == 3);
    assert_true(*sp_ll_node_unwrap(&ll, ll.tail) == 3);

    sp_ll_pop_front(&ll);
    assert_true(ll.head == NULL);
    assert_true(ll.tail == NULL);

    sp_ll_free(&ll);
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
    assert_true(queue.data == NULL);
    assert_true(queue.head == 0);
    assert_true(queue.tail == 0);
    assert_true(queue.count == 0);
    assert_true(queue.capacity == 0);
}

static void sptl_test_queue_push_peek_pop(void **state) {
    (void) state;

    Sp_Queue(int) queue = {0};

    sp_queue_push(&queue, 1);
    sp_queue_push(&queue, 2);
    sp_queue_push(&queue, 3);

    int expected[] = {1, 2, 3};

    size_t i = 0;
    while (queue.count > 0) {
        assert_true(expected[i++] == sp_queue_peek(&queue));
        sp_queue_pop(&queue);
    }

    sp_queue_free(&queue);
    assert_true(queue.data == NULL);
    assert_true(queue.head == 0);
    assert_true(queue.tail == 0);
    assert_true(queue.count == 0);
    assert_true(queue.capacity == 0);
}

static void sptl_test_ht_insert(void **state) {
    (void) state;

    Sp_Hash_Table(const char *, int) ht = {0};

    sp_ht_insert(&ht, "Alpha", 1);
    sp_ht_insert(&ht, "Beta", 2);
    sp_ht_insert(&ht, "Sigma", 3);
    sp_ht_insert(&ht, "Omega", 4);

    assert_true(ht.count == 4);

    sp_ht_node_t(&ht) *ptr = NULL;
    sp_ht_get(&ht, "Alpha", &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 1);

    sp_ht_get(&ht, "Beta", &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 2);

    sp_ht_get(&ht, "Sigma", &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 3);

    sp_ht_get(&ht, "Omega", &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 4);

    sp_ht_free(&ht);
    assert_true(ht.table.data == NULL);
    assert_true(ht.table.count == 0);
    assert_true(ht.table.capacity == 0);
    assert_true(ht.count == 0);
}

static void sptl_test_ht_dup_insert(void **state) {
    (void) state;

    Sp_Hash_Table(const char *, int) ht = {0};
    sp_ht_node_t(&ht) *ptr = NULL;

    sp_ht_insert(&ht, "Bob", 5);

    sp_ht_get(&ht, "Bob", &ptr);
    assert_true(ptr);

    assert_true(ptr->value == 5);

    sp_ht_insert(&ht, "Bob", 10);
    assert_true(ptr->value == 10);

    sp_ht_insert(&ht, "Bob", 15);
    assert_true(ptr->value == 15);

    sp_ht_free(&ht);
}

static const struct CMUnitTest sptl_tests[] = {
    /* Sp_Dynamic_Array */
    cmocka_unit_test(sptl_test_da_resize),
    cmocka_unit_test(sptl_test_da_pop_overflow),

    /* Sp_Linked_List */
    cmocka_unit_test(sptl_test_ll_push_pop_back),
    cmocka_unit_test(sptl_test_ll_push_pop_front),

    /* Sp_Queue */
    cmocka_unit_test(sptl_test_queue_pop_overflow),
    cmocka_unit_test(sptl_test_queue_push_peek_pop),

    /* Sp_Hash_Table */
    cmocka_unit_test(sptl_test_ht_insert),
    cmocka_unit_test(sptl_test_ht_insert),
    cmocka_unit_test(sptl_test_ht_dup_insert),
};

int main(void) { return cmocka_run_group_tests(sptl_tests, NULL, NULL); }
