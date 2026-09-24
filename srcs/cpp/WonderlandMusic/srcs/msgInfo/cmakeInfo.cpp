#include "cmakeInfo.h"

#include <QDateTime>
#include <QFileInfo>
#include <QString>

#include <cmake_property_to_c_cpp_header_env.h>

#include <cmake_to_c_cpp_header_env.h>

bool CmakeInfo::getGeneratePorjectDateTime( QDateTime &result_data_time ) {
	QString format = cmake_property_Generate_Date_Time_Format;
	format.replace( "%Y", "yyyy" );
	format.replace( "%m", "MM" );
	format.replace( "%d", "dd" );
	format.replace( "%H", "HH" );
	format.replace( "%M", "mm" );
	format.replace( "%S", "ss" );
	result_data_time = QDateTime::fromString(
		cmake_property_Generate_Date_Time,
		format
		);
	return true;
}
bool CmakeInfo::getGeneratePorjectCmakeSourceDir( QString &result_source_dir ) {
	result_source_dir = QString( Cmake_Source_Dir );
	QFileInfo fileInfo( result_source_dir );
	if( fileInfo.exists( ) == false )
		return false;
	result_source_dir = fileInfo.absoluteFilePath( );
	return true;
}
bool CmakeInfo::getGeneratePorjectCmakeAppName( QString &result_target_obj_name ) {
	result_target_obj_name = QString( current_target_obj );
	return result_target_obj_name.isEmpty( ) == false;
}
bool CmakeInfo::getGeneratePorjectCmakeProjectName( QString &result_project_name ) {
	result_project_name = QString( Cmake_Project_Name );
	return result_project_name.isEmpty( ) == false;
}
