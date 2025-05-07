import time


def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)


start_time = time.time()
factorial(1000)
end_time = time.time()

print("Execution time with CPython: {} seconds".format(end_time - start_time))
