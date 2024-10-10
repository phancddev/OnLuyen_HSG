import os
import random
import math

def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def sieve(n):
    primes = []
    for i in range(2, n + 1):
        if is_prime(i):
            primes.append(i)
    return primes

def generate_tests():
    base_folder = "all_tests"
    os.makedirs(base_folder, exist_ok=True)
    
    for test_num in range(1, 100):
        folder_name = f"{base_folder}/{test_num:02d}"
        os.makedirs(folder_name, exist_ok=True)
        n = random.randint(1, 10**12)
        with open(f"{folder_name}/snt.inp", "w") as inp_file:
            inp_file.write(f"{n}\n")
        primes = sieve(int(math.sqrt(n)))
        with open(f"{folder_name}/snt.out", "w") as out_file:
            out_file.write(" ".join(map(str, primes)) + "\n")
    
    for test_num in range(101, 200):
        folder_name = f"{base_folder}/{test_num:02d}"
        os.makedirs(folder_name, exist_ok=True)
        n = random.randint(10**15, 10**18)
        with open(f"{folder_name}/snt.inp", "w") as inp_file:
            inp_file.write(f"{n}\n")
        primes = sieve(int(math.sqrt(n)))
        with open(f"{folder_name}/snt.out", "w") as out_file:
            out_file.write(" ".join(map(str, primes)) + "\n")

generate_tests()
