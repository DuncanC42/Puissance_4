#!/bin/bash
for fic in code/*.c; do
    filename=$(basename $fic)
    filename=${filename%.c}
    cc ./"$fic" -o "$filename" -Wall
    mv "$filename" strats/"$filename"
done
./evaluation
