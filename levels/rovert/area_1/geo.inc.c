#include "src/game/envfx_snow.h"

const GeoLayout rovert_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rovert_dl__decor_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_dl__decor_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_TRANSPARENT, 0, -3467, 0, rovert_dl__decor1_mesh_layer_5),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_TRANSPARENT, 0, -3467, 0, rovert_dl__decor2_mesh_layer_5),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 57, 1119, 1935, rovert_dl_CloudVis_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 4807, 2886, -967, rovert_dl_CloudVis_002_mesh_layer_1),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 5553, 3142, -293, 0, 45, 0, rovert_dl_CloudVis_003_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 5016, 3533, 535, rovert_dl_CloudVis_004_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -2297, 4121, -9685, rovert_dl_CloudVis_008_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -2947, 4448, -9994, rovert_dl_CloudVis_009_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -3368, 4853, -9313, rovert_dl_CloudVis_010_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -3492, 6086, -7781, rovert_dl_CloudVis_011_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -3492, 6470, -6903, rovert_dl_CloudVis_012_mesh_layer_1),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 6648, 3099, -7650, 0, 45, 0, rovert_dl_CloudVis_013_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_dl_Cylinder_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rovert_dl_Cylinder_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rovert_dl_Cylinder_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rovert_dl_Cylinder_003_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, rovert_dl_Cylinder_005_mesh_layer_6),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rovert_dl_Cylinder_005_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_dl_Cylinder_005_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rovert_dl_nonsolid_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, rovert_dl_nonsolid_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout rovert_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(0),
		GEO_OPEN_NODE(),
			GEO_NODE_ORTHO(100.0000),
			GEO_OPEN_NODE(),
				GEO_BACKGROUND(BACKGROUND_BELOW_CLOUDS, geo_skybox_main),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 40000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, rovert_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rovert_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, rovert_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rovert_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, rovert_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
