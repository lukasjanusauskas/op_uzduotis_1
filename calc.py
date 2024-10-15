import re

def calcAvg(lst: list):
    avgs = []
    for i in range(4):
        avgs.append(sum(lst[i::4])/len(lst[i::4]))

    return(avgs)

with open("res.txt", "r") as f:
    results = {}
    for line in f.readlines():
        num = re.sub(r".*studentai(\d+)[\w\s\.]*", r"\1", line)
        if num == "\n":
            continue
        speed = re.sub(r".* ([\d\.]+) s", r"\1", line)
        if num in results:
            results[num].append(float(speed))
        else:
            results[num] = [float(speed)]
        
    for key in results:
        nus, rik, kat, isv = calcAvg(results[key])
        print(f"- Nuskaitė {key} per {nus:.5f}")
        print(f"- Surikiavo {key} per {rik:.5f}")
        print(f"- Kategorizavo {key} per {kat:.5f}")
        print(f"- Išvedė kaetegorizuotus {key} per {isv:.5f}")
        print()
