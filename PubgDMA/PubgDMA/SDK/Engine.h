#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

struct ItemInfo {
    UEVector position;
    std::string label;
};

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActor;
	int MaxPacket;
	int localTempId;
	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo
	std::vector<std::shared_ptr<ActorEntity>> Actors;
	std::vector<ItemInfo> Items;

	uint64_t UWorld, CurrentLevel, GameInstance, LocalPlayers, PlayerController, AcknowledgedPawn, PlayerCameraManager, GNames;

public:
	Engine();
	inline bool InitDecrypt(uint64_t offset);
	void Cache();
	void CacheItems();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	std::vector<ItemInfo> GetItems();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	uint64_t GetActorSize();
	uintptr_t xe_decrypt(const uintptr_t encrypted);
	DWORD DecryptCIndex(DWORD Encrypted);
	void GetGNames();
	std::string GetNames(DWORD ID);
};