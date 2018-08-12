# Release Notes

## 27.06.2018 V1.2.1 - Consistency Fixes
* Debugger output is adjusted to show more consistency
* Operator instructions now show their values in signed, unsigned, and hex form.
  This is useful when doing arithmetic with addresses.

## 12.06.2018 V1.2 - Debugger V2:
* Added debugger command "m" for memory inspection.
* Added debugger command "l" to list instructions at a certain address.
      Note: The Virtual Machine does not distinguish between data and code. Because instructions have different lengths, to find "correct" instructions, it currently scans the machine memory from the start.
	  This approach breaks down when you are using static data. The language SPL has no need for static data, so this should not be a problem for now.

## 06.06.2018 V1.1 - Debugger:

* Added extensive debugger with breakpoints, single step execution, register inspection and code inspection. 
	  It is started by using the --debug command line switch and will immediately trigger a breakpoints.
	  Use the "?" command when execution is paused to 
	  When an interrupt is thrown the 
* Added the "--interupt-when-writing-code" command line switch. When specified the virtual machine will throw an interrupt whenever there is a store instruction affecting a data area the machine registers as code.


# Building
This is the repository for the Puck Virtual Machine.
It is a C++ Project, using the boost libraries.

It can be build by generating build files for the various plattforms using cmake.
IMPORTANT: The cmake version in your package manager might not be up to date.
Refer to https://askubuntu.com/a/865294/642361 for instructions to install the latest version.
On Linux the call is simply

~~~~
cd path/to/project
cmake .
make
~~~~

# Documentation
The Puck Virtual Machine is a very simple virtual machine that has a lot of similarities to the ECO32 by Prof. Geisse.
It is designed for maximum simplicity for Compiler Engineering courses and can be used as a target platform for many languages.

It does not have a graphical display, to ensure platform independence.
Runtime performance is not a concern, as this virtual machine is only used for teaching purposes.

The virtual machine executes Puck Executables, which are created by the Puck linker and Puck assembler.
Those tools are available separately.

The virtual machine is invoked with:

~~~~
.\puck --input-file path/to/executable
~~~~

The following command line options are available:

| Option                       |  Effect                                                                  |
| ---------------------------- |:-------------------------------------------------------------------------|
| --input-file <path>          | Sets the executable file                                                 |
| --debug                      | Activates the debugger                                                   |
| --interupt-when-writing-code | Execution is interrupted when executing a memory store in the code area  |

# Contribute

Bug reports and Feature requests are greatly appreciated. Please use GitLab Issues for this purpose.

To contribute please fork the repository and submit a pull request when you are done. 
If your feature is finished you may create a merge request for the master branch and wait for your request to be accepted.

Additions to the debugger are currently appreciated the most
