#include "src/game/envfx_snow.h"

const GeoLayout triarc_plat1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, triarc_plat1_cylin_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, triarc_plat1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
