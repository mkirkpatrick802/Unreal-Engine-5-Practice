// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThirdPersonV2/Public/EnemyCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyCharacter() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyCharacter();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister();
	THIRDPERSONV2_API UEnum* Z_Construct_UEnum_ThirdPersonV2_EEnemyState();
	UPackage* Z_Construct_UPackage__Script_ThirdPersonV2();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyState;
	static UEnum* EEnemyState_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EEnemyState.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EEnemyState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ThirdPersonV2_EEnemyState, (UObject*)Z_Construct_UPackage__Script_ThirdPersonV2(), TEXT("EEnemyState"));
		}
		return Z_Registration_Info_UEnum_EEnemyState.OuterSingleton;
	}
	template<> THIRDPERSONV2_API UEnum* StaticEnum<EEnemyState>()
	{
		return EEnemyState_StaticEnum();
	}
	struct Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enumerators[] = {
		{ "IdleWander", (int64)IdleWander },
		{ "Flocking", (int64)Flocking },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Flocking.DisplayName", "Flocking" },
		{ "Flocking.Name", "Flocking" },
		{ "IdleWander.DisplayName", "Wander" },
		{ "IdleWander.Name", "IdleWander" },
		{ "ModuleRelativePath", "Public/EnemyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_ThirdPersonV2,
		nullptr,
		"EEnemyState",
		"EEnemyState",
		Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Regular,
		METADATA_PARAMS(Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_ThirdPersonV2_EEnemyState()
	{
		if (!Z_Registration_Info_UEnum_EEnemyState.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyState.InnerSingleton, Z_Construct_UEnum_ThirdPersonV2_EEnemyState_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EEnemyState.InnerSingleton;
	}
	void AEnemyCharacter::StaticRegisterNativesAEnemyCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyCharacter);
	UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister()
	{
		return AEnemyCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnemyState_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_EnemyState;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_ThirdPersonV2,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "EnemyCharacter.h" },
		{ "ModuleRelativePath", "Public/EnemyCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_EnemyState_MetaData[] = {
		{ "Category", "Enemy|Enums|" },
		{ "ModuleRelativePath", "Public/EnemyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_EnemyState = { "EnemyState", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AEnemyCharacter, EnemyState), Z_Construct_UEnum_ThirdPersonV2_EEnemyState, METADATA_PARAMS(Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_EnemyState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_EnemyState_MetaData)) }; // 1981037268
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_EnemyState,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams = {
		&AEnemyCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEnemyCharacter()
	{
		if (!Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton, Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton;
	}
	template<> THIRDPERSONV2_API UClass* StaticClass<AEnemyCharacter>()
	{
		return AEnemyCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyCharacter);
	AEnemyCharacter::~AEnemyCharacter() {}
	struct Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::EnumInfo[] = {
		{ EEnemyState_StaticEnum, TEXT("EEnemyState"), &Z_Registration_Info_UEnum_EEnemyState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1981037268U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyCharacter, AEnemyCharacter::StaticClass, TEXT("AEnemyCharacter"), &Z_Registration_Info_UClass_AEnemyCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyCharacter), 3013253344U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_2467987776(TEXT("/Script/ThirdPersonV2"),
		Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyCharacter_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
