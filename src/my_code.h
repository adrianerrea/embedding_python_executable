#ifndef MY_CODE_H
#define MY_CODE_H


#include <string>
#include <vector>

#include "structs.h"


struct _object;
typedef _object PyObject;

namespace my_namespace {
    class my_code {
public:
    my_code();
    ~my_code();
    bool initialize(const std::string &configDir);
    bool doingInference(const Image &image, const std::string &configDir);

private:
    std::string configDir;
    std::string model_path;
    PyObject* myModule;
};
}

#endif // MY_CODE_H
