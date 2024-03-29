# diff tool

This was my Programming and Algorithims semester project, the idea was to replicate the unix diff tool and add extra features documented below.

Feel free to use/extend this project. However, please do not use it for any submissions school/university related, thanks.  

```
Welcome to the Diff command tool, a new and refined way to compare your Directories/Files!
Usage: ./diff [Options] file1 [Options] file2 [Output Option]

-ignore "text"           Ignores text within quotations in file
-ig "text"               Same as -ignore "text"
-w                       Removes Whitespaces except for paragraphs
-u                       Ignores urls
-equal "text1" "text2"   text2 will be treated the same as text1 in the same file only
-eq "text1" "text2"      Same as -equal "text1" "text2"
-r                       Recursive mode to go through Directories inside the directory being compared
-out=binary              Compares files in Binary
-out=bin                 Same as -out=binary


How The Program Works:
* If you inserted two different file types, they will be automatically compared in binary mode.

* File types supported are:
    - Text files:   WhiteSpaces are ignored, Difference measured by paragraphs.
    - Html files:   Attribute orders are ignored, Difference measured by lines.
    - Binary files: Difference measured by bytes.

* Directories can be compared with each other:
    - File names are compared first.
    - Equal file names are then compared with each other.
    - if -r was specified, then directories inside will be compared as well.
    - parameters included when comparing the directories, will be set for all
      of its files that are compared.

* The parameters set will not change the actual file. However, a new file name will be added
  in the same directory of the original file with a '.' in the end. This file will have all
  of the parameter changes, just in case you would like to use it for other purposes, think
  of it as a small sed program as well.


tool examples:
./diff -ig "Spaghetti Code" file1 -eq "I hate Progtest" "I love Progtest" file2 -out=binary


Program Output:
    - If there is a difference, it reports it. If not, nothing will be outputed.
    - output examples:
        + 1a2
          < abc
          * This means after line 1 in file1, add "abc" to be equal to file2 till line 2.
        + 2d2
          > abc
          * This means in line 2 of file1, delete "abc" to be equal to file2 till line 2.
        + 2c2
          < "abc"
          > "xyz"
          * This means change line 2 of file 1, by adding "abc" and removing "xyz" to be equal
            to file2 till line 2.


Good Luck... you will need it! :) (This message was stated for Mark, and not the user of course!)

~ Created by Mark © 2019
```
