[bits 16]

%define ENDL 0x0D, 0x0A, 0

start: jmp main

main:

  mov ah, 9
  xor bh, bh
  mov cx, 1
  mov al, 'E'
  int 10h


  cli 
  hlt

