[bits 32]
[extern _start] ; externs the main function, the actuall main will be resolve at link time.

call _start ; executing the kernel

jmp $