#!/bin/bash

cd ../..

echo "This will test input handling"

echo "Extra File test"
echo "./awadmark IN_bin0 IN_bin1 IN_empty0"


echo "------------------------------------------------"

./awadmark examples/IN_bin0 examples/IN_bin1 examples/IN_ignore.html

echo "------------------------------------------------"

echo "File does not exist test"
echo "./awadmark nonExistant IN_bin0"

echo "------------------------------------------------"

./awadmark nonExistant examples/IN_bin0

echo "------------------------------------------------"

echo "Missing parameters test"
echo "./awadmark IN_bin0 -eq abc xyz"

echo "------------------------------------------------"

./awadmark examples/IN_bin0 -eq abc xyz

echo "------------------------------------------------"

echo "Dir with a file test"
echo "./awadmark test IN_bin0"

echo "------------------------------------------------"

./awadmark examples/test examples/IN_bin0


