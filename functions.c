#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "functions.h"

#define NUMLENGTH 15
#define NAMELENGTH 255
#define SSLENGTH 31
#define LINELENGTH 511


///// Taking Input /////

char *getInput(int MAXSIZE){
    //A custom input function was created to prevent the user from overflowing the standard input. This function limits the user to a certain length that cannot be surpassed thus preventing said overflow.
    char *input = (char*) malloc (MAXSIZE*sizeof(char));
    int ch,valid = 0, digits = 0, alpha = 0;
    while(!valid){
        if(fgets(input, MAXSIZE, stdin)){
            digits = 0;
            alpha = 0;
            //The comparison between alphanumeric and numeric characters allows the program to determine what is good and what is bad input which helps exclude possible errors from things such as arrow key presses or backspaces.
            for(int i = 0; i < strlen(input); i++){
                if (isdigit(input[i])){
                    digits++;
                }
                else if (isalpha(input[i]) || input[i] == 46 || input[i] == 45 || input[i] == 32){
                    alpha++;
                }
            }
            if (NULL == strchr(input, '\n')){
                printf("\n%d characters is the maximum that can be entered here. To continue, please enter a string that matches these constraints.\n", MAXSIZE);
                // Eat characters until we get the newline
                while ((ch = getchar()) != '\n');
            }
            else if (strlen(input) == 1){
                printf("\nNothing was input, please enter the appropriate input.\n");
            }
            else if (strlen(input) != (alpha + digits + 1)){
                printf("\nHitting the arrow keys or backspace repeatedly may cause issues or the use of characters that are not either numbers or alphanumeric. Please try again.\n");
            }
            else {
                input[strcspn(input, "\n")] = 0;
                valid = 1;
            }
        }
    }
    return input;
}

char *strtok_single (char * str, char const * delims){
  // strtok has trouble handling multiple delimeters in a row. This code was taken and modified from a Stack Exchanage post the link to which can be found in the readme.md.
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return "";

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }

  return ret;
}

char *strlwr(char * string){
    //The strlwr function is not standard in c11 so it was necessary to make my own.
    for (int i = 0; i < strlen(string); i++){
        string[i] = tolower(string[i]);
    }
    return string;
}


///// Binary Search Tree Functionatlity /////

void printNode(struct node *p, char *use){
    //Prints the nodes when they are created, retrieved, updated, or deleted.
    if (p != NULL){
        printf("\nProduct Name: %s\n", p->ProductName);
        printf("Manufacturer: %s\n",p->Manufacturer);
        printf("Serving Size: %.2f %s\n",p->ServingSize1, p->ServingSize1Units);
        printf("Serving Size 2: %.2f %s\n",p->ServingSize2, p->ServingSize2Units);
        printf("Calories: %.2f\n",p->Energy);
        printf("Carbs: %.2f g\n",p->Carbs);
        printf("Fat: %.2f g\n",p->Fat);
        printf("Protein: %.2f g\n",p->Protein);
        if(strncmp(use, "log", NAMELENGTH) == 0){
            printf("Date Consumed: %s\n", p->Date);
            printf("Servings Consumed: %.2f\n", p->Servings);
        }
    }
}

struct node* insert(struct node *root, char *ProductName, char *Manufacturer, char *ServingSize1Units, char *ServingSize2Units, double Energy, double Carbs, double Fat, double Protein, double ServingSize1, double ServingSize2, int ProductID, char *Date, double Servings){
    
    //searching for the place to insert
    if(root==NULL)
    {   
        //Create a new node if root == NULL 
        root = malloc(sizeof(struct node));

        root->ProductName = (char*) malloc (NAMELENGTH*sizeof(char));
        strncpy(root->ProductName, ProductName, NAMELENGTH);

        root->Manufacturer = (char*) malloc (NAMELENGTH*sizeof(char));
        strncpy(root->Manufacturer, Manufacturer, NAMELENGTH);

        root->ServingSize1Units = (char*) malloc (SSLENGTH*sizeof(char));
        strncpy(root->ServingSize1Units, ServingSize1Units, SSLENGTH);
        
        root->ServingSize2Units = (char*) malloc (SSLENGTH*sizeof(char));
        strncpy(root->ServingSize2Units, ServingSize2Units, SSLENGTH);

        root->Date = (char*) malloc (NUMLENGTH*sizeof(char));
        strncpy(root->Date, Date, NUMLENGTH);

        root->Energy = Energy;
        root->Carbs = Carbs;
        root->Fat = Fat;
        root->Protein = Protein;
        root->ServingSize1 = ServingSize1;
        root->ServingSize2 = ServingSize2;
        root->ProductID = ProductID;

        root->Servings = Servings;
        root->left_child = NULL;
        root->right_child = NULL;

        return root;

    }
    else if(0 > strncmp(ProductName, root->ProductName, NAMELENGTH))
    { // The input is smaller so it should be to the left
        root->left_child = insert(root->left_child, ProductName, Manufacturer, ServingSize1Units, ServingSize2Units, Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, ProductID, Date, Servings);
    }

    else
    { // The input is larger so it should be to the right
        root->right_child = insert(root->right_child, ProductName, Manufacturer, ServingSize1Units, ServingSize2Units, Energy, Carbs, Fat, Protein, ServingSize1, ServingSize2, ProductID, Date, Servings);
    }
    return root;
}

struct node* update(struct node *root, char *ProductName, char *Date, double Servings, char *newDate, double newServings){
    //searching for the item to be deleted
    if(root==NULL){
        return NULL;
    }

    if (0 < strncmp(ProductName, root->ProductName, NAMELENGTH)){
        // The input is larger so it should be input to the right
        update(root->right_child, ProductName, Date, Servings, newDate, newServings);
    }
    else if(0 > strncmp(ProductName, root->ProductName, NAMELENGTH)){
        // The input is smaller so it should be input to the left
        update(root->left_child, ProductName, Date, Servings, newDate, newServings);
    }
    else
    {   // The node must have the correct name but must also have the correct date and number of servings because there may be multiple entries with the same name.
        if (strncmp(Date, root->Date, NUMLENGTH) == 0 && Servings == root->Servings ){
            strncpy(root->Date, newDate, NUMLENGTH);
            root->Servings = newServings;
            root->Energy = root->Energy * newServings/Servings;
            root->Carbs = root->Carbs * newServings/Servings;
            root->Protein = root->Protein * newServings/Servings;
            root->Fat = root->Fat * newServings/Servings;
            printf("\nThe node has been updated to:\n");
            printNode(root, "log");
        }
        else {
            // Entries that have the same name are inserted to the right of the last one
            update(root->right_child, ProductName, Date, Servings, newDate, newServings);
        }
    }
    return root;
}

struct node* find_minimum(struct node *root){
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // The smallest node will not have a left chile
        return find_minimum(root->left_child); // The farthest left node will be the smallest
    return root;
}

struct node* delete(struct node *root, char *ProductName, char *Date, double Servings){
    //searching for the item to be deleted
    if(root==NULL){
        return NULL;
    }
    if (0 < strncmp(ProductName, root->ProductName, NAMELENGTH)){
        // The input is larger so it should be to the right
        root->right_child = delete(root->right_child, ProductName, Date, Servings);
    }
    else if(0 > strncmp(ProductName, root->ProductName, NAMELENGTH)){
        // The input is smaller so it should be to the left
        root->left_child = delete(root->left_child, ProductName, Date, Servings);
    }
    else
    {
        if (strncmp(Date, root->Date, NUMLENGTH) == 0 && Servings == root->Servings ){
            //No Children - The root is NULL.
            if(root->left_child==NULL && root->right_child==NULL)
            {
                free(root);
                return NULL;
            }

            //One Child - The child becomes the root.
            else if(root->left_child==NULL || root->right_child==NULL)
            {
                struct node *temp = malloc(sizeof(struct node));
                if(root->left_child==NULL){
                    temp = root->right_child;
                }
                else {
                    temp = root->left_child;
                }
                free(root);
                return temp;
            }

            //Two Children - The smallest sub-child becomes the root.
            else
            {

                struct node *temp = malloc(sizeof(struct node));
                temp = find_minimum(root->right_child);
                strncpy(root->ProductName, temp->ProductName, NAMELENGTH);
                strncpy(root->Manufacturer, temp->Manufacturer, NAMELENGTH);
                strncpy(root->ServingSize1Units, temp->ServingSize1Units, NAMELENGTH);
                strncpy(root->ServingSize2Units, temp->ServingSize2Units, NAMELENGTH);
                root->Energy = temp->Energy;
                root->Carbs = temp->Carbs;
                root->Fat = temp->Fat;
                root->Protein = temp->Protein;
                root->ServingSize1 = temp->ServingSize1;
                root->ServingSize2 = temp->ServingSize2;
                root->ProductID = temp->ProductID;
                strncpy(root->Date, temp->Date, NAMELENGTH);
                root->Servings = temp->Servings;
                root->right_child = delete(root->right_child, temp->ProductName, Date, Servings);
                free(temp);
            }
        }
        else {
            //If it is the correct name but not the correct entry we must continue down the right tree.
            root->right_child = delete(root->right_child, ProductName, Date, Servings);
        }

    }
    return root;
}

int deleteBST(struct node *root){
    //Easy was to help clean out memory by deleting old search trees when they are no longer needed.
    if(root != NULL)
    {
        deleteBST(root->left_child);
        deleteBST(root->right_child);
        free(root); // Freeing the parent of the children last
    }
    return 0;
}

void writeFromBST(struct node *root, FILE *fp){
    // The function used to write to the log file.
    if(root!=NULL)
    {
        writeFromBST(root->left_child, fp);
        fprintf(fp, "%d~%s~%s~%f~%f~%f~%f~%f~%s~%f~%s~%s~%f\n", root->ProductID, root->ProductName, root->Manufacturer, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize1Units, root->ServingSize2, root->ServingSize2Units, root->Date, root->Servings);
        writeFromBST(root->right_child, fp);
    }
}

struct node *readIntoBST(struct node *tree, char *filename, char* reading){
    char *buffProductID = (char*) malloc (NUMLENGTH*sizeof(char)),*buffProductName = (char*) malloc (NAMELENGTH*sizeof(char)), *buffManufacturer = (char*) malloc (NAMELENGTH*sizeof(char)), *buffEnergy = (char*) malloc (NUMLENGTH*sizeof(char)),*buffCarb = (char*) malloc (NUMLENGTH*sizeof(char)), *buffFat = (char*) malloc (NUMLENGTH*sizeof(char)), *buffProtein = (char*) malloc (NUMLENGTH*sizeof(char)), *buffServingSize1 = (char*) malloc (NUMLENGTH*sizeof(char)), *buffServingSize1Units = (char*) malloc (SSLENGTH*sizeof(char)), *buffServingSize2 = (char*) malloc (NUMLENGTH*sizeof(char)), *buffServingSize2Units = (char*) malloc (SSLENGTH*sizeof(char)), *buffDate = (char*) malloc (NUMLENGTH*sizeof(char)), *buffServings = (char*) malloc (NUMLENGTH*sizeof(char));

    FILE *fp;

    if (strncmp(reading, "log", NAMELENGTH) == 0){
        fp = fopen(filename, "ab+");
        rewind(fp); //ab+ opens the file and points to the end, rewind it to the top
    }
    else {
        fp = fopen(filename, "r");
    }

    char *lineDB = (char*) malloc (LINELENGTH*sizeof(char));
    char *nullCheck = (char*) malloc (NUMLENGTH*sizeof(char));

    double nutrientScale; //The Energy, Carb, Fat, and Protein data is per 100 millileters/grams so a conversion will be necessary to accurately reflect the amount of Energy, Carbs, Fat, and protein in a serving.

    int flagDB = fscanf(fp, "%[^\n]%*[\n]", lineDB);
    while(flagDB != EOF){
        //Using a modified str_tok to split up the data by the '~' delimeter.
        strncpy(buffProductID, strtok_single(lineDB, "~"), NUMLENGTH);
        strncpy(buffProductName, strtok_single(NULL, "~"), NAMELENGTH);
        strncpy(buffManufacturer,strtok_single(NULL, "~"),NAMELENGTH);
        strncpy(buffEnergy,strtok_single(NULL, "~"),NUMLENGTH);
        strncpy(buffCarb,strtok_single(NULL, "~"),NUMLENGTH);
        strncpy(buffFat,strtok_single(NULL, "~"),NUMLENGTH);
        strncpy(buffProtein,strtok_single(NULL, "~"),NUMLENGTH);
        strncpy(buffServingSize1,strtok_single(NULL, "~"),NUMLENGTH);
        strncpy(buffServingSize1Units,strtok_single(NULL, "~"),SSLENGTH);
        strncpy(buffServingSize2,strtok_single(NULL, "~"),NUMLENGTH);
        if (strncmp(reading, "log", NAMELENGTH) == 0){
            strncpy(buffServingSize2Units,strtok_single(NULL, "~"),SSLENGTH);
            strncpy(buffDate, strtok_single(NULL, "~"), NUMLENGTH);
            strncpy(buffServings, strtok_single(NULL, "~"), NUMLENGTH);
            //Insert the newly read in node.
            tree = insert(tree, buffProductName, buffManufacturer, buffServingSize1Units, buffServingSize2Units, atof(buffEnergy), atof(buffCarb), atof(buffFat), atof(buffProtein), atof(buffServingSize1), atof(buffServingSize2), atoi(buffProductID), buffDate, atof(buffServings));
        }
        else  {
            nullCheck = strtok_single(NULL, "~");
            //Whenever the file ends with a delimeter the string becomes null before it reads in teh final empty string, this can be fixed by checking if the last value is null and if so replacing with the empty string
            if(nullCheck == NULL){
                strncpy(buffServingSize2Units,"",SSLENGTH);
            }
            else{
                strncpy(buffServingSize2Units,nullCheck,SSLENGTH);
            }

            nutrientScale = atof(buffServingSize1)/100;
            strncpy(buffDate, "1900-01-01", NUMLENGTH);
            strncpy(buffServings, "0", NUMLENGTH);
            //Insert the newly read in node. This is separate from the other one because of the nutrientScale that is used for the database.
            tree = insert(tree, buffProductName, buffManufacturer, buffServingSize1Units, buffServingSize2Units, atof(buffEnergy) * nutrientScale, atof(buffCarb) * nutrientScale, atof(buffFat) * nutrientScale, atof(buffProtein) * nutrientScale, atof(buffServingSize1), atof(buffServingSize2), atoi(buffProductID), buffDate, atof(buffServings));
        }

        flagDB = fscanf(fp, "%[^\n]%*[\n]", lineDB);
    }

    fclose(fp); 

    //Free up all of the memory that had previously been malloced
    free(buffProductID); 
    free(buffProductName); 
    free(buffManufacturer); 
    free(buffEnergy); 
    free(buffCarb); 
    free(buffFat); 
    free(buffProtein); 
    free(buffServingSize1); 
    free(buffServingSize1Units); 
    free(buffServingSize2); 
    free(buffServingSize2Units); 
    free(buffDate); 
    free(buffServings);
    free(lineDB);

    return tree;
}


///// Search Functions /////

struct node* dfs(struct node *root, struct node *searchresults, char *term, char *searchby){
    //A depth first search to use when no string started with the exact matching string that was searched for.
    char *temp = (char*) malloc (NAMELENGTH*sizeof(char));
    if(root!=NULL)
    {
        //The DFS can search by food or date with the small modifications made below.
        if(strncmp(searchby, "food", NAMELENGTH) == 0){
            strncpy(temp, root->ProductName, NAMELENGTH);
            strlwr(temp);
        }
        else if(strncmp(searchby, "date", NAMELENGTH) == 0){
            strncpy(temp, root->Date, NAMELENGTH);
        }

        searchresults = dfs(root->left_child, searchresults, term, searchby);
        if (strstr(temp, term) != NULL){
            //If a match is found, insert the node.
            searchresults = insert(searchresults, root->ProductName, root->Manufacturer, root->ServingSize1Units, root->ServingSize2Units, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize2, root->ProductID, root->Date, root->Servings);
        }
        searchresults = dfs(root->right_child, searchresults, term, searchby);// visiting right child
    }
    free(temp);
    return searchresults;
}

struct node* search(struct node *root, struct node *searchresults, char *term){
    if(root==NULL)
    {    
        //If the tree is empty return the current search results
        return searchresults;
    }

    char *tempName = (char*) malloc (NAMELENGTH*sizeof(char));
    strncpy(tempName, root->ProductName, NAMELENGTH);
    strlwr(tempName);
    if(0 > strncmp(tempName, term, strlen(term)))
    { // The input is smaller so it should be to the left
        searchresults = search(root->right_child, searchresults, term);
    }
    else if(0 < strncmp(tempName, term, strlen(term)))
    { // The input is greater so it should be to the right
        searchresults = search(root->left_child, searchresults, term);
    }
    else {
        searchresults = insert(searchresults, root->ProductName, root->Manufacturer, root->ServingSize1Units, root->ServingSize2Units, root->Energy, root->Carbs, root->Fat, root->Protein, root->ServingSize1, root->ServingSize2, root->ProductID, root->Date, root->Servings);
        //When the term matches the product name we must check both because for some items the letters following what matches cause valid search results to go to both sides. This occurs because a longer string such as "GREEK YOGURT SMOOTHIE" would go to the 'incorrect' side of the tree even though it is still valid and will contain other valid search results.
        searchresults = search(root->left_child, searchresults, term);
        searchresults = search(root->right_child, searchresults, term);
    }
    free(tempName);
    return searchresults;
}

int printOptions(struct node *root, int counter, char *use, int logProductName, int logManufacturer, int logDate, int logServings, int dbProductName, int dbManufacturer){
    // A function to easily print the options that were found by the search results.
    // The '*'s in the printf statements allow the program to control dynamically how long each string should be.
    char *buffer = (char*) malloc (NUMLENGTH*sizeof(char));
    if(root!=NULL) {
        if (strncmp(use, "log", NAMELENGTH) == 0){
            if (counter == 0 && root->left_child == NULL){
                printf("\n%5.5s | %*.*s | %*.*s | %*.*s | %*.*s \n", "#", logProductName, logProductName, "Product Name", logManufacturer, logManufacturer, "Manufacturer", logDate, logDate, "Date", logServings, logServings, "Servings");
                for (int i = 0; i < (logProductName + logManufacturer + logDate + logServings + 18); i++){
                    printf("-");
                }
                printf("\n");
            }
            counter = printOptions(root->left_child, counter, use, logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
            counter = counter + 1;
            sprintf(buffer, "%d", counter);
            printf("%5.5s | %*.*s | %*.*s | %*.*s | %*.2f\n", buffer, logProductName, logProductName, root->ProductName, logManufacturer, logManufacturer, root->Manufacturer, logDate, logDate, root->Date, logServings, root->Servings);
            counter = printOptions(root->right_child, counter, use, logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
        }
        else {
            if (counter == 0 && root->left_child == NULL){
                printf("\n%5.5s | %*.*s | %*.*s \n", "#", dbProductName, dbProductName, "Product Name", dbManufacturer, dbManufacturer, "Manufacturer");
                for (int i = 0; i < (dbProductName + dbManufacturer + 12); i++){
                    printf("-");
                }
                printf("\n");
            }
            counter = printOptions(root->left_child, counter, use, logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
            counter = counter + 1;
            sprintf(buffer, "%d", counter);
            printf("%5.5s | %*.*s | %*.*s \n", buffer, dbProductName, dbProductName, root->ProductName, dbManufacturer, dbManufacturer, root->Manufacturer);        
            counter = printOptions(root->right_child, counter, use, logProductName, logManufacturer, logDate, logServings, dbProductName,  dbManufacturer);
        }

    }
    free(buffer);
    return counter;
}

int selectOption(struct node *p, struct node *selected, int counter, int userSelection){
    if (p != NULL)
    {
        //Use a DFS in order to find which of the foods was selected.
        counter = selectOption(p->left_child, selected, counter, userSelection);
        counter = counter + 1;
        if (counter == userSelection){
            //Had to include slightly modified insert code rather than using the function in this scenario
            selected->ProductName = (char*) malloc (NAMELENGTH*sizeof(char));
            strncpy(selected->ProductName, p->ProductName, NAMELENGTH);

            selected->Manufacturer = (char*) malloc (NAMELENGTH*sizeof(char));
            strncpy(selected->Manufacturer, p->Manufacturer, NAMELENGTH);

            selected->ServingSize1Units = (char*) malloc (SSLENGTH*sizeof(char));
            strncpy(selected->ServingSize1Units, p->ServingSize1Units, SSLENGTH);
            
            selected->ServingSize2Units = (char*) malloc (SSLENGTH*sizeof(char));
            strncpy(selected->ServingSize2Units, p->ServingSize2Units, SSLENGTH);

            selected->Date = (char*) malloc (NUMLENGTH*sizeof(char));
            strncpy(selected->Date, p->Date, NUMLENGTH);

            selected->Energy = p->Energy;
            selected->Carbs = p->Carbs;
            selected->Fat = p->Fat;
            selected->Protein = p->Protein;
            selected->ServingSize1 = p->ServingSize1;
            selected->ServingSize2 = p->ServingSize2;
            selected->ProductID = p->ProductID;

            selected->Servings = p->Servings;
            selected->left_child = NULL;
            selected->right_child = NULL;
        }
        counter = selectOption(p->right_child, selected, counter, userSelection);
    }
    return counter;
}


///// Validate and Error Check Various Types of Input /////

char * validateDate(char *date){
    char *tempdate = (char*) malloc (NUMLENGTH*sizeof(char));
    int year = 0, month = 0, day = 0, alpha = 0, digits = 0, valid = 0;
        
    //Get the current date to ensure a future date is not entered
    time_t T = time(NULL);
    struct  tm tm = *localtime(&T);

    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;

    strncpy(tempdate, date, NUMLENGTH);

    while(!valid){
        digits = 0;
        alpha = 0;
        //see how many alphanumeric versus how many numeric
        for(int i = 0; i < strlen(tempdate); i++){
            if (isdigit(tempdate[i])){
                digits++;
            }
            else{
                alpha++;
            }
        }
        //Prevents anything longer or shorter than the format 'YYYY-MM-DD' from continuing.
        if (strlen(tempdate) != 10){
            printf("\nPlease enter a valid date of the format 'YYYY-MM-DD'. You entered a date format that is either too long or too short.\n");
        }
        //Now you know that the dashes are in the correct spot
        else if (tempdate[4] != '-' || tempdate[7] != '-'){
            printf("\nPlease enter a valid date of the format 'YYYY-MM-DD'. You entered a date format that either did not possess the '-' marks or put them in the wrong place.\n");
        }
        //You should detect 8 digits and 2 alphanumeric, it does not matter where they are located because you already know where the 2 alphanumeric characters are so thus by deduction where the 8 digits are located
        else if (digits != 8 || alpha != 2){
            printf("\nPlease enter a valid date of the format 'YYYY-MM-DD'. You entered a date that has alphanumeric characters where the year, month, or day should be.\n");
        }

        else{
            //At this point the program knows that the date is in the right format. Now it will validate the actual contents of the date.
            year = atoi(strtok(tempdate, "-"));
            month = atoi(strtok(NULL, "-"));
            day = atoi(strtok(NULL, "-"));

            //Year is not older than the oldest living person
            if(year < 1900){
                printf("\nIf you had consumed this food before 1900 that would make you the oldest person still alive! Please enter a date that is after 1900 but not after today.\n");
            }
            //Year is not in the future
            else if (year > currentYear){
                printf("\nAre you from the future? I am guessing not. Please enter a date that is after 1900 but not after today.\n");
            }
            //The month is not larger than the possible amount of months
            else if (month > 12){
                printf("\nThat is not a valid month!\n");
            }
            //Month is not in the future of the current year should it be selected
            else if (month > currentMonth && year == currentYear){
                printf("\nAre you from the future? I am guessing not. Please enter a date that is after 1900 but not after today.\n");
            }
            //Does that specific day exists in that specfic month?
            else if (((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31)) || ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) || ((month == 2) && (day > 28) && (year%4 != 0)) || ((month == 2) && (day > 29) && (year%4 == 0))){
                printf("\nThat is not a valid day in this month! %d\n", month);
            }
            //Is the day that has been selected in the future of this month?
            else if (day > currentDay && month == currentMonth && year == currentYear){
                printf("\nAre you from the future? I am guessing not. Please enter a date that is after 1900 but not after today.\n");
            }
            else {
                valid = 1;
            }
        }
        if (!valid){
            date = getInput(NUMLENGTH);
            strncpy(tempdate, date, NUMLENGTH);
        }
    }
    free(tempdate);
    return date;
}

int validateNum (char * numStr){
    int digits = 0, valid = 0;

    while (!valid){
        digits = 0;
        //Count the number of digits in the string
        for(int i = 0; i < strlen(numStr); i++){
            if (isdigit(numStr[i])){
                digits++;
            }
        }
        //If the number of digits present represents the length of the string then the string must be just an integer.
        if(digits == strlen(numStr)){
            if(atoi(numStr)>0){
                valid = 1;              
            }
        }
        //Prompt the user to enter proper input.
        else {
            printf("\nPlease enter a valid integer. No alphanumeric characters or decimal places will be accepted and the number must be above 0.\n");
            numStr = getInput(NUMLENGTH);
        }
    }
    return atoi(numStr);
}

double validateFloat (char * numStr){
    char *tempStr = (char*) malloc (NUMLENGTH*sizeof(char));
    int digits = 0, valid = 0;

    strncpy(tempStr, numStr, NUMLENGTH);

    while (!valid){
        digits = 0;
        //Count the number of digits in the string
        for(int i = 0; i < strlen(numStr); i++){
            if (isdigit(numStr[i])){
                digits++;
            }
        }
        //Limit the length of the float to 10 digits
        if (strlen(numStr) > 10){
            printf("\nThat is too many digits. The maximum amount of numbers you can enter is 10 so you may need to round your decimal places.\n");
        }
        //The number can be an integer or it must contain only one alphanumeric non-numeric character and that is the '.'.
        else if((digits == strlen(numStr)) || ((digits == strlen(numStr) - 1) && strpbrk(tempStr, ".") && strlen(numStr) != 1)){
            if (atof(numStr) > 0){
                valid = 1;
            }
            else {
                printf("\nThe amount of servings you consumed must be above 0.\n");
            }
            
        }
        //Prompt the user to enter proper input.
        if (valid == 0){
            printf("\nPlease enter a valid decimal number.\n");
            numStr = getInput(NUMLENGTH);
            strncpy(tempStr, numStr, NUMLENGTH);
        }
    }
    free(tempStr);
    return atof(numStr);
}

char * validateBinary(char * input, char *choice1, char *choice2){
    input = strlwr(input);
    int valid = 0;

    while (!valid){
        //Check to see if the input matches either of the possible selections.
        if(strncmp(input, choice1, LINELENGTH) == 0 || strncmp(input, choice2, LINELENGTH) == 0){
            valid = 1;
        }
        //Prompt the user to enter proper input.
        else  {
            printf("\nPlease enter either '%s' or '%s'.\n", choice1, choice2);
            input = getInput(NUMLENGTH);
        }
    }
    return input;
}

int validateSelection(int input, int max){
    int valid = 0;

    while (!valid){
        //Make sure the number is in the range of possible selections.
        if(input <= max && input > 0){
            valid = 1;
        }
        //Prompt the user to enter proper input.
        else {
            printf("\nThat number is not in the range of potential selection options. Please enter a number from 1 to %d.\n", max);
            input = validateNum(getInput(NUMLENGTH));
        }
    }
    return input;
}


///// Manage Settings /////

int readSettings(char *filename, int *logProductName, int *logManufacturer, int *logDate, int *logServings, int *dbProductName, int *dbManufacturer){

    FILE *fp;

    fp = fopen(filename, "ab+");

    //Check the file size
    long fsize = 0;
    if(fp != NULL) 
    {
        // Go to end of the file
        fseek(fp, 0, SEEK_END); 
        fsize= ftell(fp);
    }

    rewind(fp); //ab+ opens the file and points to the end, rewind it to the top

    //If the file is empty write/create a file containing the default settings
    if (fsize == 0){
        fprintf(fp, "%d\n", *logProductName);
        fprintf(fp, "%d\n", *logManufacturer);
        fprintf(fp, "%d\n", *logDate);
        fprintf(fp, "%d\n", *logServings);
        fprintf(fp, "%d\n", *dbProductName);
        fprintf(fp, "%d\n", *dbManufacturer);
    }
    //If the file is not empty read the file containing the settings
    else {
        fscanf(fp, "%d", logProductName);
        fscanf(fp, "%d", logManufacturer);
        fscanf(fp, "%d", logDate);
        fscanf(fp, "%d", logServings);
        fscanf(fp, "%d", dbProductName);
        fscanf(fp, "%d", dbManufacturer);
    }

    fclose(fp);
    return 0;
}

int updateSettings(char *filename, int *logProductName, int *logManufacturer, int *logDate, int *logServings, int *dbProductName, int *dbManufacturer){
    FILE *fp;

    remove(filename);
    fp = fopen(filename, "ab+");

    //Rewrite the file to contain the new settings so they can be saved over multiple runs.
    fprintf(fp, "%d\n", *logProductName);
    fprintf(fp, "%d\n", *logManufacturer);
    fprintf(fp, "%d\n", *logDate);
    fprintf(fp, "%d\n", *logServings);
    fprintf(fp, "%d\n", *dbProductName);
    fprintf(fp, "%d\n", *dbManufacturer);

    fclose(fp);

    return 0;
}




