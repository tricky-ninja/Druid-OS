[bits 16]

switch_to_32_bit:
  cli                     ; disable interrupts
  lgdt [gdt_descriptor]   ; load GDT descriptor
  mov eax, cr0
  or eax, 0x1             ; enable protected mode
  mov cr0, eax
  jmp CODE_SEG:start_32bit ; far jump to flush cpu pipeline of any 16 bit instructions

[bits 32]
start_32bit:

  ; set up stack
  mov ebp, 0x90000
  mov esp, ebp

  call START_KENREL