#!/bin/bash

echo "[1/5] Compiling C Core Terminal..."
gcc terminal.c -o mini-term

echo "[2/5] Assembling x86_64 Assembly Module..."
nasm -f elf64 sysinfo.asm -o sysinfo.o
ld sysinfo.o -o sysinfo

echo "[3/5] Compiling C++ Processor Utility..."
g++ squarer.cpp -o squarer

echo "[4/5] Compiling C# Engine Container..."
dotnet new console -o GreeterApp --force > /dev/null
cp Program.cs GreeterApp/Program.cs
dotnet build GreeterApp -c Release -o ./bin > /dev/null
cp ./bin/GreeterApp greeter

echo -e "\n[5/5] Launching Mini-Terminal Environments...\n"
# Execute our core C terminal
./mini-term

echo -e "\nExited Mini-Term. Cleaning binaries..."
rm -rf mini-term sysinfo sysinfo.o squarer greeter GreeterApp bin obj
