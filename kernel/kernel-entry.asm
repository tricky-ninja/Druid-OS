[bits 32]

[extern main]
call main

halt:
  hlt
  jmp halt
