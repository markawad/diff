#!/bin/bash

cd ../..

echo "This is a test that will remove whitespaces from f1 which is a text file, and also remove f2 which is an html file with so we will add -w"

echo "./awadmark IN_removeWhitespaces1 -w IN_removeWhitespaces2.html"

./awadmark examples/IN_removeWhitespaces1 -w examples/IN_removeWhitespaces2.html;

cd examples/

echo -e "file1:\\n" && cat IN_removeWhitespaces1. && echo -e "\\nfile2:\\n" && cat IN_removeWhitespaces2.html.


