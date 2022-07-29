// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_ShootingComponent.h"

#include "FS_Projectile.h"
#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "ForeignSea/Characters/FS_GenericPawn.h"


// Sets default values for this component's properties
UFS_ShootingComponent::UFS_ShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFS_ShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<AFS_GenericPawn>(GetOwner());
}

void UFS_ShootingComponent::StartFiring()
{
	PlayerWantToShoot = true;
	TRACE_SCREEN(1,"player want to shoot !");
	TRACE("shoot !");
}

void UFS_ShootingComponent::StopFiring()
{
	PlayerWantToShoot = false;
	TRACE_SCREEN(1,"stop shooting !");
	TRACE("stop shoot !");
}


void UFS_ShootingComponent::SpawnProjectile()
{
	//todo Faire un actor component avec un ou plusieurs shoot point ?
	//check(ShootingPoint);

	// auto* Projectile = GetWorld()->SpawnActor<AFS_Projectile>(ProjectyleClass,GetComponentLocation(), GetComponentRotation());
	FTransform SpawnTransform; //création d'un transform
	SpawnTransform.SetLocation(GetComponentLocation());
	SpawnTransform.SetRotation(GetComponentRotation().Quaternion());
	//on commence le spawning
	auto* Projectile = GetWorld()->SpawnActorDeferred<AFS_Projectile>(ProjectyleClass, SpawnTransform);
	Projectile->ShootingPawn = Pawn; //ça nous laisse le temps de set cette variable
	Projectile->FinishSpawning(SpawnTransform); //on finalise le spawn
}

// Called every frame
void UFS_ShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//pour le délai entre les tirs
	TimerShootDelay += DeltaTime;

	//si on est en dessous du timer on peut tirer
	if (CanShoot && PlayerWantToShoot)
	{
		SpawnProjectile();
		CanShoot = false;
		TimerShootDelay = 0; //permet de ne pas avoir un écart plus court entre la 1ere et 2eme bullet 
	}
	
	if (TimerShootDelay > ShootingSpeed) //il faut attrendre le rechargement
	{
		CanShoot = true;
		TimerShootDelay = 0;
	}
}
