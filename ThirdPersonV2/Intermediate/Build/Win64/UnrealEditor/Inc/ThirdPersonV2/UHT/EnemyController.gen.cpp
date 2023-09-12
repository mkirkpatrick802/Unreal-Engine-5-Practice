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
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyController();
	THIRDPERSONV2_API UClass* Z_Construct_UClass_AEnemyController_NoRegister();
	THIRDPERSONV2_API UEnum* Z_Construct_UEnum_ThirdPersonV2_EConstantTypes();
	UPackage* Z_Construct_UPackage__Script_ThirdPersonV2();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EConstantTypes;
	static UEnum* EConstantTypes_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EConstantTypes.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EConstantTypes.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ThirdPersonV2_EConstantTypes, (UObject*)Z_Construct_UPackage__Script_ThirdPersonV2(), TEXT("EConstantTypes"));
		}
		return Z_Registration_Info_UEnum_EConstantTypes.OuterSingleton;
	}
	template<> THIRDPERSONV2_API UEnum* StaticEnum<EConstantTypes>()
	{
		return EConstantTypes_StaticEnum();
	}
	struct Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enumerators[] = {
		{ "Wandering", (int64)Wandering },
		{ "Seperation", (int64)Seperation },
		{ "Cohesion", (int64)Cohesion },
		{ "Alignment", (int64)Alignment },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enum_MetaDataParams[] = {
		{ "Alignment.DisplayName", "Alignment" },
		{ "Alignment.Name", "Alignment" },
		{ "BlueprintType", "true" },
		{ "Cohesion.DisplayName", "Cohesion" },
		{ "Cohesion.Name", "Cohesion" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
		{ "Seperation.DisplayName", "Seperation" },
		{ "Seperation.Name", "Seperation" },
		{ "Wandering.DisplayName", "Wandering" },
		{ "Wandering.Name", "Wandering" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_ThirdPersonV2,
		nullptr,
		"EConstantTypes",
		"EConstantTypes",
		Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Regular,
		METADATA_PARAMS(Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_ThirdPersonV2_EConstantTypes()
	{
		if (!Z_Registration_Info_UEnum_EConstantTypes.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EConstantTypes.InnerSingleton, Z_Construct_UEnum_ThirdPersonV2_EConstantTypes_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EConstantTypes.InnerSingleton;
	}
	DEFINE_FUNCTION(AEnemyController::execSetConstant)
	{
		P_GET_PROPERTY(FByteProperty,Z_Param_type);
		P_GET_PROPERTY(FFloatProperty,Z_Param_value);
		P_FINISH;
		P_NATIVE_BEGIN;
		AEnemyController::SetConstant(EConstantTypes(Z_Param_type),Z_Param_value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEnemyController::execFlocking)
	{
		P_GET_TARRAY_REF(AActor*,Z_Param_Out_c_neighbours);
		P_GET_PROPERTY(FIntProperty,Z_Param_c_length);
		P_GET_TARRAY_REF(AActor*,Z_Param_Out_s_neighbours);
		P_GET_PROPERTY(FIntProperty,Z_Param_s_length);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Flocking(Z_Param_Out_c_neighbours,Z_Param_c_length,Z_Param_Out_s_neighbours,Z_Param_s_length);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEnemyController::execAddForceDirection)
	{
		P_GET_STRUCT(FVector,Z_Param_directionToBeAdded);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddForceDirection(Z_Param_directionToBeAdded);
		P_NATIVE_END;
	}
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
			{ "AddForceDirection", &AEnemyController::execAddForceDirection },
			{ "Flocking", &AEnemyController::execFlocking },
			{ "InitController", &AEnemyController::execInitController },
			{ "SetConstant", &AEnemyController::execSetConstant },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics
	{
		struct EnemyController_eventAddForceDirection_Parms
		{
			FVector directionToBeAdded;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_directionToBeAdded;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::NewProp_directionToBeAdded = { "directionToBeAdded", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventAddForceDirection_Parms, directionToBeAdded), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::NewProp_directionToBeAdded,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::Function_MetaDataParams[] = {
		{ "Category", "Enemy|Movement|" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyController, nullptr, "AddForceDirection", nullptr, nullptr, sizeof(Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::EnemyController_eventAddForceDirection_Parms), Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEnemyController_AddForceDirection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyController_AddForceDirection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AEnemyController_Flocking_Statics
	{
		struct EnemyController_eventFlocking_Parms
		{
			TArray<AActor*> c_neighbours;
			int32 c_length;
			TArray<AActor*> s_neighbours;
			int32 s_length;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_c_neighbours_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_c_neighbours_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_c_neighbours;
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_c_length;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_s_neighbours_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_s_neighbours_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_s_neighbours;
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_s_length;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours_Inner = { "c_neighbours", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours = { "c_neighbours", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventFlocking_Parms, c_neighbours), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours_MetaData)) };
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_length = { "c_length", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventFlocking_Parms, c_length), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours_Inner = { "s_neighbours", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours = { "s_neighbours", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventFlocking_Parms, s_neighbours), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours_MetaData)) };
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_length = { "s_length", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventFlocking_Parms, s_length), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyController_Flocking_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_neighbours,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_c_length,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_neighbours,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_Flocking_Statics::NewProp_s_length,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_Flocking_Statics::Function_MetaDataParams[] = {
		{ "Category", "Enemy|Movement|" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyController_Flocking_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyController, nullptr, "Flocking", nullptr, nullptr, sizeof(Z_Construct_UFunction_AEnemyController_Flocking_Statics::EnemyController_eventFlocking_Parms), Z_Construct_UFunction_AEnemyController_Flocking_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_Flocking_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_Flocking_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_Flocking_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEnemyController_Flocking()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyController_Flocking_Statics::FuncParams);
		}
		return ReturnFunction;
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
	struct Z_Construct_UFunction_AEnemyController_SetConstant_Statics
	{
		struct EnemyController_eventSetConstant_Parms
		{
			TEnumAsByte<EConstantTypes> type;
			float value;
		};
		static const UECodeGen_Private::FBytePropertyParams NewProp_type;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AEnemyController_SetConstant_Statics::NewProp_type = { "type", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventSetConstant_Parms, type), Z_Construct_UEnum_ThirdPersonV2_EConstantTypes, METADATA_PARAMS(nullptr, 0) }; // 3117771293
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AEnemyController_SetConstant_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(EnemyController_eventSetConstant_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyController_SetConstant_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_SetConstant_Statics::NewProp_type,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyController_SetConstant_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyController_SetConstant_Statics::Function_MetaDataParams[] = {
		{ "Category", "Enemy|Utility|" },
		{ "ModuleRelativePath", "Public/EnemyController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyController_SetConstant_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyController, nullptr, "SetConstant", nullptr, nullptr, sizeof(Z_Construct_UFunction_AEnemyController_SetConstant_Statics::EnemyController_eventSetConstant_Parms), Z_Construct_UFunction_AEnemyController_SetConstant_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_SetConstant_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AEnemyController_SetConstant_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyController_SetConstant_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AEnemyController_SetConstant()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyController_SetConstant_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_AEnemyController_AddForceDirection, "AddForceDirection" }, // 751657149
		{ &Z_Construct_UFunction_AEnemyController_Flocking, "Flocking" }, // 3031567528
		{ &Z_Construct_UFunction_AEnemyController_InitController, "InitController" }, // 1259502489
		{ &Z_Construct_UFunction_AEnemyController_SetConstant, "SetConstant" }, // 3610179448
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
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::EnumInfo[] = {
		{ EConstantTypes_StaticEnum, TEXT("EConstantTypes"), &Z_Registration_Info_UEnum_EConstantTypes, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3117771293U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyController, AEnemyController::StaticClass, TEXT("AEnemyController"), &Z_Registration_Info_UClass_AEnemyController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyController), 471692024U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_1848092550(TEXT("/Script/ThirdPersonV2"),
		Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Michael_Documents_Unreal_Projects_Unreal_Engine_5_Practice_ThirdPersonV2_Source_ThirdPersonV2_Public_EnemyController_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
