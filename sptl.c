#include "sptl.h"

Sp_Hash_Table(char) HT_Char;

int main(void) {
    HT_Char ht = {0};
    sp_ht_insert(&ht, "A", (char) 'A');
    sp_ht_insert(&ht, "A", (char) 'a');
    sp_ht_insert(&ht, "B", (char) 'B');
    sp_ht_insert(&ht, "C", (char) 'C');
    sp_ht_insert(&ht, "D", (char) 'D');
    sp_ht_insert(&ht, "E", (char) 'E');
    sp_ht_insert(&ht, "Q", (char) 'Q');

    sp_ht_reserve(&ht, 32);

    sp_ht_print(&ht);

    sp_ht_node_ptr(&ht) ptr = sp_ht_get(&ht, "C");
    printf("%c\n", ptr->value);
    ptr = sp_ht_get(&ht, "D");
    printf("%c\n", ptr->value);
    ptr = sp_ht_get(&ht, "F");
    printf("%c\n", ptr->value);

    sp_ht_free(&ht);
}
