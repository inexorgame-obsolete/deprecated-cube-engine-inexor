requires = (
    ("InexorGlueGen/0.6.8@inexorgame/stable"),
    ("protobuf/3.5.1@bincrafters/stable"),
    ("gRPC/1.9.1@inexorgame/stable"),
    ("doxygen/1.8.13@inexorgame/stable"),
    ("Boost/1.66.0@conan/stable"),
    ("zlib/1.2.11@conan/stable"),
    ("gtest/1.8.0@bincrafters/stable"),
    ("ENet/1.3.13@inexorgame/stable"),
    ("spdlog/0.16.3@bincrafters/stable"),
        ("fmt/4.1.0@bincrafters/stable"),  # fix version to make it re-producable, remove at next spdlog update
    ("sdl2/2.0.8@bincrafters/testing"),  # not self-contained
    ("sdl2_image_lowercase/2.0.1@inexorgame/stable"),  # todo: unfork
        ("libpng/1.6.34@bincrafters/stable"),  # override for Conan >= 0.30.0 compatibility
        ("libjpeg-turbo/1.5.2@bincrafters/stable"),  # override for Conan >= 0.30.0 compatibility
    ("CEF/3.3239.1709.g093cae4@inexorgame/testing")  # not self-contained
)

options = '''
  zlib:shared=False
  gtest:shared=False
  gtest:build_gmock=False
  ENet:shared=False
  Boost:shared=False
  SDL2:shared=False
  SDL2_image:shared=False
  spdlog:fmt_external=True
  protobuf:with_zlib=True
'''
