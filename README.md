# nutritional-database

This project was created in order to demonstrate te ability to read in and manage large amounts of data in an efficient way. To do this I have chosen to create a nutrition log which pulls the food information from every FDA approved food that is on the market. In the program users are able to create, retrieve, update, and delete entries from their logs which are maintained over the course of different sessions in the program.

# Getting Started

### Downloading Nutritional Data
To download and assemble the nutritional data all you need to do is run the buildall.sh file. Before running this file it is important to make sure that you have both `curl` and `unzip` installed on your command line. This can easily be done using the commands `sudo apt-get install unzip` and `sudo apt-get install curl`. After installing these two packages and running the buildall.sh file the data should be prepared properly for the program.

### Starting the Program
A make file is included to make this as easy as possible. First ensure that you have already run the buildall.sh file and that functions.c, functions.h, and main.c are included in the file folder. Next you can type 'make' and hit enter. The program will compile to the c11 standard and will create an executable titled 'main.exe'. Run this executable to start the program and you should be good to go!

# Features
Users are able to create, retrieve, update, and delete entries from a personal nutrition log.

### Create
User are able to create new entries in their log. This includes being able to enter the number of servings you consumed which will work as a multipler to show how many calories, carbs, grams of fat, and grams of protein you consumed. The user is also able to enter the date that the food was consumed. This is helpful if you are trying to find all of your entries from one specific day!

### Retrieve
Users are able to retrieve old entries from their log. They can search either by date or by food and select the appropriate node which will then be printed for them.

### Update
Users are able to update old entries form their log as well. They can search either by date or by food and will select the node from a printed table. The user can update either the number of servings consumed or the date they were consumed on and the updated node will be printed below once this is complete.

### Delete
Users can also delete old entrie which from their log. They can search either by date or by food and will select the node from a printed table. The node will be printed for the user before it is deleted.

### Switch User
The log being accessed is determined by the name of the current user. If someone wishes to change logs they are able to switch users in the middle of a session and their work will still be saved. This allows the user to easily switch logs without having to exit the program.

### Change Settings
There are a few printing settings that the user is able to ocntrol. By default when options are printed in the table format the default width when a log entry is printed for the product name is 40 characters and the manufacturer is 20 characters when a database entry is presented the default width for the product name is 60 characters and the manutacturer is 30 characters. In general users should not have issues with product names being too long and not fitting in the table but there are a few exceptions. If the user finds the issues to be recurring they can change their settings to better accomidate their needs (these settings will be saved over multiple sessions as well).

# Functions

### Taking Input
- getInput - Takes in a number then reads an equivalent number of characters to that number.
- strtok_single - Works in a similar way to strtok except it is able to handle multiple delimeters back-to-back. Credit to [Stack Exchange](https://stackoverflow.com/questions/8705844/need-to-know-when-no-data-appears-between-two-token-separators-using-strtok "Stack Exchange") for assistance with this function.
- strlwr - Makes a string entirely lowercase. The strlwr that is built into C is not part of the C11 standard so I created my own.

### Binary Search Tree Functions
- printNode - Prints the contents of the node it is given.
- insert* - Creates a new node in its proper location.
- update - Allows the user to update the date or nunmber of servings consumed for a log entry.
- find_minimum* - Finds the successor of a BST node, used in the delete function.
- delete* - Deletes the desired node and replaces it in the BST with a NULL or one of the deleted nodes children.
- deleteBST - Deletes an entire BST. This was created in order to empty the searchresults tree and free the memory locations.
- writeFromBST - Writes the entire BST into the users log file.
- readIntoBST - Reads from a file into a BST.

### Search Functions
- search* - Searches for a particular node and takes advantaged of the sorting done in a binary search tree.
- dfs - Executes a depth first search.

### Validate and Error Check
- validateDate - Ensures that a valid date is entered. Checks the format as well as the number of days that are included in the month, the number of the month, and an approporiate year.
- validateNum - Ensures a valid integer is entered.
- validateFloat - Ensures a valid decimal number is entered.
- validateBinary - Ensures one of two binary choices are selected.
- validateSelection - Ensures that the number selected is within the range of options to be chosen.

### Manage Settings
- readSettings - Reads the users settings file or creates a new one if they did not previously have a log.
- updateSettings - Updates the settings file for the user to their desired specifications.

*Inspiration for these functions came from [Amit Kumar](https://www.codesdope.com/blog/article/binary-search-tree-in-c/
 "Amit Kumar")*
 
# Limitations
### Saving
It is important to note that the program only saves to the log at the end. If you choose to exit the program using Ctrl+C in the middle it will not save the changes you have made in that session! Therefore properly exiting is very important.

### Input String Length
When reading from the file there are various limitations on the strings length for each variable. Product Names and Manufacturers cannot be larger that 255 characters. Calories, Carbs, Fat, Protein, Product ID, and each of the serving size numbers cannot be any larger than 15 characters. The serving size units can be no larger than 31 characters. Lastly, an entire line can never be larger than 511 characters. All of these limitations comply with the FDA file that has been provided.

### File Access
If the nutritional database is not present in the folder with the program when the program is run it will close immediately after stating "Loading nutritional data..." with an error. It is also imperative that the log and settings files are not open in another program while the program is run. This will also cause the program to crash and produce another error as well. 
