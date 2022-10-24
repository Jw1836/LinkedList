# LinkedList Lab

## Purpose
To build a single-linked list with the use of templates while handling memory management.

## Background
Develop a Linked List that performs several standard operations. Linked Lists are common data structures in all object-oriented languages, and will play a vital role in your activities as a programmer.

## Requirements
* This lab must be completed on the Linux OS.
* You will use the files in this git repository to complete the lab.
* A short video has been created for this lab which you may find very helpful.  You can watch it 
[here](https://youtu.be/zRdZaBSqjEM).
* You are required to use template classes that accept various types including ints, doubles, strings, etc.
* The linked list must be a single-linked list with an external pointer only to the first node in the list. You should have a head pointer, but not a tail pointer.

### Part 1 - Insertion Tests (40 points)
* Construct a Single-Linked List that can be used with template classes and that passes all of the Test Driver's insertion tests consisting of file1.txt and file2.txt (20 points each).
* These will test your insertHead, insertTail, and insertAfter functions.

### Part 2 - Remove (24 points)
* This will test your remove and clear functions.  Includes files file3.txt and file4.txt (12 points each).

### Part 3 - Comprehensive Tests (24 points)
* Pass file5.txt of the Test Driver. This more comprehensively tests all the linked list's functions using strings.

### Part 4 - No Leaks in the Hull (12 points Pass/Fail)
* Run and pass Valgrind on your program to ensure that you have no memory leaks.

### Requirement Notes
* You may not use the predefined C++ Standard Template Library (STL) classes.
* This lab must run on the Linux machines. The pass-off scripts will work only on those machines
* For this lab only, due to the nature of template classes, you are strongly encouraged to implement the entire class in only a '.h'.  All classes that are not templates must be implemented by a '.h' and a '.cpp'
* Make sure that you pass all 5 tests before attempting to fix any memory leaks.  If anything causes the program to crash (or if the pass-off script is unable to finish testing your code) the pass-off script may terminate before it is able to delete your LinkedList, which will always result in memory leaks.
