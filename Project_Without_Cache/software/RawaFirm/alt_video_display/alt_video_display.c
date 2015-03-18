/******************************************************************************
 *                                                                             *
 * License Agreement                                                           *
 *                                                                             *
 * Copyright (c) 2007 Altera Corporation, San Jose, California, USA.           *
 * All rights reserved.                                                        *
 *                                                                             *
 * Permission is hereby granted, free of charge, to any person obtaining a     *
 * copy of this software and associated documentation files (the "Software"),  *
 * to deal in the Software without restriction, including without limitation   *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
 * and/or sell copies of the Software, and to permit persons to whom the       *
 * Software is furnished to do so, subject to the following conditions:        *
 *                                                                             *
 * The above copyright notice and this permission notice shall be included in  *
 * all copies or substantial portions of the Software.                         *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
 * DEALINGS IN THE SOFTWARE.                                                   *
 *                                                                             *
 * This agreement shall be governed in all respects by the laws of the State   *
 * of California and by the laws of the United States of America.              *
 *                                                                             *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/alt_cache.h>
#include <malloc.h>
#include <priv/alt_file.h>
#include <sys/alt_irq.h>
//#include <altera_avalon_sgdma.h>
//#include <altera_avalon_sgdma_descriptor.h>
//#include <altera_avalon_sgdma_regs.h>
#include "system.h"
#include "alt_video_display.h"

int alt_video_display_allocate_buffers_only_frame(alt_video_display* display,
		int bytes_per_frame, int buffer_location, int num_buffers);

/******************************************************************
 *                   PUBLIC API FUNCTIONS                          *
 ******************************************************************/

alt_video_display* alt_video_display_only_frame_init( // char* sgdma_name,
		int width, int height, int color_depth, int buffer_location,
//                                           int descriptor_location,
		int num_buffers) {
	alt_video_display* display;
	unsigned int bytes_per_pixel, bytes_per_frame, descriptors_per_frame, i;
	int result;

	// We'll need these values more than once, so let's pre-calculate them.
	bytes_per_pixel = color_depth >> 3; // same as /8
	bytes_per_frame = ((width * height) * bytes_per_pixel);

#if 0
	// Calculate the number of descriptors needed for each frame
	if( bytes_per_frame <= ALT_VIDEO_DISPLAY_BYTES_PER_DESC ) {
		descriptors_per_frame = 1;
	}
	else if(( bytes_per_frame % ALT_VIDEO_DISPLAY_BYTES_PER_DESC) == 0) {
		descriptors_per_frame = bytes_per_frame / ALT_VIDEO_DISPLAY_BYTES_PER_DESC;
	}
	else {
		descriptors_per_frame =
		( bytes_per_frame / ALT_VIDEO_DISPLAY_BYTES_PER_DESC ) + 1;
	}
#endif
	descriptors_per_frame = 1;

	// Check for too many frame buffers
	if (num_buffers > ALT_VIDEO_DISPLAY_MAX_BUFFERS) {
		num_buffers = ALT_VIDEO_DISPLAY_MAX_BUFFERS;
	}
	// Allocate our display struct
	display = (alt_video_display*) malloc(sizeof(alt_video_display));
	if (!display) {
		return NULL;
	}

	// Fill out the display structure
	display->width = width;
	display->height = height;
	display->color_depth = color_depth;
	display->num_frame_buffers = num_buffers;
	display->bytes_per_frame = bytes_per_frame;
	display->bytes_per_pixel = bytes_per_pixel;
	display->buffer_being_displayed = 0;
	display->buffer_being_written = (num_buffers > 1) ? 1 : 0;
	display->descriptors_per_frame = descriptors_per_frame;

	// Allocate our frame and descriptor buffers
	if (alt_video_display_allocate_buffers_only_frame(display, bytes_per_frame,
			buffer_location,
//                                         descriptor_location,
			num_buffers)) {
		return NULL;
	}

	// Clear all frame buffers to black
	for (i = 0; i < num_buffers; i++) {
		memset((void*) (display->buffer_ptrs[i]->buffer),
				ALT_VIDEO_DISPLAY_BLACK_8, display->bytes_per_frame);
	}

//  if(result) {
//    return NULL;
//  }

	return (display);
}

/******************************************************************
 *  Function: alt_video_display_init
 *
 *  Purpose: Initializes the display controller. Gets memory for the
 *           frame buffer and descriptor buffers, intitalizes the
 *           descriptors, sets the resolution of the frame buffers,
 *           clears all the frame buffers, then finally opens
 *           the SGDMA, registers the SGDMA callback function and
 *           starts the SGDMA.
 *
 *  Returns: *Note non-standard return code!*:
 *           Pointer to the display controller structure, or NULL on failure.
 ******************************************************************/

/******************************************************************
 *  Function: alt_video_display_close
 *
 *  Purpose: Closes the display and frees all malloc'd memory
 *
 *  Returns:  void
 *
 ******************************************************************/

/******************************************************************
 *  Function: alt_video_display_register_written_buffer
 *
 *  Purpose: Registers the buffer pointed to by buffer_being_written
 *           as being finished and ready for display.
 *
 *  Returns: 0 - Everything is groovy.
 *           1 - buffer_being_written is now equal to buffer_being_displayed
 *                 - It would be a good idea to wait for buffer_being_displayed
 *                   to increment before writing to buffer_being_written.
 *
 ******************************************************************/

/******************************************************************
 *  Function: alt_video_display_buffer_is_available
 *
 *  Purpose: Checks for a free frame buffer to write to.
 *
 *  Returns:  0 - Found free buffer.  buffer_being_written now points to it.
 *           -1 - Free buffer not available at this time.
 *
 ******************************************************************/

/******************************************************************
 *  Function: alt_video_display_clear_screen
 *
 *  Purpose: Uses the fast memset routine to clear the entire frame
 *           buffer.  User can specify black(0x00) or white(0xFF).
 *
 ******************************************************************/
inline void alt_video_display_clear_screen(alt_video_display* display,
		char color) {
	memset(
			(void*) (display->buffer_ptrs[display->buffer_being_written]->buffer),
			color, display->bytes_per_frame);
}

/******************************************************************
 *                     PRIVATE FUNCTIONS                           *
 ******************************************************************/

/******************************************************************
 * alt_video_display_setup_frame_descriptors
 *
 * Populate and prepare a video frame's SGDMA descriptors.
 *
 * Arguments:
 *   *display: The video display the frame is being prepared for
 *   *frame: The video frame you're constructing
 *   *buffer: The starting-address of your physical display buffer.
 *    This must be a single, continuous span of memory large enough
 *    for each pixel in the frame.
 *   *desc_base: The starting-address of memory allocated for
 *    SGDMA descriptors. Descriptor memory must be aligned to a
 *    0x20 boundary.
 ******************************************************************/

/******************************************************************
 * alt_video_display_get_descriptor_span
 *
 * Calculate the number of bytes requireed for descriptor storage
 * of a particular display. This is useful for allocating memory or
 * allocating pointers at runtime for creating new video frames.
 *
 * This routine adds two to the physical number of descriptors stored
 * in the display's properties in order to assist your memory-allocation
 * needs; the SGDMA API requires a "next" which, for the final descriptor
 * in a chain requires one extra descriptor. A second "extra" descriptor-span
 * is added to afford address alignment; SGDMA descriptors must be aligned
 * to 0x20-byte boundaries. The alt_video_display_allocate_buffers() routine
 * contains examples of these.
 *
 * Arguments:
 *   - *display: (Initialized) Video display to calculate descriptor memory
 *               requirements for
 *
 * Returns:
 *   - Size (bytes) of descriptor memory required.
 ******************************************************************/

/******************************************************************
 *  Function: alt_video_display_allocate_buffers
 *
 *  Purpose: Allocates memory for both the frame buffers and the
 *           descriptor chains.
 *
 *           If ALT_VIDEO_DISPLAY_USE_HEAP is specified for either
 *           the buffer_location or descriptor_location, the memory
 *           is allocated from the heap. Otherwise, buffer_location and
 *           descriptor_locaiton are presumed to contain the base address
 *           of memory sufficient to hold the requested number of descriptors
 *           and video frames. This memory space may be quite large.
 *
 *  Returns:  0 - Success
 *           -1 - Error allocating memory
 ******************************************************************/

int alt_video_display_allocate_buffers_only_frame(alt_video_display* display,
		int bytes_per_frame, int buffer_location, int num_buffers) {
	int i, ret_code = 0;

	/* Allocate our frame buffers and descriptor buffers */
	for (i = 0; i < num_buffers; i++) {
		display->buffer_ptrs[i] = (alt_video_frame*) malloc(
				sizeof(alt_video_frame));

		if (display->buffer_ptrs[i] == NULL) {
			ret_code = -1;
		}

		if (buffer_location == ALT_VIDEO_DISPLAY_USE_HEAP) {
			display->buffer_ptrs[i]->buffer = (void*) alt_uncached_malloc(
					(bytes_per_frame));

			if (display->buffer_ptrs[i]->buffer == NULL)
				ret_code = -1;
		} else {
			display->buffer_ptrs[i]->buffer = (void*) alt_remap_uncached(
					(void*) (buffer_location + (i * bytes_per_frame)),
					bytes_per_frame);
		}

		display->buffer_ptrs[i]->desc_base = ((void*) 0);
	}

	return ret_code;
}
