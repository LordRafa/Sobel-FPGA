/*
 * sfs.c
 *
 *  Created on: 13/04/2013
 *      Author: lordrafa
 */

#include "sfs.h"

void AGrises(unsigned int P[480][800]) {
	if ((fmask & 8) == 0) {
		int x, y;
		int gris;
		for (y = 0; y < 480; y++) {
			for (x = 0; x < 800; x++) {
				gris = (30 * (P[y][x] & 0xFF) + 60 * ((P[y][x] & 0xFF00) >> 8)
						+ 10 * ((P[y][x] & 0xFF0000) >> 16)) / 100;
				P[y][x] = gris | (gris << 8) | (gris << 16);
			}
		}
	} else {
		AGrises_HW((int)P);
	}
}

void Sobel(unsigned int P[480][800], unsigned int N[480][800]) {
	if ((fmask & 8) == 0) {
		unsigned int gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
		unsigned int gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
		int x, y,i ,j;
		int sumgx, sumgy, sum;
		for (y = 0; y < 480; y++) {
			for (x = 0; x < 800; x++) {
				sumgx = 0;
				sumgy = 0;
				for (i = -1; i < 2; i++) {
					for (j = -1; j < 2; j++) {
						sumgx += gx[1 + j][1 + i] * (P[y + j][x + i] & 0xff);
						sumgy += gy[1 + j][1 + i] * (P[y + j][x + i] & 0xff);
					}
				}
				sum = abs(sumgx) + abs(sumgy);
				sum = sum > 255 ? 255 : sum;
				sum = 255 - sum;
				N[y][x] = sum | (sum << 8) | (sum << 16);
			}
		}
	} else {
		Sobel_HW((int)P, (int)N);
	}
}



