format ELF64 executable 3
; syscall No   return  arg0  arg1  arg2  arg3  arg4  arg5
; rax          rax     rdi   rsi   rdx   r10   r8    r9

entry start
segment readable executable

start:
  mov rax, 2 ; open
  mov rdi, fn
  mov rsi, 0
  mov rdx, 0
  syscall

  cmp rax, 0
  jl error_exit

  ; Save fd
  mov [fd], eax

read_loop:
  mov rax, 0 ; read
  mov edi, [fd]
  lea rsi, [buf]
  mov rdx, 1024
  syscall
  cmp rax, 0
  jle close_file

  mov rcx, rax
  mov r8, rsi

loop_buffer:

  cmp rcx, 0
  jz read_loop

  mov al, [r8]; load current character

  cmp al, 'R'
  je .handle_right

  cmp al, 'L'
  je .handle_left

  cmp al, 10 ; '\n'
  je .handle_newline

  jmp .handle_num


  .handle_right:
  mov r9b, 0 ; rotate right
  jmp .next_char

  .handle_left:
  mov r9b, 1 ; rotate left
  jmp .next_char

  .handle_num:
  mov bl, al
  sub bl, '0' ; convert to num
  mov rax, [cur_num]
  imul rax, 10
  add rax, rbx
  mov [cur_num], rax
  jmp .next_char

  .handle_newline:
  ; Read number to diff
  mov rax, [diff]
  add rax, [cur_num]
  mov [diff], rax
  mov [cur_num], 0

  mov rax, [dial]

  cmp r9b, 0
  je .calc_right

  sub rax, [diff]
  jmp .modulo

  .calc_right:
  add rax, [diff]

  .modulo:
  mov [diff], 0
  mov [new_dial], rax

  ; TODO FIX THIS SHIT
  cqo
  idiv [divisor]  ; (rdx:rax) / divisor

  cmp     rax, 0
  jge     .quotient_ok
  neg     rax
  .quotient_ok:

  cmp     rdx, 0
  jge     .ok
  add     rdx, [divisor]
  .ok:

  mov rbx, [dial]
  test rbx, rbx
  jz .update_dial

  mov rbx, [new_dial]
  cmp rbx, 99
  jg .add_part_two

  test rbx, rbx
  jns .update_dial

  .add_part_two:
  add [total_part_two], rax

  .update_dial:
  mov rax, rdx
  mov [dial], rax

  cmp rax, 0
  jnz .next_char

  inc [total_part_one]
  inc [total_part_two]

  .next_char:
  inc r8 ; char pointer
  dec rcx ; byte counter
  jmp loop_buffer

close_file:
  mov rax, 3 ; close
  mov edi, [fd]
  syscall

  mov rax, [total_part_one]
  call print_rax

    mov rax, 1 ; write
    mov rdi, 1
    lea rsi, [lf]
    mov rdx, 1
    syscall

  mov rax, [total_part_two]
  call print_rax

  mov rax, 0
  jmp exit

print_rax:
  lea rcx, [buf+1024]
  mov rbx, 10

  .next:
  xor rdx, rdx
  div rbx               ; rax = rax / 10, rdx = rax % 10
  add dl, '0'           ; convert remainder to ASCII
  dec rcx
  mov [rcx], dl
  test rax, rax
  jnz .next

  mov rax, 1 ; write
  mov rdi, 1
  mov rsi, rcx
  lea rdx, [buf+1024]
  sub rdx, rcx
  syscall

  ret

error_exit:
  mov rax, 1 ; write
  mov rdi, 2
  lea rsi, [error_msg]
  mov rdx, 6
  syscall

  mov rax, 1

exit:
  mov rdi, rax
  mov rax, 60 ;exit
  syscall

segment readable writable

fn db "e01-input.txt", 0
fn_len = $ - fn
fd dd 0

buf rb 1024
error_msg db "ERROR: Failed to read file", 27
lf db 10

cur_num dq 0
dial dq 50
new_dial dq 0
diff dq 0
total_part_one dq 0
total_part_two dq 0
divisor dq 100

