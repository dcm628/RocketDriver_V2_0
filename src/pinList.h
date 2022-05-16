#ifndef PINLIST_H
#define PINLIST_H

namespace pin
{
    
    const int led = 13;
    

    // Node Addressing pins
    const int NodeAddress0{0};
    const int NodeAddress1{1};
    const int NodeAddress2{28};
    const int NodeAddress3{29};   // Need to figure out this pin assignment to get the extra NodeID space

    // abort interrupt pins - Not fully implemented, need to test and check
    const int abort{};
/*     const int abort{};         //Need to find the pins I want to use for this

    const int Node2Node1{};  //These are for a non CAN bus digital I/O pin.
    const int Node2Node2{}; */
    

    


};

#endif