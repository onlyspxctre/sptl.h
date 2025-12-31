#include "sptl.h"

Sp_Linked_List(char) Sp_Char_LL;

int main(void) {
    Sp_Char_LL ll;

    sp_ll_push_back(&ll, 'A');
    sp_ll_push_back(&ll, 'B');
    sp_ll_push_back(&ll, 'Q');
    sp_ll_pop_back(&ll);

    Sp_Char_LL iter = ll;

    while (iter.head) {
        printf("%c\n", iter.head->data);
        iter.head = iter.head->next;
    }

    sp_ll_free(&ll);
}
