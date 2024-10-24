#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "header/doctest.h"
#include <iostream>
#include "header/UniquePtr.h"

struct Entity{
    
    Entity() : val(3), charValue('f') {}

    Entity(int val, char charValue = 'f') : val(val), charValue(charValue) {}

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

TEST_CASE("Construct UniquePtr"){
    UniquePtr<Entity> o(new Entity(4));
    auto en = o.get();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 4);
}

TEST_CASE("Construct with own character"){
    UniquePtr<Entity> o(new Entity(4, 'a'));
    auto en = o.get();
    CHECK(en->charValue == 'a');
    CHECK(en->val == 4);
}

TEST_CASE("Construct UniquePtr with deleter"){
    auto deleter = [](Entity* ptr){delete ptr;std::cout << "Custom Deleter\n";};
    UniquePtr<Entity, decltype(deleter)> jf(new Entity(), deleter);
    auto en = jf.get();
    CHECK(en->charValue == 'f');
}

TEST_CASE("Construct with make_UniquePtr"){
    UniquePtr<Entity> k = make_UniquePtr<Entity>();
    auto en = k.get();
    CHECK(en->charValue == 'f');
}

TEST_CASE("Move Constructor"){
    UniquePtr<Entity> o(new Entity(4));
    UniquePtr<Entity> k(std::move(o));
    auto en = k.get();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 4);
}

TEST_CASE("Move Assignment"){
    UniquePtr<Entity> o(new Entity(4));
    UniquePtr<Entity> k(new Entity(5));
    k = std::move(o);
    auto en = k.get();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 4);
}

TEST_CASE("Move the same object"){
    UniquePtr<Entity> o(new Entity(4));
    o = std::move(o);
    auto en = o.get();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 4);
}

TEST_CASE("Move Constructor with deleter"){
    auto deleter = [](Entity* ptr){delete ptr;std::cout << "Custom Deleter\n";};
    UniquePtr<Entity, decltype(deleter)> o(new Entity(), deleter);
    UniquePtr<Entity, decltype(deleter)> k(std::move(o));
    auto en = k.get();
    CHECK(en->charValue == 'f');
}

TEST_CASE("Reset"){
    UniquePtr<Entity> o(new Entity(4));
    o.reset();
    auto en = o.get();
    CHECK(en == nullptr);
}

TEST_CASE("Reset with new object"){
    UniquePtr<Entity> o(new Entity(4));
    o.reset(new Entity(5));
    auto en = o.get();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 5);
}

TEST_CASE("Reset with nullptr"){
    UniquePtr<Entity> o(new Entity(4));
    o.reset(nullptr);
    auto en = o.get();
    CHECK(en == nullptr);
}

TEST_CASE("Reset with deleter"){
    auto deleter = [](Entity* ptr){delete ptr;std::cout << "Custom Deleter\n";};
    UniquePtr<Entity, decltype(deleter)> o(new Entity(), deleter);
    o.reset();
    auto en = o.get();
    CHECK(en == nullptr);
}

TEST_CASE("Release"){
    UniquePtr<Entity> o(new Entity(4));
    auto en = o.release();
    CHECK(en->charValue == 'f');
    CHECK(en->val == 4);
}

TEST_CASE("Released internal pointer should be be nullptr"){
    UniquePtr<Entity> o(new Entity(4));
    auto discard = o.release();
    auto en = o.get();
    CHECK(en == nullptr);
}

TEST_CASE("Swap"){
    UniquePtr<Entity> o(new Entity(4, 'a'));
    UniquePtr<Entity> k(new Entity(5, 'z'));
    o.swap(k);
    auto en = o.get();
    auto en2 = k.get();
    CHECK(en->charValue == 'z');
    CHECK(en->val == 5);
    CHECK(en2->charValue == 'a');
    CHECK(en2->val == 4);
}

TEST_CASE("Swap with deleter"){
    auto deleter = [](Entity* ptr){delete ptr;std::cout << "Custom Deleter\n";};
    UniquePtr<Entity, decltype(deleter)> o(new Entity(4, 'a'), deleter);
    UniquePtr<Entity, decltype(deleter)> k(new Entity(5, 'z'), deleter);
    o.swap(k);
    auto en = o.get();
    auto en2 = k.get();
    CHECK(en->charValue == 'z');
    CHECK(en->val == 5);
    CHECK(en2->charValue == 'a');
    CHECK(en2->val == 4);
}

TEST_CASE("Operator ->"){
    UniquePtr<Entity> o(new Entity(4));
    auto en = o->charValue;
    CHECK(en == 'f');
}

TEST_CASE("Operator *"){
    UniquePtr<Entity> o(new Entity(4));
    auto en = (*o).charValue;
    CHECK(en == 'f');
}

TEST_CASE("Operator bool"){
    UniquePtr<Entity> o(new Entity(4));
    CHECK((bool)o == true);
    auto temp = o.release();
    CHECK_FALSE((bool)o);
}





// int main(){
//     auto deleter = [](Entity* ptr){delete ptr;std::cout << "HERE HHHJHjsdksah\n";};

//     UniquePtr<Entity> o(new Entity(4));
//     auto en = o.get();
//     std::cout << en->charValue << en->val << '\n';
//     std::cout << o << '\n';
//     UniquePtr<Entity, decltype(deleter)> jf(new Entity(), deleter);
    
//     UniquePtr<Entity> k = make_UniquePtr<Entity>();
//     k.reset(o.release());
//     auto p = k.get();
//     if(!(bool)p){
//         std::cout << "heloekopdfkfj" << '\n';
//     }
//     std::cout << p->charValue << '\n';
// }