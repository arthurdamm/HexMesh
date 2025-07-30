#pragma once

#ifdef MY_CLASSNAME
#define LOG_CLASS(Format, ...) UE_LOG(LogTemp, Warning, TEXT("%s::%s:%d " Format), MY_CLASSNAME, *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define LOG_CLASS_ERR(Format, ...) UE_LOG(LogTemp, Error, TEXT("%s::%s:%d " Format), MY_CLASSNAME, *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#else
#define LOG_CLASS(Format, ...) UE_LOG(LogTemp, Warning, TEXT("??::%s():%d " Format), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define LOG_CLASS_ERR(Format, ...) UE_LOG(LogTemp, Error, TEXT("??::%s():%d " Format), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#endif