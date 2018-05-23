#!/bin/bash

cp -f main ../images/xray\ emergencias/
echo "main copied to ../images/xray\ emergencias"
cp -rf include ../images/xray\ emergencias/
echo "include copied to ../images/xray\ emergencias"
cp -rf imebraLib ../images/xray\ emergencias/
echo "imebraLib copied to ../images/xray\ emergencias"
cd ../images/xray\ emergencias/
./main