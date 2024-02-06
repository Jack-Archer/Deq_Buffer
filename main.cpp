#include "deq_buffer.h"

#include <iostream>



int main() {

    DeqBuffer<int> buf(10);

    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10, 11, 12,13,15,16,17};
    buf.insertRange(vec.begin(), vec.end());

    std::cout << std::endl << buf.getFrame(6) << std::endl;

    buf.clearBuf();
    buf.resizeBuf(11);
    buf.insertFrame(34);
    buf.insertFrame(34);
    buf.insertFrame(34);

    std::cout << buf.bufCurSize() << std::endl;
    std::cout << buf.isEmptyBuf() << std::endl;

    auto v = buf.getFrameRange(0,6);
    for(auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;



return 0;
}
