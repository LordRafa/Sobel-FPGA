/*************************************************************************
* Copyright (c) 2008 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
*************************************************************************/
/******************************************************************************
 *
 * Description
 * ----------- 
 * This programs demonstrates how to configure and control the Altera Video and
 * Image Processing Suite MegaCore functions using a set of software API
 * classes.
 * 
 * In this example, the program uses these classes to access the register map of
 * the following MegaCore functions:
 * 
 * HSMC Bitec Quad Video daughtercard               (HSMC_Quad_Video.hpp)
 * HSMC Bitec DVI I/O daughtercard                  (HSMC_Dual_DVI.hpp)
 * Clocked Video Input                              (Clocked_Video_Input.hpp)
 * Clocked Video Output                             (Clocked_Video_Output.hpp)
 * Frame Buffer                                     (Frame_Buffer.hpp)
 * Mixer                                            (Mixer.hpp)
 * 
 * The software project also provides classes to access the following MegaCore functions:
 * 
 * Clipper                                          (Clipper.hpp)
 * Scaler                                           (Scaler.hpp)
 * Gamma Corrector                                  (Gamma_Corrector.hpp)
 * Base class to start/stop each video function     (Vipcore.hpp)
 * 
 * The VIP Suite functions are controllable at run-time via Avalon-MM Slave interfaces.
 *
 *
 * This program performs the following functions:
 *  - Initialises the HSMC Bitec Quad Video daughtercard     (HSMC_Quad_Video.hpp) 
 *  - Initialises the HSMC Bitec DVI I/O daughtercard        (HSMC_Dual_DVI.hpp)
 *  - Starts the Frame Buffer MegaCore function              (Frame_Buffer.hpp)
 *  - Initialised the Alpha Blending Mixer MegaCore function (Mixer.hpp)
 *  - Starts the Clocked Video Input MegaCore function       (Clock_Video_Input.hpp) 
 *  - Starts the Clocked Video Output MegaCore function      (Clock_Video_Output.hpp) 
 *  - Writes to the Mixer function to change the location of the Quad Video card video 
 *    stream input relative to the test pattern background image 
 */

#include <system.h>
#include "Frame_Reader.hpp"
#include "unistd.h"
#include "vip_wrapper_for_c_func.h"

#ifdef ALT_VIP_VFR_0_BASE
Frame_Reader * the_frame_reader = ( Frame_Reader *)NULL;
void Frame_Reader_init(void){

   /* Start the Clocked Video Input MegaCore function */
   the_frame_reader = new Frame_Reader(ALT_VIP_VFR_0_BASE);
}
void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced){
   the_frame_reader->set_frame_0_properties(base_address, words, samples, width, height, interlaced);
}
void Frame_Reader_set_frame_1_properties(int base_address, int words, int samples, int width, int height, int interlaced){
   the_frame_reader->set_frame_1_properties(base_address, words, samples, width, height, interlaced);
}
void Frame_Reader_switch_to_pb0(void){
   the_frame_reader->switch_to_pb0();
}
void Frame_Reader_switch_to_pb1(void){
   the_frame_reader->switch_to_pb1();
}
void Frame_Reader_start(void){
  the_frame_reader->start();
}
void Frame_Reader_stop(void){
  the_frame_reader->stop(true);
}

bool Frame_Reader_is_running(void) {
  return the_frame_reader->is_running();
}

void Frame_Reader_enable_interrupt(void){
  the_frame_reader->enable_interrupt(0);
}

#endif  // ALT_VIP_VFR_0_BASE
