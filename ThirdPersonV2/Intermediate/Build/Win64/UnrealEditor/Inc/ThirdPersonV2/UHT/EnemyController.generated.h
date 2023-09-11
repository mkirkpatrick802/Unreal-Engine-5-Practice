// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EnemyController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef THIRDPERSONV2_EnemyController_generated_h
#error "EnemyController.generated.h already included, missing '#pragma once' in EnemyController.h"
#endif
#define THIRDPERSONV2_EnemyController_generated_h

#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_SPARSE_DATA
#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFlocking); \
	DECLARE_FUNCTION(execAddForceDirection); \
	DECLARE_FUNCTION(execInitController);


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFlocking); \
	DECLARE_FUNCTION(execAddForceDirection); \
	DECLARE_FUNCTION(execInitController);


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_ACCESSORS
#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyController(); \
	friend struct Z_Construct_UClass_AEnemyController_Statics; \
public: \
	DECLARE_CLASS(AEnemyController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ThirdPersonV2"), NO_API) \
	DECLARE_SERIALIZER(AEnemyController)


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_INCLASS \
private: \
	static void StaticRegisterNativesAEnemyController(); \
	friend struct Z_Construct_UClass_AEnemyController_Statics; \
public: \
	DECLARE_CLASS(AEnemyController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ThirdPersonV2"), NO_API) \
	DECLARE_SERIALIZER(AEnemyController)


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemyController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyController(AEnemyController&&); \
	NO_API AEnemyController(const AEnemyController&); \
public: \
	NO_API virtual ~AEnemyController();


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemyController(AEnemyController&&); \
	NO_API AEnemyController(const AEnemyController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemyController) \
	NO_API virtual ~AEnemyController();


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_20_PROLOG
#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_SPARSE_DATA \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_RPC_WRAPPERS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_ACCESSORS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_INCLASS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_SPARSE_DATA \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_ACCESSORS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_INCLASS_NO_PURE_DECLS \
	FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> THIRDPERSONV2_API UClass* StaticClass<class AEnemyController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
