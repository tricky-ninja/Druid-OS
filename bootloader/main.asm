[bits 16]
[org 0x7c00]

%define ENDL 0x0D, 0x0A, 0

start: jmp boot

KERNEL_OFFSET equ 0x7f00

%include "bios_functions/out.asm"
%include "bios_functions/disk.asm"
%include "bootloader/gdt.asm"
%include "bootloader/switch-to-32-bit.asm"

load_kernel:
  mov dl, [BOOT_DRIVE]
  mov bx, KERNEL_OFFSET   ; store to es:bx(0x0:0x7f00)
  mov dh, 5   ; read 5 segments

  ; loads and jumps to the kernel
  call read_kernel
  ret


halt:
  hlt
  jmp halt


boot:
  mov [BOOT_DRIVE], dl
  
  mov bp, 0x7c00
  mov sp, bp


  mov si, wlcm_msg
  call print

  call load_kernel
  call switch_to_32_bit

  jmp halt


[bits 32]
START_KENREL:
  call KERNEL_OFFSET
  jmp halt


wlcm_msg: db "Winterburn v0.1.22.11", ENDL
BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55