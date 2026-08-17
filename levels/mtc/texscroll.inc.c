void scroll_gfx_mtc_dl_Course_13_mesh_layer_1() {
	Gfx *mat = segmented_to_virtual(mtc_dl_Course_13_mesh_layer_1);




	shift_t(mat, 847, PACK_TILESIZE(0, 2));
	shift_t(mat, 1134, PACK_TILESIZE(0, 1));
	shift_t(mat, 2543, PACK_TILESIZE(0, 1));
	shift_t(mat, 3336, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mtc_dl_Course_13_007_mesh_layer_1() {
	Gfx *mat = segmented_to_virtual(mtc_dl_Course_13_007_mesh_layer_1);

	shift_t(mat, 14, PACK_TILESIZE(0, 1));

};

void scroll_mtc() {
	scroll_gfx_mtc_dl_Course_13_mesh_layer_1();
	scroll_gfx_mtc_dl_Course_13_007_mesh_layer_1();
};
