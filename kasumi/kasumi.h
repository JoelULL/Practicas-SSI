typedef unsigned  char   u8;
typedef unsigned short  u16;
typedef unsigned  long  u32;
 
typedef union {
	u32 b32[2];
	u16 b16[4];
	u8  b8[8];
} REGISTER64;
 

void KeySchedule( u8 *key );
void Kasumi( u8 *data );
u8 * f9( u8 *key,int count,int fresh, int dir,u8 *data,int length );
void f8( u8 *key,int count,int bearer,int dir,u8 *data,int length );