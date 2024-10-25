.code32
.data
a: 
    .float 3.15

.text
.globl check_for_sse_support, enable_sse
check_for_sse_support:
    movl $0x1, %eax
    cpuid
    movl %edx, %eax
    movl $0x2000000, %edx
    andl %edx, %eax
    ret

enable_sse:
    movl %CR0, %eax
    movl $0x4, %edx
    notl %edx
    andl %edx, %eax
    movl $0x1, %edx
    orl %edx, %eax
    movl %eax, %CR0
    movl %CR4, %eax
    xorl %edx, %edx
    movl $0x600, %edx
    orl %edx, %eax
    movl %eax, %CR4
    ret