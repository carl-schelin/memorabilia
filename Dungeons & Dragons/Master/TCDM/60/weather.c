/* []---------------------------------------------------------------------[] */
/* |     Weather.cpp: Weather calling routine and initialization code.     | */
/* |                                                                       | */
/* |             The Weather.cpp source code and concepts are              | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __WEATHER__

#include <stdio.h>
#include <stdlib.h>
#include <TcxlHlp.H>
#include <TcxlInp.H>
#include <TcxlMnu.H>
#include <TcxlSel.H>
#include <TcxlWin.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID GenerateWeather(NOARG);
VOID GetWorldLocation(NOARG);
VOID CTYP ResolveLatitude(NOARG);
VOID CTYP ResolveLatHemi(NOARG);
VOID CTYP ResolveLongitude(NOARG);
VOID CTYP ResolveLongHemi(NOARG);
VOID CTYP ResolveTerrainType(NOARG);
VOID DetermineWeather(NOARG);
VOID DisplayWeather(NOARG);

GBL IntT Roll_Dice(IntT sides, IntT times);

IntT WindChill[12][12] = {
	 {  33,  27,  21,  16,  12,   7,   1,  -6, -11, -15, -22, -28 },
	 {  21,  16,   9,   2,  -2,  -9, -15, -22, -27, -31, -37, -43 },
	 {  16,  11,   1,  -6, -11, -18, -25, -33, -40, -45, -51, -58 },
	 {  12,   3,  -4,  -9, -17, -24, -32, -40, -46, -52, -58, -64 },
	 {   7,   0,  -7, -15, -22, -29, -37, -45, -52, -58, -65, -72 },
	 {   5,  -2, -11, -18, -26, -33, -41, -49, -56, -63, -70, -78 },
	 {   3,  -4, -13, -20, -27, -35, -43, -52, -60, -67, -75, -82 },
	 {   1,  -4, -15, -22, -29, -36, -45, -54, -62, -69, -76, -83 },
	 {   1,  -6, -17, -24, -31, -38, -46, -55, -63, -70, -77, -84 },
	 {   0,  -7, -17, -24, -31, -38, -47, -56, -64, -71, -78, -85 },
	 {  -1,  -8, -19, -25, -33, -39, -48, -57, -65, -75, -79, -86 },
	 {  -3, -10, -21, -27, -34, -40, -49, -58, -66, -73, -80, -87 }
};

/*                  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16 */
ChrP MonthName[] = { "Taig", "Feud", "Lessa", "Abria", "Beren", "Kala",
	 "Septia", "Selig", "Issur", "Galia", "Alfa", "Daria", "Ciria", "Tychia",
    "Asyre", "Batim" };
IntT AvgTemp[] = { 32, 34, 37, 40, 44, 50, 61, 70, 77, 76, 70, 65, 56, 49, 41, 34 };
IntT HighAdj[] = { 10,  6,  6,  8,  8, 10, 10,  8,  6,  4,  8,  8, 10, 10,  8,  8 };
IntT HighMod[] = {  1,  4,  5,  4,  6,  6,  6,  8,  4,  6,  4,  6,  5,  6,  4,  5 };
IntT LowAdj[]  = { 20, 10, 10, 10,  8,  8, 10,  6,  6,  6,  8,  8, 10, 10, 10, 20 };
IntT LowMod[]  = {  1,  4,  4,  2,  4,  6,  6,  6,  6,  6,  4,  6,  4,  5,  4,  1 };
IntT SunRiseH[] = {  7,  7,  6,  5,  5,  4,  4,  4,  4,  5,  6,  6,  7,  7,  7,  7 };
IntT SunRiseM[] = { 21,  0, 30, 58, 32, 55, 32, 32, 55, 35, 10, 42, 11, 26, 37, 41 };
IntT SunSetH[]  = {  5,  5,  6,  6,  7,  7,  7,  7,  7,  7,  6,  6,  5,  5,  4,  4 };
IntT SunSetM[]  = {  1, 31,  3, 36,  4, 20, 32, 32, 22,  6, 36,  4, 35,  9, 49, 52 };
IntT ClearSky[]   = { 24, 26, 28, 26, 21, 21, 21, 21, 23, 26, 28, 34, 36, 29, 21, 26 };
IntT CloudySky[]  = { 50, 50, 54, 50, 55, 53, 57, 60, 62, 60, 56, 54, 60, 55, 50, 50 };
IntT NumberDays[] = { 34, 32, 32, 34, 32, 32, 31, 33, 31, 33, 32, 32, 34, 32, 33, 33 };
IntT AvgRain[]    = { 46, 41, 39, 43, 42, 43, 41, 36, 33, 33, 33, 34, 37, 40, 42, 44 };

ChrP TerrainName[] = { "Windstorm", "Earthquake", "Quicksand", "Earthquake", 
    "Volcano", "Rain Forest Downpour", "Quicksand", "Earthquake", "Quicksand",
    "Sunshower", "Earthquake", "Flashflood", "Duststorm", "Tornado", 
    "Earthquake", "Tornado", "Earthquake", "Flashflood", "Sandstorm", "Oasis",
    "Mirage Oasis", "Earthquake", "Windstorm", "Rock Avalanche", 
    "Snow Avalanche", "Volcano", "Earthquake", "Earthquake", "Tsunami",
    "Undersea Volcano","Tsunami","Undersea Volcano","Undersea Earthquake"};
IntT TerrainRoll[] = { 80, 100,  80, 100,   5,  60,  80, 100,  25,  80, 100, 
    40,  75,  85, 100,  50, 100,  85,  50,  65,  85, 100,  80,  50,  75,  80,
    100, 80,  94, 100,  20,  40, 100 };
IntT Weather[] = {   2,  3,  7,  3,  5,  9,  7,  3,  7, 10,  3,  8,  1, 11,  3,
    11,  3,  8,  1, 12, 12,  3,  2,  4,  4,  5,  3,  3,  6,  5,  6,  5,  3 };

ChrP TerrainType[] = {
    "Rough Terrain or Hills", 
    "Forest", 
    "Jungle", 
    "Swamp or Marsh", 
    "Dust-Day", 
    "Dust-Night", 
    "Plains", 
    "Desert-Day", 
    "Desert-Night", 
    "Mountains", 
    "Seacoast-Within 28 Miles of Coastline-Cold Current", 
    "Seacoast-Within 28 Miles of Coastline-Warm Current", 
    "Sea-More than 28 Miles from Coast-Cold Current", 
    "Sea-More than 28 Miles from Coast-Warm Current"
};
IntT PrecipAdj[] = {  0,   0,  10,   5, -25, -25,   0, -30, -30,   0,   5,   5,  15,  15 };
IntT TempAdj[]   = {  0,  -5,   5,   5,  10, -10,   0,  10, -10,  -3,  -5,   5, -10,  10 };
IntT WindAdj[]   = {  5,  -5, -10,  -5,   0,   0,   5,   5,   5,   5,   5,   5,   0,   0 };
IntT StartRoll[] = {  1,   3,   5,   9,  12,  12,  16,  18,  18,  23,  28,  28,  31,  31 };
IntT EndRoll[]   = {  2,   4,   8,  11,  15,  15,  17,  22,  22,  27,  30,  30,  33,  33 };

IntT PrecDie[]  = {  2,   5,  10,  20,  25,  27,  30,  38,  40,  45,  60,  70,
    84,  89,  94,  97,  99, 100 };
ChrP PrecType[] = { "Heavy Blizzard", "Blizzard", "Heavy Snowstorm", 
    "Light Snowstorm", "Sleet Storm", "Hailstorm", "Heavy Fog", "Light Fog", 
    "Mist", "Drizzle", "Light Rainstorm", "Heavy Rainstorm", "Thunderstorm", 
    "Tropical Storm", "Monsoon", "Gale", "Hurricane or Typhoon", "Special" };
IntT MinTemp[]  = { -200, -200, -200, -200, -200, -200,   20,   30,   30,   25,
    25,   25,   30,   40,   55,   40,   55,    0 };
IntT MaxTemp[]  = { 10,  20,  25,  35,  35,  65,  60,  70, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500 };
IntT Continue[] = { 5, 10, 20, 25, 20, 10, 25, 30, 15, 20, 45, 30, 15, 20, 30,
    15, 20,  1 };
IntT Rainbow[]  = { 0,  0,  0,  1,  0,  0,  1,  3, 10,  5, 15, 20, 20, 10,  5,
    10,  5,  0 };
IntT Shutdown[] = { 1, 1, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 3, 4, 1, 1, 2 };

/*     FOOT    HORSE   CART    VISION    INFRA      TRACKING    LOST   LOST */
ChrP WeatherInfo[29][8] = {
    { "x1/8", "x1/4", "None",  "2' Rad", "None",        "None", "50%", "50" },
    { "x1/4", "x1/4", "x1/4", "10' Rad", "x1/2",         "40%", "35%", "35" },
    { "x1/2", "x1/2", "x1/2",    "x1/2", "x1/2",        "-25%", "20%", "20" },
    { "x3/4",  "Std",  "Std",    "x3/4", "x3/4",        "-10%", "10%", "10" },
    { "x3/4", "x1/2", "x1/2",    "x3/4", "x3/4",        "-10%",  "5%",  "5" },
    { "x3/4", "x3/4", "x3/4",     "Std",  "Std",        "-10%", "10%", "10" },
    { "x1/4", "x1/4", "x1/4",  "2' Rad", "x1/2",        "-60%", "50%", "50" },
    { "x1/2", "x1/2", "x1/2",    "x1/4", "x3/4",        "-30%", "30%", "30" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",         "-5%", "Std",  "0" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",  "-1% Pt Cum", "Std",  "0" },
    {  "Std",  "Std",  "Std",     "Std",  "Std", "-10% Pt Cum", "Std",  "0" },
    { "x3/4",  "Std", "x3/4",    "x3/4", "x3/4", "-10% Pt Cum", "10%", "10" },
    { "x1/2", "x1/2", "x1/2",    "x3/4", "x3/4", "-10% Pt Cum", "10%", "10" },
    { "x1/4", "x1/4", "None",    "x1/2", "x1/2",        "None", "30%", "30" },
    { "x1/4", "x1/4", "None",    "x1/4", "x1/4",        "None", "30%", "30" },
    { "x1/4", "x1/4", "None",    "x1/4", "x1/4",        "None", "20%", "20" },
    { "x1/4", "x1/4", "None",    "x1/4", "x1/4",        "None", "30%", "30" },
    { "None", "None", "None",      "No",   "No",          "No", "80%", "80" },
    { "x1/2", "x1/2", "x1/2",    "x1/2", "x3/4",          "No", "30%", "30" },
    { "x1/4", "x1/4",   "No",     "Std",  "Std",        "-50%", "10%", "10" },
    { "Blkd", "Blkd", "Blkd",     "Std",  "Std",        "-60%", "10%", "10" },
    { "x1/2", "x1/2", "x1/2",    "x1/2", "x1/2",        "-50%", "20%", "20" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",          "No", "Std",  "0" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",          "No", "Std",  "0" },
    { "x3/4", "x3/4", "x3/4",     "Std",  "Std",      "-5% Pt", "10%", "10" },
    { "x1/2", "x1/2",   "No",    "x3/4", "x3/4",      "-5% Pt", "20%", "20" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",         "Std", "Std",  "0" },
    {   "No",   "No",   "No",    "x3/4", "x3/4",          "No", "40%", "40" },
    {  "Std",  "Std",  "Std",     "Std",  "Std",         "Std", "Std",  "0" }
};

GBL AtrT cAlt[4];

WthP CDC _WthCtrl;

WndT WorldWind;
ChrT HoldWorldLoc[4][65];
ChrP LatHemisphere[] = { "North", "South", NULL };
ChrP LongHemisphere[] = { "East", "West", NULL };
ChrP CloudType[] = { "Clear", "Partly Cloudy", "Cloudy" };
ChrT SunRise[6];
ChrT SunSet[6];

VOID GenerateWeather(NOARG)
{
    TctlWth = _WthCtrl;
    WthLati = 40;
    WthHemi = 1;
    WthLong = 80;
    WthLine = 1;
    WthType = 0;
    WthWind = 0;
    WthCast = 1;
    GetWorldLocation();
    DetermineWeather();
    DisplayWeather();
}

VOID GetWorldLocation(NOARG)
{
    WorldWind = Wopen( 6, 5, 12, 72, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
        Fix_Shadow(WorldWind);
        Wtitle(" World Location ", TTL_LFT, cAlt[TCDM_WINDOW]);
        sprintf(HoldWorldLoc[0], "Latitude: %d%c  ",  WthLati, 0xF8);
        sprintf(HoldWorldLoc[1], "Hemisphere: %s",    LatHemisphere[WthHemi]);
        sprintf(HoldWorldLoc[2], "Longitude: %d%c  ", WthLong, 0xF8);
        sprintf(HoldWorldLoc[3], "Hemisphere: %s",    LongHemisphere[WthLine]);
        sprintf(HoldWorldLoc[4], "Terrain Type: %s",  TerrainType[WthType]);
        MnuAct(5);
            MnuItm(0, 1, HoldWorldLoc[0], 'L', 1, ITM_NOR, ResolveLatitude,    0, HLP_LATITUDE);
            MnuItm(1, 1, HoldWorldLoc[1], 'H', 2, ITM_NOR, ResolveLatHemi,     0, HLP_LATHEMI);
            MnuItm(2, 1, HoldWorldLoc[2], 'g', 3, ITM_NOR, ResolveLongitude,   0, HLP_LONGITUDE);
            MnuItm(3, 1, HoldWorldLoc[3], 's', 4, ITM_NOR, ResolveLongHemi,    0, HLP_LONGHEMI);
            MnuItm(4, 1, HoldWorldLoc[4], 'T', 5, ITM_NOR, ResolveTerrainType, 0, HLP_TERRAINTYPE);
        MnuEnd(1, MNU_VER|MNU_OMN, 65, 0, cAlt[TCDM_WINDOW], cAlt[TCDM_QUICK], cAlt[TCDM_DESELECT], cAlt[TCDM_BARINPUT]);
        MnuGet();
    WVclose(WorldWind);
    HlpSet(HLP_MAIN);
}

VOID CTYP ResolveLatitude(NOARG)
{
    ChrT temp[5];

    sprintf(temp, "%d", WthLati);
    Wgotoxy(0, 1);
    VcurHid(1);
    if (KwGetFmt(temp, "'Latitude: '????'  '") == ERR_NUL) {
        WthLati = atoi(temp);
        sprintf(HoldWorldLoc[0], "Latitude: %d%c  ", WthLati, 0xF8);
    }
    VcurHid(0);
}

VOID CTYP ResolveLatHemi(NOARG)
{
    IntT k;

    Wprts(1, 1, cAlt[TCDM_WINDOW], "Hemisphere: ");
    k = SelTxt(1, 13, cAlt[TCDM_BARINPUT], LatHemisphere, WthHemi);
    if (k != ERR_ARG) {
        WthHemi = k;
        sprintf(HoldWorldLoc[1], "Hemisphere: %s",  LatHemisphere[WthHemi]);
    }
}

VOID CTYP ResolveLongitude(NOARG)
{
    ChrT temp[5];

    sprintf(temp, "%d", WthLong);
    Wgotoxy(2, 1);
    VcurHid(1);
    if (KwGetFmt(temp, "'Longitude: '????'  '") == ERR_NUL) {
        WthLong = atoi(temp);
        sprintf(HoldWorldLoc[2], "Longitude: %d%c  ", WthLong, 0xF8);
    }
    VcurHid(0);
}

VOID CTYP ResolveLongHemi(NOARG)
{
    IntT k;

    Wprts(3, 1, cAlt[TCDM_WINDOW], "Hemisphere: ");
    k = SelTxt(2, 13, cAlt[TCDM_BARINPUT], LongHemisphere, WthLine);
    if (k != ERR_ARG) {
        WthLine = k;
        sprintf(HoldWorldLoc[3], "Hemisphere: %s",  LongHemisphere[WthLine]);
    }
}

VOID CTYP ResolveTerrainType(NOARG)
{
    IntT k;

    Wprts(4, 1, cAlt[TCDM_WINDOW], "Terrain Type: ");
    k = SelTxt(4, 15, cAlt[TCDM_BARINPUT], TerrainType, WthType);
    if (k != ERR_ARG) {
        WthType = k;
        sprintf(HoldWorldLoc[4], "Terrain Type: %s", TerrainType[WthType]);
    }
}

VOID DetermineWeather(NOARG)
{
    IntT holding, j;

    WthHTmp = AvgTemp[TctlMon-1] + Roll_Dice(HighAdj[TctlMon-1], 1) + 1 + 
        Roll_Dice(HighMod[TctlMon-1], 1) + WthLati;
    WthLTmp = AvgTemp[TctlMon-1] - Roll_Dice( LowAdj[TctlMon-1], 1) + 1 + 
        Roll_Dice(LowMod[TctlMon-1], 1) + WthLati;
    holding = Roll_Dice(100, 1);
    WthCast = 1;
    if (holding < ClearSky[TctlMon-1])
        WthCast = 0;
    if (holding > CloudySky[TctlMon-1])
        WthCast = 2;
    WthHTmp += TempAdj[WthType];
    WthLTmp += TempAdj[WthType];
    WthRain = AvgRain[TctlMon-1] + PrecipAdj[WthType];
    holding = Roll_Dice(100, 1);
    if (holding > WthRain) {
        WthWind = Roll_Dice(20, 1) + WindAdj[WthType];
        if (WthWind < 0)
            WthWind = 0;
    }
    else {
        holding = Roll_Dice(100, 1);
        for (j = 0; j < 18; j++) {
            for (;;) {
                if (holding <= Continue[j]) {
						  switch (Shutdown[j]) {
								case 1 :
									 if (WthType == 7 || WthType == 8)
										  holding = Roll_Dice(100, 1);
									 break;

								case 2 :
									 if (WthType == 4 || WthType == 5 || WthType == 7)
										  holding = Roll_Dice(100, 1);
									 break;

                        case 3 : 
									 if (WthType == 6 || WthType == 7 || WthType == 8)
                                holding = Roll_Dice(100, 1);
									 break;
    
								case 4 :
                            if (WthType >  3 && WthType <  8)
										  holding = Roll_Dice(100, 1);
									 break;

								default :
									 holding = Roll_Dice(100, 1);
									 break;
						  }
					 }
					 if (holding > Continue[j])
						  break;
				}
		  }
		  if (WthHTmp < MaxTemp[j] && WthLTmp > MinTemp[j]) {
				WthWTyp = j;
				WthWCon = Continue[j];
				WthRBow = Rainbow[j];
		  }
		  else
				/* try random number again */;
        holding = Roll_Dice(100, 1);
        for (j = StartRoll[WthType]; j < EndRoll[WthType]; j++)
            if (holding < TerrainRoll[j]) {
                WthSTyp = j;
                WthSWth = j;
                break;
            }
    }
    WthMRis = SunRiseM[TctlMon-1] + WthLong;
    WthMSet = SunSetM[TctlMon-1] + WthLong;

    WthHRis = SunRiseH[TctlMon-1];
    WthHSet = SunSetH[TctlMon-1];

    while (WthMRis > 59) {
        WthMRis -= 60;
        WthHRis++;
        if (WthHRis > 12)  /* 1pm? Heh, talk about a late day. */
            WthHRis = 1;
    }

    while (WthMRis < 0) {
        WthMRis += 60;
        WthHRis--;
        if (WthHRis < 0)  /* 11pm? This should NEVER happen, but... */
            WthHRis = 11;
    }

    while (WthMSet > 59) {
        WthMSet -= 60;
        WthHSet++;
        if (WthHSet > 12)  /* 1am? */
            WthHSet = 1;
    }

    while (WthMSet < 0) {
        WthMSet += 60;
        WthHSet++;
          if (WthHSet < 0)  /* 11am? */
                WthHSet = 11;
	 }

}

VOID DisplayWeather(NOARG)
{

#ifdef CARL
IntT WthType = 0;
IntT WeatherType;
IntT WeatherCont;
IntT WeatherRBow;
IntT SpecialType;
IntT SpecialWeather;
#endif

	WndT ShowWind;

	ShowWind = Wopen( 6, 5, 14, 72, BOX_DBL, cAlt[TCDM_WINDOW], cAlt[TCDM_WINDOW]);
		Fix_Shadow(ShowWind);
		Wtitle(" Current Weather ", TTL_LFT, cAlt[TCDM_WINDOW]);
		sprintf(Message, "Current position is %d%c %s latitude, %d%c %s longitude",
          WthLati, 0xF8, LatHemisphere[WthHemi], WthLong, 0xF8, LongHemisphere[WthLine]);
		Wprts(0, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(SunRise, "%d:%02d", WthHRis, WthMRis);
        sprintf(SunSet, "%d:%02d", WthHSet, WthMSet);
		sprintf(Message, "Sunrise is at: %s, Sunset is at: %s", SunRise, SunSet);
		Wprts(1, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(Message, "It will be a %s day", CloudType[WthCast]);
		Wprts(2, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(Message, "Today's high will be: %d%c", WthHTmp, 0xF8);
		Wprts(3, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(Message, "Today's low will be: %d%c", WthLTmp, 0xF8);
		Wprts(4, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(Message, "Wind will be %d mph", WthWind);
		Wprts(5, 1, cAlt[TCDM_WINDOW], Message);
        sprintf(Message, "There will be %d inches of precipitation", WthRain);
		Wprts(6, 1, cAlt[TCDM_WINDOW], Message);
		KeyGetc();
	WVclose(ShowWind);
	HlpSet(HLP_MAIN);
}

VOID HeavyBlizzard(NOARG)
{
	 WthRain += Roll_Dice(100, 1) + 10;
    
	 WthWind += Roll_Dice(8, 6) + 40;
    
}

#ifdef CARL
1880 Rem
2080 Rem          GOTO SPECIAL WEATHER TYPE OR JUST WEATHER.
2090 If TYPE=0 then 2120
2100 If TYPE>=1 and TYPE<=18 then 
        On  TYPE gosub 2440,2540,2640,2720,2800,2870,2960,3010,3060,
                       3110,3160,3220,3360,3390,3480,3570,3670,2120
2110 Rem                  1    2    3    4    5    6    7    8    9  
                         10   11   12   13   14   15   16   17   18
2120 If WEATHER$="SPECIAL" then [
         TYPE=SPECIAL;
         If TYPE>0 and TYPE<13 then 
             On TYPE gosub 3760,3840,3930,3990,4060,4130,
                           4250,4320,4380,4440,4510,4580]
2130 Rem                      1    2    3    4    5    6
                              7    8    9   10   11   12
2140 If TEM1<35 or TEM2<35 then [
         WIND1=int(WIND/5);
         TEMP1=int(abs(TEM1-35)/5);
         TEMP2=int(abs(TEM2-35)/5);
         WIND_CHILL_FACTOR1=WINDCHILL(WIND1,TEMP1);
         WIND_CHILL_FACTOR2=WINDCHILL(WIND1,TEMP2)
     ]

2150 Rem                     * * * * * * * * * * * *
                       * * *   Short Weather Return  * * *
                             * * * * * * * * * * * *
    
2160 If DURATION$="" then 
         DURATION$=" H"
2170 If COMMAND$="W" then [
         COLOR 0,7;
         LOCATE 15,1;
         Print ' '*80,;
         COLOR 7,0;
         COMMAND$=""
     ]
2180 LOCATE 15,2;
     COLOR 0,7;
     Print "2:",trim$(str$(TEM1))," DAWN:",trim$(str$(TEM2))," ",
2190 LOCATE 15,17;
     Print "RISE:",RISE$(MONTH)," SET:",SET$(MONTH),
2200 LOCATE 15,37;
     Print "             ",;
     LOCATE 15,36;
     Print CLOUD$
2210 If WIND>29 then 
         THE_COLOR=16 
     else
         THE_COLOR=0
2220 LOCATE 15,52;
     Print "WIND:",;
     COLOR THE_COLOR,7;
     Print trim$(str$(WIND)),"  ",;
     COLOR 7,0
2230 COLOR 16,7
2240 LOCATE 15,63;
     Print ' '*15,;
     If WEATHER$<>"" then [
         LOCATE 15,63;
         Print WEATHER$,
     ]
2250 If WEATHER$<>"" then [
         LOCATE 15,61;
         Print "N",
     ] 
     else [
         LOCATE 15,61;
         Print " ",
     ]
2260 COLOR 7,0
2270 Goto 2420

2280 COLOR 0,7;
     LOCATE 15,1;
     Print ' '*80,
2290 LOCATE 15,2;
     Print "RAIN:",PRECIPIN$,"  LASTS:",trim$(str$(DURATION)),DURATION$,
2300 Print "  F:",WEATHER_INFORMATION$(TYPE,1)," H:",WEATHER_INFORMATION$(TYPE,2)," C:",WEATHER_INFORMATION$(TYPE,3)
2310 Print "  VIS:",WEATHER_INFORMATION$(TYPE$,4)
2320 Print "  U/I VIS:",WEATHER_INFORMATION$(TYPE,5)
2330 COLOR 7,0
2340 Goto 2420

2350 COLOR 0,7
2360 LOCATE 15,1;
     Print ' '*80,
2370 LOCATE 15,2;
     Print "TRACKING:",WEATHER_INFORMATION$(TYPE,6),
2380 Print "  GETTING LOST:",WEATHER_INFORMATION$(TYPE,7),
2390 If WIND_CHILL_FACTOR1<35 then 
         Print "  LOW WINDCHILL:",WIND_CHILL_FACTOR1,
2400 If WIND_CHILL_FACTOR<35 then 
         Print "  HIGH WINDCHILL:",WIND_CHILL_FACTOR2,
2410 COLOR 7,0
2420 Goto 20310

#endif
