; The console.asm module, but adjusted for 32 bit.
[bits 32]

; constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK: equ 0xf0

console:
  ; prints a null-terminated string pointed by edx.
  ; put your string pointer in ebx.
  .print_string_pm:
    pusha 
    mov edx, VIDEO_MEMORY ; sets edx to the start of the video memory.

    .print_string_pm_loop:
      mov al, [ebx] ; store the char in ebx at al.
      mov ah, [WHITE_ON_BLACK]

      cmp al, 0
      je .print_string_pm_done

      mov [edx], ax
      add ebx, 1 ; go to the next char in ebx.
      add edx, 2 ; go to the next cell in the vid memory.
      jmp .print_string_pm_loop

    .print_string_pm_done: 
      popa 
      ret

  .clear:
    pusha 
    mov edx, VIDEO_MEMORY

    .clear_loop:
      mov ah, 0
      mov al, 0

      cmp edx, 0xBFFFF
      jnb .clear_done

      mov [edx], ax
      add edx, 2
      jmp .clear_loop

      .clear_done: 
        popa
        ret