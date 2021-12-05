[org 0x7c00] ; bootloader offset
    KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl
    
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print.print_string ; This will be written after the BIOS messages

    call load_kernel

    call switch_to_pm ; We are never return from here.
    jmp $ ; this will actually never be executed

%include "src/boot/modules/disk.asm"
%include "src/boot/switch_pm/gdt.asm"
%include "src/boot/modules/console.asm"
%include "src/boot/modules/console32.asm"
%include "src/boot/switch_pm/switch_to_pm.asm"


[bits 16]
; loads the kernel
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print.print_string

    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk.load

    ret


[bits 32]
BEGIN_PM: ; after the switch we will get here
    call console.clear
    mov ebx, MSG_PROT_MODE
    call console.print_string_pm ; Note that this will be written at the top left corner

    call KERNEL_OFFSET

    jmp $


; globals
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Starts loading the kernel", 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55