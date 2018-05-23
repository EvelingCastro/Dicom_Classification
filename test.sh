#!/bin/bash
echo $1
cp -f main "$1"
echo "main copied to $1"
cp -rf include "$1"
echo "include copied to $1"
cp -rf imebraLib "$1"
echo "imebraLib copied to $1"
cd "$1"
./main