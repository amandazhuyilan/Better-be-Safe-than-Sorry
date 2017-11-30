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
 
 






