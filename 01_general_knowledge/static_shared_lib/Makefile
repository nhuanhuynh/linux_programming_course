
PRJ_NAME := hello

CUR_PATH := .

BIN_DIR := $(CUR_PATH)/bin
INC_DIR := $(CUR_PATH)/inc
SRC_DIR := $(CUR_PATH)/src
OBJ_DIR := $(CUR_PATH)/obj
LIB_DIR := $(CUR_PATH)/lib

LIB_SHARED_DIR := $(LIB_DIR)/shared
LIB_STATIC_DIR := $(LIB_DIR)/static

## Shared Lib ##
create_shared_obj:
	gcc -c -fPIC $(SRC_DIR)/hello_nhuan.c -o $(OBJ_DIR)/hello_nhuan.o
	gcc -c -fPIC $(SRC_DIR)/hello_world.c -o $(OBJ_DIR)/hello_world.o

create_shared_lib: create_shared_obj
	gcc -shared $(OBJ_DIR)/hello_nhuan.o $(OBJ_DIR)/hello_world.o -o $(LIB_SHARED_DIR)/lib$(PRJ_NAME).so

shared_bin: create_shared_lib
	gcc -c -fPIC $(CUR_PATH)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l$(PRJ_NAME) -o $(BIN_DIR)/use-shared-library

## Static Lib ##
create_static_obj: clean
	gcc -c $(SRC_DIR)/hello_nhuan.c -o $(OBJ_DIR)/hello_nhuan.o
	gcc -c $(SRC_DIR)/hello_world.c -o $(OBJ_DIR)/hello_world.o

create_static_lib: create_static_obj
	ar rcs $(LIB_STATIC_DIR)/lib$(PRJ_NAME).a $(OBJ_DIR)/hello_nhuan.o $(OBJ_DIR)/hello_world.o

static_bin: create_static_lib
	gcc -c $(CUR_PATH)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l$(PRJ_NAME) -o $(BIN_DIR)/statically-linked

clean:
	rm $(OBJ_DIR)/*.o
