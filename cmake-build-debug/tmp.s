.intel_syntax noprefix
.global main
main:
  push 1
  push 2
  push 3
  imul rax, rdi
  add rax, rdi
  push rax
  pop rax
  ret