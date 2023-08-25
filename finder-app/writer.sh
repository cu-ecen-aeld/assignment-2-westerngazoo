#!/bin/bash

# Check args
if [ $# -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile="$1"
writestr="$2"

# Create the directory if it doesn't exist
mkdir -p "$(dirname "$writefile")"

#if there was an error in creating the directory return 1
if [ $? -ne 0 ]; then
    echo "Error: Could not create directory for $writefile"
    exit 1
fi

# Write the content to the file
echo "$writestr" > "$writefile"

#check if the file was written successfully
if [ $? -ne 0 ]; then
    echo "Error: Could not write to $writefile"
    exit 1
fi

echo "Text written to $writefile"
exit 0
