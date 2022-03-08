// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Добавление предмета в инвентарь
bool UInventoryComponent::AddItem(FItemInfo NewItem)
{
	if (ItemArray.Num() < MaxItemCount)
	{

		ItemArray.Add(NewItem);
		CanBeChased.Broadcast(false);
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

//Выкидывание предмета из инвентаря
void UInventoryComponent::RemoveItem(int32 ItemIndex)
{
	if (ItemArray.Num() > 0)
	{
		ItemArray.RemoveAt(ItemIndex);
	}

	if (ItemArray.Num()<1)
	{
		CanBeChased.Broadcast(true);
	}
	else
	{
		CanBeChased.Broadcast(false);
	}

}



