cmake_minimum_required(VERSION 2.8)

project(AutoShape)

set (AutoShape_VERSION_MAJOR 0)
set (AutoShape_VERSION_MINOR 2)

find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtDesigner REQUIRED )

set(CMAKE_INSTALL_PREFIX /home/namatv)

set(CMAKE_BUILD_TYPE Debug) # empty Debug Release RelWithDebInfo MinSizeRel

include(${QT_USE_FILE})

include_directories(
  ${QT_INCLUDES} 
  ${CMAKE_CURRENT_BINARY_DIR} 
  ./src
  ./src/menu
  ./src/shapes
  ./src/dialogs
)

set(AutoShape_SRCS
	./src/forma.cpp
	./src/font.cpp
	./src/draw_var.cpp
	./src/stack.cpp
	./src/main.cpp
	./src/forma_l.cpp
	./src/edit_menu.cpp
	./src/draw_point.cpp
	./src/strings.cpp
	./src/menu/menu.cpp

	./src/shapes/shapes.cpp
	./src/shapes/shape_.cpp
	./src/shapes/shape_12.cpp
	./src/shapes/shape_34.cpp
	./src/shapes/shape_56.cpp
	./src/shapes/shape_7.cpp
	./src/shapes/shape_89.cpp
	./src/shapes/shape_a.cpp	
	./src/shapes/shape_b.cpp
	./src/shapes/shape_cd.cpp
	./src/shapes/shape_e.cpp

	./src/dialogs/main_form.cpp
	./src/dialogs/dialog_draw_vars.cpp
	./src/dialogs/dialog_forms_header.cpp
	./src/dialogs/dialog_arc_octant_edit.cpp
	./src/dialogs/dialog_font_header.cpp
	./src/dialogs/dialog_stack_edit.cpp
	./src/dialogs/dialog_pen_edit.cpp
	./src/dialogs/dialog_arc_digit_edit.cpp
	./src/dialogs/dialog_forms_find.cpp
	./src/dialogs/dialog_line_edit.cpp
	./src/dialogs/dialog_scale_edit.cpp
	./src/dialogs/dialog_multi_line_edit.cpp
	./src/dialogs/dialog_multi_arc_edit.cpp
)

set(AutoShape_UIS 
	./src/dialogs/main_form_1.ui
	./src/dialogs/dialog_multi_line_edit.ui
	./src/dialogs/dialog_stack_edit.ui
	./src/dialogs/dialog_line_edit.ui
	./src/dialogs/dialog_reference_edit.ui
	./src/dialogs/main_form.ui
	./src/dialogs/dialog_scale_edit.ui
	./src/dialogs/dialog_draw_vars.ui
	./src/dialogs/dialog_pen_edit.ui
	./src/dialogs/dialog_arc_octant_edit.ui
	./src/dialogs/dialog_forms_find.ui
	./src/dialogs/dialog_font_header.ui
	./src/dialogs/dialog_multi_arc_edit.ui
	./src/dialogs/dialog_arc_digit_edit.ui
	./src/dialogs/dialog_forms_header.ui
)


QT4_WRAP_UI(AutoShape_UIS_H ${AutoShape_UIS})

qt4_automoc(${AutoShape_SRCS})

add_executable (AutoShape ${AutoShape_SRCS} ${AutoShape_UIS_H} )

target_link_libraries(AutoShape
  ${QT_QTCORE_LIBRARY} 
  ${QT_QTGUI_LIBRARY} 
  ${QT_QTDESIGNER_LIBRARY} 
)

install(
  TARGETS AutoShape
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static
)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${AutoShape_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${AutoShape_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH  0)

set (CPACK_PACKAGE_VENDOR "MNASoft")
set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/description.txt")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "AutoShape - интерактивный редактор, служащий для создания файлов описания шрифта (shp-файлов) системы AutoCAD.")
set (CPACK_TOPLEVEL_TAG "/usr/bin/AutoShape")

include (CPack)

# cpack -C CPackConfig.cmake
# cpack -C CPackSourceConfig.cmake