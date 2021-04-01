#ifndef HUFMAN_H
#define HUFMAN_H
// Structures d'arbres et listes d'arbres
typedef enum {typeNode, typeLeaf} typeStruct;

typedef struct node
{
	typeStruct type;
	unsigned int proba;
	union {
		struct node *n[2];
		int carac;
	};
} node;

typedef struct node_list
{
	node *n;
	struct node_list *nxt;
} node_list;

typedef struct head_list
{
	struct node_list *first;
} head_list;

typedef	struct dict
{
	char c;
	char *code;
	int size;
	struct dict *nxt;
} Dict;

typedef	struct head_dict
{
	struct dict *first;
} head_dict;

// Affichage
void print_dict(head_dict *hd);
void affiche_listenodes(head_list *tl);

// Gestion de noeuds
int depth_tree(head_list *ln);
void link(head_list *tl, node *n1, node *n2);

head_list *Huffman(List list);
head_list *init_leafs(List l);
node *create_leafs(int c, unsigned int proba);

node *search_firstnode(head_list *tl);
int nb_nodes(head_list *tl);
void add_node(head_list *tl, node *n);
void remove_node(head_list *tl, node *n);

// Dico
char *val_dict(head_dict *hd, char key);
head_dict *fill_dict(head_list *tl);
void fill_buf(node *n, char dir, int i, head_dict *hd);
void find_code(head_list *tl, head_dict *hd);

void blek(char *str, int size);

// Liberation de memoire
void free_headdict(head_dict *hd);
void free_node(node *root);
void free_headlist(head_list *tl);
void free_nodelist(node_list *ln);

char convert_strbin_to_char(char *str);
void compress(FILE *fd);
void decompress(FILE *fd);

#endif