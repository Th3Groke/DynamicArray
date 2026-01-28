#define CATCH_CONFIG_MAIN
#include "inc/catch.hpp"
#include "inc/Array.h"
#include "inc/Serializer.h"

#include <algorithm>

struct TestUser {
    std::string username;
    int id;
    bool operator==(const TestUser& other) const {
        return username == other.username && id == other.id;
    }

    void SaveBinary(std::ofstream& out) const {
        Serializer<std::string>::Save(out, username);
        Serializer<int>::Save(out, id);
    }

    void LoadBinary(std::ifstream& in) {
        Serializer<std::string>::Load(in, username);
        Serializer<int>::Load(in, id);
    }
};

TEST_CASE("Array Size and Capacity", "[Array]") {
    Array<int> arr(5);

    SECTION("Initial state") {
        REQUIRE(arr.Size() == 0);
        REQUIRE(arr.Capacity() == 5);
        REQUIRE(arr.IsEmpty() == true);
    }

    SECTION("Push Back increases size") {
        arr.push_back(10);
        REQUIRE(arr.Size() == 1);
        REQUIRE(arr[0] == 10);
        REQUIRE(arr.IsEmpty() == false);
    }
}

TEST_CASE("Sorting Logic", "[Sort]") {
    Array<int> arr = {5, 1, 4, 2, 8};
    arr.Sort();

    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 4);
    REQUIRE(arr[3] == 5);
    REQUIRE(arr[4] == 8);
}

TEST_CASE("Find Element", "[Find]") {
    Array<int> arr = {10, 20, 30};

    REQUIRE(arr.Find(20) == 1);
    REQUIRE(arr.Find(99) == arr.Size());
}

TEST_CASE("Rule of Five: Copy and Move", "[Memory]") {
    SECTION("Copy Constructor creates deep copy") {
        Array<int> original = {1,2,3};
        Array<int> copy = original;

        copy[0] =999;

        REQUIRE(original[0]==1);
        REQUIRE(copy[0]==999);
        REQUIRE(original.Size() == 3);
        REQUIRE(copy.Size() == 3);
    }
    SECTION("Move Constructor steals resources") {
        Array<int> original = {10,20,30};
        Array<int> destination = std::move(original);
        REQUIRE(destination.Size() == 3);
        REQUIRE(destination[0] == 10);
        REQUIRE(original.Size() == 0);
    }
    SECTION("Copy Assignment Operator") {
        Array<int> a = {1, 2};
        Array<int> b = {3, 4, 5};
        a = b;
        REQUIRE(a.Size() == 3);
        REQUIRE(a[0] == 3);
        a[0] = 100;
        REQUIRE(b[0] == 3);
    }
}
TEST_CASE("Exception Safety", "[Exceptions]") {
    Array<int> arr = {1, 2, 3};

    SECTION("Accessing out of bounds throws") {
        REQUIRE_THROWS_AS(arr[10], IndexOutOfBounds);
    }

    SECTION("Pop back on empty throws") {
        Array<int> emptyArr(5);
        REQUIRE_THROWS_AS(emptyArr.pop_back(), IndexOutOfBounds);
    }
}


TEST_CASE("Sorting Edge Cases", "[Sort]") {
    SECTION("Empty Array") {
        Array<int> empty(5);
        REQUIRE_NOTHROW(empty.Sort());
        REQUIRE(empty.Size() == 0);
    }

    SECTION("Reverse Sorted") {
        Array<int> arr = {5, 4, 3, 2, 1};
        arr.Sort();
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[4] == 5);
    }

    SECTION("Duplicates") {
        Array<int> arr = {3, 1, 3, 2, 1};
        arr.Sort();
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 1);
        REQUIRE(arr[2] == 2);
        REQUIRE(arr[3] == 3);
        REQUIRE(arr[4] == 3);
    }
}

TEST_CASE("Large Data Stress Test", "[Stress]") {

    SECTION("Sorting 100,000 Random Integers") {
        const int NUM_ITEMS = 100000;
        Array<int> bigArr(10);


        for(int i = 0; i < NUM_ITEMS; i++) {
            bigArr.push_back(rand() % 100000);
        }

        REQUIRE(bigArr.Size() == NUM_ITEMS);

        REQUIRE_NOTHROW(bigArr.Sort());


        bool sorted = std::is_sorted(bigArr.begin(), bigArr.end());
        REQUIRE(sorted == true);
    }
}
TEST_CASE("Serialization Save and Load", "[IO]") {
    std::string filename = "test_data.bin";

    SECTION("Save and Load Integers") {
        Array<int> original = {42, 100, -5};
        original.Save(filename);

        Array<int> loaded(1);
        loaded.Load(filename);

        REQUIRE(loaded.Size() == 3);
        REQUIRE(loaded[0] == 42);
        REQUIRE(loaded[1] == 100);
        REQUIRE(loaded[2] == -5);
    }

    std::remove(filename.c_str());
}

TEST_CASE("Advanced Serialization", "[Serializer]") {
    std::string filename = "test_advanced.bin";

    SECTION("Array of std::string") {
        Array<std::string> words = {"Hello", "World", "C++", "Serialization"};

        // Save
        words.Save(filename);

        // Load
        Array<std::string> loaded(1);
        loaded.Load(filename);

        REQUIRE(loaded.Size() == 4);
        REQUIRE(loaded[0] == "Hello");
        REQUIRE(loaded[1] == "World");
        REQUIRE(loaded[3] == "Serialization");
    }

    SECTION("Array of Custom Classes (TestUser)") {
        Array<TestUser> users(2);
        users.push_back({"Alice", 101});
        users.push_back({"Bob", 202});
        users.push_back({"Charlie", 999});

        // Save
        users.Save(filename);

        // Load
        Array<TestUser> loadedUsers(1);
        loadedUsers.Load(filename);

        REQUIRE(loadedUsers.Size() == 3);
        REQUIRE(loadedUsers[0].username == "Alice");
        REQUIRE(loadedUsers[0].id == 101);
        REQUIRE(loadedUsers[2].username == "Charlie");
    }

    // Cleanup
    std::remove(filename.c_str());
}
