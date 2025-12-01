format ELF64 executable 3
; syscall No   return  arg0  arg1  arg2  arg3  arg4  arg5
; rax          rax     rdi   rsi   rdx   r10   r8    r9

entry start
segment readable executable

start:
  mov rax, -50
  cqo

  idiv [divisor]  ; (rdx:rax) / divisor
  cmp     rdx, 0
  jge     .ok
  add     rdx, [divisor]
  .ok:

  mov rax, rdx
  mov [num], rax

  mov rax, 60
  mov rdi, [num]
  syscall

segment readable writable

num dq 0
divisor dq 100

