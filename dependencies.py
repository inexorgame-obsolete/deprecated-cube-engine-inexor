requires = (
    ("InexorGlueGen/0.6.3@inexorgame/stable"),
    ("Protobuf/3.5.1@inexorgame/stable"),
    ("gRPC/1.8.3@inexorgame/stable"),
    ("doxygen/1.8.13@inexorgame/stable"),
    ("cmake-findboost/0.2.0@bincrafters/stable"),
    ("boost_filesystem/1.66.0@bincrafters/testing"),
    ("boost_program_options/1.66.0@bincrafters/testing"),
    ("boost_random/1.66.0@bincrafters/testing"),
    ("boost_regex/1.66.0@bincrafters/testing"),
    ("boost_system/1.66.0@bincrafters/testing"),
    ("boost_thread/1.66.0@bincrafters/testing"),
    ("RapidJSON/1.1.0@inexorgame/stable"),
    ("zlib/1.2.11@conan/stable"),
    ("gtest/1.8.0@lasote/stable"),
    ("ENet/1.3.13@inexorgame/stable"),
    ("spdlog/0.14.0@bincrafters/stable"),
    ("fmt/4.1.0@bincrafters/stable"),  # spdlog dependency (fix version to make it re-producable)
    ("SDL2/2.0.5@lasote/testing"),  # not self-contained
    ("SDL2_image/2.0.1@lasote/stable"),
    ("libpng/1.6.34@bincrafters/stable"),  # override SDl2_image dep for Conan >= 0.30.0 compatibility
    ("libjpeg-turbo/1.5.2@bincrafters/stable"),  # override SDl2_image dep for Conan >= 0.30.0 compatibility
    ("CEF/3.3239.1709.g093cae4@inexorgame/testing")  # not self-contained
)

options = '''
  zlib:shared=False
  gtest:shared=False
  gtest:no_gmock=True
  ENet:shared=False
  Boost:shared=False
  SDL2:shared=False
  SDL2_image:shared=False
  spdlog:fmt_external=True
'''
