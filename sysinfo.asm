section .data
    text db "--- Mini-Term Native Assembly Subsystem Active ---", 10
    text_len equ $ - text

section .text
    global _start

_start:
    ; sys_write (syscall 1) to stdout (file descriptor 1)
    mov rax, 1          
    mov rdi, 1          
    mov rsi, text       
    mov rdx, text_len   
    syscall             

    ; sys_exit (syscall 60) with exit code 0
    mov rax, 60         
    mov rdi, 0          
    syscall
