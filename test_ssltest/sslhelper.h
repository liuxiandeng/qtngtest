#ifndef SSLHELPER_H
#define SSLHELPER_H

#include <qtnetworkng/qtnetworkng.h>

namespace NSNetwork {
    class SSLHelper
    {
    public:
        /**
         * @brief createCertificate   创建数字证书
         * @param inFilePath          [IN] 数字证书保存文件路径
         * @param inPublicKey         [IN] 公钥对象
         * @param inPrivateKey        [IN] 私钥对象
         * @param inCommonName        [IN] 通用名
         * @param inCountryCode       [IN] 国家代码
         * @param inOrganization      [IN] 组织机构
         * @param inMsgDigestAlgo     [IN] 数字证书生成算法
         * @param inSerialNumber      [IN] 序列号
         * @param inYears             [IN] 有效期(年)
         * @param inFormat            [IN] 数字证书保存文件编码格式
         * @return true : 成功
         *         false: 失败
         */
        static bool createCertificate(const QString& inFilePath,
                                      const qtng::PublicKey& inPublicKey,
                                      const qtng::PrivateKey& inPrivateKey,
                                      const QString& inCommonName,
                                      const QString& inCountryCode,
                                      const QString& inOrganization,
                                      const qtng::MessageDigest::Algorithm& inMsgDigestAlgo = qtng::MessageDigest::Sha256,
                                      const long& inSerialNumber = 171686,
                                      const int& inYears = 100,
                                      const qtng::Ssl::EncodingFormat& inFormat = qtng::Ssl::Pem);

        /**
         * @brief createPrivateKey   创建私钥
         * @param inFilePath         [IN] 私钥保存文件路径
         * @param outPrivateKey      [OUT]私钥对象
         * @param inPrivateKeyAlgo   [IN] 私钥生成算法
         * @param inPrivateKeyBits   [IN] 私钥位数
         * @param inFormat           [IN] 私钥保存文件编码格式
         * @param inPwd              [IN] 私钥保存文件密码
         * @return true : 成功
         *         false: 失败
         */
        static bool createPrivateKey(const QString& inFilePath,
                                     qtng::PrivateKey& outPrivateKey,
                                     const qtng::PrivateKey::Algorithm& inPrivateKeyAlgo = qtng::PrivateKey::Rsa,
                                     const int& inPrivateKeyBits = 2048,
                                     const qtng::Ssl::EncodingFormat& inFormat = qtng::Ssl::Pem,
                                     const QByteArray& inPwd = QByteArray());
    };
}

#endif // SSLHELPER_H
