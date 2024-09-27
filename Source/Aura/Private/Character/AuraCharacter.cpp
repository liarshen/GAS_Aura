// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"

AAuraCharacter::AAuraCharacter()
{
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	MyCamera->SetupAttachment(MySpringArm);

	MySpringArm->SetRelativeRotation(FRotator(-45.f, 0, 0));
	MySpringArm->TargetArmLength = 750.f;

	// 摄像机不会从它所附加的对象那里继承俯仰角度
	MySpringArm->bInheritPitch = false;
	MySpringArm->bInheritRoll = false;
	MySpringArm->bInheritYaw = false;

	//使得角色的朝向会根据其移动方向自动调整
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// 这个函数在角色被一个新的控制器（Controller）控制时被调用。
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//从服务端server初始化ability actor info
	InitAbilityActorInfo();

}

// 它在角色的玩家状态属性通过网络复制到客户端时被调用。
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//从客户端client初始化ability actor info
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
