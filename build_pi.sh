#!/bin/sh

clang++ -std=c++11 `pkg-config hidapi-libusb --cflags` `pkg-config hidapi-libusb --libs` -lusb -o tempsense main.cpp
