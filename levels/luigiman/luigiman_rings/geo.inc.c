#include "src/game/envfx_snow.h"

const GeoLayout luigiman_rings_geo[] = {
	GEO_CULLING_RADIUS(5365),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigiman_rings_Rings_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigiman_rings_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
