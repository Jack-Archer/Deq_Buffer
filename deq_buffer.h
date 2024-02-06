#pragma once

#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <exception>


template <typename Type>
class DeqBuffer {
public:
    DeqBuffer() = delete;

    DeqBuffer(uint16_t size_) {
        max_size_ = size_;
    }

    auto getDeque() {
        return buf_;
    }

    void clearBuf(){
        buf_.clear();
        cur_size_ = 0;
        std::cerr << "Buffer is cleared" << std::endl;
    }

    bool isEmptyBuf() {
        return buf_.size() == 0;
    }

    uint16_t bufCurSize() {
        return cur_size_;
    }

    void resizeBuf(uint16_t new_size) {
        if(new_size < 0){
            std::cerr << "New size is to small" << std::endl;
            return;
        }
        if(new_size >= max_size_) {
            max_size_ = new_size;
        } else {
            max_size_ = new_size;
            if(cur_size_ >= new_size) {
                buf_.resize(new_size);
                cur_size_ = new_size;
            } else {
                buf_.resize(new_size);
            }
        }
        std::cerr << "Resize Buffer successful" << std::endl;
    }

    void insertFrame(Type frame) {
        if (cur_size_ >= max_size_) {
             buf_.pop_front();
             buf_.emplace_back(frame);
        } else {
             buf_.emplace_back(frame);
             ++cur_size_;
             if(cur_size_ == max_size_) {
                buf_.shrink_to_fit();
             }
            }
    }

    template <typename It>
    void insertRange(It it_begin, It it_end){
        if(std::distance(it_begin, it_end) >= max_size_) {
            buf_.clear();
            std::copy(it_end - max_size_, it_end, std::back_inserter(buf_));
            cur_size_ = max_size_;
        } else {
            std::for_each(it_begin, it_end, [this](auto &element){
                this->insertFrame(element);
            });
        }
    }

    const Type getFrame(uint16_t index) {
        if(index >= cur_size_ || index < 0) {
            throw std::out_of_range("Out of range: incorrect index");
        }
        if(buf_.empty()) {
            throw std::underflow_error("The Buffer is empty");
        }
        return buf_.at(index);
    }

     const std::vector<Type> getFrameRange(uint16_t start_index, uint16_t end_index) {
        std::vector<Type> out_range;
        if(start_index < 0 || start_index >= max_size_ || end_index < start_index || end_index >= max_size_) {
            throw std::out_of_range("Incorrect range");
        }
        std::copy(buf_.begin() + start_index, buf_.begin() + end_index + 1, std::back_inserter(out_range));
        return out_range;
    }

private:
    std::deque<Type> buf_{};
    uint16_t max_size_ = 0;
    uint16_t cur_size_  = 0;
};
