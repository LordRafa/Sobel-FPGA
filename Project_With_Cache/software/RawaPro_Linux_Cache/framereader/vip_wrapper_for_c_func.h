#ifndef VIP_WRAPPER_FOR_C_FUNC_H_
#define VIP_WRAPPER_FOR_C_FUNC_H_

#include "../system_alias.h"
//#define NULL ((void *) 0)

#ifdef __cplusplus

extern "C" void Frame_Reader_init(void);
extern "C" void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern "C" void Frame_Reader_set_frame_1_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern "C" void Frame_Reader_switch_to_pb0(void);
extern "C" void Frame_Reader_switch_to_pb1(void);
extern "C" void Frame_Reader_start(void);
extern "C" void Frame_Reader_stop(void);
extern "C" bool Frame_Reader_is_running(void);
extern "C" void Frame_Reader_enable_interrupt(void);

#else

typedef int bool;
extern void Frame_Reader_init(void);
extern void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern void Frame_Reader_set_frame_1_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern void Frame_Reader_switch_to_pb0(void);
extern void Frame_Reader_switch_to_pb1(void);
extern void Frame_Reader_start(void);
extern void Frame_Reader_stop(void);
extern bool Frame_Reader_is_running(void);
extern void Frame_Reader_enable_interrupt(void);

#endif

#endif /*VIP_WRAPPER_FOR_C_FUNC_H_*/
