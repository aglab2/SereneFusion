#include "src/game/envfx_snow.h"

const GeoLayout waterfally_switch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, waterfally_switch_waterfally_switch_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, waterfally_switch_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
