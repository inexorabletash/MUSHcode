## MUSHcode utilities

A collection of globals for MUSHes. I haven't worked on these in ~20
years so the state of the art may have advanced, and my recollection
of details may be a bit hazy. Use them if they're useful to you.

All of the contact information for these is obsolete.

Most of these were developed for various incarnations of NarniaMUSH,
where I was wizarding as Tash or Algol in the early 1990s.

### MPP - a MUSH "pre-processor"

This is a command line utility written in C that lets you write nicely
formatted MUSHcode in text files and preprocess them into valid code
before uploading. (I recall this could be done in one step from
dedicated MUD clients.)

Input:
```
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
```
Output:
```
&ALPHA beta=$gamma *:@switch %0=delta,{@pemit %#=%b/%bYou%bhave%btyped%bDelta%b\\%r%b\\%b%b%b%bPrepare%bto%bdie.%b%b%b/},{@trigger me/Epsilon=%#,%0};@trigger me/vaporize=%#
@va me=Test Case
```

Parsing/formatting rules:

1. Blank lines and lines starting with `@@` are stripped.

2. A non-whitespace, non-`>` character in the first column indicates
   the start of a new line of MUSHcode.

3. Leading whitespace on a line is otherwise stripped, and indicates
   the line is a continuation of the previous line.

4. Lines starting with `>` (in the first column) are treated as
   continuations and are converted from plain ASCII to "MUSH-ready"
   ASCII, i.e. spaces -> `%b`, [ -> `\[`, etc. `%r` characters are
   prepended to any subsequent `>` lines.

5. In any other line, each tab is converted to a space. Width is not
   conserved.

Most of the MUSHcode examples in this repo require processing with MPP
before uploading.

### Dynamic Space

This code lets you set up rectilinear grids of rooms that only exist
when needed. This is useful for doing sky areas, oceans, terrain, or
even the surfaces of entire planets!

Included is an optional module for mapped spaces. This code allows you
to define vast areas of a Dynamic Space with default names, descs,
succs, etc, by the use of a simple-to-create ASCII map. The normal
room altering commands provided by the Dynamic Space system override
anything created by the Map module, so these areas can be further
customized.

### Mail System

Yet another MUSH mail system.

This one does not generate mailbox objects. Instead it uses attributes
with only wizard visibility applied to the character objects.

### Money

A money system developed for NarniaMUSH.

### PEX

A set of "pretty examine" globals that output formatted MUSHcode.
This is basically the inverse of MPP.
