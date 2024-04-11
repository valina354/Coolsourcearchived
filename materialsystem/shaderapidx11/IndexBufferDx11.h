#pragma once

#include "shaderapidx9/meshbase.h"
#include "shaderapi/ishaderdevice.h"

#include "Dx11Global.h"

//-----------------------------------------------------------------------------
// Forward declaration
//-----------------------------------------------------------------------------
struct ID3D11Buffer;

//-----------------------------------------------------------------------------
// Dx11 implementation of an index buffer
//-----------------------------------------------------------------------------
class CIndexBufferDx11 : public CIndexBufferBase
{
	typedef CIndexBufferBase BaseClass;

	// Methods of IIndexBuffer
public:
	virtual int IndexCount() const;
	virtual MaterialIndexFormat_t IndexFormat() const;
	virtual int GetRoomRemaining() const;
	virtual bool Lock( int nMaxIndexCount, bool bAppend, IndexDesc_t& desc );
	virtual bool LockEx( int nFirstIndex, int nMaxIndex, IndexDesc_t &desc );
	virtual void Unlock( int nWrittenIndexCount, IndexDesc_t& desc );
	virtual void ModifyBegin( bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t& desc );
	virtual void ModifyEnd( IndexDesc_t& desc );
	virtual bool IsDynamic() const;
	virtual void BeginCastBuffer( MaterialIndexFormat_t format );
	virtual void EndCastBuffer();
	bool HasEnoughRoom( int nVertCount ) const;

#ifdef _DEBUG
	void UpdateShadowIndices( unsigned short *pData )
	{
		Assert( m_LockedStartIndex + m_LockedNumIndices <= m_NumIndices );
		memcpy( m_pShadowIndices + m_LockedStartIndex, pData, m_LockedNumIndices * IndexSize() );
	}

	unsigned short GetShadowIndex( int i )
	{
		Assert( i >= 0 && i < (int)m_NumIndices );
		return m_pShadowIndices[i];
	}
#endif

	int IndexPosition() const
	{
		return m_Position;
	}

	// Other public methods
public:
	// constructor, destructor
	CIndexBufferDx11( ShaderBufferType_t type, MaterialIndexFormat_t fmt, int nIndexCount, const char* pBudgetGroupName );
	virtual ~CIndexBufferDx11();

	ID3D11Buffer* GetDx11Buffer() const;
	MaterialIndexFormat_t GetIndexFormat() const;

	// Only used by dynamic buffers, indicates the next lock should perform a discard.
	void Flush();

	// Returns the size of the index in bytes
	int IndexSize() const;

	int SizeForIndex( MaterialIndexFormat_t fmt ) const;

protected:
	// Creates, destroys the index buffer
	bool Allocate();
	void Free();

#ifdef _DEBUG
	unsigned short *m_pShadowIndices;
	unsigned int m_NumIndices;
	unsigned int m_LockedStartIndex;
	unsigned int m_LockedNumIndices;
#endif

	// Used for static buffers to keep track of the memory
	// and not throw it away when a section needs modification.
	unsigned char *m_pIndexMemory;
	int m_nIndicesLocked;

	ID3D11Buffer* m_pIndexBuffer;
	MaterialIndexFormat_t m_IndexFormat;
	int m_nIndexSize;
	int m_nIndexCount;
	int m_nBufferSize;
	int m_Position;	// Used only for dynamic buffers, indicates where it's safe to write (nooverwrite)
	bool m_bIsLocked : 1;
	bool m_bIsDynamic : 1;
	bool m_bFlush : 1;				// Used only for dynamic buffers, indicates to discard the next time

#ifdef _DEBUG
	static int s_nBufferCount;
#endif
};

//-----------------------------------------------------------------------------
// Returns the size of the index in bytes
//-----------------------------------------------------------------------------
inline int CIndexBufferDx11::IndexSize() const
{
	return m_nIndexSize;
}

inline ID3D11Buffer* CIndexBufferDx11::GetDx11Buffer() const
{
	return m_pIndexBuffer;
}

inline MaterialIndexFormat_t CIndexBufferDx11::GetIndexFormat() const
{
	return m_IndexFormat;
}