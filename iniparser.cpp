#include "iniparser.h"

int INIparser::createFile(string filename)
{
	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(file.exists())
	{
		// qDebug() << "File already exists";
		return -1;
	}

	if(!file.open(QIODevice::WriteOnly))
	{
		// qDebug() << "Failed to create file";
		return -2;
	}

	file.close();
	return 0;
}

int INIparser::deleteFile(string filename)
{
	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.remove())
	{
		// qDebug() << "Failed to remove file";
		return -2;
	}

	return 0;
}

int INIparser::createVariable(string filename, string data, string value)
{
	if(data.contains('='))
	{
		// qDebug() << "Invalid characters in data";
		// qDebug() << "User cannot use '='";
		return -4;
	}

	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadWrite | QIODevice::Text))		// |QIODevice::Text to enable \n
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	if(string.contains(data + '='))
	{
		// qDebug() << "Data already exists";
		file.close();
		return -3;
	}

	if(file.pos() != 0)								// To remove whitespace at beginning of file
	{
		string = '\n' + data + '=' + value;
	}
	else
	{
		string = data + '=' + value;
	}

	file.write(string.toUtf8());
	file.close();
	return 0;
}

int INIparser::deleteVariable(string filename, string data)
{
	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadWrite))
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	if(!string.contains(data + '='))
	{
		// qDebug() << "Data does not exists";
		file.close();
		return -3;
	}

	file.seek(0);							// Reset pos to start of file
	temp = "";								// Clear temp
	while(!file.atEnd())
	{
		// Add all the lines which don't contain <data>
		string = file.readLine();
		if(!string.contains(data + '='))
		{
			temp.append(string);
		}
	}

	file.resize(0);					// Empty the file
	file.write(temp.toUtf8());		// Write to the file
	file.close();

	return 0;
}

int INIparser::getData(string filename, string data, string *output)
{
	filename = filename.toLower();
	if(!filename.contains(".ini"))
	{
		filename = filename + ".ini";
	}
	File file(filename);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadOnly))
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	if(!string.contains(data + '='))
	{
		// qDebug() << "There is no data called " + data;
		return -3;
		file.close();
	}

	file.seek(0);			// Reset pos to start of file
	string = "";			// empty sting
	string temp = "";
	while(!string.contains(data + '='))
	{
		string = file.readLine();
		if(string.contains(data + '='))
		{
			int i = 0;
			while(string.at(i) != '=')
			{
				i++;
			}

			char end = 1;				// Avoid illegal memory acces
			if(!file.atEnd())
			{
				end = 3;				// Remove \r\n & avoid illegal memory acces
			}

			while(i < (string.length() - end))
			{
				i++;
				temp.append(string.at(i));
			}
		}
	}

	file.close();
	*output = temp;
	return 0;
}

int INIparser::setData(string filename, string data, string value, bool createIfNotExist)
{
	if(data.contains('='))
	{
		// qDebug() << "Invalid characters in data";
		// qDebug() << "User cannot use '='";
		return -4;
	}

	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadWrite))
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	if(!string.contains(data + '='))
	{
		if(!createIfNotExist)
		{
			// qDebug() << "Data does not exists, Stopping";
			file.close();
			return -3;
		}
		else
		{
			// qDebug() << "Data does not exist, creating new variable";
			file.close();
			return createVariable(filename, data, value);
		}
	}

	file.seek(0);							// Reset pos to start of file
	temp = "";								// Clear temp
	while(!file.atEnd())
	{
		// Add all the lines which don't contain <data>
		string = file.readLine();
		if(!string.contains(data + '='))
		{
			temp.append(string);
		}
		else
		{
			// Add new value instead of old one
			temp.append(data + '=' + value);
			if(!file.atEnd())
			{
				temp.append("\r\n");
			}
		}
	}

	file.resize(0);					// Empty the file
	file.write(temp.toUtf8());		// Write to the file
	file.close();
	return 0;
}

int INIparser::addSection(string filename, string sectionName)
{
	if(sectionName.contains('='))
	{
		// qDebug() << "Invalid characters in sectionName";
		// qDebug() << "User cannot use '='";
		return -4;
	}

	string temp = filename.toLower();
	if(!filename.contains(".ini"))
	{
		temp = temp + ".ini";
	}
	File file(temp);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadWrite | QIODevice::Text))		// |QIODevice::Text to enable \n
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	sectionName = '[' + sectionName + ']';

	if(string.contains(sectionName))
	{
		// qDebug() << "sectionName already exists";
		file.close();
		return -3;
	}

	if(file.pos() != 0)					// To remove whitespace at beginning of file
	{
		string = string + "\n\n";
	}

	string.append(sectionName);

	file.resize(0);						// Empty the file
	file.write(string.toUtf8());		// Write to the file
	file.close();
	return 0;
}
