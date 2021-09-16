/*  tcmou.h - header for Turbo C mouse routines
 *
 *  Richard Hale Shaw
 */
#ifndef TRUE
#define FALSE 0
#define TRUE  !FALSE
#endif

#define MouClose     MouOpen
#define LeftMouButton(val)    (val & 0x01)
#define RightMouButton(val)   (val & 0x02)
#define CenterMouButton(val)  (val & 0x03)
#define LRMouButtons(val)     (LeftMouButton(val) && RightMouButton(val))

#define MouCharPos(n)    (n / 8)
#define MouVPos(n)       (n * 8)

extern Mouse;
extern unsigned MouNumButtons(void);
extern unsigned MouOpen(void);
extern void MouDrawPtr(void);
extern void MouRemovePtr(void);
extern void MouReadEventInfo(unsigned *row, unsigned *col, unsigned *buttons);
extern void MouSetPtrPos(unsigned row, unsigned col);
extern void MouCharIn(unsigned *row, unsigned *col, unsigned *buttons);
extern void MouPtr(int pointer);
