#pragma once
#include "Engine.h"
extern std::shared_ptr<Engine> EngineInstance;
extern std::string ProcessName;

struct _Local
{
    int Teamid;
    int SpectatedCount;
} inline Local;

struct OFFSET {// ── Core pointers ────────────────────────────────────────────────────────
    uint64_t UWorld = 0x1231C808;
    uint64_t Decrypt = 0x10905328;
    uint64_t GNames = 0x125ADC00;
    uint64_t GNames_offset = 0x0;
    uint32_t ElementsPerChunk = 0x4050;
    uint32_t Offset = 0xC;         // ObjID

    // ── Name decryption ──────────────────────────────────────────────────────
    uint64_t NameIndexXor1 = 0x62557116;
    uint64_t NameIndexXor2 = 0xF9A9EE54;
    uint64_t NameIndexXor3 = 0x30000;
    uint32_t NameIndexOne = 0x1E;         // Rval
    uint32_t NameIndexTwo = 0xC;          // Sval
    uint32_t NameIndexDval = 0x14;
    uint32_t NameIsROR = 0x1;

    // ── World / level ────────────────────────────────────────────────────────
    uint32_t CurrentLevel = 0x920;
    uint32_t GameInstance = 0x418;
    uint32_t LocalPlayers = 0xE0;         // LocalPlayer
    uint32_t Actors = 0x2A8;
    uint32_t ObjectID = 0xC;         // ObjID

    // ── Player chain ─────────────────────────────────────────────────────────
    uint32_t PlayerController = 0x38;
    uint32_t AcknowledgedPawn = 0x4C0;
    uint32_t PlayerCameraManager = 0x4E8;
    uint32_t RootComponent = 0x278;
    uint32_t PlayerState = 0x448;
    uint32_t PlayerStatistics = 0x558;

    // ── Camera ───────────────────────────────────────────────────────────────
    uint32_t CameraFov = 0x1048;       // CameraCacheFOV
    uint32_t CameraPos = 0xA90;        // CameraCacheLocation
    uint32_t CameraRot = 0x104C;       // CameraCacheRotation
    uint32_t ViewTarget = 0x1760;

    // ── Mesh / components ────────────────────────────────────────────────────
    uint32_t Mesh = 0x580;
    uint32_t Mesh3P = 0x820;
    uint32_t AnimScriptInstance = 0xE40;
    uint32_t StaticMesh = 0xAF8;
    uint32_t ComponentToWorld = 0x220;
    uint32_t ComponentLocation = 0x230;
    uint32_t Eyes = 0x76C;

    // ── Health (offsets) ─────────────────────────────────────────────────────
    uint32_t HeaFlag = 0x30C;
    uint32_t Health1 = 0xA70;
    uint32_t Health2 = 0xA20;
    uint32_t Health3 = 0xA44;
    uint32_t Health4 = 0xA30;
    uint32_t Health5 = 0xA45;
    uint32_t Health6 = 0xA40;
    uint32_t GroggyHealth = 0x1640;

    // ── Health XOR keys ──────────────────────────────────────────────────────
    uint64_t HealthXorKey0 = 0xCEC7A58F;
    uint64_t HealthXorKey1 = 0x9B63B216;
    uint64_t HealthXorKey2 = 0xCA2B72A5;
    uint64_t HealthXorKey3 = 0x163848B3;
    uint64_t HealthXorKey4 = 0x34911D0A;
    uint64_t HealthXorKey5 = 0x23DDBD34;
    uint64_t HealthXorKey6 = 0x945B3C8;
    uint64_t HealthXorKey7 = 0xA521A621;
    uint64_t HealthXorKey8 = 0xBBD7A58;
    uint64_t HealthXorKey9 = 0xB0EF1687;
    uint64_t HealthXorKey10 = 0xE27503A6;
    uint64_t HealthXorKey11 = 0x878ADB28;
    uint64_t HealthXorKey12 = 0xBD34D3D5;
    uint64_t HealthXorKey13 = 0x1693B307;
    uint64_t HealthXorKey14 = 0xB3099E38;
    uint64_t HealthXorKey15 = 0xF2C72ACC;

    // ── Team / player info ───────────────────────────────────────────────────
    uint32_t LastTeamNum = 0x1210;
    uint32_t TeamNumber = 0x730;
    uint32_t CharacterName = 0x2700;
    uint32_t CharacterState = 0x1620;
    uint32_t CharacterMovement = 0x718;
    uint32_t SpectatedCount = 0x1E88;
    uint32_t Gender = 0xB50;
    uint32_t PlayerArray = 0x428;
    uint32_t AccountId = 0x980;
    uint32_t PlayerName = 0x478;
    uint32_t PlayerStatusType = 0x46C;
    uint32_t SquadMemberIndex = 0x8B0;

    // ── Weapon system ────────────────────────────────────────────────────────
    uint32_t WeaponProcessor = 0xA28;
    uint32_t EquippedWeapons = 0x208;
    uint32_t CurrentWeaponIndex = 0x319;
    uint32_t CurrentAmmoData = 0xB20;
    uint32_t WeaponTrajectoryData = 0x11F8;
    uint32_t TrajectoryGravityZ = 0x111C;
    uint32_t TrajectoryConfig = 0x108;
    uint32_t FiringAttachPoint = 0x8E0;
    uint32_t ScopingAttachPoint = 0x1020;
    uint32_t WeaponConfig_Class = 0x799;
    uint32_t AttachedItems = 0x878;
    uint32_t WeaponAttachmentData = 0x128;
    uint32_t ElapsedCookingTime = 0xC48;
    uint32_t AimOffsets = 0x1BA0;

    // ── Controller / input ───────────────────────────────────────────────────
    uint32_t ControlRotation_CP = 0x654;
    uint32_t RecoilADSRotation_CP = 0x824;
    uint32_t LeanLeftAlpha_CP = 0x69C;
    uint32_t LeanRightAlpha_CP = 0x6A0;
    uint32_t bIsDBNO_CP = 0x931;
    uint32_t bIsActiveRagdoll_CP = 0x934;
    uint32_t bIsScoping_CP = 0x85D;
    uint32_t bIsReloading_CP = 0x73D;
    uint32_t MouseX = 0x5169;
    uint32_t MouseY = 0x516A;
    uint32_t PlayerInput = 0x560;
    uint32_t InputAxisProperties = 0x138;

    // ── Movement / physics ───────────────────────────────────────────────────
    uint32_t LastUpdateVelocity = 0x3E0;
    uint32_t ReplicatedMovement = 0xC8;

    // ── Vehicle ──────────────────────────────────────────────────────────────
    uint32_t VehicleRiderComponent = 0x2110;
    uint32_t VehicleMovement = 0x480;
    uint32_t VehicleCommonComponent = 0xB40;
    uint32_t VehicleFuel = 0x2E0;
    uint32_t VehicleFuelMax = 0x2E4;
    uint32_t VehicleHealth = 0x2D8;
    uint32_t VehicleHealthMax = 0x2DC;
    uint32_t LastVehiclePawn = 0x270;
    uint32_t SeatIndex = 0x230;
    uint32_t Wheels = 0x328;
    uint32_t WheelLocation = 0x100;
    uint32_t DampingRate = 0x54;
    uint32_t ShapeRadius = 0x48;

    // ── Map / zone ───────────────────────────────────────────────────────────
    uint32_t WorldToMap = 0x934;
    uint32_t SafetyZonePosition = 0xB0;
    uint32_t SafetyZoneRadius = 0xBC;
    uint32_t BlueZonePosition = 0xC0;
    uint32_t BlueZoneRadius = 0xCC;
    uint32_t NumAliveTeams = 0x484;
    uint32_t TrainingMapGrid = 0x600;
    uint32_t MortarLocation = 0xB0;
    uint32_t MortarRotation = 0x538;

    // ── Inventory ────────────────────────────────────────────────────────────
    uint32_t InventoryFacade = 0x1DA8;
    uint32_t Inventory = 0x440;
    uint32_t InventoryItems = 0x6A8;
    uint32_t InventoryItemTagCount = 0x40;
    uint32_t ItemTable = 0xB0;
    uint32_t ItemID = 0x240;
    uint32_t Equipment = 0x428;
    uint32_t ItemsArray = 0x588;
    uint32_t Durability = 0x1E4;
    uint32_t DurabilityMax = 0x1E0;
    uint32_t DroppedItem = 0x470;
    uint32_t DroppedItemGroup = 0x2B8;
    uint32_t ItemPackageItems = 0x590;
    uint32_t DroppedItemGroup_UItem = 0x880;

    // ── Misc ─────────────────────────────────────────────────────────────────
    uint32_t GameState = 0x348;
    uint32_t MyHUD = 0x4E0;
    uint32_t LayoutData = 0x40;
    uint32_t StaticSockets = 0xC8;
    uint32_t StaticSocketName = 0x30;
    uint32_t StaticRelativeLocation = 0x38;
    uint32_t StaticRelativeRotation = 0x44;
    uint32_t StaticRelativeScale = 0x50;
    uint32_t TimeSeconds = 0x248;
    uint32_t TimeTillExplosion = 0x844;
    uint32_t ExplodeState = 0x648;
    uint32_t PreEvalPawnState = 0x638;
    uint32_t FeatureRepObject = 0xD10;
    uint32_t AntiCheatSyncManager = 0x850;
    uint32_t CharacterClanInfo = 0x910;
    uint32_t DamageDealtOnEnemy = 0x72C;
    uint32_t PartnerLevel = 0x6EC;
    uint32_t SurvivalTier = 0xE68;
    uint32_t SurvivalLevel = 0xE6C;
    uint32_t BallisticCurve = 0x28;
    uint32_t FloatCurves = 0x38;
    uint32_t PhysxSDK = 0x11DC5088;
    uint32_t bAlwaysCreatePhysics = 0x498;
    uint32_t Keys = 0x60;
    uint32_t Slot = 0x38;
    uint32_t Alignment = 0x20;
    uint32_t Visibility = 0xA9;
    uint32_t Offsets = 0x0;
    uint32_t BlockInputWidgetList = 0x5D8;
    uint32_t bShowMouseCursor = 0x670;
    uint32_t WidgetStateMap = 0x560;
    uint32_t SelectMinimapSizeIndex = 0x550;
    uint32_t AttachedStaticMap = 0x1508;
    uint32_t ComponentVelocity = 0x358;
} inline SDK;
