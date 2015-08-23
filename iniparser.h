#ifndef _INIPARSER_H_
#define _INIPARSER_H_

#include <QtCore>
#include <QDebug>
#include <QFile>

class INIparser : public QObject
{
	Q_OBJECT

public:
	static qint16 createFile(QString filename);
	static qint16 deleteFile(QString filename);

	static qint16 createVariable(QString filename, QString data, QString value);
	static qint16 deleteVariable(QString filename, QString data);

	static qint16 setData(QString filename, QString data, QString value, bool createIfNotExist = true);
	static qint16 getData(QString filename, QString data, QString *output);

	static qint16 addSection(QString filename, QString sectionName);
	// Static so function can be called outside of the class without makeing an object first
};

#endif
