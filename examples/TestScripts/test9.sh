#!/bin/bash

cd ../..

echo "This is a test that will output in binary mode"

echo "./awadmark  IN_bin0 IN_bin1 -out=bin"

echo "------------------------------------------------"

./awadmark examples/IN_bin0 examples/IN_bin1 -out=bin

cd examples/

echo "------------------------------------------------"
echo -e "file1 edited:\\n"
cat IN_bin0. 
echo -e "\\n------------------------------------------------"
echo -e "file2 edited:\\n"
cat IN_bin1.
echo