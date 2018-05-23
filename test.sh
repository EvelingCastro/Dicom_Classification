#!/bin/bash

cp -f main ../images/xray/
echo "main copied to ../images/xray"
cp -rf include ../images/xray/
echo "include copied to ../images/xray"
cp -rf imebraLib ../images/xray/
echo "imebraLib copied to ../images/xray"
cd ../images/xray/
./main