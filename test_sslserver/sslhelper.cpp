/**************************************************************************************************************
 *
 * @file: sslhelper.cpp
 * @brief:
 * @details:
 *
 * @author: 章文兴
 * @date: 2021/06/23
 * @version:
 * @note:
 *
 **************************************************************************************************************/
#include "sslhelper.h"

using namespace NSNetwork;

bool SSLHelper::createCertificate(const QString& inFilePath,
                                  const qtng::PublicKey& inPublicKey,
                                  const qtng::PrivateKey& inPrivateKey,
                                  const QString& inCommonName,
                                  const QString& inCountryCode,
                                  const QString& inOrganization,
                                  const qtng::MessageDigest::Algorithm& inMsgDigestAlgo,
                                  const long& inSerialNumber,
                                  const int& inYears,
                                  const qtng::Ssl::EncodingFormat& inFormat)
{
    QString strAbsPath = QFileInfo(inFilePath).absolutePath();
    QDir dir(strAbsPath);
    if(!dir.exists())
    {
        dir.mkpath(strAbsPath);
    }

    QFile file(inFilePath);
    if(!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QMultiMap<qtng::Certificate::SubjectInfo, QString> info;
    info.insert(qtng::Certificate::CommonName, inCommonName);
    info.insert(qtng::Certificate::CountryName, inCountryCode);
    info.insert(qtng::Certificate::Organization, inOrganization);
    const QDateTime& now = QDateTime::currentDateTime();
    const qtng::Certificate& cert = qtng::Certificate::generate(inPublicKey, inPrivateKey, inMsgDigestAlgo, inSerialNumber, now, now.addYears(inYears), info);
    file.write(cert.save(inFormat));
    file.close();
    return true;
}

bool SSLHelper::createPrivateKey(const QString& inFilePath,
                                 qtng::PrivateKey& outPrivateKey,
                                 const qtng::PublicKey::Algorithm& inPrivateKeyAlgo,
                                 const int& inPrivateKeyBits,
                                 const qtng::Ssl::EncodingFormat& inFormat,
                                 const QByteArray& inPwd)
{
    QString strAbsPath = QFileInfo(inFilePath).absolutePath();
    QDir dir(strAbsPath);
    if(!dir.exists())
    {
        dir.mkpath(strAbsPath);
    }

    QFile file(inFilePath);
    if(!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    outPrivateKey = qtng::PrivateKey::generate(inPrivateKeyAlgo, inPrivateKeyBits);
    file.write(outPrivateKey.save(inFormat, inPwd));
    file.close();
    return true;
}
