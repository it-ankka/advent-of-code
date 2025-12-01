format ELF64 executable 3
; syscall No   return  arg0  arg1  arg2  arg3  arg4  arg5
; rax          rax     rdi   rsi   rdx   r10   r8    r9

entry start
segment readable executable

start:
  ; open file as read only
  mov rax, 2
  mov rdi, fn
  mov rsi, 0
  mov rdx, 0
  syscall

  ; Exit with status 1 if fd < 0
  cmp rax, 0
  jl error_exit

  ; Save fd
  mov [fd], eax

read_loop:
  mov rax, 0
  mov edi, [fd]
  lea rsi, [buffer]
  mov rdx, 1024
  syscall

  mov rcx, rax
  mov r8, rsi

loop_buffer:

  cmp rcx, 0
  je close_file

  mov al, [r8]; load current character

  cmp al, 'R'
  je handle_right

  cmp al, 'L'
  je handle_left

  cmp al, 10 ; '\n'
  je handle_newline

  jmp handle_num


handle_right:
  mov r9, 0 ; rotate right
  jmp next_char

handle_left:
  mov r9, 1 ; rotate left
  jmp next_char


handle_num:
  mov bl, al
  sub bl, '0' ; convert to num
  mov rax, [cur_num]
  imul rax, 10
  add rax, rbx
  mov [cur_num], rax
  jmp next_char

handle_newline:
  ; Read number to diff
  mov rax, [diff]
  add rax, [cur_num]
  mov [diff], rax
  mov [cur_num], 0


  mov rax, [dial]

  cmp r9, 0
  jz modulo


modulo:
  cqo
  idiv [divisor]  ; (rdx:rax) / divisor
  cmp     rdx, 0
  jge     .ok
  add     rdx, [divisor]
  .ok:

  mov rax, rdx
  mov [dial], rax

  jmp next_char

next_char:
  inc r8 ; char pointer
  dec rcx ; byte counter
  jmp loop_buffer

close_file:
  mov rax, 3
  mov edi, [fd]
  syscall
  jmp exit

error_exit:
  mov rax, 1
  mov rdi, 2
  lea rsi, [error]
  mov rdx, 6
  syscall

  mov rax, 60
  mov rdi, 1
  syscall

exit:
  mov rax, 60
  mov rdi, [diff]
  syscall

segment readable writable

fn db "e01-test2.txt", 0
fn_len = $ - fn
fd dd 0
buffer rb 1024

error db "ERROR", 10

cur_num dq 0

dial dq 50
diff dq 0
total dq 0
divisor dq 100

