/* []---------------------------------------------------------------------[] */
/* |            AClass.c: Modify the character's Armor Class.              | */
/* |                                                                       | */
/* |              The AClass.c source code and concepts are                | */
/* |    Copyright (C) 1979-1997 by Carl Schelin, All Rights Reserved.      | */
/* |                                                                       | */
/* []---------------------------------------------------------------------[] */

#define __ARMORCLASS__

#include <TcxlDef.H>

#pragma hdrstop
#include "..\Include\Tcdm.H"

VOID Adjust_Armor_Class(NOARG);

GBL dexterity[];                          /*  Dexterity Table             */


/*    -1    0    1    2    3    4    5    6    7    8    9   10                            */
IntT Armor_Points[14][13] = {
	{ 999, 825, 705, 580, 480, 370, 320, 280, 200, 135,  80,  00 }, /*0 Full Field Plate   */
	{ 999, 999, 660, 515, 465, 380, 305, 240, 180, 115,  65,  00 }, /*1 Field Plate Armor  */
	{ 999, 999, 999, 470, 400, 330, 275, 220, 165, 110,  55,  00 }, /*2 Plate Armor        */
	{ 999, 999, 999, 999, 400, 330, 260, 208, 156, 104,  52,  00 }, /*3 Banded Armor       */
	{ 999, 999, 999, 999, 365, 300, 235, 188, 141,  94,  47,  00 }, /*4 Splinted Armor     */
	{ 999, 999, 999, 999, 999, 325, 265, 200, 145,  95,  52,  00 }, /*5 Bronze Plate       */
	{ 999, 999, 999, 999, 999, 999, 390, 321, 240, 170,  90,  00 }, /*6 Elfin Chain Mail   */
	{ 999, 999, 999, 999, 999, 372, 300, 228, 171, 114,  57,  00 }, /*7 Chain Mail         */
	{ 999, 999, 999, 999, 999, 999, 323, 250, 177, 118,  59,  00 }, /*8 Scale Mail         */
	{ 999, 999, 999, 999, 999, 999, 999, 280, 200, 120,  60,  00 }, /*9 Ring Mail          */
	{ 999, 999, 999, 999, 999, 999, 999, 140, 100,  60,  30,  00 }, /*0 Studded Leather    */
	{ 999, 999, 999, 999, 999, 999, 999, 999, 999,  50,  20,  00 }, /*1 Padded Armor       */
	{ 999, 999, 999, 999, 999, 999, 999, 999, 999,  60,  25,  00 }, /*2 Leather Armor      */
	{ 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999,  00 }  /*3 No Armor           */
};

IntT Armor_Max[14] = {705, 515, 400, 330, 300, 325, 390, 300, 250, 200, 100,
	50, 60,  0};

/*     0    1                          */
IntT Shield_Points[7][2] = {
	{   0,  60},  /*0 Kite Shield      */
	{   0,  40},  /*1 Metal Shield     */
	{   0,  25},  /*2 Reinforced Wood  */
	{   0,  15},  /*3 Wooden Shield    */
	{   0,   5},  /*4 Flora Shield     */
	{   0,   5},  /*5 Fauna Shield     */
	{   0,   0}   /*6 No Shield        */
};
    
/*    0    1                           */
IntT Helm_Points[7][2] = {
	{  0,  10},  /*0 Great Helm   */
	{  0,   9},  /*1 Nasal Helm   */
	{  0,   6},  /*2 Metal Helm   */
	{  0,   4},  /*3 Mail Coif    */
	{  0,   4},  /*4 Metal Cap    */
	{  0,   2},  /*5 Leather Cap  */
	{  0,   0}   /*6 No Helm      */
};

/*GBL IntT Armor_Points[14][13]
GBL IntT Shield_Points[7][2]
GBL IntT Helm_Points[7][2]*/

/**[ Adjust Armor Class ]******************************************

	Input: None
	Returns: None
	Description: Take the character's armor/shield/helm points and calculate
		his/her armor class by using the armor tables.
	Pseudocode:
		loop through main armor table
			search for a match to armor type and number of points
			make the loop position the ac
			break loop
		if user has shield, subtract one from the ac
		subtract adjustments
		subtract dexterity bonus (if any)
 ******************************************************************/



VOID Adjust_Armor_Class(NOARG)
{
	IntT j;

	for (j = 11; j >= 0; j--)
		if ((cData[CHARNUM].APoints - cData[CHARNUM].APtDown) <= 
			Armor_Points[cData[CHARNUM].AType][j]) {
			cData[CHARNUM].AClass = j - 1;
			break;
		}

	if ((cData[CHARNUM].SPoints - cData[CHARNUM].SPtDown) > 0)
		cData[CHARNUM].AClass--;

	cData[CHARNUM].AClass -= cData[CHARNUM].ACAdj;

	cData[CHARNUM].AClass += dexterity[StaDex(CHARNUM) - 1];
}

