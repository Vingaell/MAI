if(EXISTS "/home/vingael/projects/OOP/lab1/build/tests[1]_tests.cmake")
  include("/home/vingael/projects/OOP/lab1/build/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
