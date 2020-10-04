//
//  urlfiltering.c
//  mactinyproxy
//
//  Created by Avishay Dinar on 23/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#include "urlfiltering.h"
#include <curl/curl.h>

void categorizeurl(char *url, char *content)
{
    CURLcode ret;
    CURL *hnd;
    struct curl_slist *slist1;
    char *jsonstr = url;
    sprintf(jsonstr, "{\"url\":\"%s""}", url);
    

    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");
    slist1 = curl_slist_append(slist1, "X-Nimbus-ClientId: m_NimbusClientID");

    hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_URL, "https://nimbus.bitdefender.net/batch/url/status");
    curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jsonstr);
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "tdproxy");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

    ret = curl_easy_perform(hnd);

    curl_easy_cleanup(hnd);
    hnd = NULL;
    curl_slist_free_all(slist1);
    slist1 = NULL;

}
