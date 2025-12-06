day = 3
test = 0

r1, r2 = 0, 0
fn = f"e{str(day).zfill(2)}-{'test' if test else 'input'}.txt"
lines = open(fn).read().strip().split("\n")


for l in lines:
    s = list(l)
    highest = sorted(s[:-1], reverse=True)[0]
    pos = l.find(highest)
    s[pos] = "0"
    second = sorted(s[pos:], reverse=True)[0]
    num = highest + second
    # print(num)
    r1 += int(num)

for l in lines:
    nums = []
    pos = 0
    for i in range(12, 0, -1):
        end = len(l) - i + 1
        c = max(l[pos:end])
        pos = l.index(c, pos, end) + 1
        nums.append(c)
    num = int("".join(nums))
    r2 += num
print(r2)
