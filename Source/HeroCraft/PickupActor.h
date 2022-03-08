// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Types.h"
#include "Components/BillboardComponent.h"
#include "Components/ComboBoxString.h"
#include "Particles/ParticleSystemComponent.h"
#include "PickupActor.generated.h"

UENUM(BlueprintType)
enum class ItemToAppear : uint8
{
	One_Two UMETA(DisplayName = "first"),
	Two_row UMETA(DisplayName = "second")
};

UCLASS()
class HEROCRAFT_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	UPROPERTY(BlueprintReadOnly, Category = Components, VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(BlueprintReadOnly, Category = Components, VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadOnly, Category = Components, VisibleAnywhere)
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Choice")
	FDataTableRowHandle RowHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BillBoard")
	UBillboardComponent* Billboard; 

	FItemInfo ItemInfo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ItemInit();

	UFUNCTION(BlueprintCallable)
	void ItemGetThrown(FItemInfo ItemInfoThrow);


	UFUNCTION()
	void CollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& HitResult);

	UFUNCTION()
	void CollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);



};
