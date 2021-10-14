# My First COM Server

Some lovely examples from the book
["Developer's Workshop to COM and ATL 3.0" by Andrew Troelsen](https://archive.org/details/developersworksh00andr/)

## Notes on building

Run `build.cmd` from a VC x64 command prompt - install the VS build tools.

## Lab 3-1

COM interfaces demonstrated in a single CPP project without class registration.

## Lab 3-2

COM in-proc server binary complete with class registration.

Run `reg import ClassRegistration.reg` to register classes (not implemented in the binary yet)

## Lab 3-3

Consuming the in-proc server binary from 3-2