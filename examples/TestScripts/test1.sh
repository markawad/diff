#!/bin/bash

cd ../..

echo "This test will will not add any file to check if error page is displayed" 
echo -e "\\n"

echo "./awadmark"

./awadmark -eq "sad" "happy"

cd examples/


