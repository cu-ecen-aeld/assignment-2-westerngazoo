#!/bin/bash

 if [ $# -ne 2 ]
 then
 	echo "Usage: $0 <directory> <string>"
 	exit 1
 fi

 filesdir="$1"
 searchstr="$2"

#check if the first arg is a dir
if [ ! -d "$filesdir" ]; then
	echo "Error: $filesdir is not a directory"
	exit 1
fi

#check the number of files 
num_files=0
num_matching_lines=0

while IFS= read -r -d '' file || [ -n "$file" ]; do
    if [ -f "$file" ]; then
        num_files=$((num_files+1))
        matching_lines=$(grep -c "$searchstr" "$file")
        num_matching_lines=$((num_matching_lines+matching_lines))
    fi
done < <(find "$filesdir" -type f -print0)

echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"
exit 0
