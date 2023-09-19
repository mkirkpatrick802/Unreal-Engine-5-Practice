// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMP_Plugin_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MP_Plugin;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MP_Plugin()
	{
		if (!Z_Registration_Info_UPackage__Script_MP_Plugin.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/MP_Plugin",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x0F42110C,
				0x0A539555,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MP_Plugin.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_MP_Plugin.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MP_Plugin(Z_Construct_UPackage__Script_MP_Plugin, TEXT("/Script/MP_Plugin"), Z_Registration_Info_UPackage__Script_MP_Plugin, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x0F42110C, 0x0A539555));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
