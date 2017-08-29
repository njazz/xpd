#include "pd_consoleobserver.h"

namespace xpd {

ConsoleObserverPtr PdConsoleObserver::_pdConsoleObserver;

void PdConsoleObserver::hookFunction(const char* str)
{
    if (_pdConsoleObserver) {
        //cout << "print hook: " << str << endl;
        _pdConsoleObserver->setText(str);
        _pdConsoleObserver->update();
    }
}

} // namespace xpd