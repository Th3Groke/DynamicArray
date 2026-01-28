#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <fstream>
#include <string>


template<typename T>
struct Serializer {
    static void Save(std::ofstream& out, const T& obj) {
        obj.SaveBinary(out); 
    }
    
    static void Load(std::ifstream& in, T& obj) {
        obj.LoadBinary(in);
    }
};


template<> 
struct Serializer<int> {
    static void Save(std::ofstream& out, const int& val) {
        out.write(reinterpret_cast<const char*>(&val), sizeof(val));
    }
    static void Load(std::ifstream& in, int& val) {
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
    }
};


template<> 
struct Serializer<std::string> {
    static void Save(std::ofstream& out, const std::string& val) {
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));

        out.write(val.c_str(), len);
    }
    
    static void Load(std::ifstream& in, std::string& val) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));

        val.resize(len);

        in.read(&val[0], len);
    }
};

#endif