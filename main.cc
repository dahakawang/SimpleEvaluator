#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>

std::string load_file(const std::string& file_path) {
    std::stringstream buffer_stream;
    std::ifstream input_stream(file_path, std::ios_base::in | std::ios_base::binary);
    if (!input_stream) throw std::runtime_error("can't open file " + file_path);

    std::copy(std::istreambuf_iterator<char>(input_stream), 
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(buffer_stream));

    return buffer_stream.str();
}

class value_t {
public:
    enum type_t { DECIMAL, INTEGER, STRING };

    template<typename T>
    value_t(T _v,
            typename std::enable_if<std::is_integral<T>::value>::type* dummy = nullptr) {
        _type = INTEGER;
        _data.integer = _v;
    }

    template<typename T>
    value_t(T _v,
            typename std::enable_if<std::is_floating_point<T>::value>::type* dummy = nullptr) {
        _type = DECIMAL;
        _data.decimal = _v;
    }

    value_t(const std::string& _v) {
        _type = STRING;
        _data.str = _v;
    }

    value_t(const char* _v) {
        _type = STRING;
        _data.str = _v;
    }


    type_t type() const {
        return _type;
    }

    long long get_integer() const {
        return _data.integer;
    }

    double get_decimal() const {
        return _data.decimal;
    }

    const std::string& get_string() const {
        return _data.str;
    }

    friend std::ostream& operator<<(std::ostream& stream, const value_t& value);
private:
    type_t _type;
    struct {
        long long integer;
        double decimal;
        std::string str;
    } _data;
};

std::ostream& operator<<(std::ostream& stream, const value_t& value) {
    if (value._type == value_t::DECIMAL) {
        stream << value.get_decimal();
    } else if (value._type == value_t::INTEGER) {
        stream << value.get_integer();
    } else {
        stream << value.get_string();
    }

    return stream;
};


class expression_t {
public:
    virtual value_t eval();
};

class const_expression_t : public expression_t {
public:
    value_t eval() override {
        return _value;
    }

private:
    value_t _value;
};

int main(int argc, char *argv[]) {
    value_t v("sdfasf");
    std::cout << v << std::endl;
    return 0;
}
