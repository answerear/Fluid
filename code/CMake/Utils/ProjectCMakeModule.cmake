####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
#
# This file suply some cmake module function help to setup project
####################################################################################################


# Set project name
# project_name : name of project
# Usage : SET_PROJECT_NAME(ProjectName)
macro(SET_PROJECT_NAME project_name)
	set(LIB_NAME ${project_name})
	set(BIN_NAME ${project_name})
	string(TOUPPER ${LIB_NAME} LIB_NAME_TOUPPER)
endmacro(SET_PROJECT_NAME)


function(ADD_PROJECT_FILES file_list group dir)
	foreach(var ${ARGN})
		list(APPEND temp_files ${dir}${var})
		source_group(${group} FILES ${dir}${var})
	endforeach(var)
	
	set(file_list "${temp_files}" PARENT_SCOPE)
endfunction(ADD_PROJECT_FILES)


function(ADD_PROJECT_FILES_BY_EXT out_files group dir ext)
	file(GLOB var ${dir}*${ext})

	foreach(f ${var})
		get_filename_component(name ${f} NAME_WE)
		add_project_files(file_list ${group} ${dir} "${name}${ext}")
		list(APPEND temp_list ${file_list})
	endforeach()

	set(out_files "${temp_list}" PARENT_SCOPE)
endfunction(ADD_PROJECT_FILES_BY_EXT)


macro(SET_PROJECT_FILES group dir ext)
	add_project_files_by_ext(out_files ${group} ${dir} ${ext})
	list(APPEND SOURCE_FILES ${out_files})
endmacro(SET_PROJECT_FILES)
	