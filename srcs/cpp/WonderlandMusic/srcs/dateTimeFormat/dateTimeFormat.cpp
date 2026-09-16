#include "dateTimeFormat.h"

#include <qdatetime.h>

#include <application/appInstance.h>
#include <application/appInstance/appDataManage/translate/dateTimeFormatTranslate.h>

void DateTimeFormat::fillData( const QChar *source_data, const qsizetype &source_count, QChar *dest_data ) const {
	qsizetype index = 0;
	for( ; index < source_count; ++index )
		dest_data[ index ] = source_data[ index ];
}
DateTimeFormat::~DateTimeFormat( ) {
	delete currentDate;
	delete currentTime;
}

DateTimeFormat::DateTimeFormat( const QDate &current_date, const QTime &current_time ) {
	currentDate = new QDate( current_date );
	currentTime = new QTime( current_time );
}

DateTimeFormat::DateTimeFormat( const QDateTime &current_date_time ) : DateTimeFormat( current_date_time.date( ), current_date_time.time( ) ) {
}

DateTimeFormat::DateTimeFormat( ) {
	auto current = QDateTime::currentDateTime( );
	currentDate = new QDate( current.date( ) );
	currentTime = new QTime( current.time( ) );
}

QString & DateTimeFormat::formatData( QString &result_format, const QDate &format_data ) const {
	QString year;
	QString month;
	QString day;
	if( AppTranslateTools::getDateTimeFormat( [&] ( DateTimeFormatTranslate &translate ) {
		year = translate.getYear( );
		month = translate.getMonth( );
		day = translate.getDay( );
		return true;
	} ) == false ) {
		year = QObject::tr( "年" );
		month = QObject::tr( "月" );
		day = QObject::tr( "日" );
	}

	// 测量年翻译的长度
	qsizetype translateYearLenght = year.length( );
	// 测量月翻译的长度
	qsizetype translateMonthLenght = month.length( );
	// 测量日翻译的长度
	qsizetype translateDayLenght = day.length( );
	// 年份转字符串
	auto yearDataToString = QString( "%1" ).arg( QString::number( format_data.year( ) ), 4, '0' );
	// 月份转字符串
	auto monthDataToString = QString( "%1" ).arg( QString::number( format_data.month( ) ), 2, '0' );
	// 日期转字符串
	auto dayDataToString = QString( "%1" ).arg( QString::number( format_data.day( ) ), 2, '0' );
	// 年数字长度
	qsizetype yearDataToStringLenght = yearDataToString.length( );
	// 月数字长度
	qsizetype monthDataToStringLenght = monthDataToString.length( );
	// 日数字长度
	qsizetype dayDataToStringLenght = dayDataToString.length( );
	// 新的大小
	qsizetype resetMaxSize = yearDataToStringLenght + monthDataToStringLenght + dayDataToStringLenght + translateYearLenght + translateMonthLenght + translateDayLenght;
	// 重置字符串大小
	result_format.resize( resetMaxSize );
	// 填充计数
	qsizetype fillIndex;
	// 获取目标地址
	QChar *destData = result_format.data( );

	// 填充年份数字
	fillData( yearDataToString.data( ), yearDataToStringLenght, destData );
	// 填充年翻译
	fillIndex = yearDataToStringLenght;
	fillData( year.data( ), translateYearLenght, destData + fillIndex );

	// 填充月份数字
	fillIndex = fillIndex + translateYearLenght;
	fillData( monthDataToString.data( ), monthDataToStringLenght, destData + fillIndex );
	// 填充月翻译
	fillIndex = fillIndex + monthDataToStringLenght;
	fillData( month.data( ), translateMonthLenght, destData + fillIndex );

	// 填充日期数字
	fillIndex = fillIndex + translateMonthLenght;
	fillData( dayDataToString.data( ), dayDataToStringLenght, destData + fillIndex );
	// 填充日期翻译
	fillIndex = fillIndex + dayDataToStringLenght;
	fillData( day.data( ), translateDayLenght, destData + fillIndex );

	return result_format;
}

QString & DateTimeFormat::formatTime( QString &result_format, const QTime &format_time ) const {
	QString hour;
	QString minute;
	QString second;
	QString millsecond;

	if( AppTranslateTools::getDateTimeFormat( [&] ( DateTimeFormatTranslate &translate ) {
		hour = translate.getHour( );
		minute = translate.getMinute( );
		second = translate.getSecond( );
		millsecond = translate.getMillsecond( );
		return true;
	} ) == false ) {
		hour = QObject::tr( "时" );
		minute = QObject::tr( "分" );
		second = QObject::tr( "秒" );
		millsecond = QObject::tr( "毫秒" );
	}

	// 测量时翻译的长度
	qsizetype translateHourLenght = hour.length( );
	// 测量分翻译的长度
	qsizetype translateMinuteLenght = minute.length( );
	// 测量秒翻译的长度
	qsizetype translateSecondLenght = second.length( );
	// 测量毫秒翻译的长度
	qsizetype translateMillsecondLenght = millsecond.length( );

	// 小时转字符串
	auto hourTimeToString = QString( "%1" ).arg( QString::number( format_time.hour( ) ), 2, '0' );
	// 分钟转字符串
	auto minuteTimeToString = QString( "%1" ).arg( QString::number( format_time.minute( ) ), 2, '0' );
	// 秒数转字符串
	auto secondTimeToString = QString( "%1" ).arg( QString::number( format_time.second( ) ), 2, '0' );
	// 毫秒转字符串
	auto millsecondTimeToString = QString( "%1" ).arg( QString::number( format_time.msec( ) ), 3, '0' );

	// 小时数字长度
	qsizetype hourTimeToStringLenght = hourTimeToString.length( );
	// 分钟数字长度
	qsizetype minuteTimeToStringLenght = minuteTimeToString.length( );
	// 秒数数字长度
	qsizetype secondTimeToStringLenght = secondTimeToString.length( );
	// 毫秒数字长度
	qsizetype millsecondTimeToStringLenght = millsecondTimeToString.length( );

	// 新的大小
	qsizetype resetMaxSize = hourTimeToStringLenght + minuteTimeToStringLenght + secondTimeToStringLenght + millsecondTimeToStringLenght + translateHourLenght + translateMinuteLenght + translateSecondLenght + translateMillsecondLenght;
	result_format.resize( resetMaxSize );

	// 重置字符串大小
	result_format.resize( resetMaxSize );
	// 填充计数
	qsizetype fillIndex;
	// 获取目标地址
	QChar *destData = result_format.data( );

	// 填充小时数字
	fillData( hourTimeToString.data( ), hourTimeToStringLenght, destData );
	// 填充小时翻译
	fillIndex = hourTimeToStringLenght;
	fillData( hour.data( ), translateHourLenght, destData + fillIndex );

	// 填充分钟数字
	fillIndex = fillIndex + translateHourLenght;
	fillData( minuteTimeToString.data( ), minuteTimeToStringLenght, destData + fillIndex );
	// 填充分钟翻译
	fillIndex = fillIndex + minuteTimeToStringLenght;
	fillData( minute.data( ), translateMinuteLenght, destData + fillIndex );

	// 填充秒数数字
	fillIndex = fillIndex + translateMinuteLenght;
	fillData( secondTimeToString.data( ), secondTimeToStringLenght, destData + fillIndex );
	// 填充秒数翻译
	fillIndex = fillIndex + secondTimeToStringLenght;
	fillData( second.data( ), translateSecondLenght, destData + fillIndex );

	// 填充秒数数字
	fillIndex = fillIndex + translateSecondLenght;
	fillData( millsecondTimeToString.data( ), millsecondTimeToStringLenght, destData + fillIndex );
	// 填充秒数翻译
	fillIndex = fillIndex + millsecondTimeToStringLenght;
	fillData( millsecond.data( ), translateMillsecondLenght, destData + fillIndex );

	return result_format;
}

QString DateTimeFormat::formatData( const QDate &format_data ) const {
	QString result;
	return formatData( result, format_data );
}

QString DateTimeFormat::formatTime( const QTime &format_time ) const {
	QString result;
	return formatTime( result, format_time );
}

QString & DateTimeFormat::formatData( QString &result_format ) const {
	return formatData( result_format, *this->currentDate );
}

QString & DateTimeFormat::formatTime( QString &result_format ) const {
	return formatTime( result_format, *this->currentTime );
}

QString DateTimeFormat::formatData( ) const {
	QString result;
	return formatData( result );
}

QString DateTimeFormat::formatTime( ) const {
	QString result;
	return formatTime( result );
}

QString DateTimeFormat::millsecondToHourMinSecFrom( qint64 totalMs ) {
	qint64 totalSec = totalMs / 1000;
	qint64 h = totalSec / 3600;
	qint64 m = ( totalSec % 3600 ) / 60;
	qint64 s = totalSec % 60;
	return QString( "%1:%2:%3" )
			.arg( h, 2, 10, QChar( '0' ) )
			.arg( m, 2, 10, QChar( '0' ) )
			.arg( s, 2, 10, QChar( '0' ) );
}
QString DateTimeFormat::millsecondToHourMinSecFrom( qint64 totalMs, bool remove_zero ) {
	if( remove_zero == false )
		return DateTimeFormat::millsecondToHourMinSecFrom( totalMs );
	qint64 totalSec = totalMs / 1000;
	qint64 h = totalSec / 3600;
	qint64 m = ( totalSec % 3600 ) / 60;
	qint64 s = totalSec % 60;
	if( h == 0 ) {
		if( m == 0 )
			return QString( "%1" ).arg( s, 2, 10, QChar( '0' ) );
		else
			return QString( "%1:%2" ).arg( m, 2, 10, QChar( '0' ) ).arg( s, 2, 10, QChar( '0' ) );
	}
	return QString( "%1:%2:%3" )
			.arg( h, 2, 10, QChar( '0' ) )
			.arg( m, 2, 10, QChar( '0' ) )
			.arg( s, 2, 10, QChar( '0' ) );
}
QString DateTimeFormat::millsecondToHourMinSecFrom( const QTime &totalMs ) {
	return millsecondToHourMinSecFrom( totalMs.msecsSinceStartOfDay( ) );
}
QString DateTimeFormat::millsecondToHourMinSecFrom( const QTime &totalMs, bool remove_zero ) {
	return millsecondToHourMinSecFrom( totalMs.msecsSinceStartOfDay( ), remove_zero );
}
