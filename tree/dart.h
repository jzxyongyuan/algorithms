/**
* @file   dart.h
* @author wanguanglu(wanguanglu@qq.com)
* @date   2016/06/27 12:58:55
* @brief 
*  
**/

#include <assert.h>
#include <logging.h>
#include <vector>

namespace wangl {
namespace algorithm {


struct DartNode {
    int _code;
    int _depth;
    int _left;
    int _right;
};

struct DartUnit {
    int _base;
    int _check;
};

struct DartInstance {
    int _next_check_pos;
};

class DoubleArray {

typedef std::vector<int> KeyType;

public:
    DoubleArray() {
        _array      = NULL;
        _alloc_size = 0;
    }

    ~DoubleArray() {
        if (_array) {
            delete [] _array;
        }
    }

    int resize(int new_size) {
        assert(new_size >= 0);

        if (new_size == 0) {
            if (_array) {
                delete [] _array;
            }
            _alloc_size = 0;
            return 0;
        }

        DartUnit* new_array = new DartUnit[new_size];
        if (new_array == NULL) {
            log_fatal("new for new_array failed.");
            return -1;
        }

        for (int i=0; i<_alloc_size; i++) {
            new_array[i] = _array[i];
        }

        for (int i=_alloc_size; i<new_size; i++) {
            new_array[i]._base  = 0;
            new_array[i]._check = 0;
        }

        delete [] _array;
        _array      = new_array;
        _alloc_size = new_size;
        
        return 0;
    }

    int fetch(DartNode& parent, std::vector<KeyType>& keys,
              std::vector<DartNode>& siblings) {

        int length = 0;
        int pre    = -1;
        int cur    = 0;
        siblings.clear();

        for (int index=parent._left; index<parent._right; index++) {
            KeyType& key = keys[index];
            length = key.size();

            if (length < parent._depth) {
                continue;
            }

            cur = length == parent._depth ? 0 : key[parent._depth];
            if (cur != pre) {
                if (cur < pre) {
                    log_warn("keys is not sorted.");
                    return -1;
                }

                DartNode node;
                node._code  = cur;
                node._depth = parent._depth + 1;
                node._left  = index;

                if (siblings.size() != 0) {
                    siblings[siblings.size()-1]._right = index;
                    node._right = index;
                }
                siblings.push_back(node);

                pre = cur;
            }
        }

        if (siblings.size() != 0) {
            siblings[siblings.size()-1]._right = parent._right;
        }

        return 0;
    }

    int insert(std::vector<KeyType>& keys, std::vector<DartNode>& siblings, 
                        DartInstance& instance, int start) {

        int base = (instance._next_check_pos > siblings[0]._code ? instance._next_check_pos : siblings[0]._code) - siblings[0]._code;
        size_t i    = 0;
        int nonzero_num = 0;
        int ret  = 0;
        int next = 0;

        log_debug("start: %d depth:%d.", start, siblings[0]._depth);

        for (i=0; i<siblings.size(); i++) {
            log_debug("siblings[%d]: %d", i, siblings[i]._code);
        }

        while (true) {
            for (i=0; i<siblings.size(); i++) {
                DartNode& node = siblings[i]; 
                next       = base + node._code;

                if (_alloc_size < next) {
                    resize(next + next/2);
                }
                
                if(_array[next]._check != 0) {
                    nonzero_num ++;
                    break;
                }
            }

            if (i != siblings.size()) {
                base ++;
            } else {
                break;
            }
        }

        if (1.0*nonzero_num /(base+siblings[0]._code) > 0.95) {
            instance._next_check_pos = base + siblings[0]._code;
        }

        log_debug("base: %d", base);

        for (i=0; i<siblings.size(); i++) {
            DartNode& node = siblings[i]; 
            next = base + node._code;
            _array[next]._check = start;
            log_debug("next: %d start %d.", next, start);
        }

        for (i=0; i<siblings.size(); i++) {
            DartNode& node = siblings[i]; 
            next = base + node._code;

            std::vector<DartNode> next_siblings;
            ret = fetch(node, keys, next_siblings);
            if (ret < 0) {
                log_warn("fetch for node failed.");
                return -1;
            }

            if (next_siblings.size() == 0) {
                _array[next]._base = - node._left - 1;
            } else {
                ret = insert(keys, next_siblings, instance, next);
                
                if (ret < 0) {
                    log_warn("insert failed.");
                    return -1;
                }
                _array[next]._base = ret;
            }
        }

        return base;
    }

    int build(std::vector<KeyType>& keys) {
        int ret = 0;
        resize(8092);

        DartNode root;
        root._code  = 0;
        root._depth = 0;
        root._left  = 0;
        root._right = keys.size();

        //virtual node
        _array[0]._base  = -1;
        _array[0]._check = -1;

        //check is root
        _array[1]._check = -1;
        std::vector<DartNode> siblings;
        ret = fetch(root, keys, siblings);
        if (ret != 0) {
            log_warn("fetch siblings failed.");
            return -1;
        }

        if (siblings.size() == 0) {
            log_warn("siblings is empty.");
            return 0;
        }

        DartInstance instance;
        instance._next_check_pos = 0;

        _array[1]._base = insert(keys, siblings, instance, 1);

        return 0;
    }

    int exact_match(KeyType& key) {
        int start = 1;
        int next  = 0;

        for (size_t i=0; i<key.size(); i++) {
            next = _array[start]._base + key[i]; 
            if (_array[next]._check != start) {
                return -1;
            }

            start = next;
        }

        next = _array[start]._base + 0;
        if (_array[next]._check != start) {
            return -1;
        }

        int ret = -_array[next]._base-1;
        return ret;
    }

private:
    DartUnit* _array;
    int       _alloc_size;
};

}
}
