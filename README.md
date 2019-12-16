# C-Shell (Seashell)

**Everything is condensed to one file (except the makefile).**

Our shell implements exit & cd explicitly and has support for multiple commands. In addition, we utilize both forms of simple redirection (< and >), as well as pipes (|). We completed the entire assignment and have removed bugs. However, there is minimal error catching and we often times assume that the input is valid.

We attempted to implement >>, but were unsuccessful.

Function headers:
  * int main();
  * char *** processInput(char *line);

Each function description can be found right above its header in main.c, instead of here.
