﻿# CMakeList.txt: проект CMake для xo; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (xo "main.cpp"  "cli.h" "cli.cpp" "tictactoe.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET xo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
