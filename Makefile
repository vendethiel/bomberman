# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/karp/etna/ext_bomberman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/karp/etna/ext_bomberman

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.9.1/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.9.1/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/karp/etna/ext_bomberman/CMakeFiles /Users/karp/etna/ext_bomberman/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/karp/etna/ext_bomberman/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bombe_hermann

# Build rule for target.
bombe_hermann: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 bombe_hermann
.PHONY : bombe_hermann

# fast build rule for target.
bombe_hermann/fast:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/build
.PHONY : bombe_hermann/fast

client.o: client.c.o

.PHONY : client.o

# target to build an object file
client.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client.c.o
.PHONY : client.c.o

client.i: client.c.i

.PHONY : client.i

# target to preprocess a source file
client.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client.c.i
.PHONY : client.c.i

client.s: client.c.s

.PHONY : client.s

# target to generate assembly for a file
client.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client.c.s
.PHONY : client.c.s

client_actions.o: client_actions.c.o

.PHONY : client_actions.o

# target to build an object file
client_actions.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client_actions.c.o
.PHONY : client_actions.c.o

client_actions.i: client_actions.c.i

.PHONY : client_actions.i

# target to preprocess a source file
client_actions.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client_actions.c.i
.PHONY : client_actions.c.i

client_actions.s: client_actions.c.s

.PHONY : client_actions.s

# target to generate assembly for a file
client_actions.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/client_actions.c.s
.PHONY : client_actions.c.s

display.o: display.c.o

.PHONY : display.o

# target to build an object file
display.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/display.c.o
.PHONY : display.c.o

display.i: display.c.i

.PHONY : display.i

# target to preprocess a source file
display.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/display.c.i
.PHONY : display.c.i

display.s: display.c.s

.PHONY : display.s

# target to generate assembly for a file
display.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/display.c.s
.PHONY : display.c.s

game.o: game.c.o

.PHONY : game.o

# target to build an object file
game.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/game.c.o
.PHONY : game.c.o

game.i: game.c.i

.PHONY : game.i

# target to preprocess a source file
game.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/game.c.i
.PHONY : game.c.i

game.s: game.c.s

.PHONY : game.s

# target to generate assembly for a file
game.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/game.c.s
.PHONY : game.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/main.c.s
.PHONY : main.c.s

map.o: map.c.o

.PHONY : map.o

# target to build an object file
map.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/map.c.o
.PHONY : map.c.o

map.i: map.c.i

.PHONY : map.i

# target to preprocess a source file
map.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/map.c.i
.PHONY : map.c.i

map.s: map.c.s

.PHONY : map.s

# target to generate assembly for a file
map.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/map.c.s
.PHONY : map.c.s

platforms/common/socket.o: platforms/common/socket.c.o

.PHONY : platforms/common/socket.o

# target to build an object file
platforms/common/socket.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/common/socket.c.o
.PHONY : platforms/common/socket.c.o

platforms/common/socket.i: platforms/common/socket.c.i

.PHONY : platforms/common/socket.i

# target to preprocess a source file
platforms/common/socket.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/common/socket.c.i
.PHONY : platforms/common/socket.c.i

platforms/common/socket.s: platforms/common/socket.c.s

.PHONY : platforms/common/socket.s

# target to generate assembly for a file
platforms/common/socket.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/common/socket.c.s
.PHONY : platforms/common/socket.c.s

platforms/posix/socket_client.o: platforms/posix/socket_client.c.o

.PHONY : platforms/posix/socket_client.o

# target to build an object file
platforms/posix/socket_client.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_client.c.o
.PHONY : platforms/posix/socket_client.c.o

platforms/posix/socket_client.i: platforms/posix/socket_client.c.i

.PHONY : platforms/posix/socket_client.i

# target to preprocess a source file
platforms/posix/socket_client.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_client.c.i
.PHONY : platforms/posix/socket_client.c.i

platforms/posix/socket_client.s: platforms/posix/socket_client.c.s

.PHONY : platforms/posix/socket_client.s

# target to generate assembly for a file
platforms/posix/socket_client.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_client.c.s
.PHONY : platforms/posix/socket_client.c.s

platforms/posix/socket_server.o: platforms/posix/socket_server.c.o

.PHONY : platforms/posix/socket_server.o

# target to build an object file
platforms/posix/socket_server.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_server.c.o
.PHONY : platforms/posix/socket_server.c.o

platforms/posix/socket_server.i: platforms/posix/socket_server.c.i

.PHONY : platforms/posix/socket_server.i

# target to preprocess a source file
platforms/posix/socket_server.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_server.c.i
.PHONY : platforms/posix/socket_server.c.i

platforms/posix/socket_server.s: platforms/posix/socket_server.c.s

.PHONY : platforms/posix/socket_server.s

# target to generate assembly for a file
platforms/posix/socket_server.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/socket_server.c.s
.PHONY : platforms/posix/socket_server.c.s

platforms/posix/thread.o: platforms/posix/thread.c.o

.PHONY : platforms/posix/thread.o

# target to build an object file
platforms/posix/thread.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/thread.c.o
.PHONY : platforms/posix/thread.c.o

platforms/posix/thread.i: platforms/posix/thread.c.i

.PHONY : platforms/posix/thread.i

# target to preprocess a source file
platforms/posix/thread.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/thread.c.i
.PHONY : platforms/posix/thread.c.i

platforms/posix/thread.s: platforms/posix/thread.c.s

.PHONY : platforms/posix/thread.s

# target to generate assembly for a file
platforms/posix/thread.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/platforms/posix/thread.c.s
.PHONY : platforms/posix/thread.c.s

server.o: server.c.o

.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i

.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s

.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server.c.s
.PHONY : server.c.s

server_state.o: server_state.c.o

.PHONY : server_state.o

# target to build an object file
server_state.c.o:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server_state.c.o
.PHONY : server_state.c.o

server_state.i: server_state.c.i

.PHONY : server_state.i

# target to preprocess a source file
server_state.c.i:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server_state.c.i
.PHONY : server_state.c.i

server_state.s: server_state.c.s

.PHONY : server_state.s

# target to generate assembly for a file
server_state.c.s:
	$(MAKE) -f CMakeFiles/bombe_hermann.dir/build.make CMakeFiles/bombe_hermann.dir/server_state.c.s
.PHONY : server_state.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... bombe_hermann"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... client_actions.o"
	@echo "... client_actions.i"
	@echo "... client_actions.s"
	@echo "... display.o"
	@echo "... display.i"
	@echo "... display.s"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... map.o"
	@echo "... map.i"
	@echo "... map.s"
	@echo "... platforms/common/socket.o"
	@echo "... platforms/common/socket.i"
	@echo "... platforms/common/socket.s"
	@echo "... platforms/posix/socket_client.o"
	@echo "... platforms/posix/socket_client.i"
	@echo "... platforms/posix/socket_client.s"
	@echo "... platforms/posix/socket_server.o"
	@echo "... platforms/posix/socket_server.i"
	@echo "... platforms/posix/socket_server.s"
	@echo "... platforms/posix/thread.o"
	@echo "... platforms/posix/thread.i"
	@echo "... platforms/posix/thread.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... server_state.o"
	@echo "... server_state.i"
	@echo "... server_state.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

