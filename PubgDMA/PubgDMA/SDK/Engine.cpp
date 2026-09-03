#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"
#include "Globals.h"
#include <codecvt>
#include <locale>
Engine::Engine()
{

	if (InitDecrypt(SDK.Decrypt)) {

		uintptr_t base_data = TargetProcess.GetBaseAddress(ProcessName);
		uintptr_t uworld_raw = TargetProcess.Read<uintptr_t>(base_data + SDK.UWorld);
		UWorld = xe_decrypt(uworld_raw);
		CurrentLevel = xe_decrypt(TargetProcess.Read<uint64_t>(UWorld + SDK.CurrentLevel));
		GameInstance = xe_decrypt(TargetProcess.Read<uint64_t>(UWorld + SDK.GameInstance));
		LocalPlayers = xe_decrypt(TargetProcess.Read<uint64_t>(TargetProcess.Read<uint64_t>(GameInstance + SDK.LocalPlayers)));
		PlayerController = xe_decrypt(TargetProcess.Read<uint64_t>(LocalPlayers + SDK.PlayerController));
		AcknowledgedPawn = xe_decrypt(TargetProcess.Read<uint64_t>(PlayerController + SDK.AcknowledgedPawn));
		PlayerCameraManager = TargetProcess.Read<uint64_t>(PlayerController + SDK.PlayerCameraManager);
		CameraEntry.POV.FOV = TargetProcess.Read<float>(PlayerCameraManager + SDK.CameraFov);
		CameraEntry.POV.Location = TargetProcess.Read<UEVector>(PlayerCameraManager + SDK.CameraPos);
		CameraEntry.POV.Rotation = TargetProcess.Read<UERotator>(PlayerCameraManager + SDK.CameraRot);
#ifdef _DEBUG
		printf("base_data       = 0x%llx\n", base_data);
		printf("GWorld          = 0x%llx\n", UWorld);
		printf("PersistentLevel = 0x%llx\n", CurrentLevel);
		printf("GameInstance    = 0x%llx\n", GameInstance);
		printf("LocalPlayers    = 0x%llx\n", LocalPlayers);
		printf("PlayerCtrl      = 0x%llx\n", PlayerController);
		printf("AckPawn         = 0x%llx\n", AcknowledgedPawn);
		printf("CameraManager   = 0x%llx\n", PlayerCameraManager);
#endif
		GetGNames();
	}
}


typedef int64_t(__fastcall* DecryptFunctoin)(uintptr_t key, uintptr_t argv);
inline DecryptFunctoin fnDecryptFunctoin = NULL;
inline uint64_t Tmpadd;
inline bool Engine::InitDecrypt(uint64_t offset)
{
	uintptr_t DecryptPtr = TargetProcess.Read<uintptr_t>(TargetProcess.GetBaseAddress(ProcessName) + offset);
	while (!DecryptPtr)
	{
		DecryptPtr = TargetProcess.Read<uintptr_t>(TargetProcess.GetBaseAddress(ProcessName) + offset);
		Sleep(1000);
	}
	int32_t Tmp1Add = TargetProcess.Read<int32_t>(DecryptPtr + 3);
	Tmpadd = Tmp1Add + DecryptPtr + 7;
#ifdef _DEBUG
	printf("DecryptPtr = %p  Tmpadd = 0x%llx\n", DecryptPtr, Tmpadd);
#endif
	unsigned char ShellcodeBuff[1024] = { NULL };
	ShellcodeBuff[0] = 0x90;
	ShellcodeBuff[1] = 0x90;
	VMMDLL_MemReadEx(TargetProcess.vHandle, TargetProcess.ReturnPid(), DecryptPtr, &ShellcodeBuff[2], sizeof(ShellcodeBuff) - 2, NULL, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOCACHEPUT | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO | VMMDLL_FLAG_NOPAGING);
	ShellcodeBuff[2] = 0x48;
	ShellcodeBuff[3] = 0x8B;
	ShellcodeBuff[4] = 0xC1;
	ShellcodeBuff[5] = 0x90;
	ShellcodeBuff[6] = 0x90;
	ShellcodeBuff[7] = 0x90;
	ShellcodeBuff[8] = 0x90;
	void* mem = VirtualAlloc(NULL, sizeof(ShellcodeBuff) + 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	RtlCopyMemory(mem, ShellcodeBuff, sizeof(ShellcodeBuff));
	DWORD oldProt;
	VirtualProtect(mem, sizeof(ShellcodeBuff) + 4, PAGE_EXECUTE_READ, &oldProt);
	fnDecryptFunctoin = (DecryptFunctoin)mem;
	return 1;
}
inline uintptr_t Engine::xe_decrypt(const uintptr_t encrypted)
{
	uintptr_t data = fnDecryptFunctoin(Tmpadd, encrypted);
	return data;
}
// DecryptCIndex
auto _SHL_(auto value, auto x) {
	return value << x;
}
auto _XOR_(auto a, auto b) {
	return a ^ b;
}

auto _ROR_(auto value, auto steps) {
	steps %= 32;
	return (value << steps) | (value >> (32 - steps));
}

auto _ROL_(auto value, auto steps) {
	steps %= 32;
	return (value >> steps) | (value << (32 - steps));
}
DWORD Engine::DecryptCIndex(DWORD Encrypted)
{
	int _TableOne = SDK.NameIndexOne;
	int _TableTwo = SDK.NameIndexTwo;
	uint64_t _DecryptOne = SDK.NameIndexXor1;
	uint64_t _DecryptTwo = SDK.NameIndexXor2;
	if (SDK.NameIsROR == 3) return _XOR_(_XOR_(_SHL_(Encrypted, _TableTwo), _DecryptTwo), Encrypted);
	if (SDK.NameIsROR == 1) {
		const DWORD xored = _XOR_(Encrypted, static_cast<DWORD>(_DecryptOne));
		return (((xored >> 14) & 0x000F0000u) | (xored << 18))
		     ^ _ROR_(xored, _TableOne)
		     ^ static_cast<DWORD>(_DecryptTwo);
	}
	Encrypted = _ROL_(_XOR_(Encrypted, _DecryptOne), _TableOne);
	return _XOR_(_XOR_(_SHL_(Encrypted, _TableTwo), _DecryptTwo), Encrypted);
}
std::wstring string_to_wstring(const std::string& str) {
	std::wstring ws(str.begin(), str.end());
	return ws;
}
bool contains(const std::string& haystack, const std::string& needle) {
	return haystack.find(needle) != std::string::npos;
}
void Engine::Cache()
{

	OwningActor = xe_decrypt(TargetProcess.Read<uint64_t>(CurrentLevel + SDK.Actors));
	AcknowledgedPawn = xe_decrypt(TargetProcess.Read<uint64_t>(PlayerController + SDK.AcknowledgedPawn));
	Local.Teamid = TargetProcess.Read<uint64_t>(AcknowledgedPawn + SDK.LastTeamNum);
	Local.SpectatedCount = TargetProcess.Read<uint64_t>(AcknowledgedPawn + SDK.SpectatedCount);
	MaxPacket = TargetProcess.Read<int>(OwningActor + 8);
#ifdef _DEBUG
	printf("Actor Array: %p  Size: %d\n", OwningActor, MaxPacket);
#endif
	if (MaxPacket == 0) {
		return;
	}

	OwningActor = TargetProcess.Read<uint64_t>(OwningActor);
	std::vector<uint64_t> entitylist;
	entitylist.resize(MaxPacket);
	std::unique_ptr<uint64_t[]> object_raw_ptr = std::make_unique<uint64_t[]>(MaxPacket);
	TargetProcess.Read(OwningActor, object_raw_ptr.get(), MaxPacket * sizeof(uint64_t));
	for (size_t i = 0; i < MaxPacket; i++)
	{
		entitylist[i] = object_raw_ptr[i];
	}
	std::list<std::shared_ptr<ActorEntity>> actors;
	auto handle = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (actor == AcknowledgedPawn)
			continue;
		if (!actor)
			continue;
		std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, handle);
		actors.push_back(entity);
		
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);


	handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		if (entity->RootComponent) {
			entity->isCheck = true;
		}
		entity->SetUp1(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);

	handle = TargetProcess.CreateScatterHandle();
	std::vector<std::shared_ptr<ActorEntity>> playerlist;
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp2(handle);

	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		entity->SetUp3();
		if (entity->Head3D.X == 0 && entity->Head3D.Y == 0 && entity->Head3D.Z)
			continue;
		playerlist.push_back(entity);
	}
	Actors = playerlist;
	CacheItems();
}
void Engine::GetGNames()
{
	GNames = xe_decrypt(TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress(ProcessName)+ SDK.GNames));
	GNames = xe_decrypt(TargetProcess.Read<uint64_t>(GNames + SDK.GNames_offset));
}
typedef struct StringA
{
	char buffer[1024];
};
std::string Engine::GetNames(DWORD ID)
{
	std::string emp = "Unknown";
	if (ID <= 0) return emp;
	uint32_t IdDiv = ID / SDK.ElementsPerChunk;
	uint32_t Idtemp = ID % SDK.ElementsPerChunk;
	uint64_t Serial = TargetProcess.Read<uint64_t>(GNames + IdDiv * 0x8);
	if (!Serial || Serial < 0x100000)
		return emp;
	uint64_t pName = TargetProcess.Read<uint64_t>(Serial + 0x8 * Idtemp);
	if (!pName || pName < 0x100000)
		return emp;

	StringA names = TargetProcess.Read<StringA>(pName + 0x10);
	char te[256];
	memset(&te, 0, 256);
	if (memcmp(names.buffer, te, 256) == 0)
		return emp;

	std::string str(names.buffer);
	return str;
}
void Engine::UpdatePlayers()
{
	auto handle = TargetProcess.CreateScatterHandle();
	for (std::shared_ptr<ActorEntity> entity : Actors)
	{

		entity->UpdateBone(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	for (std::shared_ptr<ActorEntity> entity : Actors)
	{

		entity->SetUp3();
	}
}


void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, PlayerCameraManager + SDK.CameraFov, reinterpret_cast<void*>(&CameraEntry.POV.FOV), sizeof(float));
	TargetProcess.AddScatterReadRequest(handle, PlayerCameraManager + SDK.CameraPos, reinterpret_cast<void*>(&CameraEntry.POV.Location), sizeof(UEVector));
	TargetProcess.AddScatterReadRequest(handle, PlayerCameraManager + SDK.CameraRot,reinterpret_cast<void*>(&CameraEntry.POV.Rotation),sizeof(UERotator));
}

CameraCacheEntry Engine::GetCameraCache()
{
	return CameraEntry;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetActors()
{
	return Actors;
}

uint64_t Engine::GetActorSize()
{
	return MaxPacket;
}

std::vector<ItemInfo> Engine::GetItems()
{
	return Items;
}

void Engine::CacheItems()
{
	Items.clear();
	if (!OwningActor || MaxPacket <= 0 || MaxPacket > 5000)
		return;

	std::vector<uint64_t> actorList(MaxPacket);
	TargetProcess.Read(OwningActor, actorList.data(), MaxPacket * sizeof(uint64_t));

	// Scatter-read Mesh and RootComponent for every non-null actor
	std::vector<uint64_t> meshPtrs(MaxPacket, 0);
	std::vector<uint64_t> rootComps(MaxPacket, 0);
	std::vector<size_t> validIdx;
	validIdx.reserve(512);
	{
		auto handle = TargetProcess.CreateScatterHandle();
		for (size_t i = 0; i < (size_t)MaxPacket; i++) {
			if (!actorList[i]) continue;
			if (actorList[i] == AcknowledgedPawn) continue;
			validIdx.push_back(i);
			TargetProcess.AddScatterReadRequest(handle, actorList[i] + SDK.Mesh,
			                                   &meshPtrs[i], sizeof(uint64_t));
			TargetProcess.AddScatterReadRequest(handle, actorList[i] + SDK.RootComponent,
			                                   &rootComps[i], sizeof(uint64_t));
		}
		TargetProcess.ExecuteReadScatter(handle);
		TargetProcess.CloseScatterHandle(handle);
	}

	// Actors with no skeletal mesh but a valid root component are world items/objects
	// Player characters have Mesh >= 65535 (valid pointer); items/packages do not
	std::vector<size_t> candidates;
	candidates.reserve(256);
	for (size_t i : validIdx) {
		if (meshPtrs[i] >= 65535) continue;   // has skeletal mesh = player character, skip
		if (rootComps[i] < 0x10000) continue;  // invalid root component
		candidates.push_back(i);
	}
	if (candidates.empty())
		return;

	// Scatter-read world position for candidates
	std::vector<UEVector> positions(MaxPacket, {});
	{
		auto handle = TargetProcess.CreateScatterHandle();
		for (size_t i : candidates)
			TargetProcess.AddScatterReadRequest(handle, rootComps[i] + SDK.ComponentLocation,
			                                   &positions[i], sizeof(UEVector));
		TargetProcess.ExecuteReadScatter(handle);
		TargetProcess.CloseScatterHandle(handle);
	}

	for (size_t i : candidates) {
		auto& p = positions[i];
		if (p.X == 0.f && p.Y == 0.f && p.Z == 0.f) continue;
		Items.push_back({ p, "Loot" });
	}
}
