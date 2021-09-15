@Echo Off
Space %1 %2 > Nul
If ErrorLevel 3 Goto Syntax
If ErrorLevel 2 Goto BadDrive
If ErrorLevel 1 Goto NoSpace
Echo There is enough space...
Goto Dos
:NoSpace
Echo Not enough room on %1...
Goto Dos
:BadDrive
Echo %1 is an invalid drive...
Goto Dos
:Syntax
Echo You blew it!
Goto Dos
:Dos
