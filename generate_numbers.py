import random
import sys

n = int(sys.argv[1])

for _ in range(n):
    print(random.randint(1, 100000), end=" ")
