import Test
import timeit

t1 = timeit.timeit(lambda: Test.profiling_old(), number=1)
print(f"old: {t1:.3f}")

t2 = timeit.timeit(lambda: Test.profiling_new(), number=1)
print(f"new: {t2:.3f}")
