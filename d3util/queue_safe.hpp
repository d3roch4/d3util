/*
 * Check the README.txt file at the project root for more information and see
 * The LICENSE.txt file to see the license in use in the project
 */

/* 
 * File:   queue_safe.hpp
 * Author: André Rocha <d3roch4@gmail.com>
 *
 * Created on 11 de Abril de 2017, 20:51
 */

#ifndef QUEUE_SAFE_HPP
#define QUEUE_SAFE_HPP

#include <list>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

template <typename T>
class queue_safe {
public:
    ~queue_safe(){}

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            cond_.wait(lock);
        }
        auto item = queue_.front();
        queue_.pop_front();
        return item;
    }

    void pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            cond_.wait(lock);
        }
        item = queue_.front();
        queue_.pop_front();
    }

    template<typename chrono_duration=std::chrono::microseconds>
    bool try_pop (T& item, chrono_duration timeout = chrono_duration(500))
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if(queue_.empty())
            if(cond_.wait_for(lock, timeout) == std::cv_status::timeout)
                return false;
        item = queue_.front();
        queue_.pop_front();
        return true;
    }

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(item);
        cond_.notify_one();
    }

    void push(T&& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push_back(item);
        cond_.notify_one();
    }

    void clear(){
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.clear();
    }

    typedef T                                        value_type;
    typedef typename std::list<T>::iterator iterator;
    typedef typename std::list<T>::const_iterator const_iterator;

    iterator begin(){
        return queue_.begin();
    }
    const_iterator cbegin(){
        return queue_.cbegin();
    }

    iterator end() {
        return queue_.end();
    }
    const_iterator cend() {
        return queue_.cend();
    }

private:
    std::list<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif /* QUEUE_SAFE_HPP */
