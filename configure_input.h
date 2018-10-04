#ifndef CONFIGURE_INPUT_H
#define CONFIGURE_INPUT_H
#include <QDebug>
template <class T>
class Configure_Input
{
protected:
    T mConfigureData;
public:
    Configure_Input(){};
    Configure_Input(const T& _configureData); // constant referance
    void reconfig(const T& _configureData);
    const T& getConfigInfo();
};

template <typename T>
Configure_Input<T>::Configure_Input(const T& _configureData)
    : mConfigureData(_configureData)
{
    qDebug()<<"constructor Configure_Input worked";
}

template <typename T>
const T& Configure_Input<T>::getConfigInfo()
{
    return mConfigureData;
}

template <typename T>
void Configure_Input<T>::reconfig(const T& _configureData)
{
    mConfigureData = _configureData;
}

#endif // CONFIGURE_INPUT_H
