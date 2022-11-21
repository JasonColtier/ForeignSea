// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_Projectile.h"
#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "Components/CapsuleComponent.h"
#include "ForeignSea/Characters/FS_EnemyPawn.h"
#include "ForeignSea/Characters/FS_GenericPawn.h"

// Sets default values
AFS_Projectile::AFS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	//Attaching
	RootComponent = Mesh;
	CapsuleComponent->SetupAttachment(Mesh);

	//binding overlaps
	this->OnActorBeginOverlap.AddDynamic(this,&AFS_Projectile::OnBeginOverlap);
	
}

// Called when the game starts or when spawned
void AFS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TimeCounter += DeltaTime;

	//au bout de X sec on détruit le projectile
	//Todo : réincarnation ?
	if(TimeCounter > LifeTime)
	{
		Destroy();
	}

	//déplacement de notre projectile
	AddActorWorldOffset(GetActorForwardVector()*BaseSpeed,true);

}

void AFS_Projectile::OnBeginOverlap(AActor* SelfActor, AActor* OtherActor)
{
	//si ce n'est pas un enemy pour l'instant on passe au travers
	if(!OtherActor->IsA(AFS_EnemyPawn::StaticClass()))
		return;
	
	// TRACE_SCREEN("HIT Enemy !");

	//damage basique
	FDamageEvent DamageEvent;
	//on inflige les dégats à l'enemy
	OtherActor->TakeDamage(BaseDamage,DamageEvent,ShootingPawn->GetController(),ShootingPawn);
	
	Destroy();
}

