cmake_minimum_required( VERSION 3.16 )

get_absolute_path( prject_name "." )
get_current_dir_name( prject_name ${prject_name} )

# # set( prject_name demo001 )
message( "============ ${prject_name}" )
message( "name = " ${prject_name} ) # # 当前文件名配置为项目名称
project( ${prject_name} VERSION 0.1 )
message( "============ ${CURRENT_FOLDER}" )


get_cmake_separator( _cmake_sep )
init_std_builder_path( )


set( qt_find_mode_list Widgets Core LinguistTools Network Multimedia OpenGLWidgets Core5Compat Gui Concurrent )
set( qt_link_lib_list Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Multimedia Qt6::OpenGLWidgets Qt6::Core5Compat Qt6::Concurrent )

find_package( Qt6 QUIET COMPONENTS ${qt_find_mode_list} )

if( NOT Qt6_FOUND OR NOT EXISTS "${Qt6_DIR}" )
	# # 使用 qt6
	set( Current_Qt_Version 6.11.1 )
	set( Qt6_DIR "C:/Qt/${Current_Qt_Version}/msvc2022_64/lib/cmake/QT6/" )
	init_qt_dir_event( "${Qt6_DIR}" )
	find_package( Qt6 REQUIRED COMPONENTS ${qt_find_mode_list} )
else( )
	init_qt_dir_event( "${Qt6_DIR}" )
endif( )


# # 加载 ffmpeg 9.0 lgpl 模块
find_package( ffmpeg REQUIRED PATHS "${CMAKE_HOME_DIRECTORY}/srcs/lib/ffmpeg_9_lgpl" )


printf_qt_cmake_out( )

qt_standard_project_setup( )

# append_source_file_extensions( LANGUAGES C CXX SUFFIXS hc HC )

get_path_sources( project_src_file PATHS "${CMAKE_CURRENT_LIST_DIR}/srcs" LANGUAGES CXX C )

set( app_run_bin "${Project_Run_Bin_Path}/${prject_name}" )
set( app_static_lib_bin "${Project_Run_Static_Lib_Path}/${prject_name}" )
set( app_pdb_bin "${Project_Run_Pbd_Path}/${prject_name}" )

## 编译时非常消耗内存，我不明白，为什么编译 41 mb 的资源需要消费 8 G 内存去运行编译器。
## list( APPEND image_sources
##     "${CMAKE_CURRENT_LIST_DIR}/resources/Resource.qrc"
## )
## qt_add_resources(
##     resource_qrc
##     ${image_sources}
## 	OPTIONS -no-compress -threshold 10240
## )

list( APPEND project_src_file ${image_sources} ${resource_qrc} )

if( ${QT_VERSION_MAJOR} GREATER_EQUAL 6 )
	# cancel_target_PDB_propertie( "${prject_name}" )
	qt_add_executable( ${prject_name}
		MANUAL_FINALIZATION
		${project_src_file}
	)
	set_target_bin_out_path_property( "${prject_name}" "${app_run_bin}" )
	set_target_static_lib_out_path_property( "${prject_name}" "${app_static_lib_bin}" )
	set_target_pdb_out_path_property( "${prject_name}" "${app_pdb_bin}" )
	set_target_bin_out_name_property( "${prject_name}" "${prject_name}" )
	copy_ffmpeg_dll_to_target( "${app_run_bin}" )
	# target_obj_PDB_propertie( "${prject_name}" )
else( )
	if( ANDROID )
		add_library( ${prject_name} SHARED
			${project_src_file}
		)
	else( )
		add_executable( ${prject_name}
			${project_src_file}
		)
	endif( )
endif( )

target_link_libraries( ${prject_name} PRIVATE ${qt_link_lib_list} )

if( ${QT_VERSION} VERSION_LESS 6.1.0 )
	set( BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${prject_name} )
endif( )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
	set( Release_Status TRUE )
else( )
	set( Release_Status FALSE )
endif( )

set_target_properties( "${prject_name}" PROPERTIES
	${BUNDLE_ID_OPTION}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE ${Release_Status}
)

if( QT_VERSION_MAJOR EQUAL 6 )
	# # qt_finalize_executable( ${prject_name} )
	qt_finalize_target( "${prject_name}" )
endif( )

qt_generate_deploy_cmake_script_inatll_job( scrpt_path_ "${prject_name}" )

# # 生成文件
set( cmake_definitions_env_out "${CMAKE_CURRENT_LIST_DIR}/auto_generate_files/macro/" )
configure_temp_files( ${cmake_definitions_env_out} "${prject_name}" )


set( builder_option )
set( builder_platform )

if( CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
	set( builder_platform 1 )
elseif( MSVC )
	set( builder_platform 2 )
	# AppleClang单独区分（macOS）
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
	set( builder_platform 3 )
endif( )

if( NOT Release_Status )
	if( builder_platform EQUAL 1 )
		set( builder_option -Werror -Wfatal-errors -finput-charset=UTF-8 )
	elseif( builder_platform EQUAL 2 )
		set( builder_option /utf-8 /MP /EHsc /WX )
		un_show_include_info( ${prject_name} )
		set_property( GLOBAL PROPERTY VS_GLOBAL_StopOnFirstBuildError "true" )
	endif( )
	
else( )
	if( builder_platform EQUAL 1 )
		set( builder_option -Werror -Wfatal-errors -finput-charset=UTF-8 )
	elseif( builder_platform EQUAL 2 )
		set( builder_option /utf-8 /MP /WX )
		target_compile_options( "${prject_name}" PRIVATE ${builder_option} )
		un_show_include_info( ${prject_name} )
		set_property( GLOBAL PROPERTY VS_GLOBAL_StopOnFirstBuildError "true" )
	endif( )
endif( )

target_compile_options( "${prject_name}" PRIVATE ${builder_option} )

target_include_directories( "${prject_name}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/srcs" )
link_ffmpeg_lib_to_target( "${prject_name}" )

set( app_resouce_path "${app_run_bin}/program/" )
get_filename_component( app_resouce_path "${app_resouce_path}" ABSOLUTE ) # 全路径
set( app_resouce_path "${app_resouce_path}/" )

## 未完成项目，该处使用 FALSE
set( generate_translation_file TRUE )
if( generate_translation_file )
	# # 需要生成的 *.ts 文件保存到 translation_file_list 变量当中
	set( translation_file_list
		# # 美语
		"${PROJECT_SOURCE_DIR}/cmake_generate/translations/${prject_name}_en.ts"
		# # 汉语
		"${PROJECT_SOURCE_DIR}/cmake_generate/translations/${prject_name}_zh_CN.ts"
		# # 默认加载的文件
		"${PROJECT_SOURCE_DIR}/cmake_generate/translations/${prject_name}.ts"
	)
	# # 设置 *.pm 的输出位置
	set_source_files_properties( ${translation_file_list} PROPERTIES OUTPUT_LOCATION "${app_resouce_path}/translations" )
	# # 生成 *.ts 和 *.pm 的脚本任务
	qt_add_translations(
		"${prject_name}"
		TS_FILES ${translation_file_list}
		SOURCES ${project_src_file}
		LUPDATE_OPTIONS -no-obsolete
	)
endif( )

set( copy_file_src_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources" )
copy_file( FALSE "${copy_file_src_dir}" "${copy_file_src_dir}/font" "${app_resouce_path}" )
copy_file( FALSE "${copy_file_src_dir}" "${copy_file_src_dir}/music" "${app_resouce_path}" )
copy_file( FALSE "${copy_file_src_dir}" "${copy_file_src_dir}/png" "${app_resouce_path}" )
copy_file( FALSE "${copy_file_src_dir}" "${copy_file_src_dir}/json" "${app_resouce_path}" )

set_property( TARGET "${prject_name}" PROPERTY appResoucePath "${app_resouce_path}" )
