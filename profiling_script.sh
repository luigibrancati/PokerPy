#!/bin/bash
echo "Running tests on new"
pip install -U -e .
pytest -p no:cacheprovider
echo "Profiling new"
g++ profiling_new.cpp -pg -o profiling_new.out -O2
./profiling_new.out
gprof profiling_new.out gmon.out > analysis_new.txt
echo "Profiling old"
g++ profiling_old.cpp -pg -o profiling_old.out -O2
./profiling_old.out
gprof profiling_old.out gmon.out > analysis_old.txt
echo "Clean directory"
rm *.out
rm -rf */__pycache__
rm -rf .pytest*
rm -rf build
rm -rf *.egg-info
rm *.so