/**
* @file   stack.h
* @author wanguanglu(wanguanglu@qq.com)
* @date   2016/06/16 23:27:11
* @brief 
*  
**/

#include <boost/exception/all.hpp>

namespace wangl {
namespace algorithm {


/**
 * class stack
 */
template <class T>
class Stack {

public:
    Stack(int capacity) {
        _array     = new T[capacity];
        assert(_array != NULL);
        this->_capacity = capacity;
        this->_size = 0;
    }

    ~Stack() {
        if (_array) {
            delete []_array;
        }
    }

    void push(const T& value) {
        assert(_size != _capacity);
        _array[_size++] = value;
    }

    T pop() {
        assert(_size != 0);
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
