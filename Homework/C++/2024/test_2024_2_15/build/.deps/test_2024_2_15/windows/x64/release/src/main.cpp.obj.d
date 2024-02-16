{
    files = {
        [[src\main.cpp]]
    },
    values = {
        "clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-fexceptions",
            "-fcxx-exceptions",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build\\.objs\\test_2024_2_15\\windows\\x64\\release\\src\\__cpp_main.cpp.cpp:   src/main.cpp\
"
}