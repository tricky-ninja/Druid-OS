[bits 32]
section .entry

extern __bss_start
extern __end

global kernel_entry
[extern _start]
kernel_entry:
  call _start

halt:
  hlt
  jmp halt
