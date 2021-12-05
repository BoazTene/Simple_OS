; The console.asm module, includes all kind of prints, keyboard handling, etc.

; The print label, can print strings and chars.
print:
  ; gets the string through the si paramater.
  .print_string:
    .print_string_loop:
        mov al, [bx]
        cmp al, 0
        je .return

        call .print_char

        inc bx

        jmp .print_string_loop


  ; Gets the number in dx.
  ; The function print the number stored in dx in hex.
  .print_hex:
    push dx

    ; Prints the prefix 0xhex-number
    mov al, '0'
    call .print_char
    mov al, 'x'
    call .print_char

    ; prints the first number, stored in the high dh.
    shr dx, 12
    mov al, dl
    call .print_one_hex_number

    pop dx
    push dx

    ; prints the second number, stored in the low dh.
    shl dx, 4
    shr dx, 12
    mov al, dl
    call .print_one_hex_number
    
    pop dx
    push dx

    ; prints the third number stored in the high dl.
    shl dx, 8
    shr dx, 12
    mov al, dl
    call .print_one_hex_number

    pop dx

    ; prints the forth number stored in the low dl.
    shl dx, 12
    shr dx, 12
    mov al, dl
    call .print_one_hex_number

    mov al, 0x20 ; adding a space as a suffix.
    call .print_char

    jmp .return

  ; Please do not call outside the console.asm module, 
  ; Gets the number in al and print it as hex without any prefixes
  .print_one_hex_number:
    cmp al, 9
    ja .above9

    ; below 9, means we can treat it like it a regular number.
    add al, '0'
    call .print_char
    ret

    ; If the number is greater than 9, it will reduce the number by 9 so 10 is 1 11 is 2, etc. And the first number is A so we add A.
    .above9: 
      sub al, 10
      add al, 'A'
      call .print_char
      ret
      

  ; gets the char via the al register
  .print_char:
    pusha
    mov ah, 0x0e
    int 10h
    popa
    ret

  ; returns
  .return:
    ret
