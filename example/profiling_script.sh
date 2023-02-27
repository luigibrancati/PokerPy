#!/bin/bash
echo "Building test code"
pip install -U .
echo "Profiling old algo"
g++ profiling_old.cpp -pg -o scripts/profiling_old.out -O2 --std=c++20
./scripts/profiling_old.out
gprof scripts/profiling_old.out gmon.out > scripts/prof_cpp_old.txt
echo "Profiling new algo"
g++ profiling_new.cpp -pg -o scripts/profiling_new.out -O2 --std=c++20
./scripts/profiling_new.out
gprof scripts/profiling_new.out gmon.out > scripts/prof_cpp_new.txt
echo "Python code running time"
python performances.py > scripts/perf_python.txt
echo "Clean directory"
rm -rf */__pycache__
rm -rf .pytest*
rm -rf build
rm -rf *.egg-info
rm *.so
rm *.out
echo "Uninstall Test"
pip uninstall Test -y