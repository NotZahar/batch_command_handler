#ifndef BATCH_H
#define BATCH_H

#include <iostream>
#include <list>
#include <memory>
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

        virtual void append(T element) = 0;
        
        virtual void end() {
            if (_batch.empty())
                return;
            std::cout << serialize() << '\n';
            clear();
        }

    protected:
        virtual void clear() = 0;
        virtual std::string serialize() const = 0;

        int _maxSize;
        std::list<T> _batch;
    };

    template <class T>
    class DBatch : public Batch<T> {
    public:
        DBatch(int size)
            : Batch<T>(size),
              _noNestingLevel(0),
              _nestingLevel(_noNestingLevel)
        {}

        ~DBatch() = default;
        
        void append(T element) override {
            assert(blockExists());
            Batch<T>::_batch.push_back(element);
        }

        void addBlock() {
            _nestingLevel += 1;
        }

        bool blockExists() const {
            return _nestingLevel != _noNestingLevel;
        }

        void end() override {
            if (Batch<T>::_batch.empty())
                return;

            _nestingLevel -= 1;
            if (!blockExists()) {
                std::cout << serialize() << '\n';
                clear();                
            }
        }

    protected:
        void clear() override {
            Batch<T>::_batch.clear();
            _nestingLevel = _noNestingLevel;
        }

        std::string serialize() const override {
            std::string serializedBatch = "";
            if (Batch<T>::_batch.empty())
                return serializedBatch;

            serializedBatch += messages::BULK;
            auto it = Batch<T>::_batch.cbegin();
            serializedBatch += (" " + *it);
            for (++it; it != Batch<T>::_batch.cend(); ++it)
                serializedBatch += (", " + *it);
            return serializedBatch;
        }

    private:
        const int _noNestingLevel;
        int _nestingLevel;
    };
    
    template <class T>
    class SBatch : public Batch<T> {
    public:
        SBatch(int size)
            : Batch<T>(size)
        {}

        ~SBatch() = default;

        int size() const {
            return Batch<T>::_batch.size();
        }
        
        void append(T element) override {
            assert(size() < Batch<T>::_maxSize);
            Batch<T>::_batch.push_back(element);
        }

    protected:
        void clear() override {
            Batch<T>::_batch.clear();
        }

        std::string serialize() const override {
            std::string serializedBatch = "";
            if (Batch<T>::_batch.empty())
                return serializedBatch;

            serializedBatch += messages::BULK;
            auto it = Batch<T>::_batch.cbegin();
            serializedBatch += (" " + *it);
            for (++it; it != Batch<T>::_batch.cend(); ++it)
                serializedBatch += (", " + *it);
            return serializedBatch;
        }
    };
}

#endif // BATCH_H