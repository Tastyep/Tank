#include "TimeHandling.hpp"

TimeHandling::TimeHandling(const std::chrono::milliseconds &targetFrameDuration)
    : targetFrameDuration(std::chrono::duration_cast<std::chrono::microseconds>(
          targetFrameDuration)),
      totalElapsed(0), lag(0), nbFrame(0) {}

void TimeHandling::start() {
  this->startTime = std::chrono::system_clock::now();
}

void TimeHandling::endFrame() {
  std::chrono::microseconds elapsed;

  std::chrono::time_point<std::chrono::system_clock> end =
      std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
      end - this->startTime);
  this->startTime = end;
  this->totalElapsed += elapsed;
  this->nbFrame += 1;
  this->lag += elapsed;
  if (this->lag < this->targetFrameDuration)
    std::this_thread::sleep_for(this->targetFrameDuration);
  this->lag -= this->targetFrameDuration;
}
