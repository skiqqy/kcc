kcc
===

[![Build Status](https://travis-ci.com/Skippy404/kcc.svg?branch=master)](https://travis-ci.com/Skippy404/kcc)

---

You've heard of GCC, cc and clang. Now get ready for: kcc, aka the Kak C Compiler

---

## About the project

The aim of the project is to write a fully working C compiler, the compiler
will be broken down into 4 stages, namely

* scanning
* parsing
* typechecking
* codegen

This list will most likely be updated.

---

## Compiling

For compilation we will be using a Makefile, with each section having its own
'test' program, to ensure that that section of the larger project is working.

To compile the entire project, simply type `make`, each sub group will be
compiled like so:

* test scanner
````
make testscanner
````

---

* test parser
````
make testparser
````

---

* test typechecking
````
make testtype
````

---

* test codegen
````
make testcode
````

---

## Other

If you would like to join the project, please send an email to
skippycochrane@gmail.com
