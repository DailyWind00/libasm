section .text
global ft_strcpy

ft_strcpy:
	mov rax, 0
	jmp loop

loop:
	cmp byte [rsi + rax], 0
	je end

	mov dl, [rsi + rax]
	mov byte [rdi + rax], dl
	
	inc rax
	jmp loop

end:
	mov byte [rdi + rax], 0
	mov rax, rdi
	ret

section .note.GNU-stack noalloc noexec nowrite progbits