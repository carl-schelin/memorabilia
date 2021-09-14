100 REM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
110 REM *                                                                     *
120 REM *   Program Name - Block Buster.                                      *
130 REM *                                                                     *
140 REM *   Date Created - November 8th, 1986   Created by - T. Carl Schelin  *
150 REM *                                                                     *
160 REM *   File Name - BlokBust.Bas                                          *
170 REM *                                                                     *
180 REM *   Brief Description - This program is a computerized version of     *
190 REM *   the game where you and a partner alternate at drawing lines to    *
200 REM *   make boxes. I tried to comment and layout the program in a        *
210 REM *   structured format.                                                *
220 REM *                                                                     *
230 REM *   Note about Corrections/Enhancements - If you wish to make changes *
240 REM *   to my program, no problem. I would (and everyone else) would like *
250 REM *   you to fill out the update description below so we know what has  *
260 REM *   been done. Please leave your name, the date of the update, and a  *
270 REM *   brief description of the change along with the line number if     *
280 REM *   possible. Please leave a copy of the new program at The Escape    *
290 REM *   Hatch (my brother's board) at 703-659-3033 or if you have an idea *
300 REM *   that you think should be done and don't feel like attempting to   *
310 REM *   change the program, leave a text file or note to me, Hanse        *
320 REM *   Shadowspawn on The Escape Hatch.                                  *
330 REM *                                                                     *
340 REM *   Last Update - December 1st, 1986    Updated by - T. Carl Schelin  *
350 REM *                                                                     *
360 REM *   Correction Description - Finalization of program and making the   *
370 REM *   dimensions of the playing area variable.                          *
380 REM *                                                                     *
390 REM *   Last Update - December 21st, 1986   Updated by - T. Carl Schelin  *
400 REM *                                                                     *
410 REM *   Correction Description - Changed PSet information so it can be    *
420 REM *   read into an array rather than printed and read from the screen.  *
430 REM *   Affected lines - 2050-2100 and 3080-3100.                         *
440 REM *                                                                     *
450 REM *   Last Update -                       Updated by -                  *
460 REM *                                                                     *
470 REM *   Correction Description -                                          *
480 REM *                                                                     *
490 REM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
500 REM
510 KEY OFF
800 GOSUB 61000:REM                     ;Check the monitor switch setting.
810 GOSUB 7000:REM                      ;Print Copywrite Screen.
820 GOSUB 1000:REM                      ;Find out about instructions.
830 GOSUB 2000:REM                      ;Initialize data and arrays.
840 GOSUB 3000:REM                      ;Set up the screen.
850 GOSUB 4000:REM                      ;Basic input screens.
860 IF SWITCH THEN GOSUB 6000:REM       ;Finalization routine.
870 REM
880 CLS
890 WIDTH 80
900 SCREEN 0,0,0
910 END
1000 REM                  * * * * * * * * * * * *
1010 REM            * * *   Ask for Instructions  * * *
1020 REM                  * * * * * * * * * * * *
1030 REM
1050 COLOR 12,0
1060 LOCATE 23,10:PRINT "Do you want instructions? ";
1070 COLOR 14,0
1080 INPUT "",CHECK$
1081 CLS
1090 UPPER$=CHECK$:GOSUB 50000:CHECK$=UPPER$
1100 IF MID$(CHECK$,1,1)="Y" THEN GOSUB 1300
1110 COLOR 11,0,0
1120 LOCATE 8,10:PRINT "What is the first players name? ";
1130 COLOR 14,0,0
1140 INPUT "",NAME.ONE$
1150 COLOR 11,0,0
1160 LOCATE 9,10:PRINT "What is the second players name? ";
1170 COLOR 14,0,0
1180 INPUT "",NAME.TWO$
1190 COLOR 11,0,0
1200 LOCATE 11,10:PRINT "What is the width of the game? (5 - 28) ";
1210 COLOR 14,0,0
1220 INPUT "",MAX.X
1230 IF MAX.X<5 OR MAX.X>28 THEN 1190 ELSE MAX.X=MAX.X+2
1240 COLOR 11,0,0
1250 LOCATE 12,10:PRINT "What is the height of the game? (5 - 12) ";
1260 COLOR 14,0,0
1270 INPUT "",MAX.Y
1280 IF MAX.Y<5 OR MAX.Y>12 THEN 1240 ELSE MAX.Y=MAX.Y+2
1290 RETURN
1300 REM                 * * * * * * * *
1310 REM           * * *   Instructions  * * *
1320 REM                 * * * * * * * *
1330 REM
1340 CLS
1350 COLOR 12,0,0
1360 PRINT
1370 PRINT "                                  Block Buster"
1380 COLOR 9,0,0
1390 PRINT "                                By: Carl Schelin"
1400 PRINT
1410 COLOR 11,0,0
1420 PRINT "     This is the classic game that most people played in school. You basically"
1430 PRINT "alternated with a partner in drawing lines on the paper, if you get a box, you"
1440 PRINT "put your initial in it and must draw another line somewhere else. Well I've"
1450 PRINT "computerized it. Instead of initials the computer will fill in a color. When"
1460 PRINT "all of the boxes are filled in, there will be an arrow pointing at the winner."
1470 PRINT "Press <Enter> and the program will end."
1480 PRINT
1490 PRINT "        ";CHR$(24);" ";CHR$(26);" ";CHR$(25);" ";CHR$(27);"  curser keys to move the curser (::) around the playing area."
1500 PRINT
1510 PRINT "        ";CHR$(17);"ÄÄÙ +   go to and draw the lines."
1520 PRINT
1530 PRINT "        Q ";CHR$(27);"      quit the game."
1540 PRINT
1560 PRINT
1570 PRINT "                                                Carl Schelin"
1580 PRINT "                                                LAN Systems Consulting"
1590 PRINT "                                                67 Chestnut Drive"
1600 PRINT "                                                Stafford, VA  22554"
1610 INPUT "",CHECK$
1620 CLS
1630 RETURN
2000 REM                      * * * * * * * * * * * * * * *
2010 REM                * * *   Initialize data and arrays  * * *
2020 REM                      * * * * * * * * * * * * * * *
2030 REM
2040 KEY OFF
2050 DEFINT A,B
2060 DIM A(4),B(4),COORDIN$(MAX.X,MAX.Y)
2070 DATA 6,3,68,68,0
2080 FOR J=0 TO 4
2090     READ B(J)
2100 NEXT
2110 SCREEN 0,0,0
2120 WIDTH 80
2130 FILL.COLOR=2
2140 X.COOR=20
2150 Y.COOR=20
2160 END.GAME=(MAX.X-2)*(MAX.Y-2)
2170 REM          * * *   Initialize Coordinate Array   * * *
2180 FOR J=1 TO MAX.X
2190     FOR K=1 TO MAX.Y
2200         COORDIN$(J,K)="00000"
2210     NEXT
2220 NEXT
2230 REM          * * *   Set up the borders of the Array   * * *
2240 FOR J=1 TO MAX.Y
2250     COORDIN$(1,J)="11111"
2260     COORDIN$(MAX.X,J)="11111"
2270 NEXT
2280 FOR J=1 TO MAX.X
2290     COORDIN$(J,1)="11111"
2300     COORDIN$(J,MAX.Y)="11111"
2310 NEXT
2320 RETURN
3000 REM                  * * * * * * * * * * *
3010 REM            * * *   Set up the screen   * * *
3020 REM                  * * * * * * * * * * *
3030 REM
3040 SCREEN 1,1
3050 WIDTH 40
3060 COLOR 0,0
3070 GET(1,1)-(3,3),A
3080 FOR J=0 TO 4
3090     A(J)=B(J)
3100 NEXT
3110 CLS
3120 FOR J=2 TO MAX.X
3130     FOR K=2 TO MAX.Y+1
3140         PSET(J*10,K*10),1
3150     NEXT K
3160 NEXT J
3170 LINE (0,0)-(MAX.X*10+20,MAX.Y*10+20),2,B
3180 LINE (10,10)-(MAX.X*10+10,MAX.Y*10+10),2,B
3190 PAINT(5,5),CHR$(&H66)+CHR$(&H99)+CHR$(&H66)+CHR$(&H99)+CHR$(&H66)+CHR$(&H99)+CHR$(&H66)+CHR$(&H99),2
3200 GOSUB 51000
3210 RETURN
4000 REM                    * * * * * * * * *
4010 REM              * * *   Input routine   * * *
4020 REM                    * * * * * * * * *
4030 REM
4040 PUT(X.COOR-1,Y.COOR-1),A,XOR
4050 CURSOR.INPUT$=INKEY$
4060 IF SCORE.ONE+SCORE.TWO=END.GAME THEN SWITCH=1:RETURN ELSE SWITCH=0
4070 IF CURSOR.INPUT$="" THEN 4050
4080 PUT(X.COOR-1,Y.COOR-1),A,XOR
4090 IF CURSOR.INPUT$=CHR$(0)+CHR$(72) OR CURSOR.INPUT$="8" THEN IF Y.COOR<30 THEN Y.COOR=MAX.Y*10 ELSE Y.COOR=Y.COOR-10
4100 IF CURSOR.INPUT$=CHR$(0)+CHR$(80) OR CURSOR.INPUT$="2" THEN IF Y.COOR>MAX.Y*10-10 THEN Y.COOR=20 ELSE Y.COOR=Y.COOR+10
4110 IF CURSOR.INPUT$=CHR$(0)+CHR$(75) OR CURSOR.INPUT$="4" THEN IF X.COOR<30 THEN X.COOR=MAX.X*10 ELSE X.COOR=X.COOR-10
4120 IF CURSOR.INPUT$=CHR$(0)+CHR$(77) OR CURSOR.INPUT$="6" THEN IF X.COOR>MAX.X*10-10 THEN X.COOR=20 ELSE X.COOR=X.COOR+10
4130 IF CURSOR.INPUT$=CHR$(13) OR CURSOR.INPUT$="+" THEN NEW.X=X.COOR:NEW.Y=Y.COOR:GOTO 5000
4140 UPPER$=CURSOR.INPUT$:GOSUB 50000:CURSOR.INPUT$=UPPER$
4150 IF CURSOR.INPUT$="Q" OR CURSOR.INPUT$=CHR$(27) THEN LOCATE 22,1:PRINT SPACE$(40):LOCATE 22,1:INPUT "Are you sure? ",CHECK$:UPPER$=CHECK$:GOSUB 50000:CHECK$=UPPER$:IF CHECK$="Y" THEN RETURN ELSE GOSUB 51000
4160 GOTO 4000
5000 REM                    * * * * * * * * * * *
5010 REM              * * *   Sub-Input routine   * * *
5020 REM                    * * * * * * * * * * *
5030 REM
5040 PSET(NEW.X,NEW.Y),1
5050 LINE(X.COOR,Y.COOR)-(NEW.X,NEW.Y),1
5060 NEW.INPUT$=INKEY$
5070 PSET(NEW.X,NEW.Y),1
5080 PRESET(NEW.X,NEW.Y)
5090 IF NEW.INPUT$="" THEN 5060
5100 LINE(X.COOR,Y.COOR)-(NEW.X,NEW.Y),0
5110 PSET(NEW.X,NEW.Y),1
5120 IF NEW.INPUT$=CHR$(0)+CHR$(72) OR NEW.INPUT$="8" THEN GOSUB 5180
5130 IF NEW.INPUT$=CHR$(0)+CHR$(80) OR NEW.INPUT$="2" THEN GOSUB 5270
5140 IF NEW.INPUT$=CHR$(0)+CHR$(75) OR NEW.INPUT$="4" THEN GOSUB 5360
5150 IF NEW.INPUT$=CHR$(0)+CHR$(77) OR NEW.INPUT$="6" THEN GOSUB 5450
5160 IF NEW.INPUT$=CHR$(13) OR NEW.INPUT$="+" THEN GOTO 5540
5170 GOTO 5000
5180 REM                       * * * * * * * *
5190 REM                 * * *   Draw line up  * * *
5200 REM                       * * * * * * * *
5210 REM
5220 NEW.X=X.COOR
5230 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),4,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),2,1)="1" THEN NEW.Y=Y.COOR:RETURN
5240 IF NEW.Y=Y.COOR-10 THEN NEW.Y=Y.COOR+10 ELSE NEW.Y=NEW.Y-10:RETURN
5250 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10),4,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),2,1)="1" THEN NEW.Y=Y.COOR
5260 RETURN
5270 REM                      * * * * * * * * *
5280 REM                * * *   Draw line down  * * *
5290 REM                      * * * * * * * * *
5300 REM
5310 NEW.X=X.COOR
5320 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10),4,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),2,1)="1" THEN NEW.Y=Y.COOR:RETURN
5330 IF NEW.Y=Y.COOR+10 THEN NEW.Y=Y.COOR-10 ELSE NEW.Y=NEW.Y+10:RETURN
5340 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),4,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),2,1)="1" THEN NEW.Y=Y.COOR
5350 RETURN
5360 REM                     * * * * * * * * * * *
5370 REM               * * *   Draw line to left   * * *
5380 REM                     * * * * * * * * * * *
5390 REM
5400 NEW.Y=Y.COOR
5410 IF MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),1,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),3,1)="1" THEN NEW.X=X.COOR:RETURN
5420 IF NEW.X=X.COOR-10 THEN NEW.X=X.COOR+10 ELSE NEW.X=NEW.X-10:RETURN
5430 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10),1,1)="1" AND MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),3,1)="1" THEN NEW.X=X.COOR
5440 RETURN
5450 REM                     * * * * * * * * * * *
5460 REM               * * *   Draw line to right  * * *
5470 REM                     * * * * * * * * * * *
5480 REM
5490 NEW.Y=Y.COOR
5500 IF MID$(COORDIN$(X.COOR/10,Y.COOR/10),1,1)="1" AND MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),3,1)="1" THEN NEW.X=X.COOR:RETURN
5510 IF NEW.X=X.COOR+10 THEN NEW.X=X.COOR-10 ELSE NEW.X=NEW.X+10:RETURN
5520 IF MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),1,1)="1" AND MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),3,1)="1" THEN NEW.X=X.COOR
5530 RETURN
5540 REM                    * * * * * * * * * * * * *
5550 REM              * * *   Enter has been pressed  * * *
5560 REM                    * * * * * * * * * * * * *
5570 REM
5580 IF NEW.X=X.COOR AND NEW.Y=Y.COOR THEN 4000
5590 IF NEW.X=X.COOR+10 THEN GOSUB 5780
5600 IF NEW.X=X.COOR-10 THEN GOSUB 5790
5610 IF NEW.Y=Y.COOR+10 THEN GOSUB 5800
5620 IF NEW.Y=Y.COOR-10 THEN GOSUB 5810
5630 GOSUB 5670
5640 IF SWITCH THEN IF FILL.COLOR=2 THEN FILL.COLOR=3 ELSE FILL.COLOR=2
5650 GOSUB 51000
5660 GOTO 4000
5670 LINE(X.COOR,Y.COOR)-(NEW.X,NEW.Y),1
5680 SWITCH=1
5690 IF (X.COOR<>20 AND Y.COOR<>20) AND COORDIN$(X.COOR/10-1,Y.COOR/10-1)="11110" THEN PAINT(X.COOR-5,Y.COOR-5),FILL.COLOR,1:COORDIN$(X.COOR/10-1,Y.COOR/10-1)="11111":GOSUB 5820:SWITCH=0
5700 IF (X.COOR<>MAX.X*10 AND Y.COOR<>20) AND COORDIN$(X.COOR/10,Y.COOR/10-1)="11110" THEN PAINT(X.COOR+5,Y.COOR-5),FILL.COLOR,1:COORDIN$(X.COOR/10,Y.COOR/10-1)="11111":GOSUB 5820:SWITCH=0
5710 IF (X.COOR<>20 AND Y.COOR<>MAX.Y*10) AND COORDIN$(X.COOR/10-1,Y.COOR/10)="11110" THEN PAINT(X.COOR-5,Y.COOR+5),FILL.COLOR,1:COORDIN$(X.COOR/10-1,Y.COOR/10)="11111":GOSUB 5820:SWITCH=0
5720 IF (X.COOR<>MAX.X*10 AND Y.COOR<>MAX.Y*10) AND COORDIN$(X.COOR/10,Y.COOR/10)="11110" THEN PAINT(X.COOR+5,Y.COOR+5),FILL.COLOR,1:COORDIN$(X.COOR/10,Y.COOR/10)="11111":GOSUB 5820:SWITCH=0
5730 RETURN
5740 REM
5750 REM
5760 REM
5770 REM
5780 MID$(COORDIN$(X.COOR/10,Y.COOR/10),1,1)="1":MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),3,1)="1":RETURN
5790 MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),1,1)="1":MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),3,1)="1":RETURN
5800 MID$(COORDIN$(X.COOR/10,Y.COOR/10),4,1)="1":MID$(COORDIN$(X.COOR/10-1,Y.COOR/10),2,1)="1":RETURN
5810 MID$(COORDIN$(X.COOR/10,Y.COOR/10-1),4,1)="1":MID$(COORDIN$(X.COOR/10-1,Y.COOR/10-1),2,1)="1":RETURN
5820 REM
5830 REM
5840 REM
5850 REM
5860 IF FILL.COLOR=2 THEN SCORE.ONE=SCORE.ONE+1:RETURN
5870 IF FILL.COLOR=3 THEN SCORE.TWO=SCORE.TWO+1:RETURN
5880 REM
5890 REM
5900 REM
5910 REM
6000 REM                  * * * * * * * * * * * *
6010 REM            * * *   Finalization Routine  * * *
6020 REM                  * * * * * * * * * * * *
6030 REM
6040 IF SCORE.ONE>SCORE.TWO THEN LOCATE 22,20:PRINT CHR$(27)
6050 IF SCORE.ONE<SCORE.TWO THEN LOCATE 22,20:PRINT CHR$(26)
6060 IF SCORE.ONE=SCORE.TWO THEN LOCATE 22,20:PRINT CHR$(29)
6070 LOCATE 22,1
6075 IF INKEY$="" THEN 6075
6080 RETURN
7000 REM                 * * * * * * * * * *
7010 REM           * * *  Copywrite Notice   * * *
7020 REM                 * * * * * * * * * *
7030 REM
7031 CLS
7040 COLOR 11,0,0
7050 LOCATE 3,6,0:PRINT CHR$(219)+STRING$(26,223)+CHR$(219)
7060 FOR J=1 TO 7
7070     LOCATE 3+J,6:PRINT CHR$(219);
7080     LOCATE 3+J,33:PRINT CHR$(219);
7090 NEXT
7100 LOCATE 11,6:PRINT CHR$(219)+STRING$(26,220)+CHR$(219)
7110 COLOR 10,0
7120 LOCATE 4,8:PRINT CHR$(214)+STRING$(22,196)+CHR$(183)
7130 FOR J=1 TO 5
7140     LOCATE 4+J,8:PRINT CHR$(186);
7150     LOCATE 4+J,31:PRINT CHR$(186);
7160 NEXT
7170 LOCATE 10,8:PRINT CHR$(211)+STRING$(22,196)+CHR$(189)
7180 COLOR 12,0
7190 LOCATE 5,14:PRINT "Block Buster"
7200 COLOR 11,0
7210 LOCATE 6,19:PRINT "By"
7220 COLOR 13,0
7230 LOCATE 7,14:PRINT "Carl Schelin"
7240 COLOR 14,0
7250 LOCATE 9,14:PRINT "Version 1.0"
7260 COLOR 11,0
7270 LOCATE 3,43:PRINT "This program is Copywrited (C) 1987"
7280 LOCATE 4,38:PRINT "as the property of Carl Schelin.  It may"
7290 LOCATE 5,38:PRINT "and should be allowed public consumption"
7300 LOCATE 6,38:PRINT "through the medium of BBS's and the free"
7310 LOCATE 7,38:PRINT "transfer by hand to anyone who wants it."
7320 LOCATE 8,43:PRINT "Updates can be found on most boards"
7330 LOCATE 9,38:PRINT "in the mid-Virginia area. If you wish to"
7340 LOCATE 10,38:PRINT "have updates mailed to your home/office,"
7350 LOCATE 11,38:PRINT "please send the paltry sum of 15 dollars"
7360 LOCATE 12,38:PRINT "to:"
7370 LOCATE 13,49:PRINT "Carl Schelin"
7380 LOCATE 14,49:PRINT "67 Chestnut Drive"
7390 LOCATE 15,49:PRINT "Stafford, VA  22554"
7400 LOCATE 17,43:PRINT "Don't forget including your address"
7410 LOCATE 18,38:PRINT "with your check/money-order. It's really"
7420 LOCATE 19,38:PRINT "not wise to send cash in the mail due to"
7430 LOCATE 20,38:PRINT "someone ripping it off and then you will"
7440 LOCATE 21,38:PRINT "be calling me to complain about it."
7450 LOCATE 13,6:PRINT "Other Programs by Carl:"
7460 LOCATE 15,6:PRINT "FileSort - Disk Cataloger"
7470 LOCATE 16,6:PRINT "StarTrek - 3D game of kill"
7480 LOCATE 17,17:PRINT "the Klingons"
7490 LOCATE 18,6:PRINT "DM       - Dungeons & Dragons"
7500 LOCATE 19,17:PRINT "Utility to monitor"
7510 LOCATE 20,17:PRINT "character stats"
7520 LOCATE 21,6:PRINT "ListFile - List files on disk"
7530 RETURN
50000 REM                   * * * * * * * * * * * * * * * *
50010 REM             * * *   Routine to capitalize input   * * *
50020 REM                   * * * * * * * * * * * * * * * *
50030 REM
50040 FOR PROC.LOOP=1 TO LEN(UPPER$)
50050     IF ASC(MID$(UPPER$,PROC.LOOP,1))>96 AND ASC(MID$(UPPER$,PROC.LOOP,1))<123 THEN MID$(UPPER$,PROC.LOOP,1)=CHR$(ASC(MID$(UPPER$,PROC.LOOP,1))-32)
50060 NEXT PROC.LOOP
50070 RETURN
51000 REM                     * * * * * * * * * * * * * * * *
51010 REM               * * *   Change the Character Colors   * * *
51020 REM                     * * * * * * * * * * * * * * * *
51030 REM
51040 LOCATE 22,1:PRINT SPACE$(40)
51050 GOSUB 52000
51060 LOCATE 22,4:PRINT NAME.ONE$;":"
51070 LOCATE 22,LEN(NAME.ONE$)+5:PRINT SCORE.ONE
51080 GOSUB 52500
51090 LOCATE 22,24:PRINT NAME.TWO$;":"
51100 LOCATE 22,LEN(NAME.TWO$)+25:PRINT SCORE.TWO
51110 RETURN
52000 REM             * * * * * * * * * * * * * * * * * * * * * *
52010 REM       * * *   Set up the colored squares for player one  * * *
52020 REM             * * * * * * * * * * * * * * * * * * * * * *
52030 REM
52040 IF FILL.COLOR=2 THEN CIRCLE(5,171),4,1 ELSE LINE(1,168)-(9,175),1,B
52050 PAINT(2,171),2,1
52060 RETURN
52500 REM             * * * * * * * * * * * * * * * * * * * * * *
52510 REM       * * *   Set up the colored squares for player two  * * *
52520 REM             * * * * * * * * * * * * * * * * * * * * * *
52530 REM
52540 IF FILL.COLOR=3 THEN CIRCLE(165,171),4,1 ELSE LINE(161,168)-(169,175),1,B
52550 PAINT(162,171),3,1
52560 RETURN
61000 REM                * * * * * * * * * * * * * * * * * * *
61010 REM          * * *   Check whether color monitor or not  * * *
61020 REM                * * * * * * * * * * * * * * * * * * *
61030 REM
61040 DEF SEG=0: MONBITS=(PEEK(&H410) AND &H30)
61050 IF MONBITS=&H30 THEN GOSUB 61100:RETURN:REM       two monitors
61060 IF MONBITS=&H20 THEN GOSUB 61200:RETURN:REM       color monitor
61070 IF MONBITS=&H10 THEN GOSUB 61300:RETURN:REM       composite monitor
61080 IF MONBITS=&H0 THEN GOSUB 61500:RETURN:REM        no monitor attached
61100 REM
61110 REM                * * * * * * * * * * * * * * * *
61120 REM          * * *   You have 2 monitors attached  * * *
61130 REM                * * * * * * * * * * * * * * * *
61140 REM
61150 DEF SEG=&HB800:POKE 0,0:TT=PEEK(0)
61160 IF TT<>0 THEN GOSUB 61600:RETURN
61200 REM
61210 REM               * * * * * * * * * * * * *
61220 REM         * * *   Color Monitor Attached  * * *
61230 REM               * * * * * * * * * * * * *
61240 REM
61250 RETURN
61300 REM
61310 REM                * * * * * * * * * * * * * * * * * *
61320 REM          * * *   Composite monitor or TV attached  * * *
61330 REM                * * * * * * * * * * * * * * * * * *
61340 REM
61350 WIDTH 40
61360 COLOR 15,0,0
61370 PRINT "WARNING - You have a low resolution"
61380 PRINT "monitor.  Block Buster is intended"
61390 PRINT "for a high resolution monitor."
61400 PRINT
61410 PRINT "You may proceed, but the displays may"
61420 PRINT "appear a bit smeared and the text may"
61430 PRINT "be somewhat hard to read."
61440 PRINT
61450 PRINT
61460 PRINT "Press any key to continue."
61470 A$=INKEY$:IF A$="" THEN 61470
61480 WIDTH 80
61490 RETURN
61500 REM                     * * * * * * * * * * * *
61510 REM               * * *   No monitor attached   * * *
61520 REM                     * * * * * * * * * * * *
61530 REM
61540 PRINT "Mother board switch setting (switch 1) indicates no monitor."
61550 PRINT "Program aborted."
61560 SOUND 50,10
61570 STOP
61600 REM                 * * * * * * * * * * * * * * * *
61610 REM           * * *   Must be a Monochrome Monitor  * * *
61620 REM                 * * * * * * * * * * * * * * * *
61630 REM
61640 CLS
61660 PRINT
61670 PRINT "This game is intended for Color/Composite monitors only and will not run on a"
61680 PRINT "Monochrome monitor."
61690 PRINT
61700 PRINT
61710 PRINT
61720 PRINT
61740 PRINT "                                                 Carl Schelin"
61750 PRINT "                                                 LAN Systems Consulting"
61760 PRINT "                                                 67 Chestnut Drive"
61770 PRINT "                                                 Stafford, VA  22554"
61781 PRINT
61782 PRINT
61785 PRINT
61786 PRINT
61790 END
