# How to use python to write a c dependencies manager or compiler?

They all require the c coder use relative header importing like `#include "./folder_path/*.h"`

## Method 1, require every function and variable have unique names, and code is written in .h file, will produce a single ".h file"
1. You have to do a parse on the main.c file, so that you could get the `#include "<.h_file_path>"`
2. Then you do parse again on the .h_file_path to get more ".h header file paths", the final data you get is like a node tree, for each folder level, you have a lot of .h files.
3. put all code from bottom(deepest) to top, into a single .h file, then use gcc to do the compile.

## Method 2, require every function and variable have unique names, will produce a single ".h file"
1. You have to do a parse on the main.c file, so that you could get the `#include "<.h_file_path>"`, then inside of that .h file folder, you do a search for the same file name .c file, you put the .c file code at the bottom of the .h file.
2. Then you do parse again on the .h_file_path to get more ".h header file paths", the final data you get is like a node tree, for each folder level, you have a lot of .h files.
3. put all code from bottom(deepest in tree) to top, into a single .h file, then use gcc to do the compile.
