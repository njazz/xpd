#ifndef LOCALPDPROCESS_H
#define LOCALPDPROCESS_H

#include "abstractserverprocess.h"
#include "cpd/cpd_list.h"
#include "cpd/cpd_receiver.h"
#include <map>

namespace xpd {

class PdObjectObserver;

class PdLocalProcess : public AbstractServerProcess {
    t_receiver *receiver_;
public:
    PdLocalProcess(const AbstractServer* parent, const ServerProcessSettings& s);
    ~PdLocalProcess();

    void dspSwitch(bool value) override;

    /**
     * Creates PdCanvas
     * @return pointer to new canvas or 0 on error
     */
    virtual CanvasPtr createCanvas() override;

    virtual void post(const std::string& text = "") override;
    virtual void error(const std::string& text = "") override;
    virtual void log(LogLevel level, const std::string& text) override;

    virtual void setLogLevel(LogLevel l) override;

    virtual void registerConsoleObserver(ConsoleObserverPtr o) override;
    virtual void unregisterConsoleObserver(ConsoleObserverPtr o) override;

    virtual void addSearchPath(const std::string &path) override;

    virtual LibraryList loadedLibraries() const override;
    virtual ClassList loadedClasses() const override;

    std::string getBindObjectList();
    std::vector<std::string> getLoadedClassesList();

    static void receiverCallback(t_cpd_list* msg);
    static std::map<t_cpd_object*,ObserverPtr> objectObserverMap;
};

} // namespace xpd

#endif // LOCALPDPROCESS_H
