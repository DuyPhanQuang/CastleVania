
#define SAFE_DELETE(p) {if(p) { delete(p); p = NULL;} } 

#define GAME_WIDTH 640
#define GAME_HEIGHT 480
#define GAME_FONT "Resource\\font\\prstart.ttf"
#define FULLSCREEN false
#define CLASS_NAME_GAME "Castle Vania"
#define GAME_TITLE "Castle Vania"
#define FRAME_RATE 30
#define FPS	60
#define EARTH_ACCELERATION -2000
#define SPEED 150
#define MAX_TIME_PER_FRAME	1000 / FPS

//sprite
#define SIMON_SPRITE "Resource\\sprites\\Simon\\Simon_ver_editted.png"
#define CASTLE_SPRITE "Resource\\sprites\\Castle-lv1.png"
#define NULL_SPRITE "Resource\\sprites\\Ground\\NULL.png"
#define GROUND "Resource\\sprites\\Ground\\0.png"
#define GROUND_2 "Resource\\sprites\\Ground\\2.png"
#define SIMON_SPRITE "Resource\\sprites\\Simon\\Simon_ver_editted.png"
#define HELICOPTER_SPRITE "Resource\\sprites\\helicopter.png"
#define DEAD_SPRITE "Resource\\sprites\\Effect\\DEAD.png"
#define COLLIDER_EFFECT_SPRITE "Resource\\sprites\\Effect\\0.png"
#define DOOR_SPRITE	"Resource\\sprites\\Ground\\Door.png"
#define BAT_SPRITE "Resource\\sprites\\bat.png"

//BG
#define LEVEL_ONE_BG "Resource\\sprites\\lv1.s"
#define LEVEL_ONE_MATRIX_BG "Resource\\sprites\\lv1.b"
#define INTRO_SCENE_BG "Resource\\sprites\\intro.s"
#define INTRO_SCENE_MATRIX_BG "Resource\\sprites\\intro.b"

//Header
#define HEADER_BLACK "Resource\\sprites\\UI\\black.png"
#define HEADER_SIMON_HP "Resource\\sprites\\UI\\HP.png"
#define HEADER_ENEMY_HP "Resource\\sprites\\UI\\EnemyHP.png"
#define HEADER_HEART "Resource\\sprites\\UI\\Heart.png"
#define HEADER_HOLY_WATER "Resource\\sprites\\UI\\HOLY_WATER.png"
#define HEADER_CROSS "Resource\\sprites\\UI\\CROSS.png"
#define HEADER_STOPWATCH  "Resource\\sprites\\UI\\STOP_WATCH.png"
#define HEADER_UPGRADE1 "Resource\\sprites\\UI\\DOUBLE_SHOOT_UI.png"
#define HEADER_UPGRADE2 "Resource\\sprites\\UI\\TRIPLE_SHOOT_UI.png"

//
#define TAG_NULL -100
#define TAG_CHANGE_STATE -1
#define TAG_WALL 0
#define TAG_GROUND 12
#define TAG_SIMON 31
#define TAG_DOOR 20
#define TAG_BAT 4
#define TAG_CHECK_POINT 21

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
