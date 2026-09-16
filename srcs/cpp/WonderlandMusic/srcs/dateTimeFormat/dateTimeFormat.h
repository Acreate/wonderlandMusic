#ifndef DATETIMEFORMAT_H_H_HEAD__FILE__
#define DATETIMEFORMAT_H_H_HEAD__FILE__
#include <qtypes.h>

class QString;
class QChar;
class QDateTime;
class QTime;
class QDate;

class DateTimeFormat {
	QDate *currentDate;
	QTime *currentTime;

private:
	virtual void fillData( const QChar *source_data, const qsizetype &source_count, QChar *dest_data ) const;

public:
	virtual ~DateTimeFormat( );
	DateTimeFormat( const QDate &current_date, const QTime &current_time );
	DateTimeFormat( const QDateTime &current_date_time );
	DateTimeFormat( );

	virtual QString & formatData( QString &result_format, const QDate &format_data ) const;
	virtual QString & formatTime( QString &result_format, const QTime &format_time ) const;
	virtual QString formatData( const QDate &format_data ) const;
	virtual QString formatTime( const QTime &format_time ) const;
	virtual QString & formatData( QString &result_format ) const;
	virtual QString & formatTime( QString &result_format ) const;
	virtual QString formatData( ) const;
	virtual QString formatTime( ) const;

public:
	static QString millsecondToHourMinSecFrom( qint64 totalMs );
	static QString millsecondToHourMinSecFrom( qint64 totalMs, bool remove_zero );
	static QString millsecondToHourMinSecFrom( const QTime &totalMs );
	static QString millsecondToHourMinSecFrom( const QTime &totalMs, bool remove_zero );
};

#endif // DATETIMEFORMAT_H_H_HEAD__FILE__
