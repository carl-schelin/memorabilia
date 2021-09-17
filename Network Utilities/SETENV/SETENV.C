#include <dos.h>
#include <alloc.h>
#include <d3l.h>
#include <string.h>

/*
 *   Mstr_FindEnvironment:
 *     Scans for the "Master" Environment area, and returns
 *     a pointer to it, and the size of the environment.
*/
void Mstr_FindEnvironment ( char far **Env , unsigned *EnvSize )
{
   unsigned int far *CommandSeg, far *TempSeg ;
   char far *BlockSeg ;

   /*
    *  Scan through PSP's looking for a block that is its own father.
    *  This block is the PSP of COMMAND.COM
   */
  TempSeg = MK_FP ( _psp , 0 ) ;
   do
   {
     CommandSeg = TempSeg ;
     TempSeg = MK_FP ( *(TempSeg+8) , 0 ) ;
   }
   while ( TempSeg != CommandSeg ) ;

   /*
    *  Scan forward through memory looking for the correct MSB.
    *  This will have COMMAND.COM's PSP as owner, and begin with
    *  the character M
   */
   BlockSeg = (char far *)CommandSeg ;
   do
   {
    BlockSeg = MK_FP ( FP_SEG(BlockSeg)+1 , 0 ) ;
   }
   while ( ( *(unsigned int far *)(BlockSeg+1) != FP_SEG ( CommandSeg ) ) ||
           ( *BlockSeg != 'M' ) ) ;

   /*
    *  The environment is the NEXT segment of memory
    *  and bytes 4 and 5 are the size in paragraphs
   */
   *Env = MK_FP ( FP_SEG(BlockSeg)+1 , 0 ) ;
   *EnvSize = 16 * *(unsigned int far *)(BlockSeg+3) ;
}

/*
 *   Mstr_getenv:
 *     Scans the "Master" Environment for a given "sub string"
 *     and returns a pointer to it.
 *     Similar to Turbo routine "getenv" but uses the Master copy of the
 *     environment table.
*/
char far *Mstr_getenv (char far *Env , char far *name)
{
   char far *Sub_Env, far *str1, far *str2 ;

   /*
    *  Start at the beginning of the environment
   */
   Sub_Env = Env ;

   /*
    *  While the "sub string" we're looking at is non-zero
   */
   for ( ; *Sub_Env ; )
   {
     /*
      *  Simulate a "strcmp" on the "sub string" of the environment
      *  and the string we're looking for
     */
     for ( str1 = Sub_Env , str2 = name ;
           (*str1) && (*str2) && ( *str1 == *str2) ;
           str1++ , str2++ ) ;
     /*
      *  If we reached the end of the string we're looking for
      *  we've found the correct portion of the environment.
      *  Return the ptr to the start of this "sub string"
     */
     if ( !*str2 )
       return ( Sub_Env ) ;

     /*
      *  Otherwise, advance to the next "sub string" in the environment
      *  by performing a "strchr" function
     */
     for ( ; *(Sub_Env++) ; ) ;
   }

   /*
    *  Obviously, the string is not present in the environment.
    *  Return this fact.
   */
  return ( NULL ) ;
}

/*
 *   Mstr_delenv:
 *     Scans the "Master" Environment for a given "sub string"
 *     and removes it.
*/
int Mstr_delenv (char far *Env , unsigned EnvSize , char far *name)
{
   char far *Sub_Env , far *New_Env ;
   char huge *Dest , far *Src , huge *End_Env ;

   int Done  ;
   unsigned Ctr ;

   /*
    *  Allocate a chunk of storage to act as a "working" copy of
    *  the Environment table
   */
   New_Env = farmalloc ( EnvSize ) ;

   /*
    *  Copy the data from the Master to Working copy of the
    *  Environment table.
    *  Simulates a "memcpy" function.
   */
   for ( Src = Env , Dest = (char far *)New_Env , Ctr = 0 ;
         Ctr < EnvSize ;
         *(Dest++) = *(Src++) , Ctr++ ) ;

   /*
    *  Scan the working copy of the environment for the desired
    *  sub string
   */
   Sub_Env = Mstr_getenv ( New_Env , name ) ;

   if ( Sub_Env == NULL )
   {
     /*
      *  If not found, do nothing
     */
     Done = -1 ;
   } else {
     /*
      *  Locate the end of the string to delete
      *  Simulate a "strchr" call
     */
     for ( Src = Sub_Env ; *(Src++) ; ) ;

     /*
      *  Move the rest of the environment back over the "sub string"
      *  being deleted.
      *  Simulated "memcpy" function.
      *  Huge pointers used for pointer comparison purposes.
     */
     for ( Dest = (char huge *)Sub_Env , End_Env = (char huge *) (New_Env + EnvSize ) ;
         ( Dest < End_Env ) ;
         *(Dest++) = *(Src++) ) ;

     /*
      *  Copy the data from the Working to Master copy of the
      *  Environment table.
      *  Simulates a "memcpy" function.
     */
     for ( Src = New_Env , Dest = (char huge *)Env , Ctr = 0 ;
         Ctr < EnvSize ;
         *(Dest++) = *(Src++) , Ctr++ ) ;

     /*
      *  Signal all done
     */
     Done = 0 ;
   }

   /*
    *  Free all working storage
   */
   farfree ( New_Env ) ;

   return ( Done ) ;
}

/*
 *   Mstr_putenv:
 *     Adds/Replaces a given "sub string" in the Master Environment.
 *     Similar to Turbo routine "putenv" but uses the Master copy of the
 *     environment table.
*/
int Mstr_putenv (char far *Env , unsigned EnvSize , char far *name )
{
   char far *Sub_Env , far *Temp_Name ;
   char huge *Dest , far *Src , huge *End_Env ;
   int Done ;

   /*
    *  Allocate a chunk of storage to create the Variable name to add
    *  to the Environment table
   */
   Temp_Name = farmalloc ( 256 ) ;

   /*
    *  Extract only the Name portion of the data to add to the Environment
   */
   for ( Src = name , Dest = Temp_Name ;
         *Src && ( *Src != '=' ) ;
        *(Dest++) = *(Src++) ) ;

   /*
    *  Ensure that the resulting name is well formed.
   */
   *(Dest++) = '=' ;
   *Dest = 0 ;

   /*
    *  Delete this sub string if found in the environment
   */
   Mstr_delenv ( Env , EnvSize , Temp_Name ) ;

   /*
    *  Locate the END of the Master table by locating a zero length
    *  String in it
   */
   Sub_Env = Env ;
   for ( ; *Sub_Env ; )
   {
     for ( ; *(Sub_Env++) ; ) ;
   }

   /*
    *  Add the new string to the END of the existing environment, with
    *  trincation IF needed
   */
   for ( Dest = (char huge *)(Sub_Env) , Src = name , End_Env = (char huge *) (Env + EnvSize ) ;
         ( Dest < End_Env ) && (*Src) ;
         *(Dest++) = *(Src++) ) ;

   Done = -1 ;
   if ( !*Src )
   {
     /*
      *  If the string to add was FULLY added, ensure that the
      *  newly updated environment is properly finished
     */
     Done = 0 ;
     *(Dest++) = 0 ;
     *Dest = 0 ;
   }

   /*
    *  As a real safety measure, ensure that the FINAL two bytes of the
    *  Environment are both 0. This will finish the last string AND
    *  ensure that a zero length string is also present
   */
   *(End_Env-1) = 0 ;
  *(End_Env-2) = 0 ;

   /*
    *  Free all working storage
   */
   farfree ( Temp_Name ) ;

   return ( Done ) ;
}

void main(int argc, char *argv[])
{
    char far *Env;
    unsigned EnvSize;
    char tempdata[128] = {""};
    char tmpstring[128];

    if (argc > 2) {
        argv[1]=strupr(argv[1]);
        argv[2]=strupr(argv[2]);
        strcpy(tmpstring, argv[2]);
        strcat(tmpstring, "=");
        Mstr_FindEnvironment(&Env, &EnvSize);
        if (strcmp(argv[1], "NAME") == 0)
            D3LGetLoginName(tempdata);
        if (strcmp(argv[1], "ADDR") == 0)
            D3LGetEthAddr(tempdata);
        strcat(tmpstring, tempdata);
        Mstr_putenv(Env, EnvSize, tmpstring);
    }
    else {
        printf("ERROR: Insufficient parameters!\n");
        printf("SetEnv [NAME | ADDR] Environment_Name\n");
        exit(1);
    }
}
