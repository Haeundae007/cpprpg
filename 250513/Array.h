#pragma once

#include <assert.h>

template <typename T>
class CArray
{
public:
	CArray()
	{
		mArray = new T[mCapacity];
	}

	~CArray()
	{
		delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int	mSize = 0;
	int	mCapacity = 2;

public:
	void push_back(const T& Data)
	{
		// 배열이 꽉 찼는지 확인한다.
		if (mSize == mCapacity)
		{
			// 새로운 공간을 기존 공간의 2배 크기로 생성한다.
			mCapacity *= 2;

			T* Array = new T[mCapacity];

			// 새로운 공간에 기존 배열의 내용을 복사한다.
			memcpy(Array, mArray, sizeof(T) * mSize);

			// 기존 배열을 제거한다.
			delete[]	mArray;

			// 새로운 배열의 주소를 멤버 포인터에 넣어준다.
			mArray = Array;
		}

		mArray[mSize] = Data;
		++mSize;
	}

	// 마지막에 추가된 데이터를 제거한다.
	void pop_back()
	{
		// 인자로 조건을 주고 거짓일 경우 프로그램을 종료시킨다.
		// assert는 디버그 모드일때만 동작한다.
		assert(mSize > 0);

		--mSize;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	void clear()
	{
		mSize = 0;
	}

	// 인자로 들어온 값을 찾아서 제거한다.
	void erase(const T& Data)
	{
		// 제거할 뒤의 값을 1칸씩 앞으로 이동시켜준다.
		for (int i = 0; i < mSize; ++i)
		{
			if (mArray[i] == Data)
			{
				eraseIndex(i);
				break;
			}
		}
	}

	// 인자로 들어온 인덱스를 제거한다.
	void eraseIndex(int Index)
	{
		assert(0 <= Index && Index < mSize);

		for (int i = Index; i < mSize - 1; ++i)
		{
			mArray[i] = mArray[i + 1];
		}

		--mSize;
	}

	void eraseIndex1(int Index)
	{
		assert(0 <= Index && Index < mSize);

		// 마지막에 추가된 데이터를 현재 인덱스에 대입하고
		// 추가된 수를 줄여준다.
		mArray[Index] = mArray[mSize - 1];

		--mSize;
	}

	T& operator [] (int Index)
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}

	const T& operator [] (int Index)	const
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index];
	}
};

