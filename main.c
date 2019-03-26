#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

int main() {

	struct node* database = new_node("Beascuit", "Let's Get Fiscal", "golden grams", "pieces", 128.10, 123.5, 7, 8.9, 1.0, 1.0, 11553002, "2000-01-01", 0);
	insert(database, "Bacon", "Benjamin Franklin", "golden grams", "pieces", 128.10, 123.5, 7, 8.9, 1.0, 1.0, 11553003, "2000-01-01", 0);
	insert(database, "Wine", "Accounts Playable", "golden grams", "pieces", 128.0, 12.5, 7, 0.9, 1.0, 1.0, 11553004, "2000-01-01", 0);
	insert(database, "Green Beans", "Jennifer Honeycutt", "golden grams", "pieces", 128.10, 123.5, 7, 8.9, 1.90, 1.20, 11553005, "2000-01-01", 0);
	insert(database, "Babel", "Hand in the Cookie Jar Inc.", "golden grams", "pieces", 128.10, 123.5, 7, 8.9, 1.90, 1.20, 11553006, "2000-01-01", 0);

	struct node *currentLog = new_node("NULL", "NULL", "NULL", "NULL", 0, 0, 0, 0, 0, 0, 11553007, "2000-01-01", 0);

	////////////////// User Interface //////////////////
	char *name = (char*) malloc (63*sizeof(char));
	char *crud = (char*) malloc (63*sizeof(char));
	char *input = (char*) malloc (63*sizeof(char));
	char *input2 = (char*) malloc (63*sizeof(char));
	char *input3 = (char*) malloc (63*sizeof(char));
	int inputNum = 0;
	char buffProductID[255],buffProductName[255], buffManufacturer[255], buffEnergy[255], buffCarb[255], buffFat[255], buffProtein[255], buffServingSize1[255], buffServingSize1Units[255], buffServingSize2[255], buffServingSize2Units[255], buffDate[255], buffServings[255];

	printf("Hello! Welcome to your nutirion log! What is your name?\n");
	scanf("%s", name);
	
	
	//Read in the current contents of the log file.
	FILE *logFile;
	strcat(name, ".csv");

	logFile = fopen(name, "r"); 

	//Is the file empty?
	long fsize = 0;
	if(logFile != NULL) 
	{
		// Go to end of the file
		fseek(logFile, 0, SEEK_END); 
		fsize= ftell(logFile);
	}
	//Set the pointer back to the front in order to read each line
	rewind(logFile);

	// //Read in the old entries unless the file is empty
	if(fsize != 0){
		int flag = fscanf(logFile, "%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~\n]%*[\n]", buffProductName, buffManufacturer, buffEnergy, buffCarb, buffFat, buffProtein, buffServingSize1, buffServingSize1Units, buffServingSize2, buffServingSize2Units, buffProductID, buffDate, buffServings);
		while(flag != EOF){
			insert(currentLog, buffProductName, buffManufacturer, buffServingSize1Units, buffServingSize2Units, atof(buffEnergy), atof(buffCarb), atof(buffFat), atof(buffProtein), atof(buffServingSize1), atof(buffServingSize2), atoi(buffProductID), buffDate, atof(buffServings));
			flag = fscanf(logFile, "%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~\n]%*[\n]", buffProductName, buffManufacturer, buffEnergy, buffCarb, buffFat, buffProtein, buffServingSize1, buffServingSize1Units, buffServingSize2, buffServingSize2Units, buffProductID, buffDate, buffServings);
		}
	}

	currentLog = delete(currentLog, "NULL");
	fclose(logFile);

	printf("\nWould you like to 'create', 'retrieve', 'update', or 'delete' a record? (Type the one you would like below or 'quit' to exit.)\n");
	scanf("%s", crud);
	crud = strlwr(crud);

	while(strcmp(crud, "quit")){

		if (strcmp(crud, "create") == 0){
			struct node *searchresultsC = new_node("A", "NULL", "NULL", "NULL", 0, 0, 0, 0, 0, 0, 11553007, "2000-01-01", 0);
			printf("\nEnter the name of the food you would like to search for below:\n");
			scanf("%s", input);
			strcpy(input3, input);
			input = strlwr(input);
			search(currentLog, searchresultsC, input);
			if (searchresultsC->left_child == NULL && searchresultsC->right_child == NULL){
				printf("\nNothing begins with '%s' so a Depth First Search will be used.", 	input3);
				dfs(currentLog, searchresultsC, input, input2);
			}	
			searchresultsC = delete(searchresultsC, "A");

			printf("\nPlease enter the number of the food you would like to add to your log:\n");
			printSearchResults(searchresultsC, 0);
			scanf("%d", &inputNum);
			
			struct node *selectedNodeC = selectSearchResults(searchresultsC, 0, inputNum);
			printf("\nHow many servings did you consume?\n");
			scanf("%lf", &selectedNodeC->Servings);
			
			printf("\nWhat date was this eaten? (enter date in the format 'YYYY-MM-DD')\n");
			//May want to read this in as three integers before translating it into a string that way it can easily be checked for invalid dates.
			scanf("%s", input);
			selectedNodeC->Date = input;
			printf("\n%s has been added to your log.\n", selectedNodeC->ProductName);

			newEntry(selectedNodeC, name);
			insert(currentLog, selectedNodeC->ProductName, selectedNodeC->Manufacturer, selectedNodeC->ServingSize1Units, selectedNodeC->ServingSize2Units, selectedNodeC->Energy, selectedNodeC->Carbs, selectedNodeC->Fat, selectedNodeC->Protein, selectedNodeC->ServingSize1, selectedNodeC->ServingSize2, selectedNodeC->ProductID, selectedNodeC->Date, selectedNodeC->Servings);
			deleteBST(searchresultsC);
		}

		else if (strcmp(crud, "retrieve") == 0){
		
			printf("\nHow would you like to retrieve your data? (Searching by 'date' or 'food')\n");
			scanf("%s", input2);
			input2 = strlwr(input2);

			struct node *searchresultsR = new_node("A", "NULL", "NULL", "NULL", 0, 0, 0, 0, 0, 0, 11553007, "2000-01-01", 0);
			if (strcmp(input2, "food") == 0){
				printf("\nEnter the name of the food in the entry you are searching for:\n");
				scanf("%s", input);
				strcpy(input3, input);
				input = strlwr(input);
				search(currentLog, searchresultsR, input);
				if (searchresultsR->left_child == NULL && searchresultsR->right_child == NULL){
					printf("\nNothing begins with '%s' so a Depth First Search will be used.", input3);
					dfs(currentLog, searchresultsR, input, input2);
				}
			}
			else if (strcmp(input2, "date") == 0){
				printf("\nEnter the date of the entry you are searching for:\n");
				scanf("%s", input);
				dfs(currentLog, searchresultsR, strlwr(input), input2);
			}

			searchresultsR = delete(searchresultsR, "A");

			printf("\nPlease enter the number of the entry you would like to view:\n");
			printSearchResults(searchresultsR, 0);
			scanf("%d", &inputNum);

			struct node *selectedNodeR = selectSearchResults(searchresultsR, 0, inputNum);
			printf("Date: %s\n", selectedNodeR->Date);
			printf("Servings: %.2f\n", selectedNodeR->Servings);
			deleteBST(searchresultsR);
		}


		// printf("\n~~~%d~~~\n", strncmp("Wine", "Wineday", 3));
		// printf("\n~~~%ld~~~\n", strlen("Wine"));

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// else if (strcmp(crud, "update") == 0){
		// 	printf("Update data from their log.");
		// }
		// else if (strcmp(crud, "delete") == 0){
		// 	printf("Delete data from their log.");
		// }
		// else {
		// 	printf("Create an error catch here becasue the command is not recognized. String you entered is: %s", crud);
		// }

		printf("\nWould you like to 'create', 'retrieve', 'update', or 'delete' a record? (Type the one you would like below or 'quit' to exit.)\n");
		scanf("%s", crud);
		crud = strlwr(crud);
	}



	//Prompt for who is using the program, this will affect which log will be accessed. Or if it is a new person.
		//Read all of the logs that are in the current folder by name and then the user can select if they are present or if they are new

	//While (input != 'quit')
		// Would you like to add (type 'add'), delete (type 'del'), review (type 'rev') or update (type 'upd') an entry in your nutritional diary? (If you are finished type 'quit')

		//If structure to use each of the CRUD features.


	// ////////////////// Read in the File //////////////////

	// printf("Loading nutritional data...");

	// FILE *fp;
	

	// fp = fopen("food_nutrient_db.csv", "r"); //Open the nutritional database file.

	// // For - all lines, read in these data points
	// 	//Read them into objects that are part of a linked list?

	// for (int i = 0; i < 2000; i++){
	
	// 	fscanf(fp, "%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~]%*[~]%[^~\n]%*[\n]", buffProductID,buffProductName, buffManufacturer, buffEnergy, buffCarb, buffFat, buffProtein, buffServingSize1, buffServingSize1Units, buffServingSize2, buffServingSize2Units);
	// 	printf("%s\t", buffProductID);
	// }
	

	// fclose(fp); //Close the nutritional database file.



	return 0;
}