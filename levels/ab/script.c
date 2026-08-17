#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"


/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/ab/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ab_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _ab_segment_7SegmentRomStart, _ab_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_5), 
	JUMP_LINK(script_func_global_14), 
	LOAD_MODEL_FROM_GEO(MODEL_AB_LAVAWALL, ab_lavawall), 
	LOAD_MODEL_FROM_GEO(MODEL_AB_SAND, ab_sand), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ab_area_1),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x31, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 1, 0x41, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0, 0x02, 0, 0, 0),
		WARP_NODE(0x0B, LEVEL_AB, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_AB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x10, LEVEL_AB, 0x01, 0x11, WARP_NO_CHECKPOINT),
		WARP_NODE(0x11, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, -2, 8839, -127, -8800),
		OBJECT(MODEL_CLAM_SHELL, 9608, -79, -9010, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 12304, -19, -10573, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 11798, -79, -7375, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 12859, 182, -13236, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 11132, 944, -12919, 0, -97, 0, 0x00000000, bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 10650, 1164, -13296, 0, 85, 0, 0x00000000, bhvClamShell),
		OBJECT(MODEL_NONE, 11260, -192, -9001, 0, -2, 0, 0x00000000, bhvAbClamCtl),
		OBJECT(MODEL_CLAM_SHELL, 12486, 175, -13813, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 10194, -79, -10241, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 10392, -79, -7625, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 12812, -76, -8900, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13132, 174, -11962, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13125, 190, -12627, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_BLUE_COIN, -7545, -43, -3134, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -8519, 123, -3545, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -7819, 86, -4023, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6952, 47, -4197, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -7866, 113, -4852, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5885, 8, -3455, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6012, 8, -2600, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_YELLOW_COIN, -6484, 414, -7840, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -6849, 743, -8468, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -7112, 896, -9363, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -7158, 896, -10208, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -7047, 689, -11292, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_NONE, -3695, -2606, -9170, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -5059, -153, -4773, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 11269, -643, -8994, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3182, 69, -2121, 0, 88, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -129, -88, -6326, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3563, -3271, -9110, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7770, 636, -11010, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3736, -291, -11106, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 9052, -105, -8941, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1835, 69, -423, 0, -127, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -674, -139, -10694, 0, 65, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -8115, -8, -2464, 0, -2, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_UNAGI, 424, -1462, -8381, 0, -2, 0, 0x00000000, bhvUnagi),
		OBJECT(MODEL_EXCLAMATION_BOX, -5998, 358, -5768, 0, -2, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -2214, 431, -4172, 0, 39, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -5702, 122, -11997, 0, 31, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 6618, -663, -8262, 0, 2, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 12409, 345, -7506, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 11318, 793, -13489, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -4231, -2246, -9348, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -2830, 517, -709, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 5802, 180, -5746, 0, 25, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_NONE, -3069, -2151, -8858, 0, 72, 0, (4 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3919, 69, -1410, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -6420, -78, -4827, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -2555, -153, -4926, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 9243, -86, -8677, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_AB_LAVAWALL, -5608, -60, -1480, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -8010, -106, -1470, 0, 110, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3203, 69, -1505, 0, -138, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3204, 69, -1505, 0, 102, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3206, 70, -1502, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_MANTA_RAY, -6061, 1942, -11388, 0, -32, 0, (0x10 << 16), bhvAbManta),
		OBJECT(MODEL_NONE, -6432, 2254, -11964, 0, 59, 0, (0x11 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, -6716, 1942, -11667, 0, 148, 0, (43 << 24) | (43 << 16), bhvMessagePanel),
		OBJECT(MODEL_NONE, -5084, 134, -4796, 0, -18, 0, (0xa << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -3682, -2323, -9092, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3277, -1300, -8036, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2989, 250, -11039, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4144, -1446, -6842, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3226, 120, -8437, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3969, -1138, -10065, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 497, -2333, -7796, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1445, -633, -7736, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_AB_SAND, 4476, -8340, -8379, 0, -2, 0, (2 << 24), bhvAbSand),
		OBJECT(MODEL_FISH, 200, -2460, -8724, 0, -2, 0, (2 << 16), bhvFishSpawner),
		OBJECT(MODEL_NONE, 438, -2585, -9138, 0, -2, 0, 0x00000000, bhvHiddenStarTrigger),
		OBJECT(MODEL_SKEETER, -5615, -517, -7388, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 159, -519, -7532, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 8795, -127, -9264, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_NONE, 8295, -143, -8778, 0, -2, 0, (0xb << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, -2798, -143, -4736, 0, -2, 0, (0xc << 16), bhvFadingWarp),
		OBJECT(MODEL_SKEETER, 1154, -519, -9449, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, -6263, -142, -6392, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_STAR, 7569, 2113, -13975, 0, -2, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, -2750, 235, -4767, 0, -2, 0, (4 << 24), bhvHiddenStar),
		OBJECT(MODEL_NONE, 1976, 1181, -5558, 0, -2, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, -5067, 211, -4785, 0, -2, 0, (0 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, 10697, 1620, -13842, 0, -2, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 2009, 1102, -5718, 0, -2, 0, 0x00000000, bhvAbTroll),
		TERRAIN(ab_area_1_collision),
		MACRO_OBJECTS(ab_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_C1),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, ab_area_2),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x31, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 1, 0x41, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -5044, -153, -5508, 0, -2, 0, 0x00000000, bhvAbMusic),
		OBJECT(MODEL_NONE, 1976, 1180, -5559, 0, -2, 0, (3 << 24), bhvStar),
		TERRAIN(ab_area_2_collision),
		MACRO_OBJECTS(ab_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -2, 8839, -127, -8800),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
