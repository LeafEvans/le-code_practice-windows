{
    files = {
        [[src\main.cpp]]
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
    depfiles_gcc = "main.o: src\\main.cpp src\\../include/array.hpp\
"
}