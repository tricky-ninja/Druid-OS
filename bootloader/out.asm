;
; @params
;   ds:si - points to the string to be printed
;
print:
  ; saves registers
  push si
  push ax
  push bx


.loop:
  lodsb  ; loads the next character from ds:si to al
  or al, al   ; checks if the charcater is null
  jz .done

  mov ah, 0Eh
  mov bh, 0
  int 10h
  jmp .loop

.done:
  pop bx
  pop ax
  pop si
  ret
