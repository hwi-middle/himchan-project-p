// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 사운드 파일 명 확정되지 않은 것은 "SC_TestSound" 사용
#define TEST_SOUND "SC_TestSound"

// UI 애니메이션 관련
// 버튼의 경우 Widget BP에서 직접 설정함.
#define WIDGET_MOVE_SOUND "SC_TestSound"
#define WIDGET_OPEN_SOUND "SC_TestSound"
#define WIDGET_CLOSE_SOUND "SC_TestSound"

// 총기 관련
#define GUN_FIRE_SOUND "SC_TestSound"
#define GUN_GRAB_ON_HAND_SOUND "SC_TestSound"
#define GUN_COOLDOWN_SOUND "SC_TestSound"
#define GUN_OVERHEAT_SOUND "SC_TestSound"
#define GUN_TOGGLE_FLASH_SOUND "SC_TestSound"

// 플레이어 관련
// 이동에 애님 노티파이를 쓰지 못하므로 함수 내 호출로 대체
#define PLAYER_HIT_SOUND "SC_TestSound"
#define PLAYER_WALK_SOUND "SC_TestSound"
#define PLAYER_SPRINT_SOUND "SC_TestSound"

// 커맨더 관련
// 튜토리얼 트리거 사운드는 트리거 액터에서 따로 관리 하는 것으로 합니다.
#define COMMANDER_TYPING_SOUND "SC_TestSound"
#define COMMANDER_RADIO_SOUND "SC_TestSound"
#define COMMANDER_HEALTH_WARING_SOUND "SC_TestSound"

// 커맨더 보스 관련 경고
#define COMMANDER_BOSS_VISIT_SOUND "SC_TestSound"
#define COMMANDER_BOSS_VG_SOUND "SC_TestSound"
#define COMMANDER_BOSS_LT_SOUND "SC_TestSound"
#define COMMANDER_BOSS_GF_SOUND "SC_TestSound"
#define COMMANDER_BOSS_TW_SOUND "SC_TestSound"

// 보스 관련.
// 일단은 선언만 해놓고 애님 노티파이로 빠지는 것들은 주석처리
// VG = 덩굴정원, LT = 리프 템페스트, GF = 녹빛안개, TW = 가시채찍
#define BOSS_VG_OMEN_SOUND "SC_TestSound"
#define BOSS_VG_SPAWN_SOUND "SC_TestSound"
#define BOSS_LT_OMEN_SOUND "SC_TestSound"
#define BOSS_LT_SPAWN_SOUND "SC_TestSound"
#define BOSS_LT_EXPLODE_SOUND "SC_TestSound"
#define BOSS_GF_OMEN_SOUND "SC_TestSound"
#define BOSS_GF_SPAWN_SOUND "SC_TestSound"
#define BOSS_TW_OMEN_SOUND "SC_TestSound"
#define BOSS_TW_SPAWN_SOUND "SC_TestSound"
#define BOSS_TW_SWING_SOUND "SC_TestSound"

// 기믹 관련
// BP 인스턴스로 관리하거나 애님노티파이로 빠지는 것들은 주석처리
#define GIMMICK_DOOR_OPEN_SOUND "SC_TestSound"
#define GIMMICK_GLASS_DESTROY_SOUND "SC_TestSound"