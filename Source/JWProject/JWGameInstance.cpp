// Fill out your copyright notice in the Description page of Project Settings.


#include "JWGameInstance.h"

bool UJWGameInstance::GetObjectInfoByName(FName ObjectName, FObjectInfo& OutInfo)
{
	bool bIsFind = false;
	FObjectInfo* ObjectInfoRow;

	if (ObjectInfoTable)
	{
		ObjectInfoRow = ObjectInfoTable->FindRow<FObjectInfo>(ObjectName, "", false);
		if (ObjectInfoRow)
		{
			bIsFind = true;
			OutInfo = *ObjectInfoRow;
		}
	}


	return bIsFind; 
}