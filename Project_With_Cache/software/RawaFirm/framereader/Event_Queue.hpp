#ifndef EVENT_QUEUE_HPP_
#define EVENT_QUEUE_HPP_

class Vipcore;

class EventQueue
{
    public:
    
    EventQueue()
    :read_pointer(0), write_pointer(0)
    {}
    
    struct Event
    {
        Vipcore* core;
        int status;
    };
    
    void push(Vipcore* core, int status) volatile
    {
        cores[write_pointer].core = core;
        cores[write_pointer].status = status;
        write_pointer++;
    }
    
    volatile Event& pop() volatile
    {
        return cores[read_pointer++];
    }
    
    bool is_empty() volatile
    {
        return read_pointer == write_pointer;
    }
    
    private:
    
    static const int CAPACITY = 256;
    
    volatile Event cores[CAPACITY];
    volatile alt_u8 read_pointer;
    volatile alt_u8 write_pointer;
};

#endif /*EVENT_QUEUE_HPP_*/
