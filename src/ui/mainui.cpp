#include "base.h"
#include "mainui.h"
#include "utils.h"
#include "../globals.h"

#include <thread>

void MainUI::display(ui::Screen *screen) {
  currentScreen = screen;
}

void MainUI::init() {
  uiThread = std::thread(MainUI::mainRoutine);
}

void MainUI::exit() {
  uiThread.join();
}

void MainUI::draw(NanoCanvas::Canvas& ctx) {
  using namespace drawing;
  currentScreen->draw(ctx);
}

bool MainUI::keypress(ui::Key key) {
  keys[key] = true;
  if (globKeyPre(key)) return true;
  if (currentScreen->keypress(key)) return true;
  return globKeyPost(key);
}

bool MainUI::keyrelease(ui::Key key) {
  keys[key] = false;
  return currentScreen->keyrelease(key);
}

bool MainUI::globKeyPost(ui::Key key) {
  switch (key) {
  case ui::K_PLAY:
    if (GLOB.tapedeck.playing) {
      GLOB.tapedeck.stop();
    } else {
      GLOB.tapedeck.play(1);
    }
    return true;
  }
  return false;
}

bool MainUI::globKeyPre(ui::Key key) {
  using namespace ui;
  switch (key) {
  case K_QUIT:
    GLOB.running = false;
    break;
  case K_TAPE:
    GLOB.tapedeck.display();
    break;
  case K_MIXER:
    GLOB.mixer.display();
    break;
  default:
    return false;
  }
  return true;
}
