; James Rhodes
; CSc 35 Sec 10
; Spring 2017

.model small
.stack 100h

.data

inputX DB "Input  X=",'$'
inputY DB "Input  Y=",'$'
outputW DB "Output W=",'$'
prompt DB "Press q to quit",0Dh,0Ah,'$'

loc DW ?
X DW ?
Y DW ?
W DW ?
Sum DW ?

.code

main PROC
	mov ax,@data
	mov ds,ax

BeginMain:
	mov dx,OFFSET inputX			; prompt for X
	call Print

	call ReceiveInput				; call to get X and Y
	mov X,ax

	call PrintNewLine				; basic new line

	mov dx,OFFSET inputY			; prompt for Y
	call Print

	call ReceiveInput				; call to get X and Y
	mov Y,ax

	mov ax,X
	mov bx,Y
	call CalculateW					; Calls all calculate procedures
	mov W,ax

	call PrintNewline				

	mov dx,offset outputW			; display W
	call Print						; Basic print
	mov ax,W
	call Convert					; To decimal
	call PrintNewline

	call PromptExit
	cmp ax,1						; ax == 1 if user presses 'q'
	jne BeginMain					; loop until user exits

	call PrintNewLine

	mov ax,4c00h
	int 21h
main ENDP

CalculateW PROC
	;LOC
	mov cx,ax	; X param in cx
	mov ax,160
	mul bx
	mov bx,cx	; X param in bx
	mov cx,ax
	mov ax,2
	mul bx
	add ax,cx	; result in ax
	mov loc,ax
	
	;Sum
	mov bx,8
	xor dx,dx
	div bx
	mov bx,1257
	add ax,bx	; result in ax
	
	;W
	mov bx,7
	xor dx,dx
	div bx
	mov ax,dx
	add ax,5	; result in ax
	ret
CalculateW ENDP

Print PROC
	mov ah,09h
	int 21h
	ret
Print ENDP

PrintNewline PROC
	mov ah,06h
	mov dl,0Dh
	int 21h
	mov ah,06h
	mov dl,0Ah
	int 21h
	ret
PrintNewline ENDP

ReceiveInput PROC
	xor bx,bx		; clear register
	mov cx,10
L1:
	mov ah,01h		; receive input
	int 21h

	cmp al,0Dh		; check for carriage return
	je Finish		; jump if equal to return

	mov ah,0
	sub ax,48
	push ax

	mov ax,bx		; move previous sum to accumulator
	mul cx
	pop bx
	add ax,bx		; add newly converted decimal
	mov bx,ax		; store sum in bx

	jmp L1			; loop back to top
Finish:
	mov ax,bx		; result in ax
	ret
ReceiveInput ENDP

Convert PROC
	mov cx,0			; set count to zero
	mov bx,10			; divisor 10 to convert to decimal
L1:
	xor dx,dx			; clear dx
	div bx
	add dx,30h			; convert to ASCII
	push dx				; push to stack
	inc cx
	cmp ax,0			; check for another character
	jg L1
L2:
	pop ax				; pull first digit from the stack
	mov ah,06h
	mov dl,al			; output character
	int 21h
	loop L2
	ret
Convert ENDP

PromptExit PROC
	mov dx,OFFSET prompt
	call Print

	mov ah,01h		; receive input
	int 21h
	
	cmp al,71h		; check for 'q'
	jne Miss		; if not equal, repeat program
	mov ax,1
	ret				; this return ends program, ax == 1
Miss:
	mov ax,0
	ret
PromptExit ENDP

END main
