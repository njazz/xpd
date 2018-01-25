#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

class PdLocalServer : public AbstractServer {
public:
    PdLocalServer(const ServerSettings& s);
    ~PdLocalServer();
    virtual ProcessPtr createProcess() override;
};

} // namespace xpd

#endif // LOCALSERVER_H
