#pragma once

template <class ClassType>
class cSingleton
{
private:
	static ClassType* mPInstance;
protected:
	cSingleton() {};
	cSingleton(ClassType& _Instance) {};
	virtual ~cSingleton() {};

public:
	static ClassType* getInstance()
	{
		if (mPInstance == nullptr)
		{
			mPInstance = new ClassType;
		}

		return mPInstance;
	}

	static void destroyInstance()
	{
		if (mPInstance)
		{
			delete mPInstance;
			mPInstance = nullptr;
		}
	}
};

template <typename ClassType>
ClassType * cSingleton<ClassType>::mPInstance = 0;

