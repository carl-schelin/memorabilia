@Echo Off
dosver
if errorlevel 6 goto dos6
if errorlevel 5 goto dos5
if errorlevel 4 goto dos4
if errorlevel 3 goto dos3
if errorlevel 2 goto dos2
if errorlevel 1 goto dos1
goto end
:dos1
echo Dos v1.x
goto end
:dos2
echo Dos v2.x
goto end
:dos3
echo Dos v3.x
goto end
:dos4
echo Dos v4.x
goto end
:dos5
echo Dos v5.x
goto end
:dos6
echo Dos v6.x
goto end
:end
