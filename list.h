#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct element {
	int nb;
	char carac;
	struct element *nxt;
} element, *Element;

typedef struct List{
	Element first;
	int nb_symb;
}List;

List *init_list();
void add_char(char c, List *list);
void add_freq(char c, int nb, List *list);
void print_list(List list);
void free_element(Element el);
void free_list(List *list);

#endif