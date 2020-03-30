# Lines starting with # are comments

# These are variables, and can be used by surrounding them in $(...).
# CC and CFLAGS are used by make in its default rules, and refer to the
#   C compiler, and flags for the compiler respectively.
CC = gcc
CFLAGS = -Wall -Werror -lm -std=c11 

###############################################################################
# Rules (also called recipes) are written as NAME: DEPENDENCIES, and define
#   how make should compile different things.
# The lines following a rule definition specify the exact instructions to run.
# Don't forget to indent them.
# The very first rule in a make file is the one run when you don't specify a
#   rule. If you ran "make" alone, it would run this rule.
# Unless the dependencies are edited, or the target (hello in this case) is
#   deleted, make won't run the command. This means you can have many rules
#   which all run, but only the ones that need to run will.
inverted: invertedIndex.c string_manipulate.c InvertedIndexBST.c FileList.c  
	$(CC) $(CFLAGS) $^ -o inverted
# The above line would be interpreted as:
#   gcc -Wall -Werror hello.c -o hello
# If you want to specify the rule, you can run "make hello"

###############################################################################
# If you don't specify any commands in a rule, make will try and compile it
#   using one of its built-in rules.

# goodbye: goodbye.c


# On my computer, this rule is interpreted as:
#   gcc -Wall -Werror goodbye.c -o goodbye
# Notice how the values I assigned to CC and CFLAGS were used, even though
#   it's a built-in rule.

###############################################################################
# You can also combine rules together, so you only have to run one make command
#   and it will run multiple rules
# Again, the rule won't do anything if the files haven't been changed.
# If you were to edit hello.c ("touch hello.c" works, since it modifies the
# last modified time) and run this rule, it would recompile hello, but not
# goodbye, since the goodbye rule doesn't need to update anything


# greetings: goodbye hello

# You can also nest these rules.
# The following rule compiles both grettings, double, and dubstep


# all: greetings double dubstep

###############################################################################
# The compiler uses object files during compilation. C files are "compiled" to
#   object files (usually .o files) independently of each other, then linked
#   together at the end. This linking is when functions defined in different
#   files get combined, into one file.
# You may have seen an error message like the following before:
#   (.text+0x20): undefined reference to `main'
#	collect2: error: ld returned 1 exit status
# This error is caused by the linking step, when it attempts to locate the
#   functions defined in other files. In this case, there is no main function,
#   so the linker wasn't able to "link" a call to main, with the actual
#   function.
# These object files allow larger projects to recompile much faster. If a .c
#   file hasn't been modified, but other files used to make an executable have,
#   then a rule such as the following will have to recompile both files:


# baddouble: double1.c double2.c
# 	$(CC) $(CFLAGS) double1.c double2.c -o double

# If, however, each file is compiled to an object file first, only one needs to
#   be recompiled, then both object files can be linked. (much faster for big
#   files)
# gcc can link object files together itself as well.



# double: double1.o double2.o
# 	$(CC) $(CFLAGS) double1.o double2.o -o double




# Try editing one of the files, and run "make double".
# Only one of the object files should be recompiled, then both linked together.

###############################################################################
# Rules don't always have to compile programs. Sometimes they're used for
#   utilities. A clean rule is very common, and deleted all the compiled
#   parts of a program, so you can recompile a "clean" version, in case
#   make thinks everything's fine, but files have been edited
# The .PHONY tells make that the clean rule doesn't compile into anything
# This means that make won't try to check if the "clean" file exists before
#   running the commands, so it will always run.
# If there was no .PHONY here, and a file named "clean" was in the directory,
#   the rule wouldn't run unless it was deleted.



# .PHONY: clean
# clean:
# 	rm -f hello goodbye double dubstep *.o



# The *.o part removes all object files (all files ending in .o).
# These kinds of rules can contain anything you want really.

###############################################################################
# There are some special "variables" you can use to avoid repeating things.
# The main ones you might find useful are:
#   $@ is the name of the rule (e.g. double, goodbye, etc.)
#   $^ is a list of all prerequisites (e.g. double1.c double2.c)
#   $< is the name of the first prerequisite (e.g. double1.c)
# We could re-write the double rule as:



# dubstep: double1.o double2.o
# 	$(CC) $(CFLAGS) $^ -o $@




###############################################################################
# Any more than this is well beyond what you'd need for 2521 (even this much is
#   probably more than you'll use), but here's some fun things you might want
#   to try to do yourself:
#
#   You can get gcc to write rules for you, which include all used header files
#	  as dependencies. How do you do this?
#   You can specify a certain goal as the default goal, rather than it always
#     being the first rule in the makefile. How do you do this?
#   You can make it so variables have different values in different patterns.
#     For example, so that CFLAGS is "-c" when you're running any rule in the
#     form "(something).o : (something else)". How do you do this?