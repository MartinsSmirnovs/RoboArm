#ifndef bt
#include <Arduino.h>
    class BtClassic{
        public:
            BtClassic(); //initializes object
            void checkNewData(); //gets new data and assigns it to variables
            bool getNewData(); //returns true if got new data 
            void loop(); //main loop

            byte getType();//gets type value
            int getValue(); //gets main value
        private:
            byte _type;
            int _value;
            bool _newData;
            char _receivedChars[4];
    };
#endif 


