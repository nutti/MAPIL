/**
*	@file	RingBuffer.hpp
*	@brief	
*	@date	2011.6.10(Fri) 21:52
*/

#ifndef INCLUDED_MAPIL_RINGBUFFER_HPP
#define INCLUDED_MAPIL_RINGBUFFER_HPP

#include "../Type.h"
#include "../Util/Memory.hpp"

namespace MAPIL
{
	template < typename Type, MapilInt32 DEPTH >
	class RingBuffer
	{
	private:
		Type*			m_pBuf;		// Data buffer.
		MapilInt32		m_ReadPos;		// Position of reading.
		MapilInt32		m_WritePos;	// Position of writing.
		MapilInt32		m_Interval;	// Interval between position of reading and position of writing.
	public:
		// Constructor.
		RingBuffer();
		// Destructor.
		~RingBuffer();
		// Get value of Data at position of reading.
		Type GetValue() const;
		// Set value to position of writing.
		MapilVoid SetValue( Type value );
		// Forward position of reading.
		MapilVoid ForwardReadPos( MapilInt32 num );
		// Forward position of writing.
		MapilVoid ForwardWritePos( MapilInt32 num );
		// Is ring buffer full?
		MapilBool IsFull() const;
		// Is ring buffer empty?
		MapilBool IsEmpty() const;
		// Get interval between position of reading and position of writing.
		MapilInt32 GetInterval() const;
		// Reset ring buffer.
		MapilVoid Reset();
	};

	// Constructor.
	template < typename Type, MapilInt32 DEPTH >
	RingBuffer < Type, DEPTH > ::RingBuffer() :	m_ReadPos( 0 ),
														m_WritePos( 0 ),
														m_Interval( 0 )
	{
		m_pBuf = new Type[ DEPTH ];
		ZeroObject( m_pBuf, sizeof( Type ) * DEPTH );
	}

	// Destructor.
	template < typename Type, MapilInt32 DEPTH >
	RingBuffer < Type, DEPTH > ::~RingBuffer()
	{
		SafeDeleteArray( m_pBuf );
	}

	// Get value of Data at position of reading.
	template < typename Type, MapilInt32 DEPTH >
	inline Type RingBuffer < Type, DEPTH > ::GetValue() const
	{
		return m_pBuf[ m_ReadPos ];
	}

	// Set value to position of writing.
	template < typename Type, MapilInt32 DEPTH >
	inline MapilVoid RingBuffer < Type, DEPTH > ::SetValue( Type value )
	{
		m_pBuf[ m_WritePos ] = value;
	}

	// Forward position of reading.
	template < typename Type, MapilInt32 DEPTH >
	MapilVoid RingBuffer < Type, DEPTH > ::ForwardReadPos( MapilInt32 num )
	{
		m_ReadPos = ( ( m_ReadPos + num ) % DEPTH );
		m_Interval--;
	}

	// Forward position of writing.
	template < typename Type, MapilInt32 DEPTH >
	MapilVoid RingBuffer < Type, DEPTH > ::ForwardWritePos( MapilInt32 num )
	{
		m_WritePos = ( ( m_WritePos + num ) % DEPTH );
		m_Interval++;
	}

	// Is ring buffer full?
	template < typename Type, MapilInt32 DEPTH >
	MapilBool RingBuffer < Type, DEPTH > ::IsFull() const
	{
		return ( m_Interval == DEPTH ) ? MapilTrue : MapilFalse;
	}

	// Is ring buffer empty?
	template < typename Type, MapilInt32 DEPTH >
	MapilBool RingBuffer < Type, DEPTH > ::IsEmpty() const
	{
		return ( m_Interval == 0 ) ? MapilTrue : MapilFalse;
	}

	// Get interval between position of reading and position of writing.
	template < typename Type, MapilInt32 DEPTH >
	inline MapilInt32 RingBuffer < Type, DEPTH > ::GetInterval() const
	{
		return m_Interval;
	}

	// Reset ring buffer.
	template < typename Type, MapilInt32 DEPTH >
	MapilVoid RingBuffer < Type, DEPTH > ::Reset()
	{
		m_ReadPos = 0;
		m_WritePos = 0;
		m_Interval = 0;
		ZeroObject( m_pBuf, sizeof( Type ) * DEPTH );
	}
}

#endif
