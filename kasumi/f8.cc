#include "kasumi.h"
#include <stdio.h>
 
void f8( u8 *key, int count, int bearer, int dir, u8 *data, int length )
{
	REGISTER64 A;		
	REGISTER64 temp;		
	int i, n;
	u8  ModKey[16];		
	u16 blkcnt;			
 
	temp.b32[0]  = temp.b32[1]  = 0;
	A.b32[0]     = A.b32[1]     = 0;
 
 
	A.b8[0]  = (u8) (count>>24);
	A.b8[1]  = (u8) (count>>16);
	A.b8[2]  = (u8) (count>>8);
	A.b8[3]  = (u8) (count);
	A.b8[4]  = (u8) (bearer<<3);
	A.b8[4] |= (u8) (dir<<2);
 
 
	for( n=0; n<16; ++n )
		ModKey[n] = (u8)(key[n] ^ 0x55);
	KeySchedule( ModKey );
 
	Kasumi( A.b8 );	
 
	blkcnt = 0;
	KeySchedule( key );

 
	while( length > 0 )
	{

		temp.b32[0] ^= A.b32[0];
		temp.b32[1] ^= A.b32[1];
		temp.b8[7] ^= (u8)  blkcnt;
		temp.b8[6] ^= (u8) (blkcnt>>8);
 
 
		Kasumi( temp.b8 );
 
 
		if( length >= 64 )
			n = 8;
		else
			n = (length+7)/8;
 
 
		for( i=0; i<n; ++i )
			*data++ ^= temp.b8[i];
		length -= 64;	
		++blkcnt;		
	}
}
 
