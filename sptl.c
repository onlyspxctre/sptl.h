#include "sptl.h"

Sp_Hash_Table(char) HT_Char;

int main(void) {
    HT_Char ht = {0};
    sp_ht_insert(&ht, "A", 'A');
    sp_ht_insert(&ht, "B", 'B');
    sp_ht_insert(&ht, "C", 'C');
    sp_ht_insert(&ht, "D", 'D');
    sp_ht_insert(&ht, "E", 'E');
    sp_ht_insert(&ht, "Q", 'Q');

    sp_ht_print(&ht);
}
