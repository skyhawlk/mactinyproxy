//
//  main.cpp
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#include "main.hpp"
#include "commonheader.h"

ProxyManager *proxymgr = nullptr;

int main()
{
    start:
    printf("Menu:\r\n");
    printf("1: Start Proxy\r\n");
    printf("2: Stop Proxy\r\n");
    printf("e: Exit\r\n");
    printf("?: Help\r\n");
      
    char cmd = '0';
    while(cmd != 'e')
    {
        cmd = getchar();
        if (cmd == '?')
        {
            goto start;
        }
        else if (cmd == '1') // start
        {
           //Start proxy
            proxymgr = new ProxyManager();
            proxymgr->OnStart();
        }
        else if (cmd == '2') // stop
         {
             proxymgr->OnStop();
             cmd = 'e';
             break;
         }
      
    }
    return 0;
}
