#include "countrycode.h"

CountryCode::CountryCode()
{

}

CountryCode::CountryCode(QString flagFile, QString countryName, QString shortName, int countryPrefix){
    this->flagFile = flagFile;
    this->countryName = countryName;
    this->shortName = shortName;
    this->countryPrefix = countryPrefix;
}

QString CountryCode::getFlagFile(){
    return flagFile;
}

QString CountryCode::getIconFullPath(QString iconPath){
    QString fullPath = iconPath + flagFile + ".jpg";
    fullPath.remove(" ");
    return fullPath;
   }

QString CountryCode::getCountryName(){
    return countryName;
}

QString CountryCode::getShortName(){
    return shortName;
}

int CountryCode::getCountryPrefix(){
    return countryPrefix;
}


