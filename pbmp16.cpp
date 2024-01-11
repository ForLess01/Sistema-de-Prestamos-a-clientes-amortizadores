#include "gBMP16.h" 

void main(){
	cBMP16 oBMPzigzag;
	oBMPzigzag.PresentaBMP();

	cBMP16 oBMPrombos("c:\\windows\\rombos.bmp");
	oBMPrombos.PresentaBMP();

	cBMP16 oBMParos("c:\\windows\\aros. bmp ");
	oBMParos.PresentaBMP();
}
