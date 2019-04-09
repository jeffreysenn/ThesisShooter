// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ThesisShooterCharacter.h"
#include "ThesisShooterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Public/Target.h"
#include "Public/ThesisSHooterPlayerController.h"
#include "C_ThesisGameInstance.h"
#include "Haptics/HapticFeedbackEffect_Base.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AThesisShooterCharacter

AThesisShooterCharacter::AThesisShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	bUsingGyroScope = true;
	

}

void AThesisShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	//if (bUsingGyroScope)
	//{
	//	VR_Gun->SetHiddenInGame(false, true);
	//	Mesh1P->SetHiddenInGame(true, true);ThesisGameInstance
	//}
	//else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}

	if (Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance()))
	{
		ThesisGameInstance = Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("@BeinPlay Failed to cast and assign  variable gmae instance to UC_ThesisGameInstance "));
	}

	if (Cast<AThesisSHooterPlayerController>(this->GetController()))
	{
		ThesisPlayerController = Cast<AThesisSHooterPlayerController>(this->GetController());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("@BeinPlay Failed to cast and assign  variable player controller to AThesisSHooterPlayerController "));
	}
	
}

void AThesisShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bUsingGyroScope && ThesisPlayerController)
	{
		FVector OutTilt, OutRotationRate, OutGravity, OutAcceleration;

		ThesisPlayerController->GetInputMotionState(OutTilt, OutRotationRate, OutGravity, OutAcceleration);
		AddControllerYawInput(OutRotationRate.X * -BaseGyroTurnRate);
		AddControllerPitchInput(OutRotationRate.Y * BaseGyroLookUpRate);
	}
}





//////////////////////////////////////////////////////////////////////////
// Input

void AThesisShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AThesisShooterCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThesisShooterCharacter::OnResetVR);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AThesisShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThesisShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThesisShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThesisShooterCharacter::LookUpAtRate);

}

void AThesisShooterCharacter::OnFire()
{
	// try and fire a projectile
	if (CanShoot==true) 
	{
		UWorld* const World = GetWorld();
		//Cast<APlayerController>(this->GetController())->PlayDynamicForceFeedback(0.5f,0.5f,false,true,false,true)
		if (World != NULL)
		{
			if (ThesisGameInstance != NULL)
			{


				if (FirstPersonCameraComponent != NULL)
				{
					//if (bUsingMotionControllers)
					//{
					//	const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
					//	const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
					//	//World->SpawnActor<AThesisShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
					//}
					//else
					{
						const FRotator SpawnRotation = GetControlRotation();
						// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
						const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

						//Set Spawn Collision Handling Override
						//FActorSpawnParameters ActorSpawnParams;
						//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
						FHitResult OutHit;
						FCollisionQueryParams Params;
						FCollisionResponseParams  ResponseParam;
						// Find the crosshair position in pixel coordinates
						int32 ViewportSizeX, ViewportSizeY;
						GetWorld()->GetFirstPlayerController()->GetViewportSize(ViewportSizeX, ViewportSizeY);
						auto ScreenLocation = FVector2D(ViewportSizeX / 2, ViewportSizeY / 2);

						FVector CameraWorldLocation;
						FVector LookDirection;
						// "De-project" the screen position of the crosshair to a world direction
						if (GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(
							ScreenLocation.X,
							ScreenLocation.Y,
							CameraWorldLocation,
							LookDirection
						))
						{

							if (World->LineTraceSingleByChannel(OutHit, CameraWorldLocation - LookDirection * RaySpawnLocationOffset, CameraWorldLocation + LookDirection * RayRange, ECollisionChannel::ECC_Visibility, Params, ResponseParam))
							{
								ThesisGameInstance->Shots++;

								//FColor Color = FColor(0, 0, 255);
								//DrawDebugLine(World, CameraWorldLocation - LookDirection * RaySpawnLocationOffset, CameraWorldLocation + LookDirection * RayRange, Color, false, 1.0f, 0, 4.0f);
								//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *OutHit.GetActor()->GetName());

								//OnTargetHit
								if (Cast<ATarget>(OutHit.GetActor()))
								{
									if (Cast<ATarget>(OutHit.GetActor())->bIsShootable == true)
									{
										if (ThesisGameInstance->GameSection == 0) {
											ThesisGameInstance->GameSection = 1;
										}
										ThesisGameInstance->ShotHits++;
										ThesisGameInstance->AccuracyScore += Cast<ATarget>(OutHit.GetActor())->OnTargetHit(OutHit.Location);

										if (ThesisGameInstance->GameSection == 1)
										{
											ThesisGameInstance->HitTimesFirstSectionTargets.Add(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
										}
										else if (ThesisGameInstance->GameSection == 3)
										{

										}

									}

								}

							}

						}



						// spawn the projectile at the muzzle
						//World->SpawnActor<AThesisShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					}
				}
			}
		}


		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				//AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
	else
	{
		return;
	}
		
}

void AThesisShooterCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThesisShooterCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}

	TouchItem.FingerIndex = FingerIndex;
	TouchItem.bIsPressed = true;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AThesisShooterCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (FingerIndex != TouchItem.FingerIndex)
	{
		return;
	}
	
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

void AThesisShooterCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	
		if (TouchItem.bIsPressed && (TouchItem.FingerIndex == FingerIndex))
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (FMath::Abs(ScaledDelta.X) >= 1.0 / ScreenSize.X)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTouchTurnRate;
						AddControllerYawInput(Value);
					}
					if (FMath::Abs(ScaledDelta.Y) >= 1.0 / ScreenSize.Y)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y * BaseTouchLookUpRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
}

void AThesisShooterCharacter::MoveForward(float Value)
{
	if (CanMove==true)
	{
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);
		}
	}
	
}

void AThesisShooterCharacter::MoveRight(float Value)
{
	if (CanMove==true)
	{
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorRightVector(), Value);
		}
	}
	
}

void AThesisShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThesisShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AThesisShooterCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AThesisShooterCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AThesisShooterCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AThesisShooterCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

void AThesisShooterCharacter::SetUsingGyroScope(bool bShouldUse)
{
	bUsingGyroScope = bShouldUse;
}

