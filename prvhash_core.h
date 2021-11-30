/**
 * prvhash_core.h version 4.1
 *
 * The inclusion file for the "prvhash_core*" PRVHASH core functions for
 * various state variable sizes. Also includes several auxiliary functions,
 * for endianness-correction.
 *
 * Description is available at https://github.com/avaneev/prvhash
 *
 * License
 *
 * Copyright (c) 2020-2021 Aleksey Vaneev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef PRVHASH_CORE_INCLUDED
#define PRVHASH_CORE_INCLUDED

#include <stdint.h>
#include <string.h>

/**
 * This function runs a single PRVHASH random number generation round. This
 * function can be used both as a hash generator and as a general-purpose
 * random number generator. In the latter case, it is advisable to initially
 * run this function 5 times before using its random output, to neutralize any
 * possible oddities of "Seed"'s and "lcg"'s initial values.
 *
 * To generate hashes, the "lcg" variable should be XORed with entropy input
 * prior to calling this function.
 *
 * @param[in,out] Seed0 The current "Seed" value. Can be initialized to any
 * value.
 * @param[in,out] lcg0 The current "lcg" value. Can be initialized to any
 * value.
 * @param[in,out] Hash0 Current hash word in a hash word array.
 * @return Current random value.
 */

static inline uint64_t prvhash_core64( uint64_t* const Seed0,
	uint64_t* const lcg0, uint64_t* const Hash0 )
{
	uint64_t Seed = *Seed0; uint64_t lcg = *lcg0; uint64_t Hash = *Hash0;

	const uint64_t plcg = lcg;
	const uint64_t mx = Seed * ( lcg - ~lcg );
	const uint64_t rs = mx >> 32 | mx << 32;
	lcg += ~mx;
	Hash += rs;
	Seed = Hash ^ plcg;
	const uint64_t out = lcg ^ rs;

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint32_t prvhash_core32( uint32_t* const Seed0,
	uint32_t* const lcg0, uint32_t* const Hash0 )
{
	uint32_t Seed = *Seed0; uint32_t lcg = *lcg0; uint32_t Hash = *Hash0;

	const uint32_t plcg = lcg;
	const uint32_t mx = Seed * ( lcg - ~lcg );
	const uint32_t rs = mx >> 16 | mx << 16;
	lcg += ~mx;
	Hash += rs;
	Seed = Hash ^ plcg;
	const uint32_t out = lcg ^ rs;

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint16_t prvhash_core16( uint16_t* const Seed0,
	uint16_t* const lcg0, uint16_t* const Hash0 )
{
	uint16_t Seed = *Seed0; uint16_t lcg = *lcg0; uint16_t Hash = *Hash0;

	const uint16_t plcg = lcg;
	const uint16_t mx = (uint16_t) ( Seed * ( lcg - ~lcg ));
	const uint16_t rs = (uint16_t) ( mx >> 8 | mx << 8 );
	lcg += (uint16_t) ~mx;
	Hash += rs;
	Seed = (uint16_t) ( Hash ^ plcg );
	const uint16_t out = (uint16_t) ( lcg ^ rs );

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint8_t prvhash_core8( uint8_t* const Seed0,
	uint8_t* const lcg0, uint8_t* const Hash0 )
{
	uint8_t Seed = *Seed0; uint8_t lcg = *lcg0; uint8_t Hash = *Hash0;

	const uint8_t plcg = lcg;
	const uint8_t mx = (uint8_t) ( Seed * ( lcg - ~lcg ));
	const uint8_t rs = (uint8_t) ( mx >> 4 | mx << 4 );
	lcg += (uint8_t) ~mx;
	Hash += rs;
	Seed = (uint8_t) ( Hash ^ plcg );
	const uint8_t out = (uint8_t) ( lcg ^ rs );

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint8_t prvhash_core4( uint8_t* const Seed0,
	uint8_t* const lcg0, uint8_t* const Hash0 )
{
	uint8_t Seed = *Seed0; uint8_t lcg = *lcg0; uint8_t Hash = *Hash0;

	const uint8_t plcg = lcg;
	const uint8_t mx = (uint8_t) (( Seed * ( lcg - ~lcg )) & 15 );
	const uint8_t rs = (uint8_t) (( mx >> 2 | mx << 2 ) & 15 );
	lcg += (uint8_t) ~mx;
	lcg &= 15;
	Hash += rs;
	Hash &= 15;
	Seed = (uint8_t) ( Hash ^ plcg );
	const uint8_t out = (uint8_t) ( lcg ^ rs );

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint8_t prvhash_core2( uint8_t* const Seed0,
	uint8_t* const lcg0, uint8_t* const Hash0 )
{
	uint8_t Seed = *Seed0; uint8_t lcg = *lcg0; uint8_t Hash = *Hash0;

	const uint8_t plcg = lcg;
	const uint8_t mx = (uint8_t) (( Seed * ( lcg - ~lcg )) & 3 );
	const uint8_t rs = (uint8_t) (( mx >> 1 | mx << 1 ) & 3 );
	lcg += (uint8_t) ~mx;
	lcg &= 3;
	Hash += rs;
	Hash &= 3;
	Seed = (uint8_t) ( Hash ^ plcg );
	const uint8_t out = (uint8_t) ( lcg ^ rs );

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

// Likelihood macros that are used for manually-guided optimization.

#if defined( __GNUC__ ) || defined( __clang__ ) || \
	( defined( __GNUC__ ) && defined( __INTEL_COMPILER ))

	#define PRVHASH_LIKELY( x )  __builtin_expect( x, 1 )
	#define PRVHASH_UNLIKELY( x )  __builtin_expect( x, 0 )

#else // likelihood macros

	#define PRVHASH_LIKELY( x ) ( x )
	#define PRVHASH_UNLIKELY( x ) ( x )

#endif // likelihood macros

// Macros that apply byte-swapping.

#if defined( __GNUC__ ) || defined( __clang__ ) || \
	( defined( __GNUC__ ) && defined( __INTEL_COMPILER ))

	#define PRVHASH_BYTESW32( v ) __builtin_bswap32( v )
	#define PRVHASH_BYTESW64( v ) __builtin_bswap64( v )

#elif defined( _MSC_VER )

	#define PRVHASH_BYTESW32( v ) _byteswap_ulong( v )
	#define PRVHASH_BYTESW64( v ) _byteswap_uint64( v )

#else // defined( _MSC_VER )

	#define PRVHASH_BYTESW32( v ) ( \
		( v & 0xFF000000 ) >> 24 | \
		( v & 0x00FF0000 ) >> 8 | \
		( v & 0x0000FF00 ) << 8 | \
		( v & 0x000000FF ) << 24 )

	#define PRVHASH_BYTESW64( v ) ( \
		( v & 0xFF00000000000000 ) >> 56 | \
		( v & 0x00FF000000000000 ) >> 40 | \
		( v & 0x0000FF0000000000 ) >> 24 | \
		( v & 0x000000FF00000000 ) >> 8 | \
		( v & 0x00000000FF000000 ) << 8 | \
		( v & 0x0000000000FF0000 ) << 24 | \
		( v & 0x000000000000FF00 ) << 40 | \
		( v & 0x00000000000000FF ) << 56 )

#endif // defined( _MSC_VER )

/**
 * This function runs a single PRVHASH random number generation round, an
 * "ideal" core hash function variant. This function can be used both as a
 * hash generator and as a general-purpose random number generator. In the
 * latter case, it is advisable to initially run this function 5 times before
 * using its random output, to neutralize any possible oddities of "Seed"'s
 * and "lcg"'s initial values.
 *
 * To generate hashes, the "lcg" variable should be XORed with entropy input
 * prior to calling this function.
 *
 * @param[in,out] Seed0 The current "Seed" value. Can be initialized to any
 * value.
 * @param[in,out] lcg0 The current "lcg" value. Can be initialized to any
 * value.
 * @param[in,out] Hash0 Current hash word in a hash word array.
 * @return Current random value.
 */

static inline uint64_t prvhash_core64i( uint64_t* const Seed0,
	uint64_t* const lcg0, uint64_t* const Hash0 )
{
	uint64_t Seed = *Seed0; uint64_t lcg = *lcg0; uint64_t Hash = *Hash0;

	Seed ^= Hash ^ lcg;
	Seed *= lcg - ~lcg;
	lcg += ~Seed;
	const uint64_t rs = PRVHASH_BYTESW64( Seed );
	Hash += rs;
	const uint64_t out = lcg ^ rs;

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

static inline uint8_t prvhash_core2i( uint8_t* const Seed0,
	uint8_t* const lcg0, uint8_t* const Hash0 )
{
	uint8_t Seed = *Seed0; uint8_t lcg = *lcg0; uint8_t Hash = *Hash0;

	Seed ^= (uint8_t) ( Hash ^ lcg );
	Seed *= (uint8_t) ( lcg - ~lcg );
	Seed &= 3;
	lcg += (uint8_t) ~Seed;
	lcg &= 3;
	const uint8_t rs = (uint8_t) (( Seed >> 1 | Seed << 1 ) & 3 );
	Hash += rs;
	Hash &= 3;
	const uint8_t out = (uint8_t) ( lcg ^ rs );

	*Seed0 = Seed; *lcg0 = lcg; *Hash0 = Hash;

	return( out );
}

// Endianness-definition macro, can be defined externally (e.g. =1, if
// endianness-correction is unnecessary in any case).

#if !defined( PRVHASH_LITTLE_ENDIAN )
	#if defined( _WIN32 ) || defined( __LITTLE_ENDIAN__ ) || \
		( defined( __BYTE_ORDER__ ) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ )

		#define PRVHASH_LITTLE_ENDIAN 1

	#elif defined( __BIG_ENDIAN__ ) || \
		( defined( __BYTE_ORDER__ ) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ )

		#define PRVHASH_LITTLE_ENDIAN 0

	#else // defined( __BIG_ENDIAN__ )

		#warning PRVHASH: cannot determine endianness, assuming little-endian.

		#define PRVHASH_LITTLE_ENDIAN 1

	#endif // defined( __BIG_ENDIAN__ )
#endif // !defined( PRVHASH_LITTLE_ENDIAN )

// Macros that apply byte-swapping, used for endianness-correction.

#if PRVHASH_LITTLE_ENDIAN

	#define PRVHASH_EC32( v ) ( v )
	#define PRVHASH_EC64( v ) ( v )

#else // PRVHASH_LITTLE_ENDIAN

	#define PRVHASH_EC32( v ) PRVHASH_BYTESW32( v )
	#define PRVHASH_EC64( v ) PRVHASH_BYTESW64( v )

#endif // PRVHASH_LITTLE_ENDIAN

/**
 * An auxiliary function that returns an unsigned 32-bit value created out of
 * individual bytes in a buffer. This function is used to convert endianness
 * of supplied 32-bit unsigned values, and to avoid unaligned memory accesses.
 *
 * @param p 4-byte buffer. Alignment is unimportant.
 */

static inline uint32_t prvhash_lu32ec( const uint8_t* const p )
{
	uint32_t v;
	memcpy( &v, p, 4 );

	return( PRVHASH_EC32( v ));
}

/**
 * An auxiliary function that returns an unsigned 64-bit value created out of
 * individual bytes in a buffer. This function is used to convert endianness
 * of supplied 64-bit unsigned values, and to avoid unaligned memory accesses.
 *
 * @param p 8-byte buffer. Alignment is unimportant.
 */

static inline uint64_t prvhash_lu64ec( const uint8_t* const p )
{
	uint64_t v;
	memcpy( &v, p, 8 );

	return( PRVHASH_EC64( v ));
}

/**
 * Function loads 64-bit message word and pads it with the "final byte". This
 * function should only be called if there is less than 8 bytes left to read.
 * Function performs endianness-correction automatically.
 *
 * @param Msg Message pointer, alignment is unimportant. Should be below or
 * equal to MsgEnd.
 * @param MsgEnd Message's end pointer.
 * @param fb Final byte used for padding.
 */

static inline uint64_t prvhash_lpu64ec( const uint8_t* Msg,
	const uint8_t* const MsgEnd, const uint64_t fb )
{
	const int l = (int) ( MsgEnd - Msg );
	uint64_t r = fb << ( l << 3 );

	if( l > 3 )
	{
		r |= (uint64_t) prvhash_lu32ec( Msg );
		Msg += 4;

		if( Msg < MsgEnd )
		{
			r |= (uint64_t) *Msg << 32;

			if( ++Msg < MsgEnd )
			{
				r |= (uint64_t) *Msg << 40;

				if( ++Msg < MsgEnd )
				{
					r |= (uint64_t) *Msg << 48;
				}
			}
		}

		return( r );
	}

	if( l != 0 )
	{
		r |= *Msg;

		if( ++Msg < MsgEnd )
		{
			r |= (uint64_t) *Msg << 8;

			if( ++Msg < MsgEnd )
			{
				r |= (uint64_t) *Msg << 16;
			}
		}
	}

	return( r );
}

#endif // PRVHASH_CORE_INCLUDED
