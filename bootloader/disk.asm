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

  xor ch,ch ; sets the cylinder to 3
  xor dh, dh  ; sets the head number to 3

  mov cl, 02h ; the sector number to read, 1st is our bootloader
  mov dl, [boot_drive]

  mov di, 5

.loop:
  test di, di   ; set zf to 1 if di is 0
  jz .read_err
  stc     ; some bioses won't set the carry flag
  int 13h
  dec di
  jc .loop ; if carry flag is set then there is an error, so we try again

  pop dx
  push ax
  mov al, 2
  cmp al, dh  ; sector read count
  pop ax
  jne .sector_err

  popa
  ret

.read_err:
  mov si, read_err_msg
  call print
  mov dh, ah
  jmp halt

.sector_err:
  mov si, sector_err_msg
  call print
  jmp .loop
  ret


read_err_msg: db "Reading from disk failed!", ENDL
sector_err_msg: db "Incorrect number of sectors to read! Trying again...", ENDL