# A small project that takes some text input and converts it into an image as a form of encryption
# Inspired by Cicada 3301 (https://clevcode.org/cicada-3301/), but nowhere near as sophisticated or effective

import numpy as np
from PIL import Image
import math


text = ""
with open("dummy.txt") as f:
    text = f.read()


def encode(text, outfile):

    while len(text) % 4 != 0:
        text += " "

    out = [(text[i : i + 4]) for i in range(0, len(text), 4)]
    size = math.ceil(math.sqrt(len(out)))
    while len(out) != size * size:
        out += ["    "]
    data = np.reshape(out, (size, size))
    imgdata = np.zeros((data.shape[0], data.shape[1], 4), np.uint8)
    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            imgdata[i][j] = [
                ord(data[i][j][0]),
                ord(data[i][j][1]),
                ord(data[i][j][2]),
                ord(data[i][j][3]),
            ]

    img = Image.fromarray(imgdata)  # Create a PIL image
    img.save(outfile)


def decode(infile):
    data = np.asarray(Image.open(infile))
    text = ""
    for i in data:
        for j in i:
            for k in j:
                text += chr(k)
    return text.rstrip()


encode(text, "testrgba.png")
print(decode("duck.png"))
