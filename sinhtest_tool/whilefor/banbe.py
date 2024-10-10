import os
import random

# Hàm tính tổng các ước số thực sự của một số
def sum_of_divisors(num):
    total = 1  # Mọi số đều có ước là 1
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            total += i
            if i != num // i:
                total += num // i
    return total

# Hàm kiểm tra xem hai số có phải là bạn bè hay không
def are_friends(n, m):
    return sum_of_divisors(n) == m and sum_of_divisors(m) == n

# Hàm sinh test và tạo folder
def generate_tests(num_tests):
    if not os.path.exists("banbe"):
        os.mkdir("banbe")

    for i in range(1, num_tests + 1):
        # Tạo folder cho từng test
        folder_name = f"banbe/{i:02}"  # Định dạng số với 2 chữ số (01, 02, 03,...)

        os.mkdir(folder_name)

        # Sinh ngẫu nhiên hai số n và m
        n = random.randint(1, 10**9)
        m = random.randint(1, 10**9)

        # Ghi vào file banbe.inp
        with open(f"{folder_name}/banbe.inp", "w") as inp_file:
            inp_file.write(f"{n} {m}\n")

        # Ghi kết quả kiểm tra vào banbe.out
        with open(f"{folder_name}/banbe.out", "w") as out_file:
            if are_friends(n, m):
                out_file.write("1\n")
            else:
                out_file.write("0\n")

if __name__ == "__main__":
    num_tests = 100  # Số lượng test cần sinh
    generate_tests(num_tests)
    print("Đã sinh 100 folder với các file banbe.inp và banbe.out trong folder banbe.")
