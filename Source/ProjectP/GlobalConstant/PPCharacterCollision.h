// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Character를 상속받는 객체들에 대한 충돌체 구분
// 이후 개발 과정에서 충돌체 상속 종류가 다양해진다면 상속 구분 없이 한 헤더로 통합 고려중
constexpr FName PLAYER_COLLISION_CAPSULE = FName(TEXT("PlayerCapsule"));
constexpr FName ENEMY_COLLISION_CAPSULE = FName(TEXT("EnemyCapsule"));
constexpr FName BOSS_COLLISION_BODY = FName(TEXT("BossBody"));
constexpr FName BOSS_COLLISION_CORE = FName(TEXT("BossCore"));