#!/bin/bash

cd ../..

echo "This is a test that will replace a word with another word from a file using -eq \"email\" \"letter\""

echo "./awadmark -eq \"email\" \"letter\" IN_equalWords0.html IN_equalWords1.html"

echo "------------------------------------------------"

./awadmark -eq email letter examples/IN_equalWords0.html examples/IN_equalWords1.html

cd examples/

echo "------------------------------------------------"
echo -e "file1:\\n"
cat IN_equalWords0.html
echo -e "\\n------------------------------------------------"
echo -e "file1 Edited:\\n"
cat IN_equalWords0.html.
echo