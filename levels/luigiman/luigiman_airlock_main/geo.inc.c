#include "src/game/envfx_snow.h"

const GeoLayout luigiman_airlock_main_geo[] = {
	GEO_CULLING_RADIUS(4000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigiman_airlock_main_Airlock_Main_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigiman_airlock_main_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
