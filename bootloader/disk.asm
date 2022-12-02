;
; @params:
;   dx(dl) - number of sectors to load
;   bx - loaction in ram to store the read data
;
read_kernel:
  pusha
  push dx

  mov ah, 02h 
  mov al, dh ; sectors to read
  mov cl, 02h ; the sector to read 1 is our bootloader

 mov ch, 0
 mov dh, 0
 mov dl, [boot_drive]


  int 13h
  jc read_err ; if carry flag is set then there is an error

  pop dx
  cmp al, dh  ; sector read count
  jne sector_err

  popa
  ret

read_err:
  mov si, read_err_msg
  call print
  mov dh, ah
  jmp halt

sector_err:
  mov si, sector_err_msg
  call print
  jmp halt


read_err_msg: db "Reading from disk failed!", ENDL
sector_err_msg: db "Incorrect number of sectors to read!", ENDL