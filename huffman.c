#include "list.h"
#include "huffman.h"
#include<string.h>

char *BUF;

void link(head_list *tl, node *n1, node *n2)
{
	node *new;
	new = malloc(sizeof(node));
	if(new == NULL)
	{
		printf("Echec d'allocation de memoire\n");
		exit(1);
	}
	new->type = typeNode;
	new->proba = n1->proba + n2->proba;
	new->n[0] = n1;
	new->n[1] = n2;
	add_node(tl, new);
}

node *search_firstnode(head_list *tl)
{
	node_list *ln = tl->first;
	node *min_node = ln->n;
	unsigned int min = ln->n->proba;
	while(ln)
	{
		if(ln->n->proba < min)
		{
			min = ln->n->proba;
			min_node = ln->n;
		}
		ln = ln->nxt;
	}

	// On supprime le node mais il va etre rajoute avec link
	remove_node(tl, min_node);
	return(min_node);
}

void remove_node(head_list *tl, node *n)
{
	node_list *tmp2 = tl->first;
	node_list *tmp;
	if(tmp2->n == n)
	{
		if(tl->first->nxt != NULL)
			tl->first = tl->first->nxt;
		else
			tl->first = NULL;
		return;
	}
	while(tmp2)
	{
		if(tmp2->n == n)
		{
			tmp->nxt = tmp2->nxt;
			return;
		}
		tmp = tmp2;
		tmp2 = tmp2->nxt;
	}
}

node *create_leaf(int c, unsigned int proba)
{
	node *new_f;
	new_f = malloc(sizeof(node));
	if(new_f == NULL)
	{
		printf("Echec d'allocation de memoire\n");
		exit(1);
	}
	new_f->type = typeLeaf;
	new_f->carac = c;
	new_f->proba = proba;
	return(new_f);
}

void print_tree(node *root)
{
	typeStruct t = root->type;
	if(t == typeNode)
	{
		print_tree(root->n[0]);
		print_tree(root->n[1]);
		printf("Noeud: %d\n", root->proba);
	}
	else
		printf("Feuille: %c, %d\n",root->carac, root->proba);
}

void affiche_listenodes(head_list *tl)
{
	node_list *ln = tl->first;
	printf("Affichage d'une liste de nodes\n");
	while(ln)
	{
		print_tree(ln->n);
		ln = ln->nxt;
	}
}

void print_dict(head_dict *hd)
{
	Dict *d = hd->first;
	printf("Affichage du dico\n");
	while(d)
	{
		printf("%c: %s, size:%d\n", d->c, d->code, d->size);
		d = d->nxt;
	}
}

head_list *init_leafs(List l)
{
	Element tmp = l.first;
	head_list *tl = malloc(sizeof(head_list));
	node_list *ln = malloc(sizeof(node_list));
	if(ln == NULL || tl == NULL)
	{
		printf("Echec d'allocation de memoire\n");
		exit(1);
	}
	ln->nxt = NULL;
	ln->n = create_leaf(tmp->carac, tmp->nb);
	tmp = tmp->nxt;
	tl->first = ln;
	while(tmp)
	{
		add_node(tl,create_leaf(tmp->carac, tmp->nb));
		tmp = tmp->nxt;
	}
	return(tl);
}

void add_node(head_list *tl, node *n)
{
	node_list *ln = tl->first;
	node_list *new = malloc(sizeof(node_list));
	if(new == NULL)
	{
		printf("Echec d'allocation de memoire\n");
		exit(1);
	}
	new->nxt = NULL;
	new->n = n;
	if(tl->first == NULL)
	{
		tl->first = new;
		return; 
	}
	while(ln->nxt)
		ln = ln->nxt;
	ln->nxt = new;
}

// Fonction qui renvoie le nombre de nodes dans une liste de nodes
int nb_nodes(head_list *tl)
{
	node_list *ln = tl->first;
	unsigned int i = 0;
	while(ln)
	{
		i++;
		ln = ln->nxt;
	}
	return(i);
}

void free_node(node *root)
{
	if(!root)
		return;
	typeStruct t = root->type;
	if(t == typeNode)
	{
		free_node(root->n[0]);
		free_node(root->n[1]);
	}
	free(root);
}

void free_nodelist(node_list *ln)
{
	if(ln == NULL)
		return;
	free_node(ln->n);
	free(ln);
}

void free_headlist(head_list *tl)
{
	node_list *tmp = tl->first;
	node_list *tmp2;
	while(tmp)
	{
		tmp2 = tmp->nxt;
		free_nodelist(tmp);
		tmp = tmp2;
	}
	free(tl);
}

int depth_tree(head_list *tl)
{
	int i  = 0;
	node_list *ln = tl->first;
	node *n = ln->n;
	while(n)
	{
		if(n->type == typeNode)
		{
			if(n->n[0]->type == typeNode)
				n = n->n[0];
			else
				n = n->n[1];
			i++;
		}
		else
			break;
	}
	i++;
	return(i);
}

void free_dict(Dict *d)
{
	if(d == NULL)
		return;
	free_dict(d->nxt);
	free(d->code);
	free(d);
}

void free_headdict(head_dict *hd)
{
	free_dict(hd->first);
	free(hd);
}

char *val_dict(head_dict *hd, char key)
{
	Dict *d = hd->first;
	while(d)
	{
		if(key == d->c)
			return(d->code);
		d = d->nxt;
	}
	return(NULL);
}

void add_el_to_dict(head_dict *hd, char *code, char carac)
{
	Dict *new_d = malloc(sizeof(Dict));
	new_d->code = strdup(code);
	new_d->c = carac;
	int i = 0;
	Dict *tmp;
	while(code[i])
		i++;
	new_d->size = i;
	if(!hd->first)
	{
		new_d->nxt = NULL;
		hd->first = new_d;
		return;
	}
	new_d->nxt = NULL;
	tmp = hd->first;
	while(tmp->nxt)
		tmp = tmp->nxt;
	tmp->nxt = new_d;
}

// Fonction Huffmann qui prend une liste de frequences et qui renvoie un arbre 
head_list *Huffman(List list)
{
	node *tmp;
	node *tmp2;
	head_list *tl;

	tl = init_leafs(list);

	while(nb_nodes(tl) != 1)
	{
		tmp = search_firstnode(tl);
		tmp2 = search_firstnode(tl);

		link(tl, tmp, tmp2);
	}
	return(tl);
}


void blek(char *str, int size)
{
	int i;
	for(i = 0; i<size; i++)
		str[i] = '\0';
}

head_dict *fill_dict(head_list *tl)
{
	head_dict *hd = malloc(sizeof(head_dict));
	hd->first = NULL;

	node_list *ln = tl->first;
	int n = depth_tree(tl);
	BUF = malloc(sizeof(char) * n);
	blek(BUF, n);
	fill_buf(ln->n, 'N', 0, hd);
	free(BUF);
	return(hd);
}

void fill_buf(node *n, char dir, int i, head_dict *hd)
{
	if(n == NULL)
		return;
	if(dir == 'N')
		i--;
	else
		BUF[i] = dir;
	if(n->type == typeNode)
	{
		fill_buf(n->n[0], '0', i+1, hd);
		fill_buf(n->n[1], '1', i+1, hd);
	}
	else
	{
		BUF[i+1] = '\0';
		add_el_to_dict(hd, BUF, n->carac);
	}
	BUF[i] = '\0';
}

// Fonction qui convertit une chaine binaire en int puis cast en char pour n'avoir qu'un seul octet
char convert_strbin_to_char(char *str)
{
	int len = strlen(str);
	while(len < 8)
	{
		str[len] = '0';
		len++;
	}
	unsigned int c = 0;
	int t = 1;
	for(int i = 0; i < 8; ++i)
	{
		if(str[8-i-1] == '1')
			c = c+t;
		t <<= 1;
	}
	return((char)c);
}

// Fonction de compression
void compress(FILE *fd)
{
	printf("Compression en cours...\n");
	List *list;
	list = init_list();

	head_list *tl;

	int i;
	fseek(fd, 0, SEEK_END);
	int len_file = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	char c[len_file];
	fread(c, 1, len_file, fd);
	for (i = 0; i < len_file; ++i)
		add_char(c[i], list);

	tl = Huffman(*list);

	int size = depth_tree(tl);
	char *full_code = malloc(sizeof(char) * i * size);

	blek(full_code, i*size); // On vide la chaine

	head_dict *hd = fill_dict(tl);

	for (i = 0; i < len_file; ++i)
		strcat(full_code,val_dict(hd, c[i]));

	print_dict(hd);

	int len = i; // size (en octets) du fichier d'entree

	int len_freq = list->nb_symb;
	fclose(fd);

	int n = strlen(full_code);
	int octets = (int)n / 8;
	if(n%8)
		octets++;
	FILE *fd2;
	fd2 = fopen("compressed.bin","wb");
	if(fd2 == NULL)
	{
		perror("Error");
		exit(1);
	}
	
	printf("Taille du fichier: %d octets\n", len);
	fwrite((char*)&len, 4, 1, fd2); // ecriture de la size (octets) du fichier original sur 4 octets
	fwrite(&octets, 4, 1, fd2); // ecriture de la size (octets) de la chaine composee de tous les codes
	fwrite(&len_freq, 2, 1, fd2); // ecriture de la size (octets) de la liste de frequences sur 2 octets

	// ecriture de la liste des frequences (occurences shehfickos)
	Element el = list->first;
	while(el)
	{
		fwrite(&el->carac, 1, 1, fd2); // ecriture du symbole
		fwrite(&el->nb, 4, 1, fd2); // ecriture de sa frequence
		el = el->nxt;
	}
 
	char buffer[9];
	int j;
	char carac;
	i = 0;
	while(i < n - n%8)
	{
		j = 0;
		while(j < 8)
		{
			buffer[j] = full_code[i+j];
			j++;
		}
		buffer[j] = '\0';
		carac = convert_strbin_to_char(buffer);

		fwrite(&carac, sizeof(char), 1, fd2);
		i = i + j;
	}
	int h;
	carac = 0;
	if(i < n)
	{
		for (h = 0; h < n%8; ++h)
		{
			if(full_code[i+h] == '1')
				carac |= (1 << (7-h));
		}
	}
	fwrite(&carac, sizeof(char), 1, fd2);

	free_headdict(hd);
	free(full_code);
	free_headlist(tl);
	free_list(list);
	fclose(fd2);
}

void decompress(FILE *fd)
{
	int len = 0;
	int len_freq = 0;
	int n = 0;
	fread(&len, 4, 1, fd); // lecture de la size (octets) du fichier original sur 4 octets
	fread(&n, 4, 1, fd); // lecture de la size (octets) de la chaine composee de tous les codes
	fread(&len_freq, 2, 1, fd); // lecture de la size (octets) de la liste de frequences

	printf("Taille du fichier: %d octets\n", len);
	printf("Decompression en cours...\n");

	List *list = init_list();
	char c;
	int nb;
	// Remplissage de la liste des frequences
	for (int i = 0; i < len_freq; ++i)
	{
		fread(&c, 1, 1, fd);
		fread(&nb, 4, 1, fd);
		add_freq(c, nb, list);
	}

	head_list *tl;
	tl = Huffman(*list);

	unsigned char buffer[n];
	unsigned char bit_curr;

	node *node = tl->first->n; // On commence a la root de l'arbre

	FILE *fd2;
	fd2 = fopen("decompressed", "w");

	if(fd2 == NULL)
	{
		perror("Error");
		exit(1);
	}

	fread(buffer, 1, n, fd);
	for (int i = 0; i < n; ++i)
	{
		for (bit_curr = 0x80; len && bit_curr; bit_curr >>= 1)
		{
			if(node->type == typeLeaf)
			{
				len--;
				fputc(node->carac, fd2);
				node = tl->first->n; // On a trouve un caractere donc on revient a la root
			}
			if(buffer[i] & bit_curr)
				node = node->n[1];
			else
				node = node->n[0];
		}
	}

	fclose(fd2);
	free_headlist(tl);
	free_list(list);
}