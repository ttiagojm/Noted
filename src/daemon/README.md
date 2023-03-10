# Dependencies
* [libcurl](https://curl.se/download.html)
* [MingW (Installation Tutorial)](https://www.geeksforgeeks.org/installing-mingw-tools-for-c-c-and-changing-environment-variable/)

# How to use
* First , go to the makefile and change the `CURLPATH` variable to the libcurl path folder (where you have bin, include and lib folders)
* Second, make sure to put the libcurl `bin` in your environment Path variables
* Third, for compilation you have 2 options:
    * make: Compile the main executable
    * make test: Compile the unit test executable
* Fourth, you need to pass the path of a `cacert.pem` file (you can downlaod it [here](https://curl.se/ca/cacert.pem)):
    * `executable.exe /your/cacert/path/cacert.pem`
* Fifth, be happy

**This program is under development, this mini tutorial can change!**