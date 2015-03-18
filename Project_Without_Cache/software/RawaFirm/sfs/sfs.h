/*
 * sfs.h
 *
 *  Created on: 12/04/2013
 *      Author: lordrafa
 */

#ifndef SFS_H_
#define SFS_H_

#include <stdio.h>
#include <stdlib.h>
#include "../system_alias.h"

extern char fmask;

void AGrises(unsigned int P[480][800]);
void Sobel(unsigned int P[480][800], unsigned int N[480][800]);

#endif /* SFS_H_ */
