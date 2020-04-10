.data
str_d:
.asciz "%d\n"
array:
.byte 1, 2, 1, 3, 2, 4, 1, 2, 1, 2

.set count_el, (.-array)/4


.globl main
.type main, @function
.text


main:

movl $0, %ecx
/*movl $2, %ebx*/
movl array, %eax
jmp is_last



shift:
movl array(,%ecx,1), %eax
test $1, %eax
jz arithmetic
shl $1, %eax
jge adding

arithmetic:
sar $1, %eax
jge adding

adding:
inc %ecx

is_last:
cmpl $count_el, %ecx
jl shift
xor %eax, %eax
ret

