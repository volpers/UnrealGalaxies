#pragma once

#include "Runtime/AssetRegistry/Public/AssetData.h"
#include <map>

using namespace std;

namespace EMeshType {
	enum Type {
		StaticMesh,
		PrimitiveMesh,
		SkeletalMesh
	};
}

class AssetManager {
	public:
	AssetManager();
	~AssetManager();

	template <typename AssetType>
	static FORCEINLINE void CreateObjectLibrary(const EMeshType::Type type,
		const FString path) 
	{
		UObjectLibrary* lib = UObjectLibrary::CreateLibrary(AssetType::StaticClass(), false, true);
		lib->LoadAssetDataFromPath(path);
		lib->AddToRoot();
		objectLibs[type] = lib;
	}
	static UObject* LoadAsset(UObjectLibrary* lib, const FName name);
	static map<EMeshType::Type, UObjectLibrary*>& GetObjectLibraries();

	private:
	static map<EMeshType::Type, UObjectLibrary*> objectLibs;

};

