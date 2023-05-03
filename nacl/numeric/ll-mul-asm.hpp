// arg1 * arg2 % arg3, x86-64 SYSV only
__attribute__((naked)) long long
modmul(long long, long long, long long) {
  asm(R"(
    mov %rdi, %rax
    mov %rdx, %rcx
    imul %rsi
    idiv %rcx
    mov %rdx, %rax
    ret
  )");
}
