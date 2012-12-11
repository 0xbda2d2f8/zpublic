
//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	KTree.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-3-14  17:55
//	Comment:	��ͨ��(���ݽṹ)
//
//
//  ����������������:
//  1. 	 m_data         ���ڴ������
//  2.   m_pParent      ָ��ý��ĸ����, ����ý��Ϊ�����, m_pParentΪ��
//  3.   m_pFirstChild  ָ��ý��ĵ�һ���ӽ��, ���û���ӽ��, m_pFirstChildΪ��
//  4.   m_pNextSibling ָ��ý�����һ���ֵܽ��, �������û���ֵ�, m_pNextSiblingΪ��
//
//  �� �������:
//  1.   Clear          �����, ɾ�����н��
//  2.   InsertItem     ��ָ���ĸ����������ӽ��ĩβ ����һ�����
//  3.   DeleteItem     ɾ��ָ����� �Լ��ýڵ�������ӽ��
//	4.   GetParent      ��ȡָ�����ĸ����, �����ĸ����ΪNULL
//  5.   GetNextSibling ��ȡָ��������һ���ֵܽ��
//  6.   GetFirstChild  ��ȡָ�����ĵ�һ���ӽ��
//  7.   HasChildren    �鿴ָ������Ƿ����ӽ��
//  8.   Size           ��ȡ��ǰ�������
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef _KTREE_H_
#define _KTREE_H_
#include <assert.h>


//////////////////////////////////////////////////////////////////////////
//
// ��
//
//////////////////////////////////////////////////////////////////////////

template<class T>
class KTreeItem;



template<class T>
class KTree
{ 
public:
	KTree()
	{
		m_pRoot = NULL;
		m_nItemCount = 0;
	}

	~KTree()
	{
		Clear();
	}

	KTreeItem<T>* GetRootItem() const
	{
		return m_pRoot;
	}

	void Clear()
	{
		if( m_pRoot != NULL )
		{
			DeleteItem( m_pRoot );
		}

		assert( m_nItemCount == 0 );
	}

	KTreeItem<T>* InsertItem( const T& data, KTreeItem<T>* pParent )
	{
		KTreeItem<T>* pItem = new KTreeItem<T>;
		if( pItem == NULL )
		{
			return NULL;
		}
		m_nItemCount++;


		pItem->m_data    = data;
		pItem->m_pParent = pParent;

		if( pParent == NULL )
		{
			assert( m_pRoot == NULL );
			m_pRoot = pItem;
		}
		else
		{
			KTreeItem<T>* pIter = pParent->m_pFirstChild;

			if( pIter == NULL )
			{
				pParent->m_pFirstChild = pItem;
			}
			else
			{
				while( pIter->m_pNextSibling != NULL )
				{
					pIter = pIter->m_pNextSibling;
				}

				pIter->m_pNextSibling = pItem;
			}
		}

		return pItem;
	}


	void DeleteItem( KTreeItem<T>* pItem )
	{
		assert( pItem != NULL );

		DeleteChildren( pItem );

		if( pItem != m_pRoot )
		{
			KTreeItem<T>*  pParent = GetParent( pItem );
			KTreeItem<T>*  pIter   = pParent->m_pFirstChild;

			if( pIter == pItem )
			{
				pParent->m_pFirstChild = pIter->m_pNextSibling;
			}
			else
			{
				while( pIter->m_pNextSibling != pItem )
				{
					pIter = pIter->m_pNextSibling;
					assert( pIter != NULL );
				}

				pIter->m_pNextSibling = pItem->m_pNextSibling;
			}

		}
		else
		{
			m_pRoot = NULL;
		}

		delete pItem;
		m_nItemCount--;
	}



	KTreeItem<T>* GetParent( const KTreeItem<T>* pItem ) const
	{
		assert( pItem != NULL );
		return pItem->m_pParent;
	}

	KTreeItem<T>* GetNextSibling( const KTreeItem<T>* pItem ) const
	{
		assert( pItem != NULL );
		return pItem->m_pNextSibling;
	}


	KTreeItem<T>* GetFirstChild( const KTreeItem<T>* pItem ) const
	{
		assert( pItem != NULL );
		return pItem->m_pFirstChild;
	}


	bool HasChildren( const KTreeItem<T>* pItem ) const
	{
		return ( pItem->m_pFirstChild != NULL );
	}


	int Size() const
	{
		return m_nItemCount;
	}

private:
	void DeleteChildren( KTreeItem<T>* pItem )
	{
		KTreeItem<T>* pNext = NULL;
		KTreeItem<T>* pIter = NULL;

		for( pIter = pItem->m_pFirstChild; pIter != NULL; pIter = pNext )
		{
			pNext = pIter->m_pNextSibling;

			DeleteChildren( pIter );
			delete pIter;
			pIter = NULL;
			m_nItemCount--;
		}
	}


private: 
	KTreeItem<T>* m_pRoot;
	int           m_nItemCount;
};


//////////////////////////////////////////////////////////////////////////
//
// �����
//
//////////////////////////////////////////////////////////////////////////


template<class T>
class KTreeItem
{
	friend class KTree<T>;
public:
	KTreeItem()
	{
		m_pParent      = NULL;
		m_pFirstChild  = NULL;
		m_pNextSibling = NULL;
	}

	~KTreeItem()
	{
	}

	const T& GetData() const
	{
		return m_data;
	}

	T& GetData()
	{
		return m_data;
	}

	void SetData( const T& data )
	{
		m_data = data;
	}


	T      m_data;

	KTreeItem<T>*  m_pParent;  
	KTreeItem<T>*  m_pFirstChild;
	KTreeItem<T>*  m_pNextSibling;              
};



#endif // _KTREE_H_