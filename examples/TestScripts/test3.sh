#!/bin/bash

cd ../..

echo "This is a test that will remove urls from f1"

echo "./awadmark -u IN_removeURL0 IN_removeURL1"

echo "------------------------------------------------"

./awadmark -u examples/IN_removeURL0 examples/IN_removeURL1

cd examples/

echo "------------------------------------------------"
echo -e "file1:\\n"
cat IN_removeURL0 
echo -e "\\n------------------------------------------------"
echo -e "file1 Edited:\\n"
cat IN_removeURL0.
