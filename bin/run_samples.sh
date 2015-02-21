#!/bin/bash

./formatting < samples/test.in.spec
if [ -f generator.cpp ]; then
  g++ generator.cpp -o generator
fi
