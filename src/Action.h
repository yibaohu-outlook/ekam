// ekam -- http://code.google.com/p/ekam
// Copyright (c) 2010 Kenton Varda and contributors.  All rights reserved.
// Portions copyright Google, Inc.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of the ekam project nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef EKAM_ACTION_H_
#define EKAM_ACTION_H_

#include <string>
#include <vector>
#include <sys/types.h>

#include "OwnedPtr.h"
#include "File.h"
#include "Entity.h"
#include "EventManager.h"

namespace ekam {

class ProcessExitCallback {
public:
  virtual ~ProcessExitCallback();

  // Negative = signal number.
  virtual void done(int exit_status) = 0;
};

class BuildContext {
public:
  virtual ~BuildContext();

  virtual File* findProvider(EntityId id, const std::string& title) = 0;
  virtual File* findOptionalProvider(EntityId id) = 0;

  virtual void provide(File* file, const std::vector<EntityId>& entities) = 0;
  virtual void log(const std::string& text) = 0;

  virtual void newOutput(const std::string& basename, OwnedPtr<File>* output) = 0;

  virtual void success() = 0;
  virtual void passed() = 0;
  virtual void failed() = 0;
};

class Action {
public:
  virtual ~Action();

  virtual std::string getVerb() = 0;
  virtual void start(EventManager* eventManager, BuildContext* context) = 0;
};

class ActionFactory {
public:
  virtual ~ActionFactory();

  virtual bool tryMakeAction(File* file, OwnedPtr<Action>* output) = 0;
  virtual void enumerateTriggerEntities(std::back_insert_iterator<std::vector<EntityId> > iter) = 0;
  virtual bool tryMakeAction(const EntityId& id, File* file, OwnedPtr<Action>* output) = 0;
};

}  // namespace ekam

#endif  // EKAM_ACTION_H_