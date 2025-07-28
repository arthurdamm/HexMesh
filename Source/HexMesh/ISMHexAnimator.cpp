#include "ISMHexAnimator.h"
#include "Components/InstancedStaticMeshComponent.h"

void UISMHexAnimator::Init(UInstancedStaticMeshComponent* InISM, float InHexSize)
{
	ISM = InISM;
	HexSize = InHexSize;
}

void UISMHexAnimator::Tick(float DeltaTime)
{
	if (!ISM) return;

	for (int32 i = Animations.Num() - 1; i >= 0; --i)
	{
		FHexInstanceAnimation& Anim = Animations[i];
		Anim.ElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(Anim.ElapsedTime / Anim.Duration, 0.f, 1.f);
		FVector NewPos = FMath::Lerp(Anim.Start, Anim.End, Alpha);
		FTransform NewTransform(FQuat::Identity, NewPos, FVector(1.0f));
		ISM->UpdateInstanceTransform(Anim.InstanceIndex, NewTransform, false, true);

		if (Alpha >= 1.f)
		{
			Animations.RemoveAt(i);
		}
	}
	ISM->MarkRenderStateDirty();
}

void UISMHexAnimator::AnimateToAxial(int32 InstanceIndex, const FIntPoint& FromQR, const FIntPoint& ToQR, float Duration)
{
	FHexInstanceAnimation Anim;
	Anim.InstanceIndex = InstanceIndex;
	Anim.Start = HexToWorld(FromQR);
	Anim.End = HexToWorld(ToQR);
	Anim.Duration = Duration;
	Anim.ElapsedTime = 0.f;
	Animations.Add(Anim);
}

FVector UISMHexAnimator::HexToWorld(const FIntPoint& Axial) const
{
	float X = HexSize * 3.f / 2.f * Axial.X;
	float Y = HexSize * FMath::Sqrt(3.f) * (Axial.Y + Axial.X / 2.f);
	return FVector(X, Y, 0.f);
}
