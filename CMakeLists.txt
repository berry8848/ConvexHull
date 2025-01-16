# CMakeLists.txt 
# CMake Template file. 12/Nov/2022


# $ tree .
# .
# ├── CMakeLists.txt
# ├── build
# └── src
#     ├── include
#     │   └── bits
#     │       └── stdc++.h
#     └── main.cpp


cmake_minimum_required(VERSION 3.20)

# コンパイラに渡すオプションを指定
# 警告レベルを指定している。紳士の嗜みとして脳死で覚える。
# if (MSVC)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
# else()
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# endif()

# プロジェクト名を指定
# CXXを指定しなしと、Cコンパイラになる。
# その場合、C++固有の機能を使えなくなる？（C++を使っていると判断してCXXコンパイラにしてくれてそう）
project(ConvexHull CXX)

# デフォルトのビルドタイプを指定
if(NOT CMAKE_BUILD_TYPE)        
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "CMAKE_BUILD_TYPE" = ${CMAKE_BUILD_TYPE})

# プロジェクトのソースファイルを指定
# なお、下記の書き方もある。
# file(GLOB SRC "src/*.cpp" "src/*.c" "src/*.m" "src/*.mm" "src/*.f90")
# add_executable(${PROJECT_NAME}
#     ${SRC}
# )
set(SOURCE_FILES
    src/main.cpp
    src/StlFile.cpp 
    src/ConvexHull.cpp 
)
# プロジェクトのヘッダーファイルを指定
set(HEADER_FILES
    include/StlFile.h
    include/ConvexHull.h
)

# 実行ファイルの作成
add_executable(ConvexHull ${SOURCE_FILES})

# C++ のバージョンを指定
# cxx_std_98, cxx_std_11, cxx_std_14, cxx_std_17, cxx_std_20, cxx_std_23などがある。
# set(CMAKE_CXX_STANDARD 11)
# 上記は非推奨の書き方。推奨される方法は以下のように書く。
# add_executableの後ろに書かないとエラーが発生する。
target_compile_features(ConvexHull PRIVATE cxx_std_17)


# ---------------------------------------
# Set Qhull
# ---------------------------------------

# DLLファイルのヘッダーファイルとインポートライブラリのパスを設定
# 下記のように、自動で必要なパッケージを探す方法もあるが、見つけてくれなかった。（Find<PackageName>.cmakeが存在しない？）
# find_package(Qhull REQUIRED)
set(QHULL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/qhull/include)

# Debug/ReleaseでQHULL_LIB_DIRを切り替える。
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
    set(QHULL_LIB_DIR ${PROJECT_SOURCE_DIR}/qhull/Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building in Release mode")
    set(QHULL_LIB_DIR ${PROJECT_SOURCE_DIR}/qhull/Release)
endif()

# ヘッダーファイルのディレクトリをインクルードパスに追加
# include_directoriesはターゲットの指定ができないため非推奨。
# include_directories(${QHULL_INCLUDE_DIR})
target_include_directories(ConvexHull PUBLIC ${PROJECT_SOURCE_DIR}/include ${QHULL_INCLUDE_DIR})


# Qhull ライブラリをリンク
# ${QHULL_LIB_DIR}/qhullstatic_r.libではなく、{QHULL_LIB_DIR}/qhullstatic.libを利用するとnon-reentrantエラーが発生する。
# Debug/ReleaseでQHULL_LIB_DIRを切り替える。
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(ConvexHull ${QHULL_LIB_DIR}/qhull_rd.lib ${QHULL_LIB_DIR}/qhullstatic_rd.lib  ${QHULL_LIB_DIR}/qhullcpp_d.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(ConvexHull ${QHULL_LIB_DIR}/qhull_r.lib ${QHULL_LIB_DIR}/qhullstatic_r.lib  ${QHULL_LIB_DIR}/qhullcpp.lib)
endif()

# IDE でヘッダーファイルを表示させる
target_sources(ConvexHull PRIVATE ${HEADER_FILES})


# ---------------------------------------
# Define install
# ---------------------------------------



