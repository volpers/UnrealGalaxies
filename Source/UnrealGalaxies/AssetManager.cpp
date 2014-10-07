#include "UnrealGalaxies.h"
#include "AssetManager.h"

map<EMeshType::Type, UObjectLibrary*> AssetManager::objectLibs;


AssetManager::AssetManager() {
}


AssetManager::~AssetManager() {
}

UObject* AssetManager::LoadAsset(UObjectLibrary* lib, const FName name) {
	TArray<FAssetData> assetDatas;
	lib->GetAssetDataList(assetDatas);
	for (FAssetData data : assetDatas) {
		if (data.AssetName == name) {
			//data.GetAsset()->
			return data.GetAsset();
		}
	}
	return NULL;
}

map<EMeshType::Type, UObjectLibrary*>& AssetManager::GetObjectLibraries() {
	return objectLibs;
}