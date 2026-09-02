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
    uint64_t UWorld = 0x12284408;
    uint64_t Decrypt = 0x108ED528;
    uint64_t GNames = 0x12515880;
    uint64_t GNames_offset = 0x0;
    uint32_t ElementsPerChunk = 0x3F00;
    uint32_t Offset = 0x18;         // ObjID

    // ── Name decryption ──────────────────────────────────────────────────────
    uint64_t NameIndexXor1 = 0x1F65BC48;
    uint64_t NameIndexXor2 = 0xB91AE7CF;
    uint64_t NameIndexXor3 = 0x70000;
    uint32_t NameIndexOne = 0x1D;         // Rval
    uint32_t NameIndexTwo = 0xD;          // Sval
    uint32_t NameIndexDval = 0x13;
    uint32_t NameIsROR = 0x1;

    // ── World / level ────────────────────────────────────────────────────────
    uint32_t CurrentLevel = 0x9A8;
    uint32_t GameInstance = 0x8F8;
    uint32_t LocalPlayers = 0xF0;         // LocalPlayer
    uint32_t Actors = 0x2A0;
    uint32_t ObjectID = 0x18;         // ObjID

    // ── Player chain ─────────────────────────────────────────────────────────
    uint32_t PlayerController = 0x38;
    uint32_t AcknowledgedPawn = 0x4B8;
    uint32_t PlayerCameraManager = 0x4E0;
    uint32_t RootComponent = 0x1C0;
    uint32_t PlayerState = 0x440;
    uint32_t PlayerStatistics = 0x850;

    // ── Camera ───────────────────────────────────────────────────────────────
    uint32_t CameraFov = 0x1D20;       // CameraCacheFOV
    uint32_t CameraPos = 0x1770;       // CameraCacheLocation
    uint32_t CameraRot = 0x1D2C;       // CameraCacheRotation
    uint32_t ViewTarget = 0xAB0;

    // ── Mesh / components ────────────────────────────────────────────────────
    uint32_t Mesh = 0x470;
    uint32_t Mesh3P = 0x800;
    uint32_t AnimScriptInstance = 0xE40;
    uint32_t StaticMesh = 0xAF8;
    uint32_t ComponentToWorld = 0x240;
    uint32_t ComponentLocation = 0x250;
    uint32_t Eyes = 0x76C;

    // ── Health (offsets) ─────────────────────────────────────────────────────
    uint32_t HeaFlag = 0x1A8;
    uint32_t Health1 = 0xA44;
    uint32_t Health2 = 0xA40;
    uint32_t Health3 = 0xA6C;
    uint32_t Health4 = 0xA58;
    uint32_t Health5 = 0xA6D;
    uint32_t Health6 = 0xA68;
    uint32_t GroggyHealth = 0x1E90;

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
    uint32_t LastTeamNum = 0x1818;
    uint32_t TeamNumber = 0x8D0;
    uint32_t CharacterName = 0x1A30;
    uint32_t CharacterState = 0x1E49;
    uint32_t CharacterMovement = 0x7B0;
    uint32_t SpectatedCount = 0x17E8;
    uint32_t Gender = 0xB50;
    uint32_t PlayerArray = 0x418;
    uint32_t AccountId = 0x958;
    uint32_t PlayerName = 0x458;
    uint32_t PlayerStatusType = 0x914;
    uint32_t SquadMemberIndex = 0x840;

    // ── Weapon system ────────────────────────────────────────────────────────
    uint32_t WeaponProcessor = 0x9A0;
    uint32_t EquippedWeapons = 0x208;
    uint32_t CurrentWeaponIndex = 0x319;
    uint32_t CurrentAmmoData = 0xBC4;
    uint32_t WeaponTrajectoryData = 0x11E8;
    uint32_t TrajectoryGravityZ = 0x110C;
    uint32_t TrajectoryConfig = 0x108;
    uint32_t FiringAttachPoint = 0x8C0;
    uint32_t ScopingAttachPoint = 0xB00;
    uint32_t WeaponConfig_Class = 0x5FC;
    uint32_t AttachedItems = 0x858;
    uint32_t WeaponAttachmentData = 0x120;
    uint32_t ElapsedCookingTime = 0xC48;
    uint32_t AimOffsets = 0x1C50;

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
    uint32_t PlayerInput = 0x558;
    uint32_t InputAxisProperties = 0x130;

    // ── Movement / physics ───────────────────────────────────────────────────
    uint32_t LastUpdateVelocity = 0x3E0;
    uint32_t ReplicatedMovement = 0x88;

    // ── Vehicle ──────────────────────────────────────────────────────────────
    uint32_t VehicleRiderComponent = 0x20D0;
    uint32_t VehicleMovement = 0x478;
    uint32_t VehicleCommonComponent = 0xB40;
    uint32_t VehicleFuel = 0x2E0;
    uint32_t VehicleFuelMax = 0x2E4;
    uint32_t VehicleHealth = 0x2D8;
    uint32_t VehicleHealthMax = 0x2DC;
    uint32_t LastVehiclePawn = 0x270;
    uint32_t SeatIndex = 0x230;
    uint32_t Wheels = 0x328;
    uint32_t WheelLocation = 0x100;
    uint32_t DampingRate = 0x4C;
    uint32_t ShapeRadius = 0x40;

    // ── Map / zone ───────────────────────────────────────────────────────────
    uint32_t WorldToMap = 0x38;
    uint32_t SafetyZonePosition = 0xB0;
    uint32_t SafetyZoneRadius = 0xBC;
    uint32_t BlueZonePosition = 0xC0;
    uint32_t BlueZoneRadius = 0xCC;
    uint32_t NumAliveTeams = 0x4D8;
    uint32_t TrainingMapGrid = 0x600;
    uint32_t MortarLocation = 0xB0;
    uint32_t MortarRotation = 0x530;

    // ── Inventory ────────────────────────────────────────────────────────────
    uint32_t InventoryFacade = 0x19A8;
    uint32_t Inventory = 0x430;
    uint32_t InventoryItems = 0x698;
    uint32_t InventoryItemTagCount = 0x38;
    uint32_t ItemTable = 0xB0;
    uint32_t ItemID = 0x240;
    uint32_t Equipment = 0x418;
    uint32_t ItemsArray = 0x578;
    uint32_t Durability = 0x1E4;
    uint32_t DurabilityMax = 0x1E0;
    uint32_t DroppedItem = 0x460;
    uint32_t DroppedItemGroup = 0x2D0;
    uint32_t ItemPackageItems = 0x580;
    uint32_t DroppedItemGroup_UItem = 0x880;

    // ── Misc ─────────────────────────────────────────────────────────────────
    uint32_t GameState = 0x9D8;
    uint32_t MyHUD = 0x4D8;
    uint32_t LayoutData = 0x40;
    uint32_t StaticSockets = 0xC8;
    uint32_t StaticSocketName = 0x30;
    uint32_t StaticRelativeLocation = 0x38;
    uint32_t StaticRelativeRotation = 0x44;
    uint32_t StaticRelativeScale = 0x50;
    uint32_t TimeSeconds = 0x9A0;
    uint32_t TimeTillExplosion = 0x834;
    uint32_t ExplodeState = 0x638;
    uint32_t PreEvalPawnState = 0x638;
    uint32_t FeatureRepObject = 0xD10;
    uint32_t AntiCheatSyncManager = 0x1420;
    uint32_t CharacterClanInfo = 0x8E8;
    uint32_t DamageDealtOnEnemy = 0x8E4;
    uint32_t PartnerLevel = 0x6B0;
    uint32_t SurvivalTier = 0xE48;
    uint32_t SurvivalLevel = 0xE4C;
    uint32_t BallisticCurve = 0x28;
    uint32_t FloatCurves = 0x18;
    uint32_t PhysxSDK = 0x11DAD088;
    uint32_t bAlwaysCreatePhysics = 0x498;
    uint32_t Keys = 0x60;
    uint32_t Slot = 0x38;
    uint32_t Alignment = 0x20;
    uint32_t Visibility = 0xA9;
    uint32_t Offsets = 0x0;
    uint32_t BlockInputWidgetList = 0x5C8;
    uint32_t bShowMouseCursor = 0x668;
    uint32_t WidgetStateMap = 0x548;
    uint32_t SelectMinimapSizeIndex = 0x548;
    uint32_t AttachedStaticMap = 0x1508;
    uint32_t ComponentVelocity = 0x358;
} inline SDK;