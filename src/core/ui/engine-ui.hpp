#pragma once

#include "core/ui/base.hpp"

namespace otto::ui {

  /**
   * A screen that belongs to a engine of type M
   */
  template<class M>
  class EngineScreen : public Screen {
  protected:
    M* engine;

  public:
    using ptr = std::unique_ptr<EngineScreen<M>>;

    EngineScreen() : Screen(), engine (nullptr){}

    EngineScreen(M* engine) : Screen (), engine (engine) {}

    virtual ~EngineScreen() {}
  };

} // otto::ui
