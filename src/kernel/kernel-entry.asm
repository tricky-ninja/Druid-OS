[bits 32]

[extern _start]
call _start

halt:
  hlt
  jmp halt
