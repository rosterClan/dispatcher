from random import randrange
import subprocess
import os
import time

stringContent = ""
for idx in range(0, 4):
    tempString = f'{idx+randrange(20)},{randrange(100)},{randrange(3)}\n'
    stringContent += tempString
f = open("dynamicInput.txt", "w")
f.write(stringContent)
f.close()
    