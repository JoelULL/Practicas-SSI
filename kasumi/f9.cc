#include "kasumi.h"
#include <stdio.h>
 
u8 *f9( u8 *key, int count, int fresh, int dir, u8 *data, int length )
{
	REGISTER64 A;	
	REGISTER64 B;	
	u8  FinalBit[8] = {0x80, 0x40, 0x20, 0x10, 8,4,2,1};
	u8  ModKey[16];
	static u8 mac_i[4];	
	int i, n;
 
	KeySchedule( key );
 
	for( n=0; n<4; ++n )
	{
		A.b8[n]   = (u8)(count>>(24-(n*8)));
		A.b8[n+4] = (u8)(fresh>>(24-(n*8)));
	}
	Kasumi( A.b8 );
	B.b32[0] = A.b32[0];
	B.b32[1] = A.b32[1];
 
	while( length >= 64 )
	{
		for( n=0; n<8; ++n )
			A.b8[n] ^= *data++;
		Kasumi( A.b8 );
		length -= 64;
		B.b32[0] ^= A.b32[0];	
		B.b32[1] ^= A.b32[1];	
	}
 
	n = 0;
	while( length >=8 )
	{
		A.b8[n++] ^= *data++;
		length -= 8;
	}

	if( length )
	{
		i = *data;
		if( dir )
			i |= FinalBit[length];
	}
	else
		i = dir ? 0x80 : 0;
 
	A.b8[n++] ^= (u8)i;
 
 
	if( (length==7) && (n==8 ) )	
	{
		Kasumi( A.b8 );
		B.b32[0] ^= A.b32[0];	
		B.b32[1] ^= A.b32[1];	
 
		A.b8[0] ^= 0x80;			
		i = 0x80;
		n = 1;
	}
	else
	{
		if( length == 7 )		
			A.b8[n] ^= 0x80;		
		else
			A.b8[n-1] ^= FinalBit[length+1];
	}
 
	Kasumi( A.b8 );
	B.b32[0] ^= A.b32[0];
	B.b32[1] ^= A.b32[1];	
 
	for( n=0; n<16; ++n )
		ModKey[n] = (u8)*key++ ^ 0xAA;
	KeySchedule( ModKey );
	Kasumi( B.b8 );
 
	for( n=0; n<4; ++n )
		mac_i[n] = B.b8[n];
 
	return( mac_i );
}