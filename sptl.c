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

    sp_ht_print(&ht);
}
