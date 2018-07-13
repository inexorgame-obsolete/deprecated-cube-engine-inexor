requires = (
    ("InexorGlueGen/0.6.8@inexorgame/stable"),
    ("protobuf/3.5.2@bincrafters/stable"),
    ("gRPC/1.9.1@inexorgame/stable"),
    ("doxygen/1.8.13@inexorgame/stable"),
    ("Boost/1.66.0@conan/stable"),
    ("zlib/1.2.11@conan/stable"),
    ("gtest/1.8.0@bincrafters/stable"),
    ("enet/1.3.13@bincrafters/stable"),
    ("spdlog/0.17.0@bincrafters/stable"),
    ("sdl2/2.0.8@bincrafters/testing"),  # not self-contained
    ("sdl2_image/2.0.3@bincrafters/stable"),
    ("CEF/3.3239.1709.g093cae4@inexorgame/testing")  # not self-contained
)

options = '''
  zlib:shared=False
  gtest:shared=False
  gtest:build_gmock=False
  enet:shared=False
  Boost:shared=False
  sdl2:shared=False
  sdl2_image:shared=False
  spdlog:fmt_external=True
  protobuf:with_zlib=True
'''
