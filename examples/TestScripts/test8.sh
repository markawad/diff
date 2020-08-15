#!/bin/bash

cd ../..

echo "This is a test that will compare two directories and the parameter changes will be set for every file in directory"

echo "./awadmark -ig 2 test test2"

echo "------------------------------------------------"

./awadmark -ig 2 examples/test examples/test2

cd examples/

echo "------------------------------------------------"
