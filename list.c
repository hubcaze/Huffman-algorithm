#include"list.h"

List *init_list()
{
	List *list = malloc(sizeof(List));
	if(list == NULL)
	{
		printf("Erreur lors de l'allocation de memoire\n");
		exit(1);
	}
	list->first = NULL;
	list->nb_symb = 0;
	return(list);
}

void add_char(char c, List *list)
{
	if(list->first == NULL)
	{
		Element el = malloc(sizeof(element));
		el->carac = c;
		el->nb = 1;
		el->nxt = NULL;
		list->first = el;
		list->nb_symb = 1;
	}
	else
	{
		Element tmp = list->first;
		while(tmp->nxt)
		{
			if(tmp->carac == c)
			{
				tmp->nb++;
				return;
			}
			tmp = tmp->nxt;
		}
		if(tmp->carac == c)
		{
			tmp->nb++;
			return;
		}
		else
		{
			Element new_list = malloc(sizeof(element));
			new_list->carac = c;
			new_list->nb = 1;
			new_list->nxt = NULL;
			tmp->nxt = new_list;
			list->nb_symb++;
		}
	}
}

void add_freq(char c, int nb, List *list)
{
	if(list->first == NULL)
	{
		Element el = malloc(sizeof(element));
		el->carac = c;
		el->nb = nb;
		el->nxt = NULL;
		list->first = el;
		list->nb_symb = 1;
	}
	else
	{
		Element tmp = list->first;
		while(tmp->nxt)
			tmp = tmp->nxt;
		Element new_list = malloc(sizeof(element));
		new_list->carac = c;
		new_list->nb = nb;
		new_list->nxt = NULL;
		tmp->nxt = new_list;
		list->nb_symb++;
	}
}

void print_list(List list)
{
	printf("Affichage d'une liste de symboles\n");
	Element tmp = list.first;
	while(tmp)
	{
		printf("Caractere: %c\n", tmp->carac);
		printf("Nb d'occurrences: %d\n\n", tmp->nb);
		tmp = tmp->nxt;
	}
}

void free_element(Element el)
{
	if(el == NULL)
		return;
	free_element(el->nxt);
	free(el);
}

void free_list(List *list)
{
	free_element(list->first);
	free(list);
}