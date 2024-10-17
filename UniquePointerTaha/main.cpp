#include <iostream>
#include <memory>
#include "header/UniquePtr.h"
#include <stdio.h>

struct Entity{
    Entity() : val(3), charValue('f') {}

    Entity(int val, char charValue = 'c') : val(val), charValue(charValue) {}

    Entity(Entity&& en) noexcept {
        std::cout << "move" << '\n';
    }
    
    Entity& operator=(Entity&& en) noexcept {
        std::cout << "move a" << '\n';
        return *this;
    }

    int val;
    char charValue;
};

int main(){
    auto deleter = [](Entity* ptr){delete ptr;std::cout << "HERE HHHJHjsdksah\n";};

    UniquePtr<Entity> o(new Entity(4));
    auto en = o.get();
    std::cout << en->charValue << en->val << '\n';
    std::cout << o << '\n';
    UniquePtr<Entity, decltype(deleter)> jf(new Entity(), deleter);
    
    UniquePtr<Entity> k = make_UniquePtr<Entity>();
    k.reset(o.release());
    auto p = k.get();
    if(!(bool)p){
        std::cout << "heloekopdfkfj" << '\n';
    }
    std::cout << p->charValue << '\n';
}