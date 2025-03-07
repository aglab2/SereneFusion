#include "src/game/envfx_snow.h"

const GeoLayout dan_bird_geo[] = {
	GEO_CULLING_RADIUS(1000),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 66, 0, dan_bird_root_mesh_layer_4),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, dan_bird_root_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, dan_bird_h_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 30, 56, 0, dan_bird_h_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_h_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_l1_skinned_mesh_layer_4),
			GEO_ANIMATED_PART(LAYER_ALPHA, 43, 37, -34, dan_bird_l1_mesh_layer_4),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_l2_skinned_mesh_layer_4),
				GEO_ANIMATED_PART(LAYER_ALPHA, -74, -56, -1, dan_bird_l2_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_r1_skinned_mesh_layer_4),
			GEO_ANIMATED_PART(LAYER_ALPHA, 43, 37, 36, dan_bird_r1_mesh_layer_4),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_r2_skinned_mesh_layer_4),
				GEO_ANIMATED_PART(LAYER_ALPHA, -74, -56, 1, dan_bird_r2_mesh_layer_4),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, dan_bird_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dan_bird_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
