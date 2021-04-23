#!/bin/bash

if [ -f "try" ]; then 
	rm try
fi

g++ -o try main.cpp
./try
