[bits 16]
[org 0x7c00]

%define ENDL 0x0D, 0x0A, 0

start: jmp boot

%include "bootloader/out.asm"
%include "bootloader/disk.asm"

halt:
  hlt
  jmp halt

boot:
  mov [boot_drive], dl
  xor ax, ax ;  sets ax to 0

  ; sets data segments to 0
  mov ds, ax
  mov es, ax

  ; sets up stack
  mov ss, ax
  mov sp, 0x7c00
  mov bp, sp


  mov si, wlcm_msg
  call print

  mov dh, 30
  mov bx, kernel
  call read_kernel
  jmp kernel

  jmp halt


wlcm_msg: db "Welcome to winterburn v0.1.22.11", ENDL
boot_drive: db 0

times 510-($-$$) db 0
dw 0xaa55
kernel: db 0