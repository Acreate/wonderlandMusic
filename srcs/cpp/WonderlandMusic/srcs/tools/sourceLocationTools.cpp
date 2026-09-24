#include "sourceLocationTools.h"
#include <QFileInfo>
#include <QString>
#include <source_location>
#include <stacktrace>

#include "calculateTools.h"
#include "instanceTools.h"

#include "../application/appInstance.h"
#include "../application/appInstance/applicationManage.h"
#include "../application/appInstance/appDataManage/translate/messageTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../msgInfo/cmakeInfo.h"
#include "../msgInfo/messageString.h"

SourceLocationTools::SourceLocation::~SourceLocation( ) {
	delete fileName;
	delete functionName;
}
SourceLocationTools::SourceLocation::SourceLocation( ) : SourceLocation( 0, 0, "", "" ) {
}
SourceLocationTools::SourceLocation::SourceLocation( const SourceLocation &other ) : index { other.index }, lineCode { other.lineCode }, functionName { new QString( *other.functionName ) }, fileName { new QString( *other.fileName ) } {
}
SourceLocationTools::SourceLocation & SourceLocationTools::SourceLocation::operator=( const SourceLocation &other ) {
	if( this == &other )
		return *this;
	index = other.index;
	lineCode = other.lineCode;
	*functionName = *other.functionName;
	*fileName = *other.fileName;
	return *this;
}
SourceLocationTools::SourceLocation::SourceLocation( const size_t &index, const size_t &line_code, const QString &function_name, const QString &file_name ) : index( index ),
	lineCode( line_code ),
	functionName( new QString( function_name ) ),
	fileName( new QString( file_name ) ) {
}
SourceLocationTools::SourceLocation::SourceLocation( const size_t &index, const std::stacktrace_entry &stacktrace_entry ) : SourceLocation( index, stacktrace_entry.source_line( ), QString::fromStdString( stacktrace_entry.description( ) ), QString::fromStdString( stacktrace_entry.source_file( ) ) ) {
}
const size_t & SourceLocationTools::SourceLocation::getIndex( ) const {
	return index;
}
const size_t & SourceLocationTools::SourceLocation::getLineCode( ) const {
	return lineCode;
}
const QString & SourceLocationTools::SourceLocation::getFunctionName( ) const {
	return *functionName;
}
const QString & SourceLocationTools::SourceLocation::getFileName( ) const {
	return *fileName;
}
QString SourceLocationTools::SourceLocation::toString( ) const {
	auto maxFieldWidth = QString::number( CalculateTools::max< decltype(lineCode) >( ) ).length( );
	return QString( "[ %1 ]{\n\tfile := %2\n\tline := %3\n\tfunction := %4\n};" )
			.arg( QString::number( index ), maxFieldWidth )
			.arg( *fileName )
			.arg( QString::number( lineCode ), maxFieldWidth )
			.arg( *functionName );
}
SourceLocationTools::SourceLocation::operator QString( ) const {
	return this->toString( );
}
void SourceLocationTools::formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg ) {
	uint_least32_t msgCodeLine = location.line( );
	QString msgCodeFileName = location.file_name( );
	QString msgCodeFunctionName = location.function_name( );
	QFileInfo info( msgCodeFileName );
	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	msgCodeFileName = absoluteFilePath.remove( cmakeSourceDir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	bool message = AppTranslateTools::getMessage( [&] ( MessageTranslate &message_translate ) {
		source_file = message_translate.getSourceFile( );
		source_function = message_translate.getSourceFunction( );
		source_line = message_translate.getSourceLine( );
		return true;
	} );
	if( message == false ) {
		source_file = QObject::tr( "源文件" );
		source_function = QObject::tr( "源函数" );
		source_line = QObject::tr( "源行号" );
	}
	format_string.append( "\n-----\n :: \n : " ).append( source_file ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( source_function ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( source_line ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );
}

void SourceLocationTools::formatString( QString &format_string, const std::source_location &location, const QString &msg ) {
	QString source_file, source_function, source_line;
	SourceLocationTools::formatString( format_string, source_file, source_function, source_line, location, msg );
}

void SourceLocationTools::formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location ) {
	source_line = QString::number( location.line( ) );
	source_file = location.file_name( );
	source_function = location.function_name( );
	QFileInfo info( source_file );
	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	source_file = absoluteFilePath.remove( cmakeSourceDir );
}
size_t SourceLocationTools::formatStacktrace( QString &stack_trace, const size_t &skip ) {
	stack_trace.clear( );
	std::vector< SourceLocation > stackTrace;
	auto first = skip + 1;
	size_t count = SourceLocationTools::formatStacktrace( stackTrace, first );
	if( count == 0 )
		return count;
	first = count - 1;
	auto data = stackTrace.data( );
	if( first )
		for( count = 0; count < first; count += 1 )
			stack_trace.append( data[ count ].toString( ) + "\n" );
	stack_trace.append( data[ first ].toString( ) );
	return first + 1;
}
size_t SourceLocationTools::formatStacktrace( std::vector< SourceLocation > &stack_trace, const size_t &skip ) {
	auto st = std::stacktrace::current( skip );
	size_t entryCount = st.size( );
	if( entryCount == 0 )
		return 0;
	QString sourceDir;
	if( CmakeInfo::getGeneratePorjectCmakeSourceDir( sourceDir ) == false )
		return 0;
	QString applicationName;
	if( CmakeInfo::getGeneratePorjectCmakeAppName( applicationName ) == false )
		return 0;
	applicationName += "!";
	size_t stackTraceIndex = 0;
	auto iterator = st.begin( );
	auto end = st.end( );
	QString description;
	QString fileName;
	QFileInfo fileInfo;
	qsizetype indexOf;
	qsizetype startIndex = applicationName.length( );
	for( ; iterator != end; ++iterator ) {
		auto &refIterVar = *iterator;
		description = QString::fromStdString( refIterVar.description( ) );
		if( description.startsWith( applicationName ) == false )
			continue;
		fileName = QString::fromStdString( refIterVar.source_file( ) );
		fileInfo.setFile( fileName );
		if( fileInfo.exists( ) == false )
			continue;
		fileName = fileInfo.absoluteFilePath( );
		if( fileName.startsWith( sourceDir ) == false )
			continue;
		fileName.remove( sourceDir );
		indexOf = description.lastIndexOf( "+0x" );
		if( indexOf != -1 )
			description = description.mid( startIndex, indexOf - startIndex );
		else
			description = description.mid( startIndex );

		stack_trace.emplace_back( SourceLocation( stackTraceIndex, refIterVar.source_line( ), description, fileName ) );
		stackTraceIndex += 1;
	}
	return stackTraceIndex;
}

void SourceLocationTools::formatString( QString &result_msg, const DateTimeFormat &date_time_format, const std::source_location &source_location, const QString &msg ) {
	uint_least32_t msgCodeLine = source_location.line( );
	QString msgCodeFileName = source_location.file_name( );
	QString msgCodeFunctionName = source_location.function_name( );
	QFileInfo info( msgCodeFileName );

	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	msgCodeFileName = absoluteFilePath.remove( cmakeSourceDir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;
	bool message = AppTranslateTools::getMessage( [&sourceFile, &sourceFunction, &sourceLine] ( MessageTranslate &message_translate ) {
		sourceFile = message_translate.getSourceFile( );
		sourceFunction = message_translate.getSourceFunction( );
		sourceLine = message_translate.getSourceLine( );
		return true;
	} );
	if( message == false ) {
		sourceFile = QObject::tr( "源文件" );
		sourceFunction = QObject::tr( "源函数" );
		sourceLine = QObject::tr( "源行号" );
	}

	result_msg.append( "\n-----\n :: \n : " ).append( sourceFile ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( sourceFunction ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( sourceLine ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );
}
