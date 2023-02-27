#!/bin/bash
echo "Running tests on new"
pip install -U -e .
# pytest -p no:cacheprovider
echo "Profiling old"
g++ profiling_old.cpp -pg -o profiling_old.out -O1
./profiling_old.out
gprof profiling_old.out gmon.out > prof_cpp_old.txt
echo "Profiling new"
g++ profiling_new.cpp -pg -o profiling_new.out -O1
./profiling_new.out
gprof profiling_new.out gmon.out > prof_cpp_new.txt
echo "Python performances"
python performances.py > perf_python.txt
echo "Clean directory"
rm -rf */__pycache__
rm -rf .pytest*
rm -rf build
rm -rf *.egg-info
rm *.so