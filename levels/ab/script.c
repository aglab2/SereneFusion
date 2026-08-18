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
		MARIO_POS(0x01, -2, 9273, 1834, -1534),
		OBJECT(MODEL_CLAM_SHELL, 10042, 1882, -1744, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 12738, 1942, -3307, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 12232, 1882, -109, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13293, 2143, -5970, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 11566, 2905, -5653, 0, -97, 0, 0x00000000, bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 11084, 3125, -6030, 0, 85, 0, 0x00000000, bhvClamShell),
		OBJECT(MODEL_NONE, 11694, 1769, -1735, 0, -2, 0, 0x00000000, bhvAbClamCtl),
		OBJECT(MODEL_CLAM_SHELL, 12920, 2136, -6547, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 10628, 1882, -2975, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 10826, 1882, -359, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13246, 1885, -1634, 0, -2, 0, (1 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13566, 2135, -4696, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_CLAM_SHELL, 13559, 2151, -5361, 0, -2, 0, (2 << 16), bhvClamShell),
		OBJECT(MODEL_BLUE_COIN, -7111, 1919, 4132, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -8085, 2084, 3721, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -7385, 2047, 3243, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6518, 2008, 3069, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -7432, 2074, 2414, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5451, 1969, 3811, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5578, 1969, 4666, 0, -2, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_YELLOW_COIN, -6050, 2375, -574, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -6415, 2704, -1202, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -6678, 2857, -2097, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -6724, 2857, -2942, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -6613, 2650, -4026, 0, -2, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_NONE, -3261, -645, -1904, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -4624, 1809, 2493, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 11703, 1318, -1728, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -2748, 2031, 5145, 0, 88, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 305, 1873, 940, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3129, -1309, -1844, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7336, 2597, -3744, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4170, 1671, -3840, 0, 109, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 9486, 1857, -1675, 0, -2, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1401, 2031, 6843, 0, -127, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -240, 1822, -3427, 0, 65, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -7681, 1953, 4802, 0, -2, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_EXCLAMATION_BOX, -5564, 2319, 1498, 0, -2, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1780, 2392, 3094, 0, 39, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -5268, 2084, -4731, 0, 31, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 7052, 1299, -996, 0, 2, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 12843, 2306, -240, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 11752, 2754, -6223, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -3797, -285, -2082, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -2396, 2478, 6557, 0, -60, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 6236, 2141, 1520, 0, 25, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_NONE, -2635, -190, -1592, 0, 72, 0, (4 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3485, 2031, 5856, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -5986, 1883, 2439, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -2121, 1809, 2340, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 9677, 1875, -1411, 0, -2, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_AB_LAVAWALL, -5174, 1901, 5786, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -7576, 1855, 5796, 0, 110, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -2768, 2031, 5761, 0, -138, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -2770, 2031, 5761, 0, 102, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -2772, 2031, 5764, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_MANTA_RAY, -5627, 3903, -4122, 0, -32, 0, (0x10 << 16), bhvAbManta),
		OBJECT(MODEL_NONE, -5997, 4215, -4698, 0, 59, 0, (0x11 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, -6281, 3903, -4401, 0, 148, 0, (43 << 24) | (43 << 16), bhvMessagePanel),
		OBJECT(MODEL_NONE, -4650, 2095, 2470, 0, 150, 0, (0xa << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -3248, -362, -1826, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2843, 661, -770, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2555, 2211, -3773, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4320, 1913, 1786, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2792, 2081, -1171, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3535, 824, -2799, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4404, 600, -1619, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3296, 1254, 752, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_AB_SAND, 4910, -6378, -1113, 0, -2, 0, (2 << 24), bhvAbSand),
		OBJECT(MODEL_SKEETER, -5181, 1444, -122, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 593, 1442, -266, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 9230, 1834, -1998, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_NONE, 8729, 1818, -1512, 0, -2, 0, (0xb << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, -2363, 1818, 2530, 0, -2, 0, (0xc << 16), bhvFadingWarp),
		OBJECT(MODEL_SKEETER, 1588, 1442, -2183, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, -5829, 1819, 874, 0, -2, 0, 0x00000000, bhvSkeeter),
		OBJECT(MODEL_STAR, 8003, 4074, -6709, 0, -2, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_YELLOW_COIN, 11086, 3094, -7039, 0, -2, 0, (1 << 24), bhvYellowCoin),
		OBJECT(MODEL_NONE, 2410, 3143, 1708, 0, -2, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, -4632, 2172, 2481, 0, -2, 0, (0 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, 11131, 3581, -6576, 0, -2, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_NONE, 2443, 3063, 1548, 0, -2, 0, 0x00000000, bhvAbTroll),
		OBJECT(MODEL_PURPLE_SWITCH, 912, -614, -480, 0, 16, 0, 0x00000000, bhvAbPurpleSwitch),
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
		OBJECT(MODEL_NONE, -4610, 1809, 1759, 0, -2, 0, 0x00000000, bhvAbMusic),
		OBJECT(MODEL_NONE, 2410, 3142, 1707, 0, -2, 0, (3 << 24), bhvStar),
		TERRAIN(ab_area_2_collision),
		MACRO_OBJECTS(ab_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -2, 9273, 1834, -1534),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
