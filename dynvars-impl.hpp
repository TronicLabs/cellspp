// Copyright 2012, Matthias Andreas Benkard.
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#ifndef DYNVARS_IMPL_HPP
#define DYNVARS_IMPL_HPP

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <functional>
#include <memory>
#include <future>
#include <list>

#include "dynvars.hpp"

namespace dynvars {

using namespace ::std;

template <typename T>
dynvar<T>::dynvar(T val) {
  this->push(val);
}

template <typename T>
dynvar<T>& dynvar<T>::operator =(T val) {
  if (!value_stack.empty()) {
    this->pop();
  }
  this->push(val);
  return *this;
}

template <typename T>
void dynvar<T>::push(T val) {
  value_stack.push_front(val);
}

template <typename T>
void dynvar<T>::pop() {
  value_stack.pop_front();
}

template <typename T>
dynvar<T>::operator bool() const {
  return !value_stack.empty();
}

template <typename T>
T& dynvar<T>::operator *() {
  return value_stack.front();
}

template <typename T>
T* dynvar<T>::operator ->() {
  return &value_stack.front();
}

template <typename R>
dyn<R>::dyn(dynvar<R>& var, R val) : myvar(var) {
  myvar.push(val);
}

template <typename R>
dyn<R>::~dyn() {
  myvar.pop();
}

template <typename R, typename T>
T
with(dynvar<R>& var, R val, function<T ()> f) {
  dyn<R> d_(var, val);
  return f();
}

}

#endif //DYNVARS_IMPL_HPP
