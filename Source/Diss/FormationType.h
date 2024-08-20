// Oliver Perrin c3043508@newcastle.ac.uk

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFormationType : uint8
{
	LINE UMETA(DisplayName = "Line Formation"),
	SQUARE UMETA(DisplayName = "Square Formation"),
	DIAMOND UMETA(DisplayName = "Diamond Formation"),
};