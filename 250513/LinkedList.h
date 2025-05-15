#pragma once

#include <assert.h>

template <typename T>
class CListNode
{
	// CLinkedList 클래스에서 CListNode 클래스의
	// private 멤버들에 접근이 가능하다.
	// template 클래스이므로 아래와 같이 friend 처리를 한다.
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CListIterator;

	template <typename T>
	friend class CListReverseIterator;

private:
	CListNode()
	{
	}

	~CListNode()
	{
	}

private:
	T	mData;
	CListNode<T>* mNext = nullptr;
	CListNode<T>* mPrev = nullptr;
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListIterator()
	{
	}

	CListIterator(CListNode<T>* Node) :
		mNode(Node)
	{
	}

	~CListIterator()
	{
	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator == (const CListIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	bool operator == (const CListReverseIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListReverseIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CListIterator<T>& operator ++ ()
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListIterator<T>& operator ++ (int)
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListIterator<T>& operator -- ()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListIterator<T>& operator -- (int)
	{
		mNode = mNode->mPrev;

		return *this;
	}

	T& operator * ()
	{
		return mNode->mData;
	}

	const T& operator * ()	const
	{
		return mNode->mData;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListReverseIterator()
	{
	}

	CListReverseIterator(CListNode<T>* Node) :
		mNode(Node)
	{
	}

	~CListReverseIterator()
	{
	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator == (const CListReverseIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListReverseIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	bool operator == (const CListIterator<T>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListIterator<T>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CListReverseIterator<T>& operator ++ ()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListReverseIterator<T>& operator ++ (int)
	{
		mNode = mNode->mPrev;

		return *this;
	}

	const CListReverseIterator<T>& operator -- ()
	{
		mNode = mNode->mNext;

		return *this;
	}

	const CListReverseIterator<T>& operator -- (int)
	{
		mNode = mNode->mNext;

		return *this;
	}

	T& operator * ()
	{
		return mNode->mData;
	}

	const T& operator * ()	const
	{
		return mNode->mData;
	}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		mBegin = new CListNode<T>;
		mEnd = new CListNode<T>;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CLinkedList()
	{
		CListNode<T>* Node = mBegin;

		while (Node != nullptr)
		{
			CListNode<T>* Next = Node->mNext;

			delete Node;

			Node = Next;
		}
	}

public:
	typedef CListIterator<T>	iterator;
	typedef const CListIterator<T>	const_iterator;

	typedef CListReverseIterator<T>	reverse_iterator;
	typedef const CListReverseIterator<T>	const_reverse_iterator;

private:
	CListNode<T>* mBegin;
	CListNode<T>* mEnd;
	int			mSize = 0;

public:
	void push_back(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// End노드와 End의 이전노드 사이에 추가한다.
		CListNode<T>* Prev = mEnd->mPrev;

		Prev->mNext = Node;
		Node->mPrev = Prev;

		Node->mNext = mEnd;
		mEnd->mPrev = Node;

		++mSize;
	}

	void push_front(const T& Data)
	{
		CListNode<T>* Node = new CListNode<T>;

		Node->mData = Data;

		// Begin노드와 Begin의 다음노드 사이에 추가한다.
		CListNode<T>* Next = mBegin->mNext;

		mBegin->mNext = Node;
		Node->mPrev = mBegin;

		Node->mNext = Next;
		Next->mPrev = Node;

		++mSize;
	}

	// iter와 iter의 다음 노드 사이에 새로운 노드를 만들고 데이터를 데입하여
	// 추가한다.
	void insert(const_iterator& iter, const T& Data)
	{
		assert(iter != end());

		CListNode<T>* Next = iter.mNode->mNext;

		CListNode<T>* NewNode = new CListNode<T>;

		NewNode->mData = Data;

		iter.mNode->mNext = NewNode;
		NewNode->mPrev = iter.mNode;

		NewNode->mNext = Next;
		Next->mPrev = NewNode;

		++mSize;
	}

	void pop_back()
	{
		assert(mSize > 0);

		// 지울 노드
		CListNode<T>* DeleteNode = mEnd->mPrev;

		// 지울 노드의 이전노드
		CListNode<T>* Prev = DeleteNode->mPrev;

		// 지울노드의 이전노드와 End노드를 연결한다.
		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		// 지울노드의 메모리를 제거한다.
		delete	DeleteNode;

		--mSize;
	}

	void pop_front()
	{
		assert(mSize > 0);

		// 지울 노드
		CListNode<T>* DeleteNode = mBegin->mNext;

		// 지울 노드의 다음노드
		CListNode<T>* Next = DeleteNode->mNext;

		// 지울노드의 이전노드와 End노드를 연결한다.
		mBegin->mNext = Next;
		Next->mPrev = mBegin;

		// 지울노드의 메모리를 제거한다.
		delete	DeleteNode;

		--mSize;
	}

	int size()	const
	{
		return mSize;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	void clear()
	{
		// Begin의 다음노드부터 End의 이전노드까지 제거한다.
		CListNode<T>* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			CListNode<T>* Next = Node->mNext;

			delete Node;

			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	iterator begin()	const
	{
		iterator	iter(mBegin->mNext);
		return iter;
	}

	const_iterator cbegin()	const
	{
		const_iterator	iter(mBegin->mNext);
		return iter;
	}

	reverse_iterator rbegin()	const
	{
		reverse_iterator	iter(mEnd->mPrev);
		return iter;
	}

	const_reverse_iterator crbegin()	const
	{
		const_reverse_iterator	iter(mEnd->mPrev);
		return iter;
	}

	iterator end()	const
	{
		iterator	iter(mEnd);
		return iter;
	}

	const_iterator cend()	const
	{
		const_iterator	iter(mEnd);
		return iter;
	}

	reverse_iterator rend()	const
	{
		reverse_iterator	iter(mBegin);
		return iter;
	}

	const_reverse_iterator crend()	const
	{
		const_reverse_iterator	iter(mBegin);
		return iter;
	}

	// 제거된 노드의 다음 노드를 가지고 있는 iterator를 반환한다.
	iterator erase(const T& Data)
	{
		iterator	iter;
		iterator	iterEnd = end();

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			if (*iter == Data)
			{
				return erase(iter);
			}
		}

		return end();
	}

	iterator erase(const iterator& iter)
	{
		assert(iter.mNode != nullptr && iter.mNode != mBegin && iter.mNode != mEnd);

		// 지울 노드의 이전노드와 다음노드를 얻어온다.
		CListNode<T>* Prev = iter.mNode->mPrev;
		CListNode<T>* Next = iter.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		// 노드를 제거한다.
		delete iter.mNode;

		--mSize;

		return iterator(Next);
	}

	// Start와 End 사이의 노드를 제거한다.
	iterator erase(const_iterator& Start, const_iterator& End)
	{
		iterator _Start = Start;
		iterator _End = End;

		iterator	iter;
		iterator	iterEnd = end();

		bool	Find = false;

		for (iter.mNode = Start.mNode; iter != iterEnd; ++iter)
		{
			if (iter == End)
			{
				Find = true;
				break;
			}
		}

		if (!Find)
		{
			_Start = End;
			_End = Start;
		}

		// B 1 2 3 4 5 6 7 8 E
		CListNode<T>* Prev = _Start.mNode->mPrev;
		CListNode<T>* Next = _End.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		iterator	result(Next);

		while (_Start != _End)
		{
			Next = _Start.mNode->mNext;
			delete _Start.mNode;
			_Start.mNode = Next;
			--mSize;
		}

		// _End는 지우지 않았기 때문에 여기에서 지워준다.
		delete	_Start.mNode;
		--mSize;

		return result;
	}
};

