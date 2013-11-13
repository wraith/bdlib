#ifndef BD_SCRIPTINTERPTCLCALLBACKS_H
#define BD_SCRIPTINTERPTCLCALLBACKS_H

#include "indices.h"

/**
 * @class ScriptCallbackDispatchTCL
 * @brief Execute the callback and set the return type
 */
template <typename ReturnType, typename... Params>
struct ScriptCallbackDispatchTCL {
  typedef ReturnType (*function_t)(Params...);
  static inline void dispatch(Tcl_Interp* interp, function_t callback, Params&&... args) {
    ReturnType result = std::move(callback(std::forward<Params>(args)...));
    Tcl_SetObjResult(interp, std::move(c_to_tcl_cast<ReturnType>::from(std::move(result))));
  }
};

// Specialize for void return-type
template <typename... Params>
struct ScriptCallbackDispatchTCL<void, Params...> {
  typedef void (*function_t)(Params...);
  static inline void dispatch(Tcl_Interp* interp, function_t callback, Params&&... args) {
    callback(std::forward<Params>(args)...);
  }
};

template <typename ReturnType, typename... Params>
class ScriptCallbackTCL : public ScriptCallbackTCLBase {
  typedef ReturnType (*function_t)(Params...);

  private:
    function_t _callback;

    template<std::size_t... Indices>
    inline void real_call(size_t argc, void* const argv[], void *proxy_data, indices<Indices...>) {
      Tcl_Obj* CONST *objv = reinterpret_cast<Tcl_Obj* CONST *>(argv);
      Tcl_Interp* interp = static_cast<Tcl_Interp*>(proxy_data);
      // Doing argc check to pass default params in if not enough were passed to the handler
      ScriptCallbackDispatchTCL<ReturnType, Params...>::dispatch(interp, _callback,
          (
           ((argc - 1) >= Indices + 1) ?
           (std::move(tcl_to_c_cast<Params>::from(std::move(objv[Indices + 1])))) :
           (std::move(Params()))
          )...
      );
    }

  public:
    ScriptCallbackTCL(function_t callback) : _callback(callback) {};
    inline virtual void call(size_t argc, void* const argv[], ScriptInterp* si, void *proxy_data) {
      real_call(argc, argv, proxy_data, make_indices<sizeof...(Params)>());
    }
};

/**
 * @class ScriptCallbackDispatchTCL
 * @brief Execute the callback and set the return type. This is the same as ScriptCallbackDispatchTCL but it sends in the ScriptInterp as well.
 */
template <typename ReturnType, typename... Params>
struct ScriptCallbackDispatchInterpTCL {
  typedef ReturnType (*function_t)(ScriptInterp*, Params...);
  static inline void dispatch(Tcl_Interp* interp, ScriptInterp* si, function_t callback, Params&&... args) {
    ReturnType result = std::move(callback(si, std::forward<Params>(args)...));
    Tcl_SetObjResult(interp, std::move(c_to_tcl_cast<ReturnType>::from(std::move(result))));
  }
};

// Specialize for void return-type
template <typename... Params>
struct ScriptCallbackDispatchInterpTCL<void, Params...> {
  typedef void (*function_t)(ScriptInterp*, Params...);
  static inline void dispatch(Tcl_Interp* interp, ScriptInterp* si, function_t callback, Params&&... args) {
    callback(si, std::forward<Params>(args)...);
  }
};

/**
 * @class ScriptCallbackInterpTCL
 * @brief Handle calling function from TCL. Same as ScriptCallbackTCL, but passes in ScriptInterp as well
 */
template <typename ReturnType, typename... Params>
class ScriptCallbackInterpTCL : public ScriptCallbackTCLBase {
  typedef ReturnType (*function_t)(ScriptInterp*, Params...);

  private:
    function_t _callback;

    template<std::size_t... Indices>
    inline void real_call(size_t argc, void* const argv[], ScriptInterp* si, void *proxy_data, indices<Indices...>) {
      Tcl_Obj* CONST *objv = reinterpret_cast<Tcl_Obj* CONST *>(argv);
      Tcl_Interp* interp = static_cast<Tcl_Interp*>(proxy_data);
      // Doing argc check to pass default params in if not enough were passed to the handler
      ScriptCallbackDispatchInterpTCL<ReturnType, Params...>::dispatch(interp, si, _callback,
          (
           ((argc - 1) >= Indices + 1) ?
           (std::move(tcl_to_c_cast<Params>::from(std::move(objv[Indices + 1])))) :
           (std::move(Params()))
          )...
      );
    }

  public:
    ScriptCallbackInterpTCL(function_t callback) : _callback(callback) {};
    inline virtual void call(size_t argc, void* const argv[], ScriptInterp* si, void *proxy_data) {
      real_call(argc, argv, si, proxy_data, make_indices<sizeof...(Params)>());
    }
};
#endif
