#include <Python.h>
#include <iostream>
#include <filesystem>

#include "my_code.h"

using namespace std;
using namespace my_namespace;

my_code::my_code(){}
my_code::~my_code(){}


bool my_code::initialize(const std::string &configDir){
    model_path = configDir + "/breed_classifier.pkl";
    string import_variable = "import sys;sys.path.append('"+configDir+"')";
    const std::filesystem::path configDirPath(configDir);
    std::filesystem::path python_home = configDirPath / ".." / "my_python";
    //std::filesystem::path python_home = "/home/adrian/anaconda3/envs/medium_cplus/";

    Py_SetPythonHome(Py_DecodeLocale(python_home.c_str(),NULL));
    Py_Initialize(); // initialize the Python interpreter
    PyRun_SimpleString(import_variable.c_str());

    myModule = PyImport_Import(PyUnicode_FromString("python_script"));
    if (myModule != NULL){
        std::cout << "initialize exec successfully" << std::endl;
        return 0;
    }else{
        std::cout << "module load failed in initalization" << std::endl;
        Py_Finalize();
        return -1;
    }
}

bool my_code::doingInference(const Image &image, const std::string &configDir){

    if (myModule != NULL){
        PyObject* inferenceFunc = PyObject_GetAttrString(myModule, "inference_function");

        const uint8_t *data = image.data.get();  // Get a pointer to the data buffer.
        size_t data_size = image.size();  // Get the size of the data buffer.
        uint16_t height = image.height;
        uint16_t width = image.width;
        uint16_t depth = image.depth;

        PyObject *pArgs, *pValue;

        pArgs = PyTuple_New(5);

        pValue = PyBytes_FromStringAndSize(reinterpret_cast<const char*>(data), data_size);

        PyTuple_SetItem(pArgs, 0, pValue);

        pValue = PyLong_FromSize_t(height);
        PyTuple_SetItem(pArgs, 1, pValue);

        pValue = PyLong_FromSize_t(width);
        PyTuple_SetItem(pArgs, 2, pValue);

        pValue = PyLong_FromSize_t(depth);
        PyTuple_SetItem(pArgs, 3, pValue);

        PyObject* pyString = PyUnicode_FromString(model_path.c_str());
        PyTuple_SetItem(pArgs, 4, pyString);

        PyObject *pResult = PyObject_CallObject(inferenceFunc, pArgs);
        std::vector<float> vector;
        if (pResult!= NULL){
            const char* c_string = PyUnicode_AsUTF8(pResult);
            std::cout << "Breed detected: " << c_string << "\n" << std::oct;
            return 0;
        }else{
            Py_Finalize();
            return -1;
        }
    }else{
        Py_Finalize(); // clean up and shut down the Python interpreter
        return -1;
    }
}
