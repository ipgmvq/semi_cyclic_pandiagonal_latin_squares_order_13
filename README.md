# Overview

This repository is created to publish a new computational fast algorithm of constructing semi-cyclic (including cyclic) pandiagonal Latin squares for an arbitrary order and the datasets of such squares with most interesting orders for cross-verification with other researchers.

# An environment to launch in
The first version is not multithreaded and designed for both the POSIX environments (Linux, macOS) and Windows. An additional version, which I will upload very soon, is going to be multithreaded, but suited for the POSIX environments only, because it employes POSIX threads.

# Usage
After compilation (for which the attached Makefile can be used), it is best launched from the Linux/macOS terminal or Windows PowerShell/Command Prompt. The file computes (semi)cyclic pandiagonal Latin squares of the order of 5 by default. It has a minimum limit of 3 and a maximum limit of 19, inclusive. In order to compute the squares in this range with the order other than 5, one needs to supply the order as a first parameter after the program file name in the Linux/macOS terminal or Windows PowerShell/Command Prompt respectively.

Windows
``` > latin.exe 13 ```

Linux/macOS
``` % ./latin.exe 13 ```

The output is saved in a text file with the .txt extension, with semi-cyclic and (fully) cyclic squares mixed together.
