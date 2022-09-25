#include "application_settings.h"

int main(int argc, char *argv[]) {

  // Set some examples for the settings
  ApplicationSettings settings;

  settings.id = 1;
  settings.log_level = "debug";
  settings.input_file.filename = "input.txt";
  settings.input_file.time = 999;

  settings.position_x = 1.0f;
  settings.position_x = -1.5f;
  settings.position_x = 2.5f;

  settings.ips = {"127.0.0.1", "192.168.1.0"};

  ApplicationSettings::File file_1;
  file_1.filename = "image_0.jpeg";
  file_1.time = 100;

  ApplicationSettings::File file_2;
  file_2.filename = "image_1.jpeg";
  file_2.time = 150;

  settings.files.push_back(file_1);
  settings.files.push_back(file_2);

  // Write the settings to disk
  settings.write("settings.xml");

  // Read the settings from the newly created file settings.xml
  auto app_settings = ApplicationSettings::read("settings.xml");
  return 0;
}