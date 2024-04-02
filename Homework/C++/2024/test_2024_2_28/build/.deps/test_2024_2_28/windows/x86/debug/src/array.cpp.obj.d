{
    files = {
        [[src\array.cpp]]
    },
    values = {
        "gcc",
        {
            "-m32",
            "-g",
            "-O0",
            "-fexceptions"
        }
    },
    depfiles_gcc = "array.o: src\\array.cpp src\\../include/array.hpp\
"
}