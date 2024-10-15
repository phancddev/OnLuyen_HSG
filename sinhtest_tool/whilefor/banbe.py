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

# Một số cặp số bạn bè đã biết
def known_friend_pairs():
    return [(220, 284), (1184, 1210), (2620, 2924), (5020, 5564), (6232, 6368)]

# Hàm sinh test và tạo folder
def generate_tests(num_tests, num_friend_tests):
    if not os.path.exists("banbe"):
        os.mkdir("banbe")

    # Lấy các cặp số bạn bè đã biết
    friends_pairs = known_friend_pairs()

    # Sinh các test chắc chắn có output là 1
    for i in range(1, num_friend_tests + 1):
        # Tạo folder cho từng test
        folder_name = f"banbe/{i}"
        os.mkdir(folder_name)

        # Chọn ngẫu nhiên một cặp số bạn bè
        n, m = random.choice(friends_pairs)

        # Ghi vào file banbe.inp
        with open(f"{folder_name}/banbe.inp", "w") as inp_file:
            inp_file.write(f"{n} {m}\n")

        # Ghi kết quả vào banbe.out (luôn là 1)
        with open(f"{folder_name}/banbe.out", "w") as out_file:
            out_file.write("1\n")

    # Sinh các test ngẫu nhiên có thể ra kết quả 1 hoặc 0
    for i in range(num_friend_tests + 1, num_tests + 1):
        # Tạo folder cho từng test
        folder_name = f"banbe/{i}"
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
    num_friend_tests = 10  # Số lượng test chắc chắn ra 1
    generate_tests(num_tests, num_friend_tests)
    print("Đã sinh 100 folder với các file banbe.inp và banbe.out trong folder banbe.")
