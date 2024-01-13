{
    values = {
        "gcc",
        {
            "-m64",
            "-g",
            "-O0"
        }
    },
    files = {
        [[src\main.c]]
    },
    depfiles_gcc = "main.o: src\\main.c\
"
}