#ifndef KEYSWAPPER_H
#define KEYSWAPPER_H

#include "Libraries.h"
#include "AES.h"

class keyswapper : public QThread
{
    Q_OBJECT
public:
    keyswapper();
    void givekey(std::string);
    void sendtext(std::string&, bool);

    // QThread interface
protected:
    void run();

public slots:
    void endloopslot();

private:
    std::string key;

    std::string encryptor1;
    std::string encryptor2;
    std::string encryptor3;

    bool loop;
    Rijndael aes;
};

#endif // KEYSWAPPER_H
