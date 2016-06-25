/**
* @file   stack.h
* @author wanguanglu(wanguanglu@qq.com)
* @date   2016/06/16 23:27:11
* @brief 
*  
**/

#include <boost/exception/all.hpp>

namespace glorey {
namespace algorithm {

//定义错误信息类型，
typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;
class StackException : virtual public std::exception,
                       virtual public boost::exception {
};

/**
 * class stack
 */
template <class T>
class Stack {

public:
    Stack(int capacity) {
        _array     = new T[capacity];
        if (NULL == _array) {
            throw StackException()<< err_no(-1) << err_str("new for stack array failed.");
        }
        this->_capacity = capacity;
        this->_size = 0;
    }

    ~Stack() {
        if (_array) {
            delete []_array;
        }
    }

    void push(const T& value) {
        if (_size == _capacity) {
            throw StackException()<< err_no(-1) << err_str("stack is full.");
        }

        _array[_size++] = value;
    }

    T pop() {
        if (_size == 0) {
            throw StackException()<< err_no(-1) << err_str("stack is empty.");
        }

        return _array[--_size];
    }

    int size() {
        return _size;
    }

private:
    T*  _array;
    int _capacity;
    int _size;
};

}
}
