gdt_start:
  dq 0  ; null segment

;
; base - 0(start of memory)
; limit - 0xfffff (maximum posible memory)
;
code_segment:
  dw 0xffff  ; limit (first 16 bytes)

  ; base (first 24 bits)
  dw 0x0  ; 16 bits
  db 0x0  ; 8 bits total 24

  db 0b10011010 ; present(1 bit), privilage(2 bits), type(1 bit), type flags(4bits)[code(1)/data(0), conforming, readable, accessed(managed by cpu)]

  db 0b11001111   ; other flags[granularity, 32bits, 64bits, available], limit last 4 bits

  ; last 8 bits of base
  db 0x0

;
; base - 0(start of memory)
; limit - 0xfffff (maximum posible memory)
;
data_segment:
  dw 0xffff  ; limit (first 16 bytes)

  ; base (first 24 bits)
  dw 0x0  ; 16 bits
  db 0x0  ; 8 bits total 24

  db 0b10010010 ; present(1 bit), privilage(2 bits), type(1 bit), type flags(4bits)[code(1)/data(0), direction, writeable, accessed(managed by cpu)]

  db 0b11001111   ; other flags[granularity, 32bits, 64bits, available], limit last 4 bits

  ; last 8 bits of base
  db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit)
    dd gdt_start ; address (32 bit)


CODE_SEG equ code_segment - gdt_start
DATA_SEG equ data_segment - gdt_start