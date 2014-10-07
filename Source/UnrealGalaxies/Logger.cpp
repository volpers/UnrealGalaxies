#include "UnrealGalaxies.h"
#include "Logger.h"


void Logger::Print(string text) {
	FString s = FString(text.c_str());
	UE_LOG(LogTemp, Log, TEXT("%s"), *s);
}

void Logger::Print(double number) {
	FString s = FString::SanitizeFloat(number);
	UE_LOG(LogTemp, Log, TEXT("%s"), *s);
}

void Logger::Print(int32 number) {
	FString s = FString::FromInt(number);
	UE_LOG(LogTemp, Log, TEXT("%s"), *s);

}

void Logger::Print(FVector vec) {
	UE_LOG(LogTemp, Log, TEXT("X: %f , Y: %f , Z: %f "), vec.X, vec.Y, vec.Z);
}
