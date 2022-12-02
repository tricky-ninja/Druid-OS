[bits 16]
[org 0x7c00]

%define ENDL 0x0D, 0x0A, 0

start: jmp boot

%include "bootloader/out.asm"

halt:
  cli
  hlt
  jmp halt

boot:
  xor ax, ax ;  sets ax to 0

  ; sets segments to 0
  mov ds, ax
  mov es, ax
  mov ss, ax


  mov si, wlcm_msg
  call print

  jmp halt


wlcm_msg: db "Welcome to winterburn v0.1.22.11", ENDL

times 510-($-$$) db 0
dw 0xaa55