import os

cmp = r"g++ -O2 .\brickbreaker.cpp -o .\brickbreaker.exe"
run = r".\brickbreaker.exe"

os.system("clear")
print("Compiling...")
os.system(cmp)
print("Done! Running executable...")
os.system(run)
