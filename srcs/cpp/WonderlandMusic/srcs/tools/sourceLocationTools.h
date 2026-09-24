#ifndef SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
#define SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
#include <vector>
class MessageString;
class DateTimeFormat;
class QString;

namespace std {
	class stacktrace_entry;
	struct source_location;
}

namespace SourceLocationTools {
	class SourceLocation {
		size_t index;
		size_t lineCode;
		QString *functionName;
		QString *fileName;

	public:
		virtual ~SourceLocation( );
		SourceLocation( );
		SourceLocation( const SourceLocation &other );
		SourceLocation & operator=( const SourceLocation &other );
		SourceLocation( const size_t &index, const size_t &line_code, const QString &function_name, const QString &file_name );
		SourceLocation( const size_t &index, const std::stacktrace_entry &stacktrace_entry );
		virtual const size_t & getIndex( ) const;
		virtual const size_t & getLineCode( ) const;
		virtual const QString & getFunctionName( ) const;
		virtual const QString & getFileName( ) const;
		virtual QString toString( ) const;
		operator QString( ) const;
	};

	/// @brief 格式化输出对象
	/// @param format_string 格式化信息输出
	/// @param source_file 格式化源文件路径
	/// @param source_function 格式化源文件函数
	/// @param source_line 格式化源文件行号
	/// @param location 被格式化的源文件信号对象
	/// @param msg 格式化的消息
	void formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg );
	/// @brief 格式化输出对象
	/// @param format_string 格式化信息输出
	/// @param location 被格式化的源文件信号对象
	/// @param msg 格式化的消息
	void formatString( QString &format_string, const std::source_location &location, const QString &msg );
	/// @brief 格式化输出对象
	/// @param result_msg 格式化信息输出
	/// @param date_time_format 日期格式对象
	/// @param source_location 被格式化的源文件信号对象
	/// @param msg 格式化的消息
	void formatString( QString &result_msg, const DateTimeFormat &date_time_format, const std::source_location &source_location, const QString &msg );
	/// @brief 格式化一个源文件信息对象
	/// @param source_file 格式化源文件路径
	/// @param source_function 格式化源文件函数
	/// @param source_line 格式化源文件行号
	/// @param location 被格式化的源文件信号对象
	void formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location );
	/// @brief 获取堆栈信息
	/// @param stack_trace 堆栈信息
	/// @param skip 跳过堆栈
	size_t formatStacktrace( QString &stack_trace, const size_t &skip = 1 );

	/// @brief 获取堆栈信息
	/// @param stack_trace 堆栈信息
	/// @param skip 跳过堆栈
	size_t formatStacktrace( std::vector< SourceLocation > &stack_trace, const size_t &skip = 1 );
};
#endif // SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
