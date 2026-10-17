#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "sound_init.h"
#include "rumble_init.h"

#include "actors/common1.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "levels/castle_grounds/header.h"
#include "levels/rovert/header.h"
#include "segment2.h"
#include "segment7.h"
#include "seq_ids.h"
#include "text_strings.h"
#include "types.h"
#include "config.h"
#include "puppycam2.h"

#include "src/audio/load.h"

static f32 sTimeWarpTransition = 0.0f;

static s16 sGearRotation = 0;

u8 gPushableInit = FALSE;

s16 gRovertBC_Action;
s16 gRovertBC_Timer;

Vec3f gWigglerPosition;
s8 gWigglerHealth;

u8 gUsedHyper = 0;//bit field for used up hypercube exclamation boxes
u8 gFutureGoombasKilled = 0;//bit field for killed goombas in the future

u8 gRovertPurpleSwitchState;

static u8 sWatchAmount = 0;

static s32 sHeldLButtonFrames = 0;
static u8 sCanLWarp = FALSE;
static f32 sLastVisitedPool[3];
static u8 sLWarpAction = 0;

static void* sWatchDL_List[] = {
    &watch5_watch_mesh,
    &watch4_watch_mesh,
    &watch3_watch_mesh,
    &watch2_watch_mesh,
    &watch_watch_mesh,
};

void rovert_init(void) {
    sWatchAmount = 4;
    sTimeWarpTransition = 0.0f;
    sGearRotation = 0;
    gPushableInit = FALSE;
    
    gRovertBC_Timer = 0;
    gRovertBC_Action = 0;

    gWigglerPosition[0] = -47.3581*100.0f;
    gWigglerPosition[1] = 24.4845*100.0f;
    gWigglerPosition[2] = 102.066*100.0f;
    gWigglerHealth = 4;

    gUsedHyper = 0;
    gFutureGoombasKilled = 0;

    gRovertPurpleSwitchState = 0;
    sCanLWarp = 0;
    sHeldLButtonFrames = 0;
    sLWarpAction = 0;

    // Level start
    sLastVisitedPool[0] = 57.f;
    sLastVisitedPool[1] = 787.f;
    sLastVisitedPool[2] = 15.f;
}

static int sDeferWarp = 0;
void rovert_check_instant_warp()
{
    if (gCurrLevelNum != LEVEL_ROVERT)
        sDeferWarp = 0;
    if (!sDeferWarp)
        return;

    sDeferWarp = 0;
    u8 goarea = (gCurrAreaIndex==1) ? 2 : 1;
    u16 cameraAngle = gMarioState->area->camera->yaw;
    change_area(goarea);
    gMarioState->area = gCurrentArea;
    gMarioState->area->camera->yaw = cameraAngle;
    sTimeWarpTransition = 255.0f;
    sWatchAmount --;
    play_sound(SOUND_OBJ_MRI_SHOOT,gMarioState->marioObj->header.gfx.cameraToObject);
    if (gCurrAreaIndex == 1) {
        load_segment_decompress_skybox(0xA,_cloud_floor_skybox_yay0SegmentRomStart,_cloud_floor_skybox_yay0SegmentRomEnd);
    } else {
        load_segment_decompress_skybox(0xA,_bidw_skybox_mio0SegmentRomStart, _bidw_skybox_mio0SegmentRomEnd);
    }
}

void rovert_loop(void) {

    //osRTCInit();

    if (gCurrLevelNum == LEVEL_ROVERT) {
        if (!gCurrCreditsEntry)
            gSequencePlayers[0].tempo = gCurrAreaIndex == 1 ? 7668 : 5968; 

        if ((gPlayer1Controller->buttonPressed & L_TRIG) 
         && (gMarioState->action != ACT_HOLDING_POLE)
         && (gMarioState->action != ACT_GRAB_POLE_FAST)
         && (gMarioState->action != ACT_GRAB_POLE_SLOW)
         && (gMarioState->action != ACT_CLIMBING_POLE)
         && (gMarioState->action != ACT_TOP_OF_POLE_TRANSITION)
         && (gMarioState->action != ACT_TOP_OF_POLE)
         && (sWatchAmount > 0)
         && (gWigglerHealth > 1)
         && (0 == sLWarpAction)) {
            sDeferWarp = 1;
        }

        if (!gCurrCreditsEntry)
        {
            if (sHeldLButtonFrames >= 0)
            {
                if (gPlayer1Controller->buttonDown & L_TRIG)
                {
                    sHeldLButtonFrames++;

                    if (sCanLWarp)
                    {
                        if (0 == sWatchAmount || sHeldLButtonFrames > 30)
                        {
                            print_text_centered(160, 20, "HOLD L TO WARP TO POOL");
                        }

                        s32 whenToWarp = 0 == sWatchAmount ? 50 : 80;
                        if (sHeldLButtonFrames > whenToWarp)
                        {
                            sHeldLButtonFrames = -1;
                        }
                    }
                }
                else
                {
                    sHeldLButtonFrames = 0;
                }
            }
            else
            {
                // zapped till frames are reset because warp condition occured
            }
        }

        if (gCurrAreaIndex == 1) {//present
            sGearRotation += 0x200;
        } else {//future
        }
    }

}

void rovert_hud(void) {
    if (gCurrLevelNum == LEVEL_ROVERT) {

        //Render "Blink"
        if (sTimeWarpTransition > 1.0f) {
            create_dl_translation_matrix(MENU_MTX_PUSH, 0.0f, 240.0f, 0.0f);
            create_dl_scale_matrix(MENU_MTX_NOPUSH, 4.0f, 4.0f, 1.0f);

            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, (u8)sTimeWarpTransition);
            gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);

            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            sTimeWarpTransition *= 0.8f;
        }


        //Render Watch
        create_dl_translation_matrix(MENU_MTX_PUSH, 20.0f, 20.0f, 0.0f);

        gDPSetEnvColor(gDisplayListHead++, 255,255,255,100);
        gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, sWatchDL_List[sWatchAmount]);

        gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    }
}

void rovert_fluxium_pool(void) {
    if ((gCurrentObject->oDistanceToMario < 400.0f)&&(gCurrentObject->oPosY>gMarioState->pos[1])) {
        if (sWatchAmount != 4 || !sCanLWarp) {
            sWatchAmount = 4;
            play_sound(SOUND_MENU_EXIT_PIPE,gMarioState->marioObj->header.gfx.cameraToObject);
        }
        sCanLWarp = 1;
        sLastVisitedPool[0] = o->oPosX;
        sLastVisitedPool[1] = o->oPosY;
        sLastVisitedPool[2] = o->oPosZ;
    }
}

void rovert_gear(void) {
    if (gCurrentObject->oBehParams2ndByte % 2 == 0) {
        gCurrentObject->oFaceAngleRoll = sGearRotation;
    } else {
        gCurrentObject->oFaceAngleRoll = -sGearRotation;
    }
}

extern u8 gDeathFloorBarrier;
void rovert_l_warp(void) {
    if (0 == sLWarpAction)
    {
        if (sHeldLButtonFrames == -1 || gDeathFloorBarrier)
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
            sLWarpAction = 1;
        }
        // top conditonal
        if (sLastVisitedPool[1] > 9466.f && gMarioStates->pos[2] < -8800.f && (6000.f < gMarioStates->pos[1] && gMarioStates->pos[1] < 7000.f))
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
            sLWarpAction = 1;
        }
#if 0
        if (gMarioStates->pos[1] < o->oPosY)
        {
        }
        else
        {
            if (floor && gMarioStates->floorHeight == gMarioStates->pos[1] && (floor->type == SURFACE_NOT_SLIPPERY || floor->type == 0))
            {
                u32 rbTimer = rb->timer % 8;
                rb->positions[rbTimer].x = gMarioStates->pos[0];
                rb->positions[rbTimer].y = gMarioStates->pos[1];
                rb->positions[rbTimer].z = gMarioStates->pos[2];
                rb->timer++;
            }
        }
#endif
    }
    else
    {
        sLWarpAction++;
        if (sLWarpAction == 14)
        {
            gMarioStates->pos[0] = sLastVisitedPool[0];
            gMarioStates->pos[1] = sLastVisitedPool[1] + 30.f;
            gMarioStates->pos[2] = sLastVisitedPool[2];
            gMarioStates->vel[0] = 0;
            gMarioStates->vel[1] = 0;
            gMarioStates->vel[2] = 0;
            gMarioStates->forwardVel = 0;
            if (gMarioStates->action == ACT_SQUISHED)
            {
                gMarioStates->actionState = 2;
            }
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
        }
        if (sLWarpAction == 15)
        {
            reset_camera(gCamera);
        }
        if (sLWarpAction == 16)
        {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0,0,0);
            sLWarpAction = 0;
            sHeldLButtonFrames = 0;
            gDeathFloorBarrier = 0;
        }
    }
}
