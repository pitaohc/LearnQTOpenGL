cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "D:/Library/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(LearnQTOpenGL LANGUAGES CXX)

# 设置c++标准 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON) # 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
# set(CMAKE_AUTOUIC ON) # 设置自动生成ui.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
set(CMAKE_AUTORCC ON) # 【optional】设置自动处理.qrc文件


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#################################################
find_package(Qt5 COMPONENTS core gui widgets  REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
#################################################
# 添加QT资源管理文件
set(RES_DIRS resources)
file(GLOB_RECURSE RES_DIRS ${RES_DIRS}/*.qrc)
message("QT 资源管理文件:")
# 逐行输出QT资源管理文件
foreach(FILE ${RES_DIRS})
    message(${FILE})
endforeach()
# 将QT资源管理文件添加到筛选器
source_group("Resource Files" FILES ${RES_DIRS})
#################################################
# 添加ui文件
set(UI_DIRS ui)
file(GLOB_RECURSE UI_FILES ${UI_DIRS}/*.ui)
qt5_wrap_ui(ui_FILES ${UI_FILES})
message("UI 文件:")
# 逐行输出UI_FILES
foreach(FILE ${UI_FILES})
    message(${FILE})
endforeach()
# 将ui文件添加到筛选器
source_group("Form Files" FILES ${UI_FILES})
#################################################
# 添加shader文件
set(SHADER_DIRS shader)
file(GLOB_RECURSE SHADER_FILES ${SHADER_DIRS}/*.frag ${SHADER_DIRS}/*.vert ${SHADER_DIRS}/*.vs ${SHADER_DIRS}/*.fs)
message("SHADER 文件:")
# 逐行输出SHADER_FILES
foreach(FILE ${SHADER_FILES})
    message(${FILE})
endforeach()
# 将shader文件添加到筛选器
# Note: 只有在 add_executable() 中的文件才会被 source_group 分组. 如果你发现有些文件没有被正确分组, 应该首先确认这些文件是否出现在 add_executable() 的 [source-x] 列表中.
source_group("Shader Files" FILES ${SHADER_FILES}) 

#################################################
# 添加头文件目录
set(HEADER_DIRS src)
include_directories(${HEADER_DIRS})
# 查找源文件并将它们添加到可执行文件
file(GLOB_RECURSE HEADER_FILES ${HEADER_DIRS}/*.h)
message("Header 文件:")
# 逐行输出HEADER_FILES
foreach(FILE ${HEADER_FILES})
    message(${FILE})
endforeach()
#################################################
set(SOURCE_DIR src)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
message("Sources 文件:")
# 逐行输出SOURCES
foreach(FILE ${SOURCES})
    message(${FILE})
endforeach()
#################################################
# 配置release版本的CMAKE_EXE_LINKER_FLAGS
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
# 配置debug版本的CMAKE_EXE_LINKER_FLAGS
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")

#################################################
add_executable(${PROJECT_NAME} 
${SOURCES} 
${HEADER_FILES} 
${UI_FILES} 
${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets )
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} assimp::assimp)


# 判断是否是visual studio
if (MSVC)
    message("Generating Visual Studio project")
    # 设置项目编码方式，MSVC在编译时会默认以UTF-8编码读取源文件，并将文本内容以UTF-8编码保存在exe或者dll可执行文件内，这是最关键的一点。
    target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")
    # 设置项目的字符集，这里设置为Unicode字符集，也就是说，项目中的所有字符串都是Unicode编码的。
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
    "_UNICODE"
    "UNICODE")
    # 设置visual studio的启动项目
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
else()
    message("Not generating Visual Studio project")
endif()