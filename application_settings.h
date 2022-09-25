#ifndef APPLICATION_SETTINGS_H_
#define APPLICATION_SETTINGS_H_

#include <string>
#include <vector>

class ApplicationSettings {

public:
  struct File {
    std::string filename;
    std::uint64_t time;
  };

  int id;
  std::string log_level;
  File input_file;
  float position_x;
  float position_y;
  float position_z;
  std::vector<std::string> ips;
  std::vector<File> files;

  void write(const std::string &filepath);

  static ApplicationSettings read(const std::string &filepath);

private:
  const static std::string KEY_ID;
  const static std::string KEY_LOG_LEVEL;

  const static std::string KEY_INPUT_FILE;
  const static std::string KEY_TIMESTAMP_ATTR;

  const static std::string KEY_POSITION_X;
  const static std::string KEY_POSITION_Y;
  const static std::string KEY_POSITION_Z;

  const static std::string KEY_IP_LIST;
  const static std::string KEY_IP;

  const static std::string KEY_FILE_LIST;
  const static std::string KEY_FILE;
};

#endif // APPLICATION_SETTINGS_H_