#ifndef BEGGAR_H
#define BEGGAR_H

int beggar(int Nplayers, int *deck, int talkative);
void riffle_once(void *L, int len, int size, void *work);
void riffle(void *L, int len, int size, int N);
int cmp_int(void *a, void *b);
int check_shuffle(void *L, int len, int size);

#endif