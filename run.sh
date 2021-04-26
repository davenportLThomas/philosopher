#!/bin/bash

if [ -f "try" ]; then 
	rm try
fi

g++ -pthread -o try main.cpp
./try
