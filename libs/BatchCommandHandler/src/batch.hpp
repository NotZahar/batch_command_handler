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
              _nestingLevel(0)
        {}

        ~DBatch() = default;
        
        void append(T element) override {
            throw 1;
        }

        void addBlock() {

            throw 1;
        }

        bool blockExists() const {
            throw 1;
        }

        void end() override {
            throw 1;
        }

    protected:
        void clear() override {
            throw 1;
        }

        std::string serialize() const override {
            throw 1;
        }

    private:
        std::list<DBatch> _dbatches;
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
            Batch<T>::_batch.push_back(std::move(element));
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