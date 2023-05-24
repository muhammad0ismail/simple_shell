a function called _atoi that converts a string to an integer. The function works by first checking if the string is empty. If it is, the function returns 0. If the string is not empty, the function then checks if the first character of the string is a minus sign. If it is, the function sets a flag to indicate that the number is negative. The function then loops through the string, adding each digit to the result. The result is multiplied by 10 for each digit that is added. The function stops looping when it reaches the end of the string or when it encounters a non-digit character. If the flag is set, the result is multiplied by -1 before it is returned.

---------------
Builtin.c  
a shell that implements the exit, cd, and help commands. The exit command exits the shell, the cd command changes the current directory, and the help command displays help information about the shell commands.

--------------
a function called _myalias that mimics the alias builtin (man alias). The function works by first checking if the user has provided any arguments. If the user has not provided any arguments, the function prints all of the aliases. If the user has provided arguments, the function checks if each argument is an alias. If an argument is an alias, the function sets the alias. If an argument is not an alias, the function prints the alias with the given name.

-------------

