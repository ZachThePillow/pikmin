#include "types.h"

typedef struct {
	char* _0;
	char* _4;
	char* _8;
	char* _C;
	char* _10;
	char* _14;
	char* _18;
	char* _1C;
	char* _20;
	char* _2C;
	char _30;
	char _31;
	char _32;
	char _33;
	char _34;
	char _35;
	char _36;
	char _37;
} lconv;

const char stringBase0[] = ".\0\0C";

lconv __lconv = { stringBase0,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              stringBase0 + 2,
	              0x7F,
	              0x7F,
	              0x7F,
	              0x7F,
	              0x7F,
	              0x7F,
	              0x7F,
	              0x7F };
