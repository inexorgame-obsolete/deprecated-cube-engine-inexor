requires = (("InexorGlueGen/0.6.0alpha@inexorgame/testing"),
            ("Protobuf/3.1.0@inexorgame/stable"),
            ("gRPC/1.1.0-dev@inexorgame/stable"),
            ("doxygen/1.8.13@inexorgame/testing"),
            ("Boost/1.60.0@lasote/stable"),
            ("RapidJSON/1.0.2@inexorgame/stable"),
            ("zlib/1.2.8@lasote/stable"),
            ("gtest/1.7.0@lasote/stable"),
            ("ENet/1.3.13@inexorgame/stable"),
            ("spdlog/0.10.0@memsharded/stable"),
            ("SDL2/2.0.5@lasote/stable"),
            ("SDL2_image/2.0.1@lasote/stable"),
            ("CEF/3.2704.1424.gc3f0a5b@a_teammate/testing")
        )

options = '''
  zlib:shared=False
  gtest:shared=False
  ENet:shared=False
  Boost:shared=False
  SDL2:shared=False
  SDL2_image:shared=False
'''
