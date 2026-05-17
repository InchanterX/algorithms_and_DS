#!/bin/bash

DIR="${1:-.}"

find "$DIR" -type f -name "*.txt" | while read -r file; do
    echo Converting $file
    iconv -f CP1251 -t UTF-8 $file -o "${file}.tmp" && mv "${file}.tmp" "$file"
    echo
done