; James Rhodes
; CSC 35 Sec 10
; Spring 2017

.model small
.stack 100h


main PROC

.data

TestString01	BYTE  	"***********************************",0dh,0ah,
			"*    PROGRAM 5 TESTING PROCEDURE  *",0dh,0ah,
			"***********************************",0dh,0ah,0
TestString02	BYTE	"WriteBin: Printing a binary number....: ",0
TestString03	BYTE	"ReadChar: Type an ASCII character.....: ",0
TestString04	BYTE	"Writechar: That character was.........: ",0
TestString05	BYTE	"ReadString: Type an ASCII String......: ",0
TestString06	BYTE	"WriteString...........................: ",0
TestString07	BYTE	"ReadDec: Type a 16bit Decimal number..: ",0
TestString08	BYTE	"WriteDec: The Number was..............: ",0
TestString09	BYTE	"ReadHex: Type a 16bit Hex number......: ",0
TestString10	BYTE	"WriteHex:The Number was...............: ",0
TestString11	BYTE	"WriteDec: Number of Characters Typed..: ",0

Buffer		BYTE	10 DUP ('!')

.code

	mov ax ,@data
	mov ds,ax

	call ClrScr				;Clear the Screen

	mov dx,OFFSET TestString01		;First Large Prompt/Header
	call WriteString

	call CrLf

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call CrLf

	mov dx,OFFSET TestString03		;Prompt to Test ReadChar
	call WriteString;

	call ReadChar				; Reads Filtered Char into AL
	call WriteChar				; Echo char to console

	call CrLf

	mov dx,OFFSET TestString04		;Prompt for WriteChar
	call WriteString

	call WriteChar				; Writes ASCII char in AL to Screen

	call crlf

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call CrLf

	mov dx,OFFSET TestString05		;Prompt for ReadString
	call WriteString;

	mov dx,OFFSET Buffer			; Where to store the read-in-String
	mov cx,9
	call ReadString				;Stores typed string to where DX points
    
	call CrLf

	mov dx,OFFSET TestString11		; Prompt for WriteDec, which will
	call WriteString			; print out the number of characters typed

	call WriteDec
	call CrLf

	mov dx,OFFSET TestString06		; Print out the string that was entered
	call WriteString;			; uses DX register for source

	mov dx,OFFSET Buffer

	call WriteString

	call CrLf

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call crlf

	mov dx,OFFSET TestString07		;Prompt for ReadDec Test
	call WriteString;

	call ReadDec			; puts value in AX

	call crlf

	mov dx,OFFSET TestString08		; Prompt for WriteDec Test
	call WriteString;

;	mov ax,100			;test

	call WriteDec			; Print AX register in Decimal

	call crlf

	mov dx,OFFSET TestString02	; Prompt for WriteBin test
	call WriteString;

	call WriteBin			; Prints AX register in Binary

	call crlf

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;	call CrLf

;	mov dx,OFFSET TestString09		; Prompt for READHEX
;	call WriteString;

;	call ReadHex

;	call CrLf

;	mov dx,OFFSET TestString10		; Prompt for WRITEHEX
;	call WriteString;

;	call WriteHex			; Prints AX register in Hexidecimal

	mov ax,4c00h
	int 21h

main ENDP

ClrScr PROC
;clear screen = scroll the whole screen window.
;use coordinates 0,0 to 24,79 
;BIOS INT 10h function 06h
	mov ah,06h	; scroll up
	mov al,0	; entire window
	mov ch,0	; upper left row
	mov cl,0	; upper left col
	mov dh,24	; lower right row
	mov dl,79	; lower right col
	mov bh,7	; attribute for blanked area
	int 10h		; white: RGB=111=7
	ret
ClrScr ENDP

ReadChar PROC USES dx
; Read a single character from std input (keyboard).
; Returns: AL = character read
L1:
	mov ah,06h
	mov dl,0FFh
	int 21h
	jz L1		; DOS 06h input does not wait; loop until user input triggers ZF
	ret
ReadChar ENDP

ReadString PROC USES di bx
; Read string from keyboard. Stops when user presses ENTER key (0Dh)
; Requires: DX = offset of bytes where data is stored
;	    CX = max # of characters to be read
; Returns:  AX = count of bytes read
	mov di,dx
	mov bx,0
L1:
	call ReadChar
	cmp al,0Dh			; check for ENTER key
	je Break
	call WriteChar			; echo char to screen
	mov [di],al
	inc di
	inc bx
	loop L1
Break:
	mov ax,bx
	inc BYTE PTR [di]
	xor bx,bx
	mov [di],bl			; terminate the string
	ret
ReadString ENDP

WriteString PROC USES ax si
; Writes string to the screen
; Requires: DX = address of string
; Returns:  nothing
	mov si,dx
L1:
	mov ax,[si]
	cmp al,0			; check for terminator
	je Break
	call WriteChar
	inc si
	jmp L1
Break:
	ret
WriteString ENDP

CrLf PROC USES ax dx
; moves the cursor to a newline
	mov ah,06h
	mov dl,0Dh
	int 21h

	mov ah,06h
	mov dl,0Ah
	int 21h
	ret
CrLf ENDP

WriteDec PROC USES ax bx cx dx
; Write decimal digits to screen (i.e. binary to ASCII).
; Requires: AX = integer to be written
; Returns: nothing
	mov cx,0		; set the count to keep track of # of ASCII chars
	mov bx,10		; base 10 for decimal conversion
L1:
	xor dx,dx		; clear dx
	div bx
	add dx,30h		; convert result in dx to ASCII
	push dx
	inc cx
	cmp ax,0		; test for more chars
	ja L1
L2:
	pop dx
	mov ah,06h
	int 21h
	loop L2

	ret
WriteDec ENDP

WriteBin PROC USES ax bx cx
; Writes integer to screen (std  output) in ASCII BINARY format.
; Requires: AX = integer to be written
; Returns: nothing
	mov bx,ax
	mov cx,16
L1:
	shl bx,1		; shift msb into carry
	mov al,30h		; ASCII '0'
	jnc L2
	mov al,31h		; ASCII '1'

L2:
	call WriteChar
	loop L1

	ret
WriteBin ENDP

WriteChar PROC
; Writes character to screen
; Requires: AL = character to be written
	mov dl,al
	mov ah,06h
	int 21h
	ret
WriteChar ENDP

ReadDec PROC USES bx cx
; Read Decimal Digits from the keyboard (ie ASCII to Binary). Up to 4 digits assumed
; Returns: AX = value
	xor bx,bx
	xor cx,cx
L1:
	call ReadChar
	cmp al,0Dh
	je Break

	cmp al,30h		; sanitize for decimal input
	jb L1
	cmp al,39h
	ja L1

	inc cx			; decimal hit--increase count
	call WriteChar		; echo


	mov ah,00h
	sub al,30h
	push ax			; convert from ASCII and push to stack

	mov ax,bx
	
	push cx
	mov cx,10		; increase running total by power of 10
	mul cx
	pop cx
	
	pop bx
	add bx,ax		; add new value to running total 

	cmp cx,4		; up to 4 digits
	je Break
	jmp L1
Break:
	mov ax,bx
	ret
ReadDec ENDP

END main
