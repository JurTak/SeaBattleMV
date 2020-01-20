@echo off

set Path=C:\Program Files\CodeBlocks\MinGW\bin;C:\Program Files (x86)\CodeBlocks\MinGW\bin

mkdir Bin

echo compiling...

windres SBMV.rc -O coff -o Bin\SBMV.res

g++ -mwindows -s -Os "Sea Battle MV.cpp" Bin\SBMV.res -o "Bin\Sea Battle MV" -lws2_32

pause