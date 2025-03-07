#ifndef BUFFERS_H
#define BUFFERS_H

#include <PR/ultratypes.h>
#include <hvqm2dec.h>

#include "game/save_file.h"
#include "game/game_init.h"
#include "config.h"

#define THREAD1_STACK 0x100
#define THREAD2_STACK 0x800
#define THREAD3_STACK 0x200
#define THREAD4_STACK 0x2000
#define THREAD5_STACK 0x2000
#define THREAD6_STACK 0x400

extern u8 gDecompressionHeap[];

extern u8 gAudioHeap[];

extern u8 gIdleThreadStack[THREAD1_STACK];
extern u8 gThread3Stack[THREAD3_STACK];
extern u8 gThread4Stack[THREAD4_STACK];
extern u8 gThread5Stack[THREAD5_STACK];
#if ENABLE_RUMBLE
extern u8 gThread6Stack[THREAD6_STACK];
#endif

extern u8 gGfxSPTaskYieldBuffer[];

extern struct SaveBuffer gSaveBuffer;

extern u8 gGfxSPTaskStack[];

extern struct GfxPool gGfxPools[2];

extern u8 adpcmbuf[];		/* Buffer for audio records ADPCM) */

extern u64 hvq_yieldbuf[];	/* RSP task yield buffer */
extern HVQM2Info hvq_spfifo[];	/* Data area for HVQM2 microcode */
extern u16 hvqwork[];		/* Work buffer for HVQM2 decoder */
extern u8 hvqbuf[];		/* Buffer for video records (HVQM2) */
extern u8 gSkyboxBuffer[];

#endif // BUFFERS_H
