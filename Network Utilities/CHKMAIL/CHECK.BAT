@Echo Off
ChkMail
If ErrorLevel 2 Goto NotLogged
If ErrorLevel 1 Goto Mail
Goto NoMail
:NotLogged
Echo Not logged in, return to calling program...
Goto Dos
:Mail
Echo You have mail, on our way to E-Mail...
Goto Dos
:NoMail
Echo You don't have mail. Return to calling program...
:Dos
