#include "pd_canvas.h"
#include "logger.h"
#include "pd_canvas_pr.h"
#include "pd_floatarray.h"
#include "pd_object.h"

#include "cpd/cpd.h"

using namespace xpd;

PdCanvas::PdCanvas(const CanvasSettings& s)
    : Canvas(nullptr, s)
    , cnv_(nullptr)
{
    cnv_ = cpd_patch_new();
    if (!cnv_) {
        log()->error("can't create canvas");
        throw Exception("can't create canvas");
    }
}

PdCanvas::PdCanvas(const Canvas* parent, const CanvasSettings& s)
    : Canvas(parent, s)
    , cnv_(0)
{
    log()->info("subpatch created");

    auto* p = dynamic_cast<const PdCanvas*>(parent);
    if (!p) {
        throw Exception("PdCanvas expected as parent");
    }

    auto pd_cnv = const_cast<t_cpd_canvas*>(p->canvas());

    auto lst = cpd_list_new(0);
    // TODO parser arguments
    cnv_ = cpd_subpatch_new(pd_cnv, s.name().c_str(), lst, s.x(), s.y());
    cpd_list_free(lst);

    if (!cnv_) {
        log()->error("can't create canvas");
        throw Exception("can't create canvas");
    }
}

PdCanvas::~PdCanvas()
{
    obj_list_.clear();

    if (parent() == 0) {
        cpd_canvas_free(cnv_);
    } else {
        auto* p = dynamic_cast<const PdCanvas*>(parent());
        auto pd_cnv = const_cast<t_cpd_canvas*>(p->canvas());
        cpd_object_free(pd_cnv, cpd_canvas_to_object(cnv_));
    }
}

ObjectId PdCanvas::createObject(const std::string& name, int x, int y)
{
    if (isSubpatchName(name)) {
        CanvasSettings settings(name, x, y);
        Object* cnv = new PdCanvas(this, settings);
        obj_list_.append(cnv);
        return cnv->id();
    }

    //    t_cpd_atomlist* lst = cpd_list_new();
    //    lst.n = 0;
    //    lst.data = 0;

    // throws exception on error
    Object* obj = new PdObject(this, name, PdArguments(), x, y);
    // ok
    obj_list_.append(obj);

    // update inlets/outlets
    updateXlets();

    return obj->id();
}

bool PdCanvas::connect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx)
{
    t_cpd_object* pd_src = findById(src);
    t_cpd_object* pd_dest = findById(dest);

    if (!pd_src || !pd_dest) {
        log()->error("PdCanvas::connect: invalid object ID: {} {}", src, dest);
        return false;
    }

    if (!obj_list_.connect(src, outletIdx, dest, inletIdx))
        return false;

    return cpd_connect(pd_src, outletIdx, pd_dest, inletIdx);
}

const t_cpd_canvas* PdCanvas::canvas() const
{
    return cnv_;
}

t_cpd_object* PdCanvas::findById(ObjectId id)
{
    Object* o = obj_list_.findObject(id);
    return o ? static_cast<PdObject*>(o)->pdObject() : nullptr;
}

void PdCanvas::updateXlets()
{
    updateInlets();
    updateOutlets();
}

void PdCanvas::updateInlets()
{
    inlet_list_.clear();

    auto pobj = cpd_canvas_to_object(cnv_);
    const size_t N = cpd_object_inlet_count(pobj);

    for (size_t i = 0; i < N; i++) {
        auto cpd_type = cpd_object_inlet_type(pobj, i);
        auto xpd_type = inletTypeToXpd(cpd_type);
        inlet_list_.push_back(Inlet(xpd_type));
    }
}

void PdCanvas::updateOutlets()
{
    outlet_list_.clear();

    auto pobj = cpd_canvas_to_object(cnv_);
    const size_t N = cpd_object_outlet_count(pobj);

    for (size_t i = 0; i < N; i++) {
        auto cpd_type = cpd_object_outlet_type(pobj, i);
        auto xpd_type = inletTypeToXpd(cpd_type);
        outlet_list_.push_back(Outlet(xpd_type));
    }
}

ObjectId PdCanvas::createArray(const std::string& name, size_t size)
{
    Object* array = new PdFloatArray(this, name, size);
    obj_list_.append(array);
    return array->id();
}

void PdCanvas::loadbang()
{
    cpd_canvas_loadbang(cnv_);
}
