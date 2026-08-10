#include "sptl.h"
#include <cmocka.h>
#include <string.h>

static void sptl_test_da_resize(void **state) {
    (void) state;

    Sp_Dynamic_Array(int) da = {0};

    sp_da_reserve(&da, SP_DA_INIT_CAP);
    memset(da.data, 1, da.capacity * sizeof(*da.data));
    sp_da_resize(&da, 6);

    assert_true(da.count == 6);
    assert_true(da.capacity == 16);
    for (size_t i = 0; i < da.capacity; ++i) {
        if (i < da.count) {
            assert_true(da.data[i] == 0);
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

static void sptl_test_da_pop_shrink(void **state) {
    (void) state;

    Sp_Dynamic_Array(int) da = {0};

    for (size_t i = 0; i < 4; ++i) {
        sp_da_push(&da, (int) i + 1);
    }
    assert_true(da.count == 4);
    assert_true(da.capacity == SP_DA_INIT_CAP);

    sp_da_pop(&da);

    assert_true(da.count == 3);
    assert_true(da.capacity == 8);

    sp_da_free(&da);
}

static void sptl_test_sb_appendf(void **state) {
    (void) state;

    Sp_String_Builder sb = {0};

    sp_sb_appendf(&sb, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    assert_true(strcmp(sb.data, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0);
    assert_true(sb.count == 42);

    sp_da_free(&sb);
    assert_true(sb.data == NULL);
    assert_true(sb.count == 0);
    assert_true(sb.capacity == 0);
}

static void sptl_test_sv(void **state) {
    (void) state;

    Sp_String_Builder sb = {0};
    sp_sb_appendf(&sb, "sdf");

    Sp_String_View lhs = sp_cstr_slice(sb.data);
    Sp_String_View rhs = sp_cstr_slice("sdf");

    assert_true(sp_sv_cmp(&lhs, &rhs) == 0);

    sp_da_free(&sb);
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

    sp_ht_insert(&ht, sp_cstr("Alpha"), 1);
    sp_ht_insert(&ht, sp_cstr("Beta"), 2);
    sp_ht_insert(&ht, sp_cstr("Sigma"), 3);
    sp_ht_insert(&ht, sp_cstr("Omega"), 4);

    assert_true(ht.count == 4);

    sp_ht_node_t(&ht) *ptr = NULL;
    sp_ht_get(&ht, sp_cstr("Alpha"), &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 1);

    sp_ht_get(&ht, sp_cstr("Beta"), &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 2);

    sp_ht_get(&ht, sp_cstr("Sigma"), &ptr);
    assert_true(ptr != NULL);
    assert_true(ptr->value == 3);

    sp_ht_get(&ht, sp_cstr("Omega"), &ptr);
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

    sp_ht_insert(&ht, sp_cstr("Bob"), 5);

    sp_ht_get(&ht, sp_cstr("Bob"), &ptr);
    assert_true(ptr);

    assert_true(ptr->value == 5);

    sp_ht_insert(&ht, sp_cstr("Bob"), 10);
    assert_true(ptr->value == 10);

    sp_ht_insert(&ht, sp_cstr("Bob"), 15);
    assert_true(ptr->value == 15);

    sp_ht_free(&ht);
}

static void sptl_test_ht_sv_insert(void **state) {
    (void) state;

    Sp_Hash_Table(Sp_String_View, int) ht = {0};
    sp_ht_node_t(&ht) *ptr = NULL;

    sp_ht_insert(&ht, sp_cstr_slice("Bob"), 5);
    sp_ht_get(&ht, sp_cstr_slice("Bob"), &ptr);
    assert_true(ptr->value == 5);

    sp_ht_insert(&ht, sp_cstr_slice("Bob"), 7);
    sp_ht_get(&ht, sp_cstr_slice("Bob"), &ptr);
    assert_true(ptr->value == 7);

    sp_ht_insert(&ht, sp_cstr_slice("Bob"), 9);
    sp_ht_get(&ht, sp_cstr_slice("Bob"), &ptr);
    assert_true(ptr->value == 9);

    sp_ht_free(&ht);
}

static void sptl_test_mh_insert(void **state) {
    (void) state;

    // Pushing (ensure heap property)
    Sp_Heap(int) mh = {0};
    sp_heap_push(&mh, 7);
    sp_heap_push(&mh, 5);

    assert_true(sp_heap_top(&mh) == 5);
    assert_true(mh.data[1] == 7);

    sp_heap_push(&mh, 12);
    assert_true(mh.data[2] == 12);

    assert_true(mh.count == 3);

    // Popping (ensure heap property)

    sp_heap_pop(&mh);
    assert_true(sp_heap_top(&mh) == 7);

    sp_heap_pop(&mh);
    assert_true(sp_heap_top(&mh) == 12);

    sp_heap_pop(&mh);
    assert_true(mh.count == 0);

    sp_heap_free(&mh);
}

static void sptl_test_mh_expand(void **state) {
    (void) state;

    Sp_Heap(int) mh = {0};

    sp_heap_push(&mh, 1);
    assert_true(mh.count == 1);

    assert_true(mh.height == 3);
    assert_true(sp_bt_capacity_from_height(mh.height) == 7);

    for (size_t i = 2; i <= 7; ++i) {
        sp_heap_push(&mh, (int) i);
    }

    assert_true(mh.height == 3);
    assert_true(sp_bt_capacity_from_height(mh.height) == 7);

    sp_heap_push(&mh, 8);

    assert_true(mh.height == 4);
    assert_true(sp_bt_capacity_from_height(mh.height) == 15);

    sp_heap_free(&mh);
}

static inline Sp_String_Builder uint8_to_binary_str(uint8_t val) {
    Sp_String_Builder sp = {0};

    uint16_t subtractor = 256;
    bool state = false;

    while (val > 0) {
        if (val - subtractor < 0) {
            // bit is 0
            if (state) {
                sp_sb_appendf(&sp, "%c", '0');
            }
        } else {
            // bit is 1
            sp_sb_appendf(&sp, "%c", '1');
            state = true;
            val -= subtractor;
        }

        subtractor >>= 1;
    }

    return sp;
}

static void sptl_test_sb_binary(void **state) {
    (void) state;

    Sp_String_Builder sb = uint8_to_binary_str(25);

    assert_true(strcmp(sb.data, "11001") == 0);

    sp_da_free(&sb);
}

static int sptl_test_pair__checkboth(sp_pair_params(pair, int, const char *)) {
    Sp_Pair(int, const char *) pair = sp_pair_from_arg(pair);

    if (pair.left != 1) {
        return 0;
    }

    if (strcmp(pair.right, "fortnite") != 0) {
        return 0;
    }

    return 1;
}
static void sptl_test_pair(void **state) {
    (void) state;
    Sp_Pair(int, const char *) pair = {
        1,
        "fortnite"
    };

    assert_true(sptl_test_pair__checkboth(sp_pair_arg(pair)));
}

static const struct CMUnitTest sptl_tests[] = {
    /* Sp_Dynamic_Array */
    cmocka_unit_test(sptl_test_da_resize),
    cmocka_unit_test(sptl_test_da_pop_overflow),
    cmocka_unit_test(sptl_test_da_pop_shrink),

    /* Sp_String_Builder */
    cmocka_unit_test(sptl_test_sb_appendf),

    /* Sp_String_Slice */
    cmocka_unit_test(sptl_test_sv),

    /* Sp_Linked_List */
    cmocka_unit_test(sptl_test_ll_push_pop_back),
    cmocka_unit_test(sptl_test_ll_push_pop_front),

    /* Sp_Queue */
    cmocka_unit_test(sptl_test_queue_pop_overflow),
    cmocka_unit_test(sptl_test_queue_push_peek_pop),

    /* Sp_Hash_Table */
    cmocka_unit_test(sptl_test_ht_insert),
    cmocka_unit_test(sptl_test_ht_dup_insert),
    cmocka_unit_test(sptl_test_ht_sv_insert),

    /* Sp_Min_Heap */
    cmocka_unit_test(sptl_test_mh_insert),
    cmocka_unit_test(sptl_test_mh_expand),

    /* Miscellaneous */
    cmocka_unit_test(sptl_test_sb_binary),
    cmocka_unit_test(sptl_test_pair),

};

int main(void) { return cmocka_run_group_tests(sptl_tests, NULL, NULL); }
