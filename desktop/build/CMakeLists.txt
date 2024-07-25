# set a min version
cmake_minimum_required(VERSION 3.20.0)

# set a name and version of project
project(duos-pad VERSION 1.0)

# set c amd c++ compiler for riscv64
# set(CMAKE_C_COMPILER riscv64-unknown-linux-musl-gcc)
# set(CMAKE_CXX_COMPILER riscv64-unknown-linux-musl-g++)

# set c amd c++ compiler for aarch64
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# enable compilation optimization
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_RELEASE -Ofast)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3")

# set root dir of project
set(root ..)

# set directory of output of binaries
set(EXECUTABLE_OUTPUT_PATH bin)

# define function
macro(find_include_list result curdir)									#定义函数,2个参数:存放结果result；指定路径curdir；
	file(GLOB_RECURSE children ${curdir}/*.h)							#遍历获取curdir中的*.h文件列表
	set(dirlist "")														#定义dirlist中间变量，并初始化
	foreach(child ${children})											#for循环
		string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})			#字符串替换,用/前的字符替换/*h
		if(IS_DIRECTORY ${LIB_NAME})									#判断是否为路径
			list (FIND dirlist ${LIB_NAME} list_index)					#去重，查找dirlist中是否有${LIB_NAME}指定的值，可以区分字符串相同数子后缀不同的路径：例如/app/test_1和/app/test_2
			if(${list_index} LESS 0)									#若没找到则代表列表中没有该路径
				LIST(APPEND dirlist ${LIB_NAME})						#将合法的路径加入dirlist变量中  
			endif()														#结束判断
		endif()															#结束判断
	endforeach()														#结束for循环
	set(${result} ${dirlist})											#dirlist结果放入result变量中
endmacro()

#查找include目录下的所有*.h头文件,并路径列表保存到headers_list变量中
find_include_list(headers_list ${root})									#调用函数，指定参数

#将headers_list中路径列表加入工程		
include_directories(
	${headers_list}														#headers_list路径列表加入工程
)

# 查找source目录下的所有*.c源文件,并将文件列表保存到sources_list变量
file(GLOB_RECURSE sources_list "../driver/*.c" "../lvgl/*.c" "../gui/*.c")			#遍历获取路径下所有的*.c文件列表

# generate exe
add_executable(exe ../main.c ${sources_list})
