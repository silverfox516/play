#include <iostream>
#include <string>

class Encryptor {
    bool m_isIncremental;
    int m_count;

public:
    Encryptor() : m_isIncremental(0), m_count(1) {}
    Encryptor(bool isInc, int count) : m_isIncremental(isInc), m_count(count) {}
    std::string operator()(std::string data) {
        for (int i = 0; i < data.size(); i++) {
            if ((data[i] >= 'a' && data[i] <= 'z')
                    || (data[i] >= 'A' && data[i] <= 'Z')) {
//                std::cout << data[i] << " -> ";
                if (m_isIncremental)
                    data[i] = data[i] + m_count;
                else
                    data[i] = data[i] - m_count;
//                std::cout << data[i] << std::endl;
            }
        }

        return data;
    }
};

std::string buildCompleteMessage(std::string rawData, Encryptor encryptorFuncObj) {
//    rawData = "HEADER" + rawData + "FOOTER";

    rawData = encryptorFuncObj(rawData);

    return rawData;
}

int main(void)
{
    std::string data = "hello, world";

    std::cout << data << std::endl;
    std::cout << buildCompleteMessage(data, Encryptor(true, 1)) << std::endl;
    std::cout << buildCompleteMessage(data, Encryptor(false, 1)) << std::endl;

    return 0;
}
