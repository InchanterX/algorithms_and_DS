#!/bin/bash

DIR="${1:-.}"

find "$DIR" -type f -name "*.txt" | while read -r file; do
    echo Converting $file
    iconv -f UTF-8 -t CP1251 $file -o "${file}.tmp" && mv "${file}.tmp" "$file"
    echo
done