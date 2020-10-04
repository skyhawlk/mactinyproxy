//
//  global-config-support.hpp
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#ifndef global_config_support_hpp
#define global_config_support_hpp

//#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

 int set_global_proxy(int enable, const char* host, int port, void* authtoken);

#ifdef __cplusplus
}
#endif


#endif /* global_config_support_hpp */
