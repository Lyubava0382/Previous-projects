
#include "IObservable.h"
#include "Logger.h"
void IObservable::SetObservable(bool obs){
    this->observable = obs;
}

void IObservable::SetObserver(Logger* obs){
    this->observer = obs;
}
