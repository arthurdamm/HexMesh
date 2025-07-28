#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ISMHexAnimator.generated.h"

USTRUCT()
struct FHexInstanceAnimation
{
	GENERATED_BODY()

	int32 InstanceIndex = -1;
	FVector Start;
	FVector End;
	float ElapsedTime = 0.f;
	float Duration = 1.f;
};

UCLASS()
class HEXMESH_API UISMHexAnimator : public UObject
{
	GENERATED_BODY()

public:
	void Init(UInstancedStaticMeshComponent* InISM, float InHexSize);
	void Tick(float DeltaTime);
	void AnimateToAxial(int32 InstanceIndex, const FIntPoint& FromQR, const FIntPoint& ToQR, float Duration = 1.f);

private:
	TArray<FHexInstanceAnimation> Animations;
	UInstancedStaticMeshComponent* ISM = nullptr;
	float HexSize = 100.f;

	FVector HexToWorld(const FIntPoint& Axial) const;
};
