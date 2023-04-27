#指定编译器
CC = g++

#找出当前目录下，所有的源文件（以.cpp结尾）
SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v 'server\.cpp' | grep -v './Test/*')
$(warning SRCS is ${SRCS})

#确定cpp源文件对应的目标文件
OBJS := $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRCS)))
$(warning OBJS is ${OBJS})

#编译选项
CFLAGS = -g -O2 -Wall -Werror=class-memaccess -Wno-error=class-memaccess -Wno-unused -ldl -lpthread -fPIC -std=c++11
$(warning CFLAGS is ${CFLAGS})

# #消除警告选项
# TAILFALGS = -fpermissive
# $(warning TAILFALGS is ${TAILFALGS})

#找出当前目录下所有的头文件
INCLUDE_TEMP = $(shell find ./* -type d)
INCLUDE = $(patsubst %,-I %, $(INCLUDE_TEMP))
$(warning INCLUDE is ${INCLUDE})

# 目标文件路径
OBJ_PATH = ./build
SRC_SERVER = server.cpp
# 目标文件名
OBJ_SERVER = ${SRC_SERVER:%.cpp=%.o}
EXE_SERVER = server

target: ${EXE_SERVER}

$(EXE_SERVER): $(OBJ_SERVER) $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I.

clean:
	rm -f ${OBJS} ${OBJ_SERVER} ${EXE_SERVER}

%.o: %.cpp
	${CC} ${CFLAGS} -I. -c $< -o $@ ${TAILFALGS}
