#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Tree{
	char file[1000];
	struct Tree *left;
	struct Tree *right;
}tree;

typedef struct Ramo{
	char title[1000];
	struct Ramo *next; // lista de raizes de árvores.
	struct Tree *root; // raiz da árvore.
}ramo;

typedef struct pacote{
	tree *root;
	char atributo[1000];
}sedex;

void showRamo(ramo *galho){
	ramo *aux=galho;
	while(aux!=NULL){
		printf("%s\n",aux->title);
		aux=aux->next;
	}
}
void showTree(tree *root){
	if(root!=NULL){
		printf("%s\n",root->file);
	}
	else
		return;
	showTree(root->left);
	showTree(root->right);
}
// cria uma nova árvore.
ramo *criaGalho(ramo *galho, char title[1000]){
	ramo *new,*aux = galho;
	new = (ramo*)malloc(sizeof(ramo));
	new->next=NULL;
	new->root=NULL;
	strcpy(new->title,title);
	
	if(galho == NULL){
		galho = new;
		return galho;
	}
	while(aux->next!=NULL){
		aux=aux->next;
	}
	aux->next = new;
	return galho;
}
//encontra raiz da árvore na lista de árvores.
ramo *findTree(ramo *galho,char title[1000]){
	ramo *aux=galho;
	if(galho == NULL)
		return NULL;
	while(aux!=NULL){
		if(strcmp(aux->title,title)==0)
			return aux;
		aux=aux->next;
	}
	return NULL;
}
tree *bstFind(tree *root, char atributo[1000]){
	if(root==NULL){
		return NULL;
	}
	if (strcmp(atributo,root->file)==0){
		return root;
	}
	else if(strcmp(atributo,root->file)<0){
		return bstFind(root->left,atributo);
	}
	else{
		return bstFind(root->right, atributo);
	}
}
tree *criaNo(char atributo[1000]){
	tree *seed;
	seed=(tree*)malloc(sizeof(tree));
	strcpy(seed->file,atributo);
	seed->left = NULL;
	seed->right = NULL;
	return seed;
}
tree *insert(tree *root,char atributo[1000]){
	if(root == NULL){
		root = criaNo(atributo);
		return root;
	}
	else if(strcmp(atributo,root->file) < 0){
		root->left = insert(root->left,atributo);
		return root;
	}
	else{
		root->right = insert(root->right,atributo);	
		return root;
	}
}
sedex removeNoMin(tree *root){
	sedex pac;
	int t,i;
	if(root->left==NULL){
		pac.root = root->right;
		strcpy(pac.atributo,root->file);
		free(root);
		return pac;
	}
	else {
		pac = removeNoMin(root->left);
		root->left = pac.root;
		pac.root = root;		
		return pac;	
	}
}
tree *removeNo(tree *root,char atributo[1000]){
	
	tree *r,*l;
	sedex pac;
	int i,t;
	if(root==NULL){
		return NULL;
	}
	else if(strcmp(atributo,root->file) < 0) {
		root->left = removeNo(root->left, atributo);
		return root;
	}
	else if(strcmp(atributo,root->file) > 0){
		root->right = removeNo(root->right, atributo);
		return root;
	}
	else{
		if(root -> left == NULL){
			r=root->right;
			if(root!=NULL){
				free(root);
			}
			return r;
		}
		else if(root->right == NULL){
			l=root->left;
			if(root!=NULL){
				free(root);
			}
			return l;
		}
		else{
			//printf("ok\n");
			pac = removeNoMin(root->right);
			root->right= pac.root;
			strcpy(root->file,pac.atributo);
			return root;
		}
	}
}
int main (){
	
	// exemplo...
	int i,j,k,l;
	char a='w',b,c;
	char entrada[1000],atualTree[1000],comando[1000];
	ramo *galho=NULL,*raiz; // ligação entre as árvores.
	tree *leaf=NULL; // galhos
	system("clear");
	printf("Titulo para arvore: ");
	scanf(" %s",entrada);
	system("clear");
	strcpy(atualTree,entrada);
	galho = criaGalho(galho,entrada);
	raiz=findTree(galho,entrada);
	while(1){
		printf("Arvore atual [%s]\n\n",atualTree);
		printf("Ecolha um numero.\n");
		printf("1 > criar nova arvore.\n");
		printf("2 > lista de arvores.\n");
		printf("3 \"file\" > adicionar \"file\".\n");
		printf("4 \"file\" > deletar \"file\".\n");
		printf("5 > listar todos os elementos da arvore atual\n");
		printf("6 > exit\n");
		scanf("%d", &l);
		if(l==3 || l==4){
			scanf(" %s",entrada);
			if(l==3)
				raiz->root=insert(raiz->root,entrada);// uso o rais->root pois se colocar só o root ele pode estar iniciado como null, assim o novo ponteiro
			else  // se perde ao ser alocado. pegando o nó do ramo galhos eu tenho acesso direto ao ponteiro da root que aponta para a arvore.
				raiz->root=removeNo(raiz->root,entrada);
			system("clear");
		}
		else if(l==1){
			printf("Titulo para arvore: ");
			scanf(" %s",entrada);
			galho = criaGalho(galho,entrada);
			while(a!='s' && a!='n'){
				printf("Deseja continuar nesta nova arvore? s|n\n");
				scanf(" %c",&a);
				system("clear");
			}
			if(a=='s'){
				strcpy(atualTree,entrada);
				raiz=findTree(galho,entrada);
			}
			a='w';
		}
		else if(l==2){
			system("clear");
			showRamo(galho);
			while(a!='s' && a!='s'){	
				system("clear");
				showRamo(galho);
				printf("Deseja escolher uma arvore? s|n\n");
				scanf(" %c",&a);
			}
			if(a=='y'){
				printf("Digite o nome da arvore: ");
				scanf(" %s",entrada);
				strcpy(atualTree,entrada);
				raiz=findTree(galho,entrada);
			}
			system("clear");
			a='w';	
		}
		else if(l==5){
			system("clear");
			showTree(raiz->root);
		}
		else if(l==6)
			return 0;
	}

	return 0;

}