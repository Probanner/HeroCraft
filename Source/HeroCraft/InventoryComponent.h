// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeChasing, bool,bCanBeChased);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROCRAFT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FItemInfo> ItemArray;

	int32 CurrentItem = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Max Item Count")
	int32 MaxItemCount = 1;

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Chasing")
	FBeChasing CanBeChased;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool AddItem(FItemInfo NewItem);
	void RemoveItem(int32 ItemIndex);

};
