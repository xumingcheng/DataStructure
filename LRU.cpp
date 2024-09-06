#include <iostream>

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include "LRUCache.h"

int main() {
    // 定义一个使用降序排列的 std::map
    /*std::map<int, std::string, std::function<bool(int, int)>> myMap(
            [](int a, int b) { return a > b; }
    );

    // 插入一些数据
    myMap[1] = "One";
    myMap[2] = "Two";
    myMap[3] = "Three";

    // 输出 map 的内容，按键降序排列
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }*/
    LruCache<int,std::string> Lru;
    Lru.putValue(1,"china");
    Lru.putValue(2,"japan");
    Lru.putValue(3,"usa");
    Lru.putValue(4,"france");
    Lru.putValue(5,"germany");
    Lru.display();
    try{
        Lru[2];
        Lru.getValue(1);
    }
    catch (myexception &e)
    {
       std::cout<< e.what()<<std::endl;
    }
    std::cout<<"++++++++++++++++++++++++++++++++"<<std::endl;
    Lru.display();

    return 0;
}