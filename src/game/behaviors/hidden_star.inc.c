// hidden_star.inc.c

void bhv_hidden_star_init(void) {
    s16 remainingTriggers = count_objects_with_behavior(bhvHiddenStarTrigger);
    if (remainingTriggers == 0) {
        struct Object *starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    o->oHiddenStarTriggerCounter = 5 - remainingTriggers;
}

void bhv_hidden_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oHiddenStarTriggerCounter == 5) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

// every 4 vertices are referring to a cross for 5 secrets
extern Vtx rovert_dl_nonsolid_001_mesh_layer_6_vtx_1[20];
void bhv_hidden_star_trigger_loop(void) {
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        struct Object *hiddenStar = cur_obj_nearest_object_with_behavior(bhvHiddenStar);

        if (hiddenStar != NULL) {
            hiddenStar->oHiddenStarTriggerCounter++;

            if (hiddenStar->oHiddenStarTriggerCounter != 5) {
                spawn_orange_number(hiddenStar->oHiddenStarTriggerCounter, 0, 0, 0);
            }

            play_sound(SOUND_MENU_COLLECT_SECRET + (((u8) hiddenStar->oHiddenStarTriggerCounter - 1) << 16), gGlobalSoundSource);
        }

        if (gCurrCourseNum == COURSE_ROVERT)
        {
            Vtx* vtx = (Vtx*) segmented_to_virtual(rovert_dl_nonsolid_001_mesh_layer_6_vtx_1);
            for (int i = 0; i < 4; i++)
            {
                int idx = i + o->oBehParams2ndByte * 4;
                vtx[idx].n.ob[1] -= 100;
            }
        }
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (gCurrCourseNum == COURSE_SPIDERS)
    {
        if (0 == (o->oTimer % 5))
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);

        o->oFaceAngleYaw += 0x139;
        o->oFaceAngleRoll += 0x38;
    }
}

void bhv_bowser_course_red_coin_star_loop(void) {
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;

    switch (o->oAction) {
        case 0:
            if (o->oHiddenStarTriggerCounter == 8) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
