// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM()
enum class EAssertionLevel : uint8
{
	None,
	Ensure,
	Check,
};

class PROJECTP_API FPPConstructorHelper
{
public:
	template <class T>
	static T* FindAndGetObject(const TCHAR* InName, const EAssertionLevel InAssertionLevel = EAssertionLevel::None, const uint32 InLoadFlags = LOAD_None)
	{
		ConstructorHelpers::FObjectFinder<T> ObjectFinder(InName, InLoadFlags);
		AssertByAssertionLevel(ObjectFinder, InAssertionLevel);
		return ObjectFinder.Object;
	}

	template <class T>
	static void FindObjectAndInitialize(const TCHAR* InName, TFunctionRef<void(T*)> Func, const EAssertionLevel InAssertionLevel = EAssertionLevel::None, uint32 InLoadFlags = LOAD_None)
	{
		T* Object = FindAndGetObject<T>(InName, InAssertionLevel, InLoadFlags);
		if (!Object)
		{
			return;
		}
		Func(Object);
	}

	template <class T>
	static TSubclassOf<T> FindAndGetClass(const TCHAR* InName, const EAssertionLevel InAssertionLevel = EAssertionLevel::None)
	{
		ConstructorHelpers::FClassFinder<T> ObjectFinder(InName);
		AssertByAssertionLevel(ObjectFinder, InAssertionLevel);
		return ObjectFinder.Class;
	}

	template <class T>
	static void FindClassAndInitialize(const TCHAR* InName, TFunctionRef<void(TSubclassOf<T>)> Func, const EAssertionLevel InAssertionLevel = EAssertionLevel::None)
	{
		TSubclassOf<T> Class = FindAndGetClass<T>(InName, InAssertionLevel);
		if (!Class)
		{
			return;
		}
		Func(Class);
	}

private:
	template <class T>
	static void AssertByAssertionLevel(T& InFinder, const EAssertionLevel InAssertionLevel)
	{
		switch (InAssertionLevel)
		{
		case EAssertionLevel::None:
			break;
		case EAssertionLevel::Ensure:
			ensure(InFinder.Succeeded());
			break;
		case EAssertionLevel::Check:
			check(InFinder.Succeeded());
			break;
		default:
			checkNoEntry();
		}
	}
};
