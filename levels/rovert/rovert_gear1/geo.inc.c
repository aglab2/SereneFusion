#include "src/game/envfx_snow.h"

const GeoLayout rovert_gear1_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_gear1_gear1_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_gear1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
