#include "catch.hpp"

//#include "abstractserver.h"
#include "abstractserverprocess.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

class AbstractServerProcessMock : public AbstractServerProcess {
public:
    AbstractServerProcessMock(const AbstractServer* parent, const ServerProcessSettings& s)
        : AbstractServerProcess(parent, s) {};

    virtual void dspSwitch(bool value) override{};
    virtual CanvasPtr createCanvas() override {return CanvasPtr(0);}

    virtual bool loadLibrary(const std::string& libraryName) override { return true;};
    virtual bool loadExternal(const std::string& externalName) override { return true;};
};

TEST_CASE("AbstractServerProcess", "[AbstractServerProcess]")
{
    ServerProcessSettings s;
    AbstractServerProcessMock srv(0, s);

    SECTION("abstractServerProcess")
    {
//        ServerProcessSettings ts = srv.settings();
//        REQUIRE(ts == s);

//        ServerProcessSettings s2;
//        srv.setSettings(s2);
//        ts = srv.settings();
//        REQUIRE(ts == s2);

        //
        REQUIRE(srv.loadLibrary(""));
        REQUIRE(srv.loadExternal(""));

        REQUIRE(srv.createCanvas().get() == 0);
    }

    //    SECTION("serverSettings")
    //    {
    //        ServerSettings s1("testOne");
    //        ServerSettings s2("testOne");
    //        ServerSettings s3("testThree");

    //        REQUIRE(s1.name() == "testOne");

    //        REQUIRE(s1 == s2);
    //        REQUIRE(s1 != s3);
    //    }

    //    SECTION("abstractServer")
    //    {
    //        ProcessPtr p = srv.createProcess();
    //        REQUIRE(p.get() == 0);

    //        REQUIRE(srv.name() == "local");
    //        REQUIRE(srv.settings() == ServerSettings("local"));

    //        srv.setSettings(ServerSettings("newLocal"));
    //        REQUIRE(srv.name() == "newLocal");
    //        REQUIRE(srv.settings() == ServerSettings("newLocal"));
    //    }
}
