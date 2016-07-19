/**
* @file   test.cpp
* @author wanguanglu(wanguanglu@qq.com)
* @date   2016/06/25 17:58:53
* @brief 
*  
**/

#include <logging.h>
#include <stack/stack.h>

using namespace wangl::algorithm;

int test1() {
    Stack<int> stack(4);
    for (int i=0; i<10; i++) {
        stack.push(i);
    }

    while (stack.size() != 0) {
        log_info("pop from stack %d.", stack.pop());
    }
    return 0;
}

int test2() {
    Stack<int> stack(10);
    for (int i=0; i<10; i++) {
        stack.push(i);
    }

    while (stack.size() != 0) {
        log_info("pop from stack %d.", stack.pop());
    }
    return 0;
}

int main(int argc, char* argv[]) {
    test2();
    return 0;
}
