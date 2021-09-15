@Echo Off
QColor S
If ErrorLevel 1 Goto Color
Goto Mono
:Color
Set S_Monitor=Color
Goto Dos
:Mono
Set S_Monitor=Mono
:Dos
