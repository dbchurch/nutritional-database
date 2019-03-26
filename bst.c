#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

///// Binary Search Tree Functionatlity /////

//function to create a node
struct node* new_node(char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings){
    struct node *p = malloc(sizeof(struct node));
    p->ProductName = (char*) malloc (63*sizeof(char));
    strcpy(p->ProductName, ProductName);
    p->Manufacturer = (char*) malloc (63*sizeof(char));
    strcpy(p->Manufacturer, Manufacturer);
    p->ServingSize1Units = (char*) malloc (63*sizeof(char));
    strcpy(p->ServingSize1Units, ServingSize1Units);
    p->ServingSize2Units = (char*) malloc (63*sizeof(char));
    strcpy(p->ServingSize2Units, ServingSize2Units);
    p->Energy = Energy;
    p->Carbs = Carbs;
    p->Fat = Fat;
    p->Protein = Protein;
    p->ServingSize1 = ServingSize1;
    p->ServingSize2 = ServingSize2;
    p->ProductID = ProductID;
    p->Date = (char*) malloc (63*sizeof(char));
    strcpy(p->Date, Date);
    p->Servings = Servings;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings){
    //searching for the place to insert
    if(root==NULL)
    {    
    	return new_node(ProductName, Manufacturer, ServingSize1Units, ServingSize2Units, Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, ProductID, Date, Servings);
    }
    else if(0 > strcmp(ProductName, root->ProductName))
    { // x is smaller should be inserted to left
        root->left_child = insert(root->left_child, ProductName, Manufacturer, ServingSize1Units, ServingSize2Units, Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, ProductID, Date, Servings);
    }

    else
    { // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, ProductName, Manufacturer, ServingSize1Units, ServingSize2Units, Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, ProductID, Date, Servings);
    }
    return root;
}

//function to find the minimum value in a node
struct node* find_minimum(struct node *root){
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}

struct node* delete(struct node *root, char *ProductName){
    //searching for the item to be deleted
    if(root==NULL){
    	//printf("Root == NULL\n");
        return NULL;
    }
    if (0 < strcmp(ProductName, root->ProductName)){
    	//printf("0 < strcmp(ProductName, root->ProductName)\n");
        root->right_child = delete(root->right_child, ProductName);
    }
    else if(0 > strcmp(ProductName, root->ProductName)){
    	//printf("0 > strcmp(ProductName, root->ProductName)\n");
        root->left_child = delete(root->left_child, ProductName);
    }
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
        	//printf("No Children\n");
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
        	//("One Child\n");
            struct node *temp = malloc(sizeof(struct node));
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            //printf("before free");
            free(root);
            //printf("after free");
            return temp;
        }

        //Two Children
        else
        {
        	//printf("Two Children\n");
            struct node *temp = find_minimum(root->right_child);
            root->ProductName = temp->ProductName;
            root->Manufacturer = temp->Manufacturer;
            root->ServingSize1Units = temp->ServingSize1Units;
            root->ServingSize2Units = temp->ServingSize2Units;
            root->Energy = temp->Energy;
            root->Carbs = temp->Carbs;
            root->Fat = temp->Fat;
            root->Protein = temp->Protein;
            root->ServingSize1 = temp->ServingSize1;
            root->ServingSize2 = temp->ServingSize2;
            root->ProductID = temp->ProductID;
            root->Date = temp->Date;
            root->Servings = temp->Servings;
            root->right_child = delete(root->right_child, temp->ProductName);
        }
    }
    return root;
}

void diagnoseBST(struct node *root){
    printf("\n\nIn: ");
    inorder(root);
    printf("\nPre: ");
    preorder(root);
    printf("\nPost: ");
    postorder(root);
    printf("\n\n");
}

void inorder(struct node *root){
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %s,%s ", root->ProductName, root->Date); // printing ProductName at root
        inorder(root->right_child);// visiting right child
    }
}

void preorder(struct node *root){
    if(root!=NULL) // checking if the root is not null
    {
        printf(" %s,%s ", root->ProductName, root->Date);
        preorder(root->left_child); // visiting left child
        preorder(root->right_child);// visiting right child
    }
}

void postorder(struct node *root){
    if(root!=NULL) // checking if the root is not null
    {
        postorder(root->left_child); // visiting left child 
        postorder(root->right_child);// visiting right child
        printf(" %s,%s ", root->ProductName, root->Date);// printing ProductName at root
    }
}

int deleteBST(struct node *root){
    if(root != NULL) // checking if the root is not null
    {
	    deleteBST(root->left_child); // visiting left child
	    deleteBST(root->right_child);// visiting right child
	    free(root); // printing ProductName at root
    }
    return 0;
}

//Since you are inserting with DFS you are sending them all on one side essentially just creating a linked list (this is good)
struct node* dfs(struct node *root, struct node *searchresults, char *term, char *searchby){
    char *tempName = (char*) malloc (63*sizeof(char));
    if(root!=NULL) // checking if the root is not null
    {
    	if(strcmp(searchby, "food") == 0){
	        dfs(root->left_child, searchresults, term, searchby); // visiting left child
            strcpy(tempName, root->ProductName);
	        if (strstr(strlwr(tempName), term) != NULL){
	        	insert(searchresults, root->ProductName, root->Manufacturer, root->ServingSize1Units, root->ServingSize2Units, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize2, root->ProductID, root->Date, root->Servings);
	        }
	        dfs(root->right_child, searchresults, term, searchby);// visiting right child
	    }
	    else if(strcmp(searchby, "date") == 0){
	        dfs(root->left_child, searchresults, term, searchby); // visiting left child
            if (strstr(root->Date, term) != NULL){
                insert(searchresults, root->ProductName, root->Manufacturer, root->ServingSize1Units, root->ServingSize2Units, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize2, root->ProductID, root->Date, root->Servings);
	        }
	        dfs(root->right_child, searchresults, term, searchby);// visiting right child
	    }
    }
    free(tempName);
    return searchresults;
}

struct node* search(struct node *root, struct node *searchresults, char *term){
    if(root==NULL)
    {    
        return searchresults;
    }
    else if(0 > strncmp(root->ProductName, term, strlen(term)))
    { // x is smaller should be inserted to left
        search(root->left_child, searchresults, term);
    }
    else
    { // x is greater. Should be inserted to right
        search(root->right_child, searchresults, term);
        if(0 == strncmp(root->ProductName, term, strlen(term))){
            insert(searchresults, root->ProductName, root->Manufacturer, root->ServingSize1Units, root->ServingSize2Units, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize2, root->ProductID, root->Date, root->Servings);
        }
    }
    return searchresults;
}

void printNode(struct node *p){
	printf("Product Name: %s\n", p->ProductName);
    printf("Manufacturer: %s\n",p->Manufacturer);
    printf("Serving Size: %.2f %s\n",p->ServingSize1, p->ServingSize1Units);
    printf("Serving Size 2: %.2f %s\n",p->ServingSize2, p->ServingSize2Units);
    printf("Calories: %.2f\n",p->Energy);
    printf("Carbs: %.2f\n",p->Carbs);
    printf("Fat: %.2f\n",p->Fat);
    printf("Protein: %.2f\n",p->Protein);
    printf("Product ID: %d\n", p->ProductID);
    printf("Date: %s\n", p->Date);

    if(p->left_child==NULL && p->right_child==NULL)
        {
        	printf("No Children");
        }

        //One Child
        else if(p->left_child==NULL || p->right_child==NULL)
        {
        	printf("One Child\n");
        	if(p->left_child==NULL)
                printf("No left child\n");
            if (p->right_child == NULL)
                printf("No right child\n");
        }

        //Two Children
        else
        {
        	printf("Two Children");
        }
}

void printSearchResults(struct node *root, int counter){
	if(root!=NULL) 
    {
    	counter = counter + 1;
        printf("%d. %s \n", counter, root->ProductName); 
        printSearchResults(root->right_child, counter);
    }
}

struct node* selectSearchResults(struct node *p, int counter, int userSelection){
	if (p != NULL)
	{
		counter = counter + 1;
		if (counter == userSelection)
		{
			printf("\nYou selected:\n\n");
			printf("Product Name: %s\n", p->ProductName);
		    printf("Manufacturer: %s\n",p->Manufacturer);
		    printf("Serving Size: %.2f %s\n",p->ServingSize1, p->ServingSize1Units);
		    printf("Serving Size 2: %.2f %s\n",p->ServingSize2, p->ServingSize2Units);
		    printf("Calories: %.2f\n",p->Energy);
		    printf("Carbs: %.2f\n",p->Carbs);
		    printf("Fat: %.2f\n",p->Fat);
		    printf("Protein: %.2f\n",p->Protein);
		    return p;
		}
		p = selectSearchResults(p->right_child, counter, userSelection);
	}
	return p;
}

void newEntry(struct node *root, char *name){
	FILE *fp;

	fp = fopen(name, "a"); 

	fprintf(fp, "%s~%s~%f~%f~%f~%f~%f~%s~%f~%s~%d~%s~%f\n", root->ProductName, root->Manufacturer, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize1Units, root->ServingSize2, root->ServingSize2Units, root->ProductID, root->Date, root->Servings);

	fclose(fp);
}