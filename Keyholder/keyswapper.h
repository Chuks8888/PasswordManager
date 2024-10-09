#ifndef KEYSWAPPER_H
#define KEYSWAPPER_H

#include "../Libraries.h"
#include "../Rijndael/rijndael.h"

/* The keyswapper class is the thread that
 * is holding onto the key while program execution
 * during the thread's run the key is being encrypted
 * by random keys
 * when the thread stops, the key is then revealed and
 * the class can be asked to encrypt or decrypt some data
 * (i.e. std::string)
 * Then after passing the text the thread should be turned on
 * again
 * note, that only this class should have access to the key
 * and only this class is allowed to use the aes algorithm
*/
class keyswapper : public QThread
{
    Q_OBJECT
public:
    keyswapper();
    void givekey(std::string); // the class gets the key from the login input
    bool sendtext(std::string&, bool); // the class encrypts/decrypts the string

    // QThread interface
protected:
    void run(); // during runtime the keyswapping mechanism works

public slots:
    void endloopslot(); // slot to end the swapping loop

private slots: // testing slots
    void threadStart();
    void threadEnd();

private:
    std::string key;

    // randomly generated keys
    std::string encryptor1;
    std::string encryptor2;
    std::string encryptor3;

    // the aes class and the boolean
    // that keeps the loop going
    bool loop;
    Rijndael aes;
};

#endif // KEYSWAPPER_H
