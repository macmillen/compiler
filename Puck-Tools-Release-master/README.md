# Release Notes

## 25.06.2018 - New Compiler
* The compiler is now fixed and correctly compiles all examples.
* Array indices are now checked.

## 06.06.2018 - Linker Update:

* The -out switch of puckln now specifies the output file, and not the output directory.
  This means other filenames than object.procedure.x are possible.

# Documentation

The tools need a minimum of Java 9

To build an executable out of the example the following steps need to be taken:

Change working directory to the directory, that contains the .jar files

Compile example to assembly:
java -jar spl.jar -i example/helloworld.spl -o example/helloworld.a

Assemble example to object file:
java -jar puckasm.jar example/helloworld.a

Assemble standard library:
java -jar puckasm.jar spllib/spllib.a

Copy object files to staging:
cp example/helloworld.o stage/helloworld.o
cp spllib/spllib.o stage/spllib.o

Link object files:
java -jar puckln.jar helloworld.o -op stage/ -out bin/helloworld.x -proc main

The bin folder now contains helloworld.x, which is an executable for the Puck Virtual Machine.


The Virtual Machine can be downloaded by using 
git clone git@git.thm.de:Compilerbau/Puck-Virtual-Machine.git

To build it, follow the instructions of the ReadMe

Afterwards you can copy the executable to all the other paths using 
cp Puck-Virtual-Machine/puck puck

To finally execute the program use
./puck bin/helloworld.x

Please note, that we do not guarantee the correctness of any of the used tools.