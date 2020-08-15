#!/bin/bash

cd ../..

echo "This is a test that will ignore a word from a file"

echo "./awadmark -ig \"test\" IN_ignore.html IN_ignore2.html"

echo "------------------------------------------------"

./awadmark -ig "test" examples/IN_ignore.html examples/IN_ignore2.html

cd examples/

echo "------------------------------------------------"
echo -e "file1:\\n"
cat IN_ignore.html 
echo -e "\\n------------------------------------------------"
echo -e "file1 Edited:\\n"
cat IN_ignore.html.
echo