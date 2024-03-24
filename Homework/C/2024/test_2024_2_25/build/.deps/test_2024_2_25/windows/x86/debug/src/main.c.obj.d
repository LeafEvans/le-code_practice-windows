{
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m32",
            "-g",
            "-O0",
            "-fexceptions",
            "-fcxx-exceptions"
        }
    },
    files = {
        [[src\main.c]]
    },
    depfiles_gcc = "build\\.objs\\test_2024_2_25\\windows\\x86\\debug\\src\\__cpp_main.c.c:   src/main.c\
"
}