/* ********************************************************************

   MPP - a MUSH "pre-processor"
   Version 1.1
   Joshua Bell, jsbell@acs.ucalgary.ca

   Syntax:
   ~~~~~~~
        Unix:   mpp < infile > outfile
        TF/VT:  /quote !mpp < infile


   Compilation:
   ~~~~~~~~~~~~
   1. Save this file as mpp.c

   2. From Unix type:

	cc -o mpp mpp.c
   Or:
	gcc -o mpp mpp.c


   Parsing rules for mpp:
   ~~~~~~~~~~~~~~~~~~~~~~
   (Whitespace is spaces and/or tabs.)

   1. Blank lines and lines starting with @@ are stripped.
   In other words, comment lines are removed.

   2. A non-whitespace, non-'>' character in the first
   column indicates the start of a new line of MUSHcode.
   So start new commands in the first columns.

   3. Leading whitespace on a line is otherwise stripped,
   and indicates the line is a continuation of the previous
   line. So indent contination lines.

   4. Lines starting with '>' (in the first column) are treated
   as continuations and are converted from plain ASCII to
   "MUSH-ready" ASCII, i.e. spaces -> %b, [ -> \[, etc. %r
   characters are prepended to any subsequent > lines.
   This is for embedding formatted text.

   5. In any other line, each tab is converted to a space.
   Width is not conserved.

   Example:
   ~~~~~~~~
---- CUT HERE ----
@@ MUSHcode Demo 1.0
@@ by Joshua Bell, jsbell@acs.ucalgary.ca

&ALPHA beta=$gamma *:
        @switch %0=delta,{

@@ They typed "gamma delta"

                @pemit %#=

> / You have typed Delta \
> \    Prepare to die.   /

        },{
@@ Else
		@trigger me/Epsilon=%#,%0
        };

	@trigger me/vaporize=%#

@va me=Test Case
---- CUT HERE ----

   Converts to:

---- CUT HERE ----

&ALPHA beta=$gamma *:@switch %0=delta,{@pemit %#=%b/%bYou%bhave%btyped%bDelta%b\\%r%b\\%b%b%b%bPrepare%bto%bdie.%b%b%b/},{@trigger me/Epsilon=%#,%0};@trigger me/vaporize=%#
@va me=Test Case
---- CUT HERE ----
********************************************************************** */

#include <stdio.h>

#define FORMATTED 1

main() {
  char b[8192];    /* Buffer for input. Probably too much. */
  int i,           /* Pointer w/in string. */
  a = !FORMATTED;  /* ASCII state flag */

  while(gets(b)==b) {    /* Grab string from standard input */
    i = 0;

    /************************************************************
     * Determine type of line
     */

    /****************************************
     * Comment or blank
     */
    if ((b[0] == '\0') || ((b[0] == '@') && (b[1] == '@')))
      continue;

    /****************************************
     * Formatted text
     */
    if (b[0] == '>') {

      /* Insert a newline if last was line was formatted as well */
      if (a == FORMATTED) {
	putchar('%'); putchar('r');
      }

      a = FORMATTED;
      i++;			/* Skip tag */

    /****************************************
     * Continued line - skip whitespace
     */
    } else if ( (b[0] == ' ') || (b[0] == '\t')) {

      a = !FORMATTED;
      for (; (b[i]==' ') || (b[i]=='\t') ; i++);

    /****************************************
     * New line - end old one
     */
    } else {

      putchar('\n');
      a = !FORMATTED;
    }

    /************************************************************
     * Now output line, converting as necessary
     */
    for( ; b[i] ; i++) {                         /* Stop at end-of-line */

      if (a == FORMATTED) {

	switch (b[i]) {
	case '\t':
	  putchar('%');  putchar('t');  break;
	case ' ' :
	  putchar('%');  putchar('b');  break;
	case '\\':
	case '%' :
	case '[' :
	case ']' :
	case '(' :
	case ')' :
	case '{' :
	case '}' :
	  putchar('\\');
	default:
	  putchar(b[i]);
	}

      } else if (b[i] == '\t') {          /* If a tab, generate a space */
	putchar(' ');

      } else {
	putchar(b[i]);                    /* Otherwise, just output */
      }
    }
  }
  putchar('\n');                          /* Newline when input ends */
}
