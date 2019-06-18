# Programming Assignment 1
## General Instructions
1. This is an individual programming assignment.
2. You are allowed to consult any Internet resource, books, the course TA, or the instructor. You are not allowed
to exchange code snippets or anything across groups. While you may read on general socket programming
on the Internet and look at code examples, this should be only for the purpose of understanding. Do all the
coding yourself, do not copy or cut-paste code from ANY website.
3. You can use only socket programming for the project. Do not use any sophisticated libraries downloaded
from the web.
4. You should use C/C++ for coding.
5. You should allocate sufficient time for testing your code.
6. It is important that your code has adequate comment and proper indentation. Comment during/before
coding, not at the end. For every variable/function you should have a comment. Use appropriate code
comments for explaining the logic where necessary.
7. Provide documentation for your code. This should explain the code structure in terms of directories, files,
how to compile etc. Detailed instructions for submitting the documentation along with code are at the end
of the document.
8. Choose proper and intuitive names for the variable, function, file, directory, etc.
9. All of the above aspects of your code will be evaluated, not just whether or not the code runs.
10. The below projects involve multiple hosts. You may want to write the code such that your code can be run on
a single host where the multiple hosts are mimicked by using the loopback address (127.0.0.1) with different
ports. This may help during the initial phases, where you need to do a lot of debugging. The IP address/port
specification for the different hosts is ideally provided through configuration files or as arguments to your
code.
## Assignment: File Transfer Over TCP
In this assignment, you will write a program over TCP to allow a client to download files from a server. The
detailed process is as follows.
1. The server starts and waits for incoming connection request.
2. The client establishes a TCP connection with the server.
3. The client sends a filename to the server over the TCP connection.
4. The server receives the filename.
5. If the file is not present, the server informs the client by sending back an error message.
6. If the file is present, the server continuously reads the file into a buffer and sends the buffer content to the
client until file-end is reached. File end is marked by EOF.
7. Once the transmission finishes, the client verifies that the received file is correct. You need decide the
mechanism that enables verification at the client.
8. The client chooses to download a different file or close the TCP connection and exit.
The user interface need not be sophisticated, but should be usable. It can be text-based or graphical. Your program
should use TCP sockets.
