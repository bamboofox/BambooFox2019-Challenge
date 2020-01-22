import random
import os

def make_tree(num,lr,dep):
    if dep>=10:
        with open(str(lr)+"_number","w") as f:
            f.write(str(num))
        return
    
    ops = ["+","+","+","+","x","x"]+["n" for i in range(0,dep//5)]
    random.shuffle(ops)
    op = ops[random.randint(0,len(ops)-1)]
    if op == "+":
        os.mkdir(str(lr)+"_+")
        os.chdir(str(lr)+"_+")
        a = random.randint(-1000,1000)
        b = num-a
        make_tree(a,0,dep+1)
        make_tree(b,1,dep+1)
        os.chdir("..")
    elif op == "x":
        os.mkdir(str(lr)+"_x")
        os.chdir(str(lr)+"_x")
        al = []
        for i in range(1,abs(num)+1):
            if num%i == 0:
                al.append(i)
        #print(num)
        #print(al)
        if num != 0:
            a = al[random.randint(0,len(al)-1)] * [1,-1][random.randint(0,1)]
        else:
            a = 0
        b = num//a
        make_tree(a,0,dep+1)
        make_tree(b,1,dep+1)
        os.chdir("..")
    elif op == "n":
        with open(str(lr)+"_number","w") as f:
            f.write(str(num))

flag = "BAMBOOFOX{Dir_3xpres5i0n_tre3e33eeee}"
i=0
for c in flag:
    os.mkdir("flag[%d]"%(i))
    os.chdir("flag[%d]"%(i))
    make_tree(ord(c),0,1)
    os.chdir("..")
    i+=1