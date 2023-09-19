// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MP_Plugin/MP_PluginGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMP_PluginGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	MP_PLUGIN_API UClass* Z_Construct_UClass_AMP_PluginGameMode();
	MP_PLUGIN_API UClass* Z_Construct_UClass_AMP_PluginGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MP_Plugin();
// End Cross Module References
	void AMP_PluginGameMode::StaticRegisterNativesAMP_PluginGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMP_PluginGameMode);
	UClass* Z_Construct_UClass_AMP_PluginGameMode_NoRegister()
	{
		return AMP_PluginGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMP_PluginGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMP_PluginGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MP_Plugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMP_PluginGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MP_PluginGameMode.h" },
		{ "ModuleRelativePath", "MP_PluginGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMP_PluginGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMP_PluginGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMP_PluginGameMode_Statics::ClassParams = {
		&AMP_PluginGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AMP_PluginGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMP_PluginGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMP_PluginGameMode()
	{
		if (!Z_Registration_Info_UClass_AMP_PluginGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMP_PluginGameMode.OuterSingleton, Z_Construct_UClass_AMP_PluginGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMP_PluginGameMode.OuterSingleton;
	}
	template<> MP_PLUGIN_API UClass* StaticClass<AMP_PluginGameMode>()
	{
		return AMP_PluginGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMP_PluginGameMode);
	AMP_PluginGameMode::~AMP_PluginGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Engine_5_Practice_MP_Plugin_Source_MP_Plugin_MP_PluginGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Engine_5_Practice_MP_Plugin_Source_MP_Plugin_MP_PluginGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMP_PluginGameMode, AMP_PluginGameMode::StaticClass, TEXT("AMP_PluginGameMode"), &Z_Registration_Info_UClass_AMP_PluginGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMP_PluginGameMode), 4105456884U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Engine_5_Practice_MP_Plugin_Source_MP_Plugin_MP_PluginGameMode_h_2874818842(TEXT("/Script/MP_Plugin"),
		Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Engine_5_Practice_MP_Plugin_Source_MP_Plugin_MP_PluginGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_michael_kirkpatrick_Documents_Unreal_Engine_5_Practice_MP_Plugin_Source_MP_Plugin_MP_PluginGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
