from os import listdir, chdir

def solver(op):
    files = listdir(".")
    nums = []
    for f in files:
        type = f.split("_")[1]
        if type == "number":
            with open(f,"r") as fo:
                nums.append(int(fo.read()))
        else:
            chdir(f)
            nums.append(solver(type))
            chdir("..")
    if len(nums)==1:
        return nums[0]
    if op == "+":
        return nums[0]+nums[1]
    else:
        return nums[0]*nums[1]

#print(solver(""))

flag = ""
allf = listdir(".")
#print(allf)

for f in allf:
    chdir(f)
    flag += chr(solver(""))
    chdir("..")
print(flag)