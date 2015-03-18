#ifndef VIPCORE_HPP_
#define VIPCORE_HPP_

#include <altera_avalon_pio_regs.h>
#include <sys/alt_irq.h>
#include <stdio.h>
#include <system.h>
#include <io.h>

#include "Event_Queue.hpp"

#include "version_compatible.h"

using namespace std;

class Vipcore
{
public:

    static const int GO = 0;
    static const int STATUS = 1;
    static const int INTERRUPT = 2;

    Vipcore(long base_address, long irq_number=-1, volatile EventQueue* event_queue=NULL)
            : base_address(base_address), irq_number(irq_number), event_queue(event_queue)
    {
        control = 0;
        if(irq_number != -1)
        	alt_ic_isr_register(0, irq_number, genericISR, this, NULL);
                //printf("cv %d\n", irq_number);
    }

    void stop()
    {
        control = control & -2;
        do_write(GO, control);
    }
    void stop(bool is_blocking)
    {
        stop();
        bool is_running = is_blocking;
        while(is_running)
        {
            is_running = this->is_running();
        }
    }

    void start()
    {
        control = control | 1;
        do_write(GO, control);
    }

    void enable_interrupt(int number)
    {
        control = control | (1 << (number + 1));
        do_write(GO, control);
    }

    bool is_on()
    {
        return control & 0x1;
    }

    bool is_running()
    {
        return do_read(STATUS) & 0x1;
    }

    static void genericISR(void* context)
    {
        Vipcore* core = (Vipcore*)context;
        // Get the status that triggered the interrupt
        int interrupt_status = core->do_read(INTERRUPT);
        // Clear it
        core->do_write(INTERRUPT, -1);
        //core->do_write(INTERRUPT, 1);
        // Put this interrupt on the event queue
        core->event_queue->push((Vipcore*)context, interrupt_status);
        // now re-check the interrupt register...
    }

    int get_status()
    {
        return do_read(STATUS);
    }

    void do_write(int offset, int value)
    {
        IOWR(this->base_address, offset, value);
    }

    int do_read(int offset)
    {
        return IORD(base_address, offset);
    }

    long get_base_address()
    {
        return base_address;
    }

protected:
    long base_address;
    long irq_number;
    volatile EventQueue* event_queue;
    int control;

};

#endif /*VIPCORE_HPP_*/
