#include "sptl.h"

Sp_Linked_List(char) Sp_Char_LL;

int main(void) {
    Sp_Char_LL ll = {0};

    sp_ll_push_back(&ll, 'A');
    sp_ll_push_back(&ll, 'B');
    sp_ll_push_back(&ll, 'C');
    sp_ll_push_front(&ll, 'Q');
    sp_ll_pop_back(&ll);
    sp_ll_pop_front(&ll);

    sp_ll_node_ptr(&ll) ptr = ll.tail;
    while (ptr) {
        printf("%c\n", ptr->data);
        ptr = ptr->prev;
    }

    sp_ll_free(&ll);
}
