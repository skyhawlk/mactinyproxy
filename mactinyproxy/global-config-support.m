//
//  global-config-support.cpp
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#include "global-config-support.h"
#include <Foundation/Foundation.h>
#include <SystemConfiguration/SystemConfiguration.h>


int set_global_proxy(int enable, const char* host, int port, void* authtoken)
{
    printf("set global proxy %d %s %d\n", enable, host, port);
    
    AuthorizationRef auth = nil;
    OSStatus authErr = noErr;

    AuthorizationFlags rootFlags = kAuthorizationFlagDefaults
    | kAuthorizationFlagExtendRights
    | kAuthorizationFlagInteractionAllowed
    | kAuthorizationFlagPreAuthorize;

    auth = (AuthorizationRef) authtoken;
 
    authErr = AuthorizationCreate(nil, kAuthorizationEmptyEnvironment,
                                  rootFlags, &auth);
    
    authtoken = (void*)auth;
  
    SCPreferencesRef pref;
    //SCPreferencesRef prefsWithAuth;

    
    if ( geteuid() != 0 )
    {
        pref = SCPreferencesCreateWithAuthorization(NULL, CFSTR("setproxy"), NULL, auth);
    }
    else
    {
        pref = SCPreferencesCreate(NULL, CFSTR("setproxy"), NULL);
    }

    if (pref == nil)
    NSLog(@"InterfaceConfig failure");

    if (SCPreferencesLock(pref, TRUE))
    {
    //We got a write lock, that means we can do whatever
    //we want to
    //Library/Preferences/SystemConfiguration/preferences.plist
    NSLog(@"LOCK OBTAINED");
    } else {
    NSLog(@"LOCK NOT OBTAINED");
    }

    
    CFDictionaryRef set = SCPreferencesPathGetValue(pref, CFSTR("/NetworkServices/"));
    
    if(!set){
        printf("Failed to get network services.\n");
    }
    
    CFMutableDictionaryRef mset = CFDictionaryCreateMutableCopy(0, 0, set);

    SCDynamicStoreRef theDynamicStore = SCDynamicStoreCreate(nil, CFSTR("setproxy"), nil, nil);
    CFDictionaryRef returnedPList;
    returnedPList = (CFDictionaryRef)SCDynamicStoreCopyValue(theDynamicStore, CFSTR("State:/Network/Global/IPv4"));
    CFStringRef primaryService = NULL;
    
    if(returnedPList){
        primaryService = (CFStringRef)CFDictionaryGetValue(returnedPList, CFSTR("PrimaryService"));
    }

    size_t size = CFDictionaryGetCount(set);
    
    CFTypeRef *keysTypeRef = (CFTypeRef *) malloc( size * sizeof(CFTypeRef) );
    CFTypeRef *valuesTypeRef = (CFTypeRef *) malloc( size * sizeof(CFTypeRef) );
    
    CFDictionaryGetKeysAndValues(set, (const void **) keysTypeRef, (const void**)valuesTypeRef);
    
    const void **keys = (const void **) keysTypeRef;
    printf("Number of interfaces = %ld\n", size);
    
    int i;
    for(i=0; i<size && keysTypeRef[i]; i++){
        Boolean success;
        CFStringRef service = (CFStringRef)keysTypeRef[i];

        printf("Setting interface %d\n", i);

        if(enable == 1 && primaryService && CFStringCompare(service, primaryService, kCFCompareCaseInsensitive) != 0){
            continue;
        }

        CFTypeRef value = valuesTypeRef[i];
        if(!value){
            continue;
        }
        CFDictionaryRef face = (CFDictionaryRef)value;

        CFMutableDictionaryRef mface = CFDictionaryCreateMutableCopy(0, 0, face);
        CFMutableDictionaryRef mproxy = NULL;
    
        CFDictionaryRef proxy = (CFDictionaryRef)CFDictionaryGetValue(mface, CFSTR("Proxies"));
        
        if(NULL == proxy){
            if(enable == 0){
                CFRelease(mface);
                continue;
            }
            printf("proxy = %p, try to create it\n", proxy);
            mproxy = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        }else{
            mproxy = CFDictionaryCreateMutableCopy(0, 0, proxy);
            if(mproxy == NULL)
                return 4;
        }

        if(enable){
            CFStringRef cfHost = CFStringCreateWithCString(0, host, kCFStringEncodingASCII);
            CFDictionarySetValue(mproxy, CFSTR("HTTPEnable"), CFNumberCreate(0, kCFNumberIntType, &enable));
            CFDictionarySetValue(mproxy, CFSTR("HTTPProxy"), cfHost);
            CFDictionarySetValue(mproxy, CFSTR("HTTPPort"), CFNumberCreate(0, kCFNumberIntType, &port));
            CFDictionarySetValue(mproxy, CFSTR("HTTPSEnable"), CFNumberCreate(0, kCFNumberIntType, &enable));
            CFDictionarySetValue(mproxy, CFSTR("HTTPSProxy"), cfHost);
            CFDictionarySetValue(mproxy, CFSTR("HTTPSPort"), CFNumberCreate(0, kCFNumberIntType, &port));
            CFRelease(cfHost);
        }else{
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPEnable"));
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPProxy"));
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPPort"));
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPSEnable"));
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPSProxy"));
            CFDictionaryRemoveValue(mproxy, CFSTR("HTTPSPort"));
        }

        CFDictionarySetValue(mface, CFSTR("Proxies"), mproxy);
        CFDictionarySetValue(mset, service, mface);

        SCPreferencesPathSetValue(pref, CFSTR("/NetworkServices/"), mset);
        
        if (SCPreferencesCommitChanges(pref))
            printf("successfully committed.\n");
        
        if (SCPreferencesApplyChanges(pref))
            printf("successfully applied changes!\n");

        CFRelease(mface);
        CFRelease(mproxy);
    }

    CFRelease(mset);
    CFRelease(pref);
    free(keysTypeRef);
    free(valuesTypeRef);
    
    return 0;
}
