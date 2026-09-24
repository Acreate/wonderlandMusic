#ifndef CMAKEINFO_H_H_HEAD__FILE__
#define CMAKEINFO_H_H_HEAD__FILE__

class QString;
class QDateTime;

class CmakeInfo {
public:
	static bool getGeneratePorjectDateTime( QDateTime &result_data_time );
	static bool getGeneratePorjectCmakeSourceDir( QString &result_source_dir );
	static bool getGeneratePorjectCmakeAppName( QString &result_target_obj_name );
	static bool getGeneratePorjectCmakeProjectName( QString &result_project_name );
};

#endif // CMAKEINFO_H_H_HEAD__FILE__
