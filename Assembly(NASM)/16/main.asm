%include "io.inc"

CEXTERN strlen
CEXTERN strstr
CEXTERN fopen
CEXTERN fread
CEXTERN fwrite
CEXTERN fclose
CEXTERN fscanf
CEXTERN strcmp
CEXTERN qsort
CEXTERN bsearch
CEXTERN fprintf

section .bss
a resb 20000001
addr resd 1000001
n resd 1
k resd 1
prov resd 1
q resb 101
ope resd 1
clo resd 1
eddx resd 1
ebbx resd 1
eccx resd 1

section .data
stri db "%s", 0
numb db "%d", 0
unumb db "%u", 0
inputt db "input.txt", 0
outputt db "output.txt", 0
rbb db "rw", 0
wbb db "w", 0
format_n db 10, 0
sizee dd 4194305
one dd -1

;----одна точка с запятой - отладочная  печать,
;----две точки с запятой - вспомогательный интересный код-----
section .text

stricomp:
PRINT_CHAR "="
mov eax, dword[esp+4]
PRINT_DEC 4,eax
xor eax, eax
ret

GLOBAL CMAIN
CMAIN:
mov edi, esp
and esp, -16

sub esp, 8
push rbb
push inputt
call fopen
mov dword[ope], eax
;PRINT_DEC 4,eax

sub esp, 4
push n
push numb
push dword[ope]
call fscanf

;--------считываем строки и числа
mov ecx, 0
mov edx, 0
loop:
lea ebx, [a]
add ebx, edx
;PRINT_DEC 4,ebx
mov esi, ecx
mov dword[eddx], edx

sub esp, 4
push ebx
push stri
push dword[ope]
call fscanf
;PRINT_UDEC 4,ebx
;NEWLINE

;;mov dword[ebbx], ebx
;;mov ebx, dword[ebx]
;;mov dword[prov], ebx
;;mov ebx, dword[ebbx]
;;PRINT_DEC  4,prov
;;sub esp, 8
;;push dword[prov]
;;push stri
;;call printf
;PRINT_CHAR "@"

mov edx, dword[eddx]
add edx, 128

lea ebx, [a]

add ebx, edx

;;mov ecx, esi
;;imul ecx, 4
;;add edx, ecx

sub esp, 4
push ebx
push unumb
push dword[ope]
call fscanf
;NEWLINE

;;PRINT_UDEC 4,ebx
;;NEWLINE
;;mov dword[ebbx], ebx
;;mov ebx, dword[ebx]
;;mov dword[prov], ebx
;;mov ebx, dword[ebbx]
;;PRINT_DEC  4,prov
;;sub esp, 8
;;push dword[prov]
;;push numb
;;call printf
;;PRINT_CHAR "@"

mov ecx, esi
lea esi, [addr]
mov edx, ecx
imul edx, 4
add esi, edx
sub ebx, 128
mov dword[ebbx], ebx
;mov ebx, dword[ebx]
;PRINT_DEC 4,ebx

;PRINT_CHAR "+"
mov ebx, dword[ebbx]
mov dword[esi], ebx
add ebx, 128
;;mov esi, dword[esi]

;NEWLINE
;PRINT_DEC  4, esi
;NEWLINE
mov edx, dword[eddx]
add edx, 144
add esp, 32
inc ecx
cmp ecx, dword[n]
JNE loop
;--------считываем строки и числа -----конец
;NEWLINE
;PRINT_CHAR "#"
lea ebx,[addr]
mov ebx, dword[ebx]
;PRINT_DEC 4,ebx
;NEWLINE
;;add ebx, 288
;;add ebx, 144
;;NEWLINE
;;PRINT_DEC 4,ebx

;;mov dword[prov], ebx
;;PRINT_DEC  4,prov
;;sub esp, 8
;;push dword[prov]
;;push stri
;;call printf
;PRINT_CHAR "@"
;PRINT_STRING prov
;NEWLINE

;;lea ebx, [addr] ;другой эффект, можно проверить, если вызвать stricomp
lea ebx, [a]
;;mov ebx, byte[ebx]
;;PRINT_DEC 1,ebx
push strcmp
push dword 144
push dword[n]
push ebx
call qsort
add esp, 16


;-----вывод отсортированных строк-----
;;mov ecx, 0
;;mov edx, 0
;;
;;loo:
;;lea ebx,[addr]
;;add ebx, ecx
;;mov dword[eccx], ecx
;;mov dword[eddx], edx
;;mov ebx, dword[ebx]
;;;;sub ebx, 128
;;;NEWLINE
;;;PRINT_DEC 4,ebx
;;;NEWLINE
;;sub esp,8
;;push ebx
;;push stri
;;call printf
;;add esp, 16
;;mov ecx, dword[eccx]
;;mov edx, dword[eddx]
;;inc edx
;;add ecx, 4
;;cmp edx, dword[n]
;;JNE loo
;;NEWLINE
;-----вывод отсортированных строк-----конец

;;sub esp,8
;;push ebx
;;push stri
;;call printf

;;lea ebx,[a]
;;add ebx, 128
;;mov ebx, dword[ebx]
;;PRINT_UDEC 4,ebx
;;NEWLINE

;;sub esp,8
;;push ebx
;;push unumb
;;call printf
;;PRINT_UDEC 4,eax

;---------------- 2 часть ---------

sub esp, 8
push wbb
push outputt
call fopen
mov dword[clo], eax

;;sub esp, 4
;;push dword[one]
;;push numb
;;push dword[clo]
;;call fprintf
;;add esp, 16
;;PRINT_DEC 4,eax
;;PRINT_CHAR "!"
;;NEWLINE

sub esp, 4
push k
push numb
push dword[ope]
call fscanf
;PRINT_DEC 4,k
mov ebx, 0

;NEWLINE
loopy:
sub esp, 4
push q
push stri
push dword[ope]
call fscanf

sub esp, 12
lea esi, [a]
push strcmp
push dword 144
push dword[n]
push esi
push q
call bsearch

add esp, 48
;PRINT_DEC 4, eax
;NEWLINE
cmp eax, 0
JE GO
add eax, 128
mov eax, dword[eax]
;PRINT_UDEC 4,eax
;NEWLINE

sub esp, 4
push eax
push unumb
push dword[clo]
call fprintf
add esp, 16

;PRINT_DEC 4,eax
;NEWLINE
JMP NEX
GO:
sub esp, 4
push dword[one]
push numb
push dword[clo]
call fprintf
add esp, 16
NEX:
sub esp, 4
push format_n
push stri
push dword[clo]
call fprintf
add esp, 16

;PRINT_STRING q
;NEWLINE
inc ebx
cmp ebx, dword[k]
JNE loopy

GOOD:

sub esp, 12
push dword[ope]
call fclose

sub esp, 12
push dword[clo]
call fclose

mov esp, edi
xor eax, eax
ret