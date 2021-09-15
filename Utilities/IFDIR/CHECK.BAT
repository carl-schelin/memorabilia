@Echo Off
IfDir %1
If ErrorLevel 2 Goto NoPath
If ErrorLevel 1 Goto NoFound
Goto Found
:NoPath
Echo No Path Specified. USAGE: IfDir [D:[Path]]
Goto Dos
:NoFound
Echo Not a valid subdirectory.
Goto Dos
:Found
Echo Found %1!
Goto Dos
:Dos
