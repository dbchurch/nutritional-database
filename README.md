# nutritional-database

This project was created in order to demonstrate te ability to read in and manage large amounts of data in an efficient way. To do this I have chosen to create a nutrition log which pulls the food information from every FDA approved food that is on the market. In the program users are able to create, retrieve, update, and delete entries from their logs which are maintained over the course of different sessions in the program.

# Getting Started

# Features
Users are able to create, retrieve, update, and delete entries from a personal nutrition log.

## Create
When users choose to create an entry they first search for the specific food that they wish to add to their log. The initial search takes advantage of the binary search tree (a log(n) search) comparing the beginning of the product name to the search term. If using the binary search tree search does not produce any results a depth first search (a log(n) search) is used and the entire product name is searched for the search term. After the searches are complete all of the products matching the search terms are printed and the user is given the option to select the one they wish to add to their log (an example of this can be seen in the Appendix under Print Options). After a prouct is selected the user is prompted to enter the date the food was consumed and the number of servings consumed. The calories, carbs, fat, and protein are all multiplied by the number of servings consumed to accurately reflect how much of each was consumed.

## Retrieve
When users choose to retrieve an entry they are prompted to search either by date or by the name of the food. When the user chooses to search by date a depth first search (a log(n) search) is used since the binary search tree is sorted by product name rather than date. When the user selects to search by food the initial search takes advantage of the binary search tree (a log(n) search) but if nothing is found the next search is a depth first search (a log(n) search) to find if the search term is contianed in any of the product names that do not start with it. After the searches are complete all of the products matching the search terms are printed and the user is given the option to select the one they wish to add to their log (an example of this can be seen in the Appendix under Print Options). When the user selects an entry the node is printed below.

## Update
When users choose to update an entry they are prompted to search either by date or by the name of the food. When the user chooses to search by date a depth first search (a log(n) search) is used since the binary search tree is sorted by product name rather than date. When the user selects to search by food the initial search takes advantage of the binary search tree (a log(n) search) but if nothing is found the next search is a depth first search (a log(n) search) to find if the search term is contianed in any of the product names that do not start with it. After the searches are complete all of the products matching the search terms are printed and the user is given the option to select the one they wish to add to their log (an example of this can be seen in the Appendix under Print Options). After a prouct is selected the user is prompted if they would like to change the number of servings or the date the food was consumed. Once the user decides which they want to change they are then asked what they would like to change the date or number of servings to and the updated node is printed with the changes shown.

## Delete
When users choose to retrieve an entry they are prompted to search either by date or by the name of the food. When the user chooses to search by date a depth first search (a log(n) search) is used since the binary search tree is sorted by product name rather than date. When the user selects to search by food the initial search takes advantage of the binary search tree (a log(n) search) but if nothing is found the next search is a depth first search (a log(n) search) to find if the search term is contianed in any of the product names that do not start with it. After the searches are complete all of the products matching the search terms are printed and the user is given the option to select the one they wish to add to their log (an example of this can be seen in the Appendix under Print Options). When the user selects an entry the node is printed to show the entire entry and then deleted.

## Switch User
The log being accessed is determined by the name of the current user. If someone wishes to change logs they are able to switch users in the middle of a session and their work will still be saved. This allows the user to easily switch logs without having to exit the program.

## Change Settings
There are a few printing settings that the user is able to ocntrol. By default when options are printed in the table format the default width when a log entry is printed for the product name is 40 characters and the manufacturer is 20 characters when a database entry is presented the default width for the product name is 60 characters and the manutacturer is 30 characters. In general users should not have issues with product names being too long and not fitting in the table but there are a few exceptions. If the user finds the issues to be recurring they can change their settings to better accomidate their needs (these settings will be saved over multiple sessions as well).

# Functions

## Taking Input
- getInput - Takes in a number then reads an equivalent number of characters to that number.
- strtok_single - Works in a similar way to strtok except it is able to handle multiple delimeters back-to-back. Credit to [Stack Exchange](https://stackoverflow.com/questions/8705844/need-to-know-when-no-data-appears-between-two-token-separators-using-strtok "Stack Exchange") for assistance with this function.
- strlwr - Makes a string entirely lowercase. The strlwr that is built into C is not part of the C11 standard so I created my own.

## Binary Search Tree Functions
- printNode - Prints the contents of the node it is given.
- insert - Creates a new node in its proper location.
- update - Allows the user to update the date or nunmber of servings consumed for a log entry.
- find_minimum - Finds the successor of a BST node, used in the delete function.
- delete - Deletes the desired node and replaces it in the BST with a NULL or one of the deleted nodes children.
- deleteBST - Deletes an entire BST. This was created in order to empty the searchresults tree and free the memory locations.
- writeFromBST - Writes the entire BST into the users log file.
- readIntoBST - Reads from a file into a BST.

## Validate and Error Check
- validateDate - Ensures that a valid date is entered. Checks the format as well as the number of days that are included in the month, the number of the month, and an approporiate year.
- validateNum - Ensures a valid integer is entered.
- validateFloat - Ensures a valid decimal number is entered.
- validateBinary - Ensures one of two binary choices are selected.
- validateSelection - Ensures that the number selected is within the range of options to be chosen.

## Manage Settings
- readSettings - Reads the users settings file or creates a new one if they did not previously have a log.
- updateSettings - Updates the settings file for the user to their desired specifications.

# Appendix

## Print Options

### Sample of the selections printed when the database is searched.


### Sample of the selections printed when the log is searched.


