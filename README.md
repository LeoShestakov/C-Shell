# C-Shell (Seashell)

**Created by Leo Shestakov and Alex Thompson**

**Everything is condensed to one file (except the makefile).**

Our shell implements exit & cd explicitly and has support for multiple commands. In addition, we utilize both forms of simple redirection (< and >), as well as pipes (|). We completed the entire assignment. However, there is minimal error catching and we often times assume that the input is valid.

There is a bug where long (3 word) commands can sometimes fail when multiple of them are called in the same line (;)

We attempted to implement >>, but were unsuccessful.

Function headers:
  * int main();
  * char *** processInput(char *line);

Each function description can be found right above its header in **main.c**, instead of here.
