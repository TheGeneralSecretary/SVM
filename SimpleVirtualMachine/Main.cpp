#include "SimpleVirtualMachine.h"

/*
* MAX PROGRAM SIZE 1024
* MAX STACK SIZE 256
* 
PUSH 6      ; PUSH 6 STACK
PUSH 3		; PUSH 3 STACK
POP         ; POP

HLT         ; STOP PROGRAM
SET SVA 0   ; SET REGISTER SVA 0
MOV SVD, SVA; SET SVD SVA

ADD			; POP2 ADD PUSH
SUB			; POP2 SUB PUSH
MUL			; POP2 MUL PUSH
DIV			; POP2 DIV PUSH
*/

int main()
{
	SVM::SimpleVirtualMachine SVM;
	SVM.Init("Sample.SVM");
	SVM.Emulate();
	return 0;
}
