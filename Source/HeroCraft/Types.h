// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystemComponent.h"
#include "Types.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* ParticleOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Icon")
		UTexture2D* ItemIcon = nullptr;

};

UCLASS()
class HEROCRAFT_API UTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
