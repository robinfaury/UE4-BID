#include "PlayerPawn.h"
#include "Classes/Components/InputComponent.h"
#include  "Classes/Kismet/KismetSystemLibrary.h"


FORCEINLINE bool Trace(
	UWorld* World,
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Visibility,
	bool ReturnPhysMat = false
	) {
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel (
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}


// Sets default values
APlayerPawn::APlayerPawn() :
	PlayerCamera(CreateDefaultSubobject<UCameraComponent>("PlayerCamera"))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	PlayerCamera->SetupAttachment(RootComponent);

}

void APlayerPawn::MoveX(float amount)
{
	AddActorWorldRotation( FRotator::MakeFromEuler(FVector::UpVector*amount*3.0f) );
}

void APlayerPawn::MoveY(float amount)
{
	PlayerCamera->SetWorldLocation(PlayerCamera->GetComponentLocation() + GetActorForwardVector()*amount*100.0f);
}  

void APlayerPawn::MoveDownUp(float amount) 
{
	PlayerCamera->SetWorldLocation(PlayerCamera->GetComponentLocation() + FVector::UpVector*amount*100.0f);
}



// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Start = PlayerCamera->GetComponentToWorld().GetLocation();
	const FVector End = Start + PlayerCamera->GetForwardVector()*100000000.0f;

	FHitResult HitResult;

	if (Trace(GetWorld(), this, Start, End, HitResult)) 
	{
		UKismetSystemLibrary::DrawDebugSphere( GetWorld(), HitResult.Location, 10.0f, 10.0f, FColor(0, 0, 200) );
		touchedActor = HitResult.Actor;
	}
	else
	{
		touchedActor = nullptr;
	}

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ThisClass::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ThisClass::MoveY);
	PlayerInputComponent->BindAxis("MoveDownUp", this, &ThisClass::MoveDownUp);
	
}
