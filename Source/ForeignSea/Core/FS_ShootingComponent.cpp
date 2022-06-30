// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_ShootingComponent.h"

#include "FS_Projectile.h"
#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"


// Sets default values for this component's properties
UFS_ShootingComponent::UFS_ShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFS_ShootingComponent::Fire()
{
	TRACE_SCREEN("Fire !");
	SpawnProjectile();
}


// Called when the game starts
void UFS_ShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UFS_ShootingComponent::SpawnProjectile()
{
	// check(ShootingPoint);

	auto* Projectile = GetWorld()->SpawnActor<AFS_Projectile>(ProjectyleClass,GetComponentLocation(), GetComponentRotation());

	
}

// Called every frame
void UFS_ShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
