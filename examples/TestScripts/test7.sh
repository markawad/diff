#!/bin/bash

cd ../..

echo "This is a test that will compare two directories with recursive mode"

echo "./awadmark -r test test2"

echo "------------------------------------------------"

./awadmark -r examples/test examples/test2

cd examples/

echo "------------------------------------------------"
