#include "manualanysdkbindings.hpp"
#include "cocos2d_specifics.hpp"
#include "js_manual_conversions.h"
#include "jsb_anysdk_basic_conversions.h"
#include "AgentManager.h"
#include "PluginProtocol.h"
#include "ProtocolPush.h"
#include "PluginFactory.h"
#include "ProtocolAds.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolSocial.h"
#include "ProtocolIAP.h"
#include "ProtocolUser.h"
#include "JSBRelation.h"
#include "mozilla/Maybe.h"

using namespace anysdk::framework;


template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");
        
        JS::RootedObject proto(cx, typeClass->proto.ref());
        JS::RootedObject parent(cx, typeClass->parentProto.ref());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new (std::nothrow) T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }
    
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}

JSClass  *jsb_anysdk_framework_PluginParam_class;
JSObject *jsb_anysdk_framework_PluginParam_prototype;


bool js_anysdk_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    JSObject *obj = NULL;
    PluginParam* cobj = NULL;
    
    do {
        if (argc == 2) {
            int arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            
            switch (arg0)
            {
                case PluginParam::kParamTypeInt:
                {
                    int arg1;
                    ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
                    if (ok) { cobj = new (std::nothrow) PluginParam(arg1); }
                }
                    break;
                case PluginParam::kParamTypeFloat:
                {
                       double arg1;
                    ok &= JS::ToNumber(cx, args.get(1), &arg1);
                    if (ok) {
                        float tempArg = arg1;
                        cobj = new (std::nothrow) PluginParam(tempArg);
                    }
                }
                    break;
                case PluginParam::kParamTypeBool:
                {
                    bool arg1 = JS::ToBoolean(args.get(1));
                    cobj = new (std::nothrow) PluginParam(arg1);
                }
                    break;
                case PluginParam::kParamTypeString:
                {
                    const char* arg1;
                    std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
                    if (ok) { cobj = new (std::nothrow) PluginParam(arg1); }
                }
                    break;
                case PluginParam::kParamTypeStringMap:
                {
                       StringMap arg1;
                    ok &= jsval_to_StringMap(cx, args.get(1), &arg1);
                    if (ok) { cobj = new (std::nothrow) PluginParam(arg1); }
                }
                    break;
                default:
                    break;
            }
            if (!ok || NULL == cobj) { ok = true; break; }
            
            TypeTest<PluginParam> t;
            js_type_class_t *typeClass;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            assert(typeMapIter != _js_global_type_map.end());
            typeClass = typeMapIter->second;
            assert(typeClass);
            JS::RootedObject proto(cx,typeClass->proto.ref());
            JS::RootedObject parent(cx, typeClass->parentProto.ref());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);
            
            JS::RootedObject _tmp(cx, obj);
            jsb_new_proxy(cobj,_tmp);
        }
    } while (0);
    
    if (cobj) {
        args.rval().set(OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool jsb_anysdk_PluginParam_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getStringValue : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getStringValue();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool jsb_anysdk_PluginParam_getCurrentType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getCurrentType : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getCurrentType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool jsb_anysdk_PluginParam_getIntValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getIntValue : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getIntValue();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getIntValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool jsb_anysdk_PluginParam_getFloatValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getFloatValue : Invalid Native Object");
    if (argc == 0) {
        float ret = cobj->getFloatValue();
        jsval jsret = JSVAL_NULL;
        jsret.setNumber(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getFloatValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool jsb_anysdk_PluginParam_getBoolValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getBoolValue : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getBoolValue();
        jsval jsret = JSVAL_NULL;
        jsret.setBoolean(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getBoolValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool jsb_anysdk_PluginParam_getMapValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getMapValue : Invalid Native Object");
    if (argc == 0) {
        typedef std::map<std::string, PluginParam*> MAP_PLUGINPARAM;
        MAP_PLUGINPARAM values = cobj->getMapValue();
        JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        if (!tmp) return false;

        MAP_PLUGINPARAM::iterator iter;
        bool ok = true;
        for (iter = values.begin(); iter != values.end(); iter++)
        {
            std::string str_key = ((std::string)(iter->first));
            js_proxy_t *jsProxy = js_get_or_create_proxy<PluginParam>(cx, (PluginParam*)iter->second);
            ok &= JS_DefineProperty(cx, tmp, str_key.c_str(), JS::RootedValue(cx, OBJECT_TO_JSVAL(jsProxy->obj)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
        }

        jsval jsret = JSVAL_NULL;
        jsret = OBJECT_TO_JSVAL(tmp);
        args.rval().set(jsret);
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getMapValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}

bool jsb_anysdk_PluginParam_getStrMapValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getStrMapValue : Invalid Native Object");
    if (argc == 0) {
        StringMap values = cobj->getStrMapValue();
        JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        if (!tmp) return false;

        StringMap::iterator iter;
        bool ok = true;
        for (iter = values.begin(); iter != values.end(); iter++)
        {
            std::string str_key = ((std::string)(iter->first));
            std::string str_tmp = ((std::string)(iter->second));
            ok &= JS_DefineProperty(cx, tmp, str_key.c_str(), JS::RootedValue(cx, std_string_to_jsval(cx, str_tmp)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
        }

        jsval jsret = JSVAL_NULL;
        jsret = OBJECT_TO_JSVAL(tmp);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "jsb_anysdk_PluginParam_getStrMapValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_cocos2dx_PluginParam_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    PluginParam* ret = NULL;
    if(argc == 0){
        ret = new (std::nothrow) PluginParam();
    }
    else if (argc == 1){
        bool ok = true;
        JS::RootedValue arg0(cx, args.get(0));
        if ( arg0.isObject() ){
            if (arg0.isNullOrUndefined()) {
                CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
                return false;
            }
            JS::RootedObject tmp(cx, arg0.toObjectOrNull());
            
            JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
            
            StringMap arg;
            
            while (true)
            {
                JS::RootedId idp(cx);
                JS::RootedValue key(cx);
                if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
                    return false; // error
                }
                
                if (key.isNullOrUndefined()) {
                    break; // end of iteration
                }
                
                if (!key.isString()) {
                    continue; // ignore integer properties
                }
                
                JSStringWrapper keyWrapper(key.toString(), cx);
                
                std::string v1;
                std::string v2;
                
                v1 = keyWrapper.get();
                JS::RootedValue value(cx);
                JS_GetPropertyById(cx, tmp, idp, &value);
                if (value.isString())
                {
                    bool ok = jsval_to_std_string(cx, value, &v2);
                    if (ok){
                        arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
                    }
                    else{
                        CCLOG("wrong param in stringmap.\n");
                    }
                }
            }
            ret = new (std::nothrow) PluginParam( arg );
        }
        else if(arg0.isBoolean()){
            bool arg = arg0.toBoolean();
            ret = new (std::nothrow) PluginParam( arg );
        }
        else if(arg0.isInt32()){
            int arg = arg0.toInt32();
            ret = new (std::nothrow) PluginParam( arg );
        }
        else if(arg0.isNumber()){
            float arg = arg0.toNumber();
            ret = new (std::nothrow) PluginParam( arg );
        }
        else if(arg0.isString()){
            std::string arg;
            ok = jsval_to_std_string(cx, arg0, &arg);
            if (ok)
                ret = new (std::nothrow) PluginParam( arg.c_str() );
            else
                CCLOG("PluginParam string is wrong.");
        }
    }
    else{
        JS_ReportError(cx, "js_cocos2dx_PluginParam_create : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    
    jsval jsret = JSVAL_NULL;
    js_proxy_t *jsProxy = js_get_or_create_proxy<PluginParam>(cx, (PluginParam*)ret);
    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
    args.rval().set(jsret);
    return true;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_PluginParam_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginParam)", obj);
    js_proxy_t* nproxy;
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    js_proxy_t* proxy = jsb_get_js_proxy(jsobj);
    if (proxy) {
        PluginParam *nobj = static_cast<PluginParam *>(proxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(proxy);
    }
}

void js_register_anysdkbindings_PluginParam(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_PluginParam_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_PluginParam_class->name = "PluginParam";
    jsb_anysdk_framework_PluginParam_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginParam_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_PluginParam_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginParam_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_PluginParam_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_PluginParam_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_PluginParam_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_PluginParam_class->finalize = js_anysdk_PluginParam_finalize;
    jsb_anysdk_framework_PluginParam_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getCurrentType", jsb_anysdk_PluginParam_getCurrentType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIntValue", jsb_anysdk_PluginParam_getIntValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFloatValue", jsb_anysdk_PluginParam_getFloatValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoolValue", jsb_anysdk_PluginParam_getBoolValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringValue", jsb_anysdk_PluginParam_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMapValue", jsb_anysdk_PluginParam_getMapValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStrMapValue", jsb_anysdk_PluginParam_getStrMapValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_PluginParam_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_anysdk_framework_PluginParam_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype), // parent proto
        jsb_anysdk_framework_PluginParam_class,
        js_anysdk_PluginParam_constructor, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//    bool found;
//FIXME: Removed in Firefox v27    
//    JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_anysdk_framework_PluginParam_prototype);
    jsb_register_class<anysdk::framework::PluginParam>(cx, jsb_anysdk_framework_PluginParam_class, proto, JS::NullPtr());
}

class ProtocolShareResultListener : public ShareResultListener
{
public:
    ProtocolShareResultListener()
    {
    }
    ~ProtocolShareResultListener()
    {
        CCLOG("on share result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onShareResult(ShareResultCode code, const char* msg) 
    {
        CCLOG("on action result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};

bool jsb_anysdk_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp){
    CCLOG("in ProtocolShare_setResultListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_ProtocolShare_setResultListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    ProtocolShareResultListener* listener = new (std::nothrow) ProtocolShareResultListener();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setResultListener(listener);
    return true;
}


bool jsb_anysdk_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp){
    CCLOG("in ProtocolShare_share, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 1)
    {
        JS_ReportError(cx, "jsb_anysdk_ProtocolShare_share : wrong number of arguments: %d, was expecting %d", argc, 0);
        return true;
    }
    JS::RootedValue arg0(cx, args.get(0));
    if ( arg0.isObject() ){
        if (arg0.isNullOrUndefined()) {
            CCLOG("%s", "jsb_anysdk_ProtocolShare_share: js argument is not an object.");
            return false;
        }
        
        TShareInfo info;
        bool ok = jsval_to_TShareInfo(cx, arg0, &info);
        JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_ProtocolShare_share : Error processing arguments");
        
        cobj->share( info );
    }
    return true;
}

JSClass  *jsb_anysdk_framework_ProtocolShare_class;
JSObject *jsb_anysdk_framework_ProtocolShare_prototype;

void js_anysdk_framework_ProtocolShare_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolShare)", obj);
}

void js_register_anysdkbindings_ProtocolShare(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolShare_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolShare_class->name = "ProtocolShare";
    jsb_anysdk_framework_ProtocolShare_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolShare_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolShare_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolShare_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolShare_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolShare_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolShare_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolShare_class->finalize = js_anysdk_framework_ProtocolShare_finalize;
    jsb_anysdk_framework_ProtocolShare_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("share", jsb_anysdk_ProtocolShare_share, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setResultListener", jsb_anysdk_ProtocolShare_setResultListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    jsb_anysdk_framework_ProtocolShare_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype), // parent proto
        jsb_anysdk_framework_ProtocolShare_class,
        empty_constructor, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//    bool found;
//FIXME: Removed in Firefox v27    
//    JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    
    JS::RootedObject proto(cx, jsb_anysdk_framework_ProtocolShare_prototype);
    jsb_register_class<anysdk::framework::ProtocolShare>(cx, jsb_anysdk_framework_ProtocolShare_class, proto, JS::NullPtr());
}

static bool jsb_anysdk_framework_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    bool ok = true;
    if(argc == 1){
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());
        cobj->callFuncWithParam(arg0.c_str(), NULL);
        return true;
    }
    else if (argc == 0) {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());

        std::vector<PluginParam*> params;
        
        JS::RootedObject obj_1(cx, args.get(1).toObjectOrNull());
        if ( JS_IsArrayObject(cx, obj_1) )
        {
            JS::RootedObject jsArr(cx);
            bool ok = args.get(1).isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, args.get(1)), &jsArr );
            JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_PluginProtocol_callFuncWithParam : Error processing arguments");
            
            uint32_t len = 0;
            JS_GetArrayLength(cx, jsArr, &len);
            CCLOG("param len: %d", len);
            for (uint32_t i=0; i < len; i++)
            {
                JS::RootedValue value(cx);
                if (JS_GetElement(cx, jsArr, i, &value))
                {
                    if (value.isObject())
                    {
                        JS::RootedObject jsobj(cx, value.toObjectOrNull());
                        js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                        PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                        params.push_back(pobj_2);
                    }
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++)
            {
                JS::RootedObject jsobj(cx, args.get(i).toObjectOrNull());
                js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
        cobj->callFuncWithParam(arg0.c_str(), params);
        return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callStringFuncWithParam, param count:%d.\n", argc);
    bool ok = true;
    if(argc == 1){
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());
        std::string ret = cobj->callStringFuncWithParam(arg0.c_str(), NULL);
        JS::RootedValue jsret(cx, std_string_to_jsval(cx, ret));
        args.rval().set(jsret);
        return true;
    }
    else if (argc == 0) {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());

        std::vector<PluginParam*> params;
        
        JS::RootedObject obj_1(cx, args.get(1).toObjectOrNull());
        if ( JS_IsArrayObject(cx, obj_1) )
        {
            JS::RootedObject jsArr(cx);
            bool ok = args.get(1).isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, args.get(1)), &jsArr );
            JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam : Error processing arguments");
            
            uint32_t len = 0;
            JS_GetArrayLength(cx, jsArr, &len);
            CCLOG("param len: %d", len);
            for (uint32_t i=0; i < len; i++)
            {
                JS::RootedValue value(cx);
                if (JS_GetElement(cx, jsArr, i, &value))
                {
                    if (value.isObject())
                    {
                        JS::RootedObject jsobj(cx, value.toObjectOrNull());
                        js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                        PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                        params.push_back(pobj_2);
                    }
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++)
            {
                JS::RootedObject jsobj(cx, args.get(i).toObjectOrNull());
                js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
        std::string ret = cobj->callStringFuncWithParam(arg0.c_str(), params);
        JS::RootedValue jsret(cx, std_string_to_jsval(cx, ret));
        args.rval().set(jsret);
        return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callIntFuncWithParam, param count:%d.\n", argc);
    bool ok = true;
    if(argc == 1){
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());
        int ret =cobj->callIntFuncWithParam(arg0.c_str(), NULL);
        JS::RootedValue jsret(cx, INT_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
    else if (argc == 0) {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());

        std::vector<PluginParam*> params;
        
        JS::RootedObject obj_1(cx, args.get(1).toObjectOrNull());
        if ( JS_IsArrayObject(cx, obj_1) )
        {
            JS::RootedObject jsArr(cx);
            bool ok = args.get(1).isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, args.get(1)), &jsArr );
            JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam : Error processing arguments");
            
            uint32_t len = 0;
            JS_GetArrayLength(cx, jsArr, &len);
            CCLOG("param len: %d", len);
            for (uint32_t i=0; i < len; i++)
            {
                JS::RootedValue value(cx);
                if (JS_GetElement(cx, jsArr, i, &value))
                {
                    if (value.isObject())
                    {
                        JS::RootedObject jsobj(cx, value.toObjectOrNull());
                        js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                        PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                        params.push_back(pobj_2);
                    }
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++)
            {
                JS::RootedObject jsobj(cx, args.get(i).toObjectOrNull());
                js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
        int ret = cobj->callIntFuncWithParam(arg0.c_str(), params);
        JS::RootedValue jsret(cx, INT_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callBoolFuncWithParam, param count:%d.\n", argc);
    bool ok = true;
    if(argc == 1){
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());
        bool ret = cobj->callBoolFuncWithParam(arg0.c_str(), NULL);
        JS::RootedValue jsret(cx, BOOLEAN_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
    else if (argc == 0) {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());

        std::vector<PluginParam*> params;
        
        JS::RootedObject obj_1(cx, args.get(1).toObjectOrNull());
        if ( JS_IsArrayObject(cx, obj_1) )
        {
            JS::RootedObject jsArr(cx);
            bool ok = args.get(1).isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, args.get(1)), &jsArr );
            JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam : Error processing arguments");
            
            uint32_t len = 0;
            JS_GetArrayLength(cx, jsArr, &len);
            CCLOG("param len: %d", len);
            for (uint32_t i=0; i < len; i++)
            {
                JS::RootedValue value(cx);
                if (JS_GetElement(cx, jsArr, i, &value))
                {
                    if (value.isObject())
                    {
                        JS::RootedObject jsobj(cx, value.toObjectOrNull());
                        js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                        PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                        params.push_back(pobj_2);
                    }
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++)
            {
                JS::RootedObject jsobj(cx, args.get(i).toObjectOrNull());
                js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
        bool ret = cobj->callBoolFuncWithParam(arg0.c_str(), params);
        JS::RootedValue jsret(cx, BOOLEAN_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFloatFuncWithParam, param count:%d.\n", argc);
    bool ok = true;
    if(argc == 1){
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());
        double ret = cobj->callFloatFuncWithParam(arg0.c_str(), NULL);
        JS::RootedValue jsret(cx, DOUBLE_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
    else if (argc == 0) {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
        std::string arg0;
        ok &= jsval_to_std_string(cx, JS::RootedValue(cx, args.get(0)), &arg0);
        CCLOG("arg0: %s\n", arg0.c_str());

        std::vector<PluginParam*> params;
        
        JS::RootedObject obj_1(cx, args.get(1).toObjectOrNull());
        if ( JS_IsArrayObject(cx, obj_1) )
        {
            JS::RootedObject jsArr(cx);
            bool ok = args.get(1).isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, args.get(1)), &jsArr );
            JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam : Error processing arguments");
            
            uint32_t len = 0;
            JS_GetArrayLength(cx, jsArr, &len);
            CCLOG("param len: %d", len);
            for (uint32_t i=0; i < len; i++)
            {
                JS::RootedValue value(cx);
                if (JS_GetElement(cx, jsArr, i, &value))
                {
                    if (value.isObject())
                    {
                        JS::RootedObject jsobj(cx, value.toObjectOrNull());
                        js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                        PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                        params.push_back(pobj_2);
                    }
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++)
            {
                JS::RootedObject jsobj(cx, args.get(i).toObjectOrNull());
                js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
                PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
        double ret = cobj->callFloatFuncWithParam(arg0.c_str(), params);
        JS::RootedValue jsret(cx, DOUBLE_TO_JSVAL(ret));
        args.rval().set(jsret);
        return true;
    }
}

static bool jsb_anysdk_framework_AgentManager_getIAPPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);

    if (argc != 0)
    {
        CCLOG("AgentManager_getIAPPlugin param number is wrong.");
        return false;
    }
    std::map<std::string , ProtocolIAP*>* plugins = cobj->getIAPPlugin();
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));

    for (auto iter = plugins->begin(); iter != plugins->end(); ++iter)
    {
        JS::RootedValue dictElement(cx);

        std::string key = std::string(iter->first);
        CCLOG("iap key: %s.", key.c_str());
        ProtocolIAP* iap_plugin = (ProtocolIAP*)(iter->second);

        js_proxy_t *jsProxy = js_get_or_create_proxy<ProtocolIAP>(cx, (ProtocolIAP*)iap_plugin);
        dictElement = OBJECT_TO_JSVAL(jsProxy->obj);

        JS_SetProperty(cx, jsretArr, key.c_str(), dictElement);
    }
    JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(jsretArr));
    args.rval().set(jsret);

    return true;
}
static bool jsb_anysdk_framework_AgentManager_getFrameworkVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);
    
    if (argc != 0)
    {
        CCLOG("AgentManager_getIAPPlugin param number is wrong.");
        return false;
    }
    
    args.rval().set(JS::RootedValue(cx, std_string_to_jsval(cx, cobj->getFrameworkVersion())));
    return true;

}

class ProtocolAdsResultListener : public AdsListener
{
public:
    ProtocolAdsResultListener()
    {
    }
    ~ProtocolAdsResultListener()
    {
        CCLOG("on ads result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
        CCLOG("on ads result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points) 
    {
        CCLOG("on player get points: %d.", points);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        js_proxy_t *proxy = js_get_or_create_proxy(_ctx, pAdsPlugin);
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( OBJECT_TO_JSVAL(proxy->obj) );
            valArr.append( INT_TO_JSVAL(points) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }

    static ProtocolAdsResultListener* _instance;
    static ProtocolAdsResultListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new (std::nothrow) ProtocolAdsResultListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};
ProtocolAdsResultListener* ProtocolAdsResultListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    if (ProtocolAdsResultListener::_instance != NULL)
        return true;

    ProtocolAdsResultListener* listener = ProtocolAdsResultListener::getInstance();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setAdsListener(listener);
    return true;
}

static bool jsb_anysdk_framework_ProtocolAds_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolAds_removeListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolAdsResultListener::_instance != NULL)
    {
        ProtocolAdsResultListener::purge();
    }
    if(argc != 0)
        CCLOG("ProtocolAds_removeListener has wrong number of arguments.");
    return true;
}

static bool jsb_anysdk_framework_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAnalytics* cobj = (ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);

    JS::RootedValue arg0(cx, args.get(0));
    std::string arg;
    bool ok = jsval_to_std_string(cx, arg0, &arg);
    CCLOG("logevent, argc: %d, str: %s.", argc, arg.c_str());
    if (!ok)
    {
        CCLOG("ProtocolAnalytics_logEvent param type is wrong.");
        return false;
    }
    if (argc == 1)
    {
        cobj->logEvent(arg.c_str());
        return true;
    }
    else if(argc == 2)
    {
        if (!args.get(1).isObject() || args.get(1).isNullOrUndefined()) {
            CCLOG("%s", "jsval_to_stdmap: the jsval is not an object.");
            return false;
        }

        LogEventParamMap params;
        bool ok = jsval_to_TProductInfo(cx, arg0, &params);
        JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_ProtocolAnalytics_logEvent : Error processing arguments");
        
        cobj->logEvent(arg.c_str(), &params);

        return true;
    }
    JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAnalytics_logEvent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return true;
}

class ProtocolIAPResultListener : public PayResultListener
{
public:
    ProtocolIAPResultListener()
    {
    }
    ~ProtocolIAPResultListener()
    {
        CCLOG("on IAP result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onPayResult(PayResultCode code, const char* msg, TProductInfo info)
    {
        CCLOG("ProtocolIAPResultListener:on pay result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            std::string vec="{";
            for (auto iter = info.begin(); iter != info.end(); ++iter)
            {
                std::string key = std::string(iter->first);
                std::string value = (std::string)(iter->second);
                // CCLOG("productInfo key: %s, value: %s.", key.c_str(), value.c_str());
                vec += key + ":" +value+ ",";
            }
            vec.replace(vec.length() - 1, 1, "}");
            
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            valArr.append( std_string_to_jsval(_ctx, vec) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(3, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    
    virtual void onRequestResult(RequestResultCode code, const char* msg, AllProductsInfo info)
    {
        CCLOG("ProtocolIAPResultListener:on request result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            string value = "{";
            map<string, TProductInfo >::iterator iterParent;
            iterParent = info.begin();
            while(iterParent != info.end())
            {
                value.append(iterParent->first);
                value.append("={");
                map<string, string> infoChild = iterParent->second;
                map<string, string >::iterator iterChild;
                iterChild = infoChild.begin();
                while(iterChild != infoChild.end())
                {
                    value.append(iterChild->first);
                    value.append("=");
                    value.append(iterChild->second);
                    iterChild++;
                    if(iterChild != infoChild.end())
                        value.append(", ");
                }
                iterParent++;
                if(iterParent != info.end())
                    value.append("}, ");
            }
            value.append("}");

            
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            valArr.append( std_string_to_jsval(_ctx, value) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(3, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }

    typedef std::map<std::string, ProtocolIAPResultListener*> STD_MAP;
    static STD_MAP std_map;
    static ProtocolIAPResultListener* getListenerByKey(std::string key)
    {
        auto listener = std_map[key];
        if (listener == NULL) {
            listener = new (std::nothrow) ProtocolIAPResultListener();
            std_map[key] = listener;
        }
        return listener;
    }
    static void purge(std::string key)
    {
        auto listener = std_map[key];
        delete listener;
        listener = NULL;
        std_map.erase(key);
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};
ProtocolIAPResultListener::STD_MAP ProtocolIAPResultListener::std_map;

static bool jsb_anysdk_framework_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return true;
    }
    std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] == NULL)
    {
        CCLOG("will set listener:");
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::getListenerByKey(p_id);
        listener->setJSCallbackFunc( cx, args.get(0) );
        listener->setJSCallbackThis( cx, args.get(1) );
        listener->setJSCallbackCtx( cx, obj );
        cobj->setResultListener(listener);
    }

    return true;
}

static bool jsb_anysdk_framework_ProtocolIAP_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolIAP_removeListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] != NULL)
    {
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::std_map[p_id];
        listener->purge(p_id);
    }
    if(argc != 0)
        CCLOG("ProtocolIAP_removeListener has wrong number of arguments.");
    return true;
}

static bool jsb_anysdk_framework_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolIAP_payForProduct, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 1)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolIAP_payForProduct : wrong number of arguments: %d, was expecting %d", argc, 0);
        return true;
    }
    JS::RootedValue arg0(cx, args.get(0));
    if ( arg0.isObject() ){
        if (arg0.isNullOrUndefined()) {
            CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
            return true;
        }
        
        TProductInfo arg;
        bool ok = jsval_to_TPaymentInfo(cx, arg0, &arg);
        JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_ProtocolIAP_payForProduct : Error processing arguments");
        
        cobj->payForProduct( arg );
    }
    return true;
}

class ProtocolPushActionListener : public PushActionListener
{
public:
    ProtocolPushActionListener()
    {
    }
    ~ProtocolPushActionListener()
    {
        CCLOG("on Push result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
    {
        CCLOG("on push result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        js_proxy_t *proxy = js_get_or_create_proxy(_ctx, pPlugin);
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( OBJECT_TO_JSVAL(proxy->obj) );
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(3, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }

    static ProtocolPushActionListener* _instance;
    static ProtocolPushActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new (std::nothrow) ProtocolPushActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};
ProtocolPushActionListener* ProtocolPushActionListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolPush_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    if (ProtocolPushActionListener::_instance != NULL)
        return true;
    ProtocolPushActionListener* listener = ProtocolPushActionListener::getInstance();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setActionListener(listener);
    return true;
}

static bool jsb_anysdk_framework_ProtocolPush_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolPush_removeListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolPushActionListener::_instance != NULL)
    {
        ProtocolPushActionListener::purge();
    }
    if(argc != 0)
        CCLOG("ProtocolPush_removeListener has wrong number of arguments.");
    return true;
}

static bool jsb_anysdk_framework_ProtocolPush_setTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setTags : wrong number of arguments: %d, was expecting %d", argc, 0);
        return true;
    }
    JS::RootedValue arg0(cx, args.get(0));
    if ( arg0.isObject() ){
        list<std::string> arg;
        JS::RootedObject jsobj(cx, arg0.toObjectOrNull());
        JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");

        uint32_t len;
        JS_GetArrayLength(cx, jsobj, &len);
        
        for( uint32_t i=0; i< len;i++ ) {
            JS::RootedValue valarg(cx);
            JS_GetElement(cx, jsobj, i, &valarg);

            if( valarg.isString() )
            {
                CCLOG("value is string;");
                std::string key;
                bool ok = jsval_to_std_string(cx, valarg, &key);
                if (ok)
                {
                    CCLOG("key: %s.", key.c_str());
                    arg.push_back( key );
                }
            }
        }
        cobj->setTags(arg);
    }
    else {
        CCLOG("settags: is not object.");
    }
    return true;
}

static bool jsb_anysdk_framework_ProtocolPush_delTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_delTags : wrong number of arguments: %d, was expecting %d", argc, 0);
        return true;
    }
    JS::RootedValue arg0(cx, args.get(0));
    if ( arg0.isObject() ){
        list<std::string> arg;
        JS::RootedObject jsobj(cx, arg0.toObjectOrNull());
        JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");

        uint32_t len;
        JS_GetArrayLength(cx, jsobj, &len);
        
        for( uint32_t i=0; i< len;i++ ) {
            JS::RootedValue valarg(cx);
            JS_GetElement(cx, jsobj, i, &valarg);

            if( valarg.isString() )
            {
                CCLOG("value is string;");
                std::string key;
                bool ok = jsval_to_std_string(cx, valarg, &key);
                if (ok)
                {
                    CCLOG("key: %s.", key.c_str());
                    arg.push_back( key );
                }
            }
        }
        cobj->delTags(arg);
    }
    return true;
}

class ProtocolUserActionListener : public UserActionListener
{
public:
    ProtocolUserActionListener()
    {
    }
    ~ProtocolUserActionListener()
    {
        CCLOG("on user action result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
    {
        CCLOG("on user action result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());

        js_proxy_t *proxy = js_get_or_create_proxy(_ctx, pPlugin);
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( OBJECT_TO_JSVAL(proxy->obj) );
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );

            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(3, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }

    static ProtocolUserActionListener* _instance;
    static ProtocolUserActionListener* getInstance(){
        if (_instance == NULL){
            _instance = new (std::nothrow) ProtocolUserActionListener();
        }
        return _instance;
    }
    static void purge(){
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};
ProtocolUserActionListener* ProtocolUserActionListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolUser_setActionListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolUser_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    if (ProtocolUserActionListener::_instance != nullptr)
        return true;
    ProtocolUserActionListener* listener = ProtocolUserActionListener::getInstance();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setActionListener(listener);
    return true;
}
static bool jsb_anysdk_framework_ProtocolUser_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolUser_removeListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolUserActionListener::_instance != NULL)
    {
        ProtocolUserActionListener::purge();
    }
    if(argc != 0)
        CCLOG("ProtocolUser_removeListener has wrong number of arguments.");
    return true;
}

class ProtocolSocialListener : public SocialListener
{
public:
    ProtocolSocialListener()
    {
    }
    ~ProtocolSocialListener()
    {
        CCLOG("on social result ~listener");
        _jsCallback.destroyIfConstructed();
        _jsThisObj.destroyIfConstructed();
        _ctxObj.destroyIfConstructed();
    }

    virtual void onSocialResult(SocialRetCode code, const char* msg)
    {
        CCLOG("on action result: %d, msg: %s.", code, msg);
        JS::RootedObject thisObj(_ctx, _jsThisObj.ref().get().toObjectOrNull());
        JSAutoCompartment ac(_ctx, _ctxObj.ref());
        
        JS::RootedValue retval(_ctx);
        if (!_jsCallback.ref().get().isNullOrUndefined())
        {
            JS::AutoValueVector valArr(_ctx);
            valArr.append( INT_TO_JSVAL(code) );
            valArr.append( std_string_to_jsval(_ctx, msg) );
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr.begin());
            JS_CallFunctionValue(_ctx, thisObj, _jsCallback.ref(), args, &retval);
        }
    }
    
    void setJSCallbackThis(JSContext *cx, JS::HandleValue jsThisObj)
    {
        _jsThisObj.construct(cx, jsThisObj);
    }
    void setJSCallbackFunc(JSContext *cx, JS::HandleValue func) {
        _jsCallback.construct(cx, func);
    }
    void setJSCallbackCtx(JSContext *ctx, JS::HandleObject ctxObj) {
        _ctx = ctx;
        _ctxObj.construct(ctx, ctxObj);
    }

    static ProtocolSocialListener* _instance;
    static ProtocolSocialListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new (std::nothrow) ProtocolSocialListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    mozilla::Maybe<JS::PersistentRootedValue> _jsCallback;
    mozilla::Maybe<JS::PersistentRootedValue> _jsThisObj;
    mozilla::Maybe<JS::PersistentRootedObject> _ctxObj;
    JSContext* _ctx;
};
ProtocolSocialListener* ProtocolSocialListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolSocial_setListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_setListener : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    if (ProtocolSocialListener::_instance != NULL)
        return true;
    ProtocolSocialListener* listener = ProtocolSocialListener::getInstance();
    listener->setJSCallbackFunc( cx, args.get(0) );
    listener->setJSCallbackThis( cx, args.get(1) );
    listener->setJSCallbackCtx( cx, obj );
    cobj->setListener(listener);
    return true;
}

static bool jsb_anysdk_framework_ProtocolSocial_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolSocial_removeListener, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolSocialListener::_instance != NULL)
    {
        ProtocolSocialListener::purge();
    }
    if(argc != 0)
        CCLOG("ProtocolSocial_removeListener has wrong number of arguments.");
    return true;
}

static bool jsb_anysdk_framework_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("in ProtocolSocial_unlockAchievement, argc:%d.", argc);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
        JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_unlockAchievement : wrong number of arguments: %d, was expecting %d", argc, 0);
        return false;
    }
    JS::RootedValue arg0(cx, args.get(0));
    if ( arg0.isObject() ){
        if (arg0.isNullOrUndefined()) {
            CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
            return false;
        }
        
        TAchievementInfo arg;
        bool ok = jsval_to_TAchievementInfo(cx, arg0, &arg);
        JSB_PRECONDITION2(ok, cx, false, "jsb_anysdk_framework_ProtocolSocial_unlockAchievement : Error processing arguments");
        
        cobj->unlockAchievement( arg );
    }
    return true;
}

JSClass  *jsb_anysdk_framework_JSBRelation_class;
JSObject *jsb_anysdk_framework_JSBRelation_prototype;

bool js_anysdk_framework_JSBRelation_getMethodsOfPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    if (argc == 1) {
        anysdk::framework::PluginProtocol* plugin;
        JS::RootedObject arg0(cx, args.get(0).toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(arg0);
        plugin = (anysdk::framework::PluginProtocol*)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2( plugin, cx, false, "Invalid Native Object");
        std::string ret = JSBRelation::getMethodsOfPlugin(plugin);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_JSBRelation_getMethodsOfPlugin : wrong number of arguments");
    return false;
}

void js_anysdk_framework_JSBRelation_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JSBRelation)", obj);
    js_proxy_t* nproxy;
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    js_proxy_t* proxy = jsb_get_js_proxy(jsobj);
    if (proxy) {
        auto nobj = static_cast<JSBRelation *>(proxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(proxy);
    }
}

void js_register_anysdk_framework_JSBRelation(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_JSBRelation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_JSBRelation_class->name = "JSBRelation";
    jsb_anysdk_framework_JSBRelation_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_JSBRelation_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_JSBRelation_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_JSBRelation_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_JSBRelation_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_JSBRelation_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_JSBRelation_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_JSBRelation_class->finalize = js_anysdk_framework_JSBRelation_finalize;
    jsb_anysdk_framework_JSBRelation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("getMethodsOfPlugin", js_anysdk_framework_JSBRelation_getMethodsOfPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    jsb_anysdk_framework_JSBRelation_prototype = JS_InitClass(
                                                              cx, global,
                                                              JS::NullPtr(), // parent proto
                                                              jsb_anysdk_framework_JSBRelation_class,
                                                              dummy_constructor<JSBRelation>, 0, // no constructor
                                                              properties,
                                                              funcs,
                                                              NULL, // no static properties
                                                              st_funcs);
    
    JS::RootedObject proto(cx, jsb_anysdk_framework_JSBRelation_prototype);
    jsb_register_class<anysdk::framework::JSBRelation>(cx, jsb_anysdk_framework_JSBRelation_class, proto, JS::NullPtr());
}

extern JSObject* jsb_anysdk_framework_PluginProtocol_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolIAP_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolAnalytics_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolAds_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolSocial_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolPush_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolUser_prototype;
extern JSObject* jsb_anysdk_framework_AgentManager_prototype;
extern JSObject *jsb_anysdk_framework_JSBRelation_prototype;

void register_all_anysdk_manual(JSContext* cx, JS::HandleObject obj) {
    JS::RootedObject anysdkObj(cx);
    JS::RootedObject proto(cx);
    get_or_create_js_obj(cx, obj, "anysdk", &anysdkObj);

    js_register_anysdkbindings_PluginParam(cx, anysdkObj);
    js_register_anysdkbindings_ProtocolShare(cx, anysdkObj);
    js_register_anysdk_framework_JSBRelation(cx, anysdkObj);

    //PluginProtocol
    proto.set(jsb_anysdk_framework_PluginProtocol_prototype);
    JS_DefineFunction(cx, proto, "callFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "callStringFuncWithParam", jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "callIntFuncWithParam", jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "callBoolFuncWithParam", jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "callFloatFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //AgentManager
    proto.set(jsb_anysdk_framework_AgentManager_prototype);
    JS_DefineFunction(cx, proto, "getIAPPlugin", jsb_anysdk_framework_AgentManager_getIAPPlugin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "getFrameworkVersion", jsb_anysdk_framework_AgentManager_getFrameworkVersion, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //ProtocolAds
    proto.set(jsb_anysdk_framework_ProtocolAds_prototype);
    JS_DefineFunction(cx, proto, "setAdsListener", jsb_anysdk_framework_ProtocolAds_setAdsListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "removeListener", jsb_anysdk_framework_ProtocolAds_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //ProtocolAnalytics
    proto.set(jsb_anysdk_framework_ProtocolAnalytics_prototype);
    JS_DefineFunction(cx, proto, "logEvent", jsb_anysdk_framework_ProtocolAnalytics_logEvent, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //ProtocolIAP
    proto.set(jsb_anysdk_framework_ProtocolIAP_prototype);
    JS_DefineFunction(cx, proto, "setResultListener", jsb_anysdk_framework_ProtocolIAP_setResultListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "removeListener", jsb_anysdk_framework_ProtocolIAP_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "payForProduct", jsb_anysdk_framework_ProtocolIAP_payForProduct, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    //ProtocolSocial
    proto.set(jsb_anysdk_framework_ProtocolSocial_prototype);
    JS_DefineFunction(cx, proto, "setListener", jsb_anysdk_framework_ProtocolSocial_setListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "removeListener", jsb_anysdk_framework_ProtocolSocial_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "unlockAchievement", jsb_anysdk_framework_ProtocolSocial_unlockAchievement, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //ProtocolPush
    proto.set(jsb_anysdk_framework_ProtocolPush_prototype);
    JS_DefineFunction(cx, proto, "setActionListener", jsb_anysdk_framework_ProtocolPush_setActionListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "removeListener", jsb_anysdk_framework_ProtocolPush_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "setTags", jsb_anysdk_framework_ProtocolPush_setTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "delTags", jsb_anysdk_framework_ProtocolPush_delTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    //ProtocolUser
    proto.set(jsb_anysdk_framework_ProtocolUser_prototype);
    JS_DefineFunction(cx, proto, "setActionListener", jsb_anysdk_framework_ProtocolUser_setActionListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "removeListener", jsb_anysdk_framework_ProtocolUser_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

void pure_all_anysdk_Listener()
{
    ProtocolUserActionListener::purge();
    ProtocolPushActionListener::purge();
    ProtocolSocialListener::purge();
    ProtocolAdsResultListener::purge();
}
