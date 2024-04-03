Assignment 4 CMPT300 Spring 2024

Members:
- Huynh Vuong The Nguyen (301450119)
- Leang Paul Kho (301563533)

Instructors : 	Harinder Khangura

Instructions for Executing the Program:

1) Run `make`
2) Execute the program using the following command:
   ./UnixLs <options> <files>

   List of available options:
   -l    : Displays the contents of the current directory in a long listing format, one per line.
   -i    : Displays the index number of the file in the current directory.
   -li   : Displays both options.

   List of files:
   - `.`   : Current directory.
   - `..`  : Parent directory.
   - `~/[specify the file directory]` : Specify the file directory.

   Example Usage:
   - ./UnixLs -l .
   - ./UnixLs -li ..
   - ./UnixLs -i ~/CMPT300
   - ./UnixLs   : Returns the file names in the current working directory.

Additional Information About Our Implementation:
1) The list of options section of the command must start with a hyphen (-).
2) The available options are either 'l' or 'i' or a combination of those. For example, '-llli' will return the result for '-li'.
3) You can specify multiple options and multiple files. For example: ./UnixLs -li .. . ~/CMPT300
