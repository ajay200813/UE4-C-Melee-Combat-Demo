#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	TCHAR const * const target_location = TEXT("TargetLocation");
	TCHAR const * const player_distance = TEXT("DistanceFromPlayer");
	TCHAR const * const is_in_melee_range = TEXT("PlayerIsInMeleeRange");
	TCHAR const * const is_in_jump_range = TEXT("PlayerIsInJumpRange");
	TCHAR const * const player_dead = TEXT("PlayerIsDead");
}