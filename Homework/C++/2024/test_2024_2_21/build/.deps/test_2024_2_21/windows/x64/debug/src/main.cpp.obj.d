{
    depfiles_gcc = "main.o: src\\main.cpp\
",
    values = {
        "gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-fexceptions"
        }
    },
    files = {
        [[src\main.cpp]]
    }
}