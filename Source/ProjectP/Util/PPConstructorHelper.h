// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTP_API FPPConstructorHelper
{
public:
	template <class T>
	static T* FindAndGetObject(const TCHAR* InName, uint32 InLoadFlags = LOAD_None)
	{
		static ConstructorHelpers::FObjectFinder<T> ObjectFinder(InName, InLoadFlags);
		return ObjectFinder.Object;
	}

	template <class T>
	static void FindObjectAndInitialize(const TCHAR* InName, TFunctionRef<void(T*)> Func, uint32 InLoadFlags = LOAD_None)
	{
		T* Object = FindAndGetObject<T>(InName, InLoadFlags);
		if(!Object) return;
		Func(Object);
	}

	template <class T>
	static TSubclassOf<T> FindAndGetClass(const TCHAR* InName)
	{
		static ConstructorHelpers::FClassFinder<T> ObjectFinder(InName);
		return ObjectFinder.Class;
	}

	template <class T>
	static void FindClassAndInitialize(const TCHAR* InName, TFunctionRef<void(TSubclassOf<T>)> Func)
	{
		TSubclassOf<T> Class = FindAndGetClass<T>(InName);
		if(!Class) return;
		Func(Class);
	}
};
