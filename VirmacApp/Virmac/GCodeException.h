#ifndef __GCODEEXCEPTION_H__
#define __GCODEEXCEPTION_H__

#include <qstring.h>

namespace CGCodeException
{

	class FileNotFound 
	{
	public:
		FileNotFound(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

	class SyntaxError
	{
	public:
		SyntaxError(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

	class MissingDecimal
	{
	public:
		MissingDecimal(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

	class MultipleDecimal 
	{
	public:
		MultipleDecimal(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

	class MultipleAddress 
	{
	public:
		MultipleAddress(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

	class PathNotDone 
	{
	public:
		PathNotDone(QString str) : errString(str) {;}
		QString What() const { return errString; }
	private:
		QString errString;
	};

};

#endif
