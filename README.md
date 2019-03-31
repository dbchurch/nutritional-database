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

# Appendix

## Print Options

### Sample of the selections printed when the database is searched.

### Sample of the selections printed when the log is searched.


