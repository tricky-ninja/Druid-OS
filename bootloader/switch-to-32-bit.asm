[bits 16]

KbdControllerDataPort               equ 0x60
KbdControllerCommandPort            equ 0x64
KbdControllerDisableKeyboard        equ 0xAD
KbdControllerEnableKeyboard         equ 0xAE
KbdControllerReadCtrlOutputPort     equ 0xD0
KbdControllerWriteCtrlOutputPort    equ 0xD1

switch_to_32_bit:
  cli                     ; disable interrupts
  call EnableA20
  lgdt [gdt_descriptor]   ; load GDT descriptor
  mov eax, cr0
  or eax, 0x1             ; enable protected mode
  mov cr0, eax
  jmp CODE_SEG:start_32bit ; far jump to flush cpu pipeline of any 16 bit instructions

EnableA20:
    ; disable keyboard
    call A20WaitInput
    mov al, KbdControllerDisableKeyboard
    out KbdControllerCommandPort, al

    ; read control output port
    call A20WaitInput
    mov al, KbdControllerReadCtrlOutputPort
    out KbdControllerCommandPort, al

    call A20WaitOutput
    in al, KbdControllerDataPort
    push eax

    ; write control output port
    call A20WaitInput
    mov al, KbdControllerWriteCtrlOutputPort
    out KbdControllerCommandPort, al
    
    call A20WaitInput
    pop eax
    or al, 2                                    ; bit 2 = A20 bit
    out KbdControllerDataPort, al

    ; enable keyboard
    call A20WaitInput
    mov al, KbdControllerEnableKeyboard
    out KbdControllerCommandPort, al

    call A20WaitInput
    ret


A20WaitInput:
    ; wait until status bit 2 (input buffer) is 0
    ; by reading from command port, we read status byte
    in al, KbdControllerCommandPort
    test al, 2
    jnz A20WaitInput
    ret

A20WaitOutput:
    ; wait until status bit 1 (output buffer) is 1 so it can be read
    in al, KbdControllerCommandPort
    test al, 1
    jz A20WaitOutput
    ret
  
[bits 32]
start_32bit:

  ; sets up data and stack segments
  mov ax, DATA_SEG
  mov es, ax
  mov ds, ax
  mov gs, ax
  mov fs, ax
  mov ss, ax

  ; set up stack
  mov ebp, 0x90000
  mov esp, ebp

  call START_KENREL

[bits 16]

