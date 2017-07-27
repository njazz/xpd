#include "object.h"
#include "objectlist.h"
#include "propertyobserver.h"

namespace xpd {

Object::Object(const Canvas* parent, const std::string& name, int x, int y)
    : parent_(parent)
    , name_(name)
    , id_(0)
    , x_(x)
    , y_(y)
{
}

Object::~Object()
{
}

const std::string& Object::name() const
{
    return name_;
}

const Canvas* Object::parent() const
{
    return parent_;
}

const Arguments& Object::arguments() const
{
    static Arguments a;
    return a;
}

size_t Object::inletCount() const
{
    return 0;
}

size_t Object::outletCount() const
{
    return 0;
}

ObjectType Object::type() const
{
    return OBJ_TYPE_SIMPLE_BOX;
}

void Object::setType(ObjectType type)
{
}

void Object::registerObserver(ObserverPtr o)
{
}

void Object::deleteObserver(ObserverPtr)
{
}

const InletList& Object::inlets() const
{
    return inlet_list_;
}

const OutletList& Object::outlets() const
{
    return outlet_list_;
}

const ObjectProperties& Object::properties() const
{
    static ObjectProperties props;
    return props;
}

ObjectId Object::id() const
{
    return id_;
}

bool Object::isRoot() const
{
    return false;
}

bool Object::hasChildren() const
{
    return false;
}

size_t Object::childrenCount() const
{
    return 0;
}

const ObjectList& Object::children() const
{
    static ObjectList empty;
    return empty;
}

int Object::x() const
{
    return x_;
}

int Object::y() const
{
    return y_;
}

void Object::setX(int x)
{
    x_ = x;
}

void Object::setY(int y)
{
    y_ = y;
}

void Object::sendBang()
{
}

void Object::sendFloat(float f)
{
}

void Object::sendSymbol(const std::string& s)
{
}

} // namespace xpd
