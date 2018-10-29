#pragma once

#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 

#define GAME_WIDTH 640
#define GAME_HEIGHT 480
#define FULLSCREEN false
#define CLASS_NAME_GAME "Castle Vania"
#define GAME_TITLE "Castle Vania"
#define FRAME_RATE 30
#define FPS	60
#define EARTH_ACCELERATION -2000
#define SPEED 150

//sprite
#define SIMON_SPRITE "Resource\\sprites\\Simon\\Simon_ver_editted.png"
#define CASTLE_SPRITE "Resource\\sprites\\Castle-lv1.png"
#define NULL_SPRITE "Resource\\sprites\\Ground\\NULL.png"
#define GROUND "Resource\\sprites\\Ground\\0.png"
#define SIMON_SPRITE "Resource\\sprites\\Simon\\Simon_ver_editted.png"
#define HELICOPTER_SPRITE "Resource\\sprites\\helicopter.png"
#define DEAD_SPRITE "Resource\\sprites\\Effect\\DEAD.png"
#define COLLIDER_EFFECT_SPRITE "Resource\\sprites\\Effect\\0.png"
#define DOOR_SPRITE	"Resource\\sprites\\Ground\\Door.png"

//BG
#define LEVEL_ONE_BG "Resource\\sprites\\lv1.s"
#define LEVEL_ONE_MATRIX_BG "Resource\\sprites\\lv1.b"
#define INTRO_SCENE_BG "Resource\\sprites\\intro.s"
#define INTRO_SCENE_MATRIX_BG "Resource\\sprites\\intro.b"



//
#define TAG_NULL -100
#define TAG_CHANGE_STATE -1
#define TAG_WALL 0
#define TAG_GROUND 12
#define TAG_SIMON 31
#define TAG_DOOR 20

//ANIMAtion
#define MOVE 1
#define STAND_BACK 19
#define STAND 0
#define SIT 2
#define HIT_SIT 5
#define HIT_STAND 4
#define HIT_UP_STAIR 14
#define HIT_DOWN_STAIR 15
#define JUMP 3
#define DEAD 16
#define INVISIBLE 17
#define HURTED 9
#define JUMP_FORCE 570
#define STANDING_UP 10
#define STANDING_DOWN 11

//STATE
#define GAME_PLAY_STATE_ONE 1
#define GAME_INTRO_SCENE 0
#define GAME_MENU_STATE -1
