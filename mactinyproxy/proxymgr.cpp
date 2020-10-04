//
//  proxymgr.cpp
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#include "proxymgr.hpp"
#include "commonheader.h"


int ProxyManager::filterurl(const char *url)
{
    
    //0 - pass
    //1 - deny
    
    return FILTER_DEFAULT_ALLOW;
}



bool ProxyManager::OnStartThread(const void* object, const void* privateData)
{
    bool ret = false;
    ProxyManager* proxyManager = nullptr;
    
    do
    {
        proxyManager = (ProxyManager*)object;
        
        void* authtoken = nullptr;
        //Add the proxy settings to the OSX config for HTTP/HTTPS
        set_global_proxy(1, "127.0.0.1", 8888, authtoken);
        
        proxyManager->authtoken = authtoken;
        
        
        startverbs *verbs = new startverbs();
        verbs->cb = filterurl;
        
        start((void *)verbs);
     
        ret = true;
    }
    while(false);
    
    if (proxyManager != nullptr)
    {
       
    }
     
    return ret;
}

bool ProxyManager::OnStop()
{
    bool ret = false;
     
     do
     {
         //remove OSX proxy settings
          set_global_proxy(0, "127.0.0.1", 8888, this->authtoken);
         
         //Wait for thread to join
         return 0;
         
         std::cout << "Exiting Main Function" << std::endl;
         
         //m_pOnStartThread = new std::thread(ProxyManager::OnStartThread,(void*)this, privateData);

         ret = true;
     }
     while(false);
      
     return ret;
    
}
bool ProxyManager::OnStart(void* privateData /*= nullptr*/)
{
    bool ret = false;
    
    do
    {
        
        
        m_pOnStartThread = new std::thread(ProxyManager::OnStartThread,(void*)this, privateData);

        ret = true;
    }
    while(false);
     
    return ret;

}
