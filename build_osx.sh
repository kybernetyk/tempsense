#!/bin/sh

clang++ -std=c++11 `pkg-config hidapi --cflags` `pkg-config hidapi --libs` -o tempsense main.cpp
