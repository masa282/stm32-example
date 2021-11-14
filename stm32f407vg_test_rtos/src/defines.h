#ifndef _DEFINES_H_
#define _DEFINES_H_

#include "stdint.h"

typedef void (*FP)(void);
typedef int32_t ER;
#define E_OK (0)
#define E_ID (-18)
#define E_OBJ (-41)
#define __NAKED __attribute__((naked))

#endif
