@Echo Off
If "%1"=="" Goto NoParms
OnceADay %1
If ErrorLevel 2 Goto NoOpen
If ErrorLevel 1 Goto NoMatch
Echo no upgrades or checks...
Goto Dos
:NoOpen
Echo Can't open files
Goto Dos
:nomatch
Echo upgrade in process...
Goto Dos
:NoParms
Echo Forgot the parameters...
:Dos
