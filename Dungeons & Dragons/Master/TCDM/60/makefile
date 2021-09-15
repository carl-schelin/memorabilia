PROGNAME=tcdm
MODEL=l
COMPILER=bcc
LINKER=TLink

!If $d(DEBUG)

DEBLIB=d
OBJSW=-c -K -w -d -N- -k- -O -Z -v -I$(INCLUDE) -m$(MODEL)
LNKSW=/v /L$(LIB) 

!Else

OBJSW=-c -K -w -d -N- -k- -O -Z -I$(INCLUDE) -m$(MODEL)
LNKSW=/x /L$(LIB) 

!EndIf

.cpp.obj:
  $(COMPILER) $(OBJSW) {$< }

.c.obj:
  $(COMPILER) $(OBJSW) {$< }

EXE_dependencies =  \
 aclass.obj \
 addhitpt.obj \
 chkmouse.obj \
 cleric.obj \
 cload.obj \
 config.obj \
 csave.obj \
 cslogo.obj \
 datetime.obj \
 display.obj \
 fontset.obj \
 gdialog.obj \
 gendesc.obj \
 gload.obj \
 gsave.obj \
 insdel.obj \
 layout.obj \
 light.obj \
 lload.obj \
 lsave.obj \
 main.obj \
 mload.obj \
 move.obj \
 msave.obj \
 newchar.obj \
 newmons.obj \
 psionic.obj \
 random.obj \
 screen.obj \
 setting.obj \
 sthrow.obj \
 subhitpt.obj \
 swap.obj \
 thief.obj \
 timetrck.obj \
 utility.obj \
 weather.obj \
 $(TCXLROOT)\Lib\tcxlbc$(MODEL)$(DEBLIB).lib \
 makefile \
 tcdm.hlp 
 
$(PROGNAME).Exe :  $(EXE_dependencies)
   $(LINKER) $(LNKSW) @&&|
c0$(MODEL).obj+
aclass.obj+
addhitpt.obj+
chkmouse.obj+
cleric.obj+
cload.obj+
config.obj+
csave.obj+
cslogo.obj+
datetime.obj+
display.obj+
fontset.obj+
gdialog.obj+
gendesc.obj+
gload.obj+
gsave.obj+
insdel.obj+
layout.obj+
light.obj+
lload.obj+
lsave.obj+
main.obj+
mload.obj+
move.obj+
msave.obj+
newchar.obj+
newmons.obj+
psionic.obj+
random.obj+
screen.obj+
setting.obj+
sthrow.obj+
subhitpt.obj+
swap.obj+
thief.obj+
timetrck.obj+
utility.obj+
weather.obj
$(PROGNAME)
		# no map file
noeh$(MODEL).lib+
$(TCXLROOT)\Lib\tcxlbc$(MODEL)$(DEBLIB).lib+
emu.lib+
math$(MODEL).lib+
c$(MODEL).lib
|

aclass.obj : aclass.c ..\include\tcdm.h

addhitpt.obj : addhitpt.c ..\include\tcdm.h

chkmouse.obj : chkmouse.c ..\include\tcdm.h

cleric.obj : cleric.c ..\include\tcdm.h

cload.obj : cload.c ..\include\tcdm.h

config.obj : config.c ..\include\tcdm.h

csave.obj : csave.c ..\include\tcdm.h

cslogo.obj : cslogo.c ..\include\tcdm.h

datetime.obj : datetime.c ..\include\tcdm.h

display.obj : display.c ..\include\tcdm.h

fontset.obj : fontset.c ..\include\tcdm.h

gdialog.obj : gdialog.c ..\include\tcdm.h

gendesc.obj : gendesc.c ..\include\tcdm.h

gload.obj : gload.c ..\include\tcdm.h

gsave.obj : gsave.c ..\include\tcdm.h

insdel.obj : insdel.c ..\include\tcdm.h

layout.obj : layout.c ..\include\tcdm.h

light.obj : light.c ..\include\tcdm.h

lload.obj : lload.c ..\include\tcdm.h

lsave.obj : lsave.c ..\include\tcdm.h

main.obj : main.c ..\include\tcdm.h

mload.obj : mload.c ..\include\tcdm.h

move.obj : move.c ..\include\tcdm.h

msave.obj : msave.c ..\include\tcdm.h

newchar.obj : newchar.c ..\include\tcdm.h

newmons.obj : newmons.c ..\include\tcdm.h

psionic.obj : psionic.c ..\include\tcdm.h

random.obj : random.c ..\include\tcdm.h

screen.obj : screen.c ..\include\tcdm.h

setting.obj : setting.c ..\include\tcdm.h

sthrow.obj : sthrow.c ..\include\tcdm.h

subhitpt.obj : subhitpt.c ..\include\tcdm.h

swap.obj : swap.c ..\include\tcdm.h

thief.obj : thief.c ..\include\tcdm.h

timetrck.obj : timetrck.c ..\include\tcdm.h

utility.obj : utility.c ..\include\tcdm.h

weather.obj : weather.c ..\include\tcdm.h

tcdm.hlp : ..\help\tcdm.v5
  -makhlp ..\help\tcdm.v5 tcdm.hlp

