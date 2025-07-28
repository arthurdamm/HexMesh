// HexISMUtils.h
#pragma once
#include "Components/InstancedStaticMeshComponent.h"

namespace GameISMUtils
{

  constexpr int DEFAULT_NUM_CUSTOM_DATA_FLOATS = 5;
  
  inline float GetPerInstanceCustomData(
    const UInstancedStaticMeshComponent* ISM,
    int32 InstanceIndex,
    int32 CustomDataIndex)
  {
    if (!ISM) return 0.f;
    const int32 FlatIndex = InstanceIndex * ISM->NumCustomDataFloats + CustomDataIndex;
    return ISM->PerInstanceSMCustomData.IsValidIndex(FlatIndex)
         ? ISM->PerInstanceSMCustomData[FlatIndex]
         : 0.f;
  }
}