@Echo Off
QColor
If ErrorLevel 11 Goto VGA
If ErrorLevel 10 Goto MCGA
If ErrorLevel  9 Goto EGA
If ErrorLevel  8 Goto CGA
If ErrorLevel  7 Goto Incolor
If ErrorLevel  6 Goto HercPlus
If ErrorLevel  5 Goto Herc
If ErrorLevel  4 Goto VGAMono
If ErrorLevel  3 Goto MCGAMono
If ErrorLevel  2 Goto EGAMono
If ErrorLevel  1 Goto Mono
Goto Error
:VGA
Echo VGA Color
Goto Dos
:MCGA
Echo MCGA Color
Goto Dos
:EGA
Echo EGA Color
Goto Dos
:CGA
Echo CGA Color
Goto Dos
:Incolor
Echo Hercules InColor
Goto Dos
:HercPlus
Echo Hercules Graphics Plus
Goto Dos
:Herc
Echo Hercules Graphics
Goto Dos
:VGAMono
Echo VGA Monochrome
Goto Dos
:MCGAMono
Echo MCGA Monochrome
Goto Dos
:EGAMono
Echo EGA Monochrome
Goto Dos
:Mono
Echo Monochrome
Goto Dos
:Error
Echo Hey! Something is wrong!
:Dos
