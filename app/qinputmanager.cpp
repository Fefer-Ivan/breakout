#include "qinputmanager.h"
#include <QKeyEvent>
#include <algorithm>
#include <iterator>

namespace breakout {

namespace {

constexpr std::array<Qt::Key, 2> kNegativeHorizontalKeys{Qt::Key_Left, Qt::Key_A};
constexpr std::array<Qt::Key, 2> kPositiveHorizontalKeys{Qt::Key_Right, Qt::Key_D};

template<typename Container, typename Value>
auto contains(const Container& container, const Value& value) {
  return std::count(std::begin(container), std::end(container), value) > 0;
}

}  // namespace

void QInputManager::press_key(int key) {
  if (update_counters(key, 1)) {
    update_horizontal_axis();
  }
}

void QInputManager::release_key(int key) {
  if (update_counters(key, -1)) {
    update_horizontal_axis();
  }
}

bool QInputManager::update_counters(int key, int modificator) {
  if (contains(kNegativeHorizontalKeys, key)) {
    negative_horizontal_keys_count_ += modificator;
    return true;
  }
  if (contains(kPositiveHorizontalKeys, key)) {
    positive_horizontal_keys_count_ += modificator;
    return true;
  }
  return false;
}

void QInputManager::update_horizontal_axis() {
  double axis = 0.0;
  if (positive_horizontal_keys_count_ > 0) {
    axis += 1;
  }
  if (negative_horizontal_keys_count_ > 0) {
    axis -= 1;
  }
  set_horizontal_axis(axis);
}

}  // namespace breakout

