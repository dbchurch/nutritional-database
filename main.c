#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define NUMLENGTH 15
#define NAMELENGTH 255
#define SSLENGTH 31
#define LINELENGTH 511


int main() {

	char *name = (char*) malloc (NAMELENGTH*sizeof(char));
	char *namelog = (char*) malloc (NAMELENGTH*sizeof(char));
	char *namesettings = (char*) malloc (NAMELENGTH*sizeof(char));
	char *crud = (char*) malloc (NAMELENGTH*sizeof(char));
	char *binaryselection = (char*) malloc (NAMELENGTH*sizeof(char));
	char *searchterm = (char*) malloc (NAMELENGTH*sizeof(char));
	int selectionNum = 0;
	int maxselect = 0;
	double floatNum = 0;

	int logProductName = 40, logManufacturer = 20, logDate = 10, logServings = 10, dbProductName = 60, dbManufacturer = 30;

	printf("Loading nutritional data...\n");

	struct node *database = NULL;
	database = readIntoBST(database, "food_database.csv", "db");

	printf("\nHello! Welcome to your nutirion log! \nWhat is your name? (This will determine which log your data is stored to and retrieved from.)\n");
	name = getInput(NAMELENGTH);
	strncpy(namelog, name, NAMELENGTH);
	strncpy(namesettings, name, NAMELENGTH);
	namelog = strcat(strlwr(namelog), ".log");
	namesettings = strcat(strlwr(namesettings), ".settings");

	readSettings(namesettings, &logProductName, &logManufacturer, &logDate, &logServings, &dbProductName, &dbManufacturer);

	struct node *currentLog = NULL;
	currentLog = readIntoBST(currentLog, namelog, "log");

	printf("\nWould you like to 'create', 'retrieve', 'update', or 'delete' a record? (Type the one you would like below, 'quit' to exit or 'change settings' to update the print settings.)\n");
	crud = strlwr(getInput(NAMELENGTH));

	while(strncmp(crud, "quit", NAMELENGTH)){
		struct node *searchresults = NULL;

		if (strncmp(crud, "create", NAMELENGTH) == 0){
			
			printf("\nEnter the name of the food you would like to search for below:\n");
			
			searchterm = strlwr(getInput(NAMELENGTH));

			searchresults = search(database, searchresults, searchterm);

			if (searchresults == NULL){
				//Nothing starts with the searched string so a depth first search will be used.
				searchresults = dfs(database, searchresults, searchterm, "food");
			}

			if (searchresults == NULL){
				printf("\nThere is no food in the database with that name.\n");
			}
			else {
				printf("\nPlease enter the number of the food you would like to add to your log:\n");

				maxselect = printOptions(searchresults, 0, "db", logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
				selectionNum = validateSelection(validateNum(getInput(NAMELENGTH)), maxselect);

				struct node *selectedNode = malloc(sizeof(struct node));
				selectOption(searchresults, selectedNode, 0, selectionNum);
				printNode(selectedNode, "db");
				printf("\nHow many servings did you consume?\n");

				selectedNode->Servings = validateFloat(getInput(NAMELENGTH));
				
				printf("\nWhat date was this eaten? (enter date in the format 'YYYY-MM-DD')\n");
				selectedNode->Date = validateDate(getInput(NAMELENGTH));

				printf("\n%s has been added to your log.\n", selectedNode->ProductName);

				currentLog = insert(currentLog, selectedNode->ProductName, selectedNode->Manufacturer, selectedNode->ServingSize1Units, selectedNode->ServingSize2Units, selectedNode->Energy * selectedNode->Servings, selectedNode->Carbs * selectedNode->Servings, selectedNode->Fat * selectedNode->Servings, selectedNode->Protein * selectedNode->Servings, selectedNode->ServingSize1, selectedNode->ServingSize2, selectedNode->ProductID, selectedNode->Date, selectedNode->Servings);

			}
		}

		else if ((strncmp(crud, "retrieve", NAMELENGTH) == 0) && currentLog != NULL){
		
			printf("\nHow would you like to retrieve your data? Searching by 'food' or 'date'? (Enter 'food' or 'date'.)\n");
			 
			binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "food", "date");

			if (strncmp(binaryselection, "food", NAMELENGTH) == 0){
				printf("\nEnter the name of the food in the entry you are searching for:\n");
				searchterm = strlwr(getInput(NAMELENGTH));

				searchresults = search(currentLog, searchresults, searchterm);
				if (searchresults == NULL){
					//Nothing starts with the searched string so a depth first search will be used.
					searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
				}
			}
			else if (strncmp(binaryselection, "date", NAMELENGTH) == 0){
				printf("\nEnter the date of the entry you are searching for:\n");
				searchterm = validateDate(getInput(NAMELENGTH));
				searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
			}

			if (searchresults == NULL){
				printf("\nThere is no entry in the log '%s' with that %s.\n", namelog, binaryselection);
			}
			else {
				
				maxselect = printOptions(searchresults, 0, "log", logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
				printf("\nPlease enter the number of the entry you would like to view:\n");
				selectionNum = validateSelection(validateNum(getInput(NAMELENGTH)), maxselect);

				struct node *selectedNode = malloc(sizeof(struct node));
				selectOption(searchresults, selectedNode, 0, selectionNum);
				printNode(selectedNode, "log");
			}	
		}

		else if ((strncmp(crud, "update", NAMELENGTH) == 0) && currentLog != NULL){
			printf("\nHow would you like to find the entry you would like to update? By 'food' or 'date'? (Enter 'food' or 'date'.)\n");

			binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "food", "date");

			if (strncmp(binaryselection, "food", NAMELENGTH) == 0){
				printf("\nEnter the name of the food in the entry you wish to update:\n");
				searchterm = strlwr(getInput(NAMELENGTH));

				searchresults = search(currentLog, searchresults, searchterm);
				if (searchresults == NULL){
					//Nothing starts with the searched string so a depth first search will be used.
					searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
				}
			}
			else if (strncmp(binaryselection, "date", NAMELENGTH) == 0){
				printf("\nEnter the date of the entry you would like to update:\n");
				searchterm = validateDate(getInput(NAMELENGTH));
				 
				searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
			}

			if (searchresults == NULL){
				printf("\nThere is no entry in the log '%s' with that %s.\n", namelog, binaryselection);
			}
			else {
				printf("\nPlease enter the number of the entry you would like to update:\n");
				maxselect = printOptions(searchresults, 0, "log", logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
				selectionNum = validateSelection(validateNum(getInput(NAMELENGTH)), maxselect);

				struct node *selectedNode = malloc(sizeof(struct node));
				selectOption(searchresults, selectedNode, 0, selectionNum);
				printNode(selectedNode, "log");

				printf("\nWould you like to update the 'date' or the number of 'servings'? (Enter 'date' or 'servings'.)\n");
				binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "date", "servings");

				if(strncmp(binaryselection, "date", NAMELENGTH) == 0){
					printf("\nWhat would you like the updated date to be? Please enter in the format of 'YYYY-MM-DD'.\n");
					searchterm = validateDate(getInput(NAMELENGTH));
					 
					update(currentLog, selectedNode->ProductName, selectedNode->Date, selectedNode->Servings, searchterm, selectedNode->Servings);
				}
				else if (strncmp(binaryselection, "servings", NAMELENGTH) == 0){
					printf("\nWhat would you like the updated amount of servings to be?\n");
					floatNum = validateFloat(getInput(NAMELENGTH));

					update(currentLog, selectedNode->ProductName, selectedNode->Date, selectedNode->Servings, selectedNode->Date, floatNum);
				}
			}
		}

		else if ((strncmp(crud, "delete", NAMELENGTH) == 0) && currentLog != NULL){

			printf("\nHow would you like to find the entry you would like to delete? By 'food' or 'date'? (Enter 'food' or 'date'.)\n");
			binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "food", "date");

			if (strncmp(binaryselection, "food", NAMELENGTH) == 0){
				printf("\nEnter the name of the food in the entry you wish to delete:\n");
				searchterm = strlwr(getInput(NAMELENGTH));

				searchresults = search(currentLog, searchresults, searchterm);
				if (searchresults == NULL){
					//Nothing starts with the searched string so a depth first search will be used.
					searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
				}
			}
			else if (strncmp(binaryselection, "date", NAMELENGTH) == 0){
				printf("\nEnter the date of the entry you are searching for:\n");
				searchterm = getInput(NAMELENGTH);
				 
				searchresults = dfs(currentLog, searchresults, searchterm, binaryselection);
			}

			if (searchresults == NULL){
				printf("\nThere is no entry in the log '%s' with that %s.\n", namelog, binaryselection);
			}
			else {
				printf("\nPlease enter the number of the entry you would like to delete:\n");
				maxselect = printOptions(searchresults, 0, "log", logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
				selectionNum = validateSelection(validateNum(getInput(NAMELENGTH)), maxselect);

				struct node *selectedNode = malloc(sizeof(struct node));
				selectOption(searchresults, selectedNode, 0, selectionNum);

				printf("\nThe entry shown below has been deleted:\n");
				printNode(selectedNode, "log");

				currentLog = delete(currentLog, selectedNode->ProductName, selectedNode->Date, selectedNode->Servings);
	
			}


		}

		else if (strncmp(crud, "change settings", NAMELENGTH) == 0){
			printf("\nHere you can change the settings for how the log table and database table are presented when searching.\n");
			printf("\nWould you like to update how the 'log' or 'database' is presented? (Enter 'log' or 'database'.)\n");
			binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "database", "log");
			if(strncmp(binaryselection, "log", NAMELENGTH) == 0){
				printf("\nWould you like to update the width of the 'product name' or  'manufacturer'? (Enter 'product name' or 'manufacturer'.)\n");
				binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "product name", "manufacturer");
				if(strncmp(binaryselection, "product name", NAMELENGTH) == 0){
					printf("\nWhat would you like to update the table width of the product name to?\n");
					logProductName = validateNum(getInput(NUMLENGTH)); 
				}
				else if(strncmp(binaryselection, "manufacturer", NAMELENGTH) == 0){
					printf("\nWhat would you like to update the table width of the manufacturer to?\n");
					logManufacturer = validateNum(getInput(NUMLENGTH)); 
				}
			}
			else if (strncmp(binaryselection, "database", NAMELENGTH) == 0){
				printf("\nWould you like to update the width of the 'product name' or  'manufacturer'? (Enter 'product name' or 'manufacturer'.)\n");
				binaryselection = validateBinary(strlwr(getInput(NAMELENGTH)), "product name", "manufacturer");
				if(strncmp(binaryselection, "product name", NAMELENGTH) == 0){
					printf("\nWhat would you like to update the table width of the product name to?\n");
					dbProductName = validateNum(getInput(NUMLENGTH)); 
				}
				else if(strncmp(binaryselection, "manufacturer", NAMELENGTH) == 0){
					printf("\nWhat would you like to update the table width of the manufacturer to?\n");
					dbManufacturer = validateNum(getInput(NUMLENGTH)); 
				}
			}
			updateSettings(namesettings, &logProductName, &logManufacturer, &logDate, &logServings, &dbProductName, &dbManufacturer);
		}

		else {
			if (currentLog == NULL){
				printf("\nThe log is empty, so 'create' is currently the only available functinality.\n");
			}
			else {
				printf("\n%s is not a valid input.\n", crud);
			}
		}

		//Free all the search results tree after each run through the CRUD system
		deleteBST(searchresults);

		printf("\nWould you like to 'create', 'retrieve', 'update', or 'delete' a record? (Type the one you would like below, 'quit' to exit or 'change settings' to update the print settings.)\n");
		crud = strlwr(getInput(NAMELENGTH));
	}

	//Before the log is written to at the end the old log is deleted ensuring that a clean write will be made without any left over data from an older version
	remove(namelog);

	FILE *Log;
    Log = fopen(namelog, "ab+"); 
	writeFromBST(currentLog, Log);
	fclose(Log);

	return 0;
}