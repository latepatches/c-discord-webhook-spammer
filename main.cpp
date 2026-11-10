#include <curl/curl.h>
#include <iostream>
#include <thread>
#include <vector>

const char* webhook = "https://discord.com/api/webhooks/1569392604921987072/26hSJAcQ0f5m2HYvWdW6HGTBmgOr2veDwTu0H_6LM8Vr4edcGCanmfSK5TSE5bdLsvC0"; /* discord webhook goes here */
const char* data = R"({"content": "@everyone"})"; /* replace with wanted json to send */
const int amt = 10; /* amount of threads */

std::vector<std::thread> threads = {};

void post(void) {
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "content-type: application/json");
  CURL *c = curl_easy_init();
  if (c) {
    curl_easy_setopt(c, CURLOPT_URL, webhook);
    curl_easy_setopt(c, CURLOPT_POST, 1L);
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);
    CURLcode res = curl_easy_perform(c);
    if (res == CURLE_OK) { std::cout << "success" << std::endl;} else { std::cout << "failed" << std::endl;};
    curl_easy_cleanup(c);
  };
  curl_slist_free_all(headers);
}

int main(void) {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  for (auto i=0;i<amt;i++) { threads.emplace_back(post); };
  for (auto& t : threads) { t.join(); };
  curl_global_cleanup();
  return 0;
}
