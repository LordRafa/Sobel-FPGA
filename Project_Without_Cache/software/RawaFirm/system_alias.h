/*
 * system_alias.h
 *
 *  Created on: 09/10/2012
 *      Author: Lord_Rafa
 */

#ifndef SYSTEM_ALIAS_H_
#define SYSTEM_ALIAS_H_

#include "system.h"

#define ALT_VIP_VFR_0_BASE SISTEMAVIDEO_FRAMEREADER_BASE
#define FrameWrite_HW(A) ALT_CI_SOBEL_INSTRUCTION_SET(0, A, A);
#define AGrises_HW(A) ALT_CI_SOBEL_INSTRUCTION_SET(1, A, A);
#define Sobel_HW(A,B) ALT_CI_SOBEL_INSTRUCTION_SET(2, A, B);

#endif /* SYSTEM_ALIAS_H_ */
