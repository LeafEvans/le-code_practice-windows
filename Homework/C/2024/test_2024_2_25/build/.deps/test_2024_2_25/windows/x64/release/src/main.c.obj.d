{
    files = {
        [[src\main.c]]
    },
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-fexceptions",
            "-fcxx-exceptions",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build\\.objs\\test_2024_2_25\\windows\\x64\\release\\src\\__cpp_main.c.c:   src/main.c\
"
}