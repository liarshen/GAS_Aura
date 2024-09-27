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

	// �����������������ӵĶ�������̳и����Ƕ�
	MySpringArm->bInheritPitch = false;
	MySpringArm->bInheritRoll = false;
	MySpringArm->bInheritYaw = false;

	//ʹ�ý�ɫ�ĳ����������ƶ������Զ�����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// ��������ڽ�ɫ��һ���µĿ�������Controller������ʱ�����á�
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//�ӷ����server��ʼ��ability actor info
	InitAbilityActorInfo();

}

// ���ڽ�ɫ�����״̬����ͨ�����縴�Ƶ��ͻ���ʱ�����á�
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//�ӿͻ���client��ʼ��ability actor info
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
