# Writing a NSS module

NSS as name service switch is a part of *glibc*. The standard itself is part of Posix:

Documentation:

- https://github.com/google/nsscache/wiki/BackgroundOnNameServiceSwitch
- http://www.gnu.org/software/libc/manual/html_node/NSS-Modules-Interface.html#NSS-Modules-Interface
- http://www.gnu.org/software/libc/manual/html_node/NSS-Module-Function-Internals.html#NSS-Module-Function-Internals
- http://www.linuxquestions.org/questions/programming-9/writing-nss-module-904131/
- http://stackoverflow.com/questions/16366571/adding-a-service-to-name-service-switch
- https://wiki.freebsd.org/NsswitchModulesSeparation
- using syslog: http://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html

How to create a module? NSS loads modules dynamically via dlopen. So only a .so file named like libnss-mysql.so.2 with some api must be created and added to library load path.