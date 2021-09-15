@Echo Off
If "%1"=="" Goto NoParms
If "%2"=="" Goto NoParms
ChkDate %1 %2
If ErrorLevel 3 Goto NoFiles
If ErrorLevel 2 Goto NoOpen
If ErrorLevel 1 Goto Older
Echo %1 is newer than %2
Goto Dos
:NoFiles
Echo No files specified
Goto Dos
:NoOpen
Echo Can't open files
Goto Dos
:Older
Echo %1 is older than %2
Goto Dos
:NoParms
Echo Forgot the parameters...
:Dos
