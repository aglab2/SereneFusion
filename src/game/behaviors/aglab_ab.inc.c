extern const Trajectory ab_area_1_spline_manta_path[];

static void manta_reset()
{
    struct Waypoint* path = segmented_to_virtual(ab_area_1_spline_manta_path);
    o->oPathedPrevWaypointFlags = 0;
    o->oPathedStartWaypoint = o->oPathedPrevWaypoint = path;
    o->oPosX = path->pos[0];
    o->oPosY = path->pos[1];
    o->oPosZ = path->pos[2];
    o->oMoveAngleRoll = 0;
    o->oMoveAngleYaw = 0;
    o->oMoveAnglePitch = 0;
}

void bhv_ab_manta_ray_init()
{
    gDoInertia = 0;
    gDoPlatformDisplacement = 0;
    cur_obj_scale(2.5f);
    manta_reset();
}

void bhv_ab_manta_ray_loop()
{
    if (o->oMantaFailTimer)
    {
        o->oMantaFailTimer--;
        print_text_centered(160, 20, "PRESS L TO RETRY");
        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            o->oMantaFailTimer = 0;
            gMarioStates->usedObj = o;
            level_trigger_warp(gMarioStates, WARP_OP_TELEPORT);
        }
    }

    if (0 == o->oAction)
    {
        if (gMarioObject->platform == o)
        {
            play_sound(SOUND_MARIO_TWIRL_BOUNCE, gMarioStates->marioObj->header.gfx.cameraToObject);
            drop_and_set_mario_action(gMarioStates, ACT_TWIRLING, 0);
            gMarioStates->vel[1] = 50.f;
            o->oAction = 1;
        }
    }
    else if (1 == o->oAction)
    {
        if (gMarioObject->oPosY < 1000.f - 1990.f + 3951.f)
        {
            manta_reset();
            o->oAction = 0;
            o->oMantaFailTimer = 120;
            return;
        }

        int status = cur_obj_follow_path();
        if (status == PATH_REACHED_END)
        {
            o->oAction = 2;
        }
        
        if (gMarioObject->platform == o)
        {
            play_sound(SOUND_MARIO_TWIRL_BOUNCE, gMarioStates->marioObj->header.gfx.cameraToObject);
            drop_and_set_mario_action(gMarioStates, ACT_TWIRLING, 0);
            gMarioStates->vel[1] = 50.f;
        }

        o->oMantaTargetYaw   = o->oPathedTargetYaw;
        o->oMantaTargetPitch = o->oPathedTargetPitch;
        o->oForwardVel = 22.0f;

        o->oMoveAngleYaw   = approach_s16_symmetric(o->oMoveAngleYaw, o->oMantaTargetYaw, 0x80);
        o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, o->oMantaTargetPitch, 0x80);

        // This causes the ray to tilt as it turns.
        if ((s16) o->oMantaTargetYaw != (s16) o->oMoveAngleYaw) {
            o->oMoveAngleRoll -= 0x5B;
            if (o->oMoveAngleRoll < -DEGREES(30)) {
                o->oMoveAngleRoll = -0x4000 / 3;
            }
        } else {
            o->oMoveAngleRoll += 0x5B;
            if (o->oMoveAngleRoll > DEGREES(30)) {
                o->oMoveAngleRoll = 0x4000 / 3;
            }
        }

        cur_obj_set_pos_via_transform();
        obj_build_transform_from_pos_and_angle(o, O_POS_INDEX, O_FACE_ANGLE_INDEX);

        s16 animFrame = o->header.gfx.animInfo.animFrame;
        if (animFrame == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_MOVING_WATER);
        }
    }
    else
    {
        // -
    }
}

void bhv_ab_sand_init()
{ 
    o->oHomeY = -8000.f - 1990 + 3951;
}

extern const BehaviorScript bhvHiddenStarTrigger[];
extern Vtx ab_sand_Plane_mesh_layer_5_vtx_0[25];
void bhv_ab_sand_loop()
{
    // raise self up
    if (o->oPosY < o->oHomeY)
    {
        o->oPosY += 15.f;
        if (o->oPosY > o->oHomeY)
        {
            o->oPosY = o->oHomeY;
        }
    }

    // bobble
    {
        o->oKleptoTimeUntilTargetChange++;
        f32 off = 200.f * sins(o->oKleptoTimeUntilTargetChange * 324);
        Vtx* vtx = (Vtx*) segmented_to_virtual(ab_sand_Plane_mesh_layer_5_vtx_0);
        vtx[3] .v.ob[1] = off;
        vtx[7] .v.ob[1] = off;
        vtx[12].v.ob[1] = off;
        vtx[19].v.ob[1] = off;
        vtx[24].v.ob[1] = -off;
    }

    // warping thingy
    if (0 == o->oAction)
    {
        if (gMarioStates->pos[1] < -7300.f - 1990 + 3951)
        {
            spawn_star(o, 9085.f+ 5701 - 5267, 215.f - 1990 + 3951, -8925.f + 11153 - 3887);
            o->oHomeY = o->oPosY;
            o->oAction = 1;
        }
    }
    else if (1 == o->oAction)
    {
        if (gMarioStates->floorHeight == gMarioStates->pos[1])
        {
            struct Surface* floor = gMarioStates->floor;
            if (o->oHomeY < gMarioStates->pos[1] - 300.f && o->oHomeY < -1272.f - 1990 + 3951 && floor && (floor->type == SURFACE_NOT_SLIPPERY || floor->type == 0))
            {
                o->oKleptoStartPosX = gMarioStates->pos[0];
                o->oKleptoStartPosY = gMarioStates->pos[1];
                o->oKleptoStartPosZ = gMarioStates->pos[2];
                o->oHomeY = gMarioStates->pos[1] - 300.f;
            }
        }
        else if (gMarioStates->pos[1] < o->oPosY && gMarioStates->pos[0] > 1865.f - 1990 + 3951)
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0xc2 / 2, 0xb2 / 2, 0x30 / 2);
            o->oAction = 2;
            gAllowPausing = 0;
        }
    }
    else if (2 == o->oAction)
    {
        if (o->oTimer == 12)
        {
            gMarioStates->pos[0] = o->oKleptoStartPosX;
            gMarioStates->pos[1] = o->oKleptoStartPosY + 100.f;
            gMarioStates->pos[2] = o->oKleptoStartPosZ;
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
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0xc2 / 2, 0xb2 / 2, 0x30 / 2);
            o->oAction = 1;
            gAllowPausing = 1;
        }
    }
}

void bhv_ab_clam_ctl_init()
{
    cur_obj_find_all_objects_with_behavior_and_bparam(bhvClamShell, &o->oAbClamCtlObj0, 1);
    s16 yaw;
    vec3f_get_lateral_dist_and_yaw(&o->oPosVec, &o->oAbClamCtlObj0->oPosVec, &o->oAbClamCtlDistance, &yaw);
    o->oAbClamCtlDistance -= 0.f;
}

void bhv_ab_clam_ctl_loop()
{
    o->oFaceAngleYaw += 0xB9;
    struct Object** objs = &o->oAbClamCtlObj0;
    for (int i = 0; i < 6; i++)
    {
        struct Object* clam = objs[i];
        clam->oMoveAngleYaw = o->oFaceAngleYaw + 0x10000 / 6 * i;
        f32 d = o->oAbClamCtlDistance + 200.f * sins(872 * o->oTimer);
        clam->oPosX = o->oPosX + d * sins(clam->oMoveAngleYaw);
        clam->oPosZ = o->oPosZ + d * coss(clam->oMoveAngleYaw);
        clam->oPosY = find_floor_height(clam->oPosX, clam->oPosY + 100.f, clam->oPosZ);
        clam->oMoveAngleYaw += 0x4000;
    }
}

extern Gfx ab_dl_tf_mesh_layer_5[];
void bhv_ab_troll_loop()
{
    u8* env = (u8*) segmented_to_virtual(ab_dl_tf_mesh_layer_5) + 10 * 8 + 7;
    if (gMarioStates->pos[1] < 520.f - 1990 + 3951 || o->oDistanceToMario > 500.f )
    {
        *env = 0;
        return;
    }

    if (o->oDistanceToMario > 250.f)
    {
        *env = (500.f - o->oDistanceToMario);
    }
    else
    {
        *env = 255;
    }
}

#include "audio/load.h"
extern void set_instrument(struct SequenceChannel *seqChannel, u8 instId);
void bhv_ab_music_loop()
{
    if (o->oTimer == 0)
        return;
    
    set_instrument(gSequencePlayers[0].channels[4], 0x19);
    set_instrument(gSequencePlayers[0].channels[5], 0x19);
    set_instrument(gSequencePlayers[0].channels[6], 0x2a);
    set_instrument(gSequencePlayers[0].channels[7], 0x2a);
}

void ab_purple_switch_init()
{
    o->parentObj = NULL;
}

void ab_purple_switch_loop()
{
    switch (o->oAction) {
        case PURPLE_SWITCH_ACT_IDLE:
            if (o->parentObj)
            {
                o->parentObj->oPosY = -8000.f - 1990 + 3951;
            }

            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) 
            {
                if (!o->parentObj)
                {
                    o->parentObj = spawn_star(o, -442.f, 2124.f-1183.f, -2149.f);
                    o->parentObj->oBehParams = 4 << 24;
                }
                else
                {
                    o->parentObj->oPosY = 2124.f-1183.f;
                }

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
            if (gMarioStates->action & ACT_FLAG_SWIMMING) {
                o->oTimer += 2;
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            } else {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
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
