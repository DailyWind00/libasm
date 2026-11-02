section .text
global ft_calloc

extern malloc

ft_calloc:
	push rbx

	mov rax, rdi
	mov rcx, rsi
	mul rcx
	
	jc overflow

	mov rsi, 0
	mov rbx, rax

	mov rdi, rax
	call malloc wrt ..plt

	cmp rax, 0
	jne setzero

	jmp end

setzero:
	cmp rsi, rbx
	jae end

	mov byte [rax + rsi], 0

	inc rsi
	jmp setzero
	
end:
	pop rbx
	ret

overflow:
	mov rax, 0
	pop rbx
	ret

section .note.GNU-stack noalloc noexec nowrite progbits