#ifndef COUNTRYCODE_H
#define COUNTRYCODE_H

#include <QString>



class CountryCode
{
private:
    QString flagFile;
    QString countryName;
    QString shortName;
    int countryPrefix;

public:
    CountryCode();

    CountryCode(QString flagFile, QString countryName, QString shortName, int countryPrefix);
    QString getIconFullPath(QString iconPath);

    QString getFlagFile();

    QString getCountryName();

    QString getShortName();

    int getCountryPrefix();
};

#endif // COUNTRYCODE_H
