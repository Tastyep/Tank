#ifndef TIMEHANDLING_H
#define TIMEHANDLING_H

#include <chrono>
#include <thread>

class TimeHandling {
public:
  TimeHandling(const std::chrono::milliseconds &targetFrameDuration =
                   std::chrono::milliseconds(16));
  ~TimeHandling() = default;

  const std::chrono::microseconds &GetTotalElapsed() const {
    return this->totalElapsed;
  };

  std::chrono::milliseconds GetTargetFrameDuration() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        this->targetFrameDuration);
  };

  std::chrono::milliseconds GetLag() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(this->lag);
  };

  unsigned long int GetNumberOfFrame() const { return this->nbFrame; };

  void SetTargetFrameDuration(const std::chrono::milliseconds &tfd) {
    this->targetFrameDuration =
        std::chrono::duration_cast<std::chrono::microseconds>(tfd);
  };

  void start();
  void endFrame();

protected:
private:
  std::chrono::time_point<std::chrono::system_clock> startTime;
  std::chrono::microseconds targetFrameDuration;
  std::chrono::microseconds totalElapsed;
  std::chrono::microseconds lag;
  unsigned long int nbFrame;
};

#endif // TIMEHANDLING_H
