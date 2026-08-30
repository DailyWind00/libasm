section .text
global ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc

ft_strdup:
	push rbx ; save rbx (ABI)

	call ft_strlen

	mov rbx, rdi ; save string
	inc rax
	mov rdi, rax

	call malloc wrt ..plt

	cmp rax, 0
	je end

	mov rdi, rax
	mov rsi, rbx

	call ft_strcpy

	jmp end

end:
	pop rbx ; reload old rbx (ABI)
	ret

section .note.GNU-stack noalloc noexec nowrite progbits