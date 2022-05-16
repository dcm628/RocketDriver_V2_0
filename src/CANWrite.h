#ifndef CANWRITE_H
#define CANWRITE_H

#include <array>
#include <FlexCAN.h>

// This header contains the code needed to package and send CAN messages to the Raspberry Pi during a static fire

// Define CAN ids here:




template<std::size_t size>
void CANwrite(FlexCAN& CANbus, const std::array<uint8_t, size>& messageArray, const int& CanID)
{
    if (messageArray.size() <= 8) // max message size is 8 bytes, so we need to check we're not giving it a message thats too long
    {
        // build message
        static CAN_message_t msgOut;

        msgOut.ext = 1;
        msgOut.id = CanID;
        msgOut.len = messageArray.size();

        int index{0};
        for(uint8_t value : messageArray)
        {
            msgOut.buf[index] = value;
            ++index;
        }

        // write message to bus

        CANbus.write(msgOut);
        {
            // add write error handling here, for now it does nothing
        }

    }
    else
    {
        // function can print an error to serial here for debugging purposes
    }
}




#endif