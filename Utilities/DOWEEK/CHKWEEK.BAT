@Echo Off
DoWeek
If ErrorLevel 6 Goto Sat
If ErrorLevel 5 Goto fri
If ErrorLevel 4 Goto thu
If ErrorLevel 3 Goto wed
If ErrorLevel 2 Goto tue
If ErrorLevel 1 Goto mon
goto sun
:Sun
Echo It's Sunday!
Goto Dos
:Mon
Echo It's Monday!
Goto Dos
:Tue
Echo It's Tuesday!
Goto Dos
:Wed
Echo It's Wednesday!
Goto Dos
:Thu
Echo It's Thursday!
Goto Dos
:Fri
Echo It's Friday!
Goto Dos
:Sat
Echo It's Saturday!
Goto Dos
:Dos
