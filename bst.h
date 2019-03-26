#ifndef BST_H_
#define BST_H_

struct node{
    char *ProductName, *Manufacturer, *ServingSize1Units, *ServingSize2Units, *Date;
    int ProductID;
    double Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, Servings;

    struct node *right_child; // right child
    struct node *left_child; // left child
};

//function to create a node
struct node* new_node(char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings);

struct node* insert(struct node *root, char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings);

//function to find the minimum value in a node
struct node* find_minimum(struct node *root);

struct node* delete(struct node *root, char *ProductName);

void diagnoseBST(struct node *root);

void inorder(struct node *root);

void preorder(struct node *root);

void postorder(struct node *root);

int deleteBST(struct node *root);

//Since you are inserting with DFS you are sending them all on one side essentially just creating a linked list (this is good)
struct node* dfs(struct node *root, struct node *searchresults, char *term, char *searchby);

struct node* search(struct node *root, struct node *searchresults, char *term);

void printNode(struct node *p);

void printSearchResults(struct node *root, int counter);

struct node* selectSearchResults(struct node *p, int counter, int userSelection);

void newEntry(struct node *root, char *name);

#endif