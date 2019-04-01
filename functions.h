#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

struct node{
    char *ProductName, *Manufacturer, *ServingSize1Units, *ServingSize2Units, *Date;
    int ProductID;
    double Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, Servings;

    struct node *right_child; // right child
    struct node *left_child; // left child
};

///// Taking Input /////

char *getInput(int MAXSIZE);
char * strtok_single (char * str, char const * delims);
char * strlwr(char * string);

///// Binary Search Tree Functionality /////

void printNode(struct node *p, char *use);
struct node* insert(struct node *root, char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings);
struct node* update(struct node *root, char *ProductName, char *Date, double Servings, char *newDate, double newServings);
struct node* find_minimum(struct node *root);
struct node* delete(struct node *root, char *ProductName, char *Date, double Servings);
int deleteBST(struct node *root);
void writeFromBST(struct node *root, FILE *fp);
struct node *readIntoBST(struct node *tree, char *filename, char* reading);

///// Search Functions /////

struct node* dfs(struct node *root, struct node *searchresults, char *term, char *searchby);
struct node* search(struct node *root, struct node *searchresults, char *term);
int printOptions(struct node *root, int counter, char *use, int logProductName, int logManufacturer, int logDate, int logServings, int dbProductName, int dbManufacturer);
int selectOption(struct node *p, struct node *selected, int counter, int userSelection);

///// Validate and Error Check Various Types of Input /////

char * validateDate(char *date);
int validateNum (char * numStr);
double validateFloat (char * numStr);
char * validateBinary(char * input, char *choice1, char *choice2);
int validateSelection(int input, int max);

///// Manage Settings /////

int readSettings(char *filename, int *logProductName, int *logManufacturer, int *logDate, int *logServings, int *dbProductName, int *dbManufacturer);
int updateSettings(char *filename, int *logProductName, int *logManufacturer, int *logDate, int *logServings, int *dbProductName, int *dbManufacturer);

#endif