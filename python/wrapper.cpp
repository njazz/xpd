#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pd_localprocess.h"
#include "pd_localserver.h"
#include "pd_canvas.h"

#include "observer.h"

#include "canvasobserver.h"

namespace py = pybind11;

PYBIND11_MODULE(puredatapy, m) {

  // *1. server

  py::class_<xpd::ServerSettings>(m,"ServerSettings")
    .def(py::init<std::string>())
    .def("name", &xpd::ServerSettings::name);

  py::class_<xpd::PdLocalServer>(m, "LocalServer")
    .def(py::init<xpd::ServerSettings>())
    // abstract
    .def("settings", &xpd::AbstractServer::settings)
    .def("set_settings", &xpd::AbstractServer::setSettings)

    .def("name", &xpd::AbstractServer::name)
    .def("process_list", &xpd::AbstractServer::processList)

    // pd local
    .def("create_process", &xpd::PdLocalServer::createProcess)

    .def("name", &xpd::PdLocalServer::name)
    ;

  // 2a. Observers
    py::class_<xpd::Observer, xpd::ObserverPtr>(m,"Observer")

  ;
  py::class_<xpd::ConsoleObserver, xpd::ConsoleObserverPtr>(m,"ConsoleObserver")

;
  // *2. process

  py::class_<xpd::ServerProcessSettings>(m, "ServerProcessSettings")
    .def(py::init());

  py::class_<xpd::AbstractServerProcess, xpd::ProcessPtr>(m,"ServerProcess")
  // py::class_<xpd::PdLocalProcess, xpd::ProcessPtr>(m, "Process");

    .def("dsp_on", &xpd::AbstractServerProcess::dspOn)
    .def("dsp_off", &xpd::AbstractServerProcess::dspOff)
    .def("dsp_switch", &xpd::AbstractServerProcess::dspSwitch)

    .def("settings", &xpd::AbstractServerProcess::settings)
    .def("set_settings", &xpd::AbstractServerProcess::setSettings)

    .def("path", [](xpd::ProcessPtr ptr){return ptr->path();})

    .def("register_observer", &xpd::AbstractServerProcess::registerObserver)
    .def("unregister_observer", &xpd::AbstractServerProcess::unregisterObserver)

    .def("register_console_observer", &xpd::AbstractServerProcess::registerConsoleObserver)
    .def("unregister_console_observer", &xpd::AbstractServerProcess::unregisterConsoleObserver)

    .def("add_search_path", &xpd::AbstractServerProcess::addSearchPath)
    .def("load_library", &xpd::AbstractServerProcess::loadLibrary)
    .def("load_external", &xpd::AbstractServerProcess::loadExternal)

    .def("loaded_libraries", &xpd::AbstractServerProcess::loadedLibraries)
    .def("loaded_classes", &xpd::AbstractServerProcess::loadedClasses)

    .def("parent", &xpd::AbstractServerProcess::parent)

    .def("post", &xpd::AbstractServerProcess::post)
    .def("error", &xpd::AbstractServerProcess::error)
    .def("log", &xpd::AbstractServerProcess::log)

    .def("create_canvas", &xpd::AbstractServerProcess::createCanvas)
    .def("delete_canvas", &xpd::AbstractServerProcess::deleteCanvas)
    .def("canvas_list", &xpd::AbstractServerProcess::canvasList)
    .def("canvas_count", &xpd::AbstractServerProcess::canvasCount)

    .def("send_message", &xpd::AbstractServerProcess::sendMessage)

    ;

  // *3a. canvas settings
  py::class_<xpd::CanvasSettings>(m,"CanvasSettings")
    .def(py::init<std::string, int, int, size_t, size_t>())

    .def("name", &xpd::CanvasSettings::name)

    .def("x", &xpd::CanvasSettings::x)
    .def("y", &xpd::CanvasSettings::y)
    .def("width", &xpd::CanvasSettings::width)
    .def("height", &xpd::CanvasSettings::height)
  ;

  // 3b. canvas observer
  py::class_<xpd::CanvasObserver>(m,"CanvasObserver")

  ;

  // *3. canvas

  py::class_<xpd::Canvas, xpd::CanvasPtr>(m,"Canvas")
    // .def(py::init<Canvas*, CanvasSettings>())

    .def("settings", &xpd::Canvas::settings)

    .def("path", &xpd::Canvas::path)

    .def("register_observer", &xpd::Canvas::registerObserver)
    .def("delete_observer", &xpd::Canvas::deleteObserver)

    .def("objects", &xpd::Canvas::objects)

    .def("connect", &xpd::Canvas::connect)
    .def("disconnect", &xpd::Canvas::disconnect)

    .def("create_object", &xpd::Canvas::createObject)
    .def("delete_object", &xpd::Canvas::deleteObject)

    .def("create_array", &xpd::Canvas::createArray)

    .def("has_children", &xpd::Canvas::hasChildren)
    .def("children_count", &xpd::Canvas::childrenCount)
    .def("children", &xpd::Canvas::children)
    .def("remove_all_children", &xpd::Canvas::removeAllChildren)

    .def("send_bang", &xpd::Canvas::sendBang)
    .def("send_float", &xpd::Canvas::sendFloat)

    .def("loadbang", &xpd::Canvas::loadbang)

    .def("is_root", &xpd::Canvas::isRoot)

    .def("available_objects",  &xpd::Canvas::availableObjects)
;

  // *4. object list

  py::class_<xpd::ObjectList>(m,"ObjectList")
    .def("get", [](xpd::ObjectList& l){return l.get();})

    .def("connections", &xpd::ObjectList::connections)

    .def("append", &xpd::ObjectList::append)
    .def("clear", &xpd::ObjectList::clear)
    .def("remove", &xpd::ObjectList::remove)
    .def("remove_index", &xpd::ObjectList::removeIndex)

    .def("empty", &xpd::ObjectList::empty)
    .def("size", &xpd::ObjectList::size)

    .def("connect", &xpd::ObjectList::connect)
    .def("disconnect", &xpd::ObjectList::disconnect)
    .def("is_connected", &xpd::ObjectList::isConnected)

    .def("find_object",[](const xpd::ObjectList& l, xpd::ObjectId id){return l.findObject(id);})
    .def("find_object_index", &xpd::ObjectList::findObjectIndex)

    .def("contains", &xpd::ObjectList::contains)
  ;

  // 5. object properties

  // py::class_<xpd::Object>(m,"ObjectProperties")
  // ;
  // 5. object
  py::class_<xpd::Object>(m,"Object")

  .def("name", &xpd::Object::name)
  .def("parent", &xpd::Object::parent)

  .def("arguments", &xpd::Object::arguments)

  .def("inlet_count", &xpd::Object::inletCount)
  .def("outlet_count", &xpd::Object::outletCount)

  .def("type", &xpd::Object::type)
  .def("set_type", &xpd::Object::setType)

  .def("register_observer", &xpd::Object::registerObserver)
  .def("delete_observer", &xpd::Object::deleteObserver)

  .def("inlets", &xpd::Object::inlets)
  .def("outlets", &xpd::Object::outlets)

  // .def("properties", &xpd::Object::properties)

  .def("id", &xpd::Object::id)

  .def("is_root", &xpd::Object::isRoot)
  .def("has_children", &xpd::Object::hasChildren)
  .def("children_count", &xpd::Object::childrenCount)
  .def("children", &xpd::Object::children)
  .def("remove_all_children", &xpd::Object::removeAllChildren)

  .def("x", &xpd::Object::x)
  .def("y", &xpd::Object::y)
  .def("set_x", &xpd::Object::setX)
  .def("set_y", &xpd::Object::setY)

  .def("send_bang", &xpd::Object::sendBang)
  .def("send_float", &xpd::Object::sendFloat)
  .def("send_symbol", &xpd::Object::sendSymbol)
  .def("send_list", &xpd::Object::sendList)

  .def("as_canvas", [](xpd::Object* obj){return obj->asCanvas();})



;



  py::class_<xpd::Arguments>(m,"Arguments")

;

  py::class_<xpd::ArgList>(m,"ArgumentsList")

;

}
