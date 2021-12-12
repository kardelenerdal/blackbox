/*
 * How to save, compile, and run:
 * sudo apt install rpcinfo // to use rpcinfo, run once
 * Save file with .x extension.
 *
 * rpcgen -C add.x // -C for creating all the files, generate code in ANSI C.
 * rpcgen -a add.x // -a generate all the files including sample code for client and server side.
 * make -f Makefile.add // -f to use given file as a makefile.
 */

/* Specify the arguments */
struct numbers{
	int a;
	int b;
	char pathOfBlackbox[500];
};

/* 
 * 1. Name the program and give it a unique number.
 * 2. Specify the version of the program.
 * 3. Specify the signature of the program.
*/
program BLACKBOX_PROG{
	version BLACKBOX_VERS{
		/* Takes a numbers structure and gives the integer result. */
		string blackbox(numbers)=1;
	}=1;
}=0x12345678;