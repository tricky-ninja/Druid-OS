[bits 32]
section .entry

extern __bss_start
extern __end

global entry
[extern _start]
kernel_entry:
  call _start

halt:
  hlt
  jmp halt
