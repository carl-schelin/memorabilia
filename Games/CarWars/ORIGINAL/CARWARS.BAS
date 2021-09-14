1020 Dim H$(25,80)
1030 Dim I$(65,80)
1040 Dim V(65)
1050 Dim W(65)
1060 Dim X(26)
1070 Dim Y(26)
1080 Dim R1(65)
1090 Dim R2(25)
1100 L$=""
1110 CLS
1120 Print  "CAR WARS"
1130 Print  "PROGRAM BY CARL SCHELIN"
1140 Print  
1150 Print  "WHAT MODE DO YOU WANT TO BE IN?"
1160 Print  
1170 Print  "      (A) CARS"
1180 Print  "      (B) CYCLES"
1190 Print  "      (C) SIDECARS"
1200 Print  "      (D) BUSES OR RV'S"
1210 Print  "      (E) TRACTORS"
1220 Print  "      (F) TRAILERS"
1230 Print  "      (G) HELICOPTERS"
1240 Print  "      (H) EQUIPMENT"
1250 Print  "      (I) WEAPONS"
1260 Print  "      (J) WHEELGUARDS"
1270 Print  "      (K) CHARACTER SKILLS"
1280 Print  "      (L) FINISHED"
1290 B$=inchr$(-1)
1300 If B$="" then Goto 1290
1310 If asc(B$)-64>=1 and asc(B$)-64<=12 then On  asc(B$)-64 gosub 1340,3030,4300,5030,6000,6560,7450,8210,10870,11920,13400,13630
1320 If B$="L" then Gosub 12190
1330 Goto 1100
1340 N$=B$
1350 J=0
1360 CLS
1370 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
1380 Print  "YOU ARE IN THE CAR MODE. (PRESS 'F' OR 'G' FIRST)"
1390 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION."
1400 Print  "WHICH SECTION DO YOU WANT?"
1410 L$=L$+A$
1420 Print  L$
1430 Print  "    (A) CAR TYPE"
1440 Print  "    (B) CHASSIS STRENGTH"
1450 Print  "    (C) POWER PLANT"
1460 Print  "    (D) SUSPENSION"
1470 Print  "    (E) TIRES"
1480 Print  "    (F) ADD INFORMATION"
1490 Print  "    (G) SUBTRACT INFORMATION"
1500 Print  "    (H) FINISHED"
1510 A$=inchr$(-1)
1520 If A$="" then Goto 1510
1530 P=P+1
1540 If P=5 then Print  "PRESS 'F' OR 'G' AND THEN PRESS <ENTER>"
1550 If A$="H" then Return
1560 If A$="F" then [J=1;  CLS;  Goto 1390]
1570 If A$="G" then [J=2;  CLS;  Goto 1390]
1580 If J=0 then Goto 1340
1590 If A$="A" then [Gosub 1650;  P=0]
1600 If A$="B" then [Gosub 1980;  P=0]
1610 If A$="C" then [Gosub 2250;  P=0]
1620 If A$="D" then [Gosub 2510;  P=0]
1630 If A$="E" then [Gosub 2730;  P=0]
1640 Goto 1340
1650 CLS
1660 Print  "WHAT TYPE OF CAR DO YOU WANT?"
1670 Print  "    TYPE          COST  WT  LOAD SP/CG ARMOR FIRE PROOF KEVLAR"
1680 Print  "(A) SUBCOMPACT     300 1000 2300  7    11/5    22/5     66/2.5"
1690 Print  "(B) COMPACT        400 1300 3700 10    13/6    26/6     78/3"
1700 Print  "(C) MID-SIZED      600 1600 4800 13    16/8    32/8     96/4"
1710 Print  "(D) LUXURY         800 1800 5500 19    20/10   40/10   120/5"
1720 Print  "(E) STATION WAGON  800 1800 5500 14/ 7 20/10   40/10   120/5"
1730 Print  "(F) PICKUP         900 2100 6500 13/11 22/11   44/11   132/5.5"
1740 Print  "(G) VAN           1000 2000 6000 24/ 6 30/14   60/14   180/7"
1750 C$=inchr$(-1)
1760 If C$="" then Goto 1750
1770 If J=1 then Gosub 1800
1780 If J=2 then Gosub 1920
1790 Return
1800 If C$="A" then [A=300;  B=1000;  C=2300;  D=7;  E=11;  F=5;  E1=22; C$="SUBCOMPACT"]
1810 If C$="B" then [A=400;  B=1300;  C=3700;  D=10;  E=13;  F=6;  E1=26; C$="COMPACT"]
1820 If C$="C" then [A=600;  B=1600;  C=4800;  D=13;  E=16;  F=8;  E1=32; C$="MID-SIZED"]
1830 If C$="D" then [A=800;  B=1800;  C=5500;  D=19;  E=20;  F=10;  E1=40; C$="LUXURY"]
1840 If C$="E" then [A=800;  B=1800;  C=5500;  D=14;  D1=7;  E=20;  F=10; E1=40;  C$="STATION WAGON"]
1850 If C$="F" then [A=900;  B=2100;  C=2100;  D=13;  D1=11;  E=22;  F=11; E1=44;  C$="PICKUP"]
1860 If C$="G" then [A=1000;  B=2000;  C=6000;  D=24;  D1=6;  E=30;  F=14; E1=60;  C$="VAN"]
1870 A1=A
1880 C1=C
1890 B=B+150
1900 D=D-2
1910 Return
1920 Print  "ARE YOU SURE? (Y/N) IF YOU GO THIS WAY, YOU'LL HAVE TO START OVER."
1930 Z$=inchr$(-1)
1940 If Z$="" then Goto 1930
1950 If Z$="Y" then Goto 1000
1960 If Z$="N" then Return
1970 Goto 1920
1980 N=0
1990 CLS
2000 Print  "WHAT CHASSIS STRENGTH DO YOU WANT?"
2010 If J=2 then Z$="SAVE" else Z$="COST" 
2020 Print "TYPE                ",%"7M",Z$,"WT CARRIED"
2030 Print "(A) LIGHT          ",%"4I",.2*A1," ",%"4I",C-.1*C
2040 Print  $$$% "\                 \  ####         ####","(B) STANDARD",0,C
2050 Print  $$$% "\                 \  ####         ####","(C) HEAVY",.5*A1,.1* C+C
2060 Print  $$$% "\                 \  ####         ####","(D) EXTRA HEAVY",A1, .2*C+C
2070 D$=inchr$(-1)
2080 If D$="" then Goto 2070
2090 If P=2 then Goto 2110 else If D$="D" and C$="VAN" then [Print "YOU MUST HAVE A SIX-WHEELED CHASSIS AT $100 MORE";  A=A+100;  N=1]
2100 If C$="VAN" and D$<>"D" or C$="PICKUP" and D$<>"D" then [Print "YOU MAY HAVE A SIX-WHEELED CHASSIS AT $100 MORE (Y/N)?";  Input  Z$; If Z$="Y" then [A=A+100;  N=1]]
2110 If J=1 then Gosub 2140
2120 If J=2 then Gosub 2190
2130 Return
2140 If D$="A" then [A=A+.2*A1;  C=C-.1*C1;  D$="LIGHT"]
2150 If D$="B" then D$="STANDARD"
2160 If D$="C" then [A=A+.5*A1;  C=C+.1*C1;  D$="HEAVY"]
2170 If D$="D" then [A=A+A1;  C=C+.2*C1;  D$="EXTRA HEAVY"]
2180 Return
2190 If D$="A" then [A=A-.2*A1;  C=C+.1*C1]
2200 If D$="C" then [A=A-.5*A1;  C=C-.1*C1]
2210 If D$="D" then [A=A-A1;  C=C-.2*C1]
2220 D$=""
2230 If N=1 then A=A-100
2240 Return
2250 CLS
2260 Print  "WHAT KIND OF POWER PLANT DO YOU WANT?"
2270 Print  "    TYPE      PRICE   WT   SP  DP   PF    MAX MPH"
2280 Print  "(A) SMALL       500   500   3   5   800      80"
2290 Print  "(B) MEDIUM     1000   700   4   8  1400      90"
2300 Print  "(C) LARGE      2000   900   5  10  2000     100"
2310 Print  "(D) SUPER      3000  1100   6  12  2600     100"
2320 E$=inchr$(-1)
2330 If E$="" then Goto 2320
2340 If J=1 then Gosub 2370
2350 If J=2 then Gosub 2420
2360 Return
2370 If E$="A" then [A=A+500;  B=B+500;  D=D-3;  G=5;  H=800;  I=80; E$="SMALL"]
2380 If E$="B" then [A=A+1000;  B=B+700;  D=D-4;  G=8;  H=1400;  I=90; E$="MEDIUM"]
2390 If E$="C" then [A=A+2000;  B=B+900;  D=D-5;  G=10;  H=2000;  I=100; E$="LARGE"]
2400 If E$="D" then [A=A+3000;  B=B+1100;  D=D-6;  G=12;  H=2600;  I=100; E$="SUPER"]
2410 Return
2420 If E$="A" then [A=A-500;  B=B-500;  D=D+3]
2430 If E$="B" then [A=A-1000;  B=B-700;  D=D+4]
2440 If E$="C" then [A=A-2000;  B=B-900;  D=D+5]
2450 If E$="D" then [A=A-3000;  B=B-1100;  D=D+6]
2460 G=0
2470 H=0
2480 I=0
2490 E$=""
2500 Return
2510 CLS
2520 Print  "WHAT TYPE OF SUSPENSION DO YOU WANT?"
2530 If C$="VAN" then Z=1 else Z=0 
2540 If J=2 then Z$="SAVE" else Z$="COST" 
2550 Print  "    TYPE           ",Z$,"       HC"
2560 Print  "(A) LIGHT            0       ",1-Z
2570 Print  "(B) IMPROVED       ",A1,"       ",2-Z
2580 Print  "(C) HEAVY          ",A1+.5*A1,"       ",3-Z
2590 F$=inchr$(-1)
2600 If F$="" then Goto 2590
2610 If J=1 then Gosub 2640
2620 If J=2 then Gosub 2680
2630 Return
2640 If F$="A" then [K=1-Z;  F$="LIGHT"]
2650 If F$="B" then [A=A+A1;  K=2-Z;  F$="IMPROVED"]
2660 If F$="C" then [A=A+1.5*A1;  K=3-Z;  F$="HEAVY"]
2670 Return
2680 If F$="B" then A=A-A1
2690 If F$="C" then A=A-1.5*A1
2700 K=0
2710 F$=""
2720 Return
2730 CLS
2740 Print  "WHAT TYPE OF TIRES DO YOU WANT?"
2750 Print  "    TYPE                    COST     WT      DP"
2760 Print  "(A) STANDARD                 200    120       4"
2770 Print  "(B) HEAVY DUTY               400    160       6"
2780 Print  "(C) PUNCTURE RESISTANT       800    200       9"
2790 Print  "(D) RADIALS (+1 HC)         2000    240       8"
2800 Print  "(E) SOLID                   2000    300      12"
2810 G$=inchr$(-1)
2820 If G$="" then Goto 2810
2830 If J=1 then Gosub 2860
2840 If J=2 then Gosub 2940
2850 Return
2860 L=4
2870 If N=1 then L=6
2880 If G$="A" then [A=A+200;  B=B+120;  M=4;  G$="STANDARD"; If N=1 then [A=A+100;  B=B+60]]
2890 If G$="B" then [A=A+400;  B=B+160;  M=6;  G$="HEAVY DUTY"; If N=1 then [A=A+200;  B=B+80]]
2900 If G$="C" then [A=A+800;  B=B+200;  M=9;  G$="PUNCTURE RESISTANT"; If N=1 then [A=A+400;  B=B+100]]
2910 If G$="D" then [A=A+2000;  B=B+240;  M=8;  K=K+1;  G$="RADIAL"; If N=1 then [A=A+1000;  B=B+120]]
2920 If G$="E" then [A=A+2000;  B=B+300;  M=12;  G$="SOLID"; If N=1 then [A=A+1000;  B=B+150]]
2930 Return
2940 If G$="A" then [A=A-200;  B=B-120;  If N=1 then [A=A-100;  B=B-60]]
2950 If G$="B" then [A=A-400;  B=B-160;  If N=1 then [A=A-200;  B=B-80]]
2960 If G$="C" then [A=A-800;  B=B-200;  If N=1 then [A=A-200;  B=B-100]]
2970 If G$="D" then [A=A-2000;  B=B-240;  K=K-1;  If N=1 then [A=A-1000; B=B-150]]
2980 If G$="E" then [A=A-2000;  B=B-300;  If N=1 then [A=A-1000;  B=B-150]]
2990 M=0
3000 G$=""
3010 L=0
3020 Return
3030 N$=B$
3040 J=0
3050 CLS
3060 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
3070 Print  "YOU ARE IN MOTORCYCLE MODE (PRESS 'E' OR 'F' FIRST)"
3080 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION"
3090 Print  "WHICH SECTION DO YOU WANT?"
3100 L$=L$+A$
3110 Print  L$
3120 Print  "    (A) CYCLE TYPE"
3130 Print  "    (B) POWER PLANT"
3140 Print  "    (C) SUSPENSION"
3150 Print  "    (D) TIRES"
3160 Print  "    (E) ADD INFORMATION"
3170 Print  "    (F) SUBTRACT INFORMATION"
3180 Print  "    (G) FINISHED"
3190 A$=inchr$(-1)
3200 If A$="" then Goto 3190
3210 If A$="G" then Return
3220 If A$="E" then [J=1;  CLS;  Goto 3080]
3230 If A$="F" then [J=2;  CLS;  Goto 3080]
3240 If J=0 then Goto 3030
3250 If A$="A" then Gosub 3300
3260 If A$="B" then Gosub 3540
3270 If A$="C" then Gosub 3800
3280 If A$="D" then Gosub 4010
3290 Goto 3030
3300 CLS
3310 Print  "WHAT TYPE OF CYCLE DO YOU WANT?"
3320 Print  "    TYPE           COST   WT  LOAD  SP  ARMOR  FIRE PROOF"
3330 Print  "(A) LIGHT CYCLE     200  250   800   4   10/4     20/4"
3340 Print  "(B) MEDIUM CYCLE    300  300  1100   5   11/5     22/5"
3350 Print  "(C) HEAVY CYCLE     400  350  1300   7   12/6     24/6"
3360 C$=inchr$(-1)
3370 If C$="" then Goto 3360
3380 If J=1 then Gosub 3410
3390 If J=2 then Gosub 3480
3400 Return
3410 If C$="A" then [A=200;  B=250;  C=800;  D=4;  E=10;  F=4;  E1=20; C$="LIGHT CYCLE"]
3420 If C$="B" then [A=300;  B=300;  C=1100;  D=5;  E=11;  F=5;  E1=22; C$="MEDIUM CYCLE"]
3430 If C$="C" then [A=400;  B=350;  C=1300;  D=7;  E=12;  F=6;  E1=24; C$="HEAVY CYCLE"]
3440 A1=A
3450 B=B+150
3460 D=D-2
3470 Return
3480 Print  "ARE YOU SURE (Y/N)? IF YOU GO THIS WAY YOU'LL HAVE TO START OVER."
3490 Z$=inchr$(-1)
3500 If Z$="" then Goto 3490
3510 If Z$="Y" then Goto 1000
3520 If Z$="N" then Return
3530 Goto 3480
3540 CLS
3550 Print  "WHAT TYPE OF POWER PLANT DO YOU WANT?"
3560 Print  "    TYPE           COST   WT  SP  DP    PF  MAX MPH"
3570 Print  "(A) SMALL           500  100   1   2   400     90"
3580 Print  "(B) MEDUIM         1000  150   1   3   600    100"
3590 Print  "(C) LARGE          1500  175   2   4   800    100"
3600 Print  "(D) SUPER          2000  200   2   5  1000    100"
3610 E$=inchr$(-1)
3620 If E$="" then Goto 3610
3630 If J=1 then Gosub 3660
3640 If J=2 then Gosub 3710
3650 Return
3660 If E$="A" then [A=A+500;  B=B+100;  D=D-1;  G=2;  H=400;  I=90; E$="SMALL"]
3670 If E$="B" then [A=A+1000;  B=B+150;  D=D-1;  G=3;  H=600;  I=100; E$="MEDIUM"]
3680 If E$="C" then [A=A+1500;  B=B+175;  D=D-2;  G=4;  H=800;  I=100; E$="LARGE"]
3690 If E$="D" then [A=A+2000;  B=B+200;  D=D-2;  G=5;  H=1000;  I=100; E$="SUPER"]
3700 Return
3710 If E$="A" then [A=A-500;  B=B-100;  D=D+1]
3720 If E$="B" then [A=A-1000;  B=B-150;  D=D+1]
3730 If E$="C" then [A=A-1500;  B=B-175;  D=D+2]
3740 If E$="D" then [A=A-2000;  B=B-200;  D=D+2]
3750 G=0
3760 H=0
3770 I=0
3780 E$=""
3790 Return
3800 CLS
3810 Print  "WHAT TYPE OF SUSPENSION DO YOU WANT?"
3820 If J=2 then Z$="SAVE" else Z$="COST" 
3830 Print  "    TYPE              ",Z$,"       HC"
3840 Print  "(A) LIGHT               0        0"
3850 Print  "(B) IMPROVED          ",A1,"        1"
3860 Print  "(C) HEAVY             ",A1*2,"        2"
3870 F$=inchr$(-1)
3880 If F$="" then Goto 3870
3890 If J=1 then Gosub 3920
3900 If J=2 then Gosub 3960
3910 Return
3920 If F$="A" then [K=0;  F$="LIGHT"]
3930 If F$="B" then [A=A+A1;  K=1;  F$="IMPROVED"]
3940 If F$="C" then [A=A+2*A1;  K=2;  F$="HEAVY"]
3950 Return
3960 If F$="B" then A=A-A1
3970 If F$="C" then A=A-2*A1
3980 K=0
3990 F$=""
4000 Return
4010 CLS
4020 Print  "WHAT TYPE OF TIRES DO YOU WANT"
4030 Print  "    TYPE                COST  WT  DP"
4040 Print  "(A) STANDARD             100  30   4"
4050 Print  "(B) HEAVY DUTY           200  40   6"
4060 Print  "(C) PUNCTURE RESISTANT   400  50   9"
4070 Print  "(D) RADIALS (+1 HC)     1000  60   8"
4080 Print  "(E) SOLID               1000  75  12"
4090 G$=inchr$(-1)
4100 If G$="" then Goto 4090
4110 If J=1 then Gosub 4140
4120 If J=2 then Gosub 4200
4130 Return
4140 L=2
4150 If G$="A" then [A=A+100;  B=B+30;  M=4;  G$="STANDARD"]
4160 If G$="B" then [A=A+200;  B=B+40;  M=6;  G$="HEAVY DUTY"]
4170 If G$="C" then [A=A+400;  B=B+50;  M=9;  G$="PUNCTURE RESISTANT"]
4180 If G$="D" then [A=A+1000;  B=B+60;  M=8;  K=K+1;  G$="RADIAL"]
4190 If G$="E" then [A=A+1000;  B=B+75;  M=12;  G$="SOLID"]
4200 Return
4210 If G$="A" then [A=A-100;  B=B-30]
4220 If G$="B" then [A=A-200;  B=B-40]
4230 If G$="C" then [A=A-400;  B=B-50]
4240 If G$="D" then [A=A-1000;  B=B-60;  K=K-1]
4250 If G$="E" then [A=A-1000;  B=B-75]
4260 L=0
4270 M=0
4280 G$=""
4290 Return
4300 N$=B$
4310 J=0
4320 CLS
4330 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
4340 Print  "YOU ARE IN THE SIDECAR MODE (PRESS 'D' OR 'E' FIRST)"
4350 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION"
4360 Print  "WHAT SECTION DO YOU WANT?"
4370 L$=L$+A$
4380 Print  L$
4390 Print  "    (A) SIDECAR TYPE"
4400 Print  "    (B) SUSPENSION"
4410 Print  "    (C) TIRES"
4420 Print  "    (D) ADD INFORMATION"
4430 Print  "    (E) SUBTRACT IMFORMATION"
4440 Print  "    (F) FINISHED"
4450 A$=inchr$(-1)
4460 If A$="" then Goto 4450
4470 If A$="F" then Return
4480 If A$="D" then [J=1;  CLS;  Goto 4350]
4490 If A$="E" then [J=2;  CLS;  Goto 4350]
4500 If J=0 then Goto 4300
4510 If A$="A" then Gosub 4550
4520 If A$="B" then Gosub 3800
4530 If A$="C" then Gosub 4750
4540 Goto 4300
4550 CLS
4560 Print  "WHAT TYPE OF SIDECAR DO YOU WANT?"
4570 Print  "    TYPE         COST   WT LOAD  SP  ARMOR  FIRE PROOF"
4580 Print  "(A) LIGHT         300  200  400   2   5/5     10/5"
4590 Print  "(B) HEAVY         450  350  750   3   5/6     10/6"
4600 C$=inchr$(-1)
4610 If C$="" then Goto 4600
4620 If J=1 then Gosub 4650
4630 If J=2 then Gosub 4690
4640 Return
4650 If C$="A" then [A=300;  B=200;  C=400;  D=2;  E=5;  F=5;  E1=10; C$="LIGHT"]
4660 If C$="B" then [A=450;  B=350;  C=750;  D=3;  E=5;  F=6;  E1=10; C$="HEAVY"]
4670 A1=A
4680 Return
4690 Print  "ARE YOU SURE? (Y/N) IF YOU GO THIS WAY, YOU'LL HAVE TO START OVER."
4700 Z$=inchr$(-1)
4710 If Z$="" then Goto 4700
4720 If Z$="Y" then Goto 1000
4730 If Z$="N" then Return
4740 Goto 4690
4750 CLS
4760 Print  "WHAT TYPE OF TIRES DO YOU WANT?"
4770 Print  "    TYPE                   COST     WT      SP"
4780 Print  "(A) STANDARD                 50      15      4"
4790 Print  "(B) HEAVY DUTY              100      20      6"
4800 Print  "(C) PUNCTURE RESISTANT      200      25      9"
4810 Print  "(D) RADIAL (+1 HC)          500      30      8"
4820 Print  "(E) SOLID                   500    37.5     12"
4830 G$=inchr$(-1)
4840 If G$="" then Goto 4830
4850 If J=1 then Gosub 4880
4860 If J=2 then Gosub 4950
4870 Return
4880 L=1
4890 If G$="A" then [A=A+50;  B=B+15;  M=4;  G$="STANDARD"]
4900 If G$="B" then [A=A+100;  B=B+20;  M=6;  G$="HEAVY DUTY"]
4910 If G$="C" then [A=A+200;  B=B+25;  M=9;  G$="PUNCTURE RESISTANT"]
4920 If G$="D" then [A=A+500;  B=B+30;  M=8;  K=K+1;  G$="RADIAL"]
4930 If G$="E" then [A=A+500;  B=B+37.5;  M=12;  G$="SOLID"]
4940 Return
4950 If G$="A" then [A=A-50;  B=B-15]
4960 If G$="B" then [A=A-100;  B=B-20]
4970 If G$="C" then [A=A-200;  B=B-25]
4980 If G$="D" then [A=A-500;  B=B-30;  K=K-1]
4990 If G$="E" then [A=A-500;  B=B-37.5]
5000 M=0
5010 G$=""
5020 Return
5030 N$=B$
5040 J=0
5050 CLS
5060 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
5070 Print  "YOU ARE IN THE RV/BUS MODE (PRESS 'E' OR 'F' FIRST)"
5080 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION."
5090 Print  "WHICH SECTION DO YOU WANT?"
5100 L$=L$+A$
5110 Print  L$
5120 Print  "    (A) TYPE"
5130 Print  "    (B) CHASSIS STRENGTH"
5140 Print  "    (C) POWER PLANT"
5150 Print  "    (D) TIRES"
5160 Print  "    (E) ADD INFORMATION"
5170 Print  "    (F) SUBTRACT INFORMATION"
5180 Print  "    (G) FINISHED"
5190 A$=inchr$(-1)
5200 If A$="" then Goto 5190
5210 K=1
5220 F$="HEAVY"
5230 If A$="E" then [J=1;  CLS;  Goto 5080]
5240 If A$="F" then [J=2;  CLS;  Goto 5080]
5250 If A$="G" then Return
5260 If J=0 then Goto 5030
5270 If A$="A" then Gosub 5320
5280 If A$="B" then Gosub 5550
5290 If A$="C" then Gosub 5750
5300 If A$="D" then Gosub 5970
5310 Goto 5030
5320 CLS
5330 Print  "WHAT TYPE OF BUS/RV DO YOU WANT?"
5340 Print  "    TYPE          COST   WT    LOAD  SP  ARMOR  FIRE PROOF"
5350 Print  "(A) 30'-BODY      5000  4000  16000  45  35/17    70/17"
5360 Print  "(B) 40'-BODY      7000  5500  21000  60  40/18    80/18"
5370 C$=inchr$(-1)
5380 If C$="" then Goto 5370
5390 If J=1 then Gosub 5420
5400 If J=2 then Gosub 5490
5410 Return
5420 If C$="A" then [A=5000;  B=4000;  C=16000;  D=45;  E=35;  F=17;  E1=70; C$="30'-BODY"]
5430 If C$="B" then [A=7000;  B=5500;  C=21000;  D=60;  E=40;  F=18;  E1=80; C$="40'-BODY"]
5440 A1=A
5450 C1=C
5460 B=B+150
5470 D=D-2
5480 Return
5490 Print  "ARE YOU SURE? (Y/N) IF YOU DO THIS, YOU'LL HAVE TO START OVER."
5500 Z$=inchr$(-1)
5510 If Z$="" then Goto 5500
5520 If Z$="Y" then Goto 1000
5530 If Z$="N" then Return
5540 Goto 5490
5550 CLS
5560 Print  "WHAT CHASSIS STRENGTH DO YOU WANT?"
5570 If J=2 then Z$="SAVE" else Z$="COST" 
5580 Print  "    TYPE              ",Z$,"     WT CARRIED"
5590 Print  "(A) STANDARD            0       ",C
5600 Print  "(B) HEAVY             ",.5*A1,"   ",.1*C1+C
5610 Print  "(C) EXTRA HEAVY       ",A1,"   ",.2*C1+C
5620 D$=inchr$(-1)
5630 If D$="" then Goto 5620
5640 If J=1 then Gosub 5670
5650 If J=2 then Gosub 5710
5660 Return
5670 If D$="A" then D$="STANDARD"
5680 If D$="B" then [A=A+.5*A1;  C=C+C1*.1;  D$="HEAVY"]
5690 If D$="C" then [A=A+A1;  C=C+C1*.2;  D$="EXTRA HEAVY"]
5700 Return
5710 If D$="B" then [A=A-.5*A1;  C=C-C1*.1]
5720 If D$="C" then [A=A-A1;  C=C-C1*.2]
5730 D$=""
5740 Return
5750 CLS
5760 Print  "WHAT TYPE OF POWER PLANT DO YOU WANT?"
5770 Print  "    TYPE          COST   WT   SP  DP  MAX RIG WT"
5780 Print  "(A) REGULAR      15000  3000  10  20     40000"
5790 Print  "(B) LARGE        20000  3500  13  26     60000"
5800 Print  "(C) SUPER        25000  4000  16  32     80000"
5810 E$=inchr$(-1)
5820 If E$="" then Goto 5810
5830 If J=1 then Gosub 5860
5840 If J=2 then Gosub 5900
5850 Return
5860 If E$="A" then [A=A+15000;  B=B+3000;  D=D-10;  G=20;  O=40000; E$="REGULAR"]
5870 If E$="B" then [A=A+20000;  B=B+3500;  D=D-13;  G=26;  O=60000; E$="LARGE"]
5880 If E$="C" then [A=A+25000;  B=B+4000;  D=D-16;  G=32;  O=80000; E$="SUPER"]
5890 Return
5900 If E$="A" then [A=A-15000;  B=B-3000;  D=D+10]
5910 If E$="B" then [A=A-20000;  B=B-3500;  D=D+13]
5920 If E$="C" then [A=A-25000;  B=B-4000;  D=D+16]
5930 G=0
5940 O=0
5950 E$=""
5960 Return
5970 L=10
5980 Gosub 7200
5990 Return
6000 N$=B$
6010 J=0
6020 CLS
6030 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
6040 Print  "YOU ARE IN THE TRACTOR MODE (PRESS 'E' OR 'F' FIRST)"
6050 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION>"
6060 Print  "WHICH SECTION DO YOU WANT?"
6070 L$=L$+A$
6080 Print  L$
6090 Print  "    (A) TYPE"
6100 Print  "    (B) CHASSIS STRENGTH"
6110 Print  "    (C) POWER PLANT"
6120 Print  "    (D) TIRES"
6130 Print  "    (E) ADD INFORMATION"
6140 Print  "    (F) SUBTRACT INFORMATION"
6150 Print  "    (G) FINISHED"
6160 F$="HEAVY"
6170 A$=inchr$(-1)
6180 If A$="" then Goto 6160
6190 K=0
6200 If A$="E" then [J=1;  CLS;  Goto 6050]
6210 If A$="F" then [J=2;  CLS;  Goto 6050]
6220 If A$="G" then Return
6230 If J=0 then Goto 6000
6240 If A$="A" then Gosub 6290
6250 If A$="B" then Gosub 5550
6260 If A$="C" then Gosub 5750
6270 If A$="D" then Gosub 5970
6280 Goto 6000
6290 CLS
6300 Print  "WHAT TYPE OF TRACTOR DO YOU WANT?"
6310 Print  "    TYPE               COST   WT    LOAD  SP  ARMOR  FIRE PROOF"
6320 Print  "(A) STANDARD CAB      12000  3500  10000  19  30/14    60/14"
6330 Print  "(B) STANDARD LONG     14000  3700  11000  22  32/15    64/15"
6340 Print  "(C) SLEEPER CAB       17000  3900  12000  24  32/15    64/15"
6350 Print  "(D) SLEEPER LONG      20000  4100  13500  27  34/16    68/16"
6360 C$=inchr$(-1)
6370 If C$="" then Goto 6360
6380 If J=1 then Gosub 6410
6390 If J=2 then Gosub 6500
6400 Return
6410 If C$="A" then [A=12000;  B=3500;  C=10000;  D=19;  E=30;  F=14;  E1=60; C$="STANDARD CAB"]
6420 If C$="B" then [A=14000;  B=3700;  C=11000;  D=22;  E=32;  F=15;  E1=64; C$="STANDARD LONG"]
6430 If C$="C" then [A=17000;  B=3900;  C=12000;  D=24;  E=32;  F=15;  E1=64; C$="SLEEPER CAB"]
6440 If C$="D" then [A=20000;  B=4100;  C=13500;  D=27;  E=34;  F=16;  E1=68; C$="SLEEPER LONG"]
6450 A1=A
6460 C1=C
6470 B=B+150
6480 D=D-2
6490 Return
6500 Print  "ARE YOU SURE? (Y/N) IF YOU DO THIS, YOU'LL HAVE TO START OVER."
6510 Z$=inchr$(-1)
6520 If Z$="" then Goto 6510
6530 If Z$="Y" then Goto 1000
6540 If Z$="N" then Return
6550 Goto 6500
6560 CLS
6570 Print  "WHAT IS THE MAXIMUM RIG WEIGHT?"
6580 Input  O
6590 C=O
6600 N$=B$
6610 J=0
6620 CLS
6630 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
6640 Print  "YOU ARE IN THE TRAILER/SEMI-TRAILER MODE. (PRESS 'C' OR 'D' FIRST)"
6650 If B>C or D<0 then Print  "YOU NEED TO SUBTRACT SOME INFORMATION."
6660 Print  "WHICH SECTION DO YOU WANT?"
6670 L$=L$+A$
6680 Print  L$
6690 Print  "    (A) TYPE"
6700 Print  "    (B) TIRES"
6710 Print  "    (C) ADD INFORMATION"
6720 Print  "    (D) SUBTRACT INFORMATION"
6730 Print  "    (E) FINISHED"
6740 F$="HEAVY"
6750 A$=inchr$(-1)
6760 If A$="" then Goto 6740
6770 If A$="E" then Return
6780 If A$="C" then [J=1;  CLS;  Goto 6650]
6790 If A$="D" then [J=2;  CLS;  Goto 6650]
6800 If J=0 then Goto 6600
6810 If A$="A" then Gosub 6840
6820 If A$="B" then Gosub 7100
6830 Goto 6600
6840 CLS
6850 Print  "WHAT TYPE OF TRAILER DO YOU WANT?"
6860 Print  "    TYPE        COST   WT    LOAD  SP  ARMOR  FIRE PROOF"
6870 Print  "(A) FLATBED     3000  2000 ",C," 50  40/18    80/18"
6880 Print  "(B) VAN         6000  3000 ",C," 80  40/18    80/18"
6890 Print  "(C) 'REEFER'   10000  3500 ",C," 75  40/18    80/18"
6900 Print  "(D) TANKER     16000  5000 ",C," 60  40/18    80/18"
6910 C$=inchr$(-1)
6920 If C$="" then Goto 6910
6930 If J=1 then Gosub 6960
6940 If J=2 then Gosub 7040
6950 Return
6960 If C$="A" then [A=3000;  B=2000;  D=50;  C$="FLATBED"]
6970 If C$="B" then [A=6000;  B=3000;  D=80;  C$="VAN"]
6980 If C$="C" then [A=10000;  B=3500;  D=75;  C$="'REEFER'"]
6990 If C$="D" then [A=16000;  B=5000;  D=60;  C$="TANKER"]
7000 E=40
7010 F=18
7020 E1=80
7030 Return
7040 Print  "ARE YOU SURE? (Y/N) IF YOU DO THIS, YOU'LL HAVE TO START OVER."
7050 Z$=inchr$(-1)
7060 If Z$="" then Goto 7050
7070 If Z$="Y" then Goto 1000
7080 If Z$="N" then Return
7090 Goto 7040
7100 CLS
7110 Print  "WHAT KIND OF TRAILER DO YOU WANT?"
7120 Print  "(A) 12 WHEELED ",C$
7130 Print  "(B) 10 WHEELED ",C$
7140 Print  "(C) 8 WHEELED ",C$
7150 Z$=inchr$(-1)
7160 If Z$="" then Goto 7150
7170 If Z$="A" then L=12
7180 If Z$="B" then L=10
7190 If Z$="C" then L=8
7200 CLS
7210 Print  "WHAT TYPE OF TIRES DO YOU WANT?"
7220 Print  "    TYPE                    COST   WT   DP"
7230 Print  "(A) STANDARD               ",L*150," ",L*60,"  6"
7240 Print  "(B) HEAVY DUTY             ",L*300," ",L*80,"  9"
7250 Print  "(C) PUNCTURE RESISTANT     ",L*600,L*100," 14"
7260 Print  "(D) SOLID                 ",L*1500,L*150," 18"
7270 G$=inchr$(-1)
7280 If G$="" then Goto 7270
7290 If J=1 then Gosub 7320
7300 If J=2 then Gosub 7370
7310 Return
7320 If G$="A" then [A=A+L*150;  B=B+L*60;  M=6;  G$="STANDARD"]
7330 If G$="B" then [A=A+L*300;  B=B+L*80;  M=9;  G$="HEAVY DUTY"]
7340 If G$="C" then [A=A+L*600;  B=B+L*100;  M=14;  G$="PUNCTURE RESISTANT"]
7350 If G$="D" then [A=A+L*1500;  B=B+L*150;  M=18;  G$="SOLID"]
7360 Return
7370 If G$="A" then [A=A-L*150;  B=B-L*60]
7380 If G$="B" then [A=A-L*300;  B=B-L*80]
7390 If G$="C" then [A=A-L*600;  B=B-L*100]
7400 If G$="D" then [A=A-L*1500;  B=B-L*150]
7410 L=0
7420 M=0
7430 G$=""
7440 Return
7450 N$=B$
7460 J=0
7470 CLS
7480 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
7490 Print  "YOU ARE IN HELICOPTER MODE (PRESS 'C' OR 'D' FIRST)"
7500 Print  "WHICH SECTION DO YOU WANT?"
7510 L$=L$+A$
7520 Print  L$
7530 Print  "    (A) TYPE"
7540 Print  "    (B) POWER PLANT"
7550 Print  "    (C) ADD INFORMATION"
7560 Print  "    (D) SUBTRACT INFORMATION"
7570 Print  "    (E) FINISHED"
7580 A$=inchr$(-1)
7590 If A$="" then Goto 7580
7600 If A$="E" then Return
7610 If A$="C" then [J=1;  CLS;  Goto 7500]
7620 If A$="D" then [J=2;  CLS;  Goto 7500]
7630 If J=0 then Goto 7450
7640 If A$="A" then Gosub 7670
7650 If A$="B" then Gosub 7930
7660 Goto 7450
7670 CLS
7680 Print  "WHAT TYPE OF HELICOPTER DO YOU WANT?"
7690 Print  "    TYPE          COST   WT   SP/CG  ARMOR  FIRE PROOF  HC  ROT DP"
7700 Print  "(A) ONE MAN      10000   500  13     16/8     32/8       3    2/2"
7710 Print  "(B) SMALL        20000   800  19     20/10    40/10      2    3/2"
7720 Print  "(C) STANDARD     40000  1200  24/ 6  30/14    60/14      1    3/2"
7730 Print  "(D) TRANSPORT    80000  2000  24/17  35/17    70/17      0    4/2"
7740 C$=inchr$(-1)
7750 If C$="" then Goto 7740
7760 If J=1 then Gosub 7790
7770 If J=2 then Gosub 7870
7780 Return
7790 If C$="A" then [A=10000;  B=500;  D=13;  E=16;  F=8;  E1=32;  K=3;  Q=2; C$="ONE MAN"]
7800 If C$="B" then [A=20000;  B=800;  D=19;  E=20;  F=10;  E1=40;  K=2;  Q=3; C$="SMALL"]
7810 If C$="C" then [A=40000;  B=1200;  D=24;  D1=6;  E=30;  E1=60;  F=14; K=1;  Q=3;  C$="STANDARD"]
7820 If C$="D" then [A=80000;  B=2000;  D=24;  D1=17;  E=35;  E1=70;  F=17; K=0;  Q=4;  C$="TRANSPORT"]
7830 R=2
7840 B=B+150
7850 D=D-2
7860 Return
7870 Print  "ARE YOU SURE? (Y/N) IF YOU GO THIS WAY YOU'LL HAVE TO START OVER."
7880 Z$=inchr$(-1)
7890 If Z$="" then Goto 7880
7900 If Z$="Y" then Goto 1000
7910 If Z$="N" then Return
7920 Goto 7870
7930 CLS
7940 Print  "WHAT TYPE OF POWER PLANT DO YOU WANT?"
7950 Print  "    TYPE         COST   WT   SP  DP    PF   MAX SPEED"
7960 Print  "(A) MINI        10000  2500   8  16   6700     180"
7970 Print  "(B) SMALL       15000  3000  10  20  13400     200"
7980 Print  "(C) STANDARD    20000  3500  13  26  20000     200"
7990 Print  "(D) SUPER       25000  4000  16  32  26700     200"
8000 E$=inchr$(-1)
8010 If E$="" then Goto 8000
8020 If J=1 then Gosub 8050
8030 If J=2 then Gosub 8110
8040 Return
8050 If E$="A" then [A=A+10000;  B=B+2500;  D=D-8;  G=16;  H=6700;  I=180; E$="MINI"]
8060 If E$="B" then [A=A+15000;  B=B+3000;  D=D-10;  G=20;  H=13400;  I=200; E$="SMALL"]
8070 If E$="C" then [A=A+20000;  B=B+3500;  D=D-13;  G=26;  H=20000;  I=200; E$="STANDARD"]
8080 If E$="D" then [A=A+25000;  B=B+4000;  D=D-16;  G=32;  H=26700;  I=200; E$="SUPER"]
8090 C=H*3
8100 Return
8110 If E$="A" then [A=A-10000;  B=B-2500;  D=D+8]
8120 If E$="B" then [A=A-15000;  B=B-3000;  D=D+10]
8130 If E$="C" then [A=A-20000;  B=B-3500;  D=D+13]
8140 If E$="D" then [A=A-25000;  B=B-4000;  D=D+16]
8150 C=0
8160 G=0
8170 H=0
8180 I=0
8190 E$=""
8200 Return
8210 N$=B$
8220 J=0
8230 CLS
8240 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
8250 Print  "YOU ARE IN EQUIPMENT MODE (PRESS 'F' OR 'G' FIRST)"
8260 Print  "WHAT IS THE MAXIMUM PRICE YOU CAN GO?"
8270 Print  "(A) 22000"
8280 Print  "(B)  6000"
8290 Print  "(C)  3000"
8300 Print  "(D)  1000"
8310 Print  "(E)   500"
8320 Print  "(F) ADD INFORMATION"
8330 Print  "(G) SUBTRACT INFORMATION"
8340 Print  "(H) FINISHED"
8350 Z$=inchr$(-1)
8360 If Z$="" then Goto 8350
8370 If Z$="H" then Return
8380 If Z$="F" then [J=1;  CLS;  Goto 8260]
8390 If Z$="G" then [J=2;  CLS;  Goto 8260]
8400 If J=0 then Goto 8210
8410 CLS
8420 Print  "PRESS <CTRL><NUM LOCK> TO PAUSE, PRESS A TO CONTINUE"
8430 Print  "<ENTER>"
8440 Input  S$
8450 If Z$="A" then Goto 8500
8460 If Z$="B" then Goto 8610
8470 If Z$="C" then Goto 8780
8480 If Z$="D" then Goto 8880
8490 If Z$="E" then Goto 9060
8500 CLS
8510 Print  "     ITEM                       COST    WT   SP  DP  ADDS  GW"
8520 Print  "(1)  CARGO SAFE                22000  12000  15   -    -    -"
8530 Print  "      ACCESSORIES:"
8540 Print  "(2)    OXYGEN REBREATHER        4500      -   -   -    -    -"
8550 Print  "(3)    REFRIGERATION UNIT       2000      -   -   -    -    -"
8560 Print  "(4)    SELF-DESTRUCT             900      -   -   -    -    -"
8570 Print  "(5)  CYBERLINK                 16000    100   1   1   +3    -"
8580 Print  "(6)  STEALTH MODE              16000    200   2   2    -    -"
8590 Print  "(7)  INTERIOR DRESSINGS        10000      -   -   -    -    -"
8600 Print  "(8)  4-SPACE POP UP CUPOLA      6500    750   6   -   +1    -"
8610 Print  "(9)  SOUND ENHANCEMENT          6000    150   1   2    -    -"
8620 Print  "(10) 4-SPACE POP UP TURRET      4500    600   6   -    -    -"
8630 Print  "(11) HI-RES TARGETING COMPUTER  4000      -   -   -   +2    -"
8640 Print  "(12) INFRARED                   4000    100   1   -    -    -"
8650 Print  "(13) PORTABLE SHOP (4 BOXES)    4000    300   4   8    -    -"
8660 Print  "(14) REMOTE CONTROL (SEND&REC)  4000      -   -   -    -    -"
8670 Print  "(15) 3-SPACE POP UP CUPOLA      3500    600   5   -   +1    -"
8680 Print  "(16) 3-SPACE POP UP TURRET      3500    450   5   -    -    -"
8690 Print  "(17) 4-SPACE CUPOLA             3500    500   2   -   +1    -"
8700 PRIN  -    -""
8710 For Z4=1 to 4000
8720 Next Z4
8730 T$=inchr$(-1)
8740 If T$="K" then [Input  Z;  Goto 9450]
8750 CLS
8760 Print  "     ITEM                       COST    WT   SP  DP  ADDS  GW"
8770 Print  "(18) 4-SPACE TURRET             3500    400   2   -    -    -"
8780 Print  "(19) HANDHELD TV CAMERA         3000     20   -   -    -    5"
8790 Print  "(20) 2-SPACE POP UP TURRET      2500    350   4   -    -    -"
8800 Print  "(21) 3-SPACE CUPOLA             2500    400   4   -   +1    -"
8810 Print  "(22) 3-SPACE TURRET             2500    300   2   -    -    -"
8820 Print  "(23) RADAR                      2500      -   -   -    -    -"
8830 Print  "(24) 1-SPACE POP UP TURRET      2500    300   3   -    -    -"
8840 Print  "(25) FORKLIFT                   2000   3000  10   -    -    -"
8850 Print  "(26) COMMUNICATIONS CENTER      2000    100   1   2    -    -"
8860 Print  "(27) 2-SPACE TURRET             1500    200  +2   -    -    -"
8870 Print  "(28) VEHICULAR PARACHUTE        1500    150   3   4    -    -"
8880 Print  "(29) TARGETING COMPUTER         1000      -   -   -   +1    -"
8890 Print  "(30) 1 SPACE TURRET             1000    150  +1   -    -    -"
8900 Print  "(31) ANTI-THEFT SYSTEM          1000      -   -   -    -    -"
8910 Print  "(32) ROLL CAGE                  1000    300   -   -    -    -"
8920 Print  "(33) ASSAULT RAMP               1000    100   1   -    -    -"
8930 Print  "WAIT (WHEN READY FOR INPUT, PRESS 'K'. ONLY PRESS 'K' ONCE.)"
8940 For Z4=1 to 4000
8950 Next Z4
8960 T$=inchr$(-1)
8970 If T$="K" then [Input  Z;  Goto 9450]
8980 CLS
8990 Print  "     ITEM                       COST    WT   SP  DP  ADDS  GW"
9000 Print  "(34) QUICK RELEASE KINGPIN      1000      -   -   -    -    -"
9010 Print  "(35) SOUND SYSTEM               1000    100   1   2    -    -"
9020 Print  "(36) BOMB BAY                   1000    100   1   -    -    -"
9030  CUPOLA             3500    500   2   -   +1    -""
9040 Print  "(38) TOOL KIT                    600     40   1   2    -    6"
9050 Print  "(39) LONG DISTANCE RADIO         600      -   -   -    -    -"
9060 Print  "(40) LASER TARGETING SCOPE       500      -   -   -   +1    -"
9070 Print  "(41) EXPLOSIVE KINGPIN           500      -   -   -    -    -"
9080 Print  "(42) WINCH                       500    100   1   3    -    -"
9090 Print  "(43) PONTOONS                    500     50   -   7    -    -"
9100 Print  "(44) FIRE EXTINGUISHER           300    150   -   -    -    -"
9110 Print  "(45) ARTFUL DODGER (BURNING OIL) 300     30   2   -    -    -"
9120 Print  "(46) SKID STRETCHERS             300     25   -   2    -    -"
9130 Print  "(47) BODY ARMOR                  250     10   -   3    -    -"
9140 Print  "(48) PERSONAL PARACHUTE          200     20   -   4    -    2"
9150 Print  "(49) SEARCHLIGHT                 200     50   1   1    -    -"
9160 Print  "WAIT (WHEN READY FOR INPUT, PRESS 'K'. ONLY PRESS 'K' ONCE.)"
9170 For Z4=1 to 4000
9180 Next Z4
9190 T$=inchr$(-1)
9200 If T$="K" then [Input  Z;  Goto 9450]
9210 CLS
9220 Print  "     ITEM                       COST    WT   SP  DP  ADDS  GW"
9230 Print  "(50) ROCKET PLATFORM             150    200   -   -    -    -"
9240 Print  "(51) WHEELRAMP, EACH             150    100   -   -    -    -"
9250 Print  "(52) ROOF RACK; SUB, COM, P-U    100     25  +2   -    -    -"
9260 Print  "(53) ROOF RACK; MID-SIZED        100     25  +3   -    -    -"
9270 Print  "(54) ROOF RACK; SW, VAN, LUX     100     25  +4   -    -    -"
9280 Print  "(55) STANDARD KINGPIN            100      -   -   -    -    -"
9290 Print  "(56) EXTRA MAGAZINE               50     15   1   1    -    -"
9300 Print  "(57) WEAPONS LINKAGE              50      -   -   -    -    -"
9310 Print  "(58) TV CAMERA TAPES              50      2   -   -    -  1/4"
9320 Print  "(59) ROPE LADDER                  50      -   -   -    -    2"
9330 Print  "(60) WEAPONS RACK (HOLDS 15 GW)   50     25   1   -    -    -"
9340 Print  "(61) HANDHELD MG CLIP             50     55   -   -    -    2"
9350 Print  "(62) HANDHELD RR CLIP             50     20   -   -    -    2"
9360 Print  "(63) GAS MASK                     30      -   -   -    -    1"
9370 Print  "(64) HANDHELD SUB MG CLIP         20      2   -   -    -    1"
9380 Print  "(65) HANDHELD RIF, STGN, LP, HP    5      -   -   -    -  1/2"
9390 Print  "WAIT (WHEN READY FOR INPUT, PRESS 'K'. ONLY PRESS 'K' ONCE.)"
9400 For Z4=1 to 4000
9410 Next Z4
9420 T$=inchr$(-1)
9430 If T$="K" then [Input  Z;  Goto 9450]
9440 Goto 8450
9450 Print  "HOW MANY DO YOU WANT?"
9460 Input  Z1
9470 If J=1 then Gosub 9500
9480 If J=2 then Gosub 10170
9490 Return
9500 If Z=1 then [A=A+22000*Z1;  B=B+12000*Z1;  D=D-15*Z1; I$(1)="CARGO SAFE "]
9510 If Z=2 then [A=A+4500*Z1;  I$(2)=" W/OXY REBR"]
9520 If Z=3 then [A=A+2000*Z1;  I$(3)=" W/REEFER  "]
9530 If Z=4 then [A=A+900*Z1;  I$(4)=" W/SELF DES"]
9540 If Z=5 then [A=A+16000*Z1;  B=B+100*Z1;  D=D-1*Z1;  W(5)=1;  V(5)=3; I$(5)="CYBERLINK  "]
9550 If Z=6 then [A=A+16000*Z1;  B=B+200*Z1;  D=D-2*Z1;  W(6)=2; I$(6)="STEALTH    "]
9560 If Z=7 then [A=A+10000*Z1;  I$(7)="INTERIOR   "]
9570 If Z=8 then [A=A+6500*Z1;  B=B+750*Z1;  D=D-6*Z1;  V(8)=1; I$(8)="4-SP P/U CP"]
9580 If Z=9 then [A=A+6000*Z1;  B=B+150*Z1;  D=D-1*Z1;  W(9)=2; I$(9)="SOUND ENHAN"]
9590 If Z=10 then [A=A+4500*Z1;  B=B+600*Z1;  D=D-6*Z1;  I$(10)="4-SP P/U TU"]
9600 If Z=11 then [A=A+4000*Z1;  V(11)=2;  I$(11)="HI-RES TACO"]
9610 If Z=12 then [A=A+4000*Z1;  B=B+100*Z1;  D=D-1*Z1;  I$(12)="INFRARED   "]
9620 If Z=13 then [A=A+4000*Z1;  B=B+300*Z1;  D=D-4*Z1;  W(13)=8; I$(13)="PORT SHOP  "]
9630 If Z=14 then [A=A+4000*Z1;  I$(14)="REMOTE CONT"]
9640 If Z=15 then [A=A+3500*Z1;  B=B+600*Z1;  D=D-5*Z1;  V(15)=1; I$(15)="3-SP P/U CU"]
9650 If Z=16 then [A=A+3500*Z1;  B=B+450*Z1;  D=D-5*Z1;  I$(16)="3-SP TURRET"]
9660 If Z=17 then [A=A+3500*Z1;  B=B+500*Z1;  D=D-2*Z1;  V(17)=1; I$(17)="4-SP CUPOLA"]
9670 If Z=18 then [A=A+3500*Z1;  B=B+400*Z1;  D=D-2*Z1;  I$(18)="4-SP TURRET"]
9680 If Z=19 then [A=A+3000*Z1;  B=B+20*Z1;  I$(19)="HDHLD TV CM"]
9690 If Z=20 then [A=A+2500*Z1;  B=B+350*Z1;  D=D-4*Z1;  I$(20)="2-SP P/U TU"]
9700 If Z=21 then [A=A+2500*Z1;  B=B+400*Z1;  D=D-2*Z1;  V(21)=1; I$(21)="3-SP CUPOLA"]
9710 If Z=22 then [A=A+2500*Z1;  B=B+300*Z1;  D=D-2*Z1;  I$(22)="3-SP TURRET"]
9720 If Z=23 then [A=A+2500*Z1;  I$(23)="RADAR      "]
9730 If Z=24 then [A=A+2000*Z1;  B=B+300*Z1;  D=D-3*Z1;  I$(24)="1-SP P/U TU"]
9740 If Z=25 then [A=A+2000*Z1;  B=B+3000*Z1;  D=D-10*Z1; I$(25)="FORKLIFT   "]
9750 If Z=26 then [A=A+2000*Z1;  B=B+100*Z1;  D=D-1*Z1;  W(26)=2; I$(26)="COMMO CEN  "]
9760 If Z=27 then [A=A+1500*Z1;  B=B+200*Z1;  D=D+2*Z1;  I$(27)="2-SP TURRET"]
9770 If Z=28 then [A=A+1500*Z1;  B=B+150*Z1;  D=D-3*Z1;  I$(28)="VEH PARA   "]
9780 If Z=29 then [A=A+1000*Z1;  V(29)=1;  I$(29)="TAR COM    "]
9790 If Z=30 then [A=A+1000*Z1;  B=B+150*Z1;  D=D+1*Z1;  I$(30)="1-SP TURRET"]
9800 If Z=31 then [A=A+1000*Z1;  I$(31)="ANTI-THEFT "]
9810 If Z=32 then [A=A+1000*Z1;  B=B+300*Z1;  I$(32)="ROLL CAGE  "]
9820 If Z=33 then [A=A+1000*Z1;  B=B+100*Z1;  D=D-1*Z1;  I$(33)="ASSAUL RAMP"]
9830 If Z=34 then [A=A+1000*Z1;  I$(34)="Q-R KINGPIN"]
9840 If Z=35 then [A=A+1000*Z1;  B=B+100*Z1;  D=D-1*Z1;  W(35)=2; I$(35)="SOUND SYS  "]
9850 If Z=36 then [A=A+1000*Z1;  B=B+100*Z1;  D=D-1*Z1;  I$(36)="BOMB BAY   "]
9860 If Z=37 then [A=A+1000*Z1;  I$(37)="SIDE DOOR  "]
9870 If Z=38 then [A=A+600*Z1;  B=B+40*Z1;  D=D-1*Z1;  W(38)=2; I$(38)="TL KIT (6) "]
9880 If Z=39 then [A=A+600*Z1;  I$(39)="LNG DIS RAD"]
9890 If Z=40 then [A=A+500*Z1;  V(40)=1;  I$(40)="LAS TAR SCO"]
9900 If Z=41 then [A=A+500*Z1;  I$(41)="EXP KINGPIN"]
9910 If Z=42 then [A=A+500*Z1;  B=B+100*Z1;  D=D-1*Z1;  W(42)=3]; I$(42)="WINCH      "
9920 If Z=43 then [A=A+500*Z1;  B=B+50*Z1;  W(43)=7;  I$(43)="PONTOONS   "]
9930 If Z=44 then [A=A+300*Z1;  B=B+150*Z1;  I$(44)="FIRE EXTING"]
9940 If Z=45 then [A=A+300*Z1;  B=B+30*Z1;  D=D-2*Z1;  I$(45)="ARTFUL DODG"]
9950 If Z=46 then [A=A+300*Z1;  B=B+25*Z1;  W(46)=2;  I$(46)="SKD STRETCH"]
9960 If Z=47 then [A=A+250*Z1;  B=B+10*Z1;  W(47)=3;  I$(47)="BODY ARMOR "]
9970 If Z=48 then [A=A+200*Z1;  B=B+200*Z1;  W(48)=4;  I$(48)="PER PAR (2)"]
9980 If Z=49 then [A=A+200*Z1;  B=B+50*Z1;  D=D-1*Z1;  W(49)=1; I$(49)="SEARCHLIGHT"]
9990 If Z=50 then [A=A+150*Z1;  B=B+200*Z1;  I$(50)="ROCKET PLAT"]
10000 If Z=51 then [A=A+150*Z1;  B=B+100*Z1;  I$(51)="WHEELRAMP  "]
10010 If Z=52 then [A=A+100*Z1;  B=B+25*Z1;  D=D+2*Z1;  I$(52)="ROOF RACK  "]
10020 If Z=53 then [A=A+100*Z1;  B=B+25*Z1;  D=D+3*Z1;  I$(53)="ROOF RACK  "]
10030 If Z=54 then [A=A+100*Z1;  B=B+25*Z1;  D=D+4*Z1;  I$(54)="ROOF RACK  "]
10040 If Z=55 then [A=A+100*Z1;  I$(55)="STD KINGPIN"]
10050 If Z=56 then [A=A+50*Z1;  B=B+15*Z1;  D=D-1*Z1;  W(56)=1; I$(56)="EX MAGAZINE"]
10060 If Z=57 then [A=A+50*Z1;  I$(57)="WEAPON LINK"]
10070 If Z=58 then [A=A+50*Z1;  B=B+2*Z1;  I$(58)="TV TAP (1/4)"]
10080 If Z=59 then [A=A+50*Z1;  I$(59)="ROPE LAD (2)"]
10090 If Z=60 then [A=A+50*Z1;  B=B+25*Z1;  D=D-1*Z1;  I$(60)="WEAPON RACK"]
10100 If Z=61 then [A=A+50*Z1;  B=B+55*Z1;  I$(61)="HH MG CL(2)"]
10110 If Z=62 then [A=A+50*Z1;  B=B+20*Z1;  I$(62)="HH RR CL(2)"]
10120 If Z=63 then [A=A+30*Z1;  I$(63)="GAS MASK(1)"]
10130 If Z=64 then [A=A+20*Z1;  B=B+2*Z1;  I$(64)="HH SB CL(1)"]
10140 If Z=65 then [A=A+5*Z1;  I$(65)="SM ARM CL(.5)"]
10150 R1(Z)=Z1
10160 Goto 8210
10170 If Z=1 then [A=A-22000*Z1;  B=B-12000*Z1;  D=D+15*Z1]
10180 If Z=2 then A=A-4500*Z1
10190 If Z=3 then A=A-2000*Z1
10200 If Z=4 then A=A-900*Z1
10210 If Z=5 then [A=A-16000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10220 If Z=6 then [A=A-16000*Z1;  B=B-200*Z1;  D=D+2*Z1]
10230 If Z=7 then A=A-10000*Z1
10240 If Z=8 then [A=A-6500*Z1;  B=B-750*Z1;  D=D+6*Z1]
10250 If Z=9 then [A=A-6000*Z1;  B=B-150*Z1;  D=D+1*Z1]
10260 If Z=10 then [A=A-4500*Z1;  B=B-600*Z1;  D=D+6*Z1]
10270 If Z=11 then A=A-4000*Z1
10280 If Z=12 then [A=A-4000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10290 If Z=13 then [A=A-4000*Z1;  B=B-300*Z1;  D=D+4*Z1]
10300 If Z=14 then A=A-4000*Z1
10310 If Z=15 then [A=A-3500*Z1;  B=B-600*Z1;  D=D+5*Z1]
10320 If Z=16 then [A=A-3500*Z1;  B=B-450*Z1;  D=D+5*Z1]
10330 If Z=17 then [A=A-3500*Z1;  B=B-500*Z1;  D=D+2*Z1]
10340 If Z=18 then [A=A-3500*Z1;  B=B-400*Z1;  D=D+2*Z1]
10350 If Z=19 then [A=A-3000*Z1;  B=B-20*Z1]
10360 If Z=20 then [A=A-2500*Z1;  B=B-350*Z1;  D=D+4*Z1]
10370 If Z=21 then [A=A-2500*Z1;  B=B-400*Z1;  D=D+2*Z1]
10380 If Z=22 then [A=A-2500*Z1;  B=B-300*Z1;  D=D+2*Z1]
10390 If Z=23 then A=A-2500*Z1
10400 If Z=24 then [A=A-2000*Z1;  B=B-300*Z1;  D=D+3*Z1]
10410 If Z=25 then [A=A-2000*Z1;  B=B-3000*Z1;  D=D+10*Z1]
10420 If Z=26 then [A=A-2000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10430 If Z=27 then [A=A-1500*Z1;  B=B-200*Z1;  D=D-2*Z1]
10440 If Z=28 then [A=A-1500*Z1;  B=B-150*Z1;  D=D+3*Z1]
10450 If Z=29 then A=A-1000*Z1
10460 If Z=30 then [A=A-1000*Z1;  B=B-150*Z1;  D=D-1*Z1]
10470 If Z=31 then A=A-1000*Z1
10480 If Z=32 then [A=A-1000*Z1;  B=B-300*Z1]
10490 If Z=33 then [A=A-1000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10500 If Z=34 then A=A-1000*Z1
10510 If Z=35 then [A=A-1000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10520 If Z=36 then [A=A-1000*Z1;  B=B-100*Z1;  D=D+1*Z1]
10530 If Z=37 then A=A-1000*Z1
10540 If Z=38 then [A=A-600*Z1;  B=B-40*Z1;  D=D+1*Z1]
10550 If Z=39 then A=A-600*Z1
10560 If Z=40 then A=A-500*Z1
10570 If Z=41 then A=A-500*Z1
10580 If Z=42 then [A=A-500*Z1;  B=B-100*Z1;  D=D+1*Z1]
10590 If Z=43 then [A=A-500*Z1;  B=B-50*Z1]
10600 If Z=44 then [A=A-300*Z1;  B=B-150*Z1]
10610 If Z=45 then [A=A-300*Z1;  B=B-30*Z1;  D=D+2*Z1]
10620 If Z=46 then [A=A-300*Z1;  B=B-25*Z1]
10630 If Z=47 then [A=A-250*Z1;  B=B-10*Z1]
10640 If Z=48 then [A=A-200*Z1;  B=B-200*Z1]
10650 If Z=49 then [A=A-200*Z1;  B=B-50*Z1;  D=D+1*Z1]
10660 If Z=50 then [A=A-150*Z1;  B=B-200*Z1]
10670 If Z=51 then [A=A-150*Z1;  B=B-100*Z1]
10680 If Z=52 then [A=A-100*Z1;  B=B-25*Z1;  D=D-2*Z1]
10690 If Z=53 then [A=A-100*Z1;  B=B-25*Z1;  D=D-3*Z1]
10700 If Z=54 then [A=A-100*Z1;  B=B-25*Z1;  D=D-4*Z1]
10710 If Z=55 then A=A-100*Z1
10720 If Z=56 then [A=A-50*Z1;  B=B-15*Z1;  D=D+1*Z1]
10730 If Z=57 then A=A-50*Z1
10740 If Z=58 then [A=A-50*Z1;  B=B-2*Z1]
10750 If Z=59 then A=A-50*Z1
10760 If Z=60 then [A=A-50*Z1;  B=B-25*Z1;  D=D+1*Z1]
10770 If Z=61 then [A=A-50*Z1;  B=B-55*Z1]
10780 If Z=62 then [A=A-50*Z1;  B=B-20*Z1]
10790 If Z=63 then A=A-30*Z1
10800 If Z=64 then [A=A-20*Z1;  B=B-2*Z1]
10810 If Z=65 then A=A-5*Z1
10820 I$(Z)=""
10830 V(Z)=0
10840 W(Z)=0
10850 R1(Z)=0
10860 Goto 8210
10870 J=0
10880 CLS
10890 Print  "SO FAR-COST",A,":WEIGHT",B,":CAPACITY",C,":SPACE LEFT",D
10900 Print  "YOU ARE IN THE WEAPONS MODE (PRESS 'A' OR 'B' FIRST)"
10910 Print  "(A) ADD INFORMATION"
10920 Print  "(B) SUBTRACT INFORMATION"
10930 Print  "(C) FINISHED"
10940 Z$=inchr$(-1)
10950 If Z$="" then Goto 10940
10960 If Z$="C" then Return
10970 If Z$="A" then J=1
10980 If Z$="B" then J=2
10990 If J=0 then Goto 10870
11000 Print  "     TYPE             DAM  HIT   COST   WT   SP  DP  SH  CPS  WPS"
11010 Print  "(1)  ARTILLERY PIECE   8    13  25000  3000   -  15   1  150   30"
11020 Print  "(2)  HEAVY LASER       4     6  12000  1000   3   2   -   -    -"
11030 Print  "(3)  TANK GUN          6     7  10000  1200  10  10  10  100   20"
11040 Print  "(4)  LASER             3     6   8000   500   2   2   -   -    -"
11050 Print  "(5)  ANTI-TANK GUN     3     8   2000   600   3   5  10   50   10"
11060 Print  "(6)  VULCAN            2     6   2000   350   2   3  20   35    5"
11070 Print  "(7)  RECOILLESS RIFLE  2     7   1500   300   2   4  10   35    5"
11080 Print  "(8)  GRENADE LAUNCHER  *     7   1000   200   2   2  20   *     4"
11090 Print  "(9)  ROCKET LAUNCHER   2     8   1000   200   2   2  10   35    5"
11100 Print  "(10) MACHINE GUN       1     7   1000   150   1   3  20   25  2.5"
11110 Print  "(11) HVY PAINT SPRAY   #     #    800    50   2   3  10   40    8"
11120 Input  "<ENTER>",Z
11130 Print  "(12) FLAME THROWER     1     6    500   450   2   2  10   25    5"
11140 Print  "(13) MINE DROPPER      @     @    500   150   2   2  10   50    5"
11150 Print  "(14) STAR-SHELL LNCHR  -     -    500   100   1   2   5   50    5"
11160 Print  "(15) HEAVY OIL JET     #     #    500    50   3   4  10   40    8"
11170 Print  "(16) HEAVY TG SS       #     #    500    50   2   4  10  200    5"
11180 Print  "(17) HVY SMOKESCREEN   #     #    500    50   2   4  10   40   20"
11190 Print  "(18) PAINT SPRAY       #     #    400    25   1   2  25   10    2"
11200 Print  "(19) OIL JET           #     #    250    25   2   3  25   10    2"
11210 Print  "(20) TEAR GAS SS       #     #    250    25   1   4  10   50    1"
11220 Print  "(21) SMOKESCREEN       #     #    250    25   1   4  10   10    5"
11230 Print  "(22) HEAVY ROCKET      3     9    200   100   1   2   1   -    -"
11240 Print  "(23) BOMB              4     9    100   100   1   2   1   -    -"
11250 Print  "(24) SPIKEDROPPER      @     @    100   100   1   4  10   20    5"
11260 Print  "(25) A.P. FLECHETTE    -     -     50     -   -   -   -   -    -"
11270 Input  Z
11280 Print  "HOW MANY WEAPONS DO YOU WANT?"
11290 Input  Z1
11300 If J=0 then Goto 10870
11310 If J=1 then Gosub 11340
11320 If J=2 then Gosub 11620
11330 Goto 10870
11340 If Z=1 then [A=A+25000*Z1;  B=B+3000*Z1;  X(1)=15;  Y1=1;  Y2=150; Y3=30;  H$(1)="ARTILLERY PIECE"]
11350 If Z=2 then [A=A+12000*Z1;  B=B+1000*Z1;  D=D-3*Z1;  X(2)=2; H$(2)="HEAVY LASER"]
11360 If Z=3 then [A=A+10000*Z1;  B=B+12000*Z1;  D=D-10*Z1;  X(3)=10;  Y1=10; Y2=100;  Y3=20;  H$(3)="TANK GUN"]
11370 If Z=4 then [A=A+8000*Z1;  B=B+500*Z1;  D=D-2*Z1;  X(4)=2; H$(4)="LASER"]
11380 If Z=5 then [A=A+2000*Z1;  B=B+600*Z1;  D=D-3*Z1;  X(5)=5;  Y1=10; Y2=50;  Y3=10;  H$(5)="ANTI-TANK GUN"]
11390 If Z=6 then [A=A+2000*Z1;  B=B+350*Z1;  D=D-2*Z1;  X(6)=3;  Y1=20; Y2=35;  Y3=5;  H$(6)="VULCAN"]
11400 If Z=7 then [A=A+1500*Z1;  B=B+300*Z1;  D=D-2*Z1;  X(7)=4;  Y1=10; Y2=35;  Y3=5;  H$(7)="RECOILLESS RIFLE"]
11410 If Z=8 then [A=A+1000*Z1;  B=B+200*Z1;  D=D-2*Z1;  X(8)=2; H$(8)="GRENADE LAUNCHER"]
11420 If Z=9 then [A=A+1000*Z1;  B=B+200*Z1;  D=D-2*Z1;  X(9)=2;  Y1=10; Y2=35;  Y3=5;  H$(9)="ROCKET LAUNCHER"]
11430 If Z=10 then [A=A+1000*Z1;  B=B+150*Z1;  D=D-1*Z1;  X(10)=3;  Y1=20; Y2=25;  Y3=2.5;  H$(10)="MACHINE GUN"]
11440 If Z=11 then [A=A+800*Z1;  B=B+50*Z1;  D=D-2*Z1;  X(11)=3;  Y1=10; Y2=40;  Y3=8;  H$(11)="HEAVY PAINT SPRAY"]
11450 If Z=12 then [A=A+500*Z1;  B=B+450*Z1;  D=D-2*Z1;  X(12)=2;  Y1=10; Y2=50;  Y3=5;  H$(12)="FLAME THROWER"]
11460 If Z=13 then [A=A+500*Z1;  B=B+150*Z1;  D=D-2*Z1;  X(13)=2;  Y1=10; Y2=50;  Y3=5;  H$(13)="MINE DROPPER"]
11470 If Z=14 then [A=A+500*Z1;  B=B+100*Z1;  D=D-1*Z1;  X(14)=2;  Y1=5; Y2=50;  Y3=5;  H$(14)="STAR-SHELL LAUNCHER"]
11480 If Z=15 then [A=A+500*Z1;  B=B+50*Z1;  D=D-3*Z1;  X(15)=4;  Y1=10; Y2=40;  Y3=8;  H$(15)="HEAVY OIL JET"]
11490 If Z=16 then [A=A+500*Z1;  B=B+50*Z1;  D=D-2*Z1;  X(16)=4;  Y1=10; Y2=200;  Y3=5;  H$(16)="HEAVY TG SS"]
11500 If Z=17 then [A=A+500*Z1;  B=B+50*Z1;  D=D-2*Z1;  X(17)=4;  Y1=10; Y2=40;  Y3=20;  H$(17)="HEAVY SMOKESCREEN"]
11510 If Z=18 then [A=A+400*Z1;  B=B+25*Z1;  D=D-1*Z1;  X(18)=2;  Y1=25; Y2=10;  Y3=2;  H$(18)="PAINT SPRAY"]
11520 If Z=19 then [A=A+250*Z1;  B=B+25*Z1;  D=D-2*Z1;  X(19)=3;  Y1=25; Y2=10;  Y3=2;  H$(19)="OIL JET"]
11530 If Z=20 then [A=A+250*Z1;  B=B+25*Z1;  D=D-1*Z1;  X(20)=4;  Y1=10; Y2=50;  Y3=1;  H$(20)="TEAR GAS SMOKESCREEN"]
11540 If Z=21 then [A=A+250*Z1;  B=B+25*Z1;  D=D-1*Z1;  X(21)=4;  Y1=10; Y2=10;  Y3=5;  H$(21)="SMOKESCREEN"]
11550 If Z=22 then [A=A+200*Z1;  B=B+100*Z1;  D=D-1*Z1;  X(22)=2; H$(22)="HEAVY ROCKET"]
11560 If Z=23 then [A=A+100*Z1;  B=B+100*Z1;  D=D-1*Z1;  X(23)=2; H$(23)="BOMB"]
11570 If Z=24 then [A=A+100*Z1;  B=B+25*Z1;  D=D-1*Z1;  X(24)=4;  Y1=10; Y2=20;  Y3=5;  H$(24)="SPIKEDROPPER"]
11580 If Z=25 then [A=A+50*Z1;  H$(25)="ANTI-PERSONNEL FLECHETTE GRANADE"]
11590 R2(Z)=Z1
11600 Gosub 12930
11610 Return
11620 If Z=1 then [A=A-25000*Z1;  B=B-3000*Z1;  Y1=1;  Y2=150;  Y3=30]
11630 If Z=2 then [A=A-12000*Z1;  B=B-1000*Z1;  D=D+3*Z1]
11640 If Z=3 then [A=A-10000*Z1;  B=B-12000*Z1;  D=D+10*Z1;  Y1=10;  Y2=100; Y3=20]
11650 If Z=4 then [A=A-8000*Z1;  B=B-500*Z1;  D=D+2*Z1]
11660 If Z=5 then [A=A-2000*Z1;  B=B-600*Z1;  D=D+3*Z1;  Y1=10;  Y2=50; Y3=10]
11670 If Z=6 then [A=A-2000*Z1;  B=B-350*Z1;  D=D+2*Z1;  Y1=20;  Y2=35;  Y3=5]
11680 If Z=7 then [A=A-1500*Z1;  B=B-300*Z1;  D=D+2*Z1;  Y1=10;  Y2=35;  Y3=5]
11690 If Z=8 then [A=A-1000*Z1;  B=B-200*Z1;  D=D+2*Z1]
11700 If Z=9 then [A=A-1000*Z1;  B=B-200*Z1;  D=D+2*Z1;  Y1=10;  Y2=35;  Y3=5]
11710 If Z=10 then [A=A-1000*Z1;  B=B-150*Z1;  D=D+1*Z1;  Y1=20;  Y2=25; Y3=2.5]
11720 If Z=11 then [A=A-800*Z1;  B=B-50*Z1;  D=D+2*Z1;  Y1=10;  Y2=40;  Y3=8]
11730 If Z=12 then [A=A-500*Z1;  B=B-450*Z1;  D=D+2*Z1;  Y1=10;  Y2=50;  Y3=5]
11740 If Z=13 then [A=A-500*Z1;  B=B-150*Z1;  D=D+2*Z1;  Y1=10;  Y2=50;  Y3=5]
11750 If Z=14 then [A=A-500*Z1;  B=B-100*Z1;  D=D+1*Z1;  Y1=5;  Y2=50;  Y3=5]
11760 If Z=15 then [A=A-500*Z1;  B=B-50*Z1;  D=D+3*Z1;  Y1=10;  Y2=40;  Y3=8]
11770 If Z=16 then [A=A-500*Z1;  B=B-50*Z1;  D=D+2*Z1;  Y1=10;  Y2=200;  Y3=5]
11780 If Z=17 then [A=A-500*Z1;  B=B-50*Z1;  D=D+2*Z1;  Y1=10;  Y2=40;  Y3=20]
11790 If Z=18 then [A=A-400*Z1;  B=B-25*Z1;  D=D+1*Z1;  Y1=25;  Y2=10;  Y3=2]
11800 If Z=19 then [A=A-250*Z1;  B=B-25*Z1;  D=D+2*Z1;  Y1=25;  Y2=10;  Y3=2]
11810 If Z=20 then [A=A-250*Z1;  B=B-25*Z1;  D=D+1*Z1;  Y1=10;  Y2=50;  Y3=1]
11820 If Z=21 then [A=A-250*Z1;  B=B-25*Z1;  D=D+1*Z1;  Y1=10;  Y2=10;  Y3=5]
11830 If Z=22 then [A=A-200*Z1;  B=B-100*Z1;  D=D+1*Z1]
11840 If Z=23 then [A=A-100*Z1;  B=B-100*Z1;  D=D+1*Z1]
11850 If Z=24 then [A=A-100*Z1;  B=B-25*Z1;  D=D+1*Z1;  Y1=10;  Y2=20;  Y3=5]
11860 If Z=25 then A=A-50*Z1
11870 H$(Z)=""
11880 X(Z)=0
11890 R2(Z)=0
11900 Gosub 12930
11910 Return
11920 CLS
11930 P=0
11940 Print  "WHEELGUARDS? (PRESS 'C' OR 'D' FIRST)"
11950 Print  "    TYPE                        ARMOR  FIRE PROOF EXTRA COST  SP  MAX PER WHEEL"
11960 Print  "(A) WHEELGUARDS                 10/4     20/4"
11970 Print  "(B) RETRACTABLE WHEELGUARDS     10/4     20/1       250 EA     1       10"
11980 Print  "(C) ADD INFORMATION"
11990 Print  "(D) SUBTRACT INFORMATION"
12000 J$=inchr$(-1)
12010 If J$="" then Goto 12000
12020 If J$="C" then [J=1;  CLS;  Goto 11920]
12030 If J$="D" then [J=2;  CLS;  Goto 11920]
12040 If J=0 then Goto 11920
12050 Print  "HOW MANY POINTS PER WHEEL?"
12060 Input  U
12070 Print  "DO YOU WANT (1) REGULAR ARMOR; OR (2) FIRE PROOF?"
12080 Input  U1
12090 If J=1 then Gosub 12120
12100 If J=2 then Gosub 12150
12110 Return
12120 If J$="A" then [A=A+10*U1*U*L;  B=B+U*4*L;  J$="WHEELGUARDS"]
12130 If J$="B" then [A=A+10*U1*U*L+250*L;  B=B+U*4*L+25*L;  D=D-L; J$="RETRACTABLE WHEELGUARDS"]
12140 Return
12150 If J$="A" then [A=A-10*U1*U*L;  B=B-U*4*L]
12160 If J$="B" then [A=A-10*U1*U*L+250*L;  B=B-U*4*L+25*L;  D=D+L]
12170 J$=""
12180 Return
12190 CLS
12200 If N$="G" then Goto 12890
12210 If N$="D" or N$="E" or N$="F" then [M$="2.5mph UNTIL 25mph IS REACHED THEN IT IS 5mph";  Goto 12280]
12220 If N$="C" or N$="F" then Goto 12280
12230 If H<B*.33 then I1=0
12240 If H<B*.5 and H>=B*.33 then I1=5
12250 If H<B and H>=B*.5 then I1=10
12260 If H>=B then I1=15
12270 If I1=0 then [Print  "YOU DON'T HAVE ENOUGH POWER TO PULL YOUR LOAD, EITHER GET A BIGGER ENGINE OR GETRID OF SOME STUFF"; For Z=1 to 4000;  Next Z;  Return]
12280 F2=C-B
12290 F3=F2/F
12300 F3=int(F3)
12310 If U1=0 then [Print  "WHAT KIND OF ARMOR DO YOU WANT, (1) REGULAR ARMOR; OR (2) FIRE PROOF ARMOR?"; Input  U1]
12320 Print  "YOU CAN GET",F3,"POINTS OF ARMOR. THE COST WOULD BE",E*U1*F3, "FOR ",
12330 If U1=1 then Print  "REGULAR ARMOR"else Print  "FIRE PROOF ARMOR"
12340 Print  "HOW MANY POINTS OF ARMOR DO YOU WANT?"
12350 Input  F1
12360 If U1=1 then [A=A+F1*E;  B=B+F1*F]
12370 If U1=2 then [A=A+F1*E1;  B=B+F1*F;  K$="FIRE PROOF "]
12380 Print  "DO YOU WANT TO PRINT IT ON A PRINTER? (Y/N)"
12390 Z$=inchr$(-1)
12400 If Z$="" then Goto 12390
12410 If Z$="Y" then Goto 13070
12420 If Z$="N" then Goto 12440
12430 Goto 12380
12440 CLS
12450 Print  "VEHICLE TYPE-",C$,";",K$,"ARMOR-",F1,"POINTS;PRICE-",A,"; WEIGHT-",B
12460 If N$="A" or N$="D" or N$="E" then Print  "CHASSIS STRENGTH-",D$
12470 If N$="C" or N$="F" then Goto 12480 else Print  "POW PLNT-",E$,"; DAM-",G,"PTS;MAX SPEED-",I,"mph;ACC-",I1,"mph;",M$
12480 Print  "HC-",K,
12490 If N$="F" then Goto 12500 else Print  "SUSPENSION-",F$
12500 Print  "TIRES-YOU HAVE",L,G$," TIRES. WITH",M,"DAMAGE POINTS EACH."
12510 Print  "YOU HAVE",D,"SPACES LEFT AND",D1,"CARGO SPACES"
12520 If N$="E" then Print  "MAXIMUM RIG WEIGHT-",O
12530 If N$="G" then Print  "MAIN ROTOR HAS",Q, "DAMAGE POINTS AND THE STEERING ROTOR HAS",R,"DAMAGE POINTS."
12540 If J$="" then Goto 12550 else Print  J$,"-",U,"ON EACH WHEEL"
12550 Print  "CHARACTER SKILLS"
12560 For J=1 to 7
12570 Print  W$(J),W(J),
12580 If W$(J)="" then 12590 Else Next 
12590 Print  
12600 Print  "EQUIPMENT"
12610 Print  "#   ITEM",,,,,"DP",,,"COMBAT ADDS"
12620 For Z=1 to 65
12630 If I$(Z)="" then Goto 12670
12640 Print  R1(Z),I$(Z),,,,W(Z),,,V(Z)
12650 For Z1=1 to 250
12660 Next Z1
12670 Next Z
12680 Print  "WEAPONS"
12690 Print  "#   ITEM",,,,,"DP",,,"SHOTS"
12700 For Z=1 to 25
12710 If H$(Z)="" then Goto 12750
12720 Print  R2(Z),H$(Z),,,,X(Z),,,Y(Z)
12730 For Z1=1 to 250
12740 Next Z1
12750 Next Z
12760 Print  "<ENTER> TO CONTINUE"
12770 Input  Q$
12780 CLS
12790 Print  "WHAT DO YOU WANT TO DO?"
12800 Print  "(A) LOOK AT INFORMATION AGAIN?"
12810 Print  "(B) MAKE UP SOMETHING ELSE?"
12820 Print  "(C) STOP"
12830 R$=inchr$(-1)
12840 If R$="" then Goto 12830
12850 If R$="A" then Goto 12380
12860 If R$="B" then Goto 1000
12870 If R$="C" then End
12880 Goto 12760
12890 If H<B then I1=0
12900 If H<B*1.5 and H>=B then I1=5
12910 If H>B then I1=10
12920 Goto 12270
12930 If Z=2 or Z=4 or Z=22 or Z=23 then Return
12940 If J=1 then Gosub 12970
12950 If J=2 then Gosub 13030
12960 Return
12970 Print  "HOW MANY SHOTS PER MAGAZINE DO YOU WANT?"
12980 Print  "YOU HAVE",Z1,H$(Z),"S WITH A CAPACITY OF",Y1, "SHOTS PER MAGAZINE"
12990 Input  Y(Z)
13000 A=A+Y(Z)*Y2*Z1
13010 B=B+Y(Z)*Y3*Z1
13020 Return
13030 A=A-Y(Z)*Y2*Z1
13040 B=B-Y(Z)*Y3*Z1
13050 Y(Z)=0
13060 Return
13070 CLS
13080 Print #1,  "VEHICLE TYPE-",C$,";",K$,"ARMOR-",F1,"POINTS; PRICE-",A,";WEIGHT-",B
13090 If N$="A" or N$="D" or N$="E" then Print #1,  "CHASSIS STRENGTH-",D$
13100 If N$="C" or N$="F" then Goto 13110 else Print #1,  "POW PLNT-",E$, ";DAM-",G,"PTS;MAX SPEED-",I,"mph;ACC-",I1,"mph;",M$
13110 Print #1,  "HC-",K,
13120 If N$="F" then Goto 13130 else Print #1,  "SUSPENSION-",F$
13130 Print #1,  "TIRES-YOU HAVE",L,G$," TIRES. WITH",M,"DAMAGE POINTS EACH."
13140 Print #1,  "YOU HAVE",D,"SPACES LEFT AND",D1,"CARGO SPACES"
13150 If N$="E" then Print #1,  "MAXIMUM RIG WEIGHT-",O
13160 If N$="G" then Print #1,  "MAIN ROTOR HAS",Q, "DAMAGE POINTS AND THE STEERING ROTOR HAS",R,"DAMAGE POINTS."
13170 If J$="" then Goto 13180 else Print #1,  J$,"-",U,"ON EACH WHEEL"
13180 Print #1,  "CHARACTER SKILLS"
13190 For J=1 to 7
13200 Print #1,  W$(J),W(J),
13210 If W$(J)="" then 13220 Else Next 
13220 Print #1  
13230 Print #1,  "EQUIPMENT"
13240 Print #1,  "#   ITEM",,,,,"DP",,,"COMBAT ADDS"
13250 For Z=1 to 65
13260 If I$(Z)="" then Goto 13300
13270 Print #1,  R1(Z),I$(Z),,,,W(Z),,,V(Z)
13280 For Z1=1 to 250
13290 Next Z1
13300 Next Z
13310 Print #1,  "WEAPONS"
13320 Print #1,  "#   ITEM",,,,,"DP",,,"SHOTS"
13330 For Z=1 to 25
13340 If H$(Z)="" then Goto 13380
13350 Print #1,  R2(Z),H$(Z),,,,X(Z),,,Y(Z)
13360 For Z1=1 to 250
13370 Next Z1
13380 Next Z
13390 Goto 12760
13400 J=0
13410 CLS
13420 Print  "YOU HAVE 30 POINTS TO SPLIT UP BETWEEN THREE OF THESE SKILLS"
13430 Print  "CYCLELLIST"
13440 Print  "DRIVER"
13450 Print  "TRUCKER"
13460 Print  "HELICOPTER"
13470 Print  "GUNNER"
13480 Print  "MECHANIC"
13490 Print  "HELICOPTER MECHANIC"
13500 Print  "PARACHUTE/HANG GLIDER"
13510 For J=1 to 8
13520 Print  J,"-WHICH SKILL (DEF=DONE)",
13530 Input  W$(J)
13540 If W$(J)="" then Goto 13550 else [Print  J,"-HOW MANY POINTS",; Input  W(J);  XX=XX+W(J);  Next] 
13550 If XX>30 then [Print  "TRY AGAIN WITH LESS POINTS";  Goto 13430]
13560 If XX<30 then Print  "ARE YOU SURE? (Y/N)"
13570 If XX=30 then Return
13580 Z$=inchr$(-1)
13590 If Z$="" then Goto 13580
13600 If Z$="Y" then Return
13610 If Z$="N" then Goto 13430
13620 Goto 13550
13630 CLS
13640 Print  "HOW MANY GUNNERS DO YOU WANT?"
13650 Input  Z1
13660 B=B+Z1*150
13670 D=D-Z1*2
13680 Return
13700 End
