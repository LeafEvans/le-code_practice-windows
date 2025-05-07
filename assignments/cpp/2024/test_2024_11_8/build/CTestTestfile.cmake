# CMake generated Testfile for 
# Source directory: C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8
# Build directory: C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[SimpleTest]=] "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/build/Debug/test_2024_11_8.exe")
  set_tests_properties([=[SimpleTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;15;add_test;C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[SimpleTest]=] "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/build/Release/test_2024_11_8.exe")
  set_tests_properties([=[SimpleTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;15;add_test;C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[SimpleTest]=] "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/build/MinSizeRel/test_2024_11_8.exe")
  set_tests_properties([=[SimpleTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;15;add_test;C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[SimpleTest]=] "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/build/RelWithDebInfo/test_2024_11_8.exe")
  set_tests_properties([=[SimpleTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;15;add_test;C:/Code/Code_Practice/Assignments/CPP/2024/test_2024_11_8/CMakeLists.txt;0;")
else()
  add_test([=[SimpleTest]=] NOT_AVAILABLE)
endif()
