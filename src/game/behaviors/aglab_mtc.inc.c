s32 gLavaBurn = 0;

void mtc_yellow_spawner_init()
{
    o->oTimer = o->oBehParams2ndByte * 30;
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvMtcYellowPurpleSwitch, &d);
}

void mtc_yellow_spawner_loop()
{
    s32 bp1 = (o->oBehParams >> 24) & 0xFF;
    if (o->oAction == 0)
    {     
        if (bp1)
        {
            if (o->parentObj->oAction == 1)
            {
                o->oAction = 1;
            }
        }
        else
        {
            o->oAction = 1;
        }
    }
    else
    {
        if (bp1 && 0 == o->oTimer)
        {
            o->oTimer = o->oBehParams2ndByte * 30 + 1;
        }

        if (o->oTimer > 155)
        {
            o->oAction = 0;
            spawn_object(o, MODEL_MTC_BALL, bhvMtcYellowBall);
        }
    }
}

void mtc_yellow_ball_init()
{
    o->oFaceAngleYaw = random_u16();
}

void mtc_yellow_ball_loop()
{
    o->oPosY += 7.f;
    f32 scale;

    if (o->oTimer < 30)
    {
        scale = o->oTimer / 30.f;
    }
    else if (o->oTimer > 200)
    {
        scale = (230 - o->oTimer) / 30.f;
    }
    else
    {
        scale = 1.f;
    }


    f32 yscale = 1.f + 0.2f * sins(653 * o->oTimer);
    obj_scale_xyz(o, scale, yscale * scale, scale);

    if (o->oTimer == 230)
    {
        o->activeFlags = 0;
    }
}

void mtc_yellow_purple_switch_init()
{
    // -
}

void mtc_yellow_purple_switch_loop()
{
    switch (o->oAction) {
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
            }
            break;

        case PURPLE_SWITCH_ACT_TICKING:
            if (o->oTimer < 360) {
                //play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            } else {
                //play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }
            if (o->oTimer > 200) {
                o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            }
            break;

        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.5f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }
}

extern const Trajectory mtc_area_1_spline_greenpath[];

static void spinner_reset()
{
    struct Waypoint* path = segmented_to_virtual(mtc_area_1_spline_greenpath);
    o->oPosX = path->pos[0];
    o->oPosY = path->pos[1];
    o->oPosZ = path->pos[2];
    o->oPathedPrevWaypointFlags = 0;
    o->oPathedStartWaypoint = o->oPathedPrevWaypoint = path;
    o->oMtcGreenLineActiveStatus = 1;
}

static void spinner_line_reset()
{
    struct Object** objs = (struct Object**) aglabScratch;
    for (int i = 0; i < 9; i++)
    {
        if ((i % 2) == 0)
            continue;
        
        int lineStatus = !!((i - 1) % 4);
        obj_set_model(objs[i], (lineStatus ^ o->oMtcGreenLineActiveStatus) ? MODEL_MTC_LINE_INACTIVE : MODEL_MTC_LINE_ACTIVE);
    }
}

void mtc_green_spinner_init()
{
    o->parentObj = spawn_object(o, MODEL_MTC_PROPELLER, bhvStaticObjectEx);
    o->parentObj->oPosY -= 400.f;
    struct Waypoint* path = segmented_to_virtual(mtc_area_1_spline_greenpath);
    spinner_reset();

    struct Object** objs = (struct Object**) aglabScratch;
    static const int linePattern[] = { MODEL_MTC_LINE_WHOLE, MODEL_MTC_LINE_INACTIVE, MODEL_MTC_LINE_WHOLE, MODEL_MTC_LINE_ACTIVE };
    for (int i = 0; i < 9; i++)
    {
        struct Object* line = spawn_object(o, linePattern[i % 4], bhvStaticObjectEx);
        objs[i] = line;
        Vec3s objToNext;
        objToNext[0] = path[i + 1].pos[0] - path[i].pos[0];
        objToNext[1] = path[i + 1].pos[1] - path[i].pos[1];
        objToNext[2] = path[i + 1].pos[2] - path[i].pos[2];
        f32 len = ((f32) objToNext[0]) * ((f32) objToNext[0]) + ((f32) objToNext[1]) * ((f32) objToNext[1]) + ((f32) objToNext[2]) * ((f32) objToNext[2]);
        len = sqrtf(len);
        obj_scale_xyz(line, 1.f, 1.f, len / 900.f);
        line->oPosX = path[i].pos[0];
        line->oPosY = path[i].pos[1];
        line->oPosZ = path[i].pos[2];
        line->oFaceAngleYaw = atan2s(objToNext[2], objToNext[0]);
        line->oFaceAnglePitch = atan2s(sqrtf(sqr(objToNext[0]) + sqr(objToNext[2])), -objToNext[1]);
    }
}

static s32 sMtcInWarp = 0;
void mtc_green_spinner_loop()
{
    if (o->oAction == 0)
    {
        o->oPosY = o->oHomeY + 50.f * sins(142 * o->oTimer);
        if (gMarioObject->platform == o)
        {
            o->oMtcGreenLineActiveStatus = 1;
            spinner_line_reset();
            o->oAction = 6;
        }
    }
    else if (o->oAction == 1)
    {
        // print_text_fmt_int(20, 20, "T %d", o->oTimer);
        // print_text_fmt_int(20, 40, "S %d", o->oMtcGreenLineActiveStatus);
        if (gGlobalTimer % 4 == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_MOVE_2);
        }
        if (o->oPathedPrevWaypointFlags == 0) {
            o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
            o->oPathedPrevWaypointFlags = WAYPOINT_FLAGS_INITIALIZED;
        }

        struct Waypoint *startWaypoint = o->oPathedStartWaypoint;
        struct Waypoint *lastWaypoint = o->oPathedPrevWaypoint;
        struct Waypoint *targetWaypoint;
        Vec3s prevToNext, objToNext;

        if ((lastWaypoint + 1)->flags != WAYPOINT_FLAGS_END) {
            targetWaypoint = lastWaypoint + 1;
        } else {
            targetWaypoint = startWaypoint;
        }

        o->oPathedPrevWaypointFlags = lastWaypoint->flags | WAYPOINT_FLAGS_INITIALIZED;

        vec3_diff(prevToNext, targetWaypoint->pos, lastWaypoint->pos);
        vec3_diff(objToNext, targetWaypoint->pos, &o->oPosVec);

        f32 spd = 15.f;
        if (o->oTimer > 1150)
        {
            // last section, be less mean here and let the crystal go slower
            if (!o->oMtcGreenLineActiveStatus)
            {
                spd = 1.5f;
            }
            else if (gMarioObject->platform != o)
            {
                // last switch was pressed but it still might be too quick so make the thing go slightly slower
                spd = 10.f;
            }
        }
        // print_text_fmt_int(20, 60, "V %d", (int) spd);

        f32 len = sqrtf(objToNext[0] * objToNext[0] + objToNext[1] * objToNext[1] + objToNext[2] * objToNext[2]) / spd;
        if (len > 0.001f)
        {
            objToNext[0] /= len;
            objToNext[1] /= len;
            objToNext[2] /= len;
        }
        
        // If dot(prevToNext, objToNext) <= 0 (i.e. reached other side of target waypoint)
        if (vec3_dot(prevToNext, objToNext) <= 0.0f) {
            o->oPathedPrevWaypoint = targetWaypoint;
            if ((targetWaypoint + 1)->flags == WAYPOINT_FLAGS_END) {
                o->oAction = 2;
            }
        }

        if (o->oAction != 2)
        {
            int curLine = o->oPathedPrevWaypoint - o->oPathedStartWaypoint - 1;
            if ((curLine % 2 == 0))
            {
                int lineStatus = !!(curLine % 4);
                if (lineStatus ^ o->oMtcGreenLineActiveStatus)
                {
                    cur_obj_play_sound_2(SOUND_GENERAL_BIG_POUND);
                    o->oAction = 3;
                    o->oVelY = 20.f;
                }
            }
        }
        
        o->oPosX += objToNext[0];
        o->oPosY += objToNext[1];
        o->oPosZ += objToNext[2];
    }
    else if (o->oAction == 2)
    {
        // -
    }
    else if (o->oAction == 3)
    {
        print_text_centered(160, 20, "PRESS L TO RETRY");
        if (!sMtcInWarp && (gPlayer1Controller->buttonPressed & L_TRIG))
        {
            cur_obj_become_intangible();
            o->oAction = 5;
            gMarioStates->usedObj = o;
            level_trigger_warp(gMarioStates, WARP_OP_TELEPORT);
            spinner_reset();
            spinner_line_reset();
        }

        o->oVelY -= 2.f;
        o->oPosY += o->oVelY;
        if (o->oPosY < -8000.f)
        {
            cur_obj_become_intangible();
            o->oAction = 5;
            spinner_reset();
            spinner_line_reset();
        }
    }
    else if (o->oAction == 5)
    {
        if (o->oTimer > 22)
        {
            cur_obj_become_tangible();
            o->oAction = 0;
        }
    }
    else if (o->oAction == 6)
    {
        o->oAction = 1;
    }
    
    o->parentObj->oFaceAngleYaw += 369;
    o->parentObj->oPosX = o->oPosX;
    o->parentObj->oPosY = o->oPosY - 400.f;
    o->parentObj->oPosZ = o->oPosZ;
}

void mtc_green_line_switch_init()
{
    sMtcInWarp = 0;
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvMtcGreenPlatspin, &d);
}

struct SetTileSize* scroll_mtc_level_geo_mtc_line_active_get();
extern void scroll_mtc_level_geo_mtc_line_inactive_set(struct SetTileSize*);

struct SetTileSize* scroll_mtc_level_geo_mtc_line_switch_get();
void scroll_mtc_level_geo_mtc_line_switch_off_set(struct SetTileSize* ts);

void mtc_green_line_switch_loop()
{
    if (o->parentObj->oAction == 5 || o->parentObj->oAction == 6)
    {
        obj_set_model(o, MODEL_MTC_LINE_SWITCH);
        o->oAction = 0;
        o->oFaceAngleYaw += 0x169;
        o->oPosY = o->oHomeY + 10.f * sins(242 * o->oTimer);
        return;
    }

    if (0 == o->oAction)
    {
        o->oFaceAngleYaw += 0x169;
        o->oPosY = o->oHomeY + 10.f * sins(242 * o->oTimer);
        if (o->oDistanceToMario < 150.f)
        {
            cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);
            obj_set_model(o, MODEL_MTC_LINE_SWITCH_OFF);
            o->oAction = 1;
            o->parentObj->oMtcGreenLineActiveStatus = !o->parentObj->oMtcGreenLineActiveStatus;      
            struct Object** objs = (struct Object**) aglabScratch;
            scroll_mtc_level_geo_mtc_line_inactive_set(scroll_mtc_level_geo_mtc_line_active_get());
            scroll_mtc_level_geo_mtc_line_switch_off_set(scroll_mtc_level_geo_mtc_line_switch_get());
            for (int i = 0; i < 9; i++)
            {
                if ((i % 2) == 0)
                    continue;
                
                int lineStatus = !!((i - 1) % 4);
                obj_set_model(objs[i], (lineStatus ^ o->parentObj->oMtcGreenLineActiveStatus) ? MODEL_MTC_LINE_INACTIVE : MODEL_MTC_LINE_ACTIVE);
            }
        }
    }
}

void mtc_blue_rotat_init()
{
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvFloorSwitchGrills, &d);
}

void mtc_blue_rotat_loop()
{
    if (0 == o->oBehParams2ndByte)
    { 
        if (0 == o->oAction)
        {
            if (o->parentObj->oAction == 1)
            {
                o->oAction = 1;
            }
            o->oMoveAnglePitch += 0x670;
        }
        else
        {
            o->oMoveAnglePitch += 0x70;
        }
    }
    else if (1 == o->oBehParams2ndByte)
    {
        o->oMoveAngleRoll += -0xB0;
    }
    else if (2 == o->oBehParams2ndByte)
    {
        o->oMoveAnglePitch += -0xD0;
    }
    else if (3 == o->oBehParams2ndByte)
    {
        o->oMoveAngleRoll += 0xB0;
    }
}

void mtc_red_ground_init()
{

}

extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_0[60];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_1[12];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_2[24];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_3[14];

static void switch_vcol_alpha(Vtx* svtx, int size, u8 a)
{
    Vtx* vtx = segmented_to_virtual(svtx);
    for (int i = 0; i < size; i++)
    {
        vtx[i].v.cn[3] = a;
    }
}

#define ARGUMENT_WITH_SIZE(x) x, sizeof(x) / sizeof(*(x))

static void mtc_switch_all_vcol_alpha(u8 alpha)
{
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_0), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_1), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_2), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_3), alpha);
}

extern s16 sDelayedWarpOp;

extern const Collision mtc_ground_collision[];
extern const Collision mtc_ground2_collision[];
extern const Collision mtc_ground_safe_collision[];

static s32 mtc_on_golden_bar()
{
    return (-3500.f < o->oMtcLastSafeZ && o->oMtcLastSafeZ < 1849.f && o->oMtcLastSafeX > 13900.f);
}

static s32 mtc_on_golden_bar_v2()
{
    return (-4000.f < gMarioStates->pos[2] && gMarioStates->pos[2] < 2200.f && gMarioStates->pos[0] > 13700.f);
}

static s32 mtc_near_crystals_v2()
{
    return (9600.f < gMarioStates->pos[0] && gMarioStates->pos[0] < 12900.f && 6500.f < gMarioStates->pos[2] && gMarioStates->pos[2] < 9300.f);
}

static s32 mtc_on_pedestal()
{
    return (-1104.f < o->oMtcLastSafeZ && o->oMtcLastSafeZ < -392.f && 5889.f < o->oMtcLastSafeX && o->oMtcLastSafeX < 6622.f);
}

void mtc_red_ground_loop()
{
    s32 wasBurnt = gLavaBurn;
    gLavaBurn = 0;
    int type = gMarioStates->floor ? gMarioStates->floor->type : -1;
    if ((type == 0 || type == SURFACE_NOT_SLIPPERY) && (gMarioStates->pos[1] == gMarioStates->floorHeight))
    {
        o->oMtcLastSafeX = gMarioStates->pos[0];
        o->oMtcLastSafeY = gMarioStates->pos[1];
        o->oMtcLastSafeZ = gMarioStates->pos[2];
    }

    if (gMarioStates->pos[2] < 1600.f || gMarioStates->pos[0] > 1500.f || gMarioStates->pos[1] > 1128.f)
    {
        if (0 != o->oAction)
        {
            o->oMtcRedStatus = 0;
            obj_set_collision_data(o, mtc_ground_collision);
            mtc_switch_all_vcol_alpha(0xff);
            o->oAction = 0;
        }

        // quick respawn points
        if (6 != gCurrActNum)
        {
            if (0 == o->oSubAction)
            {
                sMtcInWarp = 0;
                if (gMarioStates->health > 0x380
                && 0 == sDelayedWarpOp
                && o->oMtcLastSafeY > 500.f
                && gMarioStates->pos[1] < -500.f
                && wasBurnt
                && !mtc_on_golden_bar()
                && !mtc_on_golden_bar_v2()
                && !mtc_near_crystals_v2()
                && !mtc_on_pedestal())
                {
                    o->oTimer = 0;
                    if (o->oMtcLastSafeZ > 500.f)
                    {
                        if (o->oMtcLastSafeX > 5000.f)
                        {
                            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
                            o->oSubAction = 1;
                            sMtcInWarp = 1;
                            gAllowPausing = 0;
                        }
                        else
                        {
                            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
                            o->oSubAction = 2;
                            sMtcInWarp = 1;
                            gAllowPausing = 0;
                        }
                    }
                    else
                    {
                        if (o->oMtcLastSafeX < 3000.f)
                        {
                            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
                            o->oSubAction = 3;
                            sMtcInWarp = 1;
                            gAllowPausing = 0;
                        }
                        else
                        {
                            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
                            o->oSubAction = 4;
                            sMtcInWarp = 1;
                            gAllowPausing = 0;
                        }
                    }
                }
            }
            else
            {
                if (o->oTimer == 12)
                {
                    if (1 == o->oSubAction)
                    {
                        gMarioStates->pos[0] = 5495.f;
                        gMarioStates->pos[1] = -204.f;
                        gMarioStates->pos[2] = 7612.f;
                        gMarioStates->faceAngle[1] = 0x6000;
                    }
                    else if (2 == o->oSubAction)
                    {
                        gMarioStates->pos[0] = 3065.f;
                        gMarioStates->pos[1] = -44.f;
                        gMarioStates->pos[2] = 1875.f;
                        gMarioStates->faceAngle[1] = 0;
                    }
                    else if (3 == o->oSubAction)
                    {
                        gMarioStates->pos[0] = 1846.f;
                        gMarioStates->pos[1] = -38.f;
                        gMarioStates->pos[2] = -2463.f;
                        gMarioStates->faceAngle[1] = 0xa000;
                    }
                    else if (4 == o->oSubAction)
                    {
                        gMarioStates->pos[0] = 2022.f;
                        gMarioStates->pos[1] = 602.f;
                        gMarioStates->pos[2] = -7693.f;
                        gMarioStates->faceAngle[1] = 0x4000;
                    }
                    gMarioStates->vel[0] = 0;
                    gMarioStates->vel[1] = 0;
                    gMarioStates->vel[2] = 0;
                    gMarioStates->forwardVel = 0;
                    gMarioStates->squishTimer = 0;
                    drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
                }
                if (o->oTimer == 13)
                {
                    reset_camera(gCamera);
                }
                if (o->oTimer == 14)
                {
                    play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0,0,0);
                    o->oSubAction = 0;
                    gAllowPausing = 1;
                }
            }
        }

        return;
    }
    else
    {
        o->oSubAction = 0;
    }

    if (o->oAction == 0)
    {
        o->oAction = 1;
    }
    else
    {
        if (o->oTimer <= 200 - 0x20)
        {
            if (gPlayer1Controller->buttonPressed & L_TRIG)
            {
                o->oTimer = 200 - 0x20;
            }

            if (o->oTimer && 0 == (o->oTimer % 30))
            {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }
        }
        else
        {
            if (o->oTimer > 200 - 0x10)
                obj_set_collision_data(o, mtc_ground_safe_collision);
    
            play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            if (!o->oMtcRedStatus)
                mtc_switch_all_vcol_alpha((200 - o->oTimer) * 0x8);
            else
                mtc_switch_all_vcol_alpha(0xff - (200 - o->oTimer) * 0x8);
        }

        if (200 == o->oTimer)
        {
            o->oMtcRedStatus = !o->oMtcRedStatus;
            if (o->oMtcRedStatus)
            {
                obj_set_collision_data(o, mtc_ground2_collision);
                mtc_switch_all_vcol_alpha(0);
            }
            else
            {
                obj_set_collision_data(o, mtc_ground_collision);
                mtc_switch_all_vcol_alpha(0xff);
            }

            o->oTimer = 0;
        }
    }

    load_object_collision_model();
}

void mtc_brick_ctl_init()
{
    o->parentObj = spawn_object(o, MODEL_STAR, bhvStar);
    o->parentObj->oBehParams = o->oBehParams;
}

static void update_home(struct Object* obj)
{
    obj->oHomeX = obj->oPosX;
    obj->oHomeY = obj->oPosY;
    obj->oHomeZ = obj->oPosZ;
}

extern s16 s8DirModeYawOffset;
void mtc_brick_ctl_loop()
{
    o->oPosX = o->parentObj->oPosX;
    o->oPosY = o->parentObj->oPosY;
    o->oPosZ = o->parentObj->oPosZ;

    if (0 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 1;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 16129.f;
            o->parentObj->oPosY = 1131.f;
            o->parentObj->oPosZ = -227.f;
        }
    }
    else if (1 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 2;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 16768.f;
            o->parentObj->oPosY = -280.f;
            o->parentObj->oPosZ = -2107.f;
        }
    }
    else if (2 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 3;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 10930.f;
            o->parentObj->oPosY = 50.f;
            o->parentObj->oPosZ = 7086.f;
        }
    }
    else if (3 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 4;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            o->parentObj->oPosX = 10794.f;
            o->parentObj->oPosY = -492.f;
            o->parentObj->oPosZ = 8648.f;
            update_home(o->parentObj);
            o->oMtcGoldBrickFakeStar0 = spawn_object(o, MODEL_STAR, bhvStar);
            o->oMtcGoldBrickFakeStar0->oPosX = 10343.f;
            o->oMtcGoldBrickFakeStar0->oPosY = -335.f - 1000.f;
            o->oMtcGoldBrickFakeStar0->oPosZ = 7975.f;
            o->oMtcGoldBrickFakeStar0->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar0);
            o->oMtcGoldBrickFakeStar1 = spawn_object(o, MODEL_STAR, bhvStar);
            o->oMtcGoldBrickFakeStar1->oPosX = 11748.f;
            o->oMtcGoldBrickFakeStar1->oPosY = -591.f - 1000.f;
            o->oMtcGoldBrickFakeStar1->oPosZ = 8292.f;
            o->oMtcGoldBrickFakeStar1->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar1);
            spawn_mist_particles();
        }
    }
    else if (4 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        if (o->oMtcGoldBrickSkillIssue)
        {
            o->oMtcGoldBrickFakeStar0->oPosY += 20.f;
            o->oMtcGoldBrickFakeStar1->oPosY += 20.f;
            if (50 == o->oTimer)
            {
                update_home(o->oMtcGoldBrickFakeStar0);
                update_home(o->oMtcGoldBrickFakeStar1);
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
                o->oAction = 5;
            }
        }
        else
        {
            o->oMtcGoldBrickFakeStar0->oPosY += 10.f;
            o->oMtcGoldBrickFakeStar1->oPosY += 10.f;
            if (100 == o->oTimer)
            {
                update_home(o->oMtcGoldBrickFakeStar0);
                update_home(o->oMtcGoldBrickFakeStar1);
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
                o->oAction = 5;
            }
        }
    }
    else if (5 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        int pivotTime = o->oMtcGoldBrickCount < 3 ? 30 : 10;
        if (0 == o->oTimer)
        {
            // pick 2 stars at random to swap
            int idx = random_u16() % 3;
            switch (idx)
            {
            case 0: o->oMtcGoldBrickToSwap0 = o->parentObj             ; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar0; break;
            case 1: o->oMtcGoldBrickToSwap0 = o->parentObj             ; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar1; break;
            case 2: o->oMtcGoldBrickToSwap0 = o->oMtcGoldBrickFakeStar0; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar1; break;
            }
        }
        else if (o->oTimer > pivotTime)
        {
            o->oTimer = 0; // it will not go oTimer==0
            update_home(o->oMtcGoldBrickToSwap0);
            update_home(o->oMtcGoldBrickToSwap1);
            o->oMtcGoldBrickCount++;
            if (o->oMtcGoldBrickCount > 10)
            {
                o->oMtcGoldBrickToSwap0 = NULL;
                o->oMtcGoldBrickToSwap1 = NULL;
                o->oMtcGoldBrickCount = 0;
                o->oAction = 6;
            }
        
            // pick 2 stars at random but not the ones that were swapped already
            struct Object* o1 = random_u16() % 2 ? o->oMtcGoldBrickToSwap0 : o->oMtcGoldBrickToSwap1;
            struct Object* o2 = NULL;
            if (o->oMtcGoldBrickToSwap0 != o->parentObj              && o->oMtcGoldBrickToSwap1 != o->parentObj)
                o2 = o->parentObj;
            if (o->oMtcGoldBrickToSwap0 != o->oMtcGoldBrickFakeStar0 && o->oMtcGoldBrickToSwap1 != o->oMtcGoldBrickFakeStar0)
                o2 = o->oMtcGoldBrickFakeStar0;
            if (o->oMtcGoldBrickToSwap0 != o->oMtcGoldBrickFakeStar1 && o->oMtcGoldBrickToSwap1 != o->oMtcGoldBrickFakeStar1)
                o2 = o->oMtcGoldBrickFakeStar1;

            o->oMtcGoldBrickToSwap0 = o1;
            o->oMtcGoldBrickToSwap1 = o2;
        }
        else
        {
            Vec3f mov;
            mov[0] = o->oMtcGoldBrickToSwap0->oHomeX - o->oMtcGoldBrickToSwap1->oHomeX;
            mov[1] = o->oMtcGoldBrickToSwap0->oHomeY - o->oMtcGoldBrickToSwap1->oHomeY;
            mov[2] = o->oMtcGoldBrickToSwap0->oHomeZ - o->oMtcGoldBrickToSwap1->oHomeZ;
            f32 scale = (float) o->oTimer / (float) pivotTime;
            mov[0] *= scale;
            mov[1] *= scale;
            mov[2] *= scale;
            o->oMtcGoldBrickToSwap0->oPosX = o->oMtcGoldBrickToSwap0->oHomeX - mov[0];
            o->oMtcGoldBrickToSwap0->oPosY = o->oMtcGoldBrickToSwap0->oHomeY - mov[1];
            o->oMtcGoldBrickToSwap0->oPosZ = o->oMtcGoldBrickToSwap0->oHomeZ - mov[2];
            
            o->oMtcGoldBrickToSwap1->oPosX = o->oMtcGoldBrickToSwap1->oHomeX + mov[0];
            o->oMtcGoldBrickToSwap1->oPosY = o->oMtcGoldBrickToSwap1->oHomeY + mov[1];
            o->oMtcGoldBrickToSwap1->oPosZ = o->oMtcGoldBrickToSwap1->oHomeZ + mov[2];
        }
    }
    else if (6 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        if (o->oTimer > 10)
        {
            gCamera->cutscene = 0;
            reset_camera(gCamera);
            s8DirModeYawOffset = 0x8000;
            o->oAction = 7;
        }
    }
    else if (7 == o->oAction)
    {
        Vec3f dist;
        dist[0] = o->oMtcGoldBrickFakeStar0->oPosX - gMarioStates->pos[0];
        dist[1] = o->oMtcGoldBrickFakeStar0->oPosY - gMarioStates->pos[1];
        dist[2] = o->oMtcGoldBrickFakeStar0->oPosZ - gMarioStates->pos[2];
        f32 d0 = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];
        dist[0] = o->oMtcGoldBrickFakeStar1->oPosX - gMarioStates->pos[0];
        dist[1] = o->oMtcGoldBrickFakeStar1->oPosY - gMarioStates->pos[1];
        dist[2] = o->oMtcGoldBrickFakeStar1->oPosZ - gMarioStates->pos[2];
        f32 d1 = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];

        if (d0 < (400.f * 400.f) || d1 < (400.f * 400.f))
        {
            play_sound(SOUND_PEACH_POWER_OF_THE_STARS, gMarioStates->marioObj->header.gfx.cameraToObject);
            o->parentObj->oPosX = 10794.f;
            o->parentObj->oPosY = -492.f;
            o->parentObj->oPosZ = 8648.f;
            update_home(o->parentObj);
            o->oMtcGoldBrickFakeStar0->oPosX = 10343.f;
            o->oMtcGoldBrickFakeStar0->oPosY = -335.f - 1000.f;
            o->oMtcGoldBrickFakeStar0->oPosZ = 7975.f;
            o->oMtcGoldBrickFakeStar0->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar0);
            o->oMtcGoldBrickFakeStar1->oPosX = 11748.f;
            o->oMtcGoldBrickFakeStar1->oPosY = -591.f - 1000.f;
            o->oMtcGoldBrickFakeStar1->oPosZ = 8292.f;
            o->oMtcGoldBrickFakeStar1->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar1);
            o->oAction = 4;
            o->oMtcGoldBrickSkillIssue = 1;
        }
    }
}
