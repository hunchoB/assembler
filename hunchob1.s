.data
str_d:
.asciz "%d\n"
array:
.long 1, 2, 1, 3, 2, 4, 1, 2, 1, 2

.set count_el, (.-array)/4


.globl main
.type main, @function
.text


main:

lea array, %esi
mov $count_el, %ecx
 
for:
  movl (%esi), %eax
  test $1, %eax
  jz even
    sar $1, %eax
    jmp next
  even:
    shl $1, %eax
next:
  movl %eax, (%esi)
  addl $4, %esi
loop for
xor %eax, %eax
ret

