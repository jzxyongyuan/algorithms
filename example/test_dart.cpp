/**
* @file   test_dart.cpp
* @author wanguanglu(wanguanglu@qq.com)
* @date   2016/06/27 13:22:39
* @brief 
*  
**/

#include <logging.h>
#include <tree/dart.h>

int main(int argc, char* argv[]) {

    std::vector<std::vector<int> > keys;

    std::vector<int> key1;
    key1.push_back(1);
    key1.push_back(2);
    key1.push_back(3);
    keys.push_back(key1);

    std::vector<int> key2;
    key2.push_back(1);
    key2.push_back(4);
    keys.push_back(key2);

    wangl::algorithm::DoubleArray dart;

    dart.build(keys);

    int ret = dart.exact_match(key1);
    log_info("find index of key1 %d.", ret);

    ret = dart.exact_match(key2);
    log_info("find index of key2 %d.", ret);

    key2.push_back(5);
    ret = dart.exact_match(key2);
    log_info("find index of key2 %d.", ret);
    return 0;
}
