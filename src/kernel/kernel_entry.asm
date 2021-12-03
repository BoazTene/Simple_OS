[bits 32]
[extern main] ; externs the main function, the actuall main will be resolve at link time.

call main ; executing the kernel

jmp $