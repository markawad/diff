Dear all,

The input files to be tested will be named as:
IN_XXX 

The out files would either be compared to parsed files, or output on the terminal with output:
OUT_XX

EG:

IN_removeWhitespaces
OUT_removeWhitespaces

* Run the program *
./awadmark -w IN_removeWhitespaces *any other file as we care to see if the whitespaces were removed *

then IN_removeWhitespaces. will be created
If it is the same as OUT_removeWhitespaces, then then -w parameter is working correctlly 
