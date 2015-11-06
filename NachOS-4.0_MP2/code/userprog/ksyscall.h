/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"

#include "synchconsole.h"

OpenFileId SysOpen(char *name)
{
	return kernel->interrupt->Open(name);
}

int SysWrite(char *buffer, int size, OpenFileId fid)
{
	return kernel->interrupt->Write(buffer, size, fid);
}

int SysRead(char *buffer, int size, OpenFileId fid)
{
	return kernel->interrupt->Read(buffer, size, fid);
}

int SysClose(int fid)
{
	return kernel->interrupt->Close(fid);
}

void SysPrintInt(int number)
{
	if(number < 0) kernel->synchConsoleOut->PutChar('-'), number = -number;

	char tmp[20];
	int cnt = 0;
	while(number) {
		tmp[cnt++] = number % 10 + '0';
		number /= 10;
	}

	while(cnt) {
		kernel->synchConsoleOut->PutChar(tmp[--cnt]);
	}

	kernel->synchConsoleOut->PutChar('\n');

}

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysCreate(char *filename)
{
	// return value
	// 1: success
	// 0: failed
	return kernel->interrupt->CreateFile(filename);
}


#endif /* ! __USERPROG_KSYSCALL_H__ */
