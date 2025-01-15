cmake_minimum_required(VERSION 3.10)

# # C++ のバージョンを指定
# # set(CMAKE_CXX_STANDARD 11)
# # 上記は非推奨の書き方。推奨される方法は以下のように書く
# target_compile_features(MyProject PUBLIC cxx_std_11)

# プロジェクト名を指定
# ConvexHull：凸法
project(ConvexHull)

# ConvexHullのディレクトリパスを設定
# set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
# set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

# プロジェクトのソースファイルを指定
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

# DLLファイルのヘッダーファイルとインポートライブラリのパスを設定
# 下記のように、自動で必要なパッケージを探す方法もあるが、見つけてくれなかった。（Find<PackageName>.cmakeが存在しない？）
# find_package(Qhull REQUIRED)
set(QHULL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/qhull/include)
set(QHULL_LIB_DIR ${PROJECT_SOURCE_DIR}/qhull/Debug)

# 実行ファイルの作成
add_executable(ConvexHull ${SOURCE_FILES})

# ヘッダーファイルのディレクトリをインクルードパスに追加
# include_directoriesはターゲットの指定ができないため非推奨。
# include_directories(${QHULL_INCLUDE_DIR})
target_include_directories(ConvexHull PUBLIC ${PROJECT_SOURCE_DIR}/include ${QHULL_INCLUDE_DIR})


# Qhull ライブラリをリンク
# ${QHULL_LIB_DIR}/qhullstatic_r.libではなく、{QHULL_LIB_DIR}/qhullstatic.libを利用するとnon-reentrantエラーが発生する。
target_link_libraries(ConvexHull ${QHULL_LIB_DIR}/qhull_rd.lib ${QHULL_LIB_DIR}/qhullstatic_rd.lib  ${QHULL_LIB_DIR}/qhullcpp_d.lib)

# IDE でヘッダーファイルを表示させる
target_sources(ConvexHull PRIVATE ${HEADER_FILES})
