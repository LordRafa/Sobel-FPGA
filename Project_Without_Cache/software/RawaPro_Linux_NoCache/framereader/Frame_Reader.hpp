#ifndef FRAME_READER_HPP_
#define FRAME_READER_HPP_

#include "Vipcore.hpp"

class Frame_Reader : public Vipcore{
  public:

    static const int interrupt_addressoffset = 2;
    static const int packet_bank_addressoffset = 3;
    static const int pb0_base_addressoffset = 4;
    static const int pb0_words_addressoffset = 5;
    static const int pb0_samples_addressoffset = 6;
    //static const int pb0_reserved_addressoffset = 7;
    static const int pb0_width_addressoffset = 8;
    static const int pb0_height_addressoffset = 9;
    static const int pb0_interlaced_addressoffset = 10;
    static const int pb1_base_addressoffset = 11;
    static const int pb1_words_addressoffset = 12;
    static const int pb1_samples_addressoffset = 13;
    //static const int pb1_reserved_addressoffset = 14;
    static const int pb1_width_addressoffset = 15;
    static const int pb1_height_addressoffset = 16;
    static const int pb1_interlaced_addressoffset = 17;

    Frame_Reader(long base_address) : Vipcore(base_address)
    {}

    /* DIAGNOSTIC/STATUS METHODS */

    void set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced)
    {
        do_write(pb0_base_addressoffset, base_address);
        do_write(pb0_words_addressoffset, words);
        do_write(pb0_samples_addressoffset, samples);
        do_write(pb0_width_addressoffset, width);
        do_write(pb0_height_addressoffset, height);
        do_write(pb0_interlaced_addressoffset, interlaced);
    }

    void set_frame_1_properties(int base_address, int words, int samples, int width, int height, int interlaced)
    {
        do_write(pb1_base_addressoffset, base_address);
        do_write(pb1_words_addressoffset, words);
        do_write(pb1_samples_addressoffset, samples);
        do_write(pb1_width_addressoffset, width);
        do_write(pb1_height_addressoffset, height);
        do_write(pb1_interlaced_addressoffset, interlaced);
    }

    void clear_interrupt()
    {
        do_write(interrupt_addressoffset, 0);
    }

    void switch_to_pb0()
    {
        do_write(packet_bank_addressoffset, 0);
    }

    void switch_to_pb1()
    {
        do_write(packet_bank_addressoffset, 1);
    }

    /* END DIAGNOSTIC/STATUS METHODS */
};

#endif /*FRAME_READER_HPP_*/
