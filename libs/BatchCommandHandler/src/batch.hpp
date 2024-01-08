#ifndef BATCH_H
#define BATCH_H

#include <iostream>
#include <list>
#include <cassert>

#include "helper.hpp"

namespace handler {
    template <class T>
    class Batch {
    public:
        Batch() = delete;
        Batch(int size) 
            : _maxSize(size)
        {}

        ~Batch() = default;

        int size() const {
            return _batch.size();
        }

        bool empty() const {
            return _batch.empty();
        }
        
        void clear() {
            _batch.clear();
        }
        
        void append(T element) {
            assert(size() < _maxSize);
            _batch.push_back(std::move(element));
        }

        std::string serialize() const {
            std::string serializedBatch = "";
            if (empty())
                return serializedBatch;

            serializedBatch += messages::BULK;
            auto it = _batch.cbegin();
            serializedBatch += (" " + *it);
            for (++it; it != _batch.cend(); ++it)
                serializedBatch += (", " + *it);
            return serializedBatch;
        }

    private:
        std::list<T> _batch;
        int _maxSize;
    };
}

#endif // BATCH_H