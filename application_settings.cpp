#include "application_settings.h"

#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>
#include <string>

const std::string ApplicationSettings::KEY_ID{"Settings.ID"};
const std::string ApplicationSettings::KEY_LOG_LEVEL{"Settings.LogLevel"};

const std::string ApplicationSettings::KEY_INPUT_FILE{"Settings.InputFile"};
const std::string ApplicationSettings::KEY_TIMESTAMP_ATTR{"<xmlattr>.Timestamp"}; // This is a relative subkey

const std::string ApplicationSettings::KEY_POSITION_X{"Settings.Position.X"};
const std::string ApplicationSettings::KEY_POSITION_Y{"Settings.Position.Y"};
const std::string ApplicationSettings::KEY_POSITION_Z{"Settings.Position.Z"};

const std::string ApplicationSettings::KEY_IP_LIST{"Settings.Banlist"};
const std::string ApplicationSettings::KEY_IP{"IP"}; // This is a relative subkey

const std::string ApplicationSettings::KEY_FILE_LIST{"Settings.Images"};
const std::string ApplicationSettings::KEY_FILE{"File"}; // This is a relative subkey


void ApplicationSettings::write(const std::string &filepath) { 
  boost::property_tree::ptree ptree;

  ptree.put(KEY_ID, id);
  ptree.put(KEY_LOG_LEVEL, log_level);

  ptree.put(KEY_INPUT_FILE, input_file.filename);
  ptree.put(KEY_INPUT_FILE + "." + KEY_TIMESTAMP_ATTR, input_file.time);

  ptree.put(KEY_POSITION_X, position_x);
  ptree.put(KEY_POSITION_Y, position_y);
  ptree.put(KEY_POSITION_Z, position_z);

  std::for_each(ips.begin(), ips.end(), [&ptree](auto& ip) {
    // Use add instead of put
    // 'add' will add a new node with the new value
    // 'put' would override an existing element with the new value
    ptree.add(KEY_IP_LIST + "." + KEY_IP, ip);
  });

  std::for_each(files.begin(), files.end(), [&ptree](auto& file) {
    // Use add instead of put
    // 'add' will add a new node with the new value
    // 'put' would override an existing element with the new value
    auto &y = ptree.add(KEY_FILE_LIST + "." + KEY_FILE, file.filename);
    y.put(KEY_TIMESTAMP_ATTR, file.time);
  });

  // Settings for prettier formatting
  boost::property_tree::xml_parser::xml_writer_settings<std::string> xml_writer_settings(' ', 4, "utf-8");

  boost::property_tree::write_xml(filepath, ptree, std::locale(), xml_writer_settings);
}

ApplicationSettings ApplicationSettings::read(const std::string &filepath) {
  ApplicationSettings settings;

  boost::property_tree::ptree ptree;
  // First read the XML file into a property_tree::ptree
  boost::property_tree::read_xml(filepath, ptree);

  // Get the values from the ptree using "get" and the keys
  settings.id = ptree.get<int>(KEY_ID);
  settings.log_level = ptree.get<std::string>(KEY_LOG_LEVEL);
  settings.input_file.filename = ptree.get<std::string>(KEY_INPUT_FILE);
  settings.input_file.time = ptree.get<std::uint64_t>(KEY_INPUT_FILE + "." + KEY_TIMESTAMP_ATTR);

  settings.position_x = ptree.get<float>(KEY_POSITION_X);
  settings.position_y = ptree.get<float>(KEY_POSITION_Y);
  settings.position_z = ptree.get<float>(KEY_POSITION_Z);

  // Read in a list of XML elements having the same key
  auto& ip_child_nodes = ptree.get_child(KEY_IP_LIST);
  for (boost::property_tree::ptree::value_type& child_node : ip_child_nodes) {
    if (child_node.first == KEY_IP) { // first is the key of the node
     settings.ips.push_back(child_node.second.data()); // second.data() contains the value of the node
    }
  }

  auto& file_child_nodes = ptree.get_child(KEY_FILE_LIST);
  for (boost::property_tree::ptree::value_type& child_node : file_child_nodes) {
    if (child_node.first == KEY_FILE) { // first is the key of the node

      ApplicationSettings::File file;
      file.filename = child_node.second.data(); // second.data() contains the value of the node

      // Attributes are child nodes in the node with the subkey ".<xmlattr>"
      file.time = child_node.second.get<std::uint64_t>(KEY_TIMESTAMP_ATTR);

      settings.files.push_back(file);
    }
  }

  return settings;
}