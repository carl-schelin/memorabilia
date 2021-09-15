
#define VERSION "v2.0.10"

#define LOCAL         0          /*  local drive                       */
#define LOCAL40       1          /*  local drive but dos 4.x           */
#define LOCAL50       2          /*  local drive but dos 5.x           */
#define SCSI50        3          /*  local scsi on dos 5.x             */
#define ESDI50        4          /*  local esdi on dos 5.x             */
#define DUBLDISK      5          /*  double disk v2.6 on 5.x           */
#define ONTRACK       6          /*  ontrack disk manager on 5.x       */
#define BERNOULLI     7          /*  bernoulli box                     */
#define SYQUEST40     8          /*  syquest 44m external on 4.x       */
#define SYQUEST50     9          /*  syquest 44m external on 5.x       */
#define EXTERN       10          /*  external device                   */
#define BRIDGE       11          /*  bridge external floppy            */
#define BRIDGE40     12          /*  bridge external floppy 4.x        */
#define IOMEGAZIP    13          /*  Iomega Zip Drive on Windows 95    */
#define BANYAN       14          /*  banyan vines. external device too */
#define LANMAN33     15          /*  Lan Manager on dos 3.3            */
#define LANMAN50     16          /*  lanmgr on dos5.x                  */
#define LANMAN621    17          /*  lanmgr on dos6.x                  */
#define LANMAN       18          /*  LAN Manager and 3+Share           */
#define SHARE16      19          /*  3+Share v1.6 and 3.31 Dos         */
#define PCLAN        20          /*  IBM PC LAN network drive          */
#define PCNFS        21          /*  PC NFS LAN software               */
#define PATHWORKS    22          /*  Dec LAN software                  */
#define NOINIT       23          /*  uninitialized drive               */
#define DECINIT      24          /*  initialized dec drive             */
#define SUBST        25          /*  substituted drive                 */
#define SUBST40      26          /*  4.x substituted drive             */
#define SUBST50      27          /*  5.0 substituted drive             */
#define SUBSTSCSI50  28          /*  Subst for SCSI/5.0                */
#define SUBSTVDISK   29          /*  Subst virtual disk                */
#define SUBSTADJRAM  30          /*  Subst Adjram virtual disk         */
#define SUBSTQCKMEM  31          /*  Subst Intel QuickMem              */
#define SUBSTXPDSK   32          /*  Subst pcmag xpandisk              */
#define SUBSTSYQ50   33          /*  Subst syquest on 5.0              */
#define SUBSTDDISK   34          /*  Subst double disk v2.6 on 5.0     */
#define SUBSTBERN    35          /*  Subst bernoulli                   */
#define SUBSTVGADSK  36          /*  Subst VGADisk                     */
#define SUBSTVDD     37          /*  Subst vdiskdd.sys                 */
#define SUBSTESDI50  38          /*  Subst ESDI on 5.x                 */
#define VDISK        39          /*  virtual disk (lesdisk?)           */
#define QUICKMEM     40          /*  intel quickmem ram disk           */
#define XPANDISK     41          /*  pc magazines xpandisk             */
#define VGADISK      42          /*  tommy frandsen's vgadisk          */
#define ADJRAM       43          /*  david lee's membrain or gary cramblitt's adjram or ramdrv  */
#define VDSKDD       44          /*  john white's ram.sys or vladimir lanin's vdiskdd    */
#define UNKNOWN      45          /*  unknown but prints new code       */

#define LOCDRIVE   0x00
#define NETDRIVE   0x01

#define DTEXT       6          /*  offset in switchinfo for checking data  */
#define FLOPPY     (DTEXT + 2)
#define GRAPHIC    (DTEXT + 4)
#define INFO       (DTEXT + 6)
#define NOHEX      (DTEXT + 8)
#define RESPOND    (DTEXT + 10)

char *driveinfo[] = {
    " Dos 3.x Local Drive", 
    " Dos 4.x Local Drive", 
    " Dos 5.x or Greater Local Drive", 
    " Dos 5.x SCSI Drive", 
    " Dos 5.x ESDI Drive", 
    " Dos 5.x Local Drive (Double Disk)", 
    " Dos 5.x OnTrack Disk Manager", 
    "rRemovable Drive (Bernoulli)", 
    "rRemovable Drive (Syquest 4.x Dos)", 
    "rRemovable Drive (Syquest 5.x Dos)", 
    "rRemovable Drive (3.5\")", 
    "rRemovable Drive (Bridge 5.25\")", 
    "rRemovable Drive (Bridge 5.25\" on 4.x)", 
    "rRemovable Drive (Iomega Zip on Win95)",
    "nNetwork Drive (Banyan)", 
    "nNetwork Drive (LAN Mgr 3.3 Dos)",
    "nNetwork Drive (LAN Mgr 5.x Dos)",
    "nNetwork Drive (LAN Mgr 6.x Dos)",
    "nNetwork Drive (LAN Mgr/3+Share/Token Ring)", 
    "nNetwork Drive (3+Share - 3.31 Dos)", 
    "nNetwork Drive (IBM PC LAN)", 
    "nNetwork Drive (Sun PC NFS)", 
    "nNetwork Drive (DEC PathWorks)", 
    "nNetwork Drive (Unitialized DEC?)",
    "nNetwork Drive (DEC PathWorks)",
    "sDos 3.x SUBSTituted Drive", 
    "sDos 4.x SUBSTituted Drive", 
    "sDos 5.x or Greater SUBSTituted Drive", 
    "sDos 5.x SUBSTituted Drive (SCSI Base)", 
    "sDos 3.x SUBST Virtual Ram Disk (VDisk)", 
    "sDos 3.x SUBST Virtual Ram Disk (MemBrain)", 
    "sDos 3.x SUBST Virtual Ram Disk (QuickMem)", 
    "sDos 3.x SUBST Virtual Ram Disk (XpanDisk)", 
    "sDos 5.x SUBST Removable Drive (Syquest)", 
    "sDos 5.x SUBST Expanded Disk (Double Disk)",
    "sDos 3.x SUBST Removable Drive (Bernoulli)",
    "sDos 3.x SUBST Virtual Ram Disk (VGADisk)", 
    "sDos 3.x SUBST Virtual Ram Disk (VDiskDD)", 
    "sDos 5.x SUBST ESDI Drive", 
    "vVirtual Ram Disk (VDisk/RamDrive/LesDisk)", 
    "vVirtual Ram Disk (Intel Quickmem)", 
    "vVirtual Ram Disk (XpanDisk.Sys)", 
    "vVirtual Ram Disk (VGADisk.Sys)", 
    "vVirtual Ram Disk (MemBrain/AMDisk/RamDrv)", 
    "vVirtual Ram Disk (Lanin/White Ram/VDiskDD)", 
    "?Unknown code. Forward to Carl"
};
/* maximum length of text goes no farther than --->| */

char *switchinfo = "[JAEL]-d-f-g-i-r-n";

int getpath(int);
void interrupt myhandler();
void modify_free(void);

#ifdef GRAPHICS
void initialization(void);
void graphic_setup(void);
void init_screen(void);
void print_graph(int which, int drivetype, int total, int avail);
#endif

