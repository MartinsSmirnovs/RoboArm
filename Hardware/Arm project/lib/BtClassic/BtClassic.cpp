#include "BtClassic.h"

BtClassic::BtClassic()
{
    _type = 0;
    _value = 0;
    _newData = false;
    for (byte i = 0; i < sizeof(_receivedChars); i++)
        _receivedChars[i] = '\r';
    _receivedChars[sizeof(_receivedChars)] = '\0';
}

void BtClassic::loop()
{
    checkNewData();
}

void BtClassic::checkNewData()
{
    int countDataSwCase; //recvWithStartEndMarkers switch operatora skaititajs
    static bool recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';

    byte numChars = 3;
    char rc; //saja mainigaja tiek saglabats katrs ienakosais baits

    while (Serial.available())
    {
        rc = Serial.read();
        Serial.println(rc);
        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                _receivedChars[ndx] = rc; //no siem datiem tiek pieskirtas mainigo vertibas, kas tiek iesutitas un no saraksta parveidotas skaitli
                ndx++;
                switch (countDataSwCase)
                {
                case 1: //tiek noteikts ienakoso datu tips
                    _type = atoi(_receivedChars);
                    ndx = 0;
                    break;
                case 4: //tiek noteikts kuriem led pikseliem ir jastrada
                    _value = atoi(_receivedChars);
                    ndx = 0;
                    break;
                default:
                    break;
                }
                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }
            }
            else
            {
                for (byte i = 0; i < sizeof(_receivedChars); i++)
                    _receivedChars[i] = '\r';
                _receivedChars[sizeof(_receivedChars)] = '\0'; // terminate the string, svariga koda rindina, kur ieprieks [] ieksa bija ndx. Ndx patstavigi mainas, tapec bija nepieciesams ievietot citu garuma vertibu

                recvInProgress = false;
                _newData = true;
            }
            countDataSwCase++; //datu sadalisanas dalas skaititajs
        }
        else if (rc == startMarker)
        {
            recvInProgress = true;
            countDataSwCase = 1; //reseto mainigo no ieprieksejas vertibas
        }
    }
}

bool BtClassic::getNewData()
{
    if (_newData)
    {
        _newData = false;
        return true;
    }
    return false;
}

byte BtClassic::getType()
{
    return _type;
}

int BtClassic::getValue()
{
    return _value;
}