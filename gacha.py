# A random late night idea, inspired by a conversation with a friend
# It's a basic implementation of the "wishing" or "pulling" system present in many gacha games
# https://en.wikipedia.org/wiki/Gacha_game

import numpy as np
import sys
import json
import math

with open("/home/user/data/dev/python/save.json", "r") as f:
    save = json.load(f)


def pull(n: int, id: str) -> list[str]:
    s, a = save[id]["s_tier_max"], save[id]["a_tier_max"]
    c = []
    for i in range(n):
        if int(save[id]["tokens"]) < 10:
            print("insufficient tokens")
            save[id]["history"] += ["insufficient tokens"]
            return []
        d = (
            np.random.choice(
                ["blank", "a_tier", "s_tier"],
                1,
                p=[
                    61 / 70,
                    1 / 10,
                    1 / 35,
                ],
            )
        )[0]
        if s == 34:
            d = "s_tier"
        elif a == 9:
            d = "a_tier"
        if d == "s_tier":
            d = (
                np.random.choice(
                    ["S-major", "S-minor"],
                    1,
                    p=[0.7, 0.3],
                )
            )[0]
            s = 0
            a += 1
        elif d == "a_tier":
            d = (
                np.random.choice(
                    ["A-major", "A-minor"],
                    1,
                    p=[0.7, 0.3],
                )
            )[0]
            a = 0
            s += 1
        else:
            s += 1
            a += 1
        c.append(d)
        save[id]["tokens"] -= 10
        save[id]["s_tier_max"], save[id]["a_tier_max"] = s, a
        save[id]["history"] += ["pulled: " + d]
    return c


cmd = sys.argv[1]

if cmd == "pull":
    print(pull(int(sys.argv[2]), sys.argv[3]))
    print(sys.argv[3], "has", save[sys.argv[3]]["tokens"], "tokens")
if cmd == "add":
    save[sys.argv[3]]["tokens"] += int(sys.argv[2])
    save[sys.argv[3]]["history"] += ["add tokens: " + str(int(sys.argv[2]))]
    print(sys.argv[3], "has", save[sys.argv[3]]["tokens"], "tokens")
    print(
        sys.argv[3], "can make", math.floor(save[sys.argv[3]]["tokens"] / 10), "wishes"
    )
if cmd == "remove":
    if save[sys.argv[3]]["tokens"] <= 10:
        print("<=10 tokens left, can not remove")
    else:
        save[sys.argv[3]]["tokens"] -= int(sys.argv[2])
        save[sys.argv[3]]["history"] += ["remove tokens: " + str(int(sys.argv[2]))]
        print(sys.argv[3], "has", save[sys.argv[3]]["tokens"], "tokens")
        print(
            sys.argv[3],
            "can make",
            math.floor(save[sys.argv[3]]["tokens"] / 10),
            "wishes",
        )
if cmd == "data":
    print(save[sys.argv[2]]["history"])
    print(sys.argv[2], "has", save[sys.argv[2]]["tokens"], "tokens")
    print(
        sys.argv[2], "can make", math.floor(save[sys.argv[2]]["tokens"] / 10), "wishes"
    )
if cmd == "help":
    print("10 tokens = 1 wish")
    print("S tier has a 1/35 chance and A tier has a 1/10 chance")
    print("within tiers, majors and minors are 70/30")
    # print details of rewards

with open("/home/user/data/dev/python/save.json", "w") as f:
    json.dump(save, f)
