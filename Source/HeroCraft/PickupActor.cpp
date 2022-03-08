// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "InventoryComponent.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&APickupActor::CollisionSphereBeginOverlap);
	CollisionSphere->OnComponentHit.AddDynamic(this, &APickupActor::CollisionSphereHit);
	
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetGenerateOverlapEvents(false);
	CollisionSphere->SetCollisionProfileName("ItemDrop");

	CollisionSphere->SetSimulatePhysics(true);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetupAttachment(RootComponent);

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Bill Board"));
	Billboard->SetupAttachment(RootComponent);


	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	ParticleComp->SetVisibility(false);
	ParticleComp->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	ItemInit();
}


// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CollisionSphere->AddWorldRotation(FRotator(0,1,0));
}

void APickupActor::ItemInit()
{

	if (RowHandle.DataTable && RowHandle.RowName!=NAME_None)
	{
		ItemInfo = *RowHandle.DataTable->FindRow<FItemInfo>(RowHandle.RowName, "");
	}
	
	if (ItemInfo.StaticMesh)
	{
		MeshComp->SetStaticMesh(ItemInfo.StaticMesh);
	}

	if (ItemInfo.ParticleOnGround)
	{
		ParticleComp->SetTemplate(ItemInfo.ParticleOnGround);
	}
}



void APickupActor::ItemGetThrown(FItemInfo ItemInfoThrow)
{
	ItemInfo = ItemInfoThrow;
	ItemInit();
}

void APickupActor::CollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	
	UInventoryComponent* ActorInventory = Cast<UInventoryComponent>(OtherActor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (ActorInventory)
	{
		if (ItemInfo.StaticMesh)
		{
			if (ActorInventory->AddItem(ItemInfo))
			{
				this->Destroy();
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("NO SCACE!"));
				}
			}
		}
		
	}
	
}

void APickupActor::CollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ParticleComp->SetVisibility(true);
	CollisionSphere->SetGenerateOverlapEvents(true);
	CollisionSphere->SetWorldRotation(FRotator(0));
	CollisionSphere->SetWorldLocation(Hit.Location + FVector(0,0,50));
	CollisionSphere->SetSimulatePhysics(false);
}

