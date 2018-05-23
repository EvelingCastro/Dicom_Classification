#!/bin/bash

cp -f main ../images/xray\ emergenciass/
echo "main copied to ../images/xray\ emergencias"
cp -rf include ../images/xray\ emergenciass/
echo "include copied to ../images/xray\ emergencias"
cp -rf imebraLib ../images/xray\ emergenciass/
echo "imebraLib copied to ../images/xray\ emergencias"
cd ../images/xray\ emergenciass/
./main