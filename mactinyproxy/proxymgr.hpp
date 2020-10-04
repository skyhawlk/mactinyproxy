//
//  proxymgr.hpp
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#ifndef proxymgr_hpp
#define proxymgr_hpp

#include "commonheader.h"


typedef int onFilterURL(void* object);

class ProxyManager
{
private:
    std::thread* m_pOnStartThread;
    // Create a std::promise object
    std::promise<void> exitSignal;
    //Fetch std::future object associated with promise
    std::future<void> futureObj = exitSignal.get_future();
    
    void* authtoken;
    static int filterurl(const char *url);
    
    static bool OnStartThread(const void* object,const void* privateData);
public:

    ProxyManager(){};
    ~ProxyManager(){};
    
    bool OnStart(void* privateData = nullptr);
    
    /// <summary>
    /// Stop Product Component
    /// </summary>
    /// <param name="threads">threads caller have to wait for their termination.</param>
    /// <param name="tasks">tasks caller have to wait for their termination.</param>
    /// <returns>true for success, false for an error</returns>
    bool OnStop();

    /// <summary>
    /// Call this function to resume operations early stage in the resume procudure.
    /// When suspended, new events and registered events are ignored.
    /// </summary>
    /// <returns>true for success, false for an error</returns>
    bool OnEarlyResume();

    /// <summary>
    /// Call this function to resume operations
    /// When suspended, new events and registered events are ignored.
    /// </summary>
    /// <returns>true for success, false for an error</returns>
    bool OnResume();

    /// <summary>
    /// Call this function to suspend operations
    /// When suspended, new events and registered events are ignored.
    /// </summary>
    /// <returns>true for success, false for an error</returns>
    bool OnSuspend();
    
};

#endif /* proxymgr_hpp */
