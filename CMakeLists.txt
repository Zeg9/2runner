cmake_minimum_required(VERSION 2.6)

project(2Runner)

file(
	GLOB_RECURSE
	source_files
	src/*.cpp
)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
Find_Package(Boost COMPONENTS system filesystem REQUIRED)
link_libraries(
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${SDLTTF_LIBRARY}
	${Boost_LIBRARIES}
)

add_definitions(-Wall -Wextra -pedantic -g)

add_executable(
	2runner
	${source_files}
)
