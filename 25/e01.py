day = 1
test = 0

fn = f"e{str(day).zfill(2)}-{'test' if test else 'input'}.txt"
lines = open(fn).read().strip().split("\n")

num = 50
total = 0
for l in lines:
    diff = int(l[1:])
    if l[0] == "L":
        diff = -diff
    num = (num + diff) % 100
    if num == 0:
        total += 1

print(total)


num = 50
total = 0
for l in lines:
    rot = int(l[1:])
    newNum = num + rot
    if l[0] == "L":
        newNum = num - rot
        total += int(abs(newNum) / 100)
        if num != 0 and newNum <= 0:
            total += 1
    else:
        total += int(newNum / 100)

    print(f"{num} {l} {newNum % 100} {total}")
    num = newNum % 100

print(total)
