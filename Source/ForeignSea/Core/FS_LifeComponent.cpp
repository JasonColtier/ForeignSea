// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_LifeComponent.h"

#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"

// Sets default values for this component's properties
UFS_LifeComponent::UFS_LifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFS_LifeComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UFS_LifeComponent::OnOwnerTakeDamage);
}


// Called every frame
void UFS_LifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFS_LifeComponent::OnOwnerTakeDamage(AActor* DamagedActor, float Damage,const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	TRACE_SCREEN(1,"owner got damaged for %f",Damage);
	GetOwner()->Destroy(); 
}
