#!/bin/sh
(
mkdir -p build
cd build
cmake ..
make -j
)
python setup.py build_ext --inplace