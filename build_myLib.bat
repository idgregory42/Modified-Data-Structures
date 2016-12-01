@echo off
cls

set CXXFLAGS=-g -O0

::Set drive letter if no args given
if [%1] == [] goto noArgs
goto yesArgs

:noArgs
set DRIVE_LETTER=%CD:~0,2%
goto continue

:yesArgs
set DRIVE_LETTER=%1:
:continue
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin

g++ %CXXFLAGS% -c AVLTree.cpp
g++ %CXXFLAGS% -c AVLTreeIterator.cpp
g++ %CXXFLAGS% -c AVLTreeNode.cpp


IF EXIST "libDataLib.a" (
	move "libDataLib.a" "libDataLib.a.old"
)

ar -r libDataLib.a *.o

del *.o

pause