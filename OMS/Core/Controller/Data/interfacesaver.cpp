#include "interfacesaver.h"

InterfaceSaver::InterfaceSaver(const InterfaceSaver &) : QObject() {}

bool InterfaceSaver::insertMedia(MediaPointer) {return true;}
bool InterfaceSaver::deleteMedia(QUuid) {return true;}
bool InterfaceSaver::updateMedia(QUuid) {return true;}
bool InterfaceSaver::insertPlaylist(PlaylistPointer) {return true;}
bool InterfaceSaver::deletePlaylist(QUuid) {return true;}
bool InterfaceSaver::updatePlaylist(QUuid) {return true;}
bool InterfaceSaver::insertSmartGroup(SmartGroupPointer) {return true;}
bool InterfaceSaver::deleteSmartGroup(QUuid) {return true;}
bool InterfaceSaver::updateSmartGroup(QUuid) {return true;}
bool InterfaceSaver::insertSmartRule(SmartRulePointer) {return true;}
bool InterfaceSaver::deleteSmartRule(QUuid) {return true;}
bool InterfaceSaver::updateSmartRule(QUuid) {return true;}

