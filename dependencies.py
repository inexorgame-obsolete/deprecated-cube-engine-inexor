requires = (
    ("InexorGlueGen/0.6.2@inexorgame/stable"),
    ("Protobuf/3.1.0@inexorgame/stable"),
    ("gRPC/1.1.0@inexorgame/stable"),
    ("doxygen/1.8.13@inexorgame/stable"),
    ("cmake-findboost/0.2.0@bincrafters/stable"),
    ("Boost.Filesystem/1.65.1@bincrafters/stable"),
    ("Boost.Program_Options/1.65.1@bincrafters/stable"),
    ("Boost.Random/1.65.1@bincrafters/stable"),
    ("Boost.Regex/1.65.1@bincrafters/stable"),
    ("Boost.System/1.65.1@bincrafters/stable"),
    ("Boost.Thread/1.65.1@bincrafters/stable"),
    ("RapidJSON/1.1.0@inexorgame/stable"),
    ("zlib/1.2.11@conan/stable"),
    ("gtest/1.8.0@lasote/stable"),
    ("ENet/1.3.13@inexorgame/stable"),
    ("spdlog/0.14.0@bincrafters/stable"),
    ("fmt/4.0.0@bincrafters/stable"),
    ("SDL2/2.0.5@lasote/testing"),  # not self-contained
    ("SDL2_image/2.0.1@lasote/stable"),
    ("CEF/3.2704.1424.gc3f0a5b@inexorgame/testing")  # not self-contained
)

options = '''
  zlib:shared=False
  gtest:shared=False
  gtest:no_gmock=True
  ENet:shared=False
  SDL2:shared=False
  SDL2_image:shared=False
  spdlog:fmt_external=True
'''
