//
// Created by Billy Wooton on 10/11/17.
//

#include "shaka_scheme/system/vm/Closure.hpp"

namespace shaka {

Closure::Closure(EnvPtr env,
                 NodePtr fb,
                 VariableList vl,
                 CallablePtr cl,
                 FramePtr frame) :
    env(env),
    func_body(fb),
    variable_list(vl),
    callable(cl),
    frame(frame) {}

NodePtr Closure::get_function_body() {
  return this->func_body;
}

void Closure::extend_environment(ValueRib vr) {
  for (size_t i = 0; i < variable_list.size(); i++) {
    env->set_value(variable_list[i], vr[i]);
  }
}

EnvPtr Closure::get_environment() {
  return this->env;
}

std::vector<NodePtr> Closure::call(std::vector<NodePtr> args) {
  return (*callable)(args);
}

FramePtr Closure::get_call_frame() {
  return this->frame;
}

VariableList Closure::get_variable_list() {
  return this->variable_list;
}

bool Closure::is_native_closure() {
  return this->callable != nullptr;
}

bool Closure::is_continuation_closure() {
  return this->frame != nullptr;
}


}