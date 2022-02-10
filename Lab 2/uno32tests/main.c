/* main.c

   This file written 2015 by F Lundevall and David Broman

   Latest update 2015-09-15 by David Broman

   For copyright and licensing, see file COPYING */

#include <stddef.h>   /* Declarations of integer sizes and the like, part 1 */
#include <stdint.h>   /* Declarations of integer sizes and the like, part 2 */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

void saveinfo(char s[], void * a, size_t ns );
void showinfo(void);
void u32init(void);

int gv; /* Global variable. */
int in = 3; /* Global variable, initialized to 4711. */

void fun(int param)
{
  param++;
  saveword( "AF1: param", &param );
  gv = param; /* Change the value of a global variable. */
}

/* This is the main function */
int main()
{
  /* Local variables. */
  int m;
  int * p; /* Declare p as pointer, so that p can hold an address. */
  char cs[9] = "Bonjour!";
  char *cp = cs; /* Declare cp as pointer, initialise cp to point to cs */

  /* Do some calculation. */
  gv = 4;
  m = gv + in;

  /* Check the addresses and values of some variables and stuff */
  saveword( "AM1: gv", &gv );
  saveword( "AM2: in", &in );
  saveword( "AM3: fun", &fun );
  saveword( "AM4: main", &main );

  //P gets the adress of m
  p = &m;

  /* Check p and m */
  saveword( "AM5: p", &p );
  saveword( "AM6: m", &m );

  /* Change *p */
  //Add one to p's value
  *p = *p + 1;

  /* Check p and m */
  saveword( "AM7: p", &p );
  saveword( "AM8: m", &m );

  p = (int*)cp; /* Casting a char pointer to an integer pointer */

  saveword( "AM9: p", &p );

  savebyte( "AM10: cs[0]", &cs[0] );
  savebyte( "AM11: cs[1]", &cs[1] );
  savebyte( "AM12: cs[2]", &cs[2] );
  savebyte( "AM13: cs[3]", &cs[3] );

  //Change the value of p to 0x1234abcd
  *p = 0x1234abcd; /* It starts to get interesting... */

  savebyte( "AM14: cs[0]", &cs[0] );
  savebyte( "AM15: cs[1]", &cs[1] ); 
  savebyte( "AM16: cs[2]", &cs[2] );
  savebyte( "AM17: cs[3]", &cs[3] );

  //Add one to m, saveword and then overwrite gv
  fun(m);

  /* Re-check the addresses and values of m and gv */
  saveword( "AM18: m", &m );
  saveword( "AM19: gv", &gv );

  showinfo();
}

/* QUESTIONS
1. AM19(gv) gets bigger than AM18(m) because of fun(m), that adds 1 to m and save it to gv, while m is unmodified.
   AF1 gets the same value that AM19(gv) have, from the fun function, with the saveword istruction.

2. The cp pointer is the size of 1 byte, beacuase it points on a char.

3. The cp pointer points at 9 bytes because of 8 chars for Bonjour! and one ending null byte.

4. We check AM3 for the adress of fun: 0x9D001180 and AM4 for the adress of main: 0x9D0011D8 on the IO Sheild Display.
   They are located in the Program Flash according to the PIC32 memory map. That are in the Kernal Space.
   The data section is a pointer that points to the first row of the machine code in main respectively  fun. 

EXTRA

1. We check AM2 for the adress of in: 0xA0000008 and AM1 for the adress of gv: 0xA000000C on the IO Sheild Display.
   They are located in the RAM according to the PIC32 memory map. Because the variables are stored in the RAM, because variables doesn't have to be stored when the program stops.

2. We check AM5 for the adress of p. 0xA0003FE8 and AM6 for the adress of m: 0xA0003FE4.
   Both are local variables. They are located in Reserved according to the PIC32 memory map.
   They have a much bigger adress than in and gv, because they are local variables, instead of global variables. The global variables gets loaded first and later the local variables when they are first used.

3. The adress of p. 0xA0003FE8 and it points at the adress 0xA0003FE4, which is adress for m and m has the data 0x7.

3. The adress of p. 0xA0003FE8 and it points at the adress 0xA0003FE4, which is adress for m and m has the data 0x8. It's one bigger because of *p = *p + 1.

5. Little-endian, because it reads 0x1234abcd from the right to the left, so cs[0] = CD, cs[1] = AB and so on. So the lsb comes before msb.

*/
