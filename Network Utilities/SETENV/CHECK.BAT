@Echo Off
SetEnv size %1
if errorlevel 1 goto toosmall
goto justright
:toosmall
echo It's too small
goto dos
:justright
echo It's just right
:dos
