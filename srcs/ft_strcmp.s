section .text
global ft_strcmp

ft_strcmp:
	mov rcx, 0
	jmp loop

loop:
	movzx eax, byte [rdi + rcx]
	movzx edx, byte [rsi + rcx]
	cmp eax, edx
	jne end
	
	cmp eax, 0
	je end

	inc rcx
	jmp loop

end:
	movzx eax, byte [rdi + rcx]
	movzx edx, byte [rsi + rcx]
	sub eax, edx
	ret

section .note.GNU-stack noalloc noexec nowrite progbits