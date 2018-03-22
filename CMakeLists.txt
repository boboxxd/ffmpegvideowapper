  cmake_minimum_required(VERSION 3.8.2)
  project(demo)

  set(CMAKE_CXX_STANDARD 11)

  # Find includes in corresponding build directories
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  # Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)

  include_directories(include /home/hhit/lib/ffmpeg-release/include)

  link_directories(lib /home/hhit/lib/ffmpeg-release/lib)

  # Find the QtWidgets library
  find_package(Qt5Widgets)

  # Tell CMake to create the helloworld executable
  add_executable(demo hhvideoalarm.cpp  hhvideostream.cpp  hhvideowidget.cpp  main.cpp  widget.cpp)

  # Use the Widgets module from Qt 5.
  target_link_libraries(demo Qt5::Widgets hhclient avcodec avformat swscale avdevice avfilter avutil swresample)

