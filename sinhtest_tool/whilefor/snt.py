import os
import random

# Hàm kiểm tra số nguyên tố đơn giản
def is_prime(n):
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

# Hàm sinh test và tạo folder
def generate_prime_tests(num_tests):
    if not os.path.exists("snt_tests"):
        os.mkdir("snt_tests")

    for i in range(1, num_tests + 1):
        # Tạo folder cho từng test
        folder_name = f"snt_tests/{i}"
        os.mkdir(folder_name)

        # Sinh ngẫu nhiên một số n trong khoảng từ 10^17 đến 10^18
        n = random.randint(10**17, 10**18)

        # Ghi vào file input
        with open(f"{folder_name}/snt.inp", "w") as inp_file:
            inp_file.write(f"{n}\n")

        # Liệt kê các số nguyên tố từ 1 đến n
        primes = []
        for num in range(10**17, n + 1):
            if is_prime(num):
                primes.append(str(num))

        # Ghi vào file output
        with open(f"{folder_name}/snt.out", "w") as out_file:
            out_file.write(" ".join(primes) + "\n")

if __name__ == "__main__":
    num_tests = 10  # Số lượng test cần sinh
    generate_prime_tests(num_tests)
    print("Đã sinh các test từ 10^17 đến 10^18 trong folder snt_tests.")
