// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThirdPersonV2/Public/EnemyController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyController() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_AAIController();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyController();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyController_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ThirdPersonV2();
// End Cross Module References
	DEFINE_FUNCTION(AEnemyController::execInitController)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitController();
		P_NATIVE_END;
	}
	void AEnemyController::StaticRegisterNativesAEnemyController()
	{
		UClass* Class = AEnemyController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "InitController", &AEnemyController::execInitController },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEnemyController_InitController_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_InitController_Statics::Function_MetaDataParams[] = {
		{ "Category", "Enemy|Utility|" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyController_InitController_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyController, nullptr, "InitController", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_InitController_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_InitController_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEnemyController_InitController()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyController_InitController_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyController);
	UClass* Z_Construct_UClass_AEnemyController_NoRegister()
	{
		return AEnemyController::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAIController,
		(UObject* (*)())Z_Construct_UPackage__Script_ThirdPersonV2,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AEnemyController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyController_InitController, "InitController" }, // 1259502489
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "EnemyController.h" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyController_Statics::ClassParams = {
		&AEnemyController::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEnemyController()
	{
		if (!Z_Registration_Info_UClass_AEnemyController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyController.OuterSingleton, Z_Construct_UClass_AEnemyController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AEnemyController.OuterSingleton;
	}
	template<> THIRDPERSONV2_API UClass* StaticClass<AEnemyController>()
	{
		return AEnemyController::StaticClass();
	}
	AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyController);
	AEnemyController::~AEnemyController() {}
	struct Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyController, AEnemyController::StaticClass, TEXT("AEnemyController"), &Z_Registration_Info_UClass_AEnemyController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyController), 3202781662U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_3489311136(TEXT("/Script/ThirdPersonV2"),
		Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
